/*
 * test_powertrain.c
 *
 * Host-side unit and scenario tests for the powertrain supervisor. This file
 * is compiled to nothing by CCS (everything is inside EVP_HOST_TEST).
 *
 * Build and run on a PC with any C99 compiler, from this folder:
 *
 *   gcc -std=c99 -Wall -Wextra -DEVP_HOST_TEST -I.. test_powertrain.c \
 *       ../can_codec.c ../fault_mgr.c ../monitors.c ../torque_request.c \
 *       ../drive_sm.c ../safety_gate.c ../powertrain.c ../powertrain_cal.c \
 *       ../throttle_maps.c -o test_powertrain && ./test_powertrain
 *
 * Exit status is the number of failed checks.
 */

typedef int evp_host_test_placeholder_t;  /* keeps the file non-empty outside host builds */

#ifdef EVP_HOST_TEST

#include <stdio.h>
#include <string.h>
#include "powertrain.h"

static int g_fail = 0;
static int g_checks = 0;

#define CHECK(c) do { g_checks++; if (!(c)) { g_fail++; \
    printf("FAIL %s:%d  %s\n", __FILE__, __LINE__, #c); } } while (0)

/* ------------------------------------------------------------------ codec */

static void test_codec(void)
{
    DriveCommand c;
    uint8_t d[8];
    DriveStatus1 s1;
    DriveStatus2 s2;
    DriveStatus3 s3;
    LdStatus ld;
    uint8_t live;
    static const uint8_t st1[8] = { 0x80, 0x3E, 0x88, 0x13, 0x64, 0x00, 0x50, 0xA0 };
    static const uint8_t st2[8] = { 0x50, 0x46, 0x88, 0x13, 0x88, 0x13, 0x02, 0x30 };
    static const uint8_t st3[8] = { 0x04, 0x01, 0xE8, 0x03, 0xA0, 0x0F, 0x07, 0xF0 };
    static const uint8_t ldf[8] = { 0x03, 0xFF, 0x01, 0x00, 0, 0, 0, 0 };

    /* the safe command must never be an all-zero frame */
    codec_safe_command(&c);
    codec_encode_command(&c, d);
    CHECK(d[0] == 0x08);                    /* mode 2, enable 0 */
    CHECK(d[1] == 0x00 && d[2] == 0x00 && d[3] == 0x00);
    CHECK(d[4] == 0x88 && d[5] == 0x13);    /* 5000 = 0 Nm */
    CHECK(d[6] == 0x98 && d[7] == 0x3A);    /* 15000 = 0 rpm */

    c.enable = 1U; c.gear = 1U; c.torque_nm = 15;
    codec_encode_command(&c, d);
    CHECK(d[0] == 0x19);                    /* enable, mode 2, gear 1 */
    CHECK(d[4] == 0x97 && d[5] == 0x13);    /* 5015 */

    /* saturation */
    c.torque_nm = 32000;
    codec_encode_command(&c, d);
    CHECK(d[4] == 0x10 && d[5] == 0x27);    /* 10000 */
    c.torque_nm = -32000;
    codec_encode_command(&c, d);
    CHECK(d[4] == 0x00 && d[5] == 0x00);

    /* demand limits: high 0xABC, low 0x123 */
    codec_safe_command(&c);
    c.limit_high_raw = 0xABCU; c.limit_low_raw = 0x123U;
    codec_encode_command(&c, d);
    CHECK(d[1] == 0xBC && d[2] == 0x3A && d[3] == 0x12);

    /* decode */
    CHECK(codec_decode_status1(st1, 8U, &s1) == 1U);
    CHECK(s1.speed_rpm == 1000);            /* 0x3E80 = 16000 */
    CHECK(s1.torque_nm == 0);
    CHECK(s1.ac_current_da == 100U);
    CHECK(s1.precharge_allow == 1U && s1.active_discharge_fb == 0U && s1.igbt_fb == 1U);
    CHECK(s1.live == 0xAU);
    CHECK(codec_decode_status1(st1, 7U, &s1) == 0U);

    CHECK(codec_decode_status2(st2, 8U, &s2) == 1U);
    CHECK(s2.motor_temp_c == 40 && s2.mcu_temp_c == 30);
    CHECK(s2.limit_high_nm == 5000U && s2.limit_low_nm == 0);
    CHECK(s2.fail_grade == 2U && s2.live == 3U);

    CHECK(codec_decode_status3(st3, 8U, &s3) == 1U);
    CHECK(s3.dtc0 == 0x04U && s3.dtc1 == 0x01U);
    CHECK(s3.dc_current_a == 0 && s3.dc_voltage_dv == 4000U);
    CHECK(s3.rotation_count == 7U && s3.live == 0xFU);

    CHECK(codec_decode_status4(st1, 8U, &live) == 1U && live == 0xAU);

    CHECK(codec_decode_ld(ldf, 8U, &ld) == 1U);
    CHECK(ld.pedal_raw == 1023U && ld.throttle_raw == 256U);
    CHECK(codec_decode_ld(ldf, 3U, &ld) == 0U);
}

/* ------------------------------------------------------------ torque maps */

static void test_maps(void)
{
    const ThrottleMap *ev = &g_throttleMaps[MODE_EV];

    CHECK(tq_interp(ev, 0U) == 0);
    CHECK(tq_interp(ev, 500U) == 15);
    CHECK(tq_interp(ev, 450U) == 13);       /* 12 + 3*50/100, truncated */
    CHECK(tq_interp(ev, 1000U) == 30);
    CHECK(tq_interp(ev, 5000U) == 30);      /* above range holds the last point */

    CHECK(tq_mode_from_switch(1U, 0U, 0U) == MODE_EV);
    CHECK(tq_mode_from_switch(0U, 1U, 0U) == MODE_HYBRID);
    CHECK(tq_mode_from_switch(0U, 0U, 1U) == MODE_ENGINE_ONLY);
    CHECK(tq_mode_from_switch(0U, 0U, 0U) == MODE_ENGINE_ONLY);  /* open wire */
    CHECK(tq_mode_from_switch(1U, 1U, 0U) == MODE_ENGINE_ONLY);

    CHECK(maps_validate(g_throttleMaps, 100) == 1U);
    CHECK(maps_validate(g_throttleMaps, 20) == 0U);              /* EV reaches 30 Nm */
}

/* --------------------------------------------------------- fault manager */

static void test_fault_manager(void)
{
    FaultMgr fm;
    uint8_t cond[F_COUNT];
    uint8_t i;

    fm_init(&fm);
    for (i = 0U; i < (uint8_t)F_COUNT; i++) { cond[i] = 0U; }

    /* debounce: BR_PEDAL needs 100 ms */
    cond[F_BR_PEDAL] = 1U;
    fm_step(&fm, cond, 20U, 0U);
    CHECK(fm.level == 0U);
    fm_step(&fm, cond, 20U, 0U); fm_step(&fm, cond, 20U, 0U);
    fm_step(&fm, cond, 20U, 0U); fm_step(&fm, cond, 20U, 0U);
    CHECK(fm.level == 2U);
    cond[F_BR_PEDAL] = 0U;
    for (i = 0U; i < 12U; i++) { fm_step(&fm, cond, 20U, 0U); }
    CHECK(fm.level == 0U);                  /* NL clears itself */

    /* driver latched: stays until condition gone and driver acts */
    cond[F_DD_TIMEOUT] = 1U;
    fm_step(&fm, cond, 20U, 0U);
    CHECK(fm.level == 2U);
    cond[F_DD_TIMEOUT] = 0U;
    for (i = 0U; i < 40U; i++) { fm_step(&fm, cond, 20U, 0U); }
    CHECK(fm.level == 2U);
    fm_step(&fm, cond, 20U, 1U);
    CHECK(fm.level == 0U);

    /* escalation to L3 and key latch */
    cond[F_DR_TIMEOUT] = 1U;
    for (i = 0U; i < 24U; i++) { fm_step(&fm, cond, 20U, 0U); }
    CHECK(fm.level == 2U);
    for (i = 0U; i < 4U; i++) { fm_step(&fm, cond, 20U, 0U); }
    CHECK(fm.level == 3U);
    cond[F_DR_TIMEOUT] = 0U;
    for (i = 0U; i < 100U; i++) { fm_step(&fm, cond, 20U, 1U); }
    CHECK(fm.level == 3U);                  /* never cleared by driver action */
    CHECK(fm_level_ok(&fm) == 1U);
    CHECK(fm.count >= 3U && fm.last == (uint8_t)(F_DR_TIMEOUT + 1U));
}

/* ------------------------------------------------------ scenario harness */

typedef struct {
    Powertrain pt;
    PtInputs   in;
    PtOutputs  out;
    PowertrainCal cal;
    uint8_t    live;
    uint8_t    fail_grade;
    uint16_t   pedal_raw;
    uint16_t   vdc_dv;
    uint8_t    send_ld;
    uint8_t    send_isg;
    uint8_t    mirror_enable;   /* drive feedback follows last command */
    uint8_t    mirror_torque;
    uint8_t    igbt_fb;
    uint8_t    dtc0;
    int16_t    torque_meas;
} Rig;

static void rig_cal(PowertrainCal *c)
{
    *c = g_cal;
    c->torque_max_nm = 100;
    c->regen_max_nm  = 0;
    c->speed_max_rpm = 6000U;
    c->vdc_hard_lo_dv = 3000U;
    c->vdc_soft_lo_dv = 3500U;
    c->vdc_soft_hi_dv = 4500U;
    c->vdc_hard_hi_dv = 5000U;
    c->gear_cmd = 1U;
}

static void rig_init(Rig *r, const PowertrainCal *cal)
{
    memset(r, 0, sizeof(*r));
    if (cal != 0) { r->cal = *cal; } else { rig_cal(&r->cal); }
    r->vdc_dv = 4000U;
    r->mirror_enable = 1U;
    r->mirror_torque = 1U;
    r->send_ld = 1U;
    r->send_isg = 1U;
    r->in.din_mode_ev = 1U;
    r->in.lv_dv = 130U;
    pt_init(&r->pt, &r->cal, g_throttleMaps, 20U);
}

static void put_le16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)(v & 0xFFU); p[1] = (uint8_t)(v >> 8); }

