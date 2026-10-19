/**
 * @file angle_controller.h
 * @brief Giao diện PID góc roll/pitch/yaw tạo tốc độ góc đặt.
 */
/*
 * angle_controller.h
 *
 *  Created on: 6 thg 9, 2026
 *      Author: khanh
 */

#ifndef INC_ANGLE_CONTROLLER_H_
#define INC_ANGLE_CONTROLLER_H_

#include "pid.h"

/**
 * @brief Trạng thái ba vòng PID góc roll/pitch/yaw sinh tốc độ góc đặt.
 */
typedef struct {
	/**
	 * @brief PID góc roll: đầu vào độ, đầu ra tốc độ góc đặt độ/s.
	 */
	PID_t roll;
	/**
	 * @brief PID góc pitch: đầu vào độ, đầu ra tốc độ góc đặt độ/s.
	 */
	PID_t pitch;
	/** @brief PID góc yaw: sai số góc ngắn nhất (độ), đầu ra tốc độ yaw đặt (độ/s). */
	PID_t yaw;

} AngleController_t;

/**
 * @brief Khởi tạo ba PID góc, bao gồm yaw giữ hướng dựa trên MMC.
 * @param[out] angle Bộ điều khiển góc được khởi tạo; con trỏ phải hợp lệ.
 * @note Mặc định Ki/Kd bằng 0, chỉ P sinh tốc độ đặt. Giới hạn I dự phòng
 *       là 10 độ/s cho roll/pitch, giới hạn tốc độ yaw 80 độ/s.
 *       Không kiểm tra NULL.
 */
void AngleController_Init(AngleController_t *angle);

/**
 * @brief Chuyển sai số góc roll/pitch thành tốc độ góc đặt cho vòng rate.
 * @param[in,out] angle Bộ điều khiển góc đã khởi tạo; con trỏ phải hợp lệ.
 * @param[in] roll_sp_deg Góc roll đặt, độ.
 * @param[in] pitch_sp_deg Góc pitch đặt, độ.
 * @param[in] roll_deg Góc roll đo, độ.
 * @param[in] pitch_deg Góc pitch đo, độ.
 * @param[in] dt Khoảng thời gian cập nhật, giây; PID chấp nhận 0,0005 đến 0,01 s.
 * @param[out] roll_rate_sp Nơi nhận tốc độ góc roll đặt, độ/s; con trỏ phải hợp lệ.
 * @param[out] pitch_rate_sp Nơi nhận tốc độ góc pitch đặt, độ/s; con trỏ phải hợp lệ.
 * @note Mỗi trục áp dụng chính sách dữ liệu/dt không hợp lệ của PID_Update;
 *       hàm không tự kiểm tra NULL.
 */
void AngleController_Update(AngleController_t *angle,

float roll_sp_deg, float pitch_sp_deg,

float roll_deg, float pitch_deg,

float dt,

float *roll_rate_sp, float *pitch_rate_sp);

/**
 * @brief PID giữ hướng yaw với sai số góc ngắn nhất trong [-180, 180] độ.
 * @param yaw_setpoint_deg Hướng đặt theo MMC, độ; được phép 0..360.
 * @param yaw_deg Hướng đo đã hợp nhất gyro + MMC, độ; được phép 0..360.
 * @return Tốc độ yaw đặt (độ/s) cho RateController_Update.
 * @note Kd yaw mặc định = 0. Dùng góc vòng tròn, không PID trực tiếp trên số 359/0.
 */
float AngleController_UpdateYaw(AngleController_t *angle,
                               float yaw_setpoint_deg, float yaw_deg, float dt);

#endif /* INC_ANGLE_CONTROLLER_H_ */
