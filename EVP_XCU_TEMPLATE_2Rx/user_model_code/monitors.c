/*
 * monitors.c
 *
 * See monitors.h. Each block names the matrix row it implements
 * (docs\safety\fault_matrix.md).
 */

#include "monitors.h"

static uint16_t sat_add16(uint16_t a, uint16_t b)
{
    uint32_t s = (uint32_t)a + (uint32_t)b;
    return (s > 0xFFFFUL) ? (uint16_t)0xFFFFU : (uint16_t)s;
}

static int32_t abs32(int32_t v)
{
    return (v < 0) ? -v : v;
}

void mon_init(MonState *ms)
{
    uint8_t i;

    ms->startup_ms = 0U;
    ms->ld_age_ms  = 0U;
    for (i = 0U; i < SF_COUNT; i++) {
        ms->drv_age_ms[i]   = 0U;
        ms->live_same_ms[i] = 0U;
        ms->live_last[i]    = 0U;
        ms->live_seen[i]    = 0U;
    }
    ms->last_pedal      = 0U;
    ms->have_last_pedal = 0U;
    ms->frozen_ref      = 0U;
    ms->frozen_ref_thr  = 0U;
    ms->frozen_ms       = 0U;
    ms->rate_bad        = 0U;
    ms->last_cmd_enable = 0U;
    ms->igbt_grace_ms   = 0U;
}

