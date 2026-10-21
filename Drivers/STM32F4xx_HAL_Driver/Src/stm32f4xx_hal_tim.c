#include "stm32f4xx_hal.h"

#ifdef HAL_TIM_MODULE_ENABLED

static void TIM_OC1_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
static void TIM_OC3_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
static void TIM_OC4_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
static void TIM_TI1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);
static void TIM_TI2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter);
static void TIM_TI2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter);
static void TIM_TI3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter);
static void TIM_TI4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter);
static void TIM_ITRx_SetConfig(TIM_TypeDef *TIMx, uint32_t InputTriggerSource);
static void TIM_DMAPeriodElapsedCplt(DMA_HandleTypeDef *hdma);
static void TIM_DMAPeriodElapsedHalfCplt(DMA_HandleTypeDef *hdma);
static void TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma);
static void TIM_DMATriggerCplt(DMA_HandleTypeDef *hdma);
static void TIM_DMATriggerHalfCplt(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef TIM_SlaveTimer_SetConfig(TIM_HandleTypeDef *htim,
                                                  const TIM_SlaveConfigTypeDef *sSlaveConfig);

HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim)
{

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->Base_MspInitCallback == NULL)
    {
      htim->Base_MspInitCallback = HAL_TIM_Base_MspInit;
    }

    htim->Base_MspInitCallback(htim);
#else

    HAL_TIM_Base_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  TIM_Base_SetConfig(htim->Instance, &htim->Init);

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->Base_MspDeInitCallback == NULL)
  {
    htim->Base_MspDeInitCallback = HAL_TIM_Base_MspDeInit;
  }

  htim->Base_MspDeInitCallback(htim);
#else

  HAL_TIM_Base_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim)
{
  uint32_t tmpsmcr;

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  if (htim->State != HAL_TIM_STATE_READY)
  {
    return HAL_ERROR;
  }

  htim->State = HAL_TIM_STATE_BUSY;

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  __HAL_TIM_DISABLE(htim);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim)
{
  uint32_t tmpsmcr;

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  if (htim->State != HAL_TIM_STATE_READY)
  {
    return HAL_ERROR;
  }

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  __HAL_TIM_DISABLE_IT(htim, TIM_IT_UPDATE);

  __HAL_TIM_DISABLE(htim);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length)
{
  uint32_t tmpsmcr;

  assert_param(IS_TIM_DMA_INSTANCE(htim->Instance));

  if (htim->State == HAL_TIM_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (htim->State == HAL_TIM_STATE_READY)
  {
    if ((pData == NULL) || (Length == 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      htim->State = HAL_TIM_STATE_BUSY;
    }
  }
  else
  {
    return HAL_ERROR;
  }

  htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;
  htim->hdma[TIM_DMA_ID_UPDATE]->XferHalfCpltCallback = TIM_DMAPeriodElapsedHalfCplt;

  htim->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError ;

  if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_UPDATE], (uint32_t)pData, (uint32_t)&htim->Instance->ARR,
                       Length) != HAL_OK)
  {

    return HAL_ERROR;
  }

  __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_UPDATE);

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_DMA_INSTANCE(htim->Instance));

  __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_UPDATE);

  (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_UPDATE]);

  __HAL_TIM_DISABLE(htim);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim)
{

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->OC_MspInitCallback == NULL)
    {
      htim->OC_MspInitCallback = HAL_TIM_OC_MspInit;
    }

    htim->OC_MspInitCallback(htim);
#else

    HAL_TIM_OC_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  TIM_Base_SetConfig(htim->Instance,  &htim->Init);

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->OC_MspDeInitCallback == NULL)
  {
    htim->OC_MspDeInitCallback = HAL_TIM_OC_MspDeInit;
  }

  htim->OC_MspDeInitCallback(htim);
#else

  HAL_TIM_OC_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_ENABLE(htim);
  }

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_DISABLE(htim);
  }

  __HAL_TIM_DISABLE(htim);

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_ENABLE(htim);
    }

    if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
    {
      tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
      if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
      {
        __HAL_TIM_ENABLE(htim);
      }
    }
    else
    {
      __HAL_TIM_ENABLE(htim);
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_DISABLE(htim);
    }

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                       uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
  {
    if ((pData == NULL) || (Length == 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    return HAL_ERROR;
  }

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->CCR1,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)pData, (uint32_t)&htim->Instance->CCR2,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)pData, (uint32_t)&htim->Instance->CCR3,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)pData, (uint32_t)&htim->Instance->CCR4,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_ENABLE(htim);
    }

    if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
    {
      tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
      if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
      {
        __HAL_TIM_ENABLE(htim);
      }
    }
    else
    {
      __HAL_TIM_ENABLE(htim);
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC3);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC4);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_DISABLE(htim);
    }

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim)
{

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->PWM_MspInitCallback == NULL)
    {
      htim->PWM_MspInitCallback = HAL_TIM_PWM_MspInit;
    }

    htim->PWM_MspInitCallback(htim);
#else

    HAL_TIM_PWM_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  TIM_Base_SetConfig(htim->Instance, &htim->Init);

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->PWM_MspDeInitCallback == NULL)
  {
    htim->PWM_MspDeInitCallback = HAL_TIM_PWM_MspDeInit;
  }

  htim->PWM_MspDeInitCallback(htim);
#else

  HAL_TIM_PWM_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_ENABLE(htim);
  }

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_DISABLE(htim);
  }

  __HAL_TIM_DISABLE(htim);

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_ENABLE(htim);
    }

    if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
    {
      tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
      if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
      {
        __HAL_TIM_ENABLE(htim);
      }
    }
    else
    {
      __HAL_TIM_ENABLE(htim);
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_DISABLE(htim);
    }

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                        uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
  {
    if ((pData == NULL) || (Length == 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    return HAL_ERROR;
  }

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->CCR1,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)pData, (uint32_t)&htim->Instance->CCR2,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)pData, (uint32_t)&htim->Instance->CCR3,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)pData, (uint32_t)&htim->Instance->CCR4,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_ENABLE(htim);
    }

    if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
    {
      tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
      if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
      {
        __HAL_TIM_ENABLE(htim);
      }
    }
    else
    {
      __HAL_TIM_ENABLE(htim);
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC3);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC4);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
    {

      __HAL_TIM_MOE_DISABLE(htim);
    }

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim)
{

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->IC_MspInitCallback == NULL)
    {
      htim->IC_MspInitCallback = HAL_TIM_IC_MspInit;
    }

    htim->IC_MspInitCallback(htim);
#else

    HAL_TIM_IC_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  TIM_Base_SetConfig(htim->Instance, &htim->Init);

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->IC_MspDeInitCallback == NULL)
  {
    htim->IC_MspDeInitCallback = HAL_TIM_IC_MspDeInit;
  }

  htim->IC_MspDeInitCallback(htim);
#else

  HAL_TIM_IC_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET_ALL(htim, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t tmpsmcr;
  HAL_TIM_ChannelStateTypeDef channel_state = TIM_CHANNEL_STATE_GET(htim, Channel);
  HAL_TIM_ChannelStateTypeDef complementary_channel_state = TIM_CHANNEL_N_STATE_GET(htim, Channel);

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if ((channel_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_state != HAL_TIM_CHANNEL_STATE_READY))
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

  __HAL_TIM_DISABLE(htim);

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  HAL_TIM_ChannelStateTypeDef channel_state = TIM_CHANNEL_STATE_GET(htim, Channel);
  HAL_TIM_ChannelStateTypeDef complementary_channel_state = TIM_CHANNEL_N_STATE_GET(htim, Channel);

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if ((channel_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_state != HAL_TIM_CHANNEL_STATE_READY))
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

    if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
    {
      tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
      if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
      {
        __HAL_TIM_ENABLE(htim);
      }
    }
    else
    {
      __HAL_TIM_ENABLE(htim);
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  HAL_TIM_ChannelStateTypeDef channel_state = TIM_CHANNEL_STATE_GET(htim, Channel);
  HAL_TIM_ChannelStateTypeDef complementary_channel_state = TIM_CHANNEL_N_STATE_GET(htim, Channel);

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));
  assert_param(IS_TIM_DMA_CC_INSTANCE(htim->Instance));

  if ((channel_state == HAL_TIM_CHANNEL_STATE_BUSY)
      || (complementary_channel_state == HAL_TIM_CHANNEL_STATE_BUSY))
  {
    return HAL_BUSY;
  }
  else if ((channel_state == HAL_TIM_CHANNEL_STATE_READY)
           && (complementary_channel_state == HAL_TIM_CHANNEL_STATE_READY))
  {
    if ((pData == NULL) || (Length == 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    return HAL_ERROR;
  }

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&htim->Instance->CCR1, (uint32_t)pData,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)&htim->Instance->CCR2, (uint32_t)pData,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);
      break;
    }

    case TIM_CHANNEL_3:
    {

      htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)&htim->Instance->CCR3, (uint32_t)pData,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC3);
      break;
    }

    case TIM_CHANNEL_4:
    {

      htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)&htim->Instance->CCR4, (uint32_t)pData,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC4);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      __HAL_TIM_ENABLE(htim);
    }
  }
  else
  {
    __HAL_TIM_ENABLE(htim);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));
  assert_param(IS_TIM_DMA_CC_INSTANCE(htim->Instance));

  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
      break;
    }

    case TIM_CHANNEL_2:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
      break;
    }

    case TIM_CHANNEL_3:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC3);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
      break;
    }

    case TIM_CHANNEL_4:
    {

      __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC4);
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    __HAL_TIM_DISABLE(htim);

    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode)
{

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_OPM_MODE(OnePulseMode));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->OnePulse_MspInitCallback == NULL)
    {
      htim->OnePulse_MspInitCallback = HAL_TIM_OnePulse_MspInit;
    }

    htim->OnePulse_MspInitCallback(htim);
#else

    HAL_TIM_OnePulse_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  TIM_Base_SetConfig(htim->Instance, &htim->Init);

  htim->Instance->CR1 &= ~TIM_CR1_OPM;

  htim->Instance->CR1 |= OnePulseMode;

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->OnePulse_MspDeInitCallback == NULL)
  {
    htim->OnePulse_MspDeInitCallback = HAL_TIM_OnePulse_MspDeInit;
  }

  htim->OnePulse_MspDeInitCallback(htim);
