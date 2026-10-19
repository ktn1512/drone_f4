/*
 * Host regression tests for the angle -> rate -> motor command path.
 * These checks use the real controller defaults and implementation. They do
 * not simulate the airframe or establish the physical motor/IMU orientation.
 */
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "angle_controller.h"
#include "mixer.h"
#include "pid.h"
#include "rate_controller.h"

static const float dt_s = 0.002f;
static unsigned checks;

#define CHECK(condition, message)                                            \
    do {                                                                     \
        ++checks;                                                            \
        if (!(condition)) {                                                  \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, message); \
            exit(EXIT_FAILURE);                                              \
        }                                                                    \
    } while (0)

static int near(float actual, float expected, float tolerance)
{
    return isfinite(actual) && fabsf(actual - expected) <= tolerance;
}

static void check_reset(const PID_t *pid)
{
    CHECK(pid->initialized == 0U, "reset must clear initialization history");
    CHECK(near(pid->integral, 0.0f, 1.0e-6f), "reset must clear I");
    CHECK(near(pid->prev_error, 0.0f, 1.0e-6f), "reset must clear previous error");
    CHECK(near(pid->prev_feedback, 0.0f, 1.0e-6f), "reset must clear previous feedback");
    CHECK(near(pid->derivative_filtered, 0.0f, 1.0e-6f), "reset must clear filtered D history");
}

static void test_stationary_pitch_correction(void)
{
    const float pitch_samples[] = {-6.0f, 6.0f};

    for (size_t i = 0U; i < sizeof pitch_samples / sizeof pitch_samples[0]; ++i) {
        AngleController_t angle;
        RateController_t rate;
        MotorMixer_t motor;
        float roll_sp, pitch_sp, roll_out, pitch_out, yaw_out;
        AngleController_Init(&angle);
        RateController_Init(&rate);

        AngleController_Update(&angle, 0.0f, 0.0f, 0.0f, pitch_samples[i],
                               dt_s, &roll_sp, &pitch_sp);
        RateController_Update(&rate, roll_sp, pitch_sp, 0.0f,
                              0.0f, 0.0f, 0.0f, dt_s,
                              &roll_out, &pitch_out, &yaw_out);
        Mixer_QuadX(1300.0f, roll_out, pitch_out, yaw_out, &motor);

        CHECK(pitch_samples[i] * pitch_sp < 0.0f,
              "stationary pitch error must request an opposing angular rate");
        CHECK(pitch_samples[i] * pitch_out < 0.0f,
              "stationary pitch error must produce an opposing correction");
        CHECK(near(roll_out, 0.0f, 1.0e-6f) && near(yaw_out, 0.0f, 1.0e-6f),
              "pure pitch error must not command roll or yaw");
        CHECK(motor.m1 == motor.m2 && motor.m3 == motor.m4,
              "pure pitch correction must treat both motors on a side equally");
        if (pitch_samples[i] < 0.0f) {
            CHECK(motor.m3 > motor.m1 && motor.m4 > motor.m2,
                  "negative sensor pitch must raise left M3/M4 relative to right M1/M2");
        } else {
            CHECK(motor.m1 > motor.m3 && motor.m2 > motor.m4,
                  "positive sensor pitch must raise right M1/M2 relative to left M3/M4");
        }
        CHECK(motor.m1 > 1000U && motor.m1 < 1700U &&
              motor.m2 > 1000U && motor.m2 < 1700U &&
              motor.m3 > 1000U && motor.m3 < 1700U &&
              motor.m4 > 1000U && motor.m4 < 1700U,
              "the sign check must run without mixer clipping");
    }
}

static void test_angle_has_no_residual_rate_request(void)
{
    AngleController_t angle;
    float roll_sp, pitch_sp;
    AngleController_Init(&angle);

    /* Five seconds of tilt followed by a different tilt primes both histories. */
    for (unsigned i = 0U; i < 2500U; ++i) {
        AngleController_Update(&angle, 0.0f, 0.0f, 6.0f, -8.0f,
                               dt_s, &roll_sp, &pitch_sp);
    }
    for (unsigned i = 0U; i < 500U; ++i) {
        AngleController_Update(&angle, 0.0f, 0.0f, -3.0f, 4.0f,
                               dt_s, &roll_sp, &pitch_sp);
    }
    for (unsigned i = 0U; i < 20U; ++i) {
        AngleController_Update(&angle, 0.0f, 0.0f, 0.0f, 0.0f,
                               dt_s, &roll_sp, &pitch_sp);
        CHECK(near(roll_sp, 0.0f, 1.0e-6f),
              "default angle roll must stop requesting rate when level is restored");
        CHECK(near(pitch_sp, 0.0f, 1.0e-6f),
              "default angle pitch must stop requesting rate immediately when level is restored");
    }
}

