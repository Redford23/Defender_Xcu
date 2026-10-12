/*
 * drive_sm.h
 *
 * Supervisor state machine: INIT, STANDBY, PRECHARGE, READY, DRIVE, FAULT,
 * SHUTDOWN. The xCU does not command HV contactors in this build. PRECHARGE
 * waits for the DC link voltage the drive reports to reach its window.
 *
 *   state       MCU_Enable   torque
 *   INIT        0            0
 *   STANDBY     0            0
 *   PRECHARGE   0            0
 *   READY       1            0
 *   DRIVE       1            requested, through the safety gate
 *   FAULT       unchanged    0   (level 2, drive stays enabled if it was)
 *   SHUTDOWN    0            0   (level 3, key cycle to leave)
 */

#ifndef DRIVE_SM_H_
#define DRIVE_SM_H_

#include <stdint.h>

typedef enum {
    SM_INIT      = 0,
    SM_STANDBY   = 1,
    SM_PRECHARGE = 2,
    SM_READY     = 3,
    SM_DRIVE     = 4,
    SM_FAULT     = 5,
    SM_SHUTDOWN  = 6
} SmStateId;

typedef struct {
    uint8_t  state;
    uint8_t  state_inv;     /* ~state, redundancy check */
    uint16_t state_ms;
    uint16_t vdc_ok_ms;
    uint8_t  enable;
    uint8_t  hv_up;
} SmState;

typedef struct {
    uint8_t  level;
    uint8_t  init_ok;        /* calibration, maps and step period accepted */
    uint8_t  drive_seen;     /* all four status frames received */
    uint8_t  pedal_released;
    uint8_t  brake_pressed;
    uint8_t  vdc_ok;         /* DC voltage inside the soft window */
    uint8_t  igbt_fb;
    uint16_t dt_ms;
} SmInputs;

typedef struct {
    uint8_t  state;
    uint8_t  enable;
    uint8_t  allow_torque;
    uint8_t  hv_up;
    uint8_t  precharge_active;
    uint16_t state_ms;
} SmOutputs;

void    sm_init(SmState *s);
void    sm_step(SmState *s, const SmInputs *in, SmOutputs *out);

/* 0 if the stored state is out of range or fails its inverse copy */
uint8_t sm_state_ok(const SmState *s);

#endif /* DRIVE_SM_H_ */
