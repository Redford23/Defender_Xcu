/*
 * torque_request.c
 *
 * See torque_request.h.
 */

#include "torque_request.h"

#define MODE_CHANGE_STABLE_MS 200U

static uint16_t sat_add16(uint16_t a, uint16_t b)
{
    uint32_t s = (uint32_t)a + (uint32_t)b;
    return (s > 0xFFFFUL) ? (uint16_t)0xFFFFU : (uint16_t)s;
}

void tq_init(TqState *t)
{
    t->mode      = MODE_ENGINE_ONLY;
    t->requested = MODE_ENGINE_ONLY;
    t->req_ms    = 0U;
    t->have_mode = 0U;
    t->out_nm    = 0;
}

int32_t tq_interp(const ThrottleMap *map, uint16_t pedal_permille)
{
    uint8_t i;
    int32_t x = (int32_t)pedal_permille;
    int32_t x0;
    int32_t x1;
    int32_t y0;
    int32_t y1;
    int32_t span;

    if (x > 1000) {
        x = 1000;
    }
    for (i = 1U; i < (uint8_t)MAP_POINTS; i++) {
        if (x <= (int32_t)map->pedal_permille[i]) {
            x0   = (int32_t)map->pedal_permille[i - 1U];
            x1   = (int32_t)map->pedal_permille[i];
            y0   = (int32_t)map->torque_nm[i - 1U];
            y1   = (int32_t)map->torque_nm[i];
            span = x1 - x0;
            if (span <= 0) {
                return y1;
            }
            return y0 + (((y1 - y0) * (x - x0)) / span);
        }
    }
    return (int32_t)map->torque_nm[MAP_POINTS - 1U];
}

static int32_t clamp32(int32_t v, int32_t lo, int32_t hi)
{
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

void tq_step(TqState *t, const TqInputs *in, const PowertrainCal *cal,
             const ThrottleMap *maps, uint16_t dt_ms, TqOutputs *out)
{
    DriveMode sw;
    int32_t   target;
    int32_t   pos;
    int32_t   neg;
    int32_t   cur;
    int32_t   step;
    uint32_t  rate;

    out->clamped_by_drive = 0U;

    /* ---- mode: only changes with the pedal released ---------------------- */
    sw = in->mode_req;
    if (in->mode_valid == 0U) {
        /* source missing, invalid or frozen: motor torque does not carry on
         * under a mode nobody is requesting. Takes effect at once. */
        t->mode      = MODE_ENGINE_ONLY;
        t->requested = MODE_ENGINE_ONLY;
        t->req_ms    = 0U;
    } else if (t->have_mode == 0U) {
        /* first valid request since power-on: take it at once. No torque can
         * have been requested yet, DRIVE needs the pedal released. */
        t->mode      = sw;
        t->requested = sw;
        t->req_ms    = 0U;
        t->have_mode = 1U;
    } else if (sw == t->requested) {
        t->req_ms = sat_add16(t->req_ms, dt_ms);
    } else {
        t->requested = sw;
        t->req_ms    = 0U;
    }
    if ((t->requested != t->mode) && (t->req_ms >= MODE_CHANGE_STABLE_MS) &&
        (in->pedal_released != 0U)) {
        t->mode = t->requested;
    }
    out->mode = t->mode;

    /* ---- anything that forbids torque removes it at once ------------------ */
    if ((in->allow == 0U) || (in->level >= 2U) || (in->pedal_valid == 0U)) {
        t->out_nm      = 0;
        out->torque_nm = 0;
        return;
    }

    /* ---- map ---------------------------------------------------------------- */
    target = tq_interp(&maps[t->mode], in->pedal_permille);

    /* ---- limits ------------------------------------------------------------- */
    pos = (int32_t)cal->torque_max_nm;
    neg = -(int32_t)cal->regen_max_nm;

    if (in->limits_valid != 0U) {
        if ((int32_t)in->drive_hi_nm < pos) {
            pos = (int32_t)in->drive_hi_nm;
        }
        if ((int32_t)in->drive_lo_nm > neg) {
            neg = (int32_t)in->drive_lo_nm;
        }
        if ((target > (int32_t)in->drive_hi_nm) || (target < (int32_t)in->drive_lo_nm)) {
            out->clamped_by_drive = 1U;
        }
    }
    if (in->level == 1U) {
        pos = (pos * (int32_t)cal->l1_derate_percent) / 100;
        neg = (neg * (int32_t)cal->l1_derate_percent) / 100;
    }
    if (pos < 0) {
        pos = 0;
    }
    if (neg > 0) {
        neg = 0;
    }
    target = clamp32(target, neg, pos);

    /* ---- rate limit --------------------------------------------------------- */
    cur = (int32_t)t->out_nm;
    if (target > cur) {
        rate = (uint32_t)maps[t->mode].rise_nm_per_s;
        step = (int32_t)(((rate * (uint32_t)dt_ms) + 999UL) / 1000UL);
        cur  = (target - cur > step) ? (cur + step) : target;
    } else if (target < cur) {
        rate = (uint32_t)maps[t->mode].fall_nm_per_s;
        step = (int32_t)(((rate * (uint32_t)dt_ms) + 999UL) / 1000UL);
        cur  = (cur - target > step) ? (cur - step) : target;
    }
    cur = clamp32(cur, neg, pos);   /* a lowered limit takes effect at once */

    t->out_nm      = (int16_t)cur;
    out->torque_nm = (int16_t)cur;
}