static void rig_step(Rig *r)
{
    uint8_t i;
    int16_t tq = r->mirror_torque ? r->out.cmd.torque_nm : r->torque_meas;
    uint8_t en = r->mirror_enable ? r->out.cmd.enable : r->igbt_fb;

    memset(r->in.s_data, 0, sizeof(r->in.s_data));
    memset(r->in.ld_data, 0, sizeof(r->in.ld_data));

    /* LD 0x100, big endian */
    r->in.ld_new = r->send_ld;
    r->in.ld_len = 8U;
    r->in.ld_data[0] = (uint8_t)(r->pedal_raw >> 8);
    r->in.ld_data[1] = (uint8_t)(r->pedal_raw & 0xFFU);

    r->live = (uint8_t)((r->live + 1U) & 0x0FU);
    for (i = 0U; i < SF_COUNT; i++) {
        r->in.s_new[i] = r->send_isg;
        r->in.s_len[i] = 8U;
        r->in.s_data[i][7] = (uint8_t)(r->live << 4);
    }
    /* S1: speed 0, torque, igbt feedback */
    put_le16(&r->in.s_data[0][0], 15000U);
    put_le16(&r->in.s_data[0][2], (uint16_t)(5000 + tq));
    r->in.s_data[0][6] = (uint8_t)(en ? 0x40U : 0x00U);
    /* S2: limits 5000 / 0, fail grade */
    put_le16(&r->in.s_data[1][2], 5000U);
    put_le16(&r->in.s_data[1][4], 5000U);
    r->in.s_data[1][0] = 40U + 25U; r->in.s_data[1][1] = 40U + 25U;
    r->in.s_data[1][6] = r->fail_grade;
    /* S3: dtc, voltage */
    r->in.s_data[2][0] = r->dtc0;
    put_le16(&r->in.s_data[2][2], 1000U);
    put_le16(&r->in.s_data[2][4], r->vdc_dv);

    pt_step(&r->pt, &r->in, &r->out);
}

