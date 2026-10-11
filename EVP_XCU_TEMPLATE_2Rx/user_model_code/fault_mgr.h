/*
 * fault_mgr.h
 *
 * One fault manager. Monitors only report conditions. This module owns
 * debounce, latching, escalation and the safe-state level. Nothing here
 * touches an output.
 *
 * Levels (higher wins): 0 normal, 1 derate, 2 zero torque with drive
 * enabled, 3 drive disabled. Level 4 (engine stop) is not implemented,
 * fuel shut-off wiring is not defined yet.
 *
 * Latch: NL clears itself, DL needs the condition gone plus a driver
 * action, KL clears only at the next power-on or reset.
 *
 * Rows correspond to docs\safety\fault_matrix.md.
 */

#ifndef FAULT_MGR_H_
#define FAULT_MGR_H_

#include <stdint.h>

/* The numeric value + 1 is the code broadcast as LastFaultCode. Do not
 * reorder without updating the broadcast and the matrix. */
typedef enum {
    F_DD_TIMEOUT = 0,   /* LD 0x100 not received */
    F_DD_RANGE,         /* pedal or throttle above 1023, or short frame */
    F_DD_FROZEN,        /* pedal value frozen */
    F_DD_RATE,          /* implausible pedal step */
    F_BR_PEDAL,         /* brake pressed with pedal applied */
    F_DR_TIMEOUT,       /* any iNetic status frame missing */
    F_DR_LIVE,          /* LiveCounter not incrementing */
    F_DR_FG1,           /* FailGrade 1 */
    F_DR_FG2,           /* FailGrade 2 */
    F_DR_FG34,          /* FailGrade 3 or 4 */
    F_DR_FG_UNDEF,      /* FailGrade 5..15 */
    F_DR_IGBT,          /* IGBT feedback does not match MCU_Enable */
    F_DR_TRACK,         /* measured torque disagrees with demand */
    F_DR_SIGN,          /* measured torque opposite to demand */
    F_DR_OVERSPEED,
    F_DR_CLAMP,         /* demand clamped by the drive's torque limits */
    F_DR_LIMITS,        /* drive torque limits invalid */
    F_DR_WARN,          /* drive warning bits or temperature */
    F_DR_VDC_SOFT,
    F_DR_VDC_HARD,
    F_DR_PRECHARGE,     /* precharge not complete in time */
    F_DR_DTC,           /* other DTC bit set */
    F_DR_RAW,           /* raw field out of physical range or short frame */
    F_DR_ACTDISCH,      /* active discharge while enabled */
    F_SY_LV,            /* LV supply out of window */
    F_SY_STATE,         /* state machine variable corrupt */
    F_SY_REDUND,        /* redundant copy mismatch */
    F_SY_UDS,           /* UDS programming session active */
    F_SY_CAL,           /* calibration or maps failed start-up check */
    F_SY_STEP,          /* step period outside accepted range */
    F_COUNT
} FaultId;

typedef enum { LATCH_NL = 0, LATCH_DL = 1, LATCH_KL = 2 } LatchType;

typedef struct {
    uint8_t  level;            /* base level 1..3 */
    uint8_t  latch;
    uint16_t debounce_ms;      /* condition must hold this long */
    uint16_t clear_ms;         /* condition must be absent this long */
    uint16_t escalate_ms;      /* 0 = no escalation */
    uint8_t  escalate_level;
} FaultDef;

extern const FaultDef g_faultDefs[F_COUNT];

typedef struct {
    uint16_t on_ms[F_COUNT];
    uint16_t off_ms[F_COUNT];
    uint16_t act_ms[F_COUNT];
    uint32_t active;
    uint32_t latched;
    uint32_t escalated;
    uint8_t  level;
    uint8_t  level_inv;        /* ~level, redundancy check */
    uint8_t  count;            /* faults raised since power-on, saturating */
    uint8_t  last;             /* FaultId + 1 of the most recent, 0 none */
} FaultMgr;

void    fm_init(FaultMgr *fm);

/* cond[i] is nonzero while fault i's condition is present this step.
 * clear_request is a one-step pulse meaning the driver has acted. */
void    fm_step(FaultMgr *fm, const uint8_t cond[F_COUNT], uint16_t dt_ms, uint8_t clear_request);

/* 1 if the redundant level copy agrees */
uint8_t fm_level_ok(const FaultMgr *fm);

#endif /* FAULT_MGR_H_ */
