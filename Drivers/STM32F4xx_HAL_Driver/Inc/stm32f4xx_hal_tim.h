#ifndef STM32F4xx_HAL_TIM_H
#define STM32F4xx_HAL_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t Prescaler;

  uint32_t CounterMode;

  uint32_t Period;

  uint32_t ClockDivision;

  uint32_t RepetitionCounter;

  uint32_t AutoReloadPreload;
} TIM_Base_InitTypeDef;

typedef struct
{
  uint32_t OCMode;

  uint32_t Pulse;

  uint32_t OCPolarity;

  uint32_t OCNPolarity;

  uint32_t OCFastMode;

  uint32_t OCIdleState;

  uint32_t OCNIdleState;
} TIM_OC_InitTypeDef;

typedef struct
{
  uint32_t OCMode;

  uint32_t Pulse;

  uint32_t OCPolarity;

  uint32_t OCNPolarity;

  uint32_t OCIdleState;

  uint32_t OCNIdleState;

  uint32_t ICPolarity;

  uint32_t ICSelection;

  uint32_t ICFilter;
} TIM_OnePulse_InitTypeDef;

typedef struct
{
  uint32_t  ICPolarity;

  uint32_t ICSelection;

  uint32_t ICPrescaler;

  uint32_t ICFilter;
} TIM_IC_InitTypeDef;

typedef struct
{
  uint32_t EncoderMode;

  uint32_t IC1Polarity;

  uint32_t IC1Selection;

  uint32_t IC1Prescaler;

  uint32_t IC1Filter;

  uint32_t IC2Polarity;

  uint32_t IC2Selection;

  uint32_t IC2Prescaler;

  uint32_t IC2Filter;
} TIM_Encoder_InitTypeDef;

typedef struct
{
  uint32_t ClockSource;
  uint32_t ClockPolarity;
  uint32_t ClockPrescaler;
  uint32_t ClockFilter;
} TIM_ClockConfigTypeDef;

typedef struct
{
  uint32_t ClearInputState;
  uint32_t ClearInputSource;
  uint32_t ClearInputPolarity;
  uint32_t ClearInputPrescaler;
  uint32_t ClearInputFilter;
} TIM_ClearInputConfigTypeDef;

typedef struct
{
  uint32_t  MasterOutputTrigger;
  uint32_t  MasterSlaveMode;
} TIM_MasterConfigTypeDef;

typedef struct
{
  uint32_t  SlaveMode;
  uint32_t  InputTrigger;
  uint32_t  TriggerPolarity;
  uint32_t  TriggerPrescaler;
  uint32_t  TriggerFilter;

} TIM_SlaveConfigTypeDef;

typedef struct
{
  uint32_t OffStateRunMode;

  uint32_t OffStateIDLEMode;

  uint32_t LockLevel;

  uint32_t DeadTime;

  uint32_t BreakState;

  uint32_t BreakPolarity;

  uint32_t BreakFilter;

  uint32_t AutomaticOutput;

} TIM_BreakDeadTimeConfigTypeDef;

typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,
  HAL_TIM_STATE_READY             = 0x01U,
  HAL_TIM_STATE_BUSY              = 0x02U,
  HAL_TIM_STATE_TIMEOUT           = 0x03U,
  HAL_TIM_STATE_ERROR             = 0x04U
} HAL_TIM_StateTypeDef;

typedef enum
{
  HAL_TIM_CHANNEL_STATE_RESET             = 0x00U,
  HAL_TIM_CHANNEL_STATE_READY             = 0x01U,
  HAL_TIM_CHANNEL_STATE_BUSY              = 0x02U,
} HAL_TIM_ChannelStateTypeDef;

typedef enum
{
  HAL_DMA_BURST_STATE_RESET             = 0x00U,
  HAL_DMA_BURST_STATE_READY             = 0x01U,
  HAL_DMA_BURST_STATE_BUSY              = 0x02U,
} HAL_TIM_DMABurstStateTypeDef;

typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U
} HAL_TIM_ActiveChannel;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
typedef struct __TIM_HandleTypeDef
#else
typedef struct
#endif
{
  TIM_TypeDef                        *Instance;
  TIM_Base_InitTypeDef               Init;
  HAL_TIM_ActiveChannel              Channel;
  DMA_HandleTypeDef                  *hdma[7];
  HAL_LockTypeDef                    Lock;
  __IO HAL_TIM_StateTypeDef          State;
  __IO HAL_TIM_ChannelStateTypeDef   ChannelState[4];
  __IO HAL_TIM_ChannelStateTypeDef   ChannelNState[4];
  __IO HAL_TIM_DMABurstStateTypeDef  DMABurstState;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  void (* Base_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* Base_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* IC_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* IC_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* OC_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* OC_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PWM_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PWM_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* OnePulse_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* OnePulse_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* Encoder_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* Encoder_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* HallSensor_MspInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* HallSensor_MspDeInitCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PeriodElapsedCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PeriodElapsedHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);
  void (* TriggerCallback)(struct __TIM_HandleTypeDef *htim);
  void (* TriggerHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);
  void (* IC_CaptureCallback)(struct __TIM_HandleTypeDef *htim);
  void (* IC_CaptureHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);
  void (* OC_DelayElapsedCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PWM_PulseFinishedCallback)(struct __TIM_HandleTypeDef *htim);
  void (* PWM_PulseFinishedHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);
  void (* ErrorCallback)(struct __TIM_HandleTypeDef *htim);
  void (* CommutationCallback)(struct __TIM_HandleTypeDef *htim);
  void (* CommutationHalfCpltCallback)(struct __TIM_HandleTypeDef *htim);
  void (* BreakCallback)(struct __TIM_HandleTypeDef *htim);
#endif
} TIM_HandleTypeDef;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

