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
#include "dps310.h"
#include "altitude_hold.h"

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
#define MAG_PERIOD_MS 40U
#define MAG_CONVERSION_WAIT_MS 4U
#define MAG_MEAS_TIMEOUT_MS 25U
#define MAG_FRESH_TIMEOUT_MS 300U
#define MAG_FILTER_ALPHA 0.12f
#define MAG_MAX_JUMP_DEG 35.0f
/* Offset phần cứng MMC đã dùng trong chương trình đo heading trước đây (Gauss).
 * Cần hiệu chuẩn lại XYZ/hard-iron/soft-iron trên drone đã lắp hoàn chỉnh. */
#define MAG_OFFSET_X_G 0.20172f
#define MAG_OFFSET_Y_G 0.328185f
#define MAG_OFFSET_Z_G 0.0f
#define RAD_TO_DEG 57.295779513f
/* Hiệu chuẩn gyro khi đứng yên trước khi bắt đầu điều khiển. */
#define GYRO_CAL_SAMPLES 500U
#define GYRO_CAL_DELAY_MS 2U
#define GYRO_CAL_RETRIES 3U
#define GYRO_CAL_MAX_STD_DPS 0.75f
#define GYRO_CAL_MAX_BIAS_DPS 3.0f
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
/*===Khai báo lora*/
E220_t lora;

volatile uint32_t e220_uart_tx_drone = 0;

/*Khai báo magnetometer*/
MMC5983MA_t mmc;
float mx, my, mz;
HAL_StatusTypeDef mmc_status;

/*Khai báo IMU*/
ICM42670_t icm;
ICM42670_Data_t imu;

/* Khai báo baro*/
DPS310_t dps310;

/* ALT_HOLD: control independent of Roll/Pitch/Yaw PID. */
AltitudeHold_t altitude_hold;
static uint32_t alt_hold_faults = 0U;
/* AUTO (T mode 2): cat canh + giu do cao bang altitude PID.
 * Moi mode khac (mode 0 = DUNG) -> tat ALT_HOLD, motor 1000. */
static uint8_t auto_was_requested = 0U;
static uint8_t alt_fault_latched = 0U;
static uint8_t armed = 0U;
static float ground_alt_m = 0.0f; /* do cao baro luc cat canh */
static uint32_t land_since_ms = 0U;
static int16_t climb_cmd = 0;					  /* climb thuc dung (co failsafe) */
volatile uint8_t alt_exit_reason = ALT_EXIT_NONE; /* AltExitReason_t, gui trong goi S */
#define AUTO_IDLE_US 1150.0f					  /* quay khong tai luc vua arm tren mat dat */
#define AUTO_HOVER_GUESS_US 1350.0f				  /* uoc luong ga treo, PID tu hoc them */
#define LAND_BAND_M 0.15f
#define LAND_CONFIRM_MS 1000U
/* Phai lon hon DRONE_LINK_CLIMB_TIMEOUT_MS (mat 1 goi S khong duoc kich failsafe). */
#define LINK_LOST_MS 3000U

#define FAILSAFE_CLIMB (-60) /* 0.24 m/s, nhanh hon ro rang so voi nguong dung yen */
/* Phat hien cham dat: van toc gan 0 VA ga thap hon ga treo da hoc. */
#define LAND_STILL_MPS 0.06f		 /* tren van toc da loc cham (tau ~0.5 s) */
#define LAND_THR_DROP_US 40.0f		 /* kem near_ground */
#define LAND_THR_DROP_HARD_US 150.0f /* khong can baro: ga thap the nay ma dung yen = da cham dat */
static float hover_ref_us = AUTO_HOVER_GUESS_US;
static float land_vz_lpf = 0.0f;
/* Ha canh khan cap vong ho khi baro/ALT_HOLD loi giua troi: KHONG cat motor. */
#define EMERG_START_DROP_US 25.0f
#define EMERG_RAMP_US_PER_S 3.0f
#define EMERG_ASSUMED_MPS 0.30f
#define EMERG_EXTRA_MS 6000U
#define EMERG_MAX_MS 30000U
static uint8_t emerg_active = 0U;
static float emerg_start_thr_us = 0.0f;
static uint32_t emerg_start_ms = 0U, emerg_duration_ms = 0U;
/* Mat IMU lien tiep -> cat motor (khong giu PWM cu). 10 lan ~ 20 ms. */
#define IMU_FAIL_CUT_COUNT 10U
static uint32_t imu_fail_count = 0U;

