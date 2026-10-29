#include "kalman_rp.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

#define KALMAN_RAD_TO_DEG 57.29577951308232f
#define KALMAN_DEFAULT_VARIANCE_DEG2 4.0f
#define KALMAN_DEFAULT_GYRO_NOISE_DPS2 1.0f
#define KALMAN_DEFAULT_ACCEL_NOISE_DEG2 9.0f
#define KALMAN_ACC_FULL_ERROR_G 0.10f
#define KALMAN_ACC_REJECT_ERROR_G 0.20f
#define KALMAN_MIN_NORM_G 0.0001f
#define KALMAN_MAX_DT_S 0.050f

static void Kalman1D_Init(Kalman1D_t *k, float initial_deg)
{
    memset(k, 0, sizeof(*k));
    k->angle_deg = initial_deg;
    k->variance_deg2 = KALMAN_DEFAULT_VARIANCE_DEG2;
    k->gyro_noise_dps2 = KALMAN_DEFAULT_GYRO_NOISE_DPS2;
    k->accel_noise_deg2 = KALMAN_DEFAULT_ACCEL_NOISE_DEG2;
    k->initialized = 1U;
}

static float Clamp01(float x)
{
    if (x < 0.0f) return 0.0f;
    if (x > 1.0f) return 1.0f;
    return x;
}

/* Used only for angle innovation; avoids roll's +/-180 degree jump. */
static float AngleDifferenceDeg(float measured, float predicted)
{
    float error = measured - predicted;
    while (error > 180.0f) error -= 360.0f;
    while (error < -180.0f) error += 360.0f;
    return error;
}

static void Kalman1D_Step(Kalman1D_t *k, float gyro_dps,
                          float measured_deg, float accel_weight, float dt_s)
{
    /* Predict: the same single-state formulation as ESP32_FC.
     * Q is gyro rate noise variance, hence delta(P) = dt^2 * Q. */
    k->angle_deg += gyro_dps * dt_s;
    k->variance_deg2 += (dt_s * dt_s) * k->gyro_noise_dps2;
    k->last_gain = 0.0f;

    /* Measurement weighting only: weight=0 means gyro-only prediction.
     * Increasing R reduces accelerometer influence under uncertain motion. */
    if (!(accel_weight > 0.0f) || !isfinite(measured_deg)) {
        ++k->accel_rejected_count;
        return;
    }

    const float measurement_variance = k->accel_noise_deg2 / accel_weight;
    const float gain = k->variance_deg2 /
                       (k->variance_deg2 + measurement_variance);
    k->angle_deg += gain * AngleDifferenceDeg(measured_deg, k->angle_deg);
    k->variance_deg2 *= (1.0f - gain);
    k->last_gain = gain;
    ++k->accel_used_count;
}

uint8_t KalmanRP_Init(KalmanRP_t *filter, float ax_g, float ay_g, float az_g)
{
    if (filter == NULL || !isfinite(ax_g) || !isfinite(ay_g) ||
        !isfinite(az_g)) return 0U;

    const float norm = sqrtf(ax_g * ax_g + ay_g * ay_g + az_g * az_g);
    if (!isfinite(norm) || norm < KALMAN_MIN_NORM_G) return 0U;

    memset(filter, 0, sizeof(*filter));
    filter->acc_roll_deg = atan2f(ay_g, az_g) * KALMAN_RAD_TO_DEG;
    filter->acc_pitch_deg = atan2f(-ax_g,
                                  sqrtf(ay_g * ay_g + az_g * az_g)) *
                                  KALMAN_RAD_TO_DEG;
    filter->accel_norm_g = norm;
    Kalman1D_Init(&filter->roll, filter->acc_roll_deg);
    Kalman1D_Init(&filter->pitch, filter->acc_pitch_deg);
    filter->initialized = 1U;
    return 1U;
}

uint8_t KalmanRP_SetNoise(KalmanRP_t *filter,
                          float gyro_noise_dps, float accel_noise_deg)
{
    if (filter == NULL || !filter->initialized ||
        !isfinite(gyro_noise_dps) || !isfinite(accel_noise_deg) ||
        gyro_noise_dps <= 0.0f || accel_noise_deg <= 0.0f) return 0U;

    const float q = gyro_noise_dps * gyro_noise_dps;
    const float r = accel_noise_deg * accel_noise_deg;
    if (!isfinite(q) || !isfinite(r) || q <= 0.0f || r <= 0.0f)
        return 0U;

    filter->roll.gyro_noise_dps2 = filter->pitch.gyro_noise_dps2 = q;
    filter->roll.accel_noise_deg2 = filter->pitch.accel_noise_deg2 = r;
    return 1U;
}

uint8_t KalmanRP_Update(KalmanRP_t *filter,
                        float gx_dps, float gy_dps,
                        float ax_g, float ay_g, float az_g,
                        float dt_s)
{
    if (filter == NULL || !filter->initialized ||
        !isfinite(dt_s) || dt_s <= 0.0f || dt_s > KALMAN_MAX_DT_S ||
        !isfinite(gx_dps) || !isfinite(gy_dps)) return 0U;

    float weight = 0.0f;
    float norm = 0.0f;
    float acc_roll = NAN;
    float acc_pitch = NAN;

    if (isfinite(ax_g) && isfinite(ay_g) && isfinite(az_g)) {
        norm = sqrtf(ax_g * ax_g + ay_g * ay_g + az_g * az_g);
        if (isfinite(norm) && norm >= KALMAN_MIN_NORM_G) {
            const float err = fabsf(norm - 1.0f);
            if (err <= KALMAN_ACC_FULL_ERROR_G) weight = 1.0f;
            else if (err < KALMAN_ACC_REJECT_ERROR_G) {
                weight = (KALMAN_ACC_REJECT_ERROR_G - err) /
                         (KALMAN_ACC_REJECT_ERROR_G - KALMAN_ACC_FULL_ERROR_G);
            }
            weight = Clamp01(weight);
            acc_roll = atan2f(ay_g, az_g) * KALMAN_RAD_TO_DEG;
            acc_pitch = atan2f(-ax_g,
                               sqrtf(ay_g * ay_g + az_g * az_g)) *
                               KALMAN_RAD_TO_DEG;
        }
    }

    filter->accel_weight = weight;
    filter->accel_norm_g = norm;
    filter->acc_roll_deg = acc_roll;
    filter->acc_pitch_deg = acc_pitch;

    Kalman1D_Step(&filter->roll, gx_dps, acc_roll, weight, dt_s);
    Kalman1D_Step(&filter->pitch, gy_dps, acc_pitch, weight, dt_s);
    return 1U;
}
