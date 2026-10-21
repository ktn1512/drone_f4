#include "angle_controller.h"
#include <math.h>

void AngleController_Init(AngleController_t *angle)
{
	PID_Init(&angle->roll,
			 7.2f, 0.0f, 0.0f,
			 10.0f, 200.0f);

	PID_Init(&angle->pitch,
			 7.2f, 0.2f, 0.001f,
			 10.0f, 200.0f);

	PID_Init(&angle->yaw,
			 4.0f, 0.0f, 0.0f,
			 0.0f, 80.0f);
}

void AngleController_Update(AngleController_t *angle,

							float roll_sp_deg, float pitch_sp_deg,

							float roll_deg, float pitch_deg,

							float dt,

							float *roll_rate_sp, float *pitch_rate_sp)
{
	*roll_rate_sp = PID_Update(&angle->roll, roll_sp_deg, roll_deg, dt);

	*pitch_rate_sp = PID_Update(&angle->pitch, pitch_sp_deg, pitch_deg, dt);
}

float AngleController_UpdateYaw(AngleController_t *angle,
                               float yaw_setpoint_deg, float yaw_deg, float dt)
{
    if (!isfinite(yaw_setpoint_deg) || !isfinite(yaw_deg)) {
        PID_Reset(&angle->yaw);
        return 0.0f;
    }
    float error = fmodf(yaw_setpoint_deg - yaw_deg + 180.0f, 360.0f);
    if (error < 0.0f) error += 360.0f;
    error -= 180.0f;

    return PID_Update(&angle->yaw, 0.0f, -error, dt);
}
