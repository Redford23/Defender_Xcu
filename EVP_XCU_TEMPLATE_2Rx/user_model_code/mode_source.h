/*
 * mode_source.h
 *
 * Qualifies the drive mode request received on CAN1 (ID 0x302 from the
 * display). Pure, no hardware access.
 *
 * Frame: byte 0 = mode (0 Engine only, 1 EV, 2 Hybrid), byte 1 = rolling
 * counter that changes on every frame. Anything else in the frame is ignored.
 *
 * The request is valid only while frames keep arriving, the mode value is
 * 0 to 2, and the counter keeps changing. Otherwise the mode is ENGINE_ONLY
 * (zero motor torque).
 */

#ifndef MODE_SOURCE_H_
#define MODE_SOURCE_H_

#include <stdint.h>
#include "powertrain_cal.h"
#include "throttle_maps.h"

#define ID_MODE_REQUEST 0x302UL   /* CAN1, 11-bit, DISPLAY to engine node */

typedef struct {
    uint16_t  age_ms;        /* since the last frame */
    uint16_t  same_ms;       /* since the counter last changed */
    uint8_t   last_counter;
    uint8_t   seen;
    uint8_t   bad;           /* latest frame was short or had an invalid mode */
    DriveMode mode_latest;
} ModeSrc;

void mode_src_init(ModeSrc *m);

/* Returns 1 if the request is valid this step. *mode is the requested
 * mode when valid, ENGINE_ONLY otherwise. */
uint8_t mode_src_step(ModeSrc *m, uint8_t is_new, uint8_t len, const uint8_t data[8],
                      const PowertrainCal *cal, uint16_t dt_ms, DriveMode *mode);

#endif /* MODE_SOURCE_H_ */
