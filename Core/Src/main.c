/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "e220.h"
#include "icm42670.h"
#include "gps.h"
#include "mmc5983ma.h"
#include "angle_controller.h"
#include "rate_controller.h"
#include "mixer.h"
#include "mahony.h"
#include "drone_link.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CONTROL_RATE_HZ 500U
#define CONTROL_MIN_DT_US 500U
#define CONTROL_MAX_DT_US 10000U
/* MMC: 25 Hz, chia làm hai pha không dùng HAL_Delay trong PID 500 Hz. */
#define MAG_PERIOD_MS           40U
#define MAG_CONVERSION_WAIT_MS   4U
#define MAG_MEAS_TIMEOUT_MS     25U
#define MAG_FRESH_TIMEOUT_MS   300U
#define MAG_FILTER_ALPHA       0.12f
#define MAG_MAX_JUMP_DEG       35.0f
/* Offset phần cứng MMC đã dùng trong chương trình đo heading trước đây (Gauss).
 * Cần hiệu chuẩn lại XYZ/hard-iron/soft-iron trên drone đã lắp hoàn chỉnh. */
#define MAG_OFFSET_X_G          0.20172f
#define MAG_OFFSET_Y_G          0.328185f
#define MAG_OFFSET_Z_G          0.0f
#define RAD_TO_DEG             57.295779513f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/* USER CODE BEGIN PV */
E220_t lora;

volatile uint32_t e220_uart_tx_drone = 0;

MMC5983MA_t mmc;
float mx, my, mz;
HAL_StatusTypeDef mmc_status;

ICM42670_t icm;
ICM42670_Data_t imu;

Mahony_t mahony;

AngleController_t angle_ctrl;
RateController_t rate_ctrl;

MotorMixer_t motor;

DroneLink_t drone_link;
float roll_deg, pitch_deg, yaw_deg;
float mahony_yaw_deg; /* Chỉ debug, yaw điều khiển lấy MMC + gyro */
float mag_heading_deg; /* Heading MMC theo atan2(+Y, +X), 0..360 */
float mag_yaw_deg; /* Heading MMC đã đổi dấu theo yaw gyro */
float yaw_target_deg; /* Chốt khi chuyển ga 1000 -> >1000 */
float roll_rate_sp, pitch_rate_sp, yaw_rate_sp;
static uint8_t yaw_estimate_valid;
static uint8_t yaw_target_latched;
static uint8_t mag_pending;
static uint32_t mag_next_tick, mag_start_tick, mag_last_good_tick;
static uint32_t mag_ok_count, mag_error_count, mag_rejected_count;

float roll_pid, pitch_pid, yaw_pid;

float throttle = 1000;

char uart_buf[128];

static char tx_frame[1024];

static float pitch_p_term, pitch_i_term, pitch_d_term;
static uint32_t control_dt_fault_count;

/** @brief Cực trị giữa hai lần log; giữ được xung nhiễu ngắn mà telemetry RF bỏ lỡ. */
static struct {
	uint32_t samples;
	uint32_t accel_samples;
	uint32_t gyro_samples;
	uint32_t accel_reduced;
	uint32_t max_dt_us;
	uint32_t limit_hits;
	float ax_sum, ay_sum, az_sum;
	float gyro_sum;
	float accel_norm_min, accel_norm_max;
	float gyro_min, gyro_max;
	float output_min, output_max;
	float d_abs_max;
} control_window;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM5_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/** @brief Xóa lịch sử cả hai vòng và các đầu ra, không đổi tư thế Mahony. */
static void Control_Reset(void) {
	PID_Reset(&angle_ctrl.roll);
	PID_Reset(&angle_ctrl.pitch);
	PID_Reset(&angle_ctrl.yaw);
	PID_Reset(&rate_ctrl.roll);
	PID_Reset(&rate_ctrl.pitch);
	PID_Reset(&rate_ctrl.yaw);
	roll_rate_sp = pitch_rate_sp = yaw_rate_sp = 0.0f;
	yaw_target_latched = 0U;
	roll_pid = pitch_pid = yaw_pid = 0.0f;
	pitch_p_term = pitch_i_term = pitch_d_term = 0.0f;
}

