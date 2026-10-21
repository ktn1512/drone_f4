#ifndef __STM32F4xx_LL_TIM_H
#define __STM32F4xx_LL_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (TIM1) || defined (TIM2) || defined (TIM3) || defined (TIM4) || defined (TIM5) || defined (TIM6) || defined (TIM7) || defined (TIM8) || defined (TIM9) || defined (TIM10) || defined (TIM11) || defined (TIM12) || defined (TIM13) || defined (TIM14)

static const uint8_t OFFSET_TAB_CCMRx[] =
{
  0x00U,
  0x00U,
  0x00U,
  0x00U,
  0x04U,
  0x04U,
  0x04U
};

static const uint8_t SHIFT_TAB_OCxx[] =
{
  0U,
  0U,
  8U,
  0U,
  0U,
  0U,
  8U
};

static const uint8_t SHIFT_TAB_ICxx[] =
{
  0U,
  0U,
  8U,
  0U,
  0U,
  0U,
  8U
};

static const uint8_t SHIFT_TAB_CCxP[] =
{
  0U,
  2U,
  4U,
  6U,
  8U,
  10U,
  12U
};

static const uint8_t SHIFT_TAB_OISx[] =
{
  0U,
  1U,
  2U,
  3U,
  4U,
  5U,
  6U
};

#define TIMx_OR_RMP_SHIFT  16U
#define TIMx_OR_RMP_MASK   0x0000FFFFU
#define TIM2_OR_RMP_MASK   (TIM_OR_ITR1_RMP << TIMx_OR_RMP_SHIFT)
#define TIM5_OR_RMP_MASK   (TIM_OR_TI4_RMP << TIMx_OR_RMP_SHIFT)
#define TIM11_OR_RMP_MASK  (TIM_OR_TI1_RMP << TIMx_OR_RMP_SHIFT)

#define DT_DELAY_1 ((uint8_t)0x7F)
#define DT_DELAY_2 ((uint8_t)0x3F)
#define DT_DELAY_3 ((uint8_t)0x1F)
#define DT_DELAY_4 ((uint8_t)0x1F)

#define DT_RANGE_1 ((uint8_t)0x00)
#define DT_RANGE_2 ((uint8_t)0x80)
#define DT_RANGE_3 ((uint8_t)0xC0)
#define DT_RANGE_4 ((uint8_t)0xE0)

#define TIM_GET_CHANNEL_INDEX( __CHANNEL__) \
  (((__CHANNEL__) == LL_TIM_CHANNEL_CH1) ? 0U :\
   ((__CHANNEL__) == LL_TIM_CHANNEL_CH1N) ? 1U :\
   ((__CHANNEL__) == LL_TIM_CHANNEL_CH2) ? 2U :\
   ((__CHANNEL__) == LL_TIM_CHANNEL_CH2N) ? 3U :\
   ((__CHANNEL__) == LL_TIM_CHANNEL_CH3) ? 4U :\
   ((__CHANNEL__) == LL_TIM_CHANNEL_CH3N) ? 5U : 6U)

#define TIM_CALC_DTS(__TIMCLK__, __CKD__)                                                        \
  (((__CKD__) == LL_TIM_CLOCKDIVISION_DIV1) ? ((uint64_t)1000000000000U/(__TIMCLK__))         : \
   ((__CKD__) == LL_TIM_CLOCKDIVISION_DIV2) ? ((uint64_t)1000000000000U/((__TIMCLK__) >> 1U)) : \
   ((uint64_t)1000000000000U/((__TIMCLK__) >> 2U)))

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint16_t Prescaler;

  uint32_t CounterMode;

  uint32_t Autoreload;

  uint32_t ClockDivision;

  uint32_t RepetitionCounter;
} LL_TIM_InitTypeDef;

typedef struct
{
  uint32_t OCMode;

  uint32_t OCState;

  uint32_t OCNState;

  uint32_t CompareValue;

  uint32_t OCPolarity;

  uint32_t OCNPolarity;

  uint32_t OCIdleState;

  uint32_t OCNIdleState;
} LL_TIM_OC_InitTypeDef;

typedef struct
{

  uint32_t ICPolarity;

  uint32_t ICActiveInput;

  uint32_t ICPrescaler;

  uint32_t ICFilter;
} LL_TIM_IC_InitTypeDef;

typedef struct
{
  uint32_t EncoderMode;

  uint32_t IC1Polarity;

  uint32_t IC1ActiveInput;

  uint32_t IC1Prescaler;

  uint32_t IC1Filter;

  uint32_t IC2Polarity;

  uint32_t IC2ActiveInput;

  uint32_t IC2Prescaler;

  uint32_t IC2Filter;

} LL_TIM_ENCODER_InitTypeDef;

typedef struct
{

  uint32_t IC1Polarity;

  uint32_t IC1Prescaler;

  uint32_t IC1Filter;

  uint32_t CommutationDelay;
} LL_TIM_HALLSENSOR_InitTypeDef;

typedef struct
{
  uint32_t OSSRState;

  uint32_t OSSIState;

  uint32_t LockLevel;

  uint8_t DeadTime;

  uint16_t BreakState;

  uint32_t BreakPolarity;

  uint32_t AutomaticOutput;
} LL_TIM_BDTR_InitTypeDef;

#endif

#define LL_TIM_SR_UIF                          TIM_SR_UIF
#define LL_TIM_SR_CC1IF                        TIM_SR_CC1IF
#define LL_TIM_SR_CC2IF                        TIM_SR_CC2IF
#define LL_TIM_SR_CC3IF                        TIM_SR_CC3IF
#define LL_TIM_SR_CC4IF                        TIM_SR_CC4IF
#define LL_TIM_SR_COMIF                        TIM_SR_COMIF
#define LL_TIM_SR_TIF                          TIM_SR_TIF
#define LL_TIM_SR_BIF                          TIM_SR_BIF
#define LL_TIM_SR_CC1OF                        TIM_SR_CC1OF
#define LL_TIM_SR_CC2OF                        TIM_SR_CC2OF
#define LL_TIM_SR_CC3OF                        TIM_SR_CC3OF
#define LL_TIM_SR_CC4OF                        TIM_SR_CC4OF

