/*
 * powertrain_cal.c
 *
 * Calibration for the hybrid supervisor. EDIT THE VALUES IN g_cal.
 * Throttle maps are in throttle_maps.c.
 */

#include "powertrain_cal.h"

const PowertrainCal g_cal = {
    /* step_ms_min */            10U,
    /* step_ms_max */            50U,
    /* startup_grace_ms */       1500U,
    /* ld_timeout_ms */          100U,      /* TBC against LD 0x100 frame rate */
    /* drv_timeout_ms */         100U,      /* TBC against iNetic cycle time */
    /* live_stuck_ms */          200U,
    /* igbt_grace_ms */          1000U,
    /* precharge_timeout_ms */   30000U,
    /* cmd_tx_interval_ms */     0U,        /* single shot each step. Use the step period if bench shows one frame only */

    /* ld_rx_dlc */              8U,        /* TBC: LD frame length is not documented */

    /* torque_max_nm */          0,         /* REQUIRED: not set */
    /* regen_max_nm */           0,         /* negative torque disabled until set */
    /* speed_max_rpm */          0U,        /* REQUIRED: not set */
    /* l1_derate_percent */      50U,

    /* vdc_hard_lo_dv */         0U,        /* REQUIRED: not set */
    /* vdc_soft_lo_dv */         0U,        /* REQUIRED: not set */
    /* vdc_soft_hi_dv */         0U,        /* REQUIRED: not set */
    /* vdc_hard_hi_dv */         0U,        /* REQUIRED: not set */

    /* pedal_rel_lo_permille */  30U,
    /* pedal_rel_hi_permille */  50U,
    /* pedal_brake_permille */   100U,
    /* pedal_rate_counts */      512U,
    /* pedal_frozen_ms */        3000U,

    /* lv_min_dv */              105U,      /* 10.5 V, xCU minimum operating supply is 10 V */
    /* lv_max_dv */              160U,

    /* temp_warn_c */            0U,        /* off until iNetic thresholds known */

    /* gear_cmd */               0U,        /* neutral. Set to 1 for a forward bench test */
    /* demand_limit_high_raw */  0U,
    /* demand_limit_low_raw */   0U,

    /* brake_active_high */      1U
};

/* reason codes returned by cal_validate */
#define CAL_OK              0U
#define CAL_BAD_STEP        1U
#define CAL_BAD_TIMING      2U
#define CAL_TORQUE_UNSET    3U
#define CAL_TORQUE_RANGE    4U
#define CAL_SPEED_UNSET     5U
#define CAL_VDC_UNSET       6U
#define CAL_VDC_ORDER       7U
#define CAL_PEDAL           8U
#define CAL_LV              9U
#define CAL_FIELD          10U

#define TORQUE_RAW_LIMIT_NM   5000     /* Demand_Torque DBC range */
#define SPEED_RAW_LIMIT_RPM   15000    /* MotorSpeed DBC range */
#define VDC_RAW_LIMIT_DV      10000    /* DC_Voltage DBC range, 1000 V */
#define DEMAND_LIMIT_RAW_MAX  3000     /* x4 = 12000, DBC range */

uint8_t cal_validate(const PowertrainCal *cal, uint8_t *reason)
{
    uint8_t r = CAL_OK;

    if ((cal->step_ms_min == 0U) || (cal->step_ms_min > cal->step_ms_max)) {
        r = CAL_BAD_STEP;
    } else if ((cal->ld_timeout_ms == 0U) || (cal->drv_timeout_ms == 0U) ||
               (cal->live_stuck_ms == 0U) || (cal->precharge_timeout_ms == 0U) ||
               (cal->pedal_frozen_ms == 0U)) {
        r = CAL_BAD_TIMING;
    } else if (cal->torque_max_nm <= 0) {
        r = CAL_TORQUE_UNSET;
    } else if ((cal->torque_max_nm > TORQUE_RAW_LIMIT_NM) || (cal->regen_max_nm < 0) ||
               (cal->regen_max_nm > TORQUE_RAW_LIMIT_NM)) {
        r = CAL_TORQUE_RANGE;
    } else if (cal->speed_max_rpm == 0U) {
        r = CAL_SPEED_UNSET;
    } else if (cal->speed_max_rpm > SPEED_RAW_LIMIT_RPM) {
        r = CAL_SPEED_UNSET;
    } else if ((cal->vdc_hard_lo_dv == 0U) || (cal->vdc_soft_lo_dv == 0U) ||
               (cal->vdc_soft_hi_dv == 0U) || (cal->vdc_hard_hi_dv == 0U)) {
        r = CAL_VDC_UNSET;
    } else if ((cal->vdc_hard_lo_dv >= cal->vdc_soft_lo_dv) ||
               (cal->vdc_soft_lo_dv >= cal->vdc_soft_hi_dv) ||
               (cal->vdc_soft_hi_dv >= cal->vdc_hard_hi_dv) ||
               (cal->vdc_hard_hi_dv > VDC_RAW_LIMIT_DV)) {
        r = CAL_VDC_ORDER;
    } else if ((cal->pedal_rel_lo_permille >= cal->pedal_rel_hi_permille) ||
               (cal->pedal_rel_hi_permille > 200U) ||
               (cal->pedal_rate_counts == 0U) || (cal->pedal_rate_counts > 1023U)) {
        r = CAL_PEDAL;
    } else if ((cal->lv_min_dv == 0U) || (cal->lv_min_dv >= cal->lv_max_dv)) {
        r = CAL_LV;
    } else if ((cal->l1_derate_percent == 0U) || (cal->l1_derate_percent > 100U) ||
               (cal->gear_cmd > 2U) ||
               (cal->demand_limit_high_raw > DEMAND_LIMIT_RAW_MAX) ||
               (cal->demand_limit_low_raw > DEMAND_LIMIT_RAW_MAX) ||
               (cal->ld_rx_dlc > 8U)) {
        r = CAL_FIELD;
    } else {
        r = CAL_OK;
    }

    if (reason != 0) {
        *reason = r;
    }
    return (r == CAL_OK) ? 1U : 0U;
}