typedef enum
{
  HAL_TIM_BASE_MSPINIT_CB_ID              = 0x00U
  , HAL_TIM_BASE_MSPDEINIT_CB_ID          = 0x01U
  , HAL_TIM_IC_MSPINIT_CB_ID              = 0x02U
  , HAL_TIM_IC_MSPDEINIT_CB_ID            = 0x03U
  , HAL_TIM_OC_MSPINIT_CB_ID              = 0x04U
  , HAL_TIM_OC_MSPDEINIT_CB_ID            = 0x05U
  , HAL_TIM_PWM_MSPINIT_CB_ID             = 0x06U
  , HAL_TIM_PWM_MSPDEINIT_CB_ID           = 0x07U
  , HAL_TIM_ONE_PULSE_MSPINIT_CB_ID       = 0x08U
  , HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID     = 0x09U
  , HAL_TIM_ENCODER_MSPINIT_CB_ID         = 0x0AU
  , HAL_TIM_ENCODER_MSPDEINIT_CB_ID       = 0x0BU
  , HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID     = 0x0CU
  , HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID   = 0x0DU
  , HAL_TIM_PERIOD_ELAPSED_CB_ID          = 0x0EU
  , HAL_TIM_PERIOD_ELAPSED_HALF_CB_ID     = 0x0FU
  , HAL_TIM_TRIGGER_CB_ID                 = 0x10U
  , HAL_TIM_TRIGGER_HALF_CB_ID            = 0x11U
  , HAL_TIM_IC_CAPTURE_CB_ID              = 0x12U
  , HAL_TIM_IC_CAPTURE_HALF_CB_ID         = 0x13U
  , HAL_TIM_OC_DELAY_ELAPSED_CB_ID        = 0x14U
  , HAL_TIM_PWM_PULSE_FINISHED_CB_ID      = 0x15U
  , HAL_TIM_PWM_PULSE_FINISHED_HALF_CB_ID = 0x16U
  , HAL_TIM_ERROR_CB_ID                   = 0x17U
  , HAL_TIM_COMMUTATION_CB_ID             = 0x18U
  , HAL_TIM_COMMUTATION_HALF_CB_ID        = 0x19U
  , HAL_TIM_BREAK_CB_ID                   = 0x1AU
} HAL_TIM_CallbackIDTypeDef;

typedef  void (*pTIM_CallbackTypeDef)(TIM_HandleTypeDef *htim);

#endif

#define TIM_CLEARINPUTSOURCE_NONE           0x00000000U
#define TIM_CLEARINPUTSOURCE_ETR            0x00000001U

#define TIM_DMABASE_CR1                    0x00000000U
#define TIM_DMABASE_CR2                    0x00000001U
#define TIM_DMABASE_SMCR                   0x00000002U
#define TIM_DMABASE_DIER                   0x00000003U
#define TIM_DMABASE_SR                     0x00000004U
#define TIM_DMABASE_EGR                    0x00000005U
#define TIM_DMABASE_CCMR1                  0x00000006U
#define TIM_DMABASE_CCMR2                  0x00000007U
#define TIM_DMABASE_CCER                   0x00000008U
#define TIM_DMABASE_CNT                    0x00000009U
#define TIM_DMABASE_PSC                    0x0000000AU
#define TIM_DMABASE_ARR                    0x0000000BU
#define TIM_DMABASE_RCR                    0x0000000CU
#define TIM_DMABASE_CCR1                   0x0000000DU
#define TIM_DMABASE_CCR2                   0x0000000EU
#define TIM_DMABASE_CCR3                   0x0000000FU
#define TIM_DMABASE_CCR4                   0x00000010U
#define TIM_DMABASE_BDTR                   0x00000011U
#define TIM_DMABASE_DCR                    0x00000012U
#define TIM_DMABASE_DMAR                   0x00000013U

#define TIM_EVENTSOURCE_UPDATE              TIM_EGR_UG
#define TIM_EVENTSOURCE_CC1                 TIM_EGR_CC1G
#define TIM_EVENTSOURCE_CC2                 TIM_EGR_CC2G
#define TIM_EVENTSOURCE_CC3                 TIM_EGR_CC3G
#define TIM_EVENTSOURCE_CC4                 TIM_EGR_CC4G
#define TIM_EVENTSOURCE_COM                 TIM_EGR_COMG
#define TIM_EVENTSOURCE_TRIGGER             TIM_EGR_TG
#define TIM_EVENTSOURCE_BREAK               TIM_EGR_BG

#define  TIM_INPUTCHANNELPOLARITY_RISING      0x00000000U
#define  TIM_INPUTCHANNELPOLARITY_FALLING     TIM_CCER_CC1P
#define  TIM_INPUTCHANNELPOLARITY_BOTHEDGE    (TIM_CCER_CC1P | TIM_CCER_CC1NP)

#define TIM_ETRPOLARITY_INVERTED              TIM_SMCR_ETP
#define TIM_ETRPOLARITY_NONINVERTED           0x00000000U

#define TIM_ETRPRESCALER_DIV1                 0x00000000U
#define TIM_ETRPRESCALER_DIV2                 TIM_SMCR_ETPS_0
#define TIM_ETRPRESCALER_DIV4                 TIM_SMCR_ETPS_1
#define TIM_ETRPRESCALER_DIV8                 TIM_SMCR_ETPS

#define TIM_COUNTERMODE_UP                 0x00000000U
#define TIM_COUNTERMODE_DOWN               TIM_CR1_DIR
#define TIM_COUNTERMODE_CENTERALIGNED1     TIM_CR1_CMS_0
#define TIM_COUNTERMODE_CENTERALIGNED2     TIM_CR1_CMS_1
#define TIM_COUNTERMODE_CENTERALIGNED3     TIM_CR1_CMS

#define TIM_CLOCKDIVISION_DIV1             0x00000000U
#define TIM_CLOCKDIVISION_DIV2             TIM_CR1_CKD_0
#define TIM_CLOCKDIVISION_DIV4             TIM_CR1_CKD_1

#define TIM_OUTPUTSTATE_DISABLE            0x00000000U
#define TIM_OUTPUTSTATE_ENABLE             TIM_CCER_CC1E

#define TIM_AUTORELOAD_PRELOAD_DISABLE                0x00000000U
#define TIM_AUTORELOAD_PRELOAD_ENABLE                 TIM_CR1_ARPE

#define TIM_OCFAST_DISABLE                 0x00000000U
#define TIM_OCFAST_ENABLE                  TIM_CCMR1_OC1FE

#define TIM_OUTPUTNSTATE_DISABLE           0x00000000U
#define TIM_OUTPUTNSTATE_ENABLE            TIM_CCER_CC1NE

#define TIM_OCPOLARITY_HIGH                0x00000000U
#define TIM_OCPOLARITY_LOW                 TIM_CCER_CC1P

#define TIM_OCNPOLARITY_HIGH               0x00000000U
#define TIM_OCNPOLARITY_LOW                TIM_CCER_CC1NP

#define TIM_OCIDLESTATE_SET                TIM_CR2_OIS1
#define TIM_OCIDLESTATE_RESET              0x00000000U

#define TIM_OCNIDLESTATE_SET               TIM_CR2_OIS1N
#define TIM_OCNIDLESTATE_RESET             0x00000000U

#define  TIM_ICPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define  TIM_ICPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define  TIM_ICPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE

#define  TIM_ENCODERINPUTPOLARITY_RISING   TIM_INPUTCHANNELPOLARITY_RISING
#define  TIM_ENCODERINPUTPOLARITY_FALLING  TIM_INPUTCHANNELPOLARITY_FALLING

