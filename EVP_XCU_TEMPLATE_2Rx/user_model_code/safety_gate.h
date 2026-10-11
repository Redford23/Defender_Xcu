/*
 * safety_gate.h
 *
 * The one place that decides the final drive command and the digital
 * outputs. gate_compute() is pure. gate_commit() is the only code that
 * writes the drive command frame and the digital outputs to the hardware.
 *
 * Everything starts each cycle from the safe command (enable off, torque
 * mode, 0 Nm, 0 rpm, neutral) and has to earn anything else.
 */

#ifndef SAFETY_GATE_H_
#define SAFETY_GATE_H_

#include <stdint.h>
#include "powertrain_cal.h"
#include "can_codec.h"

typedef struct {
    uint8_t enable;       /* from the state machine */
    int16_t torque_nm;    /* from the torque request */
    uint8_t level;        /* from the fault manager */
} GateRequest;

void gate_compute(const GateRequest *req, const PowertrainCal *cal, DriveCommand *cmd);

#ifndef EVP_HOST_TEST
/* Writes every digital output off and the CAN transceiver standby pins.
 * No contactor, relay or fuel output is driven by this build. */
void gate_init_outputs(void);

/* Encodes cmd and transmits it on CAN3 (single shot per step if
 * cmd_tx_interval_ms is 0), then writes the digital outputs. */
void gate_commit(const DriveCommand *cmd, const PowertrainCal *cal);
#endif

#endif /* SAFETY_GATE_H_ */
