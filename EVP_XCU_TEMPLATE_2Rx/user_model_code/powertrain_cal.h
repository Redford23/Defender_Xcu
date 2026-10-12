/*
 * powertrain_cal.h
 *
 * Limits and thresholds for the hybrid supervisor. The values live in
 * powertrain_cal.c. Every value is a proposal until Red sets it.
 *
 * Fields marked REQUIRED are shipped as 0 (unset). DRIVE is refused until
 * they are set, and the start-up check raises F_SY_CAL (see fault_mgr.h).
 */

#ifndef POWERTRAIN_CAL_H_
#define POWERTRAIN_CAL_H_

#include <stdint.h>

typedef struct {
    /* timing, milliseconds */
    uint16_t step_ms_min;          /* step period accepted at start-up */
    uint16_t step_ms_max;
    uint16_t startup_grace_ms;     /* frame timeouts ignored this long after power-on */
    uint16_t ld_timeout_ms;        /* LD 0x100 */
    uint16_t drv_timeout_ms;       /* each iNetic status frame */
    uint16_t live_stuck_ms;        /* LiveCounter unchanged while frames arrive */
    uint16_t igbt_grace_ms;        /* allowed after MCU_Enable changes */
    uint16_t precharge_timeout_ms; /* PRECHARGE to READY, then L3 */
    uint16_t cmd_tx_interval_ms;   /* 0 = single shot every step, else periodic */
    uint16_t mode_timeout_ms;      /* no mode frame (CAN1 0x302) for this long = Engine only */
    uint16_t mode_stuck_ms;        /* mode frame counter unchanged this long = Engine only */

    /* CAN */
    uint8_t  ld_rx_dlc;            /* DLC passed to the CAN3 receive box for 0x100 */
    uint8_t  mode_rx_dlc;          /* DLC passed to the CAN1 receive box for 0x302 */

    /* torque and speed */
    int16_t  torque_max_nm;        /* REQUIRED. Largest positive torque the xCU will request */
    int16_t  regen_max_nm;         /* Largest negative torque. 0 = negative torque disabled */
    uint16_t speed_max_rpm;        /* REQUIRED */
    uint8_t  l1_derate_percent;    /* L1 limits as a percentage of normal */

    /* DC link, units of 0.1 V. REQUIRED, all four, in ascending order */
    uint16_t vdc_hard_lo_dv;
    uint16_t vdc_soft_lo_dv;
    uint16_t vdc_soft_hi_dv;
    uint16_t vdc_hard_hi_dv;

    /* pedal, permille of full travel */
    uint16_t pedal_rel_lo_permille;   /* at or below: released */
    uint16_t pedal_rel_hi_permille;   /* above: not released. Hysteresis between */
    uint16_t pedal_brake_permille;    /* pedal above this with brake = BR_PEDAL */
    uint16_t pedal_rate_counts;       /* implausible change between frames, 0..1023 scale */
    uint16_t pedal_frozen_ms;

    /* LV supply, units of 0.1 V */
    uint16_t lv_min_dv;
    uint16_t lv_max_dv;

    /* optional warning threshold on motor and controller temperature, 0 = off */
    uint8_t  temp_warn_c;

    /* command frame fields with unconfirmed meaning. Sent as configured, no logic */
    uint8_t  gear_cmd;             /* 0 neutral, 1 forward, 2 reverse. Gear logic is not written */
    uint16_t demand_limit_high_raw;/* 12 bit raw, x4. Meaning in torque mode unconfirmed */
    uint16_t demand_limit_low_raw;

    /* switch and brake polarity */
    uint8_t  brake_active_high;    /* 1 = input high when brake pressed */
} PowertrainCal;

extern const PowertrainCal g_cal;

/* Returns 1 if the calibration is complete and inside hard limits.
 * On failure *reason (if not null) is a small code, see powertrain_cal.c */
uint8_t cal_validate(const PowertrainCal *cal, uint8_t *reason);

#endif /* POWERTRAIN_CAL_H_ */
