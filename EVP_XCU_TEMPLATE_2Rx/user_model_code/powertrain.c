/*
 * powertrain.c
 *
 * Fixed order each step:
 *   decode -> redundancy checks -> monitors -> fault manager ->
 *   state machine -> torque request -> safety gate
 *
 * Monitors never touch outputs. Only gate_compute() shapes the command.
 */

#include "powertrain.h"

static void decode_inputs(Powertrain *p, const PtInputs *in)
{
    uint8_t i;
    uint8_t ok;

    if (in->ld_new != 0U) {
        ok = codec_decode_ld(in->ld_data, in->ld_len, &p->ld);
        p->ld_len_ok = ok;
        if (ok != 0U) {
            p->ld_have = 1U;
        }
    }

    for (i = 0U; i < SF_COUNT; i++) {
        if (in->s_new[i] == 0U) {
            continue;
        }
        switch (i) {
        case SF_S1:
            ok = codec_decode_status1(in->s_data[i], in->s_len[i], &p->s1);
            if (ok != 0U) { p->live[i] = p->s1.live; }
            break;
        case SF_S2:
            ok = codec_decode_status2(in->s_data[i], in->s_len[i], &p->s2);
            if (ok != 0U) { p->live[i] = p->s2.live; }
            break;
        case SF_S3:
            ok = codec_decode_status3(in->s_data[i], in->s_len[i], &p->s3);
            if (ok != 0U) { p->live[i] = p->s3.live; }
            break;
        default:
            ok = codec_decode_status4(in->s_data[i], in->s_len[i], &p->live[i]);
            break;
        }
        p->s_len_ok[i] = ok;
        if (ok != 0U) {
            p->s_have[i] = 1U;
        }
    }
}

void pt_init(Powertrain *p, const PowertrainCal *cal, const ThrottleMap *maps, uint16_t step_ms)
{
    uint8_t i;

    p->cal     = cal;
    p->maps    = maps;
    p->step_ms = step_ms;

    p->cal_ok = cal_validate(cal, &p->cal_reason);
    if ((p->cal_ok != 0U) && (maps_validate(maps, cal->torque_max_nm) == 0U)) {
        p->cal_ok     = 0U;
        p->cal_reason = 99U;      /* map out of limits */
    }
    p->step_ok = ((step_ms >= cal->step_ms_min) && (step_ms <= cal->step_ms_max)) ? 1U : 0U;

    mon_init(&p->mon);
    fm_init(&p->fm);
    sm_init(&p->sm);
    tq_init(&p->tq);
    mode_src_init(&p->msrc);

    p->ld_have   = 0U;
    p->ld_len_ok = 1U;
    p->ld.pedal_raw    = 0U;
    p->ld.throttle_raw = 0U;
    for (i = 0U; i < SF_COUNT; i++) {
        p->s_have[i]   = 0U;
        p->s_len_ok[i] = 1U;
        p->live[i]     = 0U;
    }
    p->s1.speed_rpm = 0; p->s1.speed_raw = (uint16_t)RAW_SPEED_ZERO;
    p->s1.torque_nm = 0; p->s1.torque_raw = (uint16_t)RAW_TORQUE_ZERO;
    p->s1.ac_current_da = 0U; p->s1.precharge_allow = 0U;
    p->s1.active_discharge_fb = 0U; p->s1.igbt_fb = 0U; p->s1.live = 0U;
    p->s2.motor_temp_c = 0; p->s2.mcu_temp_c = 0; p->s2.limit_high_nm = 0U;
    p->s2.limit_low_nm = 0; p->s2.limit_low_raw = (uint16_t)RAW_TORQUE_ZERO;
    p->s2.fail_grade = 0U; p->s2.live = 0U;
    p->s3.dtc0 = 0U; p->s3.dtc1 = 0U; p->s3.dc_current_a = 0;
    p->s3.dc_voltage_dv = 0U; p->s3.rotation_count = 0U; p->s3.live = 0U;

    p->pedal_released   = 0U;
    p->prev_brake       = 0U;
    p->cmd_enable       = 0U;
    p->cmd_torque_nm    = 0;
    p->clamped_by_drive = 0U;
}