#else

  HAL_TIM_OnePulse_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
  HAL_TIM_ChannelStateTypeDef channel_1_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef channel_2_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_2);
  HAL_TIM_ChannelStateTypeDef complementary_channel_1_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef complementary_channel_2_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_2);

  UNUSED(OutputChannel);

  if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
      || (channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);

  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{

  UNUSED(OutputChannel);

  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_DISABLE(htim);
  }

  __HAL_TIM_DISABLE(htim);

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{
  HAL_TIM_ChannelStateTypeDef channel_1_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef channel_2_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_2);
  HAL_TIM_ChannelStateTypeDef complementary_channel_1_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef complementary_channel_2_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_2);

  UNUSED(OutputChannel);

  if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
      || (channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
      || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
  {
    return HAL_ERROR;
  }

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);

  __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);

  __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);

  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_ENABLE(htim);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel)
{

  UNUSED(OutputChannel);

  __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);

  __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);

  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
  TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {

    __HAL_TIM_MOE_DISABLE(htim);
  }

  __HAL_TIM_DISABLE(htim);

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim, const TIM_Encoder_InitTypeDef *sConfig)
{
  uint32_t tmpsmcr;
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  if (htim == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));
  assert_param(IS_TIM_COUNTER_MODE(htim->Init.CounterMode));
  assert_param(IS_TIM_CLOCKDIVISION_DIV(htim->Init.ClockDivision));
  assert_param(IS_TIM_AUTORELOAD_PRELOAD(htim->Init.AutoReloadPreload));
  assert_param(IS_TIM_ENCODER_MODE(sConfig->EncoderMode));
  assert_param(IS_TIM_IC_SELECTION(sConfig->IC1Selection));
  assert_param(IS_TIM_IC_SELECTION(sConfig->IC2Selection));
  assert_param(IS_TIM_ENCODERINPUT_POLARITY(sConfig->IC1Polarity));
  assert_param(IS_TIM_ENCODERINPUT_POLARITY(sConfig->IC2Polarity));
  assert_param(IS_TIM_IC_PRESCALER(sConfig->IC1Prescaler));
  assert_param(IS_TIM_IC_PRESCALER(sConfig->IC2Prescaler));
  assert_param(IS_TIM_IC_FILTER(sConfig->IC1Filter));
  assert_param(IS_TIM_IC_FILTER(sConfig->IC2Filter));
  assert_param(IS_TIM_PERIOD(htim, htim->Init.Period));

  if (htim->State == HAL_TIM_STATE_RESET)
  {

    htim->Lock = HAL_UNLOCKED;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

    TIM_ResetCallback(htim);

    if (htim->Encoder_MspInitCallback == NULL)
    {
      htim->Encoder_MspInitCallback = HAL_TIM_Encoder_MspInit;
    }

    htim->Encoder_MspInitCallback(htim);
#else

    HAL_TIM_Encoder_MspInit(htim);
#endif
  }

  htim->State = HAL_TIM_STATE_BUSY;

  htim->Instance->SMCR &= ~(TIM_SMCR_SMS | TIM_SMCR_ECE);

  TIM_Base_SetConfig(htim->Instance, &htim->Init);

  tmpsmcr = htim->Instance->SMCR;

  tmpccmr1 = htim->Instance->CCMR1;

  tmpccer = htim->Instance->CCER;

  tmpsmcr |= sConfig->EncoderMode;

  tmpccmr1 &= ~(TIM_CCMR1_CC1S | TIM_CCMR1_CC2S);
  tmpccmr1 |= (sConfig->IC1Selection | (sConfig->IC2Selection << 8U));

  tmpccmr1 &= ~(TIM_CCMR1_IC1PSC | TIM_CCMR1_IC2PSC);
  tmpccmr1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);
  tmpccmr1 |= sConfig->IC1Prescaler | (sConfig->IC2Prescaler << 8U);
  tmpccmr1 |= (sConfig->IC1Filter << 4U) | (sConfig->IC2Filter << 12U);

  tmpccer &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
  tmpccer &= ~(TIM_CCER_CC1NP | TIM_CCER_CC2NP);
  tmpccer |= sConfig->IC1Polarity | (sConfig->IC2Polarity << 4U);

  htim->Instance->SMCR = tmpsmcr;

  htim->Instance->CCMR1 = tmpccmr1;

  htim->Instance->CCER = tmpccer;

  htim->DMABurstState = HAL_DMA_BURST_STATE_READY;

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);

  htim->State = HAL_TIM_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));

  htim->State = HAL_TIM_STATE_BUSY;

  __HAL_TIM_DISABLE(htim);

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  if (htim->Encoder_MspDeInitCallback == NULL)
  {
    htim->Encoder_MspDeInitCallback = HAL_TIM_Encoder_MspDeInit;
  }

  htim->Encoder_MspDeInitCallback(htim);
#else

  HAL_TIM_Encoder_MspDeInit(htim);
#endif

  htim->DMABurstState = HAL_DMA_BURST_STATE_RESET;

  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_RESET);
  TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_RESET);

  htim->State = HAL_TIM_STATE_RESET;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

__weak void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_TIM_ChannelStateTypeDef channel_1_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef channel_2_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_2);
  HAL_TIM_ChannelStateTypeDef complementary_channel_1_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef complementary_channel_2_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_2);

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  if (Channel == TIM_CHANNEL_1)
  {
    if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else if (Channel == TIM_CHANNEL_2)
  {
    if ((channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
      break;
    }

    case TIM_CHANNEL_2:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
      break;
    }

    default :
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
      break;
    }
  }

  __HAL_TIM_ENABLE(htim);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
      break;
    }

    case TIM_CHANNEL_2:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
      break;
    }

    default :
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
      break;
    }
  }

  __HAL_TIM_DISABLE(htim);

  if ((Channel == TIM_CHANNEL_1) || (Channel == TIM_CHANNEL_2))
  {
    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }
  else
  {
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  HAL_TIM_ChannelStateTypeDef channel_1_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef channel_2_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_2);
  HAL_TIM_ChannelStateTypeDef complementary_channel_1_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef complementary_channel_2_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_2);

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  if (Channel == TIM_CHANNEL_1)
  {
    if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else if (Channel == TIM_CHANNEL_2)
  {
    if ((channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }
  else
  {
    if ((channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (channel_2_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_1_state != HAL_TIM_CHANNEL_STATE_READY)
        || (complementary_channel_2_state != HAL_TIM_CHANNEL_STATE_READY))
    {
      return HAL_ERROR;
    }
    else
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
    }
  }

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
      break;
    }

    case TIM_CHANNEL_2:
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
      break;
    }

    default :
    {
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC1);
      __HAL_TIM_ENABLE_IT(htim, TIM_IT_CC2);
      break;
    }
  }

  __HAL_TIM_ENABLE(htim);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  if (Channel == TIM_CHANNEL_1)
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
  }
  else if (Channel == TIM_CHANNEL_2)
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
  }
  else
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
    __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
  }

  __HAL_TIM_DISABLE(htim);

  if ((Channel == TIM_CHANNEL_1) || (Channel == TIM_CHANNEL_2))
  {
    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }
  else
  {
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length)
{
  HAL_TIM_ChannelStateTypeDef channel_1_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef channel_2_state = TIM_CHANNEL_STATE_GET(htim, TIM_CHANNEL_2);
  HAL_TIM_ChannelStateTypeDef complementary_channel_1_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_1);
  HAL_TIM_ChannelStateTypeDef complementary_channel_2_state = TIM_CHANNEL_N_STATE_GET(htim, TIM_CHANNEL_2);

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  if (Channel == TIM_CHANNEL_1)
  {
    if ((channel_1_state == HAL_TIM_CHANNEL_STATE_BUSY)
        || (complementary_channel_1_state == HAL_TIM_CHANNEL_STATE_BUSY))
    {
      return HAL_BUSY;
    }
    else if ((channel_1_state == HAL_TIM_CHANNEL_STATE_READY)
             && (complementary_channel_1_state == HAL_TIM_CHANNEL_STATE_READY))
    {
      if ((pData1 == NULL) || (Length == 0U))
      {
        return HAL_ERROR;
      }
      else
      {
        TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
        TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
      }
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else if (Channel == TIM_CHANNEL_2)
  {
    if ((channel_2_state == HAL_TIM_CHANNEL_STATE_BUSY)
        || (complementary_channel_2_state == HAL_TIM_CHANNEL_STATE_BUSY))
    {
      return HAL_BUSY;
    }
    else if ((channel_2_state == HAL_TIM_CHANNEL_STATE_READY)
             && (complementary_channel_2_state == HAL_TIM_CHANNEL_STATE_READY))
    {
      if ((pData2 == NULL) || (Length == 0U))
      {
        return HAL_ERROR;
      }
      else
      {
        TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
        TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      }
    }
    else
    {
      return HAL_ERROR;
    }
  }
  else
  {
    if ((channel_1_state == HAL_TIM_CHANNEL_STATE_BUSY)
        || (channel_2_state == HAL_TIM_CHANNEL_STATE_BUSY)
        || (complementary_channel_1_state == HAL_TIM_CHANNEL_STATE_BUSY)
        || (complementary_channel_2_state == HAL_TIM_CHANNEL_STATE_BUSY))
    {
      return HAL_BUSY;
    }
    else if ((channel_1_state == HAL_TIM_CHANNEL_STATE_READY)
             && (channel_2_state == HAL_TIM_CHANNEL_STATE_READY)
             && (complementary_channel_1_state == HAL_TIM_CHANNEL_STATE_READY)
             && (complementary_channel_2_state == HAL_TIM_CHANNEL_STATE_READY))
    {
      if ((((pData1 == NULL) || (pData2 == NULL))) || (Length == 0U))
      {
        return HAL_ERROR;
      }
      else
      {
        TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
        TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
        TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_BUSY);
        TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_BUSY);
      }
    }
    else
    {
      return HAL_ERROR;
    }
  }

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&htim->Instance->CCR1, (uint32_t)pData1,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);

      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);

      __HAL_TIM_ENABLE(htim);

      break;
    }

    case TIM_CHANNEL_2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)&htim->Instance->CCR2, (uint32_t)pData2,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);

      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

      __HAL_TIM_ENABLE(htim);

      break;
    }

    default:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&htim->Instance->CCR1, (uint32_t)pData1,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)&htim->Instance->CCR2, (uint32_t)pData2,
                           Length) != HAL_OK)
      {

        return HAL_ERROR;
      }

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC1);

      __HAL_TIM_ENABLE_DMA(htim, TIM_DMA_CC2);

      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
      TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);

      __HAL_TIM_ENABLE(htim);

      break;
    }
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel)
{

  assert_param(IS_TIM_ENCODER_INTERFACE_INSTANCE(htim->Instance));

  if (Channel == TIM_CHANNEL_1)
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
  }
  else if (Channel == TIM_CHANNEL_2)
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
  }
  else
  {
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
    TIM_CCxChannelCmd(htim->Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);

    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC1);
    __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_CC2);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
    (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
  }

  __HAL_TIM_DISABLE(htim);

  if ((Channel == TIM_CHANNEL_1) || (Channel == TIM_CHANNEL_2))
  {
    TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);
  }
  else
  {
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  }

  return HAL_OK;
}