static void rig_run(Rig *r, int steps)
{
    int i;
    for (i = 0; i < steps; i++) { rig_step(r); }
}

/* bring the rig to DRIVE with the pedal released and brake pressed */
static void rig_to_drive(Rig *r)
{
    r->in.din_brake = 1U;
    r->pedal_raw = 0U;
    rig_run(r, 150);
}

static void test_scenarios(void)
{
    Rig r;
    int i;

    /* shipped calibration is incomplete: must never enable the drive */
    rig_init(&r, &g_cal);
    r.in.din_brake = 1U;
    rig_run(&r, 200);
    CHECK(r.out.state == (uint8_t)SM_SHUTDOWN);
    CHECK(r.out.cmd.enable == 0U && r.out.cmd.torque_nm == 0);
    CHECK(r.out.level == 3U);

    /* normal bring-up */
    rig_init(&r, 0);
    CHECK(r.pt.cal_ok == 1U);
    rig_to_drive(&r);
    CHECK(r.out.state == (uint8_t)SM_DRIVE);
    CHECK(r.out.cmd.enable == 1U && r.out.cmd.torque_nm == 0);
    CHECK(r.out.mode == (uint8_t)MODE_EV);   /* switch stable and pedal released */
    CHECK(r.out.level == 0U);

    /* pedal 50 %: EV map gives 15 Nm, rate limited at 50 Nm/s = 1 Nm per 20 ms step */
    r.pedal_raw = 512U;
    rig_run(&r, 3);
    CHECK(r.out.cmd.torque_nm > 0 && r.out.cmd.torque_nm <= 3);
    rig_run(&r, 40);
    CHECK(r.out.cmd.torque_nm == 15);

    /* mode switch to hybrid with pedal applied does not change mode */
    r.in.din_mode_ev = 0U; r.in.din_mode_hybrid = 1U;
    rig_run(&r, 30);
    CHECK(r.out.mode == (uint8_t)MODE_EV);
    r.pedal_raw = 0U;
    rig_run(&r, 40);
    CHECK(r.out.mode == (uint8_t)MODE_HYBRID);
    CHECK(r.out.cmd.torque_nm == 0);

    /* open wire on the mode switch: engine only, zero torque */
    r.in.din_mode_hybrid = 0U;
    rig_run(&r, 30);
    CHECK(r.out.mode == (uint8_t)MODE_ENGINE_ONLY);
    r.pedal_raw = 800U;
    rig_run(&r, 40);
    CHECK(r.out.cmd.torque_nm == 0);

    /* LD frames stop: torque to zero within the debounce, drive stays enabled */
    r.in.din_mode_ev = 1U;
    r.pedal_raw = 0U;
    rig_run(&r, 40);
    r.pedal_raw = 512U;
    rig_run(&r, 40);
    CHECK(r.out.cmd.torque_nm == 15);
    r.send_ld = 0U;
    rig_run(&r, 6);                          /* 120 ms with no frame */
    CHECK(r.out.level >= 2U);
    CHECK(r.out.cmd.torque_nm == 0);
    CHECK(r.out.cmd.enable == 1U);           /* L2 keeps the drive enabled */
    CHECK(r.out.state == (uint8_t)SM_FAULT);

    /* frames return: still latched until the driver acts */
    r.send_ld = 1U;
    r.pedal_raw = 0U;
    rig_run(&r, 60);
    CHECK(r.out.level == 2U);
    CHECK(r.out.cmd.torque_nm == 0);
    r.in.din_brake = 0U;
    rig_run(&r, 2);
    r.in.din_brake = 1U;                     /* fresh press */
    rig_run(&r, 5);
    CHECK(r.out.level == 0U);
    rig_run(&r, 10);
    CHECK(r.out.state == (uint8_t)SM_DRIVE);

    /* FailGrade 3: disabled, zero torque, and it stays that way */
    r.fail_grade = 3U;
    rig_run(&r, 3);
    CHECK(r.out.level == 3U);
    CHECK(r.out.state == (uint8_t)SM_SHUTDOWN);
    CHECK(r.out.cmd.enable == 0U && r.out.cmd.torque_nm == 0);
    r.fail_grade = 0U;
    r.in.din_brake = 0U;
    rig_run(&r, 5);
    r.in.din_brake = 1U;
    rig_run(&r, 100);
    CHECK(r.out.state == (uint8_t)SM_SHUTDOWN);
    CHECK(r.out.cmd.enable == 0U);

    /* pedal pressed at start: never enters DRIVE */
    rig_init(&r, 0);
    r.in.din_brake = 1U;
    r.pedal_raw = 600U;
    rig_run(&r, 200);
    CHECK(r.out.state != (uint8_t)SM_DRIVE);
    CHECK(r.out.cmd.torque_nm == 0);

    /* drive feedback does not confirm enable: L3 */
    rig_init(&r, 0);
    r.mirror_enable = 0U;
    r.igbt_fb = 0U;
    r.in.din_brake = 1U;
    rig_run(&r, 300);
    CHECK(r.out.level == 3U);
    CHECK(r.out.cmd.enable == 0U);

    /* measured torque opposite to demand: L3 */
    rig_init(&r, 0);
    rig_to_drive(&r);
    r.pedal_raw = 1023U;
    rig_run(&r, 60);
    CHECK(r.out.cmd.torque_nm > 10);
    r.mirror_torque = 0U;
    r.torque_meas = -20;
    rig_run(&r, 10);
    CHECK(r.out.level == 3U);
    CHECK(r.out.cmd.torque_nm == 0 && r.out.cmd.enable == 0U);

    /* DC voltage out of the hard window: L3 */
    rig_init(&r, 0);
    rig_to_drive(&r);
    r.vdc_dv = 2000U;
    rig_run(&r, 10);
    CHECK(r.out.level == 3U);

    /* never a non-zero torque outside DRIVE */
    rig_init(&r, 0);
    r.in.din_brake = 1U;
    r.pedal_raw = 900U;
    for (i = 0; i < 100; i++) {
        rig_step(&r);
        if (r.out.state != (uint8_t)SM_DRIVE) {
            CHECK(r.out.cmd.torque_nm == 0);
        }
    }
}

int main(void)
{
    test_codec();
    test_maps();
    test_fault_manager();
    test_scenarios();
    printf("%d checks, %d failed\n", g_checks, g_fail);
    return g_fail;
}

#endif /* EVP_HOST_TEST */