/** @brief Ghi bốn lệnh motor theo thứ tự M1..M4 đã xác nhận trên khung. */
static void Motors_Write(void) {
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, motor.m1);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, motor.m2);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, motor.m3);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, motor.m4);
}

/** @brief Lỗi IMU/nhịp điều khiển: về ga tối thiểu và bỏ lịch sử PID cũ. */
static void Control_Stop(void) {
	DroneLink_SetMinimumThrottle(&drone_link);
	throttle = (float) DRONE_LINK_MIN_THR;
	Control_Reset();
	motor.m1 = motor.m2 = motor.m3 = motor.m4 = DRONE_LINK_MIN_THR;
	Motors_Write();
}

/** @brief Ghi cực trị gyro, D và lệnh pitch thực sự được sử dụng trong cửa sổ log. */
static void Control_RecordSample(void) {
	if (control_window.samples == 0U) {
		control_window.gyro_min = control_window.gyro_max = imu.gy_dps;
		control_window.output_min = control_window.output_max = pitch_pid;
	}
	if (imu.gy_dps < control_window.gyro_min)
		control_window.gyro_min = imu.gy_dps;
	if (imu.gy_dps > control_window.gyro_max)
		control_window.gyro_max = imu.gy_dps;
	if (pitch_pid < control_window.output_min)
		control_window.output_min = pitch_pid;
	if (pitch_pid > control_window.output_max)
		control_window.output_max = pitch_pid;
	if (fabsf(pitch_d_term) > control_window.d_abs_max)
		control_window.d_abs_max = fabsf(pitch_d_term);
	if (isfinite(imu.ax_g) && isfinite(imu.ay_g) && isfinite(imu.az_g) &&
	isfinite(mahony.accel_norm_g)) {
		if (control_window.accel_samples == 0U)
			control_window.accel_norm_min = control_window.accel_norm_max =
					mahony.accel_norm_g;
		if (mahony.accel_norm_g < control_window.accel_norm_min)
			control_window.accel_norm_min = mahony.accel_norm_g;
		if (mahony.accel_norm_g > control_window.accel_norm_max)
			control_window.accel_norm_max = mahony.accel_norm_g;
		control_window.ax_sum += imu.ax_g;
		control_window.ay_sum += imu.ay_g;
		control_window.az_sum += imu.az_g;
		++control_window.accel_samples;
	}
	if (isfinite(imu.gy_dps)) {
		control_window.gyro_sum += imu.gy_dps;
		++control_window.gyro_samples;
	}
	if (!isfinite(mahony.accel_weight) || mahony.accel_weight < 1.0f)
		++control_window.accel_reduced;
	if (throttle > (float) DRONE_LINK_MIN_THR
			&& (motor.m1 == 1000U || motor.m1 == 1700U || motor.m2 == 1000U
					|| motor.m2 == 1700U || motor.m3 == 1000U
					|| motor.m3 == 1700U || motor.m4 == 1000U
					|| motor.m4 == 1700U))
		++control_window.limit_hits;
	++control_window.samples;
}

/* Chuẩn góc yaw 0..360 và sai số ngắn nhất -180..180 (độ). */
static float Yaw_Wrap360(float deg) {
	deg = fmodf(deg, 360.0f);
	return (deg < 0.0f) ? deg + 360.0f : deg;
}
static float Yaw_Wrap180(float deg) {
	return Yaw_Wrap360(deg + 180.0f) - 180.0f;
}

/* Gọi ở 500 Hz: gyro cung cấp biến thiên nhanh, MMC neo heading dài hạn. */
static void Yaw_IntegrateGyro(float gyro_z_dps, float dt) {
	if (yaw_estimate_valid && isfinite(gyro_z_dps) && isfinite(dt)) {
		yaw_deg = Yaw_Wrap360(yaw_deg + gyro_z_dps * dt);
	}
}

