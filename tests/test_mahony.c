#include "mahony.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const float degrees_to_radians = 0.01745329251994329577f;
static const float integral_limit = 0.08726646f;
static unsigned int checks;

#define CHECK(condition) do { \
    ++checks; \
    if (!(condition)) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

static void close_to(float actual, float expected, float tolerance)
{
    CHECK(isfinite(actual));
    if (fabsf(actual - expected) > tolerance) {
        fprintf(stderr, "actual %.9g, expected %.9g +/- %.9g\n",
                (double)actual, (double)expected, (double)tolerance);
        CHECK(fabsf(actual - expected) <= tolerance);
    }
    ++checks;
}

/* Stationary gravity in body axes, for yaw = 0 and +Z = +1 g at level. */
static void gravity(float roll, float pitch, float *ax, float *ay, float *az)
{
    const float r = roll * degrees_to_radians;
    const float p = pitch * degrees_to_radians;
    *ax = -sinf(p);
    *ay = sinf(r) * cosf(p);
    *az = cosf(r) * cosf(p);
}

static void valid_orientation(Mahony_t *m)
{
    float roll, pitch, yaw;
    close_to(m->q0 * m->q0 + m->q1 * m->q1 +
             m->q2 * m->q2 + m->q3 * m->q3, 1.0f, 2.0e-6f);
    Mahony_GetEuler(m, &roll, &pitch, &yaw);
    CHECK(isfinite(roll));
    CHECK(isfinite(pitch));
    CHECK(isfinite(yaw));
}

static void same_orientation(const Mahony_t *m, const Mahony_t *previous)
{
    close_to(m->q0, previous->q0, 0.0f);
    close_to(m->q1, previous->q1, 0.0f);
    close_to(m->q2, previous->q2, 0.0f);
    close_to(m->q3, previous->q3, 0.0f);
}

static float pitch_of(Mahony_t *m)
{
    float roll, pitch, yaw;
    Mahony_GetEuler(m, &roll, &pitch, &yaw);
    return pitch;
}

static void test_static_tilt(void)
{
    static const float tilts[][2] = {
        { 0.0f, 0.0f }, { 0.0f, -11.0f }, { 0.0f, 30.0f },
        { 25.0f, 0.0f }, { -20.0f, 0.0f }, { 23.0f, -37.0f },
        { -31.0f, 42.0f }, { 0.0f, 75.0f }
    };
    for (size_t i = 0; i < sizeof tilts / sizeof tilts[0]; ++i) {
        Mahony_t m;
        float ax, ay, az, roll, pitch, yaw;
        gravity(tilts[i][0], tilts[i][1], &ax, &ay, &az);
        CHECK(Mahony_InitFromAccel(&m, ax, ay, az) == 1);
        CHECK(isfinite(m.twoKp) && m.twoKp > 0.0f);
        close_to(m.twoKi, 0.0f, 0.0f);
        Mahony_GetEuler(&m, &roll, &pitch, &yaw);
        close_to(roll, tilts[i][0], 2.0e-4f);
        close_to(pitch, tilts[i][1], 2.0e-4f);
        close_to(yaw, 0.0f, 2.0e-4f);

        /* Stationary updates preserve true tilt rather than setting it to zero. */
        for (int step = 0; step < 1000; ++step) {
            Mahony_Update(&m, 0.0f, 0.0f, 0.0f, ax, ay, az, 0.002f);
        }
        Mahony_GetEuler(&m, &roll, &pitch, &yaw);
        close_to(roll, tilts[i][0], 3.0e-4f);
        close_to(pitch, tilts[i][1], 3.0e-4f);
        valid_orientation(&m);

        /* A wrong level estimate must converge to measured physical tilt. */
        Mahony_Init(&m);
        for (int step = 0; step < 12500; ++step) {
            Mahony_Update(&m, 0.0f, 0.0f, 0.0f, ax, ay, az, 0.002f);
        }
        Mahony_GetEuler(&m, &roll, &pitch, &yaw);
        close_to(roll, tilts[i][0], 0.02f);
        close_to(pitch, tilts[i][1], 0.02f);
        valid_orientation(&m);
    }
}