#define TIM_ICSELECTION_DIRECTTI           TIM_CCMR1_CC1S_0
#define TIM_ICSELECTION_INDIRECTTI         TIM_CCMR1_CC1S_1
#define TIM_ICSELECTION_TRC                TIM_CCMR1_CC1S

#define TIM_ICPSC_DIV1                     0x00000000U
#define TIM_ICPSC_DIV2                     TIM_CCMR1_IC1PSC_0
#define TIM_ICPSC_DIV4                     TIM_CCMR1_IC1PSC_1
#define TIM_ICPSC_DIV8                     TIM_CCMR1_IC1PSC

#define TIM_OPMODE_SINGLE                  TIM_CR1_OPM
#define TIM_OPMODE_REPETITIVE              0x00000000U

#define TIM_ENCODERMODE_TI1                      TIM_SMCR_SMS_0
#define TIM_ENCODERMODE_TI2                      TIM_SMCR_SMS_1
#define TIM_ENCODERMODE_TI12                     (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

#define TIM_IT_UPDATE                      TIM_DIER_UIE
#define TIM_IT_CC1                         TIM_DIER_CC1IE
#define TIM_IT_CC2                         TIM_DIER_CC2IE
#define TIM_IT_CC3                         TIM_DIER_CC3IE
#define TIM_IT_CC4                         TIM_DIER_CC4IE
#define TIM_IT_COM                         TIM_DIER_COMIE
#define TIM_IT_TRIGGER                     TIM_DIER_TIE
#define TIM_IT_BREAK                       TIM_DIER_BIE

#define TIM_COMMUTATION_TRGI              TIM_CR2_CCUS
#define TIM_COMMUTATION_SOFTWARE          0x00000000U

#define TIM_DMA_UPDATE                     TIM_DIER_UDE
#define TIM_DMA_CC1                        TIM_DIER_CC1DE
#define TIM_DMA_CC2                        TIM_DIER_CC2DE
#define TIM_DMA_CC3                        TIM_DIER_CC3DE
#define TIM_DMA_CC4                        TIM_DIER_CC4DE
#define TIM_DMA_COM                        TIM_DIER_COMDE
#define TIM_DMA_TRIGGER                    TIM_DIER_TDE

#define TIM_CCDMAREQUEST_CC                 0x00000000U
#define TIM_CCDMAREQUEST_UPDATE             TIM_CR2_CCDS

#define TIM_FLAG_UPDATE                    TIM_SR_UIF
#define TIM_FLAG_CC1                       TIM_SR_CC1IF
#define TIM_FLAG_CC2                       TIM_SR_CC2IF
#define TIM_FLAG_CC3                       TIM_SR_CC3IF
#define TIM_FLAG_CC4                       TIM_SR_CC4IF
#define TIM_FLAG_COM                       TIM_SR_COMIF
#define TIM_FLAG_TRIGGER                   TIM_SR_TIF
#define TIM_FLAG_BREAK                     TIM_SR_BIF
#define TIM_FLAG_CC1OF                     TIM_SR_CC1OF
#define TIM_FLAG_CC2OF                     TIM_SR_CC2OF
#define TIM_FLAG_CC3OF                     TIM_SR_CC3OF
#define TIM_FLAG_CC4OF                     TIM_SR_CC4OF

#define TIM_CHANNEL_1                      0x00000000U
#define TIM_CHANNEL_2                      0x00000004U
#define TIM_CHANNEL_3                      0x00000008U
#define TIM_CHANNEL_4                      0x0000000CU
#define TIM_CHANNEL_ALL                    0x0000003CU

#define TIM_CLOCKSOURCE_INTERNAL    TIM_SMCR_ETPS_0
#define TIM_CLOCKSOURCE_ETRMODE1    TIM_TS_ETRF
#define TIM_CLOCKSOURCE_ETRMODE2    TIM_SMCR_ETPS_1
#define TIM_CLOCKSOURCE_TI1ED       TIM_TS_TI1F_ED
#define TIM_CLOCKSOURCE_TI1         TIM_TS_TI1FP1
#define TIM_CLOCKSOURCE_TI2         TIM_TS_TI2FP2
#define TIM_CLOCKSOURCE_ITR0        TIM_TS_ITR0
#define TIM_CLOCKSOURCE_ITR1        TIM_TS_ITR1
#define TIM_CLOCKSOURCE_ITR2        TIM_TS_ITR2
#define TIM_CLOCKSOURCE_ITR3        TIM_TS_ITR3

#define TIM_CLOCKPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_CLOCKPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED
#define TIM_CLOCKPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define TIM_CLOCKPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define TIM_CLOCKPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE

#define TIM_CLOCKPRESCALER_DIV1                 TIM_ETRPRESCALER_DIV1
#define TIM_CLOCKPRESCALER_DIV2                 TIM_ETRPRESCALER_DIV2
#define TIM_CLOCKPRESCALER_DIV4                 TIM_ETRPRESCALER_DIV4
#define TIM_CLOCKPRESCALER_DIV8                 TIM_ETRPRESCALER_DIV8

#define TIM_CLEARINPUTPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_CLEARINPUTPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED

#define TIM_CLEARINPUTPRESCALER_DIV1              TIM_ETRPRESCALER_DIV1
#define TIM_CLEARINPUTPRESCALER_DIV2              TIM_ETRPRESCALER_DIV2
#define TIM_CLEARINPUTPRESCALER_DIV4              TIM_ETRPRESCALER_DIV4
#define TIM_CLEARINPUTPRESCALER_DIV8              TIM_ETRPRESCALER_DIV8

#define TIM_OSSR_ENABLE                          TIM_BDTR_OSSR
#define TIM_OSSR_DISABLE                         0x00000000U

#define TIM_OSSI_ENABLE                          TIM_BDTR_OSSI
#define TIM_OSSI_DISABLE                         0x00000000U

#define TIM_LOCKLEVEL_OFF                  0x00000000U
#define TIM_LOCKLEVEL_1                    TIM_BDTR_LOCK_0
#define TIM_LOCKLEVEL_2                    TIM_BDTR_LOCK_1
#define TIM_LOCKLEVEL_3                    TIM_BDTR_LOCK

#define TIM_BREAK_ENABLE                   TIM_BDTR_BKE
#define TIM_BREAK_DISABLE                  0x00000000U

#define TIM_BREAKPOLARITY_LOW              0x00000000U
#define TIM_BREAKPOLARITY_HIGH             TIM_BDTR_BKP

#define TIM_AUTOMATICOUTPUT_DISABLE        0x00000000U
#define TIM_AUTOMATICOUTPUT_ENABLE         TIM_BDTR_AOE

