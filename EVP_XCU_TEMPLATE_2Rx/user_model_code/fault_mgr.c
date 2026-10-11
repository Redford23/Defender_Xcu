/*
 * fault_mgr.c
 *
 * See fault_mgr.h. Times here are the proposals in fault_matrix.md and are
 * for Red to set. Where a monitor times its own condition (frame timeouts,
 * frozen pedal) the debounce below is 0.
 */

#include "fault_mgr.h"

#define LEVEL_MAX 3U

/*                          level latch     debounce clear  escal  escal level */
const FaultDef g_faultDefs[F_COUNT] = {
    /* F_DD_TIMEOUT  */ { 2U, LATCH_DL,       0U,   500U,    0U,   0U },
    /* F_DD_RANGE    */ { 2U, LATCH_DL,       0U,   500U,    0U,   0U },
    /* F_DD_FROZEN   */ { 2U, LATCH_DL,       0U,   500U,    0U,   0U },
    /* F_DD_RATE     */ { 2U, LATCH_DL,       0U,   500U,    0U,   0U },
    /* F_BR_PEDAL    */ { 2U, LATCH_NL,     100U,   200U,    0U,   0U },
    /* F_DR_TIMEOUT  */ { 2U, LATCH_DL,       0U,   500U,  500U,   3U },
    /* F_DR_LIVE     */ { 2U, LATCH_DL,       0U,   500U,  500U,   3U },
    /* F_DR_FG1      */ { 1U, LATCH_NL,      50U,  1000U,    0U,   0U },
    /* F_DR_FG2      */ { 2U, LATCH_DL,       0U,   500U,    0U,   0U },
    /* F_DR_FG34     */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_DR_FG_UNDEF */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_DR_IGBT     */ { 3U, LATCH_KL,     300U,     0U,    0U,   0U },
    /* F_DR_TRACK    */ { 2U, LATCH_DL,     300U,   500U, 1000U,   3U },
    /* F_DR_SIGN     */ { 3U, LATCH_KL,     100U,     0U,    0U,   0U },
    /* F_DR_OVERSPEED*/ { 2U, LATCH_DL,      50U,   500U,  500U,   3U },
    /* F_DR_CLAMP    */ { 1U, LATCH_NL,       0U,   200U,    0U,   0U },
    /* F_DR_LIMITS   */ { 2U, LATCH_DL,     100U,   500U,    0U,   0U },
    /* F_DR_WARN     */ { 1U, LATCH_NL,     500U,  5000U,    0U,   0U },
    /* F_DR_VDC_SOFT */ { 2U, LATCH_DL,     100U,   500U,    0U,   0U },
    /* F_DR_VDC_HARD */ { 3U, LATCH_KL,      50U,     0U,    0U,   0U },
    /* F_DR_PRECHARGE*/ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_DR_DTC      */ { 2U, LATCH_DL,      50U,   500U,    0U,   0U },
    /* F_DR_RAW      */ { 2U, LATCH_DL,      20U,   500U,    0U,   0U },
    /* F_DR_ACTDISCH */ { 3U, LATCH_KL,     100U,     0U,    0U,   0U },
    /* F_SY_LV       */ { 2U, LATCH_DL,     200U,  1000U,    0U,   0U },
    /* F_SY_STATE    */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_SY_REDUND   */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_SY_UDS      */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_SY_CAL      */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U },
    /* F_SY_STEP     */ { 3U, LATCH_KL,       0U,     0U,    0U,   0U }
};

static uint16_t sat_add16(uint16_t a, uint16_t b)
{
    uint32_t s = (uint32_t)a + (uint32_t)b;
    return (s > 0xFFFFUL) ? (uint16_t)0xFFFFU : (uint16_t)s;
}

void fm_init(FaultMgr *fm)
{
    uint8_t i;

    for (i = 0U; i < (uint8_t)F_COUNT; i++) {
        fm->on_ms[i]  = 0U;
        fm->off_ms[i] = 0U;
        fm->act_ms[i] = 0U;
    }
    fm->active    = 0UL;
    fm->latched   = 0UL;
    fm->escalated = 0UL;
    fm->level     = 0U;
    fm->level_inv = (uint8_t)~0U;
    fm->count     = 0U;
    fm->last      = 0U;
}

void fm_step(FaultMgr *fm, const uint8_t cond[F_COUNT], uint16_t dt_ms, uint8_t clear_request)
{
    uint8_t  i;
    uint32_t bit;
    uint8_t  lvl = 0U;
    uint8_t  l;
    const FaultDef *d;

    for (i = 0U; i < (uint8_t)F_COUNT; i++) {
        bit = (uint32_t)1UL << i;
        d   = &g_faultDefs[i];

        if (cond[i] != 0U) {
            fm->off_ms[i] = 0U;
            fm->on_ms[i]  = sat_add16(fm->on_ms[i], dt_ms);
            if (fm->on_ms[i] >= d->debounce_ms) {
                if ((fm->active & bit) == 0UL) {
                    fm->active |= bit;
                    if (fm->count < 255U) {
                        fm->count++;
                    }
                    fm->last = (uint8_t)(i + 1U);
                }
            }
        } else {
            fm->on_ms[i]  = 0U;
            fm->off_ms[i] = sat_add16(fm->off_ms[i], dt_ms);
            if (fm->off_ms[i] >= d->clear_ms) {
                fm->active &= ~bit;
            }
        }

        if ((fm->active & bit) != 0UL) {
            if (d->latch != (uint8_t)LATCH_NL) {
                fm->latched |= bit;
            }
            fm->act_ms[i] = sat_add16(fm->act_ms[i], dt_ms);
            if ((d->escalate_ms != 0U) && (fm->act_ms[i] >= d->escalate_ms)) {
                fm->escalated |= bit;
                fm->latched   |= bit;   /* an escalated fault is key latched */
            }
        } else {
            fm->act_ms[i] = 0U;
        }

        /* driver action releases a driver-latched fault whose condition has gone */
        if ((clear_request != 0U) && (d->latch == (uint8_t)LATCH_DL) &&
            ((fm->active & bit) == 0UL) && ((fm->escalated & bit) == 0UL)) {
            fm->latched &= ~bit;
        }
    }

    for (i = 0U; i < (uint8_t)F_COUNT; i++) {
        bit = (uint32_t)1UL << i;
        if (((fm->active | fm->latched) & bit) != 0UL) {
            d = &g_faultDefs[i];
            l = ((fm->escalated & bit) != 0UL) ? d->escalate_level : d->level;
            if (l > lvl) {
                lvl = l;
            }
        }
    }
    if (lvl > LEVEL_MAX) {
        lvl = LEVEL_MAX;
    }
    fm->level     = lvl;
    fm->level_inv = (uint8_t)~lvl;
}

uint8_t fm_level_ok(const FaultMgr *fm)
{
    return ((uint8_t)(fm->level ^ fm->level_inv) == 0xFFU) ? 1U : 0U;
}
