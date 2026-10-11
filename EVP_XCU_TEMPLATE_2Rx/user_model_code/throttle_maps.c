/*
 * throttle_maps.c
 *
 * EDIT THIS FILE to change how pedal position maps to motor torque.
 *
 * How to read a map
 *   pedal_permille  pedal position, 0 = released, 1000 = fully pressed.
 *                   First point must be 0, last must be 1000, strictly
 *                   ascending. The xCU interpolates linearly between points.
 *   torque_nm       motor torque requested at that pedal position, in Nm.
 *                   Positive drives, negative regenerates.
 *   rise / fall     how fast torque may move up or down, in Nm per second.
 *                   A fault removes torque immediately, these do not apply.
 *
 * Limits applied after the map, in this order
 *   - CAL torque_max_nm (powertrain_cal.c) caps positive torque.
 *   - regen_max_nm caps negative torque. It is 0 until you set it, which
 *     means every negative number below is clamped to 0.
 *   - The drive's own TorqueLimit_High and TorqueLimit_Low.
 *   - Level 1 derate.
 * A map point above torque_max_nm is refused at start-up (fault F_SY_CAL).
 *
 * Modes
 *   MODE_ENGINE_ONLY   motor torque is always zero.
 *   MODE_EV, MODE_HYBRID
 *     In this build the diesel still follows the pedal in every mode. The LD
 *     controller is listen-only until its 0x104 throttle target is confirmed,
 *     so EV mode cannot yet hold the engine at idle. The two maps differ in
 *     motor torque only.
 *
 * Mode is requested by the display on CAN1, ID 0x302 (see mode_source.h):
 * byte 0 = 0 Engine only, 1 EV, 2 Hybrid, byte 1 = rolling counter. A
 * missing, invalid or frozen request means Engine only at once. The first
 * valid request after power-on is taken immediately. Later changes only
 * take effect while the pedal is released.
 *
 * The shipped numbers are small bench values, not tuned values.
 */

#include "throttle_maps.h"

const ThrottleMap g_throttleMaps[MODE_COUNT] = {
    /* MODE_ENGINE_ONLY */
    {
        /* pedal permille */ {    0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 },
        /* torque Nm      */ {    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0 },
        /* rise, fall     */ 50U, 100U
    },

    /* MODE_EV */
    {
        /* pedal permille */ {    0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 },
        /* torque Nm      */ {    0,   3,   6,   9,  12,  15,  18,  21,  24,  27,   30 },
        /* rise, fall     */ 50U, 100U
    },

    /* MODE_HYBRID */
    {
        /* pedal permille */ {    0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 },
        /* torque Nm      */ {    0,   2,   3,   5,   6,   8,   9,  11,  12,  14,   15 },
        /* rise, fall     */ 50U, 100U
    }
};

/* hard limits on the numbers above. Not data, do not edit. */
uint8_t maps_validate(const ThrottleMap *maps, int16_t torque_max_nm)
{
    uint8_t m;
    uint8_t i;
    uint8_t ok = 1U;

    for (m = 0U; m < (uint8_t)MODE_COUNT; m++) {
        if ((maps[m].pedal_permille[0] != 0) ||
            (maps[m].pedal_permille[MAP_POINTS - 1U] != 1000)) {
            ok = 0U;
        }
        for (i = 1U; i < (uint8_t)MAP_POINTS; i++) {
            if (maps[m].pedal_permille[i] <= maps[m].pedal_permille[i - 1U]) {
                ok = 0U;
            }
        }
        for (i = 0U; i < (uint8_t)MAP_POINTS; i++) {
            if (maps[m].torque_nm[i] > torque_max_nm) {
                ok = 0U;
            }
        }
        if ((maps[m].rise_nm_per_s == 0U) || (maps[m].rise_nm_per_s > 5000U) ||
            (maps[m].fall_nm_per_s == 0U) || (maps[m].fall_nm_per_s > 5000U)) {
            ok = 0U;
        }
    }
    return ok;
}