#if defined(USE_FULL_LL_DRIVER)

#define LL_TIM_BREAK_DISABLE            0x00000000U
#define LL_TIM_BREAK_ENABLE             TIM_BDTR_BKE

#define LL_TIM_AUTOMATICOUTPUT_DISABLE         0x00000000U
#define LL_TIM_AUTOMATICOUTPUT_ENABLE          TIM_BDTR_AOE

#endif

#define LL_TIM_DIER_UIE                        TIM_DIER_UIE
#define LL_TIM_DIER_CC1IE                      TIM_DIER_CC1IE
#define LL_TIM_DIER_CC2IE                      TIM_DIER_CC2IE
#define LL_TIM_DIER_CC3IE                      TIM_DIER_CC3IE
#define LL_TIM_DIER_CC4IE                      TIM_DIER_CC4IE
#define LL_TIM_DIER_COMIE                      TIM_DIER_COMIE
#define LL_TIM_DIER_TIE                        TIM_DIER_TIE
#define LL_TIM_DIER_BIE                        TIM_DIER_BIE

#define LL_TIM_UPDATESOURCE_REGULAR            0x00000000U
#define LL_TIM_UPDATESOURCE_COUNTER            TIM_CR1_URS

#define LL_TIM_ONEPULSEMODE_SINGLE             TIM_CR1_OPM
#define LL_TIM_ONEPULSEMODE_REPETITIVE         0x00000000U

#define LL_TIM_COUNTERMODE_UP                  0x00000000U
#define LL_TIM_COUNTERMODE_DOWN                TIM_CR1_DIR
#define LL_TIM_COUNTERMODE_CENTER_DOWN         TIM_CR1_CMS_0
#define LL_TIM_COUNTERMODE_CENTER_UP           TIM_CR1_CMS_1
#define LL_TIM_COUNTERMODE_CENTER_UP_DOWN      TIM_CR1_CMS

#define LL_TIM_CLOCKDIVISION_DIV1              0x00000000U
#define LL_TIM_CLOCKDIVISION_DIV2              TIM_CR1_CKD_0
#define LL_TIM_CLOCKDIVISION_DIV4              TIM_CR1_CKD_1

#define LL_TIM_COUNTERDIRECTION_UP             0x00000000U
#define LL_TIM_COUNTERDIRECTION_DOWN           TIM_CR1_DIR

#define LL_TIM_CCUPDATESOURCE_COMG_ONLY        0x00000000U
#define LL_TIM_CCUPDATESOURCE_COMG_AND_TRGI    TIM_CR2_CCUS

#define LL_TIM_CCDMAREQUEST_CC                 0x00000000U
#define LL_TIM_CCDMAREQUEST_UPDATE             TIM_CR2_CCDS

#define LL_TIM_LOCKLEVEL_OFF                   0x00000000U
#define LL_TIM_LOCKLEVEL_1                     TIM_BDTR_LOCK_0
#define LL_TIM_LOCKLEVEL_2                     TIM_BDTR_LOCK_1
#define LL_TIM_LOCKLEVEL_3                     TIM_BDTR_LOCK

#define LL_TIM_CHANNEL_CH1                     TIM_CCER_CC1E
#define LL_TIM_CHANNEL_CH1N                    TIM_CCER_CC1NE
#define LL_TIM_CHANNEL_CH2                     TIM_CCER_CC2E
#define LL_TIM_CHANNEL_CH2N                    TIM_CCER_CC2NE
#define LL_TIM_CHANNEL_CH3                     TIM_CCER_CC3E
#define LL_TIM_CHANNEL_CH3N                    TIM_CCER_CC3NE
#define LL_TIM_CHANNEL_CH4                     TIM_CCER_CC4E

#if defined(USE_FULL_LL_DRIVER)

#define LL_TIM_OCSTATE_DISABLE                 0x00000000U
#define LL_TIM_OCSTATE_ENABLE                  TIM_CCER_CC1E

#endif

#define LL_TIM_OCMODE_FROZEN                   0x00000000U
#define LL_TIM_OCMODE_ACTIVE                   TIM_CCMR1_OC1M_0
#define LL_TIM_OCMODE_INACTIVE                 TIM_CCMR1_OC1M_1
#define LL_TIM_OCMODE_TOGGLE                   (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)
#define LL_TIM_OCMODE_FORCED_INACTIVE          TIM_CCMR1_OC1M_2
#define LL_TIM_OCMODE_FORCED_ACTIVE            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)
#define LL_TIM_OCMODE_PWM1                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define LL_TIM_OCMODE_PWM2                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)

#define LL_TIM_OCPOLARITY_HIGH                 0x00000000U
#define LL_TIM_OCPOLARITY_LOW                  TIM_CCER_CC1P

#define LL_TIM_OCIDLESTATE_LOW                 0x00000000U
#define LL_TIM_OCIDLESTATE_HIGH                TIM_CR2_OIS1

#define LL_TIM_ACTIVEINPUT_DIRECTTI            (TIM_CCMR1_CC1S_0 << 16U)
#define LL_TIM_ACTIVEINPUT_INDIRECTTI          (TIM_CCMR1_CC1S_1 << 16U)
#define LL_TIM_ACTIVEINPUT_TRC                 (TIM_CCMR1_CC1S << 16U)

#define LL_TIM_ICPSC_DIV1                      0x00000000U
#define LL_TIM_ICPSC_DIV2                      (TIM_CCMR1_IC1PSC_0 << 16U)
#define LL_TIM_ICPSC_DIV4                      (TIM_CCMR1_IC1PSC_1 << 16U)
#define LL_TIM_ICPSC_DIV8                      (TIM_CCMR1_IC1PSC << 16U)