void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
  uint32_t itsource = htim->Instance->DIER;
  uint32_t itflag   = htim->Instance->SR;

  if ((itflag & (TIM_FLAG_CC1)) == (TIM_FLAG_CC1))
  {
    if ((itsource & (TIM_IT_CC1)) == (TIM_IT_CC1))
    {
      {
        __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC1);
        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

        if ((htim->Instance->CCMR1 & TIM_CCMR1_CC1S) != 0x00U)
        {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
          htim->IC_CaptureCallback(htim);
#else
          HAL_TIM_IC_CaptureCallback(htim);
#endif
        }

        else
        {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
          htim->OC_DelayElapsedCallback(htim);
          htim->PWM_PulseFinishedCallback(htim);
#else
          HAL_TIM_OC_DelayElapsedCallback(htim);
          HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif
        }
        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
      }
    }
  }

  if ((itflag & (TIM_FLAG_CC2)) == (TIM_FLAG_CC2))
  {
    if ((itsource & (TIM_IT_CC2)) == (TIM_IT_CC2))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC2);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;

      if ((htim->Instance->CCMR1 & TIM_CCMR1_CC2S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
        HAL_TIM_IC_CaptureCallback(htim);
#endif
      }

      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }

  if ((itflag & (TIM_FLAG_CC3)) == (TIM_FLAG_CC3))
  {
    if ((itsource & (TIM_IT_CC3)) == (TIM_IT_CC3))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC3);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;

      if ((htim->Instance->CCMR2 & TIM_CCMR2_CC3S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
        HAL_TIM_IC_CaptureCallback(htim);
#endif
      }

      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }

  if ((itflag & (TIM_FLAG_CC4)) == (TIM_FLAG_CC4))
  {
    if ((itsource & (TIM_IT_CC4)) == (TIM_IT_CC4))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_CC4);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;

      if ((htim->Instance->CCMR2 & TIM_CCMR2_CC4S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
        HAL_TIM_IC_CaptureCallback(htim);
#endif
      }

      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }

  if ((itflag & (TIM_FLAG_UPDATE)) == (TIM_FLAG_UPDATE))
  {
    if ((itsource & (TIM_IT_UPDATE)) == (TIM_IT_UPDATE))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->PeriodElapsedCallback(htim);
#else
      HAL_TIM_PeriodElapsedCallback(htim);
#endif
    }
  }

  if ((itflag & (TIM_FLAG_BREAK)) == (TIM_FLAG_BREAK))
  {
    if ((itsource & (TIM_IT_BREAK)) == (TIM_IT_BREAK))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_BREAK);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->BreakCallback(htim);
#else
      HAL_TIMEx_BreakCallback(htim);
#endif
    }
  }

  if ((itflag & (TIM_FLAG_TRIGGER)) == (TIM_FLAG_TRIGGER))
  {
    if ((itsource & (TIM_IT_TRIGGER)) == (TIM_IT_TRIGGER))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_TRIGGER);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->TriggerCallback(htim);
#else
      HAL_TIM_TriggerCallback(htim);
#endif
    }
  }

  if ((itflag & (TIM_FLAG_COM)) == (TIM_FLAG_COM))
  {
    if ((itsource & (TIM_IT_COM)) == (TIM_IT_COM))
    {
      __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_COM);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->CommutationCallback(htim);
#else
      HAL_TIMEx_CommutCallback(htim);
#endif
    }
  }
}

HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim,
                                           const TIM_OC_InitTypeDef *sConfig,
                                           uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CHANNELS(Channel));
  assert_param(IS_TIM_OC_MODE(sConfig->OCMode));
  assert_param(IS_TIM_OC_POLARITY(sConfig->OCPolarity));

  __HAL_LOCK(htim);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

      TIM_OC1_SetConfig(htim->Instance, sConfig);
      break;
    }

    case TIM_CHANNEL_2:
    {

      assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

      TIM_OC2_SetConfig(htim->Instance, sConfig);
      break;
    }

    case TIM_CHANNEL_3:
    {

      assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

      TIM_OC3_SetConfig(htim->Instance, sConfig);
      break;
    }

    case TIM_CHANNEL_4:
    {

      assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

      TIM_OC4_SetConfig(htim->Instance, sConfig);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  __HAL_UNLOCK(htim);

  return status;
}

HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_IC_InitTypeDef *sConfig, uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
  assert_param(IS_TIM_IC_POLARITY(sConfig->ICPolarity));
  assert_param(IS_TIM_IC_SELECTION(sConfig->ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(sConfig->ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(sConfig->ICFilter));

  __HAL_LOCK(htim);

  if (Channel == TIM_CHANNEL_1)
  {

    TIM_TI1_SetConfig(htim->Instance,
                      sConfig->ICPolarity,
                      sConfig->ICSelection,
                      sConfig->ICFilter);

    htim->Instance->CCMR1 &= ~TIM_CCMR1_IC1PSC;

    htim->Instance->CCMR1 |= sConfig->ICPrescaler;
  }
  else if (Channel == TIM_CHANNEL_2)
  {

    assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

    TIM_TI2_SetConfig(htim->Instance,
                      sConfig->ICPolarity,
                      sConfig->ICSelection,
                      sConfig->ICFilter);

    htim->Instance->CCMR1 &= ~TIM_CCMR1_IC2PSC;

    htim->Instance->CCMR1 |= (sConfig->ICPrescaler << 8U);
  }
  else if (Channel == TIM_CHANNEL_3)
  {

    assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

    TIM_TI3_SetConfig(htim->Instance,
                      sConfig->ICPolarity,
                      sConfig->ICSelection,
                      sConfig->ICFilter);

    htim->Instance->CCMR2 &= ~TIM_CCMR2_IC3PSC;

    htim->Instance->CCMR2 |= sConfig->ICPrescaler;
  }
  else if (Channel == TIM_CHANNEL_4)
  {

    assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

    TIM_TI4_SetConfig(htim->Instance,
                      sConfig->ICPolarity,
                      sConfig->ICSelection,
                      sConfig->ICFilter);

    htim->Instance->CCMR2 &= ~TIM_CCMR2_IC4PSC;

    htim->Instance->CCMR2 |= (sConfig->ICPrescaler << 8U);
  }
  else
  {
    status = HAL_ERROR;
  }

  __HAL_UNLOCK(htim);

  return status;
}

HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim,
                                            const TIM_OC_InitTypeDef *sConfig,
                                            uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_CHANNELS(Channel));
  assert_param(IS_TIM_PWM_MODE(sConfig->OCMode));
  assert_param(IS_TIM_OC_POLARITY(sConfig->OCPolarity));
  assert_param(IS_TIM_FAST_STATE(sConfig->OCFastMode));

  __HAL_LOCK(htim);

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

      TIM_OC1_SetConfig(htim->Instance, sConfig);

      htim->Instance->CCMR1 |= TIM_CCMR1_OC1PE;

      htim->Instance->CCMR1 &= ~TIM_CCMR1_OC1FE;
      htim->Instance->CCMR1 |= sConfig->OCFastMode;
      break;
    }

    case TIM_CHANNEL_2:
    {

      assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

      TIM_OC2_SetConfig(htim->Instance, sConfig);

      htim->Instance->CCMR1 |= TIM_CCMR1_OC2PE;

      htim->Instance->CCMR1 &= ~TIM_CCMR1_OC2FE;
      htim->Instance->CCMR1 |= sConfig->OCFastMode << 8U;
      break;
    }

    case TIM_CHANNEL_3:
    {

      assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

      TIM_OC3_SetConfig(htim->Instance, sConfig);

      htim->Instance->CCMR2 |= TIM_CCMR2_OC3PE;

      htim->Instance->CCMR2 &= ~TIM_CCMR2_OC3FE;
      htim->Instance->CCMR2 |= sConfig->OCFastMode;
      break;
    }

    case TIM_CHANNEL_4:
    {

      assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

      TIM_OC4_SetConfig(htim->Instance, sConfig);

      htim->Instance->CCMR2 |= TIM_CCMR2_OC4PE;

      htim->Instance->CCMR2 &= ~TIM_CCMR2_OC4FE;
      htim->Instance->CCMR2 |= sConfig->OCFastMode << 8U;
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  __HAL_UNLOCK(htim);

  return status;
}

HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim,  TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel)
{
  HAL_StatusTypeDef status = HAL_OK;
  TIM_OC_InitTypeDef temp1;

  assert_param(IS_TIM_OPM_CHANNELS(OutputChannel));
  assert_param(IS_TIM_OPM_CHANNELS(InputChannel));

  if (OutputChannel != InputChannel)
  {

    __HAL_LOCK(htim);

    htim->State = HAL_TIM_STATE_BUSY;

    temp1.OCMode = sConfig->OCMode;
    temp1.Pulse = sConfig->Pulse;
    temp1.OCPolarity = sConfig->OCPolarity;
    temp1.OCNPolarity = sConfig->OCNPolarity;
    temp1.OCIdleState = sConfig->OCIdleState;
    temp1.OCNIdleState = sConfig->OCNIdleState;

    switch (OutputChannel)
    {
      case TIM_CHANNEL_1:
      {
        assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

        TIM_OC1_SetConfig(htim->Instance, &temp1);
        break;
      }

      case TIM_CHANNEL_2:
      {
        assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

        TIM_OC2_SetConfig(htim->Instance, &temp1);
        break;
      }

      default:
        status = HAL_ERROR;
        break;
    }

    if (status == HAL_OK)
    {
      switch (InputChannel)
      {
        case TIM_CHANNEL_1:
        {
          assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

          TIM_TI1_SetConfig(htim->Instance, sConfig->ICPolarity,
                            sConfig->ICSelection, sConfig->ICFilter);

          htim->Instance->CCMR1 &= ~TIM_CCMR1_IC1PSC;

          htim->Instance->SMCR &= ~TIM_SMCR_TS;
          htim->Instance->SMCR |= TIM_TS_TI1FP1;

          htim->Instance->SMCR &= ~TIM_SMCR_SMS;
          htim->Instance->SMCR |= TIM_SLAVEMODE_TRIGGER;
          break;
        }

        case TIM_CHANNEL_2:
        {
          assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

          TIM_TI2_SetConfig(htim->Instance, sConfig->ICPolarity,
                            sConfig->ICSelection, sConfig->ICFilter);

          htim->Instance->CCMR1 &= ~TIM_CCMR1_IC2PSC;

          htim->Instance->SMCR &= ~TIM_SMCR_TS;
          htim->Instance->SMCR |= TIM_TS_TI2FP2;

          htim->Instance->SMCR &= ~TIM_SMCR_SMS;
          htim->Instance->SMCR |= TIM_SLAVEMODE_TRIGGER;
          break;
        }

        default:
          status = HAL_ERROR;
          break;
      }
    }

    htim->State = HAL_TIM_STATE_READY;

    __HAL_UNLOCK(htim);

    return status;
  }
  else
  {
    return HAL_ERROR;
  }
}

HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                              uint32_t  BurstLength)
{
  HAL_StatusTypeDef status;

  status = HAL_TIM_DMABurst_MultiWriteStart(htim, BurstBaseAddress, BurstRequestSrc, BurstBuffer, BurstLength,
                                            ((BurstLength) >> 8U) + 1U);

  return status;
}

HAL_StatusTypeDef HAL_TIM_DMABurst_MultiWriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                   uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                                   uint32_t  BurstLength,  uint32_t  DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_DMABURST_INSTANCE(htim->Instance));
  assert_param(IS_TIM_DMA_BASE(BurstBaseAddress));
  assert_param(IS_TIM_DMA_SOURCE(BurstRequestSrc));
  assert_param(IS_TIM_DMA_LENGTH(BurstLength));
  assert_param(IS_TIM_DMA_DATA_LENGTH(DataLength));

  if (htim->DMABurstState == HAL_DMA_BURST_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (htim->DMABurstState == HAL_DMA_BURST_STATE_READY)
  {
    if ((BurstBuffer == NULL) && (BurstLength > 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      htim->DMABurstState = HAL_DMA_BURST_STATE_BUSY;
    }
  }
  else
  {

  }

  switch (BurstRequestSrc)
  {
    case TIM_DMA_UPDATE:
    {

      htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;
      htim->hdma[TIM_DMA_ID_UPDATE]->XferHalfCpltCallback = TIM_DMAPeriodElapsedHalfCplt;

      htim->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_UPDATE], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC3:
    {

      htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC4:
    {

      htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMADelayPulseCplt;
      htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMADelayPulseHalfCplt;

      htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_COM:
    {

      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferCpltCallback =  TIMEx_DMACommutationCplt;
      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferHalfCpltCallback =  TIMEx_DMACommutationHalfCplt;

      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_COMMUTATION], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_TRIGGER:
    {

      htim->hdma[TIM_DMA_ID_TRIGGER]->XferCpltCallback = TIM_DMATriggerCplt;
      htim->hdma[TIM_DMA_ID_TRIGGER]->XferHalfCpltCallback = TIM_DMATriggerHalfCplt;

      htim->hdma[TIM_DMA_ID_TRIGGER]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_TRIGGER], (uint32_t)BurstBuffer,
                           (uint32_t)&htim->Instance->DMAR, DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    htim->Instance->DCR = (BurstBaseAddress | BurstLength);

    __HAL_TIM_ENABLE_DMA(htim, BurstRequestSrc);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_DMA_SOURCE(BurstRequestSrc));

  switch (BurstRequestSrc)
  {
    case TIM_DMA_UPDATE:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_UPDATE]);
      break;
    }
    case TIM_DMA_CC1:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
      break;
    }
    case TIM_DMA_CC2:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
      break;
    }
    case TIM_DMA_CC3:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
      break;
    }
    case TIM_DMA_CC4:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
      break;
    }
    case TIM_DMA_COM:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_COMMUTATION]);
      break;
    }
    case TIM_DMA_TRIGGER:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_TRIGGER]);
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    __HAL_TIM_DISABLE_DMA(htim, BurstRequestSrc);

    htim->DMABurstState = HAL_DMA_BURST_STATE_READY;
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength)
{
  HAL_StatusTypeDef status;

  status = HAL_TIM_DMABurst_MultiReadStart(htim, BurstBaseAddress, BurstRequestSrc, BurstBuffer, BurstLength,
                                           ((BurstLength) >> 8U) + 1U);

  return status;
}

HAL_StatusTypeDef HAL_TIM_DMABurst_MultiReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                  uint32_t BurstRequestSrc, uint32_t  *BurstBuffer,
                                                  uint32_t  BurstLength, uint32_t  DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_DMABURST_INSTANCE(htim->Instance));
  assert_param(IS_TIM_DMA_BASE(BurstBaseAddress));
  assert_param(IS_TIM_DMA_SOURCE(BurstRequestSrc));
  assert_param(IS_TIM_DMA_LENGTH(BurstLength));
  assert_param(IS_TIM_DMA_DATA_LENGTH(DataLength));

  if (htim->DMABurstState == HAL_DMA_BURST_STATE_BUSY)
  {
    return HAL_BUSY;
  }
  else if (htim->DMABurstState == HAL_DMA_BURST_STATE_READY)
  {
    if ((BurstBuffer == NULL) && (BurstLength > 0U))
    {
      return HAL_ERROR;
    }
    else
    {
      htim->DMABurstState = HAL_DMA_BURST_STATE_BUSY;
    }
  }
  else
  {

  }
  switch (BurstRequestSrc)
  {
    case TIM_DMA_UPDATE:
    {

      htim->hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;
      htim->hdma[TIM_DMA_ID_UPDATE]->XferHalfCpltCallback = TIM_DMAPeriodElapsedHalfCplt;

      htim->hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_UPDATE], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC1:
    {

      htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC2:
    {

      htim->hdma[TIM_DMA_ID_CC2]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC2]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC2]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC2], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC3:
    {

      htim->hdma[TIM_DMA_ID_CC3]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC3]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC3]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC3], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_CC4:
    {

      htim->hdma[TIM_DMA_ID_CC4]->XferCpltCallback = TIM_DMACaptureCplt;
      htim->hdma[TIM_DMA_ID_CC4]->XferHalfCpltCallback = TIM_DMACaptureHalfCplt;

      htim->hdma[TIM_DMA_ID_CC4]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC4], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_COM:
    {

      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferCpltCallback =  TIMEx_DMACommutationCplt;
      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferHalfCpltCallback =  TIMEx_DMACommutationHalfCplt;

      htim->hdma[TIM_DMA_ID_COMMUTATION]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_COMMUTATION], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    case TIM_DMA_TRIGGER:
    {

      htim->hdma[TIM_DMA_ID_TRIGGER]->XferCpltCallback = TIM_DMATriggerCplt;
      htim->hdma[TIM_DMA_ID_TRIGGER]->XferHalfCpltCallback = TIM_DMATriggerHalfCplt;

      htim->hdma[TIM_DMA_ID_TRIGGER]->XferErrorCallback = TIM_DMAError ;

      if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_TRIGGER], (uint32_t)&htim->Instance->DMAR, (uint32_t)BurstBuffer,
                           DataLength) != HAL_OK)
      {

        return HAL_ERROR;
      }
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    htim->Instance->DCR = (BurstBaseAddress | BurstLength);

    __HAL_TIM_ENABLE_DMA(htim, BurstRequestSrc);
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_DMA_SOURCE(BurstRequestSrc));

  switch (BurstRequestSrc)
  {
    case TIM_DMA_UPDATE:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_UPDATE]);
      break;
    }
    case TIM_DMA_CC1:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC1]);
      break;
    }
    case TIM_DMA_CC2:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC2]);
      break;
    }
    case TIM_DMA_CC3:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC3]);
      break;
    }
    case TIM_DMA_CC4:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_CC4]);
      break;
    }
    case TIM_DMA_COM:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_COMMUTATION]);
      break;
    }
    case TIM_DMA_TRIGGER:
    {
      (void)HAL_DMA_Abort_IT(htim->hdma[TIM_DMA_ID_TRIGGER]);
      break;
    }
    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {

    __HAL_TIM_DISABLE_DMA(htim, BurstRequestSrc);

    htim->DMABurstState = HAL_DMA_BURST_STATE_READY;
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource)
{

  assert_param(IS_TIM_INSTANCE(htim->Instance));
  assert_param(IS_TIM_EVENT_SOURCE(EventSource));

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  htim->Instance->EGR = EventSource;

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           const TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_TIM_OCXREF_CLEAR_INSTANCE(htim->Instance));
  assert_param(IS_TIM_CLEARINPUT_SOURCE(sClearInputConfig->ClearInputSource));

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  switch (sClearInputConfig->ClearInputSource)
  {
    case TIM_CLEARINPUTSOURCE_NONE:
    {

      CLEAR_BIT(htim->Instance->SMCR, (TIM_SMCR_ETF | TIM_SMCR_ETPS | TIM_SMCR_ECE | TIM_SMCR_ETP));
      break;
    }

    case TIM_CLEARINPUTSOURCE_ETR:
    {

      assert_param(IS_TIM_CLEARINPUT_POLARITY(sClearInputConfig->ClearInputPolarity));
      assert_param(IS_TIM_CLEARINPUT_PRESCALER(sClearInputConfig->ClearInputPrescaler));
      assert_param(IS_TIM_CLEARINPUT_FILTER(sClearInputConfig->ClearInputFilter));

      if (sClearInputConfig->ClearInputPrescaler != TIM_CLEARINPUTPRESCALER_DIV1)
      {
        htim->State = HAL_TIM_STATE_READY;
        __HAL_UNLOCK(htim);
        return HAL_ERROR;
      }

      TIM_ETR_SetConfig(htim->Instance,
                        sClearInputConfig->ClearInputPrescaler,
                        sClearInputConfig->ClearInputPolarity,
                        sClearInputConfig->ClearInputFilter);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  if (status == HAL_OK)
  {
    switch (Channel)
    {
      case TIM_CHANNEL_1:
      {
        if (sClearInputConfig->ClearInputState != (uint32_t)DISABLE)
        {

          SET_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC1CE);
        }
        else
        {

          CLEAR_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC1CE);
        }
        break;
      }
      case TIM_CHANNEL_2:
      {
        if (sClearInputConfig->ClearInputState != (uint32_t)DISABLE)
        {

          SET_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC2CE);
        }
        else
        {

          CLEAR_BIT(htim->Instance->CCMR1, TIM_CCMR1_OC2CE);
        }
        break;
      }
      case TIM_CHANNEL_3:
      {
        if (sClearInputConfig->ClearInputState != (uint32_t)DISABLE)
        {

          SET_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC3CE);
        }
        else
        {

          CLEAR_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC3CE);
        }
        break;
      }
      case TIM_CHANNEL_4:
      {
        if (sClearInputConfig->ClearInputState != (uint32_t)DISABLE)
        {

          SET_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC4CE);
        }
        else
        {

          CLEAR_BIT(htim->Instance->CCMR2, TIM_CCMR2_OC4CE);
        }
        break;
      }
      default:
        break;
    }
  }

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return status;
}

HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, const TIM_ClockConfigTypeDef *sClockSourceConfig)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  assert_param(IS_TIM_CLOCKSOURCE(sClockSourceConfig->ClockSource));

  tmpsmcr = htim->Instance->SMCR;
  tmpsmcr &= ~(TIM_SMCR_SMS | TIM_SMCR_TS);
  tmpsmcr &= ~(TIM_SMCR_ETF | TIM_SMCR_ETPS | TIM_SMCR_ECE | TIM_SMCR_ETP);
  htim->Instance->SMCR = tmpsmcr;

  switch (sClockSourceConfig->ClockSource)
  {
    case TIM_CLOCKSOURCE_INTERNAL:
    {
      assert_param(IS_TIM_INSTANCE(htim->Instance));
      break;
    }

    case TIM_CLOCKSOURCE_ETRMODE1:
    {

      assert_param(IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(htim->Instance));

      assert_param(IS_TIM_CLOCKPRESCALER(sClockSourceConfig->ClockPrescaler));
      assert_param(IS_TIM_CLOCKPOLARITY(sClockSourceConfig->ClockPolarity));
      assert_param(IS_TIM_CLOCKFILTER(sClockSourceConfig->ClockFilter));

      TIM_ETR_SetConfig(htim->Instance,
                        sClockSourceConfig->ClockPrescaler,
                        sClockSourceConfig->ClockPolarity,
                        sClockSourceConfig->ClockFilter);

      tmpsmcr = htim->Instance->SMCR;
      tmpsmcr |= (TIM_SLAVEMODE_EXTERNAL1 | TIM_CLOCKSOURCE_ETRMODE1);

      htim->Instance->SMCR = tmpsmcr;
      break;
    }

    case TIM_CLOCKSOURCE_ETRMODE2:
    {

      assert_param(IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(htim->Instance));

      assert_param(IS_TIM_CLOCKPRESCALER(sClockSourceConfig->ClockPrescaler));
      assert_param(IS_TIM_CLOCKPOLARITY(sClockSourceConfig->ClockPolarity));
      assert_param(IS_TIM_CLOCKFILTER(sClockSourceConfig->ClockFilter));

      TIM_ETR_SetConfig(htim->Instance,
                        sClockSourceConfig->ClockPrescaler,
                        sClockSourceConfig->ClockPolarity,
                        sClockSourceConfig->ClockFilter);

      htim->Instance->SMCR |= TIM_SMCR_ECE;
      break;
    }

    case TIM_CLOCKSOURCE_TI1:
    {

      assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

      assert_param(IS_TIM_CLOCKPOLARITY(sClockSourceConfig->ClockPolarity));
      assert_param(IS_TIM_CLOCKFILTER(sClockSourceConfig->ClockFilter));

      TIM_TI1_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter);
      TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI1);
      break;
    }

    case TIM_CLOCKSOURCE_TI2:
    {

      assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

      assert_param(IS_TIM_CLOCKPOLARITY(sClockSourceConfig->ClockPolarity));
      assert_param(IS_TIM_CLOCKFILTER(sClockSourceConfig->ClockFilter));

      TIM_TI2_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter);
      TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI2);
      break;
    }

    case TIM_CLOCKSOURCE_TI1ED:
    {

      assert_param(IS_TIM_CLOCKSOURCE_TIX_INSTANCE(htim->Instance));

      assert_param(IS_TIM_CLOCKPOLARITY(sClockSourceConfig->ClockPolarity));
      assert_param(IS_TIM_CLOCKFILTER(sClockSourceConfig->ClockFilter));

      TIM_TI1_ConfigInputStage(htim->Instance,
                               sClockSourceConfig->ClockPolarity,
                               sClockSourceConfig->ClockFilter);
      TIM_ITRx_SetConfig(htim->Instance, TIM_CLOCKSOURCE_TI1ED);
      break;
    }

    case TIM_CLOCKSOURCE_ITR0:
    case TIM_CLOCKSOURCE_ITR1:
    case TIM_CLOCKSOURCE_ITR2:
    case TIM_CLOCKSOURCE_ITR3:
    {

      assert_param(IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(htim->Instance));

      TIM_ITRx_SetConfig(htim->Instance, sClockSourceConfig->ClockSource);
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }
  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return status;
}

HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection)
{
  uint32_t tmpcr2;

  assert_param(IS_TIM_XOR_INSTANCE(htim->Instance));
  assert_param(IS_TIM_TI1SELECTION(TI1_Selection));

  tmpcr2 = htim->Instance->CR2;

  tmpcr2 &= ~TIM_CR2_TI1S;

  tmpcr2 |= TI1_Selection;

  htim->Instance->CR2 = tmpcr2;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig)
{

  assert_param(IS_TIM_SLAVE_INSTANCE(htim->Instance));
  assert_param(IS_TIM_SLAVE_MODE(sSlaveConfig->SlaveMode));
  assert_param(IS_TIM_TRIGGER_SELECTION(sSlaveConfig->InputTrigger));

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  if (TIM_SlaveTimer_SetConfig(htim, sSlaveConfig) != HAL_OK)
  {
    htim->State = HAL_TIM_STATE_READY;
    __HAL_UNLOCK(htim);
    return HAL_ERROR;
  }

  __HAL_TIM_DISABLE_IT(htim, TIM_IT_TRIGGER);

  __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_TRIGGER);

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim,
                                                const TIM_SlaveConfigTypeDef *sSlaveConfig)
{

  assert_param(IS_TIM_SLAVE_INSTANCE(htim->Instance));
  assert_param(IS_TIM_SLAVE_MODE(sSlaveConfig->SlaveMode));
  assert_param(IS_TIM_TRIGGER_SELECTION(sSlaveConfig->InputTrigger));

  __HAL_LOCK(htim);

  htim->State = HAL_TIM_STATE_BUSY;

  if (TIM_SlaveTimer_SetConfig(htim, sSlaveConfig) != HAL_OK)
  {
    htim->State = HAL_TIM_STATE_READY;
    __HAL_UNLOCK(htim);
    return HAL_ERROR;
  }

  __HAL_TIM_ENABLE_IT(htim, TIM_IT_TRIGGER);

  __HAL_TIM_DISABLE_DMA(htim, TIM_DMA_TRIGGER);

  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

uint32_t HAL_TIM_ReadCapturedValue(const TIM_HandleTypeDef *htim, uint32_t Channel)
{
  uint32_t tmpreg = 0U;

  switch (Channel)
  {
    case TIM_CHANNEL_1:
    {

      assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));

      tmpreg =  htim->Instance->CCR1;

      break;
    }
    case TIM_CHANNEL_2:
    {

      assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));

      tmpreg =   htim->Instance->CCR2;

      break;
    }

    case TIM_CHANNEL_3:
    {

      assert_param(IS_TIM_CC3_INSTANCE(htim->Instance));

      tmpreg =   htim->Instance->CCR3;

      break;
    }

    case TIM_CHANNEL_4:
    {

      assert_param(IS_TIM_CC4_INSTANCE(htim->Instance));

      tmpreg =   htim->Instance->CCR4;

      break;
    }

    default:
      break;
  }

  return tmpreg;
}

__weak void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

__weak void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim)
{

  UNUSED(htim);

}

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