void pt_step(Powertrain *p, const PtInputs *in, PtOutputs *out)
{
    const PowertrainCal *cal = p->cal;
    uint16_t   dt = p->step_ms;
    uint8_t    cond[F_COUNT];
    MonInputs  mi;
    SmInputs   si;
    SmOutputs  so;
    TqInputs   ti;
    TqOutputs  to;
    GateRequest gr;
    uint8_t    i;
    uint8_t    pedal_valid;
    uint16_t   pedal_permille = 0U;
    uint8_t    brake;
    uint8_t    brake_edge;
    uint8_t    clear_request;
    uint8_t    vdc_ok = 0U;
    uint8_t    limits_valid = 0U;
    uint8_t    drive_seen;
    uint8_t    mode_valid;
    DriveMode  mode_req;

    decode_inputs(p, in);

    /* ---- drive mode request ------------------------------------------------ */
    mode_valid = mode_src_step(&p->msrc, in->mode_new, in->mode_len, in->mode_data,
                               cal, dt, &mode_req);

    /* ---- pedal ------------------------------------------------------------- */
    pedal_valid = ((p->ld_have != 0U) && (p->ld_len_ok != 0U) &&
                   (p->ld.pedal_raw <= 1023U)) ? 1U : 0U;
    if (pedal_valid != 0U) {
        pedal_permille = (uint16_t)(((uint32_t)p->ld.pedal_raw * 1000UL) / 1023UL);
        if (pedal_permille <= cal->pedal_rel_lo_permille) {
            p->pedal_released = 1U;
        } else if (pedal_permille > cal->pedal_rel_hi_permille) {
            p->pedal_released = 0U;
        }
    } else {
        p->pedal_released = 0U;     /* unknown is not released */
    }

    /* ---- brake switch ------------------------------------------------------ */
    brake = ((in->din_brake != 0U) == (cal->brake_active_high != 0U)) ? 1U : 0U;
    brake_edge = ((brake != 0U) && (p->prev_brake == 0U)) ? 1U : 0U;
    p->prev_brake = brake;

    /* ---- drive derived flags ------------------------------------------------ */
    drive_seen = 1U;
    for (i = 0U; i < SF_COUNT; i++) {
        if (p->s_have[i] == 0U) {
            drive_seen = 0U;
        }
    }
    if (p->s_have[SF_S3] != 0U) {
        vdc_ok = ((p->s3.dc_voltage_dv >= cal->vdc_soft_lo_dv) &&
                  (p->s3.dc_voltage_dv <= cal->vdc_soft_hi_dv)) ? 1U : 0U;
    }
    if ((p->s_have[SF_S2] != 0U) && (p->s2.limit_high_nm <= 5000U) &&
        (p->s2.limit_low_raw <= 5000U)) {
        limits_valid = 1U;
    }

    /* ---- monitors ----------------------------------------------------------- */
    mi.ld_new   = in->ld_new;
    mi.ld_have  = p->ld_have;
    mi.ld_len_ok= p->ld_len_ok;
    mi.ld       = p->ld;
    mi.pedal_permille = pedal_permille;
    mi.pedal_valid    = pedal_valid;
    mi.brake    = brake;
    for (i = 0U; i < SF_COUNT; i++) {
        mi.s_new[i]    = in->s_new[i];
        mi.s_have[i]   = p->s_have[i];
        mi.s_len_ok[i] = p->s_len_ok[i];
        mi.live[i]     = p->live[i];
    }
    mi.s1 = p->s1;
    mi.s2 = p->s2;
    mi.s3 = p->s3;
    mi.cmd_enable     = p->cmd_enable;
    mi.cmd_torque_nm  = p->cmd_torque_nm;
    mi.sm_drive       = (p->sm.state == (uint8_t)SM_DRIVE) ? 1U : 0U;
    mi.hv_up          = p->sm.hv_up;
    mi.precharge_active = (p->sm.state == (uint8_t)SM_PRECHARGE) ? 1U : 0U;
    mi.state_ms       = p->sm.state_ms;
    mi.clamped_by_drive = p->clamped_by_drive;
    mi.lv_dv          = in->lv_dv;
    mi.uds_inhibit    = in->uds_inhibit;
    mi.cal_ok         = p->cal_ok;
    mi.step_ok        = p->step_ok;
    mi.state_ok       = sm_state_ok(&p->sm);
    mi.redund_ok      = fm_level_ok(&p->fm);
    mi.mode_src_ok    = mode_valid;
    mon_step(&p->mon, &mi, cal, dt, cond);

    /* ---- fault manager ------------------------------------------------------- */
    /* deliberate driver action: pedal released and a fresh brake press */
    clear_request = ((p->pedal_released != 0U) && (brake_edge != 0U)) ? 1U : 0U;
    fm_step(&p->fm, cond, dt, clear_request);

    /* ---- state machine ------------------------------------------------------- */
    si.level          = p->fm.level;
    si.init_ok        = (uint8_t)((p->cal_ok != 0U) && (p->step_ok != 0U));
    si.drive_seen     = drive_seen;
    si.pedal_released = p->pedal_released;
    si.brake_pressed  = brake;
    si.vdc_ok         = vdc_ok;
    si.igbt_fb        = ((p->s_have[SF_S1] != 0U) && (p->s1.igbt_fb != 0U)) ? 1U : 0U;
    si.l2_drops_enable= cal->l2_drops_enable;
    si.dt_ms          = dt;
    sm_step(&p->sm, &si, &so);

    /* ---- torque request ------------------------------------------------------ */
    ti.pedal_valid    = pedal_valid;
    ti.pedal_permille = pedal_permille;
    ti.pedal_released = p->pedal_released;
    ti.allow          = so.allow_torque;
    ti.level          = p->fm.level;
    ti.mode_valid     = mode_valid;
    ti.mode_req       = mode_req;
    ti.limits_valid   = limits_valid;
    ti.drive_hi_nm    = (int16_t)p->s2.limit_high_nm;
    ti.drive_lo_nm    = (int16_t)p->s2.limit_low_nm;
    tq_step(&p->tq, &ti, cal, p->maps, dt, &to);
    p->clamped_by_drive = to.clamped_by_drive;

    /* ---- safety gate ----------------------------------------------------------- */
    gr.enable    = so.enable;
    gr.torque_nm = to.torque_nm;
    gr.level     = p->fm.level;
    gate_compute(&gr, cal, &out->cmd);

    /* remember what was sent, for the next step's monitors */
    p->cmd_enable    = out->cmd.enable;
    p->cmd_torque_nm = out->cmd.torque_nm;

    out->state          = so.state;
    out->level          = p->fm.level;
    out->mode           = (uint8_t)to.mode;
    out->fault_count    = p->fm.count;
    out->last_fault     = p->fm.last;
    out->active         = p->fm.active;
    out->latched        = p->fm.latched;
    out->torque_req_nm  = to.torque_nm;
    out->pedal_permille = pedal_permille;
    out->cal_reason     = p->cal_reason;
}