#define TIM_TRGO_RESET            0x00000000U
#define TIM_TRGO_ENABLE           TIM_CR2_MMS_0
#define TIM_TRGO_UPDATE           TIM_CR2_MMS_1
#define TIM_TRGO_OC1              (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
#define TIM_TRGO_OC1REF           TIM_CR2_MMS_2
#define TIM_TRGO_OC2REF           (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)
#define TIM_TRGO_OC3REF           (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)
#define TIM_TRGO_OC4REF           (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)

#define TIM_MASTERSLAVEMODE_ENABLE         TIM_SMCR_MSM
#define TIM_MASTERSLAVEMODE_DISABLE        0x00000000U

#define TIM_SLAVEMODE_DISABLE                0x00000000U
#define TIM_SLAVEMODE_RESET                  TIM_SMCR_SMS_2
#define TIM_SLAVEMODE_GATED                  (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)
#define TIM_SLAVEMODE_TRIGGER                (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#define TIM_SLAVEMODE_EXTERNAL1              (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

#define TIM_OCMODE_TIMING                   0x00000000U
#define TIM_OCMODE_ACTIVE                   TIM_CCMR1_OC1M_0
#define TIM_OCMODE_INACTIVE                 TIM_CCMR1_OC1M_1
#define TIM_OCMODE_TOGGLE                   (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_PWM1                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define TIM_OCMODE_PWM2                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_FORCED_ACTIVE            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)
#define TIM_OCMODE_FORCED_INACTIVE          TIM_CCMR1_OC1M_2

#define TIM_TS_ITR0          0x00000000U
#define TIM_TS_ITR1          TIM_SMCR_TS_0
#define TIM_TS_ITR2          TIM_SMCR_TS_1
#define TIM_TS_ITR3          (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)
#define TIM_TS_TI1F_ED       TIM_SMCR_TS_2
#define TIM_TS_TI1FP1        (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)
#define TIM_TS_TI2FP2        (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)
#define TIM_TS_ETRF          (TIM_SMCR_TS_0 | TIM_SMCR_TS_1 | TIM_SMCR_TS_2)
#define TIM_TS_NONE          0x0000FFFFU

#define TIM_TRIGGERPOLARITY_INVERTED           TIM_ETRPOLARITY_INVERTED
#define TIM_TRIGGERPOLARITY_NONINVERTED        TIM_ETRPOLARITY_NONINVERTED
#define TIM_TRIGGERPOLARITY_RISING             TIM_INPUTCHANNELPOLARITY_RISING
#define TIM_TRIGGERPOLARITY_FALLING            TIM_INPUTCHANNELPOLARITY_FALLING
#define TIM_TRIGGERPOLARITY_BOTHEDGE           TIM_INPUTCHANNELPOLARITY_BOTHEDGE

#define TIM_TRIGGERPRESCALER_DIV1             TIM_ETRPRESCALER_DIV1
#define TIM_TRIGGERPRESCALER_DIV2             TIM_ETRPRESCALER_DIV2
#define TIM_TRIGGERPRESCALER_DIV4             TIM_ETRPRESCALER_DIV4
#define TIM_TRIGGERPRESCALER_DIV8             TIM_ETRPRESCALER_DIV8

#define TIM_TI1SELECTION_CH1               0x00000000U
#define TIM_TI1SELECTION_XORCOMBINATION    TIM_CR2_TI1S

#define TIM_DMABURSTLENGTH_1TRANSFER       0x00000000U
#define TIM_DMABURSTLENGTH_2TRANSFERS      0x00000100U
#define TIM_DMABURSTLENGTH_3TRANSFERS      0x00000200U
#define TIM_DMABURSTLENGTH_4TRANSFERS      0x00000300U
#define TIM_DMABURSTLENGTH_5TRANSFERS      0x00000400U
#define TIM_DMABURSTLENGTH_6TRANSFERS      0x00000500U
#define TIM_DMABURSTLENGTH_7TRANSFERS      0x00000600U
#define TIM_DMABURSTLENGTH_8TRANSFERS      0x00000700U
#define TIM_DMABURSTLENGTH_9TRANSFERS      0x00000800U
#define TIM_DMABURSTLENGTH_10TRANSFERS     0x00000900U
#define TIM_DMABURSTLENGTH_11TRANSFERS     0x00000A00U
#define TIM_DMABURSTLENGTH_12TRANSFERS     0x00000B00U
#define TIM_DMABURSTLENGTH_13TRANSFERS     0x00000C00U
#define TIM_DMABURSTLENGTH_14TRANSFERS     0x00000D00U
#define TIM_DMABURSTLENGTH_15TRANSFERS     0x00000E00U
#define TIM_DMABURSTLENGTH_16TRANSFERS     0x00000F00U
#define TIM_DMABURSTLENGTH_17TRANSFERS     0x00001000U
#define TIM_DMABURSTLENGTH_18TRANSFERS     0x00001100U

#define TIM_DMA_ID_UPDATE                ((uint16_t) 0x0000)
#define TIM_DMA_ID_CC1                   ((uint16_t) 0x0001)
#define TIM_DMA_ID_CC2                   ((uint16_t) 0x0002)
#define TIM_DMA_ID_CC3                   ((uint16_t) 0x0003)
#define TIM_DMA_ID_CC4                   ((uint16_t) 0x0004)
#define TIM_DMA_ID_COMMUTATION           ((uint16_t) 0x0005)
#define TIM_DMA_ID_TRIGGER               ((uint16_t) 0x0006)

#define TIM_CCx_ENABLE                   0x00000001U
#define TIM_CCx_DISABLE                  0x00000000U
#define TIM_CCxN_ENABLE                  0x00000004U
#define TIM_CCxN_DISABLE                 0x00000000U

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) do {                                                               \
                                                      (__HANDLE__)->State            = HAL_TIM_STATE_RESET;         \
                                                      (__HANDLE__)->ChannelState[0]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[1]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[2]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[3]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[0] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[1] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[2] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[3] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->DMABurstState    = HAL_DMA_BURST_STATE_RESET;   \
                                                      (__HANDLE__)->Base_MspInitCallback         = NULL;            \
                                                      (__HANDLE__)->Base_MspDeInitCallback       = NULL;            \
                                                      (__HANDLE__)->IC_MspInitCallback           = NULL;            \
                                                      (__HANDLE__)->IC_MspDeInitCallback         = NULL;            \
                                                      (__HANDLE__)->OC_MspInitCallback           = NULL;            \
                                                      (__HANDLE__)->OC_MspDeInitCallback         = NULL;            \
                                                      (__HANDLE__)->PWM_MspInitCallback          = NULL;            \
                                                      (__HANDLE__)->PWM_MspDeInitCallback        = NULL;            \
                                                      (__HANDLE__)->OnePulse_MspInitCallback     = NULL;            \
                                                      (__HANDLE__)->OnePulse_MspDeInitCallback   = NULL;            \
                                                      (__HANDLE__)->Encoder_MspInitCallback      = NULL;            \
                                                      (__HANDLE__)->Encoder_MspDeInitCallback    = NULL;            \
                                                      (__HANDLE__)->HallSensor_MspInitCallback   = NULL;            \
                                                      (__HANDLE__)->HallSensor_MspDeInitCallback = NULL;            \
                                                     } while(0)