void mon_step(MonState *ms, const MonInputs *in, const PowertrainCal *cal,
              uint16_t dt_ms, uint8_t cond[F_COUNT])
{
    uint8_t  i;
    uint8_t  grace;
    uint8_t  any_timeout = 0U;
    uint8_t  any_live    = 0U;
    uint8_t  any_raw     = 0U;
    int32_t  delta;
    int32_t  err;
    int32_t  tol;
    int32_t  cmd;
    int32_t  meas;

    for (i = 0U; i < (uint8_t)F_COUNT; i++) {
        cond[i] = 0U;
    }

    ms->startup_ms = sat_add16(ms->startup_ms, dt_ms);
    grace = (ms->startup_ms < cal->startup_grace_ms) ? 1U : 0U;

    /* ---- LD controller, DD-01 .. DD-04 ---------------------------------- */
    if (in->ld_new != 0U) {
        ms->ld_age_ms = 0U;
    } else {
        ms->ld_age_ms = sat_add16(ms->ld_age_ms, dt_ms);
    }
    /* DD-01 */
    cond[F_DD_TIMEOUT] = ((grace == 0U) && (ms->ld_age_ms >= cal->ld_timeout_ms)) ? 1U : 0U;

    /* DD-02 */
    if (in->ld_have != 0U) {
        if ((in->ld_len_ok == 0U) || (in->ld.pedal_raw > 1023U) || (in->ld.throttle_raw > 1023U)) {
            cond[F_DD_RANGE] = 1U;
        }
    }

    if (in->ld_new != 0U) {
        /* DD-04: two successive implausible steps */
        if (ms->have_last_pedal != 0U) {
            delta = abs32((int32_t)in->ld.pedal_raw - (int32_t)ms->last_pedal);
            if (delta > (int32_t)cal->pedal_rate_counts) {
                if (ms->rate_bad < 255U) {
                    ms->rate_bad++;
                }
            } else {
                ms->rate_bad = 0U;
            }
        }
        ms->last_pedal      = in->ld.pedal_raw;
        ms->have_last_pedal = 1U;

        /* DD-03: restart the frozen timer whenever pedal or throttle changes.
         * Both must be unchanged, so a steady foot on a live frame does not trip it. */
        if ((in->ld.pedal_raw != ms->frozen_ref) ||
            (in->ld.throttle_raw != ms->frozen_ref_thr)) {
            ms->frozen_ref     = in->ld.pedal_raw;
            ms->frozen_ref_thr = in->ld.throttle_raw;
            ms->frozen_ms      = 0U;
        }
    }
    cond[F_DD_RATE] = (ms->rate_bad >= 2U) ? 1U : 0U;

    /* A frozen value only counts above the released threshold: frozen at
     * zero is indistinguishable from released and fails to the safe side. */
    if ((in->ld_have != 0U) && (in->pedal_valid != 0U) &&
        (in->pedal_permille > cal->pedal_rel_hi_permille)) {
        ms->frozen_ms = sat_add16(ms->frozen_ms, dt_ms);
    } else {
        ms->frozen_ms = 0U;
    }
    cond[F_DD_FROZEN] = (ms->frozen_ms >= cal->pedal_frozen_ms) ? 1U : 0U;

    /* ---- Brake, BR-01 ---------------------------------------------------- */
    cond[F_BR_PEDAL] = ((in->brake != 0U) && (in->pedal_valid != 0U) &&
                        (in->pedal_permille > cal->pedal_brake_permille)) ? 1U : 0U;

    /* ---- iNetic frame timeouts and live counters, DR-01, DR-02 ---------- */
    for (i = 0U; i < SF_COUNT; i++) {
        if (in->s_new[i] != 0U) {
            ms->drv_age_ms[i] = 0U;
            if ((ms->live_seen[i] != 0U) && (in->live[i] == ms->live_last[i])) {
                /* counter did not move on a new frame: time accrues below */
            } else {
                ms->live_same_ms[i] = 0U;
            }
            ms->live_last[i] = in->live[i];
            ms->live_seen[i] = 1U;
        } else {
            ms->drv_age_ms[i] = sat_add16(ms->drv_age_ms[i], dt_ms);
        }

        if ((grace == 0U) && (ms->drv_age_ms[i] >= cal->drv_timeout_ms)) {
            any_timeout = 1U;
        }

        /* counter stuck: only meaningful while frames are still arriving */
        if ((ms->live_seen[i] != 0U) && (ms->drv_age_ms[i] < cal->drv_timeout_ms)) {
            ms->live_same_ms[i] = sat_add16(ms->live_same_ms[i], dt_ms);
            if (ms->live_same_ms[i] >= cal->live_stuck_ms) {
                any_live = 1U;
            }
        } else {
            ms->live_same_ms[i] = 0U;
        }

        if ((in->s_have[i] != 0U) && (in->s_len_ok[i] == 0U)) {
            any_raw = 1U;
        }
    }
    cond[F_DR_TIMEOUT] = any_timeout;
    cond[F_DR_LIVE]    = any_live;

    /* ---- FailGrade, DR-03 .. DR-06 --------------------------------------- */
    if (in->s_have[SF_S2] != 0U) {
        cond[F_DR_FG1]      = (in->s2.fail_grade == 1U) ? 1U : 0U;
        cond[F_DR_FG2]      = (in->s2.fail_grade == 2U) ? 1U : 0U;
        cond[F_DR_FG34]     = ((in->s2.fail_grade == 3U) || (in->s2.fail_grade == 4U)) ? 1U : 0U;
        cond[F_DR_FG_UNDEF] = (in->s2.fail_grade > 4U) ? 1U : 0U;

        /* DR-12: drive torque limits make no sense */
        if ((in->s2.limit_high_nm > 5000U) || (in->s2.limit_low_raw > 5000U)) {
            cond[F_DR_LIMITS] = 1U;
        }

        /* DR-13: temperature warning, optional */
        if (cal->temp_warn_c != 0U) {
            if ((in->s2.motor_temp_c >= (int16_t)cal->temp_warn_c) ||
                (in->s2.mcu_temp_c >= (int16_t)cal->temp_warn_c)) {
                cond[F_DR_WARN] = 1U;
            }
        }
    }

    /* ---- IGBT feedback, DR-07 -------------------------------------------- */
    if (in->cmd_enable != ms->last_cmd_enable) {
        ms->igbt_grace_ms = cal->igbt_grace_ms;
    } else if (ms->igbt_grace_ms > dt_ms) {
        ms->igbt_grace_ms = (uint16_t)(ms->igbt_grace_ms - dt_ms);
    } else {
        ms->igbt_grace_ms = 0U;
    }
    ms->last_cmd_enable = in->cmd_enable;

    if (in->s_have[SF_S1] != 0U) {
        if ((ms->igbt_grace_ms == 0U) && ((in->cmd_enable != 0U) != (in->s1.igbt_fb != 0U))) {
            cond[F_DR_IGBT] = 1U;
        }

        /* DR-08, DR-09: measured torque against what was commanded */
        if ((in->sm_drive != 0U) && (in->cmd_enable != 0U) && (in->s1.igbt_fb != 0U)) {
            cmd  = (int32_t)in->cmd_torque_nm;
            meas = in->s1.torque_nm;
            err  = abs32(meas - cmd);
            tol  = (abs32(cmd) * 15) / 100;
            if (tol < 10) {
                tol = 10;
            }
            if (err > tol) {
                cond[F_DR_TRACK] = 1U;
            }
            if (((cmd > 5) && (meas < -5)) || ((cmd < -5) && (meas > 5))) {
                cond[F_DR_SIGN] = 1U;
            }
        }

        /* DR-10 */
        if ((cal->speed_max_rpm != 0U) &&
            (abs32(in->s1.speed_rpm) > (int32_t)cal->speed_max_rpm)) {
            cond[F_DR_OVERSPEED] = 1U;
        }

        /* DR-18 raw range */
        if ((in->s1.speed_raw > 30000U) || (in->s1.torque_raw > 10000U)) {
            any_raw = 1U;
        }

        /* DR-19 */
        if ((in->cmd_enable != 0U) && (in->s1.active_discharge_fb != 0U)) {
            cond[F_DR_ACTDISCH] = 1U;
        }
    }

    /* ---- DC link and DTC bits, DR-13 .. DR-17 ---------------------------- */
    if (in->s_have[SF_S3] != 0U) {
        if (in->hv_up != 0U) {
            if ((in->s3.dc_voltage_dv < cal->vdc_soft_lo_dv) ||
                (in->s3.dc_voltage_dv > cal->vdc_soft_hi_dv)) {
                cond[F_DR_VDC_SOFT] = 1U;
            }
            if ((in->s3.dc_voltage_dv < cal->vdc_hard_lo_dv) ||
                (in->s3.dc_voltage_dv > cal->vdc_hard_hi_dv)) {
                cond[F_DR_VDC_HARD] = 1U;
            }
        }
        if ((in->s3.dtc0 != 0U) || ((in->s3.dtc1 & 0x07U) != 0U)) {
            cond[F_DR_DTC] = 1U;
        }
        if ((in->s3.dtc1 & 0x78U) != 0U) {   /* warning bits 3..6 */
            cond[F_DR_WARN] = 1U;
        }
        if (in->s3.dc_voltage_dv > 10000U) {
            any_raw = 1U;
        }
    }
    cond[F_DR_RAW] = any_raw;

    cond[F_DR_CLAMP] = in->clamped_by_drive;

    /* DR-16 */
    if ((in->precharge_active != 0U) && (in->state_ms >= cal->precharge_timeout_ms)) {
        cond[F_DR_PRECHARGE] = 1U;
    }

    /* ---- xCU internal ---------------------------------------------------- */
    cond[F_SY_LV]    = ((in->lv_dv < cal->lv_min_dv) || (in->lv_dv > cal->lv_max_dv)) ? 1U : 0U;
    cond[F_SY_UDS]   = (in->uds_inhibit != 0U) ? 1U : 0U;
    cond[F_SY_STATE] = (in->state_ok == 0U) ? 1U : 0U;
    cond[F_SY_REDUND]= (in->redund_ok == 0U) ? 1U : 0U;
    cond[F_SY_CAL]   = (in->cal_ok == 0U) ? 1U : 0U;
    cond[F_SY_STEP]  = (in->step_ok == 0U) ? 1U : 0U;

    /* MD-01: diagnostic only, the mode has already fallen to Engine only */
    cond[F_MD_SRC]   = ((grace == 0U) && (in->mode_src_ok == 0U)) ? 1U : 0U;
}
