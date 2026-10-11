/*
 * can_codec.h
 *
 * Pack and unpack the powertrain frames. Pure functions, no hardware access.
 *
 * iNetic drive (docs VCUmotor_ISG_20241216.dbc): 29-bit IDs, every signal
 * unsigned and LITTLE-endian. LD controller: 11-bit IDs, BIG-endian.
 * The MCU is big-endian, so everything is packed byte by byte. No structs,
 * bitfields or memcpy on the wire data.
 */

#ifndef CAN_CODEC_H_
#define CAN_CODEC_H_

#include <stdint.h>

/* iNetic drive, 29-bit */
#define ID_ISG_HCU_COMMAND   0x0CFF08EFUL
#define ID_ISG_MCU_STATUS1   0x0CFF0008UL
#define ID_ISG_MCU_STATUS2   0x0CFF0108UL
#define ID_ISG_MCU_STATUS3   0x0CFF0208UL
#define ID_ISG_MCU_STATUS4   0x0CFF0308UL

/* LD Performance throttle controller, 11-bit */
#define ID_LD_STATUS         0x100UL

/* raw offsets from the DBC */
#define RAW_TORQUE_ZERO      5000
#define RAW_SPEED_ZERO       15000

/* Control_Mode values */
#define CONTROL_MODE_TORQUE  2U

typedef struct {
    uint8_t  enable;         /* MCU_Enable */
    uint8_t  fault_reset;
    uint8_t  control_mode;
    uint8_t  gear;           /* 0 neutral, 1 forward, 2 reverse */
    uint8_t  foot_brake;
    uint8_t  handbrake;
    uint16_t limit_high_raw; /* 12 bit raw, x4 on the wire scale */
    uint16_t limit_low_raw;
    int16_t  torque_nm;
    int16_t  speed_rpm;      /* always zero, speed mode is not used */
} DriveCommand;

typedef struct {
    int32_t  speed_rpm;      /* raw - 15000 */
    uint16_t speed_raw;
    int32_t  torque_nm;      /* raw - 5000 */
    uint16_t torque_raw;
    uint16_t ac_current_da;  /* 0.1 A, magnitude */
    uint8_t  precharge_allow;
    uint8_t  active_discharge_fb;
    uint8_t  igbt_fb;
    uint8_t  live;
} DriveStatus1;

typedef struct {
    int16_t  motor_temp_c;
    int16_t  mcu_temp_c;
    uint16_t limit_high_nm;  /* TorqueLimit_High */
    int32_t  limit_low_nm;   /* TorqueLimit_Low, raw - 5000 */
    uint16_t limit_low_raw;
    uint8_t  fail_grade;
    uint8_t  live;
} DriveStatus2;

typedef struct {
    uint8_t  dtc0;           /* byte 0, bit 0 DC_Overvoltage .. bit 7 CANCommsFault */
    uint8_t  dtc1;           /* byte 1, bit 0 HardwareFault .. bit 6 ControllerOvervoltWarn */
    int32_t  dc_current_a;   /* raw - 1000 */
    uint16_t dc_voltage_dv;  /* 0.1 V */
    uint8_t  rotation_count;
    uint8_t  live;
} DriveStatus3;

typedef struct {
    uint16_t pedal_raw;      /* 0..1023 */
    uint16_t throttle_raw;   /* 0..1023 */
} LdStatus;

/* The safe command: enable off, torque mode, zero torque, zero speed with
 * offsets. Every cycle starts from this. An all-zero frame is -5000 Nm. */
void codec_safe_command(DriveCommand *cmd);

/* Encodes into data[8]. Torque and speed saturate to the DBC range. */
void codec_encode_command(const DriveCommand *cmd, uint8_t data[8]);

/* Each decode returns 1 if the length is sufficient, else 0 and out is untouched */
uint8_t codec_decode_status1(const uint8_t *data, uint8_t len, DriveStatus1 *out);
uint8_t codec_decode_status2(const uint8_t *data, uint8_t len, DriveStatus2 *out);
uint8_t codec_decode_status3(const uint8_t *data, uint8_t len, DriveStatus3 *out);
uint8_t codec_decode_status4(const uint8_t *data, uint8_t len, uint8_t *live);
uint8_t codec_decode_ld(const uint8_t *data, uint8_t len, LdStatus *out);

#endif /* CAN_CODEC_H_ */