#define LL_TIM_IC_FILTER_FDIV1                 0x00000000U
#define LL_TIM_IC_FILTER_FDIV1_N2              (TIM_CCMR1_IC1F_0 << 16U)
#define LL_TIM_IC_FILTER_FDIV1_N4              (TIM_CCMR1_IC1F_1 << 16U)
#define LL_TIM_IC_FILTER_FDIV1_N8              ((TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV2_N6              (TIM_CCMR1_IC1F_2 << 16U)
#define LL_TIM_IC_FILTER_FDIV2_N8              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV4_N6              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1) << 16U)
#define LL_TIM_IC_FILTER_FDIV4_N8              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV8_N6              (TIM_CCMR1_IC1F_3 << 16U)
#define LL_TIM_IC_FILTER_FDIV8_N8              ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV16_N5             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_1) << 16U)
#define LL_TIM_IC_FILTER_FDIV16_N6             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV16_N8             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2) << 16U)
#define LL_TIM_IC_FILTER_FDIV32_N5             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_0) << 16U)
#define LL_TIM_IC_FILTER_FDIV32_N6             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1) << 16U)
#define LL_TIM_IC_FILTER_FDIV32_N8             (TIM_CCMR1_IC1F << 16U)

#define LL_TIM_IC_POLARITY_RISING              0x00000000U
#define LL_TIM_IC_POLARITY_FALLING             TIM_CCER_CC1P
#define LL_TIM_IC_POLARITY_BOTHEDGE            (TIM_CCER_CC1P | TIM_CCER_CC1NP)

#define LL_TIM_CLOCKSOURCE_INTERNAL            0x00000000U
#define LL_TIM_CLOCKSOURCE_EXT_MODE1           (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)
#define LL_TIM_CLOCKSOURCE_EXT_MODE2           TIM_SMCR_ECE

#define LL_TIM_ENCODERMODE_X2_TI1                     TIM_SMCR_SMS_0
#define LL_TIM_ENCODERMODE_X2_TI2                     TIM_SMCR_SMS_1
#define LL_TIM_ENCODERMODE_X4_TI12                   (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)

#define LL_TIM_TRGO_RESET                      0x00000000U
#define LL_TIM_TRGO_ENABLE                     TIM_CR2_MMS_0
#define LL_TIM_TRGO_UPDATE                     TIM_CR2_MMS_1
#define LL_TIM_TRGO_CC1IF                      (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)
#define LL_TIM_TRGO_OC1REF                     TIM_CR2_MMS_2
#define LL_TIM_TRGO_OC2REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)
#define LL_TIM_TRGO_OC3REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)
#define LL_TIM_TRGO_OC4REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)

#define LL_TIM_SLAVEMODE_DISABLED              0x00000000U
#define LL_TIM_SLAVEMODE_RESET                 TIM_SMCR_SMS_2
#define LL_TIM_SLAVEMODE_GATED                 (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)
#define LL_TIM_SLAVEMODE_TRIGGER               (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)

#define LL_TIM_TS_ITR0                         0x00000000U
#define LL_TIM_TS_ITR1                         TIM_SMCR_TS_0
#define LL_TIM_TS_ITR2                         TIM_SMCR_TS_1
#define LL_TIM_TS_ITR3                         (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)
#define LL_TIM_TS_TI1F_ED                      TIM_SMCR_TS_2
#define LL_TIM_TS_TI1FP1                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_0)
#define LL_TIM_TS_TI2FP2                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_1)
#define LL_TIM_TS_ETRF                         (TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0)

#define LL_TIM_ETR_POLARITY_NONINVERTED        0x00000000U
#define LL_TIM_ETR_POLARITY_INVERTED           TIM_SMCR_ETP

#define LL_TIM_ETR_PRESCALER_DIV1              0x00000000U
#define LL_TIM_ETR_PRESCALER_DIV2              TIM_SMCR_ETPS_0
#define LL_TIM_ETR_PRESCALER_DIV4              TIM_SMCR_ETPS_1
#define LL_TIM_ETR_PRESCALER_DIV8              TIM_SMCR_ETPS

#define LL_TIM_ETR_FILTER_FDIV1                0x00000000U
#define LL_TIM_ETR_FILTER_FDIV1_N2             TIM_SMCR_ETF_0
#define LL_TIM_ETR_FILTER_FDIV1_N4             TIM_SMCR_ETF_1
#define LL_TIM_ETR_FILTER_FDIV1_N8             (TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV2_N6             TIM_SMCR_ETF_2
#define LL_TIM_ETR_FILTER_FDIV2_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV4_N6             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)
#define LL_TIM_ETR_FILTER_FDIV4_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV8_N6             TIM_SMCR_ETF_3
#define LL_TIM_ETR_FILTER_FDIV8_N8             (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV16_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1)
#define LL_TIM_ETR_FILTER_FDIV16_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV16_N8            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2)
#define LL_TIM_ETR_FILTER_FDIV32_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)
#define LL_TIM_ETR_FILTER_FDIV32_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)
#define LL_TIM_ETR_FILTER_FDIV32_N8            TIM_SMCR_ETF

#define LL_TIM_BREAK_POLARITY_LOW              0x00000000U
#define LL_TIM_BREAK_POLARITY_HIGH             TIM_BDTR_BKP

#define LL_TIM_OSSI_DISABLE                    0x00000000U
#define LL_TIM_OSSI_ENABLE                     TIM_BDTR_OSSI

#define LL_TIM_OSSR_DISABLE                    0x00000000U
#define LL_TIM_OSSR_ENABLE                     TIM_BDTR_OSSR

