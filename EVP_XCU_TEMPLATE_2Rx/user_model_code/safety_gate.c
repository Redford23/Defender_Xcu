/*
 * safety_gate.c
 *
 * See safety_gate.h.
 */

#include "safety_gate.h"

#ifndef EVP_HOST_TEST
#include "can_input_simulink.h"
#endif

void gate_compute(const GateRequest *req, const PowertrainCal *cal, DriveCommand *cmd)
{
    int32_t t;
    int32_t pos;
    int32_t neg;

    /* start from the safe command */
    codec_safe_command(cmd);

    /* level 3 or above: disabled, zero torque, neutral. This is the safe command. */
    if (req->level >= 3U) {
        return;
    }

    /* the drive is only enabled when the state machine asks for it */
    if (req->enable == 0U) {
        return;
    }

    cmd->enable         = 1U;
    cmd->gear           = cal->gear_cmd;
    cmd->limit_high_raw = cal->demand_limit_high_raw;
    cmd->limit_low_raw  = cal->demand_limit_low_raw;

    /* level 2: zero torque. MCU_Enable is dropped unless the calibration keeps
     * the drive enabled (l2_drops_enable = 0). The diesel is unaffected. */
    if (req->level >= 2U) {
        if (cal->l2_drops_enable != 0U) {
            codec_safe_command(cmd);
        }
        return;
    }

    /* last clamp, independent of every earlier stage */
    pos = (int32_t)cal->torque_max_nm;
    neg = -(int32_t)cal->regen_max_nm;
    t   = (int32_t)req->torque_nm;
    if (t > pos) {
        t = pos;
    }
    if (t < neg) {
        t = neg;
    }
    cmd->torque_nm = (int16_t)t;
}

#ifndef EVP_HOST_TEST

static void write_digital_outputs(void)
{
    DIGITAL_OUTPUT_BUS out = {0};   /* all outputs off */

    out.canStandby1 = 0U;           /* CAN1: Stage 1 sensor data */
    out.canStandby2 = 0U;           /* CAN2: UDS */
    out.canStandby3 = 0U;           /* CAN3: powertrain */

    /* constants that switch the contactor pull-in/hold PWM function off */
    digitalOutputSet(out, 1000U, 100U, 100U, 40U, 156U);
}

void gate_init_outputs(void)
{
    write_digital_outputs();
}

void gate_commit(const DriveCommand *cmd, const PowertrainCal *cal)
{
    CAN_MESSAGE_BUS tx;
    uint8_t         i;

    tx.Extended  = 1U;
    tx.Length    = 8U;
    tx.Remote    = 0U;
    tx.Error     = 0U;
    tx.ID        = (unsigned int)ID_ISG_HCU_COMMAND;
    tx.Timestamp = 0.0;
    for (i = 0U; i < 8U; i++) {
        tx.Data[i] = 0U;
    }
    codec_encode_command(cmd, tx.Data);

    /* buffer 1 on CAN3, interval 0 = single shot per step */
    dcan3Messagebox1Transmit(tx, 1U, (double)cal->cmd_tx_interval_ms, 1.0);

    write_digital_outputs();
}

#endif /* EVP_HOST_TEST */
