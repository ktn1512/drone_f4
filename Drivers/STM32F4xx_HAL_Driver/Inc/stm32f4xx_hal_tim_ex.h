#ifndef STM32F4xx_HAL_TIM_EX_H
#define STM32F4xx_HAL_TIM_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t IC1Polarity;

  uint32_t IC1Prescaler;

  uint32_t IC1Filter;

  uint32_t Commutation_Delay;
} TIM_HallSensor_InitTypeDef;

#if defined (TIM2)
#if defined(TIM8)
#define TIM_TIM2_TIM8_TRGO                     0x00000000U
#endif
#define TIM_TIM2_ETH_PTP                       TIM_OR_ITR1_RMP_0
#define TIM_TIM2_USBFS_SOF                     TIM_OR_ITR1_RMP_1
#define TIM_TIM2_USBHS_SOF                     (TIM_OR_ITR1_RMP_1 | TIM_OR_ITR1_RMP_0)
#endif

#define TIM_TIM5_GPIO                          0x00000000U
#define TIM_TIM5_LSI                           TIM_OR_TI4_RMP_0
#define TIM_TIM5_LSE                           TIM_OR_TI4_RMP_1
#define TIM_TIM5_RTC                           (TIM_OR_TI4_RMP_1 | TIM_OR_TI4_RMP_0)

#define TIM_TIM11_GPIO                         0x00000000U
#define TIM_TIM11_HSE                          TIM_OR_TI1_RMP_1
#if defined(SPDIFRX)
#define TIM_TIM11_SPDIFRX                      TIM_OR_TI1_RMP_0
#endif

#if defined(LPTIM_OR_TIM1_ITR2_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP)
#define LPTIM_REMAP_MASK                       0x10000000U

#define TIM_TIM9_TIM3_TRGO                     LPTIM_REMAP_MASK
#define TIM_TIM9_LPTIM                         (LPTIM_REMAP_MASK | LPTIM_OR_TIM9_ITR1_RMP)

#define TIM_TIM5_TIM3_TRGO                     LPTIM_REMAP_MASK
#define TIM_TIM5_LPTIM                         (LPTIM_REMAP_MASK | LPTIM_OR_TIM5_ITR1_RMP)

#define TIM_TIM1_TIM3_TRGO                     LPTIM_REMAP_MASK
#define TIM_TIM1_LPTIM                         (LPTIM_REMAP_MASK | LPTIM_OR_TIM1_ITR2_RMP)
#endif

#if defined(SPDIFRX)
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)                                 \
  ((((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_TIM8_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM2_USBFS_SOF)      || \
                              ((TIM_REMAP) == TIM_TIM2_USBHS_SOF)))    || \
   (((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_GPIO)           || \
                              ((TIM_REMAP) == TIM_TIM5_LSI)            || \
                              ((TIM_REMAP) == TIM_TIM5_LSE)            || \
                              ((TIM_REMAP) == TIM_TIM5_RTC)))          || \
   (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO)          || \
                              ((TIM_REMAP) == TIM_TIM11_SPDIFRX)       || \
                              ((TIM_REMAP) == TIM_TIM11_HSE))))
#elif defined(TIM2)
#if defined(LPTIM_OR_TIM1_ITR2_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP) && defined(LPTIM_OR_TIM5_ITR1_RMP)
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)                                 \
  ((((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_TIM8_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM2_ETH_PTP)        || \
                              ((TIM_REMAP) == TIM_TIM2_USBFS_SOF)      || \
                              ((TIM_REMAP) == TIM_TIM2_USBHS_SOF)))    || \
   (((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_GPIO)           || \
                              ((TIM_REMAP) == TIM_TIM5_LSI)            || \
                              ((TIM_REMAP) == TIM_TIM5_LSE)            || \
                              ((TIM_REMAP) == TIM_TIM5_RTC)))          || \
   (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO)          || \
                              ((TIM_REMAP) == TIM_TIM11_HSE)))         || \
   (((INSTANCE) == TIM1)  && (((TIM_REMAP) == TIM_TIM1_TIM3_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM1_LPTIM)))        || \
   (((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_TIM3_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM5_LPTIM)))        || \
   (((INSTANCE) == TIM9)  && (((TIM_REMAP) == TIM_TIM9_TIM3_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM9_LPTIM))))
#elif defined(TIM8)
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)                                 \
  ((((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_TIM8_TRGO)      || \
                              ((TIM_REMAP) == TIM_TIM2_ETH_PTP)        || \
                              ((TIM_REMAP) == TIM_TIM2_USBFS_SOF)      || \
                              ((TIM_REMAP) == TIM_TIM2_USBHS_SOF)))    || \
   (((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_GPIO)           || \
                              ((TIM_REMAP) == TIM_TIM5_LSI)            || \
                              ((TIM_REMAP) == TIM_TIM5_LSE)            || \
                              ((TIM_REMAP) == TIM_TIM5_RTC)))          || \
   (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO)          || \
                              ((TIM_REMAP) == TIM_TIM11_HSE))))
#else
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)                                 \
  ((((INSTANCE) == TIM2)  && (((TIM_REMAP) == TIM_TIM2_ETH_PTP)        || \
                              ((TIM_REMAP) == TIM_TIM2_USBFS_SOF)      || \
                              ((TIM_REMAP) == TIM_TIM2_USBHS_SOF)))    || \
   (((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_GPIO)           || \
                              ((TIM_REMAP) == TIM_TIM5_LSI)            || \
                              ((TIM_REMAP) == TIM_TIM5_LSE)            || \
                              ((TIM_REMAP) == TIM_TIM5_RTC)))          || \
   (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO)          || \
                              ((TIM_REMAP) == TIM_TIM11_HSE))))
#endif
#else
#define IS_TIM_REMAP(INSTANCE, TIM_REMAP)                                 \
  ((((INSTANCE) == TIM5)  && (((TIM_REMAP) == TIM_TIM5_GPIO)           || \
                              ((TIM_REMAP) == TIM_TIM5_LSI)            || \
                              ((TIM_REMAP) == TIM_TIM5_LSE)            || \
                              ((TIM_REMAP) == TIM_TIM5_RTC)))          || \
   (((INSTANCE) == TIM11) && (((TIM_REMAP) == TIM_TIM11_GPIO)          || \
                              ((TIM_REMAP) == TIM_TIM11_HSE))))
#endif

HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, const TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);

HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                          uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                           uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);

HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        const TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                const TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);

void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);

HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIMEx_GetChannelNState(const TIM_HandleTypeDef *htim,  uint32_t ChannelN);

void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);

#ifdef __cplusplus
}
#endif

#endif