#define LL_TIM_DMABURST_BASEADDR_CR1           0x00000000U
#define LL_TIM_DMABURST_BASEADDR_CR2           TIM_DCR_DBA_0
#define LL_TIM_DMABURST_BASEADDR_SMCR          TIM_DCR_DBA_1
#define LL_TIM_DMABURST_BASEADDR_DIER          (TIM_DCR_DBA_1 |  TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_SR            TIM_DCR_DBA_2
#define LL_TIM_DMABURST_BASEADDR_EGR           (TIM_DCR_DBA_2 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_CCMR1         (TIM_DCR_DBA_2 | TIM_DCR_DBA_1)
#define LL_TIM_DMABURST_BASEADDR_CCMR2         (TIM_DCR_DBA_2 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_CCER          TIM_DCR_DBA_3
#define LL_TIM_DMABURST_BASEADDR_CNT           (TIM_DCR_DBA_3 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_PSC           (TIM_DCR_DBA_3 | TIM_DCR_DBA_1)
#define LL_TIM_DMABURST_BASEADDR_ARR           (TIM_DCR_DBA_3 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_RCR           (TIM_DCR_DBA_3 | TIM_DCR_DBA_2)
#define LL_TIM_DMABURST_BASEADDR_CCR1          (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_CCR2          (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1)
#define LL_TIM_DMABURST_BASEADDR_CCR3          (TIM_DCR_DBA_3 | TIM_DCR_DBA_2 | TIM_DCR_DBA_1 | TIM_DCR_DBA_0)
#define LL_TIM_DMABURST_BASEADDR_CCR4          TIM_DCR_DBA_4
#define LL_TIM_DMABURST_BASEADDR_BDTR          (TIM_DCR_DBA_4 | TIM_DCR_DBA_0)

#define LL_TIM_DMABURST_LENGTH_1TRANSFER       0x00000000U
#define LL_TIM_DMABURST_LENGTH_2TRANSFERS      TIM_DCR_DBL_0
#define LL_TIM_DMABURST_LENGTH_3TRANSFERS      TIM_DCR_DBL_1
#define LL_TIM_DMABURST_LENGTH_4TRANSFERS      (TIM_DCR_DBL_1 |  TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_5TRANSFERS      TIM_DCR_DBL_2
#define LL_TIM_DMABURST_LENGTH_6TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_7TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_1)
#define LL_TIM_DMABURST_LENGTH_8TRANSFERS      (TIM_DCR_DBL_2 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_9TRANSFERS      TIM_DCR_DBL_3
#define LL_TIM_DMABURST_LENGTH_10TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_11TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_1)
#define LL_TIM_DMABURST_LENGTH_12TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_13TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2)
#define LL_TIM_DMABURST_LENGTH_14TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_15TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1)
#define LL_TIM_DMABURST_LENGTH_16TRANSFERS     (TIM_DCR_DBL_3 | TIM_DCR_DBL_2 | TIM_DCR_DBL_1 | TIM_DCR_DBL_0)
#define LL_TIM_DMABURST_LENGTH_17TRANSFERS     TIM_DCR_DBL_4
#define LL_TIM_DMABURST_LENGTH_18TRANSFERS     (TIM_DCR_DBL_4 |  TIM_DCR_DBL_0)

#define LL_TIM_TIM2_ITR1_RMP_TIM8_TRGO    TIM2_OR_RMP_MASK
#define LL_TIM_TIM2_ITR1_RMP_ETH_PTP      (TIM_OR_ITR1_RMP_0 | TIM2_OR_RMP_MASK)
#define LL_TIM_TIM2_ITR1_RMP_OTG_FS_SOF   (TIM_OR_ITR1_RMP_1 | TIM2_OR_RMP_MASK)
#define LL_TIM_TIM2_ITR1_RMP_OTG_HS_SOF   (TIM_OR_ITR1_RMP | TIM2_OR_RMP_MASK)

#define LL_TIM_TIM5_TI4_RMP_GPIO        TIM5_OR_RMP_MASK
#define LL_TIM_TIM5_TI4_RMP_LSI         (TIM_OR_TI4_RMP_0 | TIM5_OR_RMP_MASK)
#define LL_TIM_TIM5_TI4_RMP_LSE         (TIM_OR_TI4_RMP_1 | TIM5_OR_RMP_MASK)
#define LL_TIM_TIM5_TI4_RMP_RTC         (TIM_OR_TI4_RMP | TIM5_OR_RMP_MASK)

#define LL_TIM_TIM11_TI1_RMP_GPIO        TIM11_OR_RMP_MASK
#if defined(SPDIFRX)
#define LL_TIM_TIM11_TI1_RMP_SPDIFRX     (TIM_OR_TI1_RMP_0 | TIM11_OR_RMP_MASK)

#define  LL_TIM_TIM11_TI1_RMP_GPIO1      LL_TIM_TIM11_TI1_RMP_SPDIFRX

#else
#define LL_TIM_TIM11_TI1_RMP_GPIO1       (TIM_OR_TI1_RMP_0 | TIM11_OR_RMP_MASK)
#endif
#define LL_TIM_TIM11_TI1_RMP_GPIO2       (TIM_OR_TI1_RMP   | TIM11_OR_RMP_MASK)
#define LL_TIM_TIM11_TI1_RMP_HSE_RTC     (TIM_OR_TI1_RMP_1 | TIM11_OR_RMP_MASK)

#if defined(LPTIM_OR_TIM1_ITR2_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP) && defined(LPTIM_OR_TIM9_ITR1_RMP)

#define LL_TIM_LPTIM_REMAP_MASK           0x10000000U

#define LL_TIM_TIM9_ITR1_RMP_TIM3_TRGO    LL_TIM_LPTIM_REMAP_MASK
#define LL_TIM_TIM9_ITR1_RMP_LPTIM       (LL_TIM_LPTIM_REMAP_MASK | LPTIM_OR_TIM9_ITR1_RMP)

#define LL_TIM_TIM5_ITR1_RMP_TIM3_TRGO    LL_TIM_LPTIM_REMAP_MASK
#define LL_TIM_TIM5_ITR1_RMP_LPTIM       (LL_TIM_LPTIM_REMAP_MASK | LPTIM_OR_TIM5_ITR1_RMP)

