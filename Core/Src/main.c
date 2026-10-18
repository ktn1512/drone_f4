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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

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

ICM42670_t icm;
ICM42670_Data_t imu;

Mahony_t mahony;

AngleController_t angle_ctrl;
RateController_t rate_ctrl;

MotorMixer_t motor;

DroneLink_t drone_link;
float roll_deg, pitch_deg, yaw_deg;

float roll_rate_sp, pitch_rate_sp;

float roll_pid, pitch_pid, yaw_pid;

float throttle = 1000;

char uart_buf[128];

static char tx_frame[512];

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
uint32_t last_tick;

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
  if (ICM42670_Init(&icm) != ICM42670_OK)
  {
    sprintf(uart_buf, "ICM init err\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t *)uart_buf, strlen(uart_buf),
                      HAL_MAX_DELAY);
    Error_Handler();
  }

  if (ICM42670_CalibrateGyro(&icm, 500, 2) != ICM42670_OK)
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

  HAL_Delay(4000);

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
  Mahony_GetEuler(&mahony, &roll_deg, &pitch_deg, &yaw_deg);
  AngleController_Init(&angle_ctrl);
  RateController_Init(&rate_ctrl);

  if (E220_Init(&lora, &huart6) != HAL_OK)
  {
    Error_Handler();
  }

  DroneLink_Init(&drone_link, &lora, &angle_ctrl, &rate_ctrl);
  motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;

  last_tick = HAL_GetTick();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    DroneLink_Poll(&drone_link);

    uint32_t now = HAL_GetTick(); /**< Thời gian hiện tại của vòng lặp, đơn vị ms; phép trừ unsigned xử lý tràn tick. */

    float dt = (now - last_tick) * 0.001f; /**< Thời gian giữa hai lần cập nhật điều khiển, đổi từ ms sang giây. */

    if (dt < 0.002f)
    {
      continue;
    }

    last_tick = now;

    /* ================= IMU ================= */

    if (ICM42670_ReadAll(&imu) != ICM42670_OK)
    {
      // IMU failure must not leave the previous motor PWM active.
      DroneLink_SetMinimumThrottle(&drone_link);
      __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 1000);
      __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 1000);
      __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 1000);
      __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 1000);
      motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000;
      (void)DroneLink_SendStatus(&drone_link, roll_deg, pitch_deg,
                                 yaw_deg, motor.m1, motor.m2, motor.m3, motor.m4);
      continue;
    }

    ICM42670_ApplyCalibration(&icm, &imu);

    /* ================= MAHONY ================= */

    Mahony_Update(&mahony, imu.gx_dps, imu.gy_dps, imu.gz_dps, imu.ax_g,
                  imu.ay_g, imu.az_g, dt);

    Mahony_GetEuler(&mahony, &roll_deg, &pitch_deg, &yaw_deg);

    /*
     * Nếu IMU gắn khác chiều
     * thì đổi dấu tại đây
     */

    // roll_deg  = -roll_deg;
    // pitch_deg = -pitch_deg;
    /* ================= ANGLE PID ================= */

    AngleController_Update(&angle_ctrl, 0.0f, // roll target
                           0.0f,              // pitch target

                           roll_deg, pitch_deg, dt, &roll_rate_sp, &pitch_rate_sp);

    /* ================= RATE PID ================= */

    RateController_Update(&rate_ctrl, roll_rate_sp, pitch_rate_sp, 0.0f,
                          imu.gx_dps, imu.gy_dps, imu.gz_dps, dt, &roll_pid, &pitch_pid,
                          &yaw_pid);

    /* Snapshot the terms actually used, before minimum-throttle PID_Reset. */
    //		uint8_t pitch_pid_valid = rate_ctrl.pitch.initialized;
    //		float pitch_p_term = rate_ctrl.pitch.kp * rate_ctrl.pitch.prev_error;
    //		float pitch_i_term = rate_ctrl.pitch.integral;
    //		float pitch_d_term = -rate_ctrl.pitch.kd
    //				* rate_ctrl.pitch.derivative_filtered;

    /* ================= MIXER ================= */

    throttle = (float)DroneLink_Throttle(&drone_link);
    if (throttle > 1000.0f)
    {
      Mixer_QuadX(throttle, roll_pid, pitch_pid, yaw_pid, &motor);
    }
    else
    {
      motor.m1 = motor.m2 = motor.m3 = motor.m4 = 1000U;
      PID_Reset(&angle_ctrl.roll);
      PID_Reset(&angle_ctrl.pitch);
      PID_Reset(&rate_ctrl.roll);
      PID_Reset(&rate_ctrl.pitch);
      PID_Reset(&rate_ctrl.yaw);
    }

    // Xuat PWM ra ESC
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, motor.m1);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, motor.m2);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, motor.m3);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, motor.m4);

    (void)DroneLink_SendStatus(&drone_link,
                               roll_deg, pitch_deg, yaw_deg,
                               motor.m1, motor.m2, motor.m3, motor.m4);

    static uint32_t last_log_tick = 0U; /**< Mốc gửi log gần nhất, đơn vị ms; giữ giá trị giữa các vòng lặp. */

    uint32_t log_now = HAL_GetTick();
    if ((log_now - last_log_tick >= 500U) && (huart1.gState == HAL_UART_STATE_READY))
    {
      last_log_tick = log_now;

      /** @brief Số ký tự snprintf cần ghi, không tính NUL; chỉ gửi khi bộ đệm đủ chỗ. */
      int len =
          snprintf(tx_frame, sizeof(tx_frame),
                   "thr=%u angle=%.1f,%.1f,%.1f pid=%.1f,%.1f m=%u,%u,%u,%u\r\n"
                   "LORA T_RX=%lu P_WR=%lu P_RD=%lu TIMEOUT=%lu BAD=%lu"
                   " RX_BYTE=%lu S_REQ=%lu TX_DMA_START=%lu TX_DMA_DONE=%lu"
                   " TX_BUSY=%lu TX_ERR=%lu UART_ERR=%lu\r\n",
                   (unsigned)DroneLink_Throttle(&drone_link),
                   roll_deg, pitch_deg, yaw_deg, roll_pid, pitch_pid,
                   (unsigned)motor.m1, (unsigned)motor.m2,
                   (unsigned)motor.m3, (unsigned)motor.m4,
                   (unsigned long)drone_link.throttle_rx_count,
                   (unsigned long)drone_link.pid_write_count,
                   (unsigned long)drone_link.pid_read_count,
                   (unsigned long)drone_link.throttle_timeout_count,
                   (unsigned long)drone_link.rx_invalid_frames,
                   (unsigned long)drone_link.rx_byte_count,
                   (unsigned long)drone_link.status_request_count,
                   (unsigned long)lora.tx_start_count,
                   (unsigned long)lora.tx_done_count,
                   (unsigned long)lora.tx_busy_count,
                   (unsigned long)lora.tx_error_count,
                   (unsigned long)lora.uart_error_count);

      if ((len > 0) && ((size_t)len < sizeof(tx_frame)))
      {
        HAL_UART_Transmit_IT(&huart1, (uint8_t *)tx_frame,
                             (uint16_t)len);
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
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
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
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
  htim5.Init.Period = 19999;
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART6) {
        E220_RxCallback(&lora);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART6) {
        E220_TxCpltCallback(&lora);
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART6) {
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
