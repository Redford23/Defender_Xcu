/*
 * throttle_maps.h
 *
 * Pedal to motor torque maps, one per drive mode. The numbers are in
 * throttle_maps.c, which is the file to edit.
 */

#ifndef THROTTLE_MAPS_H_
#define THROTTLE_MAPS_H_

#include <stdint.h>

#define MAP_POINTS 11U

/* The switch positions map to these. Do not renumber. */
typedef enum {
    MODE_ENGINE_ONLY = 0,   /* motor torque zero everywhere, diesel only */
    MODE_EV          = 1,
    MODE_HYBRID      = 2
} DriveMode;

#define MODE_COUNT 3U

typedef struct {
    int16_t  pedal_permille[MAP_POINTS]; /* breakpoints, 0 to 1000, ascending */
    int16_t  torque_nm[MAP_POINTS];      /* + drive, - regen */
    uint16_t rise_nm_per_s;              /* torque moving up */
    uint16_t fall_nm_per_s;              /* torque moving down */
} ThrottleMap;

extern const ThrottleMap g_throttleMaps[MODE_COUNT];

/* Returns 1 if every map is inside hard limits. Checked at start-up. */
uint8_t maps_validate(const ThrottleMap *maps, int16_t torque_max_nm);

#endif /* THROTTLE_MAPS_H_ */