#define LL_TIM_TIM1_ITR2_RMP_TIM3_TRGO    LL_TIM_LPTIM_REMAP_MASK
#define LL_TIM_TIM1_ITR2_RMP_LPTIM       (LL_TIM_LPTIM_REMAP_MASK | LPTIM_OR_TIM1_ITR2_RMP)

#endif

#define LL_TIM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

#define LL_TIM_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)

#define __LL_TIM_CALC_DEADTIME(__TIMCLK__, __CKD__, __DT__)  \
  ( (((uint64_t)((__DT__)*1000U)) < ((DT_DELAY_1+1U) * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))    ?  \
    (uint8_t)(((uint64_t)((__DT__)*1000U) / TIM_CALC_DTS((__TIMCLK__), (__CKD__)))  & DT_DELAY_1) :      \
    (((uint64_t)((__DT__)*1000U)) < ((64U + (DT_DELAY_2+1U)) * 2U * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))  ?  \
    (uint8_t)(DT_RANGE_2 | ((uint8_t)((uint8_t)((((uint64_t)((__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),   \
                                                 (__CKD__))) >> 1U) - (uint8_t) 64) & DT_DELAY_2)) :\
    (((uint64_t)((__DT__)*1000U)) < ((32U + (DT_DELAY_3+1U)) * 8U * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))  ?  \
    (uint8_t)(DT_RANGE_3 | ((uint8_t)((uint8_t)(((((uint64_t)(__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),  \
                                                 (__CKD__))) >> 3U) - (uint8_t) 32) & DT_DELAY_3)) :\
    (((uint64_t)((__DT__)*1000U)) < ((32U + (DT_DELAY_4+1U)) * 16U * TIM_CALC_DTS((__TIMCLK__), (__CKD__)))) ?  \
    (uint8_t)(DT_RANGE_4 | ((uint8_t)((uint8_t)(((((uint64_t)(__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),  \
                                                 (__CKD__))) >> 4U) - (uint8_t) 32) & DT_DELAY_4)) :\
    0U)

#define __LL_TIM_CALC_PSC(__TIMCLK__, __CNTCLK__)   \
  (((__TIMCLK__) >= (__CNTCLK__)) ? (uint32_t)((((__TIMCLK__) + (__CNTCLK__)/2U)/(__CNTCLK__)) - 1U) : 0U)

#define __LL_TIM_CALC_ARR(__TIMCLK__, __PSC__, __FREQ__) \
  ((((__TIMCLK__)/((__PSC__) + 1U)) >= (__FREQ__)) ? (((__TIMCLK__)/((__FREQ__) * ((__PSC__) + 1U))) - 1U) : 0U)

#define __LL_TIM_CALC_DELAY(__TIMCLK__, __PSC__, __DELAY__)  \
  ((uint32_t)(((uint64_t)(__TIMCLK__) * (uint64_t)(__DELAY__)) \
              / ((uint64_t)1000000U * (uint64_t)((__PSC__) + 1U))))

#define __LL_TIM_CALC_PULSE(__TIMCLK__, __PSC__, __DELAY__, __PULSE__)  \
  ((uint32_t)(__LL_TIM_CALC_DELAY((__TIMCLK__), (__PSC__), (__PULSE__)) \
              + __LL_TIM_CALC_DELAY((__TIMCLK__), (__PSC__), (__DELAY__))))

#define __LL_TIM_GET_ICPSC_RATIO(__ICPSC__)  \
  ((uint32_t)(0x01U << (((__ICPSC__) >> 16U) >> TIM_CCMR1_IC1PSC_Pos)))

__STATIC_INLINE void LL_TIM_EnableCounter(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_CEN);
}

__STATIC_INLINE void LL_TIM_DisableCounter(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_CEN);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledCounter(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_CEN) == (TIM_CR1_CEN)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableUpdateEvent(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_UDIS);
}

__STATIC_INLINE void LL_TIM_DisableUpdateEvent(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_UDIS);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledUpdateEvent(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_UDIS) == (uint32_t)RESET) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_SetUpdateSource(TIM_TypeDef *TIMx, uint32_t UpdateSource)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_URS, UpdateSource);
}

__STATIC_INLINE uint32_t LL_TIM_GetUpdateSource(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_URS));
}

__STATIC_INLINE void LL_TIM_SetOnePulseMode(TIM_TypeDef *TIMx, uint32_t OnePulseMode)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_OPM, OnePulseMode);
}

__STATIC_INLINE uint32_t LL_TIM_GetOnePulseMode(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_OPM));
}

__STATIC_INLINE void LL_TIM_SetCounterMode(TIM_TypeDef *TIMx, uint32_t CounterMode)
{
  MODIFY_REG(TIMx->CR1, (TIM_CR1_DIR | TIM_CR1_CMS), CounterMode);
}

__STATIC_INLINE uint32_t LL_TIM_GetCounterMode(const TIM_TypeDef *TIMx)
{
  uint32_t counter_mode;

  counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_CMS));

  if (counter_mode == 0U)
  {
    counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_DIR));
  }

  return counter_mode;
}

__STATIC_INLINE void LL_TIM_EnableARRPreload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_ARPE);
}

__STATIC_INLINE void LL_TIM_DisableARRPreload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_ARPE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledARRPreload(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_ARPE) == (TIM_CR1_ARPE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_SetClockDivision(TIM_TypeDef *TIMx, uint32_t ClockDivision)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_CKD, ClockDivision);
}

__STATIC_INLINE uint32_t LL_TIM_GetClockDivision(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_CKD));
}

__STATIC_INLINE void LL_TIM_SetCounter(TIM_TypeDef *TIMx, uint32_t Counter)
{
  WRITE_REG(TIMx->CNT, Counter);
}

__STATIC_INLINE uint32_t LL_TIM_GetCounter(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CNT));
}

__STATIC_INLINE uint32_t LL_TIM_GetDirection(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_DIR));
}

