/*
 * torque_request.h
 *
 * Mode selection, pedal to torque map, limits and rate limiting. Produces a
 * REQUEST only. The safety gate has the final say.
 */

#ifndef TORQUE_REQUEST_H_
#define TORQUE_REQUEST_H_

#include <stdint.h>
#include "powertrain_cal.h"
#include "throttle_maps.h"

typedef struct {
    DriveMode mode;        /* mode in use */
    DriveMode requested;   /* mode the switch is asking for */
    uint16_t  req_ms;      /* how long the switch has asked for it */
    int16_t   out_nm;      /* torque after rate limiting */
} TqState;

typedef struct {
    uint8_t  pedal_valid;
    uint16_t pedal_permille;
    uint8_t  pedal_released;
    uint8_t  allow;            /* state machine is in DRIVE */
    uint8_t  level;            /* safe-state level */
    uint8_t  sw_ev;            /* mode switch inputs, exactly one should be high */
    uint8_t  sw_hybrid;
    uint8_t  sw_engine;
    uint8_t  limits_valid;     /* drive torque limits received and sane */
    int16_t  drive_hi_nm;      /* TorqueLimit_High */
    int16_t  drive_lo_nm;      /* TorqueLimit_Low, zero or negative */
} TqInputs;

typedef struct {
    int16_t   torque_nm;
    uint8_t   clamped_by_drive;
    DriveMode mode;
} TqOutputs;

void tq_init(TqState *t);

/* Linear interpolation of one map. pedal above 1000 is treated as 1000. */
int32_t tq_interp(const ThrottleMap *map, uint16_t pedal_permille);

/* Switch decode. Exactly one input high selects a mode. Anything else
 * (none, or more than one, which includes an open wire) is ENGINE_ONLY. */
DriveMode tq_mode_from_switch(uint8_t ev, uint8_t hybrid, uint8_t engine);

void tq_step(TqState *t, const TqInputs *in, const PowertrainCal *cal,
             const ThrottleMap *maps, uint16_t dt_ms, TqOutputs *out);

#endif /* TORQUE_REQUEST_H_ */