/*Bộ lọc mahony*/
Mahony_t mahony;

AngleController_t angle_ctrl;
RateController_t rate_ctrl;

/*mixer motor*/
MotorMixer_t motor;

DroneLink_t drone_link;
float roll_deg, pitch_deg, yaw_deg;
float mahony_yaw_deg;  /* Chỉ debug, yaw điều khiển lấy MMC + gyro */
float mag_heading_deg; /* Heading MMC theo atan2(+Y, +X), 0..360 */
float mag_yaw_deg;	   /* Heading MMC đã đổi dấu theo yaw gyro */
float yaw_target_deg;  /* Chốt khi chuyển ga 1000 -> >1000 */
float roll_rate_sp, pitch_rate_sp, yaw_rate_sp;
static uint8_t yaw_estimate_valid;
static uint8_t yaw_target_latched;
static uint8_t mag_pending;
static uint32_t mag_next_tick, mag_start_tick, mag_last_good_tick;
static uint32_t mag_ok_count, mag_error_count, mag_rejected_count;

float roll_pid, pitch_pid, yaw_pid;

float throttle = 1000;

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
/* Chỉ chấp nhận bias gyro khi FC đứng yên để có mốc tốc độ quay đúng cho điều khiển. */
static ICM42670_Status_t Gyro_CalibrateIfStationary(ICM42670_t *dev)
{
	if (dev == NULL)
		return ICM42670_ERROR;
	for (uint32_t attempt = 1U; attempt <= GYRO_CAL_RETRIES; ++attempt)
	{
		float sx = 0.0f, sy = 0.0f, sz = 0.0f;
		float sx2 = 0.0f, sy2 = 0.0f, sz2 = 0.0f;
		ICM42670_Data_t reading;
		for (uint32_t i = 0U; i < GYRO_CAL_SAMPLES; ++i)
		{
			ICM42670_Status_t st = ICM42670_ReadAll(&reading);
			if (st != ICM42670_OK)
				return st;
			float x = reading.gx_dps, y = reading.gy_dps, z = reading.gz_dps;
			sx += x;
			sy += y;
			sz += z;
			sx2 += x * x;
			sy2 += y * y;
			sz2 += z * z;
			HAL_Delay(GYRO_CAL_DELAY_MS);
		}
		const float inv = 1.0f / (float)GYRO_CAL_SAMPLES;
		const float bx = sx * inv, by = sy * inv, bz = sz * inv;
		const float std_x = sqrtf(fmaxf(0.0f, sx2 * inv - bx * bx));
		const float std_y = sqrtf(fmaxf(0.0f, sy2 * inv - by * by));
		const float std_z = sqrtf(fmaxf(0.0f, sz2 * inv - bz * bz));
		const uint8_t valid =
			isfinite(bx) && isfinite(by) && isfinite(bz) &&
			std_x <= GYRO_CAL_MAX_STD_DPS &&
			std_y <= GYRO_CAL_MAX_STD_DPS &&
			std_z <= GYRO_CAL_MAX_STD_DPS &&
			fabsf(bx) <= GYRO_CAL_MAX_BIAS_DPS &&
			fabsf(by) <= GYRO_CAL_MAX_BIAS_DPS &&
			fabsf(bz) <= GYRO_CAL_MAX_BIAS_DPS;
		if (valid)
		{
			dev->gyro_bias_x_dps = bx;
			dev->gyro_bias_y_dps = by;
			dev->gyro_bias_z_dps = bz;
			return ICM42670_OK;
		}
		HAL_Delay(300U);
	}
	/* Never arm with an invalid gyro zero-rate reference. */
	return ICM42670_ERROR;
}

/** @brief Ghi bốn lệnh motor theo thứ tự M1..M4. */
static void Motors_Write(void)
{
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, motor.m1);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, motor.m2);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, motor.m3);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, motor.m4);
}

/** @brief Tra goi S (chi khi co T dang cho): ga THAT + ly do thoat ALT_HOLD. */
static void Send_Status(void)
{
	float thr = throttle;
	if (!isfinite(thr) || thr < 1000.0f)
		thr = 1000.0f;
	else if (thr > (float)DRONE_LINK_MAX_THR)
		thr = (float)DRONE_LINK_MAX_THR;
	(void)DroneLink_SendStatus(&drone_link, (uint16_t)(thr + 0.5f),
							   roll_deg, pitch_deg, yaw_deg,
							   motor.m1, motor.m2, motor.m3, motor.m4,
							   altitude_hold.active,
							   isfinite(dps310.altitude_rel_m) ? dps310.altitude_rel_m : 0.0f,
							   alt_exit_reason);
}