/* Đọc MMC ở tần số thấp, KHÔNG poll chờ/HAL_Delay bên trong.
 * Chỉ đúng công thức khi trục X/Y/Z MMC cùng chiều trục X/Y/Z IMU.
 * Nếu lắp xoay khác chiều, cần hoán đổi/đổi dấu trục trước khi bù nghiêng. */
static void Mag_Service(void) {
	uint32_t now = HAL_GetTick();
	if (!mag_pending) {
		if ((int32_t) (now - mag_next_tick) < 0)
			return;
		mmc_status = MMC5983_StartMeasurement(&mmc);
		if (mmc_status == HAL_OK) {
			mag_pending = 1U;
			mag_start_tick = now;
		} else {
			++mag_error_count;
			mag_next_tick = now + MAG_PERIOD_MS;
		}
		return;
	}
	if ((now - mag_start_tick) < MAG_CONVERSION_WAIT_MS)
		return;
	mmc_status = MMC5983_ReadMagIfReady(&mmc, &mx, &my, &mz);
	if (mmc_status == HAL_BUSY && (now - mag_start_tick) < MAG_MEAS_TIMEOUT_MS)
		return;
	mag_pending = 0U;
	mag_next_tick = now + MAG_PERIOD_MS;
	if (mmc_status != HAL_OK) {
		++mag_error_count;
		return;
	}

	float bx = mx - MAG_OFFSET_X_G;
	float by = my - MAG_OFFSET_Y_G;
	float bz = mz - MAG_OFFSET_Z_G;
	float norm2 = bx * bx + by * by + bz * bz;
	/* Đánh giá sơ bộ độ lớn từ trường: chưa thay thế hiệu chuẩn chính xác. */
	if (!isfinite(norm2) || norm2 < 0.01f || norm2 > 4.0f ||
	!isfinite(roll_deg) || !isfinite(pitch_deg)) {
		++mag_rejected_count;
		return;
	}

	float r = roll_deg / RAD_TO_DEG;
	float p = pitch_deg / RAD_TO_DEG;
	float sr = sinf(r), cr = cosf(r), sp = sinf(p), cp = cosf(p);
	/* Bù roll/pitch theo Euler ZYX. */
	float hx = bx * cp + by * sr * sp + bz * cr * sp;
	float hy = by * cr - bz * sr;
	if (!isfinite(hx) || !isfinite(hy) || hx * hx + hy * hy < 0.001f) {
		++mag_rejected_count;
		return;
	}
	mag_heading_deg = Yaw_Wrap360(atan2f(hy, hx) * RAD_TO_DEG);
	/* Khi quay thân +yaw (gyro Z dương), vector địa từ trên MMC quay -yaw.
	 Đổi dấu để yaw từ MMC CÙNG CHIỀU với yaw gyro/Mahony. */
	mag_yaw_deg = Yaw_Wrap360(-mag_heading_deg);
	if (!yaw_estimate_valid || (now - mag_last_good_tick) > 1000U) {
		/* Sau khởi động/mất MMC lâu: lấy lại mốc heading, không PID vào mốc cũ. */
		yaw_deg = mag_yaw_deg;
		yaw_estimate_valid = 1U;
		yaw_target_latched = 0U;
	} else {
		float delta = Yaw_Wrap180(mag_yaw_deg - yaw_deg);
		if (fabsf(delta) > MAG_MAX_JUMP_DEG) {
			++mag_rejected_count;
			return;
		}
		yaw_deg = Yaw_Wrap360(yaw_deg + MAG_FILTER_ALPHA * delta);
	}
	mag_last_good_tick = now;
	++mag_ok_count;
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2C1_Init();
	MX_I2C2_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_TIM5_Init();
	MX_USART1_UART_Init();
	MX_USART6_UART_Init();
	/* USER CODE BEGIN 2 */

	/* MMC được khởi tạo một lần. KHÔNG chạy vòng while in heading test. */
	HAL_Delay(20U);
	mmc.hi2c = &hi2c1;
	mmc_status = MMC5983_Init(&mmc);
	if (mmc_status != HAL_OK) {
		snprintf(uart_buf, sizeof(uart_buf),
				"MMC INIT FAILED I2C_ERR=0x%08lX\r\n",
				(unsigned long) HAL_I2C_GetError(&hi2c1));
		HAL_UART_Transmit(&huart1, (uint8_t*) uart_buf,
				(uint16_t) strlen(uart_buf), 100U);
		Error_Handler();
	}
	mag_next_tick = HAL_GetTick();

	if (ICM42670_Init(&icm) != ICM42670_OK) {
		sprintf(uart_buf, "ICM init err\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t*) uart_buf, strlen(uart_buf),
		HAL_MAX_DELAY);
		Error_Handler();
	}

	if (ICM42670_CalibrateGyro(&icm, 500, 2) != ICM42670_OK) {
		Error_Handler();
	}

	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);

	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 1000);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 1000);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 1000);

	HAL_Delay(4000);

	const uint16_t tilt_samples = 100U;
	float ax_sum = 0.0f;
	float ay_sum = 0.0f;
	float az_sum = 0.0f;

	for (uint16_t i = 0U; i < tilt_samples; ++i) {
		if (ICM42670_ReadAll(&imu) != ICM42670_OK) {
			Error_Handler();
		}
		ax_sum += imu.ax_g;
		ay_sum += imu.ay_g;
		az_sum += imu.az_g;
		HAL_Delay(2U);
	}
	if (!Mahony_InitFromAccel(&mahony, ax_sum / tilt_samples,
			ay_sum / tilt_samples, az_sum / tilt_samples)) {
		Error_Handler();
	}
	Mahony_GetEuler(&mahony, &roll_deg, &pitch_deg, &mahony_yaw_deg);
	AngleController_Init(&angle_ctrl);
	RateController_Init(&rate_ctrl);

	if (E220_Init(&lora, &huart6) != HAL_OK) {
		Error_Handler();
	}

	DroneLink_Init(&drone_link, &lora, &angle_ctrl, &rate_ctrl);
	motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;

	/* DWT có trên Cortex-M4: đo dt bằng chu kỳ CPU, không lượng tử hóa 1 ms.
	 * Phép trừ uint32_t vẫn đúng qua lần tràn CYCCNT. TIM5 chỉ xuất PWM ESC. */
	const uint32_t control_clock_hz = SystemCoreClock;
	const uint32_t control_period_cycles = control_clock_hz / CONTROL_RATE_HZ;
	const uint32_t control_cycles_per_us = control_clock_hz / 1000000U;
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0U;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	uint32_t last_control_cycles = DWT->CYCCNT;
	uint32_t last_sample_cycles = last_control_cycles;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		DroneLink_Poll(&drone_link);

		uint32_t now_cycles = DWT->CYCCNT;
		uint32_t elapsed_cycles = now_cycles - last_control_cycles;
		if (elapsed_cycles < control_period_cycles) {
			continue;
		}

		last_control_cycles = now_cycles;
		elapsed_cycles = now_cycles - last_sample_cycles;
		uint32_t dt_us = elapsed_cycles / control_cycles_per_us;
		if (dt_us > control_window.max_dt_us)
			control_window.max_dt_us = dt_us;
		if (elapsed_cycles > control_cycles_per_us * CONTROL_MAX_DT_US) {
			/* Không đưa khoảng gián đoạn dài vào cả Mahony lẫn PID. */
			++control_dt_fault_count;
			last_sample_cycles = now_cycles;
			Control_Stop();
			continue;
		}

		/* ================= IMU ================= */

		if (ICM42670_ReadAll(&imu) != ICM42670_OK) {
			Control_Stop();
			last_control_cycles = last_sample_cycles = DWT->CYCCNT;
			(void) DroneLink_SendStatus(&drone_link, roll_deg, pitch_deg,
					yaw_deg, motor.m1, motor.m2, motor.m3, motor.m4);
			continue;
		}

		/* dt là khoảng cách giữa các mẫu đã đọc xong, kể cả trễ SPI thực tế. */
		uint32_t sample_cycles = DWT->CYCCNT;
		elapsed_cycles = sample_cycles - last_sample_cycles;
		last_sample_cycles = sample_cycles;
		dt_us = elapsed_cycles / control_cycles_per_us;
		if (dt_us > control_window.max_dt_us)
			control_window.max_dt_us = dt_us;
		if (elapsed_cycles < control_cycles_per_us * CONTROL_MIN_DT_US
				|| elapsed_cycles > control_cycles_per_us * CONTROL_MAX_DT_US) {
			++control_dt_fault_count;
			last_control_cycles = sample_cycles;
			Control_Stop();
			continue;
		}
		float dt = (float) elapsed_cycles / (float) control_clock_hz;

		ICM42670_ApplyCalibration(&icm, &imu);

		/* ================= MAHONY ================= */

		Mahony_Update(&mahony, imu.gx_dps, imu.gy_dps, imu.gz_dps, imu.ax_g,
				imu.ay_g, imu.az_g, dt);

		Mahony_GetEuler(&mahony, &roll_deg, &pitch_deg, &mahony_yaw_deg);
		Yaw_IntegrateGyro(imu.gz_dps, dt);

		/*
		 * Nếu IMU gắn khác chiều
		 * thì đổi dấu tại đây
		 */

		// roll_deg  = -roll_deg;
		// pitch_deg = -pitch_deg;
		throttle = (float) DroneLink_Throttle(&drone_link);
		if (throttle > 1000.0f) {
			/* Mặc định: góc P -> tốc độ PI. Giữ nguyên dấu IMU và mixer. */
			AngleController_Update(&angle_ctrl, 0.0f, 0.0f, roll_deg, pitch_deg,
					dt, &roll_rate_sp, &pitch_rate_sp);
			/* Yaw setpoint là hướng MMC ở thời điểm BẮT ĐẦU lên ga.
			 * Không cập nhật setpoint theo góc hiện tại khi đang bay. */
			uint32_t mag_age = HAL_GetTick() - mag_last_good_tick;
			uint8_t mag_fresh = yaw_estimate_valid
					&& (mag_age <= MAG_FRESH_TIMEOUT_MS);
			if (mag_fresh && !yaw_target_latched) {
				yaw_target_deg = yaw_deg;
				yaw_target_latched = 1U;
				PID_Reset(&angle_ctrl.yaw);
				PID_Reset(&rate_ctrl.yaw);
			}
			if (mag_fresh && yaw_target_latched) {
				yaw_rate_sp = AngleController_UpdateYaw(&angle_ctrl,
						yaw_target_deg, yaw_deg, dt);
			} else {
				/* MMC lỗi/stale: bỏ yaw holding, không tác động dựa trên hướng cũ. */
				yaw_rate_sp = 0.0f;
				yaw_target_latched = 0U;
				PID_Reset(&angle_ctrl.yaw);
				PID_Reset(&rate_ctrl.yaw);
			}
			RateController_Update(&rate_ctrl, roll_rate_sp, pitch_rate_sp,
					yaw_rate_sp, imu.gx_dps, imu.gy_dps, imu.gz_dps, dt,
					&roll_pid, &pitch_pid, &yaw_pid);
			if (!mag_fresh)
				yaw_pid = 0.0f;

			pitch_p_term =
					rate_ctrl.pitch.initialized ?
							rate_ctrl.pitch.kp * rate_ctrl.pitch.prev_error :
							0.0f;
			pitch_i_term = rate_ctrl.pitch.integral;
			pitch_d_term = -rate_ctrl.pitch.kd
					* rate_ctrl.pitch.derivative_filtered;
			Mixer_QuadX(throttle, roll_pid, pitch_pid, yaw_pid, &motor);
		} else {
			motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;
			Control_Reset();
		}

		Motors_Write();
		Control_RecordSample();
		/* Xử lý MMC sau PWM; cập nhật yaw fused cho chu kỳ điều khiển kế. */
		Mag_Service();

		(void) DroneLink_SendStatus(&drone_link, roll_deg, pitch_deg, yaw_deg,
				motor.m1, motor.m2, motor.m3, motor.m4);

		static uint32_t last_log_tick = 0U; /**< Mốc gửi log gần nhất, đơn vị ms; giữ giá trị giữa các vòng lặp. */

		uint32_t log_now = HAL_GetTick();
		if ((log_now - last_log_tick >= 500U)
				&& (huart1.gState == HAL_UART_STATE_READY)) {
			float mean_ax = NAN, mean_ay = NAN, mean_az = NAN;
			float pitch_acc = NAN;
			float accel_norm_min = NAN, accel_norm_max = NAN;
			float mean_gy = NAN;
			if (control_window.accel_samples > 0U) {
				float inv_samples = 1.0f / (float) control_window.accel_samples;
				mean_ax = control_window.ax_sum * inv_samples;
				mean_ay = control_window.ay_sum * inv_samples;
				mean_az = control_window.az_sum * inv_samples;
				accel_norm_min = control_window.accel_norm_min;
				accel_norm_max = control_window.accel_norm_max;
				if (mean_ax * mean_ax + mean_ay * mean_ay + mean_az * mean_az
						> 1.0e-12f)
					pitch_acc = atan2f(-mean_ax,
							sqrtf(mean_ay * mean_ay + mean_az * mean_az))
							* 57.2957795f;
			}
			if (control_window.gyro_samples > 0U)
				mean_gy = control_window.gyro_sum
						/ (float) control_window.gyro_samples;

			/** @brief Số ký tự snprintf cần ghi, không tính NUL; chỉ gửi khi bộ đệm đủ chỗ. */
			int len =
					snprintf(tx_frame, sizeof(tx_frame),
							"thr=%u angle=%.1f,%.1f,%.1f pid=%.1f,%.1f m=%u,%u,%u,%u\r\n"
									"CTRL dt_us=%lu max_us=%lu dt_bad=%lu n=%lu lim=%lu"
									" gy=%.1f sp=%.1f P=%.1f I=%.1f D=%.1f"
									" gy_rng=%.1f,%.1f out_rng=%.1f,%.1f Dmax=%.1f"
									" angle_k=%.2f,%.2f,%.3f rate_k=%.2f,%.2f,%.3f\r\n"
									"IMU a_g=%.3f,%.3f,%.3f norm_g=%.3f,%.3f pitch_acc=%.1f"
									" gy_avg=%.3f aw=%.2f reduced=%lu an=%lu fbY=%.5f\r\n"
									"LORA T_RX=%lu P_WR=%lu P_RD=%lu TIMEOUT=%lu BAD=%lu"
									" RX_BYTE=%lu S_REQ=%lu TX_DMA_START=%lu TX_DMA_DONE=%lu"
									" TX_BUSY=%lu TX_ERR=%lu UART_ERR=%lu\r\n"
									"YAW fused=%.1f mag=%.1f raw_heading=%.1f target=%.1f"
									" e=%.1f rate_sp=%.1f gz=%.1f out=%.1f"
									" mag_age=%lu ok=%lu err=%lu reject=%lu hold=%u\r\n",
							(unsigned) DroneLink_Throttle(&drone_link),
							roll_deg, pitch_deg, yaw_deg, roll_pid, pitch_pid,
							(unsigned) motor.m1, (unsigned) motor.m2,
							(unsigned) motor.m3, (unsigned) motor.m4,
							(unsigned long) dt_us,
							(unsigned long) control_window.max_dt_us,
							(unsigned long) control_dt_fault_count,
							(unsigned long) control_window.samples,
							(unsigned long) control_window.limit_hits,
							imu.gy_dps, pitch_rate_sp, pitch_p_term,
							pitch_i_term, pitch_d_term, control_window.gyro_min,
							control_window.gyro_max, control_window.output_min,
							control_window.output_max, control_window.d_abs_max,
							angle_ctrl.pitch.kp, angle_ctrl.pitch.ki,
							angle_ctrl.pitch.kd, rate_ctrl.pitch.kp,
							rate_ctrl.pitch.ki, rate_ctrl.pitch.kd, mean_ax,
							mean_ay, mean_az, accel_norm_min, accel_norm_max,
							pitch_acc, mean_gy, mahony.accel_weight,
							(unsigned long) control_window.accel_reduced,
							(unsigned long) control_window.accel_samples,
							mahony.integralFBy,
							(unsigned long) drone_link.throttle_rx_count,
							(unsigned long) drone_link.pid_write_count,
							(unsigned long) drone_link.pid_read_count,
							(unsigned long) drone_link.throttle_timeout_count,
							(unsigned long) drone_link.rx_invalid_frames,
							(unsigned long) drone_link.rx_byte_count,
							(unsigned long) drone_link.status_request_count,
							(unsigned long) lora.tx_start_count,
							(unsigned long) lora.tx_done_count,
							(unsigned long) lora.tx_busy_count,
							(unsigned long) lora.tx_error_count,
							(unsigned long) lora.uart_error_count, yaw_deg,
							mag_yaw_deg, mag_heading_deg, yaw_target_deg,
							Yaw_Wrap180(yaw_target_deg - yaw_deg), yaw_rate_sp,
							imu.gz_dps, yaw_pid,
							(unsigned long) (HAL_GetTick() - mag_last_good_tick),
							(unsigned long) mag_ok_count,
							(unsigned long) mag_error_count,
							(unsigned long) mag_rejected_count,
							(unsigned) yaw_target_latched);

			if ((len > 0) && ((size_t) len < sizeof(tx_frame))) {
				if (HAL_UART_Transmit_IT(&huart1, (uint8_t*) tx_frame,
						(uint16_t) len) == HAL_OK) {
					last_log_tick = log_now;
					memset(&control_window, 0, sizeof(control_window));
				}
			}
		}

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	/* HSI 16 MHz / 8 = 2 MHz PLL input. */
	RCC_OscInitStruct.PLL.PLLM = 8;
	/* PLL VCO = 2*84 = 168 MHz. */
	RCC_OscInitStruct.PLL.PLLN = 84;
	/* CPU SYSCLK = 168/2 = 84 MHz. */
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	/* APB1 42 MHz, TIM5 nhận clock 84 MHz vì timer x2. */
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	/* I2C1 Standard-mode 100kHz. */
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void) {

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	/* I2C2 Standard-mode 100kHz. */
	hi2c2.Init.ClockSpeed = 100000;
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C2_Init 2 */

	/* USER CODE END I2C2_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	/* SPI1 clock = 84/16 = 5,25 MHz. */
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	/* SPI2 clock = 42/16 = 2,625 MHz. */
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}

