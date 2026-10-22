/* Mixer Quad X: trộn throttle và Roll/Pitch/Yaw PID thành xung ESC µs. */
#include "mixer.h"
#include <math.h>

#define MOTOR_MIN_US 1000.0f // Giới hạn dưới xung ESC 1000 µs.

#define MOTOR_MAX_US 1700.0f // Giới hạn trên xung ESC 1700 µs.

static uint16_t LimitMotor(float value)
{
	if (!isfinite(value))
		return 1000U;

	if (value < MOTOR_MIN_US)
		value = MOTOR_MIN_US;

	if (value > MOTOR_MAX_US)
		value = MOTOR_MAX_US;

	return (uint16_t)(value + 0.5f);
}

void Mixer_QuadX(float throttle,
				 float roll_pid,
				 float pitch_pid,
				 float yaw_pid,
				 MotorMixer_t *motor)
{
	if (motor == NULL)
		return;

	float m1 = throttle - roll_pid - pitch_pid + yaw_pid;

	float m2 = throttle + roll_pid - pitch_pid - yaw_pid;

	float m3 = throttle - roll_pid + pitch_pid - yaw_pid;

	float m4 = throttle + roll_pid + pitch_pid + yaw_pid;

	motor->m1 = LimitMotor(m1);
	motor->m2 = LimitMotor(m2);
	motor->m3 = LimitMotor(m3);
	motor->m4 = LimitMotor(m4);
}