#else
#define __HAL_TIM_RESET_HANDLE_STATE(__HANDLE__) do {                                                               \
                                                      (__HANDLE__)->State            = HAL_TIM_STATE_RESET;         \
                                                      (__HANDLE__)->ChannelState[0]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[1]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[2]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelState[3]  = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[0] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[1] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[2] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->ChannelNState[3] = HAL_TIM_CHANNEL_STATE_RESET; \
                                                      (__HANDLE__)->DMABurstState    = HAL_DMA_BURST_STATE_RESET;   \
                                                     } while(0)
#endif

#define __HAL_TIM_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR1|=(TIM_CR1_CEN))

#define __HAL_TIM_MOE_ENABLE(__HANDLE__)             ((__HANDLE__)->Instance->BDTR|=(TIM_BDTR_MOE))

#define __HAL_TIM_DISABLE(__HANDLE__) \
  do { \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL) \
    { \
      if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      { \
        (__HANDLE__)->Instance->CR1 &= ~(TIM_CR1_CEN); \
      } \
    } \
  } while(0)

#define __HAL_TIM_MOE_DISABLE(__HANDLE__) \
  do { \
    if (((__HANDLE__)->Instance->CCER & TIM_CCER_CCxE_MASK) == 0UL) \
    { \
      if(((__HANDLE__)->Instance->CCER & TIM_CCER_CCxNE_MASK) == 0UL) \
      { \
        (__HANDLE__)->Instance->BDTR &= ~(TIM_BDTR_MOE); \
      } \
    } \
  } while(0)

#define __HAL_TIM_MOE_DISABLE_UNCONDITIONALLY(__HANDLE__)  (__HANDLE__)->Instance->BDTR &= ~(TIM_BDTR_MOE)

#define __HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))

#define __HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__))

#define __HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA__)         ((__HANDLE__)->Instance->DIER |= (__DMA__))

#define __HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA__)        ((__HANDLE__)->Instance->DIER &= ~(__DMA__))

#define __HAL_TIM_GET_FLAG(__HANDLE__, __FLAG__)          (((__HANDLE__)->Instance->SR &(__FLAG__)) == (__FLAG__))

#define __HAL_TIM_CLEAR_FLAG(__HANDLE__, __FLAG__)        ((__HANDLE__)->Instance->SR = ~(__FLAG__))

#define __HAL_TIM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->DIER & (__INTERRUPT__)) \
                                                             == (__INTERRUPT__)) ? SET : RESET)

#define __HAL_TIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)      ((__HANDLE__)->Instance->SR = ~(__INTERRUPT__))

#define __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__)    (((__HANDLE__)->Instance->CR1 &(TIM_CR1_DIR)) == (TIM_CR1_DIR))

#define __HAL_TIM_SET_PRESCALER(__HANDLE__, __PRESC__)       ((__HANDLE__)->Instance->PSC = (__PRESC__))

#define __HAL_TIM_SET_COUNTER(__HANDLE__, __COUNTER__)  ((__HANDLE__)->Instance->CNT = (__COUNTER__))

#define __HAL_TIM_GET_COUNTER(__HANDLE__)  ((__HANDLE__)->Instance->CNT)

#define __HAL_TIM_SET_AUTORELOAD(__HANDLE__, __AUTORELOAD__) \
  do{                                                    \
    (__HANDLE__)->Instance->ARR = (__AUTORELOAD__);  \
    (__HANDLE__)->Init.Period = (__AUTORELOAD__);    \
  } while(0)

#define __HAL_TIM_GET_AUTORELOAD(__HANDLE__)  ((__HANDLE__)->Instance->ARR)

#define __HAL_TIM_SET_CLOCKDIVISION(__HANDLE__, __CKD__) \
  do{                                                   \
    (__HANDLE__)->Instance->CR1 &= (~TIM_CR1_CKD);  \
    (__HANDLE__)->Instance->CR1 |= (__CKD__);       \
    (__HANDLE__)->Init.ClockDivision = (__CKD__);   \
  } while(0)

#define __HAL_TIM_GET_CLOCKDIVISION(__HANDLE__)  ((__HANDLE__)->Instance->CR1 & TIM_CR1_CKD)

#define __HAL_TIM_SET_ICPRESCALER(__HANDLE__, __CHANNEL__, __ICPSC__) \
  do{                                                    \
    TIM_RESET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__));  \
    TIM_SET_ICPRESCALERVALUE((__HANDLE__), (__CHANNEL__), (__ICPSC__)); \
  } while(0)

#define __HAL_TIM_GET_ICPRESCALER(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (((__HANDLE__)->Instance->CCMR1 & TIM_CCMR1_IC2PSC) >> 8U) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC3PSC) :\
   (((__HANDLE__)->Instance->CCMR2 & TIM_CCMR2_IC4PSC)) >> 8U)

#define __HAL_TIM_SET_COMPARE(__HANDLE__, __CHANNEL__, __COMPARE__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1 = (__COMPARE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2 = (__COMPARE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3 = (__COMPARE__)) :\
   ((__HANDLE__)->Instance->CCR4 = (__COMPARE__)))

#define __HAL_TIM_GET_COMPARE(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCR1) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCR2) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCR3) :\
   ((__HANDLE__)->Instance->CCR4))

#define __HAL_TIM_ENABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIM_CCMR1_OC1PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIM_CCMR1_OC2PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= TIM_CCMR2_OC3PE) :\
   ((__HANDLE__)->Instance->CCMR2 |= TIM_CCMR2_OC4PE))

#define __HAL_TIM_DISABLE_OCxPRELOAD(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_OC1PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_OC2PE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_OC3PE) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_OC4PE))

#define __HAL_TIM_ENABLE_OCxFAST(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= TIM_CCMR1_OC1FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= TIM_CCMR1_OC2FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= TIM_CCMR2_OC3FE) :\
   ((__HANDLE__)->Instance->CCMR2 |= TIM_CCMR2_OC4FE))