__STATIC_INLINE void LL_TIM_SetPrescaler(TIM_TypeDef *TIMx, uint32_t Prescaler)
{
  WRITE_REG(TIMx->PSC, Prescaler);
}

__STATIC_INLINE uint32_t LL_TIM_GetPrescaler(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->PSC));
}

__STATIC_INLINE void LL_TIM_SetAutoReload(TIM_TypeDef *TIMx, uint32_t AutoReload)
{
  WRITE_REG(TIMx->ARR, AutoReload);
}

__STATIC_INLINE uint32_t LL_TIM_GetAutoReload(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->ARR));
}

__STATIC_INLINE void LL_TIM_SetRepetitionCounter(TIM_TypeDef *TIMx, uint32_t RepetitionCounter)
{
  WRITE_REG(TIMx->RCR, RepetitionCounter);
}

__STATIC_INLINE uint32_t LL_TIM_GetRepetitionCounter(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->RCR));
}

__STATIC_INLINE void LL_TIM_CC_EnablePreload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR2, TIM_CR2_CCPC);
}

__STATIC_INLINE void LL_TIM_CC_DisablePreload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIM_CR2_CCPC);
}

__STATIC_INLINE uint32_t LL_TIM_CC_IsEnabledPreload(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR2, TIM_CR2_CCPC) == (TIM_CR2_CCPC)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_CC_SetUpdate(TIM_TypeDef *TIMx, uint32_t CCUpdateSource)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_CCUS, CCUpdateSource);
}

__STATIC_INLINE void LL_TIM_CC_SetDMAReqTrigger(TIM_TypeDef *TIMx, uint32_t DMAReqTrigger)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_CCDS, DMAReqTrigger);
}

__STATIC_INLINE uint32_t LL_TIM_CC_GetDMAReqTrigger(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR2, TIM_CR2_CCDS));
}

__STATIC_INLINE void LL_TIM_CC_SetLockLevel(TIM_TypeDef *TIMx, uint32_t LockLevel)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_LOCK, LockLevel);
}

__STATIC_INLINE void LL_TIM_CC_EnableChannel(TIM_TypeDef *TIMx, uint32_t Channels)
{
  SET_BIT(TIMx->CCER, Channels);
}

__STATIC_INLINE void LL_TIM_CC_DisableChannel(TIM_TypeDef *TIMx, uint32_t Channels)
{
  CLEAR_BIT(TIMx->CCER, Channels);
}

__STATIC_INLINE uint32_t LL_TIM_CC_IsEnabledChannel(const TIM_TypeDef *TIMx, uint32_t Channels)
{
  return ((READ_BIT(TIMx->CCER, Channels) == (Channels)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_OC_ConfigOutput(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_CC1S << SHIFT_TAB_OCxx[iChannel]));
  MODIFY_REG(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel]),
             (Configuration & TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]);
  MODIFY_REG(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel]),
             (Configuration & TIM_CR2_OIS1) << SHIFT_TAB_OISx[iChannel]);
}

__STATIC_INLINE void LL_TIM_OC_SetMode(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Mode)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_OC1M  | TIM_CCMR1_CC1S) << SHIFT_TAB_OCxx[iChannel]), Mode << SHIFT_TAB_OCxx[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetMode(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return (READ_BIT(*pReg, ((TIM_CCMR1_OC1M | TIM_CCMR1_CC1S) << SHIFT_TAB_OCxx[iChannel])) >> SHIFT_TAB_OCxx[iChannel]);
}

__STATIC_INLINE void LL_TIM_OC_SetPolarity(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Polarity)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel]),  Polarity << SHIFT_TAB_CCxP[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetPolarity(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel])) >> SHIFT_TAB_CCxP[iChannel]);
}

__STATIC_INLINE void LL_TIM_OC_SetIdleState(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t IdleState)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel]),  IdleState << SHIFT_TAB_OISx[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetIdleState(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel])) >> SHIFT_TAB_OISx[iChannel]);
}

__STATIC_INLINE void LL_TIM_OC_EnableFast(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel]));

}

__STATIC_INLINE void LL_TIM_OC_DisableFast(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel]));

}

__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledFast(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_OC_EnablePreload(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel]));
}

__STATIC_INLINE void LL_TIM_OC_DisablePreload(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel]));
}

__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledPreload(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_OC_EnableClear(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel]));
}

__STATIC_INLINE void LL_TIM_OC_DisableClear(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel]));
}

__STATIC_INLINE uint32_t LL_TIM_OC_IsEnabledClear(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_OC_SetDeadTime(TIM_TypeDef *TIMx, uint32_t DeadTime)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_DTG, DeadTime);
}

__STATIC_INLINE void LL_TIM_OC_SetCompareCH1(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR1, CompareValue);
}

__STATIC_INLINE void LL_TIM_OC_SetCompareCH2(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR2, CompareValue);
}

__STATIC_INLINE void LL_TIM_OC_SetCompareCH3(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR3, CompareValue);
}

__STATIC_INLINE void LL_TIM_OC_SetCompareCH4(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR4, CompareValue);
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH1(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH2(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH3(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

__STATIC_INLINE uint32_t LL_TIM_OC_GetCompareCH4(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}

__STATIC_INLINE void LL_TIM_IC_Config(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel]),
             ((Configuration >> 16U) & (TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S))                \
             << SHIFT_TAB_ICxx[iChannel]);
  MODIFY_REG(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]),
             (Configuration & (TIM_CCER_CC1NP | TIM_CCER_CC1P)) << SHIFT_TAB_CCxP[iChannel]);
}

