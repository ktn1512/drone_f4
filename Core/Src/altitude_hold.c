#include "altitude_hold.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

/* PROTOTYPE ONLY: gains must be tuned on a safe, instrumented test rig.
 * Units: Kp height [1/s], Kp speed [us/(m/s)], Ki [us/m].
 */
#define ALT_MIN_US               1000.0f
#define ALT_MAX_US               1700.0f
#define ALT_MAX_CLIMB_MPS        0.40f
#define ALT_MAX_VZ_SETPOINT      0.60f
#define ALT_HEIGHT_KP            0.90f
#define ALT_VZ_KP               70.0f
#define ALT_VZ_KI               45.0f
#define ALT_VZ_FILTER_TAU        0.25f
#define ALT_I_LIMIT_US         320.0f
#define ALT_MAX_SLEW_US_PER_S  500.0f
#define ALT_TRIM_LEARN_RATE      0.15f

static float clampf(float x, float lo, float hi)
{
    return x < lo ? lo : (x > hi ? hi : x);
}

void AltitudeHold_Reset(AltitudeHold_t *ctrl)
{
    if (ctrl != NULL) memset(ctrl, 0, sizeof(*ctrl));
}

uint8_t AltitudeHold_Start(AltitudeHold_t *ctrl,
                           float altitude_m,
                           float initial_throttle_us,
                           uint32_t sample_ms)
{
    if (ctrl == NULL || !isfinite(altitude_m) ||
        !isfinite(initial_throttle_us) ||
        initial_throttle_us <= ALT_MIN_US ||
        initial_throttle_us > ALT_MAX_US)
        return 0U;

    AltitudeHold_Reset(ctrl);
    ctrl->active = 1U;
    ctrl->target_m = altitude_m;
    ctrl->altitude_m = altitude_m;
    ctrl->last_altitude_m = altitude_m;
    ctrl->last_sample_ms = sample_ms;
    ctrl->trim_us = initial_throttle_us;
    ctrl->throttle_us = initial_throttle_us;
    return 1U;
}

uint8_t AltitudeHold_Update(AltitudeHold_t *ctrl,
                            float altitude_m,
                            uint32_t sample_ms,
                            int16_t climb_percent)
{
    if (ctrl == NULL || !ctrl->active || !isfinite(altitude_m) ||
        climb_percent < -100 || climb_percent > 100)
        return 0U;

    const uint32_t dms = sample_ms - ctrl->last_sample_ms;
    if (dms == 0U) return 1U;  /* No duplicate sample update. */
    if (dms < 15U || dms > 180U) return 0U;
    const float dt = (float)dms * 0.001f;
    ctrl->last_sample_ms = sample_ms;

    /* Vertical velocity from *filtered* pressure height, not raw IMU az. */
    const float raw_vz = (altitude_m - ctrl->last_altitude_m) / dt;
    ctrl->last_altitude_m = altitude_m;
    ctrl->altitude_m = altitude_m;
    if (!isfinite(raw_vz) || fabsf(raw_vz) > 12.0f) return 0U;
    const float alpha = dt / (ALT_VZ_FILTER_TAU + dt);
    ctrl->vz_mps += alpha * (raw_vz - ctrl->vz_mps);

    float vz_sp;
    if (climb_percent != 0) {
        /* Pilot requests VERTICAL SPEED, not direct motor PWM. */
        vz_sp = (float)climb_percent * (ALT_MAX_CLIMB_MPS / 100.0f);
        ctrl->was_moving = 1U;
        /* Track while moving; snap exact target on release only. */
        ctrl->target_m = altitude_m;
    } else {
        if (ctrl->was_moving) {
            ctrl->target_m = altitude_m;
            ctrl->was_moving = 0U;
        }
        vz_sp = ALT_HEIGHT_KP * (ctrl->target_m - altitude_m);
    }
    vz_sp = clampf(vz_sp, -ALT_MAX_VZ_SETPOINT, ALT_MAX_VZ_SETPOINT);
    ctrl->vz_setpoint_mps = vz_sp;

    const float vz_error = vz_sp - ctrl->vz_mps;
    const float p_us = ALT_VZ_KP * vz_error;
    float i_next = clampf(ctrl->integral_us + ALT_VZ_KI * vz_error * dt,
                          -ALT_I_LIMIT_US, ALT_I_LIMIT_US);
    float unbounded = ctrl->trim_us + p_us + i_next;
    /* Keep integration out of motor saturation when error pushes further. */
    if (!((unbounded > ALT_MAX_US && vz_error > 0.0f) ||
          (unbounded < ALT_MIN_US && vz_error < 0.0f)))
        ctrl->integral_us = i_next;

    /* Integral is an adaptive hover-thrust correction. Transfer a small
     * portion into the trim without changing the total commanded output.
     */
    if (climb_percent == 0 &&
        fabsf(ctrl->target_m - altitude_m) < 0.12f &&
        fabsf(ctrl->vz_mps) < 0.12f) {
        float proposed = ctrl->integral_us * ALT_TRIM_LEARN_RATE * dt;
        float next_trim = clampf(ctrl->trim_us + proposed,
                                 ALT_MIN_US, ALT_MAX_US);
        ctrl->integral_us -= next_trim - ctrl->trim_us;
        ctrl->trim_us = next_trim;
    }

    const float desired = clampf(ctrl->trim_us + p_us + ctrl->integral_us,
                                  ALT_MIN_US, ALT_MAX_US);
    const float max_step = ALT_MAX_SLEW_US_PER_S * dt;
    ctrl->throttle_us = clampf(desired,
                                ctrl->throttle_us - max_step,
                                ctrl->throttle_us + max_step);
    ctrl->throttle_us = clampf(ctrl->throttle_us,
                                ALT_MIN_US, ALT_MAX_US);
    return 1U;
}

void AltitudeHold_AlignOutput(AltitudeHold_t *ctrl)
{
    if (ctrl == NULL || !ctrl->active || !isfinite(ctrl->throttle_us) ||
        !isfinite(ctrl->trim_us))
        return;
    ctrl->integral_us = clampf(ctrl->throttle_us - ctrl->trim_us,
                               -ALT_I_LIMIT_US, ALT_I_LIMIT_US);
}