static void test_rate_integral_is_effective_and_bounded(void)
{
    RateController_t rate;
    float roll_out, pitch_out, yaw_out;
    float first_roll = 0.0f, first_pitch = 0.0f;
    RateController_Init(&rate);

    for (unsigned i = 0U; i < 5000U; ++i) {
        RateController_Update(&rate, 12.0f, 12.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, dt_s,
                              &roll_out, &pitch_out, &yaw_out);
        if (i == 0U) {
            first_roll = roll_out;
            first_pitch = pitch_out;
        }
        CHECK(fabsf(rate.roll.integral) <= rate.roll.integral_limit + 1.0e-5f &&
              fabsf(rate.pitch.integral) <= rate.pitch.integral_limit + 1.0e-5f,
              "rate I must remain within its configured bound");
    }
    CHECK(roll_out > first_roll + 1.0f && pitch_out > first_pitch + 1.0f,
          "persistent rate error must build a useful I correction");
    CHECK(near(rate.roll.integral, rate.roll.integral_limit, 1.0e-4f) &&
          near(rate.pitch.integral, rate.pitch.integral_limit, 1.0e-4f),
          "persistent moderate error must eventually reach the positive I bound");

    RateController_Update(&rate, 0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, dt_s,
                          &roll_out, &pitch_out, &yaw_out);
    CHECK(roll_out > 0.0f && pitch_out > 0.0f,
          "rate I must retain a correction when instantaneous rate error vanishes");

    for (unsigned i = 0U; i < 10000U; ++i) {
        RateController_Update(&rate, -12.0f, -12.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, dt_s,
                              &roll_out, &pitch_out, &yaw_out);
        CHECK(fabsf(rate.roll.integral) <= rate.roll.integral_limit + 1.0e-5f &&
              fabsf(rate.pitch.integral) <= rate.pitch.integral_limit + 1.0e-5f,
              "reversed rate error must not exceed either I bound");
    }
    CHECK(near(rate.roll.integral, -rate.roll.integral_limit, 1.0e-4f) &&
          near(rate.pitch.integral, -rate.pitch.integral_limit, 1.0e-4f),
          "reversed error must unwind I and reach the negative bound");
}

static void test_minimum_throttle_reset_removes_residuals(void)
{
    AngleController_t angle;
    RateController_t rate;
    MotorMixer_t motor;
    float roll_sp, pitch_sp, roll_out, pitch_out, yaw_out;
    AngleController_Init(&angle);
    RateController_Init(&rate);

    for (unsigned i = 0U; i < 2500U; ++i) {
        AngleController_Update(&angle, 0.0f, 0.0f, 3.0f, -4.0f,
                               dt_s, &roll_sp, &pitch_sp);
        RateController_Update(&rate, roll_sp, pitch_sp, 0.0f,
                              1.0f, -2.0f, 3.0f, dt_s,
                              &roll_out, &pitch_out, &yaw_out);
    }
    CHECK(rate.pitch.integral > 0.0f && rate.roll.integral < 0.0f,
          "reset test must first create residual rate I on both axes");

    /* Same reset calls used by main.c when throttle is at minimum. */
    PID_Reset(&angle.roll);
    PID_Reset(&angle.pitch);
    PID_Reset(&rate.roll);
    PID_Reset(&rate.pitch);
    PID_Reset(&rate.yaw);
    check_reset(&angle.roll);
    check_reset(&angle.pitch);
    check_reset(&rate.roll);
    check_reset(&rate.pitch);
    check_reset(&rate.yaw);

    AngleController_Update(&angle, 0.0f, 0.0f, 0.0f, 0.0f,
                           dt_s, &roll_sp, &pitch_sp);
    RateController_Update(&rate, roll_sp, pitch_sp, 0.0f,
                          0.0f, 0.0f, 0.0f, dt_s,
                          &roll_out, &pitch_out, &yaw_out);
    CHECK(near(roll_out, 0.0f, 1.0e-6f) &&
          near(pitch_out, 0.0f, 1.0e-6f) && near(yaw_out, 0.0f, 1.0e-6f),
          "level stationary restart must have no residual motor correction");
    Mixer_QuadX(1300.0f, roll_out, pitch_out, yaw_out, &motor);
    CHECK(motor.m1 == 1300U && motor.m2 == 1300U &&
          motor.m3 == 1300U && motor.m4 == 1300U,
          "restart must produce equal motor commands at zero error");
}

