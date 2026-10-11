/*
 * can_codec.c
 *
 * See can_codec.h. Bit positions are from VCUmotor_ISG_20241216.dbc.
 */

#include "can_codec.h"

#define STATUS_MIN_LEN 8U
#define LD_MIN_LEN     4U

/* little-endian 16 bit read from two bytes */
static uint16_t rd_le16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)p[0] | (uint16_t)((uint16_t)p[1] << 8));
}

/* big-endian 16 bit read, used for the LD controller only */
static uint16_t rd_be16(const uint8_t *p)
{
    return (uint16_t)((uint16_t)((uint16_t)p[0] << 8) | (uint16_t)p[1]);
}

static void wr_le16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)(v & 0xFFU);
    p[1] = (uint8_t)((v >> 8) & 0xFFU);
}

/* raw = value + offset, saturated to the 16 bit DBC range 0..2*offset */
static uint16_t to_raw(int32_t value, int32_t offset)
{
    int32_t raw = value + offset;
    int32_t top = offset * 2;

    if (raw < 0) {
        raw = 0;
    }
    if (raw > top) {
        raw = top;
    }
    return (uint16_t)raw;
}

void codec_safe_command(DriveCommand *cmd)
{
    cmd->enable         = 0U;
    cmd->fault_reset    = 0U;
    cmd->control_mode   = CONTROL_MODE_TORQUE;
    cmd->gear           = 0U;
    cmd->foot_brake     = 0U;
    cmd->handbrake      = 0U;
    cmd->limit_high_raw = 0U;
    cmd->limit_low_raw  = 0U;
    cmd->torque_nm      = 0;
    cmd->speed_rpm      = 0;
}

void codec_encode_command(const DriveCommand *cmd, uint8_t data[8])
{
    uint16_t torque_raw = to_raw((int32_t)cmd->torque_nm, RAW_TORQUE_ZERO);
    uint16_t speed_raw  = to_raw((int32_t)cmd->speed_rpm, RAW_SPEED_ZERO);
    uint16_t hi = (uint16_t)(cmd->limit_high_raw & 0x0FFFU);
    uint16_t lo = (uint16_t)(cmd->limit_low_raw & 0x0FFFU);

    /* byte 0: Enable bit 0, FaultReset bit 1, Control_Mode bits 2-3,
     * Gear bits 4-5, FootBrake bit 6, Handbrake bit 7 */
    data[0] = (uint8_t)((cmd->enable & 0x01U)
            | ((cmd->fault_reset & 0x01U) << 1)
            | ((cmd->control_mode & 0x03U) << 2)
            | ((cmd->gear & 0x03U) << 4)
            | ((cmd->foot_brake & 0x01U) << 6)
            | ((cmd->handbrake & 0x01U) << 7));

    /* Demand_Limit_High_Positive_Value bits 8..19, Low_Negative bits 20..31 */
    data[1] = (uint8_t)(hi & 0xFFU);
    data[2] = (uint8_t)(((hi >> 8) & 0x0FU) | ((lo & 0x0FU) << 4));
    data[3] = (uint8_t)((lo >> 4) & 0xFFU);

    /* Demand_Torque bits 32..47, Demand_Speed bits 48..63 */
    wr_le16(&data[4], torque_raw);
    wr_le16(&data[6], speed_raw);
}

uint8_t codec_decode_status1(const uint8_t *data, uint8_t len, DriveStatus1 *out)
{
    if (len < STATUS_MIN_LEN) {
        return 0U;
    }
    out->speed_raw          = rd_le16(&data[0]);
    out->speed_rpm          = (int32_t)out->speed_raw - RAW_SPEED_ZERO;
    out->torque_raw         = rd_le16(&data[2]);
    out->torque_nm          = (int32_t)out->torque_raw - RAW_TORQUE_ZERO;
    out->ac_current_da      = rd_le16(&data[4]);
    out->precharge_allow    = (uint8_t)((data[6] >> 4) & 0x01U);
    out->active_discharge_fb= (uint8_t)((data[6] >> 5) & 0x01U);
    out->igbt_fb            = (uint8_t)((data[6] >> 6) & 0x01U);
    out->live               = (uint8_t)((data[7] >> 4) & 0x0FU);
    return 1U;
}

uint8_t codec_decode_status2(const uint8_t *data, uint8_t len, DriveStatus2 *out)
{
    if (len < STATUS_MIN_LEN) {
        return 0U;
    }
    out->motor_temp_c   = (int16_t)((int16_t)data[0] - 40);
    out->mcu_temp_c     = (int16_t)((int16_t)data[1] - 40);
    out->limit_high_nm  = rd_le16(&data[2]);
    out->limit_low_raw  = rd_le16(&data[4]);
    out->limit_low_nm   = (int32_t)out->limit_low_raw - RAW_TORQUE_ZERO;
    out->fail_grade     = (uint8_t)(data[6] & 0x0FU);
    out->live           = (uint8_t)((data[7] >> 4) & 0x0FU);
    return 1U;
}

uint8_t codec_decode_status3(const uint8_t *data, uint8_t len, DriveStatus3 *out)
{
    if (len < STATUS_MIN_LEN) {
        return 0U;
    }
    out->dtc0           = data[0];
    out->dtc1           = data[1];
    out->dc_current_a   = (int32_t)rd_le16(&data[2]) - 1000;
    out->dc_voltage_dv  = rd_le16(&data[4]);
    out->rotation_count = data[6];
    out->live           = (uint8_t)((data[7] >> 4) & 0x0FU);
    return 1U;
}

uint8_t codec_decode_status4(const uint8_t *data, uint8_t len, uint8_t *live)
{
    if (len < STATUS_MIN_LEN) {
        return 0U;
    }
    *live = (uint8_t)((data[7] >> 4) & 0x0FU);
    return 1U;
}

uint8_t codec_decode_ld(const uint8_t *data, uint8_t len, LdStatus *out)
{
    if (len < LD_MIN_LEN) {
        return 0U;
    }
    out->pedal_raw    = rd_be16(&data[0]);
    out->throttle_raw = rd_be16(&data[2]);
    return 1U;
}