__STATIC_INLINE void LL_TIM_IC_SetActiveInput(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICActiveInput)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel]), (ICActiveInput >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetActiveInput(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

__STATIC_INLINE void LL_TIM_IC_SetPrescaler(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICPrescaler)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1PSC) << SHIFT_TAB_ICxx[iChannel]), (ICPrescaler >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetPrescaler(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1PSC) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

__STATIC_INLINE void LL_TIM_IC_SetFilter(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICFilter)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F) << SHIFT_TAB_ICxx[iChannel]), (ICFilter >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetFilter(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1F) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

__STATIC_INLINE void LL_TIM_IC_SetPolarity(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICPolarity)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]),
             ICPolarity << SHIFT_TAB_CCxP[iChannel]);
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetPolarity(const TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel])) >>
          SHIFT_TAB_CCxP[iChannel]);
}

__STATIC_INLINE void LL_TIM_IC_EnableXORCombination(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR2, TIM_CR2_TI1S);
}

__STATIC_INLINE void LL_TIM_IC_DisableXORCombination(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIM_CR2_TI1S);
}

__STATIC_INLINE uint32_t LL_TIM_IC_IsEnabledXORCombination(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR2, TIM_CR2_TI1S) == (TIM_CR2_TI1S)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH1(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH2(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH3(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

__STATIC_INLINE uint32_t LL_TIM_IC_GetCaptureCH4(const TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}

__STATIC_INLINE void LL_TIM_EnableExternalClock(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->SMCR, TIM_SMCR_ECE);
}

__STATIC_INLINE void LL_TIM_DisableExternalClock(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIM_SMCR_ECE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledExternalClock(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIM_SMCR_ECE) == (TIM_SMCR_ECE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_SetClockSource(TIM_TypeDef *TIMx, uint32_t ClockSource)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS | TIM_SMCR_ECE, ClockSource);
}

__STATIC_INLINE void LL_TIM_SetEncoderMode(TIM_TypeDef *TIMx, uint32_t EncoderMode)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS, EncoderMode);
}

__STATIC_INLINE void LL_TIM_SetTriggerOutput(TIM_TypeDef *TIMx, uint32_t TimerSynchronization)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_MMS, TimerSynchronization);
}

__STATIC_INLINE void LL_TIM_SetSlaveMode(TIM_TypeDef *TIMx, uint32_t SlaveMode)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS, SlaveMode);
}

__STATIC_INLINE void LL_TIM_SetTriggerInput(TIM_TypeDef *TIMx, uint32_t TriggerInput)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_TS, TriggerInput);
}

__STATIC_INLINE void LL_TIM_EnableMasterSlaveMode(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->SMCR, TIM_SMCR_MSM);
}

__STATIC_INLINE void LL_TIM_DisableMasterSlaveMode(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIM_SMCR_MSM);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledMasterSlaveMode(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIM_SMCR_MSM) == (TIM_SMCR_MSM)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ConfigETR(TIM_TypeDef *TIMx, uint32_t ETRPolarity, uint32_t ETRPrescaler,
                                      uint32_t ETRFilter)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_ETP | TIM_SMCR_ETPS | TIM_SMCR_ETF, ETRPolarity | ETRPrescaler | ETRFilter);
}

__STATIC_INLINE void LL_TIM_EnableBRK(TIM_TypeDef *TIMx)
{
  __IO uint32_t tmpreg;
  SET_BIT(TIMx->BDTR, TIM_BDTR_BKE);

  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

__STATIC_INLINE void LL_TIM_DisableBRK(TIM_TypeDef *TIMx)
{
  __IO uint32_t tmpreg;
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_BKE);

  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

__STATIC_INLINE void LL_TIM_ConfigBRK(TIM_TypeDef *TIMx, uint32_t BreakPolarity)
{
  __IO uint32_t tmpreg;
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_BKP, BreakPolarity);

  tmpreg = READ_REG(TIMx->BDTR);
  (void)(tmpreg);
}

__STATIC_INLINE void LL_TIM_SetOffStates(TIM_TypeDef *TIMx, uint32_t OffStateIdle, uint32_t OffStateRun)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_OSSI | TIM_BDTR_OSSR, OffStateIdle | OffStateRun);
}

__STATIC_INLINE void LL_TIM_EnableAutomaticOutput(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_AOE);
}