static void test_rate_p_still_opposes_motion_without_d_kicks(void)
{
    const float gyro_samples[] = {-20.0f, 20.0f};

    for (size_t i = 0U; i < sizeof gyro_samples / sizeof gyro_samples[0]; ++i) {
        RateController_t a, b;
        float roll_out, a_pitch, b_pitch, yaw_out;
        const float gyro = gyro_samples[i];
        RateController_Init(&a);
        RateController_Init(&b);
        /* Different histories, then the same measured angular velocity. */
        RateController_Update(&a, 0.0f, 0.0f, 0.0f, 0.0f, -gyro, 0.0f,
                              dt_s, &roll_out, &a_pitch, &yaw_out);
        RateController_Update(&b, 0.0f, 0.0f, 0.0f, 0.0f, gyro, 0.0f,
                              dt_s, &roll_out, &b_pitch, &yaw_out);
        RateController_Update(&a, 0.0f, 0.0f, 0.0f, 0.0f, gyro, 0.0f,
                              dt_s, &roll_out, &a_pitch, &yaw_out);
        RateController_Update(&b, 0.0f, 0.0f, 0.0f, 0.0f, gyro, 0.0f,
                              dt_s, &roll_out, &b_pitch, &yaw_out);
        CHECK(gyro * a_pitch < 0.0f && gyro * b_pitch < 0.0f,
              "zero rate target must still oppose measured pitch motion");
        CHECK(fabsf(a_pitch) > 1.0f && fabsf(b_pitch) > 1.0f,
              "rate damping must remain useful with default D disabled");
        CHECK(fabsf(a_pitch - b_pitch) < 0.1f,
              "default pitch rate output must not kick with different gyro derivatives");
    }
}

static void test_invalid_dt_resets_pid(void)
{
    const float invalid_dt[] = {0.0f, -0.002f, 0.0004f, 0.02f, NAN, INFINITY};

    for (size_t i = 0U; i < sizeof invalid_dt / sizeof invalid_dt[0]; ++i) {
        PID_t pid;
        PID_Init(&pid, 1.0f, 2.0f, 0.2f, 10.0f, 100.0f);
        (void)PID_Update(&pid, 0.0f, -3.0f, dt_s);
        (void)PID_Update(&pid, 0.0f, -4.0f, dt_s);
        CHECK(pid.integral > 0.0f && pid.derivative_filtered != 0.0f,
              "invalid dt test must first create I and D history");
        CHECK(near(PID_Update(&pid, 0.0f, 0.0f, invalid_dt[i]), 0.0f, 1.0e-6f),
              "invalid dt must produce zero output");
        check_reset(&pid);
        (void)PID_Update(&pid, 0.0f, 3.0f, dt_s);
        CHECK(near(pid.derivative_filtered, 0.0f, 1.0e-6f),
              "first valid sample after invalid dt must not inherit a D kick");
    }
}

static void test_explicit_d_has_no_startup_or_setpoint_kick(void)
{
    PID_t pid;
    PID_Init(&pid, 1.0f, 0.0f, 2.0f, 0.0f, 1000.0f);
    CHECK(near(PID_Update(&pid, 0.0f, 42.0f, dt_s), -42.0f, 1.0e-5f),
          "nonzero Kd must not cause a first-sample derivative kick");
    CHECK(near(PID_Update(&pid, 100.0f, 42.0f, dt_s), 58.0f, 1.0e-5f),
          "derivative on measurement must not kick on a setpoint step");
    CHECK(PID_Update(&pid, 100.0f, 43.0f, dt_s) < 57.0f,
          "explicit nonzero Kd must still respond to changing feedback");
    PID_Reset(&pid);
    CHECK(near(PID_Update(&pid, 0.0f, 43.0f, dt_s), -43.0f, 1.0e-5f),
          "reset must remove the previous derivative transient");
}

int main(void)
{
    test_stationary_pitch_correction();
    test_angle_has_no_residual_rate_request();
    test_rate_integral_is_effective_and_bounded();
    test_minimum_throttle_reset_removes_residuals();
    test_rate_p_still_opposes_motion_without_d_kicks();
    test_invalid_dt_resets_pid();
    test_explicit_d_has_no_startup_or_setpoint_kick();
    printf("PASS: 7 pitch control regression scenarios (%u checks).\n", checks);
    return EXIT_SUCCESS;
}