HAL_StatusTypeDef HAL_TIM_RegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID,
                                           pTIM_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    return HAL_ERROR;
  }

  if (htim->State == HAL_TIM_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_TIM_BASE_MSPINIT_CB_ID :
        htim->Base_MspInitCallback                 = pCallback;
        break;

      case HAL_TIM_BASE_MSPDEINIT_CB_ID :
        htim->Base_MspDeInitCallback               = pCallback;
        break;

      case HAL_TIM_IC_MSPINIT_CB_ID :
        htim->IC_MspInitCallback                   = pCallback;
        break;

      case HAL_TIM_IC_MSPDEINIT_CB_ID :
        htim->IC_MspDeInitCallback                 = pCallback;
        break;

      case HAL_TIM_OC_MSPINIT_CB_ID :
        htim->OC_MspInitCallback                   = pCallback;
        break;

      case HAL_TIM_OC_MSPDEINIT_CB_ID :
        htim->OC_MspDeInitCallback                 = pCallback;
        break;

      case HAL_TIM_PWM_MSPINIT_CB_ID :
        htim->PWM_MspInitCallback                  = pCallback;
        break;

      case HAL_TIM_PWM_MSPDEINIT_CB_ID :
        htim->PWM_MspDeInitCallback                = pCallback;
        break;

      case HAL_TIM_ONE_PULSE_MSPINIT_CB_ID :
        htim->OnePulse_MspInitCallback             = pCallback;
        break;

      case HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID :
        htim->OnePulse_MspDeInitCallback           = pCallback;
        break;

      case HAL_TIM_ENCODER_MSPINIT_CB_ID :
        htim->Encoder_MspInitCallback              = pCallback;
        break;

      case HAL_TIM_ENCODER_MSPDEINIT_CB_ID :
        htim->Encoder_MspDeInitCallback            = pCallback;
        break;

      case HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID :
        htim->HallSensor_MspInitCallback           = pCallback;
        break;

      case HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID :
        htim->HallSensor_MspDeInitCallback         = pCallback;
        break;

      case HAL_TIM_PERIOD_ELAPSED_CB_ID :
        htim->PeriodElapsedCallback                = pCallback;
        break;

      case HAL_TIM_PERIOD_ELAPSED_HALF_CB_ID :
        htim->PeriodElapsedHalfCpltCallback        = pCallback;
        break;

      case HAL_TIM_TRIGGER_CB_ID :
        htim->TriggerCallback                      = pCallback;
        break;

      case HAL_TIM_TRIGGER_HALF_CB_ID :
        htim->TriggerHalfCpltCallback              = pCallback;
        break;

      case HAL_TIM_IC_CAPTURE_CB_ID :
        htim->IC_CaptureCallback                   = pCallback;
        break;

      case HAL_TIM_IC_CAPTURE_HALF_CB_ID :
        htim->IC_CaptureHalfCpltCallback           = pCallback;
        break;

      case HAL_TIM_OC_DELAY_ELAPSED_CB_ID :
        htim->OC_DelayElapsedCallback              = pCallback;
        break;

      case HAL_TIM_PWM_PULSE_FINISHED_CB_ID :
        htim->PWM_PulseFinishedCallback            = pCallback;
        break;

      case HAL_TIM_PWM_PULSE_FINISHED_HALF_CB_ID :
        htim->PWM_PulseFinishedHalfCpltCallback    = pCallback;
        break;

      case HAL_TIM_ERROR_CB_ID :
        htim->ErrorCallback                        = pCallback;
        break;

      case HAL_TIM_COMMUTATION_CB_ID :
        htim->CommutationCallback                  = pCallback;
        break;

      case HAL_TIM_COMMUTATION_HALF_CB_ID :
        htim->CommutationHalfCpltCallback          = pCallback;
        break;

      case HAL_TIM_BREAK_CB_ID :
        htim->BreakCallback                        = pCallback;
        break;

      default :

        status = HAL_ERROR;
        break;
    }
  }
  else if (htim->State == HAL_TIM_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_TIM_BASE_MSPINIT_CB_ID :
        htim->Base_MspInitCallback         = pCallback;
        break;

      case HAL_TIM_BASE_MSPDEINIT_CB_ID :
        htim->Base_MspDeInitCallback       = pCallback;
        break;

      case HAL_TIM_IC_MSPINIT_CB_ID :
        htim->IC_MspInitCallback           = pCallback;
        break;

      case HAL_TIM_IC_MSPDEINIT_CB_ID :
        htim->IC_MspDeInitCallback         = pCallback;
        break;

      case HAL_TIM_OC_MSPINIT_CB_ID :
        htim->OC_MspInitCallback           = pCallback;
        break;

      case HAL_TIM_OC_MSPDEINIT_CB_ID :
        htim->OC_MspDeInitCallback         = pCallback;
        break;

      case HAL_TIM_PWM_MSPINIT_CB_ID :
        htim->PWM_MspInitCallback          = pCallback;
        break;

      case HAL_TIM_PWM_MSPDEINIT_CB_ID :
        htim->PWM_MspDeInitCallback        = pCallback;
        break;

      case HAL_TIM_ONE_PULSE_MSPINIT_CB_ID :
        htim->OnePulse_MspInitCallback     = pCallback;
        break;

      case HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID :
        htim->OnePulse_MspDeInitCallback   = pCallback;
        break;

      case HAL_TIM_ENCODER_MSPINIT_CB_ID :
        htim->Encoder_MspInitCallback      = pCallback;
        break;

      case HAL_TIM_ENCODER_MSPDEINIT_CB_ID :
        htim->Encoder_MspDeInitCallback    = pCallback;
        break;

      case HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID :
        htim->HallSensor_MspInitCallback   = pCallback;
        break;

      case HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID :
        htim->HallSensor_MspDeInitCallback = pCallback;
        break;

      default :

        status = HAL_ERROR;
        break;
    }
  }
  else
  {

    status = HAL_ERROR;
  }

  return status;
}

HAL_StatusTypeDef HAL_TIM_UnRegisterCallback(TIM_HandleTypeDef *htim, HAL_TIM_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (htim->State == HAL_TIM_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_TIM_BASE_MSPINIT_CB_ID :

        htim->Base_MspInitCallback              = HAL_TIM_Base_MspInit;
        break;

      case HAL_TIM_BASE_MSPDEINIT_CB_ID :

        htim->Base_MspDeInitCallback            = HAL_TIM_Base_MspDeInit;
        break;

      case HAL_TIM_IC_MSPINIT_CB_ID :

        htim->IC_MspInitCallback                = HAL_TIM_IC_MspInit;
        break;

      case HAL_TIM_IC_MSPDEINIT_CB_ID :

        htim->IC_MspDeInitCallback              = HAL_TIM_IC_MspDeInit;
        break;

      case HAL_TIM_OC_MSPINIT_CB_ID :

        htim->OC_MspInitCallback                = HAL_TIM_OC_MspInit;
        break;

      case HAL_TIM_OC_MSPDEINIT_CB_ID :

        htim->OC_MspDeInitCallback              = HAL_TIM_OC_MspDeInit;
        break;

      case HAL_TIM_PWM_MSPINIT_CB_ID :

        htim->PWM_MspInitCallback               = HAL_TIM_PWM_MspInit;
        break;

      case HAL_TIM_PWM_MSPDEINIT_CB_ID :

        htim->PWM_MspDeInitCallback             = HAL_TIM_PWM_MspDeInit;
        break;

      case HAL_TIM_ONE_PULSE_MSPINIT_CB_ID :

        htim->OnePulse_MspInitCallback          = HAL_TIM_OnePulse_MspInit;
        break;

      case HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID :

        htim->OnePulse_MspDeInitCallback        = HAL_TIM_OnePulse_MspDeInit;
        break;

      case HAL_TIM_ENCODER_MSPINIT_CB_ID :

        htim->Encoder_MspInitCallback           = HAL_TIM_Encoder_MspInit;
        break;

      case HAL_TIM_ENCODER_MSPDEINIT_CB_ID :

        htim->Encoder_MspDeInitCallback         = HAL_TIM_Encoder_MspDeInit;
        break;

      case HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID :

        htim->HallSensor_MspInitCallback        = HAL_TIMEx_HallSensor_MspInit;
        break;

      case HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID :

        htim->HallSensor_MspDeInitCallback      = HAL_TIMEx_HallSensor_MspDeInit;
        break;

      case HAL_TIM_PERIOD_ELAPSED_CB_ID :

        htim->PeriodElapsedCallback             = HAL_TIM_PeriodElapsedCallback;
        break;

      case HAL_TIM_PERIOD_ELAPSED_HALF_CB_ID :

        htim->PeriodElapsedHalfCpltCallback     = HAL_TIM_PeriodElapsedHalfCpltCallback;
        break;

      case HAL_TIM_TRIGGER_CB_ID :

        htim->TriggerCallback                   = HAL_TIM_TriggerCallback;
        break;

      case HAL_TIM_TRIGGER_HALF_CB_ID :

        htim->TriggerHalfCpltCallback           = HAL_TIM_TriggerHalfCpltCallback;
        break;

      case HAL_TIM_IC_CAPTURE_CB_ID :

        htim->IC_CaptureCallback                = HAL_TIM_IC_CaptureCallback;
        break;

      case HAL_TIM_IC_CAPTURE_HALF_CB_ID :

        htim->IC_CaptureHalfCpltCallback        = HAL_TIM_IC_CaptureHalfCpltCallback;
        break;

      case HAL_TIM_OC_DELAY_ELAPSED_CB_ID :

        htim->OC_DelayElapsedCallback           = HAL_TIM_OC_DelayElapsedCallback;
        break;

      case HAL_TIM_PWM_PULSE_FINISHED_CB_ID :

        htim->PWM_PulseFinishedCallback         = HAL_TIM_PWM_PulseFinishedCallback;
        break;

      case HAL_TIM_PWM_PULSE_FINISHED_HALF_CB_ID :

        htim->PWM_PulseFinishedHalfCpltCallback = HAL_TIM_PWM_PulseFinishedHalfCpltCallback;
        break;

      case HAL_TIM_ERROR_CB_ID :

        htim->ErrorCallback                     = HAL_TIM_ErrorCallback;
        break;

      case HAL_TIM_COMMUTATION_CB_ID :

        htim->CommutationCallback               = HAL_TIMEx_CommutCallback;
        break;

      case HAL_TIM_COMMUTATION_HALF_CB_ID :

        htim->CommutationHalfCpltCallback       = HAL_TIMEx_CommutHalfCpltCallback;
        break;

      case HAL_TIM_BREAK_CB_ID :

        htim->BreakCallback                     = HAL_TIMEx_BreakCallback;
        break;

      default :

        status = HAL_ERROR;
        break;
    }
  }
  else if (htim->State == HAL_TIM_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_TIM_BASE_MSPINIT_CB_ID :

        htim->Base_MspInitCallback         = HAL_TIM_Base_MspInit;
        break;

      case HAL_TIM_BASE_MSPDEINIT_CB_ID :

        htim->Base_MspDeInitCallback       = HAL_TIM_Base_MspDeInit;
        break;

      case HAL_TIM_IC_MSPINIT_CB_ID :

        htim->IC_MspInitCallback           = HAL_TIM_IC_MspInit;
        break;

      case HAL_TIM_IC_MSPDEINIT_CB_ID :

        htim->IC_MspDeInitCallback         = HAL_TIM_IC_MspDeInit;
        break;

      case HAL_TIM_OC_MSPINIT_CB_ID :

        htim->OC_MspInitCallback           = HAL_TIM_OC_MspInit;
        break;

      case HAL_TIM_OC_MSPDEINIT_CB_ID :

        htim->OC_MspDeInitCallback         = HAL_TIM_OC_MspDeInit;
        break;

      case HAL_TIM_PWM_MSPINIT_CB_ID :

        htim->PWM_MspInitCallback          = HAL_TIM_PWM_MspInit;
        break;

      case HAL_TIM_PWM_MSPDEINIT_CB_ID :

        htim->PWM_MspDeInitCallback        = HAL_TIM_PWM_MspDeInit;
        break;

      case HAL_TIM_ONE_PULSE_MSPINIT_CB_ID :

        htim->OnePulse_MspInitCallback     = HAL_TIM_OnePulse_MspInit;
        break;

      case HAL_TIM_ONE_PULSE_MSPDEINIT_CB_ID :

        htim->OnePulse_MspDeInitCallback   = HAL_TIM_OnePulse_MspDeInit;
        break;

      case HAL_TIM_ENCODER_MSPINIT_CB_ID :

        htim->Encoder_MspInitCallback      = HAL_TIM_Encoder_MspInit;
        break;

      case HAL_TIM_ENCODER_MSPDEINIT_CB_ID :

        htim->Encoder_MspDeInitCallback    = HAL_TIM_Encoder_MspDeInit;
        break;

      case HAL_TIM_HALL_SENSOR_MSPINIT_CB_ID :

        htim->HallSensor_MspInitCallback   = HAL_TIMEx_HallSensor_MspInit;
        break;

      case HAL_TIM_HALL_SENSOR_MSPDEINIT_CB_ID :

        htim->HallSensor_MspDeInitCallback = HAL_TIMEx_HallSensor_MspDeInit;
        break;

      default :

        status = HAL_ERROR;
        break;
    }
  }
  else
  {

    status = HAL_ERROR;
  }

  return status;
}
#endif

HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(const TIM_HandleTypeDef *htim)
{
  return htim->State;
}

HAL_TIM_ActiveChannel HAL_TIM_GetActiveChannel(const TIM_HandleTypeDef *htim)
{
  return htim->Channel;
}

HAL_TIM_ChannelStateTypeDef HAL_TIM_GetChannelState(const TIM_HandleTypeDef *htim,  uint32_t Channel)
{
  HAL_TIM_ChannelStateTypeDef channel_state;

  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  channel_state = TIM_CHANNEL_STATE_GET(htim, Channel);

  return channel_state;
}

HAL_TIM_DMABurstStateTypeDef HAL_TIM_DMABurstState(const TIM_HandleTypeDef *htim)
{

  assert_param(IS_TIM_DMABURST_INSTANCE(htim->Instance));

  return htim->DMABurstState;
}

void TIM_DMAError(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdma == htim->hdma[TIM_DMA_ID_CC1])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC2])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC3])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_READY);
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC4])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;
    TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_READY);
  }
  else
  {
    htim->State = HAL_TIM_STATE_READY;
  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->ErrorCallback(htim);
#else
  HAL_TIM_ErrorCallback(htim);
#endif

  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

static void TIM_DMADelayPulseCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdma == htim->hdma[TIM_DMA_ID_CC1])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC2])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC3])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC4])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else
  {

  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PWM_PulseFinishedCallback(htim);
#else
  HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif

  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdma == htim->hdma[TIM_DMA_ID_CC1])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC2])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC3])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC4])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;
  }
  else
  {

  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PWM_PulseFinishedHalfCpltCallback(htim);
#else
  HAL_TIM_PWM_PulseFinishedHalfCpltCallback(htim);
#endif

  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdma == htim->hdma[TIM_DMA_ID_CC1])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_1, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC2])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_2, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC3])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_READY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_3, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC4])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;

    if (hdma->Init.Mode == DMA_NORMAL)
    {
      TIM_CHANNEL_STATE_SET(htim, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_READY);
      TIM_CHANNEL_N_STATE_SET(htim, TIM_CHANNEL_4, HAL_TIM_CHANNEL_STATE_READY);
    }
  }
  else
  {

  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->IC_CaptureCallback(htim);
#else
  HAL_TIM_IC_CaptureCallback(htim);
#endif

  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdma == htim->hdma[TIM_DMA_ID_CC1])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC2])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC3])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;
  }
  else if (hdma == htim->hdma[TIM_DMA_ID_CC4])
  {
    htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;
  }
  else
  {

  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->IC_CaptureHalfCpltCallback(htim);
#else
  HAL_TIM_IC_CaptureHalfCpltCallback(htim);
#endif

  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

static void TIM_DMAPeriodElapsedCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (htim->hdma[TIM_DMA_ID_UPDATE]->Init.Mode == DMA_NORMAL)
  {
    htim->State = HAL_TIM_STATE_READY;
  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PeriodElapsedCallback(htim);
#else
  HAL_TIM_PeriodElapsedCallback(htim);
#endif
}

static void TIM_DMAPeriodElapsedHalfCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PeriodElapsedHalfCpltCallback(htim);
#else
  HAL_TIM_PeriodElapsedHalfCpltCallback(htim);
#endif
}

static void TIM_DMATriggerCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (htim->hdma[TIM_DMA_ID_TRIGGER]->Init.Mode == DMA_NORMAL)
  {
    htim->State = HAL_TIM_STATE_READY;
  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->TriggerCallback(htim);
#else
  HAL_TIM_TriggerCallback(htim);
#endif
}

static void TIM_DMATriggerHalfCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->TriggerHalfCpltCallback(htim);
#else
  HAL_TIM_TriggerHalfCpltCallback(htim);
#endif
}

void TIM_Base_SetConfig(TIM_TypeDef *TIMx, const TIM_Base_InitTypeDef *Structure)
{
  uint32_t tmpcr1;
  tmpcr1 = TIMx->CR1;

  if (IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx))
  {

    tmpcr1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
    tmpcr1 |= Structure->CounterMode;
  }

  if (IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx))
  {

    tmpcr1 &= ~TIM_CR1_CKD;
    tmpcr1 |= (uint32_t)Structure->ClockDivision;
  }

  MODIFY_REG(tmpcr1, TIM_CR1_ARPE, Structure->AutoReloadPreload);

  TIMx->ARR = (uint32_t)Structure->Period ;

  TIMx->PSC = Structure->Prescaler;

  if (IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx))
  {

    TIMx->RCR = Structure->RepetitionCounter;
  }

  SET_BIT(TIMx->CR1, TIM_CR1_URS);

  TIMx->EGR = TIM_EGR_UG;

  TIMx->CR1 = tmpcr1;
}

static void TIM_OC1_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config)
{
  uint32_t tmpccmrx;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  tmpccer = TIMx->CCER;

  TIMx->CCER &= ~TIM_CCER_CC1E;

  tmpcr2 =  TIMx->CR2;

  tmpccmrx = TIMx->CCMR1;

  tmpccmrx &= ~TIM_CCMR1_OC1M;
  tmpccmrx &= ~TIM_CCMR1_CC1S;

  tmpccmrx |= OC_Config->OCMode;

  tmpccer &= ~TIM_CCER_CC1P;

  tmpccer |= OC_Config->OCPolarity;

  if (IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_1))
  {

    assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

    tmpccer &= ~TIM_CCER_CC1NP;

    tmpccer |= OC_Config->OCNPolarity;

    tmpccer &= ~TIM_CCER_CC1NE;
  }

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {

    assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

    tmpcr2 &= ~TIM_CR2_OIS1;
    tmpcr2 &= ~TIM_CR2_OIS1N;

    tmpcr2 |= OC_Config->OCIdleState;

    tmpcr2 |= OC_Config->OCNIdleState;
  }

  TIMx->CR2 = tmpcr2;

  TIMx->CCMR1 = tmpccmrx;

  TIMx->CCR1 = OC_Config->Pulse;

  TIMx->CCER = tmpccer;
}

void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config)
{
  uint32_t tmpccmrx;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  tmpccer = TIMx->CCER;

  TIMx->CCER &= ~TIM_CCER_CC2E;

  tmpcr2 =  TIMx->CR2;

  tmpccmrx = TIMx->CCMR1;

  tmpccmrx &= ~TIM_CCMR1_OC2M;
  tmpccmrx &= ~TIM_CCMR1_CC2S;

  tmpccmrx |= (OC_Config->OCMode << 8U);

  tmpccer &= ~TIM_CCER_CC2P;

  tmpccer |= (OC_Config->OCPolarity << 4U);

  if (IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_2))
  {
    assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

    tmpccer &= ~TIM_CCER_CC2NP;

    tmpccer |= (OC_Config->OCNPolarity << 4U);

    tmpccer &= ~TIM_CCER_CC2NE;
  }

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {

    assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

    tmpcr2 &= ~TIM_CR2_OIS2;
    tmpcr2 &= ~TIM_CR2_OIS2N;

    tmpcr2 |= (OC_Config->OCIdleState << 2U);

    tmpcr2 |= (OC_Config->OCNIdleState << 2U);
  }

  TIMx->CR2 = tmpcr2;

  TIMx->CCMR1 = tmpccmrx;

  TIMx->CCR2 = OC_Config->Pulse;

  TIMx->CCER = tmpccer;
}