/**
 * @brief TIM5 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM5_Init(void) {

	/* USER CODE BEGIN TIM5_Init 0 */

	/* USER CODE END TIM5_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_OC_InitTypeDef sConfigOC = { 0 };

	/* USER CODE BEGIN TIM5_Init 1 */

	/* USER CODE END TIM5_Init 1 */
	htim5.Instance = TIM5;
	/* TIM5 PSC=83: 84MHz/(83+1) = 1MHz => 1 tick = 1µs. */
	htim5.Init.Prescaler = 83;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	/* TIM5 ARR=4999: 5000 ticks/chu kỳ => PWM 200Hz. */
	htim5.Init.Period = 4999;
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim5) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* PWM mode 1: CCR là số tick mức cao (µs). */
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM5_Init 2 */

	/* USER CODE END TIM5_Init 2 */
	HAL_TIM_MspPostInit(&htim5);

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	/* USART1 log 38400 baud, 8N1. */
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART6_UART_Init(void) {

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	/* USART6 LoRa E220 9600 baud, 8N1. */
	huart6.Init.BaudRate = 9600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* USER CODE END USART6_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	/* DMA2_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA4 */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PB12 */
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART6) {
		E220_RxCallback(&lora);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART6) {
		E220_TxCpltCallback(&lora);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART6) {
		E220_ErrorCallback(&lora);
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