static void test_gyro_propagation(void)
{
    static const float cases[][9] = {
        /* gx, gy, gz, ax, ay, az, expected roll, pitch, yaw after 2 s. */
        { -15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 0.0f, 0.0f },
        { 0.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 0.0f },
        { 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f },
        { 0.0f, -20.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f },
        { 0.0f, 25.0f, 0.0f, FLT_MAX, FLT_MAX, FLT_MAX, 0.0f, 50.0f, 0.0f },
        { 0.0f, 25.0f, 0.0f, NAN, 0.0f, 1.0f, 0.0f, 50.0f, 0.0f },
        { 0.0f, 25.0f, 0.0f, 0.0f, INFINITY, 1.0f, 0.0f, 50.0f, 0.0f },
        { 0.0f, 25.0f, 0.0f, 1.0e-9f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f }
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        Mahony_t m;
        float roll, pitch, yaw;
        Mahony_Init(&m);
        for (int step = 0; step < 1000; ++step) {
            Mahony_Update(&m, cases[i][0], cases[i][1], cases[i][2],
                          cases[i][3], cases[i][4], cases[i][5], 0.002f);
        }
        Mahony_GetEuler(&m, &roll, &pitch, &yaw);
        close_to(roll, cases[i][6], 0.01f);
        close_to(pitch, cases[i][7], 0.01f);
        close_to(yaw, cases[i][8], 0.01f);
        close_to(m.accel_weight, 0.0f, 0.0f);
        close_to(m.accel_norm_g, i == 3 ? 2.0f : 0.0f, 1.0e-6f);
        valid_orientation(&m);
    }
}

static void test_acceleration_confidence_and_recovery(void)
{
    static const float norms[] = { 0.75f, 0.85f, 0.95f, 1.0f, 1.05f, 1.15f, 1.25f };
    static const float weights[] = { 0.0f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f };
    float ax, ay, az, full_pitch = 0.0f;
    gravity(0.0f, 30.0f, &ax, &ay, &az);
    for (size_t i = 0; i < sizeof norms / sizeof norms[0]; ++i) {
        Mahony_t m;
        Mahony_Init(&m);
        /* Explicit local gain makes transient expectations independent of tuning. */
        m.twoKp = 2.0f;
        Mahony_Update(&m, 0.0f, 0.0f, 0.0f,
                      ax * norms[i], ay * norms[i], az * norms[i], 0.01f);
        close_to(m.accel_norm_g, norms[i], 1.0e-6f);
        close_to(m.accel_weight, weights[i], 2.0e-6f);
        if (weights[i] == 0.0f) {
            close_to(pitch_of(&m), 0.0f, 1.0e-6f);
        } else if (weights[i] == 1.0f) {
            CHECK(pitch_of(&m) > 0.28f);
            full_pitch = pitch_of(&m);
        } else {
            CHECK(pitch_of(&m) > 0.14f);
            CHECK(pitch_of(&m) < 0.15f);
        }
        valid_orientation(&m);
    }
    CHECK(full_pitch > 0.28f);

    Mahony_t m;
    gravity(0.0f, -11.0f, &ax, &ay, &az);
    CHECK(Mahony_InitFromAccel(&m, ax, ay, az) == 1);
    m.twoKp = 2.0f;
    for (int step = 0; step < 2500; ++step) {
        /* Wrong-direction 2 g samples must not pull a held frame toward level. */
        Mahony_Update(&m, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.7320508f, 0.002f);
    }
    close_to(pitch_of(&m), -11.0f, 0.001f);
    /* A short partially trusted disturbance may move the estimate. */
    for (int step = 0; step < 250; ++step) {
        Mahony_Update(&m, 0.0f, 0.0f, 0.0f, -0.575f, 0.0f, 0.9959292f, 0.002f);
    }
    CHECK(pitch_of(&m) > -5.0f);
    for (int step = 0; step < 6000; ++step) {
        Mahony_Update(&m, 0.0f, 0.0f, 0.0f, ax, ay, az, 0.002f);
    }
    close_to(pitch_of(&m), -11.0f, 0.01f);
    valid_orientation(&m);
}

static void test_disabled_integral(void)
{
    static const float ki_values[] = { 0.0f, -0.1f };
    static const float acceleration[][3] = {
        { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f },
        { 2.0f, 0.0f, 0.0f }, { NAN, 0.0f, 1.0f }
    };
    for (size_t ki = 0; ki < sizeof ki_values / sizeof ki_values[0]; ++ki) {
        for (size_t i = 0; i < sizeof acceleration / sizeof acceleration[0]; ++i) {
            Mahony_t m;
            Mahony_Init(&m);
            m.twoKi = ki_values[ki];
            m.integralFBx = 0.05f;
            m.integralFBy = -0.04f;
            m.integralFBz = 0.03f;
            Mahony_Update(&m, 0.0f, 0.0f, 0.0f,
                          acceleration[i][0], acceleration[i][1], acceleration[i][2], 0.01f);
            close_to(m.integralFBx, 0.0f, 0.0f);
            close_to(m.integralFBy, 0.0f, 0.0f);
            close_to(m.integralFBz, 0.0f, 0.0f);
            close_to(m.q0, 1.0f, 0.0f);
            close_to(m.q1, 0.0f, 0.0f);
            close_to(m.q2, 0.0f, 0.0f);
            close_to(m.q3, 0.0f, 0.0f);
        }
    }
}