static void TIM_OC3_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config)
{
  uint32_t tmpccmrx;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  tmpccer = TIMx->CCER;

  TIMx->CCER &= ~TIM_CCER_CC3E;

  tmpcr2 =  TIMx->CR2;

  tmpccmrx = TIMx->CCMR2;

  tmpccmrx &= ~TIM_CCMR2_OC3M;
  tmpccmrx &= ~TIM_CCMR2_CC3S;

  tmpccmrx |= OC_Config->OCMode;

  tmpccer &= ~TIM_CCER_CC3P;

  tmpccer |= (OC_Config->OCPolarity << 8U);

  if (IS_TIM_CCXN_INSTANCE(TIMx, TIM_CHANNEL_3))
  {
    assert_param(IS_TIM_OCN_POLARITY(OC_Config->OCNPolarity));

    tmpccer &= ~TIM_CCER_CC3NP;

    tmpccer |= (OC_Config->OCNPolarity << 8U);

    tmpccer &= ~TIM_CCER_CC3NE;
  }

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {

    assert_param(IS_TIM_OCNIDLE_STATE(OC_Config->OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

    tmpcr2 &= ~TIM_CR2_OIS3;
    tmpcr2 &= ~TIM_CR2_OIS3N;

    tmpcr2 |= (OC_Config->OCIdleState << 4U);

    tmpcr2 |= (OC_Config->OCNIdleState << 4U);
  }

  TIMx->CR2 = tmpcr2;

  TIMx->CCMR2 = tmpccmrx;

  TIMx->CCR3 = OC_Config->Pulse;

  TIMx->CCER = tmpccer;
}

static void TIM_OC4_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config)
{
  uint32_t tmpccmrx;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  tmpccer = TIMx->CCER;

  TIMx->CCER &= ~TIM_CCER_CC4E;

  tmpcr2 =  TIMx->CR2;

  tmpccmrx = TIMx->CCMR2;

  tmpccmrx &= ~TIM_CCMR2_OC4M;
  tmpccmrx &= ~TIM_CCMR2_CC4S;

  tmpccmrx |= (OC_Config->OCMode << 8U);

  tmpccer &= ~TIM_CCER_CC4P;

  tmpccer |= (OC_Config->OCPolarity << 12U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {

    assert_param(IS_TIM_OCIDLE_STATE(OC_Config->OCIdleState));

    tmpcr2 &= ~TIM_CR2_OIS4;

    tmpcr2 |= (OC_Config->OCIdleState << 6U);
  }

  TIMx->CR2 = tmpcr2;

  TIMx->CCMR2 = tmpccmrx;

  TIMx->CCR4 = OC_Config->Pulse;

  TIMx->CCER = tmpccer;
}

static HAL_StatusTypeDef TIM_SlaveTimer_SetConfig(TIM_HandleTypeDef *htim,
                                                  const TIM_SlaveConfigTypeDef *sSlaveConfig)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmpsmcr;
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  tmpsmcr = htim->Instance->SMCR;

  tmpsmcr &= ~TIM_SMCR_TS;

  tmpsmcr |= sSlaveConfig->InputTrigger;

  tmpsmcr &= ~TIM_SMCR_SMS;

  tmpsmcr |= sSlaveConfig->SlaveMode;

  htim->Instance->SMCR = tmpsmcr;

  switch (sSlaveConfig->InputTrigger)
  {
    case TIM_TS_ETRF:
    {

      assert_param(IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(htim->Instance));
      assert_param(IS_TIM_TRIGGERPRESCALER(sSlaveConfig->TriggerPrescaler));
      assert_param(IS_TIM_TRIGGERPOLARITY(sSlaveConfig->TriggerPolarity));
      assert_param(IS_TIM_TRIGGERFILTER(sSlaveConfig->TriggerFilter));

      TIM_ETR_SetConfig(htim->Instance,
                        sSlaveConfig->TriggerPrescaler,
                        sSlaveConfig->TriggerPolarity,
                        sSlaveConfig->TriggerFilter);
      break;
    }

    case TIM_TS_TI1F_ED:
    {

      assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
      assert_param(IS_TIM_TRIGGERFILTER(sSlaveConfig->TriggerFilter));

      if (sSlaveConfig->SlaveMode == TIM_SLAVEMODE_GATED)
      {
        return HAL_ERROR;
      }

      tmpccer = htim->Instance->CCER;
      htim->Instance->CCER &= ~TIM_CCER_CC1E;
      tmpccmr1 = htim->Instance->CCMR1;

      tmpccmr1 &= ~TIM_CCMR1_IC1F;
      tmpccmr1 |= ((sSlaveConfig->TriggerFilter) << 4U);

      htim->Instance->CCMR1 = tmpccmr1;
      htim->Instance->CCER = tmpccer;
      break;
    }

    case TIM_TS_TI1FP1:
    {

      assert_param(IS_TIM_CC1_INSTANCE(htim->Instance));
      assert_param(IS_TIM_TRIGGERPOLARITY(sSlaveConfig->TriggerPolarity));
      assert_param(IS_TIM_TRIGGERFILTER(sSlaveConfig->TriggerFilter));

      TIM_TI1_ConfigInputStage(htim->Instance,
                               sSlaveConfig->TriggerPolarity,
                               sSlaveConfig->TriggerFilter);
      break;
    }

    case TIM_TS_TI2FP2:
    {

      assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
      assert_param(IS_TIM_TRIGGERPOLARITY(sSlaveConfig->TriggerPolarity));
      assert_param(IS_TIM_TRIGGERFILTER(sSlaveConfig->TriggerFilter));

      TIM_TI2_ConfigInputStage(htim->Instance,
                               sSlaveConfig->TriggerPolarity,
                               sSlaveConfig->TriggerFilter);
      break;
    }

    case TIM_TS_ITR0:
    case TIM_TS_ITR1:
    case TIM_TS_ITR2:
    case TIM_TS_ITR3:
    {

      assert_param(IS_TIM_CC2_INSTANCE(htim->Instance));
      break;
    }

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                       uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC1E;
  tmpccmr1 = TIMx->CCMR1;

  if (IS_TIM_CC2_INSTANCE(TIMx) != RESET)
  {
    tmpccmr1 &= ~TIM_CCMR1_CC1S;
    tmpccmr1 |= TIM_ICSelection;
  }
  else
  {
    tmpccmr1 |= TIM_CCMR1_CC1S_0;
  }

  tmpccmr1 &= ~TIM_CCMR1_IC1F;
  tmpccmr1 |= ((TIM_ICFilter << 4U) & TIM_CCMR1_IC1F);

  tmpccer &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
  tmpccer |= (TIM_ICPolarity & (TIM_CCER_CC1P | TIM_CCER_CC1NP));

  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

static void TIM_TI1_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC1E;
  tmpccmr1 = TIMx->CCMR1;

  tmpccmr1 &= ~TIM_CCMR1_IC1F;
  tmpccmr1 |= (TIM_ICFilter << 4U);

  tmpccer &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
  tmpccer |= TIM_ICPolarity;

  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

static void TIM_TI2_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC2E;
  tmpccmr1 = TIMx->CCMR1;

  tmpccmr1 &= ~TIM_CCMR1_CC2S;
  tmpccmr1 |= (TIM_ICSelection << 8U);

  tmpccmr1 &= ~TIM_CCMR1_IC2F;
  tmpccmr1 |= ((TIM_ICFilter << 12U) & TIM_CCMR1_IC2F);

  tmpccer &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
  tmpccer |= ((TIM_ICPolarity << 4U) & (TIM_CCER_CC2P | TIM_CCER_CC2NP));

  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

static void TIM_TI2_ConfigInputStage(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC2E;
  tmpccmr1 = TIMx->CCMR1;

  tmpccmr1 &= ~TIM_CCMR1_IC2F;
  tmpccmr1 |= (TIM_ICFilter << 12U);

  tmpccer &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
  tmpccer |= (TIM_ICPolarity << 4U);

  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

static void TIM_TI3_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr2;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC3E;
  tmpccmr2 = TIMx->CCMR2;

  tmpccmr2 &= ~TIM_CCMR2_CC3S;
  tmpccmr2 |= TIM_ICSelection;

  tmpccmr2 &= ~TIM_CCMR2_IC3F;
  tmpccmr2 |= ((TIM_ICFilter << 4U) & TIM_CCMR2_IC3F);

  tmpccer &= ~(TIM_CCER_CC3P | TIM_CCER_CC3NP);
  tmpccer |= ((TIM_ICPolarity << 8U) & (TIM_CCER_CC3P | TIM_CCER_CC3NP));

  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

static void TIM_TI4_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection,
                              uint32_t TIM_ICFilter)
{
  uint32_t tmpccmr2;
  uint32_t tmpccer;

  tmpccer = TIMx->CCER;
  TIMx->CCER &= ~TIM_CCER_CC4E;
  tmpccmr2 = TIMx->CCMR2;

  tmpccmr2 &= ~TIM_CCMR2_CC4S;
  tmpccmr2 |= (TIM_ICSelection << 8U);

  tmpccmr2 &= ~TIM_CCMR2_IC4F;
  tmpccmr2 |= ((TIM_ICFilter << 12U) & TIM_CCMR2_IC4F);

  tmpccer &= ~(TIM_CCER_CC4P | TIM_CCER_CC4NP);
  tmpccer |= ((TIM_ICPolarity << 12U) & (TIM_CCER_CC4P | TIM_CCER_CC4NP));

  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer ;
}

static void TIM_ITRx_SetConfig(TIM_TypeDef *TIMx, uint32_t InputTriggerSource)
{
  uint32_t tmpsmcr;

  tmpsmcr = TIMx->SMCR;

  tmpsmcr &= ~TIM_SMCR_TS;

  tmpsmcr |= (InputTriggerSource | TIM_SLAVEMODE_EXTERNAL1);

  TIMx->SMCR = tmpsmcr;
}

void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter)
{
  uint32_t tmpsmcr;

  tmpsmcr = TIMx->SMCR;

  tmpsmcr &= ~(TIM_SMCR_ETF | TIM_SMCR_ETPS | TIM_SMCR_ECE | TIM_SMCR_ETP);

  tmpsmcr |= (uint32_t)(TIM_ExtTRGPrescaler | (TIM_ExtTRGPolarity | (ExtTRGFilter << 8U)));

  TIMx->SMCR = tmpsmcr;
}

void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState)
{
  uint32_t tmp;

  assert_param(IS_TIM_CC1_INSTANCE(TIMx));
  assert_param(IS_TIM_CHANNELS(Channel));

  tmp = TIM_CCER_CC1E << (Channel & 0x1FU);

  TIMx->CCER &= ~tmp;

  TIMx->CCER |= (uint32_t)(ChannelState << (Channel & 0x1FU));
}

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)

void TIM_ResetCallback(TIM_HandleTypeDef *htim)
{

  htim->PeriodElapsedCallback             = HAL_TIM_PeriodElapsedCallback;
  htim->PeriodElapsedHalfCpltCallback     = HAL_TIM_PeriodElapsedHalfCpltCallback;
  htim->TriggerCallback                   = HAL_TIM_TriggerCallback;
  htim->TriggerHalfCpltCallback           = HAL_TIM_TriggerHalfCpltCallback;
  htim->IC_CaptureCallback                = HAL_TIM_IC_CaptureCallback;
  htim->IC_CaptureHalfCpltCallback        = HAL_TIM_IC_CaptureHalfCpltCallback;
  htim->OC_DelayElapsedCallback           = HAL_TIM_OC_DelayElapsedCallback;
  htim->PWM_PulseFinishedCallback         = HAL_TIM_PWM_PulseFinishedCallback;
  htim->PWM_PulseFinishedHalfCpltCallback = HAL_TIM_PWM_PulseFinishedHalfCpltCallback;
  htim->ErrorCallback                     = HAL_TIM_ErrorCallback;
  htim->CommutationCallback               = HAL_TIMEx_CommutCallback;
  htim->CommutationHalfCpltCallback       = HAL_TIMEx_CommutHalfCpltCallback;
  htim->BreakCallback                     = HAL_TIMEx_BreakCallback;
}
#endif

#endif