#define __HAL_TIM_DISABLE_OCxFAST(__HANDLE__, __CHANNEL__)    \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_OC1FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_OC2FE) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_OC3FE) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_OC4FE))

#define __HAL_TIM_URS_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR1|= TIM_CR1_URS)

#define __HAL_TIM_URS_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR1&=~TIM_CR1_URS)

#define __HAL_TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__)    \
  do{                                                                     \
    TIM_RESET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__));               \
    TIM_SET_CAPTUREPOLARITY((__HANDLE__), (__CHANNEL__), (__POLARITY__)); \
  }while(0)

#define __HAL_TIM_SELECT_CCDMAREQUEST(__HANDLE__, __CCDMA__)    \
  MODIFY_REG((__HANDLE__)->Instance->CR2, TIM_CR2_CCDS, (__CCDMA__))

#define TIM_CCER_CCxE_MASK  ((uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E))
#define TIM_CCER_CCxNE_MASK ((uint32_t)(TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE))

#define IS_TIM_CLEARINPUT_SOURCE(__MODE__)  (((__MODE__) == TIM_CLEARINPUTSOURCE_NONE)      || \
                                             ((__MODE__) == TIM_CLEARINPUTSOURCE_ETR))

#define IS_TIM_DMA_BASE(__BASE__) (((__BASE__) == TIM_DMABASE_CR1)   || \
                                   ((__BASE__) == TIM_DMABASE_CR2)   || \
                                   ((__BASE__) == TIM_DMABASE_SMCR)  || \
                                   ((__BASE__) == TIM_DMABASE_DIER)  || \
                                   ((__BASE__) == TIM_DMABASE_SR)    || \
                                   ((__BASE__) == TIM_DMABASE_EGR)   || \
                                   ((__BASE__) == TIM_DMABASE_CCMR1) || \
                                   ((__BASE__) == TIM_DMABASE_CCMR2) || \
                                   ((__BASE__) == TIM_DMABASE_CCER)  || \
                                   ((__BASE__) == TIM_DMABASE_CNT)   || \
                                   ((__BASE__) == TIM_DMABASE_PSC)   || \
                                   ((__BASE__) == TIM_DMABASE_ARR)   || \
                                   ((__BASE__) == TIM_DMABASE_RCR)   || \
                                   ((__BASE__) == TIM_DMABASE_CCR1)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR2)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR3)  || \
                                   ((__BASE__) == TIM_DMABASE_CCR4)  || \
                                   ((__BASE__) == TIM_DMABASE_BDTR))

#define IS_TIM_EVENT_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFFFF00U) == 0x00000000U) && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_COUNTER_MODE(__MODE__)      (((__MODE__) == TIM_COUNTERMODE_UP)              || \
                                            ((__MODE__) == TIM_COUNTERMODE_DOWN)            || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED1)  || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED2)  || \
                                            ((__MODE__) == TIM_COUNTERMODE_CENTERALIGNED3))

#define IS_TIM_CLOCKDIVISION_DIV(__DIV__)  (((__DIV__) == TIM_CLOCKDIVISION_DIV1) || \
                                            ((__DIV__) == TIM_CLOCKDIVISION_DIV2) || \
                                            ((__DIV__) == TIM_CLOCKDIVISION_DIV4))

#define IS_TIM_AUTORELOAD_PRELOAD(PRELOAD) (((PRELOAD) == TIM_AUTORELOAD_PRELOAD_DISABLE) || \
                                            ((PRELOAD) == TIM_AUTORELOAD_PRELOAD_ENABLE))

#define IS_TIM_FAST_STATE(__STATE__)       (((__STATE__) == TIM_OCFAST_DISABLE) || \
                                            ((__STATE__) == TIM_OCFAST_ENABLE))

#define IS_TIM_OC_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_OCPOLARITY_HIGH) || \
                                            ((__POLARITY__) == TIM_OCPOLARITY_LOW))

#define IS_TIM_OCN_POLARITY(__POLARITY__)  (((__POLARITY__) == TIM_OCNPOLARITY_HIGH) || \
                                            ((__POLARITY__) == TIM_OCNPOLARITY_LOW))

#define IS_TIM_OCIDLE_STATE(__STATE__)     (((__STATE__) == TIM_OCIDLESTATE_SET) || \
                                            ((__STATE__) == TIM_OCIDLESTATE_RESET))

#define IS_TIM_OCNIDLE_STATE(__STATE__)    (((__STATE__) == TIM_OCNIDLESTATE_SET) || \
                                            ((__STATE__) == TIM_OCNIDLESTATE_RESET))

#define IS_TIM_ENCODERINPUT_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_ENCODERINPUTPOLARITY_RISING)   || \
                                                      ((__POLARITY__) == TIM_ENCODERINPUTPOLARITY_FALLING))

#define IS_TIM_IC_POLARITY(__POLARITY__)   (((__POLARITY__) == TIM_ICPOLARITY_RISING)   || \
                                            ((__POLARITY__) == TIM_ICPOLARITY_FALLING)  || \
                                            ((__POLARITY__) == TIM_ICPOLARITY_BOTHEDGE))

#define IS_TIM_IC_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_ICSELECTION_DIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_INDIRECTTI) || \
                                            ((__SELECTION__) == TIM_ICSELECTION_TRC))

#define IS_TIM_IC_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_ICPSC_DIV1) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV2) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV4) || \
                                            ((__PRESCALER__) == TIM_ICPSC_DIV8))

#define IS_TIM_OPM_MODE(__MODE__)          (((__MODE__) == TIM_OPMODE_SINGLE) || \
                                            ((__MODE__) == TIM_OPMODE_REPETITIVE))

#define IS_TIM_ENCODER_MODE(__MODE__)      (((__MODE__) == TIM_ENCODERMODE_TI1) || \
                                            ((__MODE__) == TIM_ENCODERMODE_TI2) || \
                                            ((__MODE__) == TIM_ENCODERMODE_TI12))

#define IS_TIM_DMA_SOURCE(__SOURCE__) ((((__SOURCE__) & 0xFFFF80FFU) == 0x00000000U) && ((__SOURCE__) != 0x00000000U))

#define IS_TIM_CHANNELS(__CHANNEL__)       (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_2) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_3) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_4) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_ALL))

#define IS_TIM_OPM_CHANNELS(__CHANNEL__)   (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                            ((__CHANNEL__) == TIM_CHANNEL_2))

#define IS_TIM_PERIOD(__HANDLE__, __PERIOD__) ((IS_TIM_32B_COUNTER_INSTANCE(((__HANDLE__)->Instance)) == 0U) ? \
                                               (((__PERIOD__) > 0U) && ((__PERIOD__) <= 0x0000FFFFU)) :        \
                                               ((__PERIOD__) > 0U))

