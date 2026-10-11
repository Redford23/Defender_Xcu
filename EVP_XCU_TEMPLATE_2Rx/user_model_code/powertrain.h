/*
 * powertrain.h
 *
 * Hybrid supervisor step. Takes the raw frames and switch states read by
 * user_model.c, runs decode, monitors, fault manager, state machine, torque
 * request and the safety gate, and returns the final drive command.
 *
 * No hardware access in this module, so the whole chain runs on a PC.
 */

#ifndef POWERTRAIN_H_
#define POWERTRAIN_H_

#include <stdint.h>
#include "powertrain_cal.h"
#include "throttle_maps.h"
#include "can_codec.h"
#include "monitors.h"
#include "fault_mgr.h"
#include "drive_sm.h"
#include "torque_request.h"
#include "safety_gate.h"

typedef struct {
    /* LD 0x100 */
    uint8_t  ld_new;
    uint8_t  ld_len;
    uint8_t  ld_data[8];

    /* iNetic S1..S4, index SF_S1..SF_S4 */
    uint8_t  s_new[SF_COUNT];
    uint8_t  s_len[SF_COUNT];
    uint8_t  s_data[SF_COUNT][8];

    /* digital inputs as read (1 = high) */
    uint8_t  din_mode_ev;
    uint8_t  din_mode_hybrid;
    uint8_t  din_mode_engine;
    uint8_t  din_brake;

    uint16_t lv_dv;         /* LV supply, 0.1 V */
    uint8_t  uds_inhibit;   /* template UDS programming session active */
} PtInputs;

typedef struct {
    DriveCommand cmd;       /* final command from the gate */
    uint8_t  state;         /* SmStateId */
    uint8_t  level;
    uint8_t  mode;          /* DriveMode in use */
    uint8_t  fault_count;
    uint8_t  last_fault;    /* FaultId + 1, 0 none */
    uint32_t active;        /* fault bitmask */
    uint32_t latched;
    int16_t  torque_req_nm; /* what the map asked for after limits, before the gate */
    uint16_t pedal_permille;
    uint8_t  cal_reason;
} PtOutputs;

typedef struct {
    const PowertrainCal *cal;
    const ThrottleMap   *maps;
    uint16_t   step_ms;
    uint8_t    cal_ok;
    uint8_t    cal_reason;
    uint8_t    step_ok;

    MonState   mon;
    FaultMgr   fm;
    SmState    sm;
    TqState    tq;

    uint8_t    ld_have;
    uint8_t    ld_len_ok;
    LdStatus   ld;
    uint8_t    s_have[SF_COUNT];
    uint8_t    s_len_ok[SF_COUNT];
    DriveStatus1 s1;
    DriveStatus2 s2;
    DriveStatus3 s3;
    uint8_t    live[SF_COUNT];

    uint8_t    pedal_released;
    uint8_t    prev_brake;
    uint8_t    cmd_enable;
    int16_t    cmd_torque_nm;
    uint8_t    clamped_by_drive;
} Powertrain;

void pt_init(Powertrain *p, const PowertrainCal *cal, const ThrottleMap *maps, uint16_t step_ms);
void pt_step(Powertrain *p, const PtInputs *in, PtOutputs *out);

#endif /* POWERTRAIN_H_ */