__STATIC_INLINE void LL_TIM_DisableAutomaticOutput(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_AOE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledAutomaticOutput(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIM_BDTR_AOE) == (TIM_BDTR_AOE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableAllOutputs(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_MOE);
}

__STATIC_INLINE void LL_TIM_DisableAllOutputs(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_MOE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledAllOutputs(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIM_BDTR_MOE) == (TIM_BDTR_MOE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ConfigDMABurst(TIM_TypeDef *TIMx, uint32_t DMABurstBaseAddress, uint32_t DMABurstLength)
{
  MODIFY_REG(TIMx->DCR, (TIM_DCR_DBL | TIM_DCR_DBA), (DMABurstBaseAddress | DMABurstLength));
}

__STATIC_INLINE void LL_TIM_SetRemap(TIM_TypeDef *TIMx, uint32_t Remap)
{
#if defined(LPTIM_OR_TIM1_ITR2_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP) && defined(LPTIM_OR_TIM9_ITR1_RMP)
  if ((Remap & LL_TIM_LPTIM_REMAP_MASK) == LL_TIM_LPTIM_REMAP_MASK)
  {

    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_LPTIM1EN);
    MODIFY_REG(LPTIM1->OR,
               (LPTIM_OR_TIM1_ITR2_RMP | LPTIM_OR_TIM5_ITR1_RMP | LPTIM_OR_TIM9_ITR1_RMP),
               Remap & ~(LL_TIM_LPTIM_REMAP_MASK));
  }
  else
  {
    MODIFY_REG(TIMx->OR, (Remap >> TIMx_OR_RMP_SHIFT), (Remap & TIMx_OR_RMP_MASK));
  }
#else
  MODIFY_REG(TIMx->OR, (Remap >> TIMx_OR_RMP_SHIFT), (Remap & TIMx_OR_RMP_MASK));
#endif
}

__STATIC_INLINE void LL_TIM_ClearFlag_UPDATE(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_UIF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_UPDATE(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_UIF) == (TIM_SR_UIF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC1(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC1IF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC1(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC1IF) == (TIM_SR_CC1IF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC2(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC2IF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC2(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC2IF) == (TIM_SR_CC2IF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC3(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC3IF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC3(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC3IF) == (TIM_SR_CC3IF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC4(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC4IF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC4(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC4IF) == (TIM_SR_CC4IF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_COM(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_COMIF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_COM(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_COMIF) == (TIM_SR_COMIF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_TRIG(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_TIF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_TRIG(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_TIF) == (TIM_SR_TIF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_BRK(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_BIF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_BRK(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_BIF) == (TIM_SR_BIF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC1OVR(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC1OF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC1OVR(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC1OF) == (TIM_SR_CC1OF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC2OVR(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC2OF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC2OVR(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC2OF) == (TIM_SR_CC2OF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC3OVR(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC3OF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC3OVR(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC3OF) == (TIM_SR_CC3OF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_ClearFlag_CC4OVR(TIM_TypeDef *TIMx)
{
  WRITE_REG(TIMx->SR, ~(TIM_SR_CC4OF));
}

__STATIC_INLINE uint32_t LL_TIM_IsActiveFlag_CC4OVR(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SR, TIM_SR_CC4OF) == (TIM_SR_CC4OF)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_UPDATE(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_UIE);
}

__STATIC_INLINE void LL_TIM_DisableIT_UPDATE(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_UIE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_UPDATE(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_UIE) == (TIM_DIER_UIE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_CC1(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC1IE);
}

__STATIC_INLINE void LL_TIM_DisableIT_CC1(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC1IE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC1(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC1IE) == (TIM_DIER_CC1IE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_CC2(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC2IE);
}

__STATIC_INLINE void LL_TIM_DisableIT_CC2(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC2IE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC2(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC2IE) == (TIM_DIER_CC2IE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_CC3(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC3IE);
}

__STATIC_INLINE void LL_TIM_DisableIT_CC3(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC3IE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC3(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC3IE) == (TIM_DIER_CC3IE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_CC4(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC4IE);
}

__STATIC_INLINE void LL_TIM_DisableIT_CC4(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC4IE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_CC4(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC4IE) == (TIM_DIER_CC4IE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_COM(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_COMIE);
}

__STATIC_INLINE void LL_TIM_DisableIT_COM(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_COMIE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_COM(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_COMIE) == (TIM_DIER_COMIE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_TRIG(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_TIE);
}

__STATIC_INLINE void LL_TIM_DisableIT_TRIG(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_TIE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_TRIG(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_TIE) == (TIM_DIER_TIE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableIT_BRK(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_BIE);
}

__STATIC_INLINE void LL_TIM_DisableIT_BRK(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_BIE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledIT_BRK(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_BIE) == (TIM_DIER_BIE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_UPDATE(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_UDE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_UPDATE(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_UDE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_UPDATE(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_UDE) == (TIM_DIER_UDE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_CC1(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC1DE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_CC1(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC1DE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC1(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC1DE) == (TIM_DIER_CC1DE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_CC2(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC2DE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_CC2(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC2DE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC2(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC2DE) == (TIM_DIER_CC2DE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_CC3(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC3DE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_CC3(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC3DE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC3(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC3DE) == (TIM_DIER_CC3DE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_CC4(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_CC4DE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_CC4(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_CC4DE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_CC4(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_CC4DE) == (TIM_DIER_CC4DE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_COM(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_COMDE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_COM(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_COMDE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_COM(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_COMDE) == (TIM_DIER_COMDE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_EnableDMAReq_TRIG(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DIER, TIM_DIER_TDE);
}

__STATIC_INLINE void LL_TIM_DisableDMAReq_TRIG(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DIER, TIM_DIER_TDE);
}

__STATIC_INLINE uint32_t LL_TIM_IsEnabledDMAReq_TRIG(const TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DIER, TIM_DIER_TDE) == (TIM_DIER_TDE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_UPDATE(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_UG);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_CC1(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_CC1G);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_CC2(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_CC2G);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_CC3(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_CC3G);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_CC4(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_CC4G);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_COM(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_COMG);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_TRIG(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_TG);
}

__STATIC_INLINE void LL_TIM_GenerateEvent_BRK(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->EGR, TIM_EGR_BG);
}

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_TIM_DeInit(const TIM_TypeDef *TIMx);
void LL_TIM_StructInit(LL_TIM_InitTypeDef *TIM_InitStruct);
ErrorStatus LL_TIM_Init(TIM_TypeDef *TIMx, const LL_TIM_InitTypeDef *TIM_InitStruct);
void LL_TIM_OC_StructInit(LL_TIM_OC_InitTypeDef *TIM_OC_InitStruct);
ErrorStatus LL_TIM_OC_Init(TIM_TypeDef *TIMx, uint32_t Channel, const LL_TIM_OC_InitTypeDef *TIM_OC_InitStruct);
void LL_TIM_IC_StructInit(LL_TIM_IC_InitTypeDef *TIM_ICInitStruct);
ErrorStatus LL_TIM_IC_Init(TIM_TypeDef *TIMx, uint32_t Channel, const LL_TIM_IC_InitTypeDef *TIM_IC_InitStruct);
void LL_TIM_ENCODER_StructInit(LL_TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct);
ErrorStatus LL_TIM_ENCODER_Init(TIM_TypeDef *TIMx, const LL_TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct);
void LL_TIM_HALLSENSOR_StructInit(LL_TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct);
ErrorStatus LL_TIM_HALLSENSOR_Init(TIM_TypeDef *TIMx, const LL_TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct);
void LL_TIM_BDTR_StructInit(LL_TIM_BDTR_InitTypeDef *TIM_BDTRInitStruct);
ErrorStatus LL_TIM_BDTR_Init(TIM_TypeDef *TIMx, const LL_TIM_BDTR_InitTypeDef *TIM_BDTRInitStruct);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