#define IS_TIM_COMPLEMENTARY_CHANNELS(__CHANNEL__) (((__CHANNEL__) == TIM_CHANNEL_1) || \
                                                    ((__CHANNEL__) == TIM_CHANNEL_2) || \
                                                    ((__CHANNEL__) == TIM_CHANNEL_3))

#define IS_TIM_CLOCKSOURCE(__CLOCK__) (((__CLOCK__) == TIM_CLOCKSOURCE_INTERNAL) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE1) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ETRMODE2) || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1ED)    || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI1)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_TI2)      || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR0)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR1)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR2)     || \
                                       ((__CLOCK__) == TIM_CLOCKSOURCE_ITR3))

#define IS_TIM_CLOCKPOLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLOCKPOLARITY_INVERTED)    || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_NONINVERTED) || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_RISING)      || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_FALLING)     || \
                                            ((__POLARITY__) == TIM_CLOCKPOLARITY_BOTHEDGE))

#define IS_TIM_CLOCKPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV1) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV2) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV4) || \
                                              ((__PRESCALER__) == TIM_CLOCKPRESCALER_DIV8))

#define IS_TIM_CLOCKFILTER(__ICFILTER__)      ((__ICFILTER__) <= 0xFU)

#define IS_TIM_CLEARINPUT_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_CLEARINPUTPOLARITY_INVERTED) || \
                                                  ((__POLARITY__) == TIM_CLEARINPUTPOLARITY_NONINVERTED))

#define IS_TIM_CLEARINPUT_PRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV1) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV2) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV4) || \
                                                    ((__PRESCALER__) == TIM_CLEARINPUTPRESCALER_DIV8))

#define IS_TIM_CLEARINPUT_FILTER(__ICFILTER__) ((__ICFILTER__) <= 0xFU)

#define IS_TIM_OSSR_STATE(__STATE__)       (((__STATE__) == TIM_OSSR_ENABLE) || \
                                            ((__STATE__) == TIM_OSSR_DISABLE))

#define IS_TIM_OSSI_STATE(__STATE__)       (((__STATE__) == TIM_OSSI_ENABLE) || \
                                            ((__STATE__) == TIM_OSSI_DISABLE))

#define IS_TIM_LOCK_LEVEL(__LEVEL__)       (((__LEVEL__) == TIM_LOCKLEVEL_OFF) || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_1)   || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_2)   || \
                                            ((__LEVEL__) == TIM_LOCKLEVEL_3))

#define IS_TIM_BREAK_FILTER(__BRKFILTER__) ((__BRKFILTER__) <= 0xFUL)

#define IS_TIM_BREAK_STATE(__STATE__)      (((__STATE__) == TIM_BREAK_ENABLE) || \
                                            ((__STATE__) == TIM_BREAK_DISABLE))

#define IS_TIM_BREAK_POLARITY(__POLARITY__) (((__POLARITY__) == TIM_BREAKPOLARITY_LOW) || \
                                             ((__POLARITY__) == TIM_BREAKPOLARITY_HIGH))

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(__STATE__) (((__STATE__) == TIM_AUTOMATICOUTPUT_ENABLE) || \
                                                  ((__STATE__) == TIM_AUTOMATICOUTPUT_DISABLE))

#define IS_TIM_TRGO_SOURCE(__SOURCE__) (((__SOURCE__) == TIM_TRGO_RESET)  || \
                                        ((__SOURCE__) == TIM_TRGO_ENABLE) || \
                                        ((__SOURCE__) == TIM_TRGO_UPDATE) || \
                                        ((__SOURCE__) == TIM_TRGO_OC1)    || \
                                        ((__SOURCE__) == TIM_TRGO_OC1REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC2REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC3REF) || \
                                        ((__SOURCE__) == TIM_TRGO_OC4REF))

#define IS_TIM_MSM_STATE(__STATE__)      (((__STATE__) == TIM_MASTERSLAVEMODE_ENABLE) || \
                                          ((__STATE__) == TIM_MASTERSLAVEMODE_DISABLE))

#define IS_TIM_SLAVE_MODE(__MODE__) (((__MODE__) == TIM_SLAVEMODE_DISABLE)   || \
                                     ((__MODE__) == TIM_SLAVEMODE_RESET)     || \
                                     ((__MODE__) == TIM_SLAVEMODE_GATED)     || \
                                     ((__MODE__) == TIM_SLAVEMODE_TRIGGER)   || \
                                     ((__MODE__) == TIM_SLAVEMODE_EXTERNAL1))

#define IS_TIM_PWM_MODE(__MODE__) (((__MODE__) == TIM_OCMODE_PWM1)               || \
                                   ((__MODE__) == TIM_OCMODE_PWM2))

#define IS_TIM_OC_MODE(__MODE__)  (((__MODE__) == TIM_OCMODE_TIMING)             || \
                                   ((__MODE__) == TIM_OCMODE_ACTIVE)             || \
                                   ((__MODE__) == TIM_OCMODE_INACTIVE)           || \
                                   ((__MODE__) == TIM_OCMODE_TOGGLE)             || \
                                   ((__MODE__) == TIM_OCMODE_FORCED_ACTIVE)      || \
                                   ((__MODE__) == TIM_OCMODE_FORCED_INACTIVE))

#define IS_TIM_TRIGGER_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0)    || \
                                                 ((__SELECTION__) == TIM_TS_ITR1)    || \
                                                 ((__SELECTION__) == TIM_TS_ITR2)    || \
                                                 ((__SELECTION__) == TIM_TS_ITR3)    || \
                                                 ((__SELECTION__) == TIM_TS_TI1F_ED) || \
                                                 ((__SELECTION__) == TIM_TS_TI1FP1)  || \
                                                 ((__SELECTION__) == TIM_TS_TI2FP2)  || \
                                                 ((__SELECTION__) == TIM_TS_ETRF))

#define IS_TIM_INTERNAL_TRIGGEREVENT_SELECTION(__SELECTION__) (((__SELECTION__) == TIM_TS_ITR0) || \
                                                               ((__SELECTION__) == TIM_TS_ITR1) || \
                                                               ((__SELECTION__) == TIM_TS_ITR2) || \
                                                               ((__SELECTION__) == TIM_TS_ITR3) || \
                                                               ((__SELECTION__) == TIM_TS_NONE))

#define IS_TIM_TRIGGERPOLARITY(__POLARITY__)   (((__POLARITY__) == TIM_TRIGGERPOLARITY_INVERTED   ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_NONINVERTED) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_RISING     ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_FALLING    ) || \
                                                ((__POLARITY__) == TIM_TRIGGERPOLARITY_BOTHEDGE   ))