static void test_enabled_integral(void)
{
    /* Brief large errors exercise both signs and all three bounded learners. */
    for (int axis = 0; axis < 3; ++axis) {
        for (int sign = -1; sign <= 1; sign += 2) {
            Mahony_t m;
            float ax = 0.0f, ay = 0.0f, az = 0.0f;
            if (axis == 2) {
                CHECK(Mahony_InitFromAccel(&m, 0.0f, 1.0f, 0.0f) == 1);
                ax = (float)sign;
            } else {
                Mahony_Init(&m);
                if (axis == 0) ay = (float)sign;
                else ax = -(float)sign;
            }
            m.twoKi = 100.0f;
            m.twoKp = 0.0f;
            Mahony_Update(&m, 0.0f, 0.0f, 0.0f, ax, ay, az, 0.01f);
            const float learned = axis == 0 ? m.integralFBx :
                                  axis == 1 ? m.integralFBy : m.integralFBz;
            close_to(learned, (float)sign * integral_limit, 1.0e-7f);
            CHECK(fabsf(m.integralFBx) <= integral_limit);
            CHECK(fabsf(m.integralFBy) <= integral_limit);
            CHECK(fabsf(m.integralFBz) <= integral_limit);
            valid_orientation(&m);
        }
    }

    Mahony_t full, partial;
    Mahony_Init(&full);
    Mahony_Init(&partial);
    full.twoKi = partial.twoKi = 4.0f;
    full.twoKp = partial.twoKp = 0.0f;
    Mahony_Update(&full, 0.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.8660254f, 0.01f);
    Mahony_Update(&partial, 0.0f, 0.0f, 0.0f, -0.575f, 0.0f, 0.9959292f, 0.01f);
    close_to(partial.integralFBy / full.integralFBy, 0.5f, 2.0e-5f);

    /* Once learned, bias continues correcting gyro through missing/rejected accel. */
    Mahony_t m;
    Mahony_Init(&m);
    m.twoKp = 0.0f;
    m.twoKi = 100.0f;
    Mahony_Update(&m, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.01f);
    const float start_pitch = pitch_of(&m);
    const float learned = m.integralFBy;
    for (int step = 0; step < 1000; ++step) {
        const float ax_missing = step < 333 ? 0.0f : step < 666 ? 2.0f : NAN;
        Mahony_Update(&m, 0.0f, 0.0f, 0.0f, ax_missing, 0.0f, 0.0f, 0.001f);
        close_to(m.integralFBy, learned, 0.0f);
        close_to(m.accel_weight, 0.0f, 0.0f);
    }
    close_to(pitch_of(&m) - start_pitch, 5.0f, 0.01f);
    valid_orientation(&m);
}

static void test_invalid_input(void)
{
    static const float invalid_dt[] = { 0.0f, -0.001f, NAN, INFINITY, -INFINITY };
    Mahony_t m;
    CHECK(Mahony_InitFromAccel(&m, 0.2f, -0.3f, 0.9327379f) == 1);
    for (size_t i = 0; i < sizeof invalid_dt / sizeof invalid_dt[0]; ++i) {
        const Mahony_t previous = m;
        Mahony_Update(&m, 20.0f, 30.0f, 40.0f, 0.0f, 0.0f, 1.0f, invalid_dt[i]);
        same_orientation(&m, &previous);
        valid_orientation(&m);
    }
    for (int axis = 0; axis < 3; ++axis) {
        for (int infinite = 0; infinite < 2; ++infinite) {
            float gyro[3] = { 20.0f, 30.0f, 40.0f };
            const Mahony_t previous = m;
            gyro[axis] = infinite ? INFINITY : NAN;
            Mahony_Update(&m, gyro[0], gyro[1], gyro[2], 0.0f, 0.0f, 1.0f, 0.002f);
            same_orientation(&m, &previous);
            valid_orientation(&m);
        }
    }
    static const float invalid_acceleration[][3] = {
        { 0.0f, 0.0f, 0.0f }, { 1.0e-9f, 0.0f, 0.0f },
        { NAN, 0.0f, 1.0f }, { 0.0f, INFINITY, 1.0f },
        { FLT_MAX, FLT_MAX, FLT_MAX }
    };
    for (size_t i = 0; i < sizeof invalid_acceleration / sizeof invalid_acceleration[0]; ++i) {
        const Mahony_t previous = m;
        CHECK(Mahony_InitFromAccel(&m, invalid_acceleration[i][0],
                                  invalid_acceleration[i][1], invalid_acceleration[i][2]) == 0);
        same_orientation(&m, &previous);
    }
    /* A valid update after rejected input still propagates a real rotation. */
    const float start_pitch = pitch_of(&m);
    Mahony_Update(&m, 0.0f, 10.0f, 0.0f, NAN, 0.0f, 1.0f, 0.01f);
    CHECK(pitch_of(&m) > start_pitch + 0.09f);
    valid_orientation(&m);
}

int main(void)
{
    test_static_tilt();
    test_gyro_propagation();
    test_acceleration_confidence_and_recovery();
    test_disabled_integral();
    test_enabled_integral();
    test_invalid_input();
    printf("Mahony regression passed (%u checks).\n", checks);
    return EXIT_SUCCESS;
}
