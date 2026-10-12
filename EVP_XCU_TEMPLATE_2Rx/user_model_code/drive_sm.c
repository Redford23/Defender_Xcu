/*
 * drive_sm.c
 *
 * See drive_sm.h.
 */

#include "drive_sm.h"

#define INIT_SETTLE_MS     500U
#define VDC_STABLE_MS      500U

static uint16_t sat_add16(uint16_t a, uint16_t b)
{
    uint32_t s = (uint32_t)a + (uint32_t)b;
    return (s > 0xFFFFUL) ? (uint16_t)0xFFFFU : (uint16_t)s;
}

static void set_state(SmState *s, uint8_t st)
{
    s->state     = st;
    s->state_inv = (uint8_t)~st;
    s->state_ms  = 0U;
}

void sm_init(SmState *s)
{
    set_state(s, (uint8_t)SM_INIT);
    s->vdc_ok_ms = 0U;
    s->enable    = 0U;
    s->hv_up     = 0U;
}

uint8_t sm_state_ok(const SmState *s)
{
    if (s->state > (uint8_t)SM_SHUTDOWN) {
        return 0U;
    }
    return ((uint8_t)(s->state ^ s->state_inv) == 0xFFU) ? 1U : 0U;
}

void sm_step(SmState *s, const SmInputs *in, SmOutputs *out)
{
    uint8_t next = s->state;

    s->state_ms = sat_add16(s->state_ms, in->dt_ms);

    if (sm_state_ok(s) == 0U) {
        next = (uint8_t)SM_SHUTDOWN;
    } else if (in->level >= 3U) {
        next = (uint8_t)SM_SHUTDOWN;
    } else {
        switch (s->state) {
        case SM_INIT:
            if ((in->init_ok != 0U) && (s->state_ms >= INIT_SETTLE_MS)) {
                next = (uint8_t)SM_STANDBY;
            }
            break;

        case SM_STANDBY:
            if ((in->level == 0U) && (in->drive_seen != 0U) && (in->pedal_released != 0U)) {
                next = (uint8_t)SM_PRECHARGE;
            }
            break;

        case SM_PRECHARGE:
            if (in->level >= 2U) {
                next = (uint8_t)SM_FAULT;
            } else {
                if (in->vdc_ok != 0U) {
                    s->vdc_ok_ms = sat_add16(s->vdc_ok_ms, in->dt_ms);
                } else {
                    s->vdc_ok_ms = 0U;
                }
                if (s->vdc_ok_ms >= VDC_STABLE_MS) {
                    next = (uint8_t)SM_READY;
                }
            }
            break;

        case SM_READY:
            if (in->level >= 2U) {
                next = (uint8_t)SM_FAULT;
            } else if ((in->level == 0U) && (in->igbt_fb != 0U) &&
                       (in->pedal_released != 0U) && (in->brake_pressed != 0U) &&
                       (in->vdc_ok != 0U)) {
                next = (uint8_t)SM_DRIVE;
            }
            break;

        case SM_DRIVE:
            if (in->level >= 2U) {
                next = (uint8_t)SM_FAULT;
            }
            break;

        case SM_FAULT:
            if (in->level < 2U) {
                next = ((s->enable != 0U) && (in->igbt_fb != 0U))
                       ? (uint8_t)SM_READY : (uint8_t)SM_STANDBY;
            }
            break;

        case SM_SHUTDOWN:
            break;

        default:
            next = (uint8_t)SM_FAULT;
            break;
        }
    }

    if (next != s->state) {
        set_state(s, next);
        s->vdc_ok_ms = 0U;
    }

    switch (s->state) {
    case SM_READY:
        s->enable = 1U;
        break;
    case SM_DRIVE:
        s->enable = 1U;
        break;
    case SM_FAULT:
        if (in->l2_drops_enable != 0U) {
            s->enable = 0U;  /* level 2: MCU_Enable dropped. Else unchanged */
        }
        break;
    default:
        s->enable = 0U;
        break;
    }

    if ((s->state == (uint8_t)SM_READY) || (s->state == (uint8_t)SM_DRIVE)) {
        s->hv_up = 1U;
    }

    out->state            = s->state;
    out->enable           = s->enable;
    out->allow_torque     = (s->state == (uint8_t)SM_DRIVE) ? 1U : 0U;
    out->hv_up            = s->hv_up;
    out->precharge_active = (s->state == (uint8_t)SM_PRECHARGE) ? 1U : 0U;
    out->state_ms         = s->state_ms;
}