#define IS_TIM_TRIGGERPRESCALER(__PRESCALER__) (((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV1) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV2) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV4) || \
                                                ((__PRESCALER__) == TIM_TRIGGERPRESCALER_DIV8))

#define IS_TIM_TRIGGERFILTER(__ICFILTER__) ((__ICFILTER__) <= 0xFU)

#define IS_TIM_TI1SELECTION(__TI1SELECTION__)  (((__TI1SELECTION__) == TIM_TI1SELECTION_CH1) || \
                                                ((__TI1SELECTION__) == TIM_TI1SELECTION_XORCOMBINATION))

#define IS_TIM_DMA_LENGTH(__LENGTH__)      (((__LENGTH__) == TIM_DMABURSTLENGTH_1TRANSFER)   || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_2TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_3TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_4TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_5TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_6TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_7TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_8TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_9TRANSFERS)  || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_10TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_11TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_12TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_13TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_14TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_15TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_16TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_17TRANSFERS) || \
                                            ((__LENGTH__) == TIM_DMABURSTLENGTH_18TRANSFERS))

#define IS_TIM_DMA_DATA_LENGTH(LENGTH) (((LENGTH) >= 0x1U) && ((LENGTH) < 0x10000U))

#define IS_TIM_IC_FILTER(__ICFILTER__)   ((__ICFILTER__) <= 0xFU)

#define IS_TIM_DEADTIME(__DEADTIME__)    ((__DEADTIME__) <= 0xFFU)

#define IS_TIM_SLAVEMODE_TRIGGER_ENABLED(__TRIGGER__) ((__TRIGGER__) == TIM_SLAVEMODE_TRIGGER)

#define TIM_SET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__, __ICPSC__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 |= (__ICPSC__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 |= ((__ICPSC__) << 8U)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 |= (__ICPSC__)) :\
   ((__HANDLE__)->Instance->CCMR2 |= ((__ICPSC__) << 8U)))

#define TIM_RESET_ICPRESCALERVALUE(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_IC1PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCMR1 &= ~TIM_CCMR1_IC2PSC) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_IC3PSC) :\
   ((__HANDLE__)->Instance->CCMR2 &= ~TIM_CCMR2_IC4PSC))

#define TIM_SET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__, __POLARITY__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER |= (__POLARITY__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 4U)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER |= ((__POLARITY__) << 8U)) :\
   ((__HANDLE__)->Instance->CCER |= (((__POLARITY__) << 12U))))

#define TIM_RESET_CAPTUREPOLARITY(__HANDLE__, __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC3NP)) :\
   ((__HANDLE__)->Instance->CCER &= ~(TIM_CCER_CC4P | TIM_CCER_CC4NP)))

#define TIM_CHANNEL_STATE_GET(__HANDLE__, __CHANNEL__)\
  (((__CHANNEL__) == TIM_CHANNEL_1) ? (__HANDLE__)->ChannelState[0] :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (__HANDLE__)->ChannelState[1] :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? (__HANDLE__)->ChannelState[2] :\
   (__HANDLE__)->ChannelState[3])

#define TIM_CHANNEL_STATE_SET(__HANDLE__, __CHANNEL__, __CHANNEL_STATE__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->ChannelState[0] = (__CHANNEL_STATE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->ChannelState[1] = (__CHANNEL_STATE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->ChannelState[2] = (__CHANNEL_STATE__)) :\
   ((__HANDLE__)->ChannelState[3] = (__CHANNEL_STATE__)))

#define TIM_CHANNEL_STATE_SET_ALL(__HANDLE__,  __CHANNEL_STATE__)\
  do {\
    (__HANDLE__)->ChannelState[0]  = (__CHANNEL_STATE__);\
    (__HANDLE__)->ChannelState[1]  = (__CHANNEL_STATE__);\
    (__HANDLE__)->ChannelState[2]  = (__CHANNEL_STATE__);\
    (__HANDLE__)->ChannelState[3]  = (__CHANNEL_STATE__);\
  } while(0)

#define TIM_CHANNEL_N_STATE_GET(__HANDLE__, __CHANNEL__)\
  (((__CHANNEL__) == TIM_CHANNEL_1) ? (__HANDLE__)->ChannelNState[0] :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? (__HANDLE__)->ChannelNState[1] :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? (__HANDLE__)->ChannelNState[2] :\
   (__HANDLE__)->ChannelNState[3])

#define TIM_CHANNEL_N_STATE_SET(__HANDLE__, __CHANNEL__, __CHANNEL_STATE__) \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->ChannelNState[0] = (__CHANNEL_STATE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->ChannelNState[1] = (__CHANNEL_STATE__)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->ChannelNState[2] = (__CHANNEL_STATE__)) :\
   ((__HANDLE__)->ChannelNState[3] = (__CHANNEL_STATE__)))

#define TIM_CHANNEL_N_STATE_SET_ALL(__HANDLE__,  __CHANNEL_STATE__)\
  do {\
    (__HANDLE__)->ChannelNState[0] = \
    (__CHANNEL_STATE__);  \
    (__HANDLE__)->ChannelNState[1] = \
    (__CHANNEL_STATE__);  \
    (__HANDLE__)->ChannelNState[2] = \
    (__CHANNEL_STATE__);  \
    (__HANDLE__)->ChannelNState[3] = \
    (__CHANNEL_STATE__);  \
  } while(0)

#include "stm32f4xx_hal_tim_ex.h"

HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                       uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                        uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim, const TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                            uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_IC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           const TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, const TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, const uint32_t  *BurstBuffer,
                                              uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiWriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                   uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                                   uint32_t BurstLength,  uint32_t DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                  uint32_t BurstRequestSrc, uint32_t  *BurstBuffer,
                                                  uint32_t  BurstLength, uint32_t  DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(const TIM_HandleTypeDef *htim, uint32_t Channel);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_TIM_RegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID,
                                           pTIM_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_TIM_UnRegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID);
#endif

HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(const TIM_HandleTypeDef *htim);

HAL_TIM_ActiveChannel HAL_TIM_GetActiveChannel(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIM_GetChannelState(const TIM_HandleTypeDef *htim,  uint32_t Channel);
HAL_TIM_DMABurstStateTypeDef HAL_TIM_DMABurstState(const TIM_HandleTypeDef *htim);

void TIM_Base_SetConfig(TIM_TypeDef *TIMx, const TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
void TIM_ResetCallback(TIM_HandleTypeDef *htim);
#endif

#ifdef __cplusplus
}
#endif

#endif
