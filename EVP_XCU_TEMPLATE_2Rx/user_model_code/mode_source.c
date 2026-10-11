/*
 * mode_source.c
 *
 * See mode_source.h.
 */

#include "mode_source.h"

static uint16_t sat_add16(uint16_t a, uint16_t b)
{
    uint32_t s = (uint32_t)a + (uint32_t)b;
    return (s > 0xFFFFUL) ? (uint16_t)0xFFFFU : (uint16_t)s;
}

void mode_src_init(ModeSrc *m)
{
    m->age_ms       = 0U;
    m->same_ms      = 0U;
    m->last_counter = 0U;
    m->seen         = 0U;
    m->bad          = 0U;
    m->mode_latest  = MODE_ENGINE_ONLY;
}

uint8_t mode_src_step(ModeSrc *m, uint8_t is_new, uint8_t len, const uint8_t data[8],
                      const PowertrainCal *cal, uint16_t dt_ms, DriveMode *mode)
{
    uint8_t valid;

    if (is_new != 0U) {
        m->age_ms = 0U;
        if ((len < 2U) || (data[0] > (uint8_t)MODE_HYBRID)) {
            m->bad = 1U;
        } else {
            m->bad         = 0U;
            m->mode_latest = (DriveMode)data[0];
            if ((m->seen == 0U) || (data[1] != m->last_counter)) {
                m->same_ms = 0U;
            }
            m->last_counter = data[1];
            m->seen         = 1U;
        }
    } else {
        m->age_ms = sat_add16(m->age_ms, dt_ms);
    }
    m->same_ms = sat_add16(m->same_ms, dt_ms);

    valid = ((m->seen != 0U) && (m->bad == 0U) &&
             (m->age_ms < cal->mode_timeout_ms) &&
             (m->same_ms < cal->mode_stuck_ms)) ? 1U : 0U;

    *mode = (valid != 0U) ? m->mode_latest : MODE_ENGINE_ONLY;
    return valid;
}
