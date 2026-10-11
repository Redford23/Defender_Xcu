/*
 * monitors.h
 *
 * Pure functions that turn decoded inputs into fault conditions. No
 * hardware access and no output writes. The fault manager decides what a
 * condition means.
 */

#ifndef MONITORS_H_
#define MONITORS_H_

#include <stdint.h>
#include "powertrain_cal.h"
#include "fault_mgr.h"
#include "can_codec.h"

/* indices into the four iNetic status frames */
#define SF_S1 0U
#define SF_S2 1U
#define SF_S3 2U
#define SF_S4 3U
#define SF_COUNT 4U

typedef struct {
    /* LD controller */
    uint8_t      ld_new;            /* a new 0x100 frame arrived this step */
    uint8_t      ld_have;           /* at least one frame decoded */
    uint8_t      ld_len_ok;         /* latest frame had enough bytes */
    LdStatus     ld;
    uint16_t     pedal_permille;
    uint8_t      pedal_valid;

    /* driver switches */
    uint8_t      brake;

    /* iNetic status */
    uint8_t      s_new[SF_COUNT];
    uint8_t      s_have[SF_COUNT];  /* decoded at least once */
    uint8_t      s_len_ok[SF_COUNT];/* latest frame had enough bytes */
    DriveStatus1 s1;
    DriveStatus2 s2;
    DriveStatus3 s3;
    uint8_t      live[SF_COUNT];

    /* what was last commanded */
    uint8_t      cmd_enable;
    int16_t      cmd_torque_nm;

    /* from the rest of the application */
    uint8_t      sm_drive;          /* state machine is in DRIVE */
    uint8_t      hv_up;             /* precharge completed this power cycle */
    uint8_t      precharge_active;
    uint16_t     state_ms;
    uint8_t      clamped_by_drive;
    uint16_t     lv_dv;
    uint8_t      uds_inhibit;
    uint8_t      cal_ok;
    uint8_t      step_ok;
    uint8_t      state_ok;
    uint8_t      redund_ok;
    uint8_t      mode_src_ok;
} MonInputs;

typedef struct {
    uint16_t startup_ms;
    uint16_t ld_age_ms;
    uint16_t drv_age_ms[SF_COUNT];
    uint16_t live_same_ms[SF_COUNT];
    uint8_t  live_last[SF_COUNT];
    uint8_t  live_seen[SF_COUNT];
    uint16_t last_pedal;
    uint8_t  have_last_pedal;
    uint16_t frozen_ref;
    uint16_t frozen_ref_thr;
    uint16_t frozen_ms;
    uint8_t  rate_bad;
    uint8_t  last_cmd_enable;
    uint16_t igbt_grace_ms;
} MonState;

void mon_init(MonState *ms);
void mon_step(MonState *ms, const MonInputs *in, const PowertrainCal *cal,
              uint16_t dt_ms, uint8_t cond[F_COUNT]);

#endif /* MONITORS_H_ */