/* Baro/ALT_HOLD loi khi dang bay: giu ga treo da hoc tru mot chut, giam dan,
 * het thoi gian uoc luong thi tat. Goi TRUOC khi AltitudeHold_Reset. */
static void Emergency_Begin(uint8_t reason, uint32_t now_ms)
{
	if (!altitude_hold.active)
		return;
	float hover = altitude_hold.trim_us + altitude_hold.integral_us;
	if (!isfinite(hover))
		hover = AUTO_HOVER_GUESS_US;
	float thr = hover - EMERG_START_DROP_US;
	if (thr < AUTO_IDLE_US)
		thr = AUTO_IDLE_US;
	if (thr > 1650.0f)
		thr = 1650.0f;
	/* target_m la do cao cuoi cung con tin duoc (altitude_m co the la mau loi). */
	float h = altitude_hold.target_m - ground_alt_m;
	if (!isfinite(h) || h < 0.0f)
		h = 0.0f;
	if (h > 20.0f)
		h = 20.0f;
	emerg_start_thr_us = thr;
	emerg_duration_ms = (uint32_t)(h / EMERG_ASSUMED_MPS * 1000.0f) + EMERG_EXTRA_MS;
	if (emerg_duration_ms > EMERG_MAX_MS)
		emerg_duration_ms = EMERG_MAX_MS;
	emerg_start_ms = now_ms;
	emerg_active = 1U;
	land_since_ms = 0U;
	alt_exit_reason = reason;
	AltitudeHold_Reset(&altitude_hold);
}

static float Emergency_Throttle(uint32_t now_ms)
{
	const uint32_t elapsed = now_ms - emerg_start_ms;
	if (elapsed >= emerg_duration_ms)
	{
		emerg_active = 0U;
		armed = 0U;
		alt_exit_reason = ALT_EXIT_EMERG_LANDED;
		return 1000.0f;
	}
	float thr = emerg_start_thr_us - EMERG_RAMP_US_PER_S * ((float)elapsed * 0.001f);
	return (thr < AUTO_IDLE_US) ? AUTO_IDLE_US : thr;
}

/* Chuẩn góc yaw 0..360 và sai số ngắn nhất -180..180 (độ). */
static float Yaw_Wrap360(float deg)
{
	deg = fmodf(deg, 360.0f);
	return (deg < 0.0f) ? deg + 360.0f : deg;
}
static float Yaw_Wrap180(float deg)
{
	return Yaw_Wrap360(deg + 180.0f) - 180.0f;
}

/* Gọi ở 500 Hz: gyro cung cấp biến thiên nhanh, MMC neo heading dài hạn. */
static void Yaw_IntegrateGyro(float gyro_z_dps, float dt)
{
	if (yaw_estimate_valid && isfinite(gyro_z_dps) && isfinite(dt))
	{
		yaw_deg = Yaw_Wrap360(yaw_deg + gyro_z_dps * dt);
	}
}

/* Đọc MMC ở tần số thấp, KHÔNG poll chờ/HAL_Delay bên trong.
 * Chỉ đúng công thức khi trục X/Y/Z MMC cùng chiều trục X/Y/Z IMU.
 * Nếu lắp xoay khác chiều, cần hoán đổi/đổi dấu trục trước khi bù nghiêng. */
