/**
 * @file angle_controller.c
 * @brief Cài đặt vòng điều khiển góc roll/pitch/yaw bằng ba PID.
 */
/*
 * angle_controller.c
 *
 *  Created on: 6 thg 9, 2026
 *      Author: khanh
 */

#include "angle_controller.h"
#include <math.h>

/**
 * @brief Khởi tạo vòng góc mặc định chỉ dùng P; vòng rate đảm nhiệm I bù mômen.
 * @note Giữ giới hạn I để vẫn có thể chủ động bật lại Ki qua dashboard.
 */
void AngleController_Init(AngleController_t *angle)
{
	PID_Init(&angle->roll,
			 7.2f, 0.0f, 0.0f,
			 10.0f, 200.0f);

	PID_Init(&angle->pitch,
			 5.2f, 0.3f, 0.001f,
			 10.0f, 180.0f);

	/* Vòng hướng yaw: P nhẹ, không tích phân, giới hạn tốc độ đặt 80 deg/s. */
	PID_Init(&angle->yaw,
			 4.0f, 0.0f, 0.0f,
			 0.0f, 80.0f);
}	

/**
 * @brief Cập nhật hai PID góc và ghi tốc độ góc đặt vào các đầu ra.
 */
void AngleController_Update(AngleController_t *angle,

							float roll_sp_deg, float pitch_sp_deg,

							float roll_deg, float pitch_deg,

							float dt,

							float *roll_rate_sp, float *pitch_rate_sp)
{
	*roll_rate_sp = PID_Update(&angle->roll, roll_sp_deg, roll_deg, dt);

	*pitch_rate_sp = PID_Update(&angle->pitch, pitch_sp_deg, pitch_deg, dt);
}

/** @brief Sai số yaw vòng tròn. Tránh sai số 358 độ khi hướng đi qua Bắc. */
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
    /* Dùng setpoint giả bằng 0, measurement=-error để giữ quy tắc PID_Update. */
    return PID_Update(&angle->yaw, 0.0f, -error, dt);
}