static void Mag_Service(void)
{
	uint32_t now = HAL_GetTick();
	if (!mag_pending)
	{
		if ((int32_t)(now - mag_next_tick) < 0)
			return;
		mmc_status = MMC5983_StartMeasurement(&mmc);
		if (mmc_status == HAL_OK)
		{
			mag_pending = 1U;
			mag_start_tick = now;
		}
		else
		{
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
	if (mmc_status != HAL_OK)
	{
		++mag_error_count;
		return;
	}

	float bx = mx - MAG_OFFSET_X_G;
	float by = my - MAG_OFFSET_Y_G;
	float bz = mz - MAG_OFFSET_Z_G;
	float norm2 = bx * bx + by * by + bz * bz;
	/* Đánh giá sơ bộ độ lớn từ trường: chưa thay thế hiệu chuẩn chính xác. */
	if (!isfinite(norm2) || norm2 < 0.01f || norm2 > 4.0f ||
		!isfinite(roll_deg) || !isfinite(pitch_deg))
	{
		++mag_rejected_count;
		return;
	}

	float r = roll_deg / RAD_TO_DEG;
	float p = pitch_deg / RAD_TO_DEG;
	float sr = sinf(r), cr = cosf(r), sp = sinf(p), cp = cosf(p);
	/* Bù roll/pitch theo Euler ZYX. */
	float hx = bx * cp + by * sr * sp + bz * cr * sp;
	float hy = by * cr - bz * sr;
	if (!isfinite(hx) || !isfinite(hy) || hx * hx + hy * hy < 0.001f)
	{
		++mag_rejected_count;
		return;
	}
	mag_heading_deg = Yaw_Wrap360(atan2f(hy, hx) * RAD_TO_DEG);
	/* Khi quay thân +yaw (gyro Z dương), vector địa từ trên MMC quay -yaw.
	 Đổi dấu để yaw từ MMC CÙNG CHIỀU với yaw gyro/Mahony. */
	mag_yaw_deg = Yaw_Wrap360(-mag_heading_deg);
	if (!yaw_estimate_valid || (now - mag_last_good_tick) > 1000U)
	{
		/* Sau khởi động/mất MMC lâu: lấy lại mốc heading, không PID vào mốc cũ. */
		yaw_deg = mag_yaw_deg;
		yaw_estimate_valid = 1U;
		yaw_target_latched = 0U;
	}
	else
	{
		float delta = Yaw_Wrap180(mag_yaw_deg - yaw_deg);
		if (fabsf(delta) > MAG_MAX_JUMP_DEG)
		{
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
int main(void)
{

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
	if (mmc_status != HAL_OK)
	{
		Error_Handler();
	}
	mag_next_tick = HAL_GetTick();

	if (ICM42670_Init(&icm) != ICM42670_OK)
	{
		Error_Handler();
	}

	if (Gyro_CalibrateIfStationary(&icm) != ICM42670_OK)
	{
		Error_Handler();
	}

	if (DPS310_Init(&dps310, &hspi2,
					GPIOB,
					GPIO_PIN_12) != HAL_OK)
	{
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

	uint32_t baro_cal_start = HAL_GetTick();

	while ((HAL_GetTick() - baro_cal_start) < 4000U)
	{
		DPS310_ReadIfReady(&dps310);
		HAL_Delay(5U);
	}

	if (!dps310.home_valid)
	{

		Error_Handler();
	}

	const uint16_t tilt_samples = 100U;
	float ax_sum = 0.0f;
	float ay_sum = 0.0f;
	float az_sum = 0.0f;

	for (uint16_t i = 0U; i < tilt_samples; ++i)
	{
		if (ICM42670_ReadAll(&imu) != ICM42670_OK)
		{
			Error_Handler();
		}
		ax_sum += imu.ax_g;
		ay_sum += imu.ay_g;
		az_sum += imu.az_g;
		HAL_Delay(2U);
	}
	if (!Mahony_InitFromAccel(&mahony, ax_sum / tilt_samples,
							  ay_sum / tilt_samples, az_sum / tilt_samples))
	{
		Error_Handler();
	}
	Mahony_GetEuler(&mahony, &roll_deg, &pitch_deg, &mahony_yaw_deg);
	AngleController_Init(&angle_ctrl);
	RateController_Init(&rate_ctrl);

	if (E220_Init(&lora, &huart6) != HAL_OK)
	{
		Error_Handler();
	}

	DroneLink_Init(&drone_link, &lora, &angle_ctrl, &rate_ctrl);
	/* Use the existing USART1 38400 8N1 settings. GPS is optional for flight.
	 * stm32f4xx_it.c must provide USART1_IRQHandler -> HAL_UART_IRQHandler. */
	HAL_NVIC_SetPriority(USART1_IRQn, 6U, 0U);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	(void)GPS_Init(&huart1);
	AltitudeHold_Reset(&altitude_hold);
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
	while (1)
	{
		DroneLink_Poll(&drone_link);
		GPS_Process(); /* Decode queued RMC/GGA outside UART IRQ. */

		uint32_t now_cycles = DWT->CYCCNT;
		uint32_t elapsed_cycles = now_cycles - last_control_cycles;
		if (elapsed_cycles < control_period_cycles)
		{
			continue;
		}

		last_control_cycles = now_cycles;
		elapsed_cycles = now_cycles - last_sample_cycles;
		if (elapsed_cycles > control_cycles_per_us * CONTROL_MAX_DT_US)
		{
			/* Không đưa khoảng gián đoạn dài vào cả Mahony lẫn PID. */
			last_sample_cycles = now_cycles;
			continue;
		}

		/* ================= IMU ================= */

		if (ICM42670_ReadAll(&imu) != ICM42670_OK)
		{
			if (++imu_fail_count >= IMU_FAIL_CUT_COUNT)
			{
				/* Khong co IMU = khong giu duoc tu the: khong de PWM cu chay mai. */
				if (altitude_hold.active || emerg_active || armed)
					alt_exit_reason = ALT_EXIT_IMU;
				AltitudeHold_Reset(&altitude_hold);
				emerg_active = 0U;
				armed = 0U;
				alt_fault_latched = 1U;
				throttle = 1000.0f;
				motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;
				Motors_Write();
			}
			last_control_cycles = last_sample_cycles = DWT->CYCCNT;
			Send_Status();
			continue;
		}
		imu_fail_count = 0U;

		/* dt là khoảng cách giữa các mẫu đã đọc xong, kể cả trễ SPI thực tế. */
		uint32_t sample_cycles = DWT->CYCCNT;
		elapsed_cycles = sample_cycles - last_sample_cycles;
		last_sample_cycles = sample_cycles;
		if (elapsed_cycles < control_cycles_per_us * CONTROL_MIN_DT_US || elapsed_cycles > control_cycles_per_us * CONTROL_MAX_DT_US)
		{
			last_control_cycles = sample_cycles;
			continue;
		}
		float dt = (float)elapsed_cycles / (float)control_clock_hz;

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
		/* AUTO / DUNG arbitration. ALT_HOLD chi chay khi T mode 2,
		 * DPS310 co home hop le va mau moi.
		 * Khong cap nhat PID do cao o toc do IMU 500 Hz.
		 */
		const uint32_t alt_now_ms = HAL_GetTick();
		const uint8_t baro_healthy = dps310.home_valid && dps310.valid && (alt_now_ms - dps310.last_update_ms <= 180U) && isfinite(dps310.altitude_rel_m);

		const uint8_t auto_mode = drone_link.auto_requested ? 1U : 0U;
		if (auto_mode)
		{
			if (!auto_was_requested)
			{
				AltitudeHold_Reset(&altitude_hold);
				armed = 0U;
				alt_fault_latched = 0U;
				land_since_ms = 0U;
				emerg_active = 0U;
			}
			/* Failsafe: mat T qua LINK_LOST_MS -> tu ha cham, KHONG cat motor giua troi. */
			const uint8_t link_lost =
				(uint32_t)(alt_now_ms - drone_link.last_throttle_ms) > LINK_LOST_MS;
			climb_cmd = link_lost ? (int16_t)FAILSAFE_CLIMB
								  : DroneLink_ClimbCommand(&drone_link);

			if (!baro_healthy && altitude_hold.active)
			{
				/* Baro hong GIUA TROI: ha canh khan cap, KHONG cat motor. */
				alt_fault_latched = 1U;
				++alt_hold_faults;
				Emergency_Begin(ALT_EXIT_BARO_LATCHED, alt_now_ms);
			}

			// if (!baro_healthy || alt_fault_latched)
			if (emerg_active)
			{
				// if (altitude_hold.active)
				// {
				// 	++alt_hold_faults;
				// 	alt_exit_reason = alt_fault_latched ? ALT_EXIT_BARO_LATCHED
				// 										: ALT_EXIT_BARO;
				// }
			}
			else if (!baro_healthy || alt_fault_latched)
			{
				AltitudeHold_Reset(&altitude_hold);
				armed = 0U;
			}
			else if (!altitude_hold.active)
			{
				/* Tren mat dat. Arm o lan day len dau tien. */
				if (!armed && !link_lost && climb_cmd > 0)
					armed = 1U;
				if (armed && link_lost)
				{
					armed = 0U; /* mat link khi o mat dat: tat */
				}
				else if (armed && climb_cmd > 0)
				{
					/* Bat giu do cao ngay tu mat dat, khong cho 0.3 m. */
					ground_alt_m = dps310.altitude_rel_m;
					land_since_ms = 0U;
					hover_ref_us = AUTO_HOVER_GUESS_US;
					land_vz_lpf = 0.0f;
					if (AltitudeHold_Start(&altitude_hold, dps310.altitude_rel_m,
										   AUTO_HOVER_GUESS_US, dps310.last_update_ms))
					{
						altitude_hold.throttle_us = AUTO_IDLE_US; /* slew len tu idle */
						alt_exit_reason = ALT_EXIT_NONE;
					}
				}
			}
			else
			{
				/* Ha canh: dang keo xuong va sat mat dat 1 s -> disarm, motor 1000.
				 * Bam LEN lai se tu arm + cat canh, khong can KICH HOAT LAI. */
				const uint8_t near_ground =
					(dps310.altitude_rel_m - ground_alt_m) < LAND_BAND_M;
				// if (climb_cmd < 0 && near_ground)
				/* vz baro nhieu +-0.1 m/s ngay ca khi nam yen: loc them truoc khi so. */
				land_vz_lpf += 0.004f * (altitude_hold.vz_mps - land_vz_lpf);
				const uint8_t still = fabsf(land_vz_lpf) < LAND_STILL_MPS;
				/* Hoc ga treo khi dang dung yen o do cao (tau ~1 s o 500 Hz). */
				if (climb_cmd == 0 && fabsf(altitude_hold.vz_mps) < 0.10f)
					hover_ref_us += 0.002f * (altitude_hold.throttle_us - hover_ref_us);
				const float thr_drop = hover_ref_us - altitude_hold.throttle_us;
				/* Chi baro gan dat la chua du (baro troi +-0.3 m): phai dung yen
				 * VA ga da tut duoi ga treo, tuc la mat dat dang do drone. */
				const uint8_t landed_like = still &&
											((near_ground && thr_drop > LAND_THR_DROP_US) ||
											 thr_drop > LAND_THR_DROP_HARD_US);
				if (climb_cmd < 0 && landed_like)
				{
					if (land_since_ms == 0U)
						land_since_ms = alt_now_ms | 1U;
					else if ((uint32_t)(alt_now_ms - land_since_ms) >= LAND_CONFIRM_MS)
					{
						AltitudeHold_Reset(&altitude_hold);
						land_since_ms = 0U;
						armed = 0U;
						alt_exit_reason = link_lost ? ALT_EXIT_FAILSAFE_LANDED
													: ALT_EXIT_LANDED;
					}
				}
				else
					land_since_ms = 0U;
			}
			// throttle = altitude_hold.active ? altitude_hold.throttle_us
			// 								: (armed ? AUTO_IDLE_US : 1000.0f);
			if (emerg_active)
				throttle = Emergency_Throttle(alt_now_ms);
			else
				throttle = altitude_hold.active ? altitude_hold.throttle_us
												: (armed ? AUTO_IDLE_US : 1000.0f);
		}
		else
		{
			/* T mode 0 (DUNG) hoac mode khong ho tro: cat ALT_HOLD, motor 1000.
			 * Truoc day nhanh nay thieu -> throttle giu gia tri cu sau khi DUNG. */
			if (altitude_hold.active)
				alt_exit_reason = ALT_EXIT_STOPPED;
			AltitudeHold_Reset(&altitude_hold);
			armed = 0U;
			alt_fault_latched = 0U;
			land_since_ms = 0U;
			emerg_active = 0U; /* DUNG = kill switch, cat ngay ca khi dang ha khan cap */
			climb_cmd = 0;
			throttle = 1000.0f;
		}
		auto_was_requested = auto_mode;
		if (throttle > 1000.0f)
		{
			/* Mặc định: góc P -> tốc độ PI. Giữ nguyên dấu IMU và mixer. */
			AngleController_Update(&angle_ctrl,
								   (float)DroneLink_RollCommand(&drone_link),
								   (float)DroneLink_PitchCommand(&drone_link),
								   roll_deg, pitch_deg,
								   dt, &roll_rate_sp, &pitch_rate_sp);
			/* Yaw setpoint là hướng MMC ở thời điểm BẮT ĐẦU lên ga.
			 * Không cập nhật setpoint theo góc hiện tại khi đang bay. */
			uint32_t mag_age = HAL_GetTick() - mag_last_good_tick;
			uint8_t mag_fresh = yaw_estimate_valid && (mag_age <= MAG_FRESH_TIMEOUT_MS);
			if (mag_fresh && !yaw_target_latched)
			{
				yaw_target_deg = yaw_deg;
				yaw_target_latched = 1U;
				PID_Reset(&angle_ctrl.yaw);
				PID_Reset(&rate_ctrl.yaw);
			}
			if (mag_fresh && yaw_target_latched)
			{
				/* Can trai ngang = toc do yaw; tha can thi yaw PID
				 * giu huong hien tai. */
				if (auto_mode)
					yaw_target_deg = Yaw_Wrap360(yaw_target_deg +
												 (float)DroneLink_YawRateCommand(&drone_link) * dt);
				yaw_rate_sp = AngleController_UpdateYaw(&angle_ctrl,
														yaw_target_deg, yaw_deg, dt);
			}
			else
			{
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

			Mixer_QuadX(throttle, roll_pid, pitch_pid, yaw_pid, &motor);
		}
		else
		{
			motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;
			/* Motor dung: lan len ga sau chot lai huong HIEN TAI va xoa
			 * tich phan/D cu, khong mang trang thai chuyen bay truoc. */
			yaw_target_latched = 0U;
			PID_Reset(&angle_ctrl.roll);
			PID_Reset(&angle_ctrl.pitch);
			PID_Reset(&angle_ctrl.yaw);
			PID_Reset(&rate_ctrl.roll);
			PID_Reset(&rate_ctrl.pitch);
			PID_Reset(&rate_ctrl.yaw);
		}

		Motors_Write();
		/* Xử lý MMC sau PWM; cập nhật yaw fused cho chu kỳ điều khiển kế. */
		Mag_Service();

		/* DPS310 32 Hz: only update vertical PID when a NEW sample arrives. */
		static uint32_t last_baro_tick = 0U;
		uint32_t baro_now_ms = HAL_GetTick();
		if ((baro_now_ms - last_baro_tick) >= 10U)
		{
			last_baro_tick = baro_now_ms;
			if (DPS310_ReadIfReady(&dps310) == HAL_OK && altitude_hold.active && dps310.home_valid)
			{
				if (!AltitudeHold_Update(&altitude_hold, dps310.altitude_rel_m,
										 dps310.last_update_ms, climb_cmd))
				{
					// alt_exit_reason = ALT_EXIT_UPDATE_FAULT;
					// AltitudeHold_Reset(&altitude_hold);
					alt_fault_latched = 1U;
					++alt_hold_faults;
					Emergency_Begin(ALT_EXIT_UPDATE_FAULT, baro_now_ms);
				}
			}
		}

		Send_Status();

		/* UART1 RX is reserved for GPS: no outgoing debug logs on this port. */

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 84;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
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
static void MX_I2C2_Init(void)
{

	/* USER CODE BEGIN I2C2_Init 0 */

	/* USER CODE END I2C2_Init 0 */

	/* USER CODE BEGIN I2C2_Init 1 */

	/* USER CODE END I2C2_Init 1 */
	hi2c2.Instance = I2C2;
	hi2c2.Init.ClockSpeed = 100000;
	hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c2.Init.OwnAddress1 = 0;
	hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c2.Init.OwnAddress2 = 0;
	hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c2) != HAL_OK)
	{
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
static void MX_SPI1_Init(void)
{

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
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
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
static void MX_SPI2_Init(void)
{

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
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
static void MX_TIM5_Init(void)
{

	/* USER CODE BEGIN TIM5_Init 0 */

	/* USER CODE END TIM5_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM5_Init 1 */

	/* USER CODE END TIM5_Init 1 */
	htim5.Instance = TIM5;
	htim5.Init.Prescaler = 83;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = 4999;
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
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
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
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
static void MX_USART6_UART_Init(void)
{

	/* USER CODE BEGIN USART6_Init 0 */

	/* USER CODE END USART6_Init 0 */

	/* USER CODE BEGIN USART6_Init 1 */

	/* USER CODE END USART6_Init 1 */
	huart6.Instance = USART6;
	huart6.Init.BaudRate = 9600;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART6_Init 2 */

	/* USER CODE END USART6_Init 2 */
}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

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
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		GPS_RxCpltCallback();
	}
	else if (huart->Instance == USART6)
	{
		E220_RxCallback(&lora);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART6)
	{
		E220_TxCpltCallback(&lora);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		GPS_ErrorCallback();
	}
	else if (huart->Instance == USART6)
	{
		E220_ErrorCallback(&lora);
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
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
