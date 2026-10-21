#include "stm32f4xx_hal.h"

#ifdef HAL_UART_MODULE_ENABLED

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
void UART_InitCallbacksToDefault(UART_HandleTypeDef *huart);
#endif
static void UART_EndTxTransfer(UART_HandleTypeDef *huart);
static void UART_EndRxTransfer(UART_HandleTypeDef *huart);
static void UART_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void UART_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void UART_DMATxHalfCplt(DMA_HandleTypeDef *hdma);
static void UART_DMARxHalfCplt(DMA_HandleTypeDef *hdma);
static void UART_DMAError(DMA_HandleTypeDef *hdma);
static void UART_DMAAbortOnError(DMA_HandleTypeDef *hdma);
static void UART_DMATxAbortCallback(DMA_HandleTypeDef *hdma);
static void UART_DMARxAbortCallback(DMA_HandleTypeDef *hdma);
static void UART_DMATxOnlyAbortCallback(DMA_HandleTypeDef *hdma);
static void UART_DMARxOnlyAbortCallback(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef UART_EndTransmit_IT(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef UART_Receive_IT(UART_HandleTypeDef *huart);
static HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                                     uint32_t Tickstart, uint32_t Timeout);
static void UART_SetConfig(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart)
{

  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  if (huart->Init.HwFlowCtl != UART_HWCONTROL_NONE)
  {

    assert_param(IS_UART_HWFLOW_INSTANCE(huart->Instance));
    assert_param(IS_UART_HARDWARE_FLOW_CONTROL(huart->Init.HwFlowCtl));
  }
  else
  {
    assert_param(IS_UART_INSTANCE(huart->Instance));
  }
  assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_OVERSAMPLING(huart->Init.OverSampling));

  if (huart->gState == HAL_UART_STATE_RESET)
  {

    huart->Lock = HAL_UNLOCKED;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    UART_InitCallbacksToDefault(huart);

    if (huart->MspInitCallback == NULL)
    {
      huart->MspInitCallback = HAL_UART_MspInit;
    }

    huart->MspInitCallback(huart);
#else

    HAL_UART_MspInit(huart);
#endif
  }

  huart->gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(huart);

  UART_SetConfig(huart);

  CLEAR_BIT(huart->Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(huart->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

  __HAL_UART_ENABLE(huart);

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart)
{

  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_UART_HALFDUPLEX_INSTANCE(huart->Instance));
  assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_OVERSAMPLING(huart->Init.OverSampling));

  if (huart->gState == HAL_UART_STATE_RESET)
  {

    huart->Lock = HAL_UNLOCKED;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    UART_InitCallbacksToDefault(huart);

    if (huart->MspInitCallback == NULL)
    {
      huart->MspInitCallback = HAL_UART_MspInit;
    }

    huart->MspInitCallback(huart);
#else

    HAL_UART_MspInit(huart);
#endif
  }

  huart->gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(huart);

  UART_SetConfig(huart);

  CLEAR_BIT(huart->Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(huart->Instance->CR3, (USART_CR3_IREN | USART_CR3_SCEN));

  SET_BIT(huart->Instance->CR3, USART_CR3_HDSEL);

  __HAL_UART_ENABLE(huart);

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength)
{

  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_UART_LIN_INSTANCE(huart->Instance));

  assert_param(IS_UART_LIN_BREAK_DETECT_LENGTH(BreakDetectLength));
  assert_param(IS_UART_LIN_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_LIN_OVERSAMPLING(huart->Init.OverSampling));

  if (huart->gState == HAL_UART_STATE_RESET)
  {

    huart->Lock = HAL_UNLOCKED;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    UART_InitCallbacksToDefault(huart);

    if (huart->MspInitCallback == NULL)
    {
      huart->MspInitCallback = HAL_UART_MspInit;
    }

    huart->MspInitCallback(huart);
#else

    HAL_UART_MspInit(huart);
#endif
  }

  huart->gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(huart);

  UART_SetConfig(huart);

  CLEAR_BIT(huart->Instance->CR2, (USART_CR2_CLKEN));
  CLEAR_BIT(huart->Instance->CR3, (USART_CR3_HDSEL | USART_CR3_IREN | USART_CR3_SCEN));

  SET_BIT(huart->Instance->CR2, USART_CR2_LINEN);

  CLEAR_BIT(huart->Instance->CR2, USART_CR2_LBDL);
  SET_BIT(huart->Instance->CR2, BreakDetectLength);

  __HAL_UART_ENABLE(huart);

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod)
{

  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_UART_INSTANCE(huart->Instance));

  assert_param(IS_UART_WAKEUPMETHOD(WakeUpMethod));
  assert_param(IS_UART_ADDRESS(Address));
  assert_param(IS_UART_WORD_LENGTH(huart->Init.WordLength));
  assert_param(IS_UART_OVERSAMPLING(huart->Init.OverSampling));

  if (huart->gState == HAL_UART_STATE_RESET)
  {

    huart->Lock = HAL_UNLOCKED;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
    UART_InitCallbacksToDefault(huart);

    if (huart->MspInitCallback == NULL)
    {
      huart->MspInitCallback = HAL_UART_MspInit;
    }

    huart->MspInitCallback(huart);
#else

    HAL_UART_MspInit(huart);
#endif
  }

  huart->gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(huart);

  UART_SetConfig(huart);

  CLEAR_BIT(huart->Instance->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(huart->Instance->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));

  CLEAR_BIT(huart->Instance->CR2, USART_CR2_ADD);
  SET_BIT(huart->Instance->CR2, Address);

  CLEAR_BIT(huart->Instance->CR1, USART_CR1_WAKE);
  SET_BIT(huart->Instance->CR1, WakeUpMethod);

  __HAL_UART_ENABLE(huart);

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart)
{

  if (huart == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_UART_INSTANCE(huart->Instance));

  huart->gState = HAL_UART_STATE_BUSY;

  __HAL_UART_DISABLE(huart);

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
  if (huart->MspDeInitCallback == NULL)
  {
    huart->MspDeInitCallback = HAL_UART_MspDeInit;
  }

  huart->MspDeInitCallback(huart);
#else

  HAL_UART_MspDeInit(huart);
#endif

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->gState = HAL_UART_STATE_RESET;
  huart->RxState = HAL_UART_STATE_RESET;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

__weak void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

HAL_StatusTypeDef HAL_UART_RegisterCallback(UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID,
                                            pUART_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {

    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  if (huart->gState == HAL_UART_STATE_READY)
  {
    switch (CallbackID)
    {
      case HAL_UART_TX_HALFCOMPLETE_CB_ID :
        huart->TxHalfCpltCallback = pCallback;
        break;

      case HAL_UART_TX_COMPLETE_CB_ID :
        huart->TxCpltCallback = pCallback;
        break;

      case HAL_UART_RX_HALFCOMPLETE_CB_ID :
        huart->RxHalfCpltCallback = pCallback;
        break;

      case HAL_UART_RX_COMPLETE_CB_ID :
        huart->RxCpltCallback = pCallback;
        break;

      case HAL_UART_ERROR_CB_ID :
        huart->ErrorCallback = pCallback;
        break;

      case HAL_UART_ABORT_COMPLETE_CB_ID :
        huart->AbortCpltCallback = pCallback;
        break;

      case HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID :
        huart->AbortTransmitCpltCallback = pCallback;
        break;

      case HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID :
        huart->AbortReceiveCpltCallback = pCallback;
        break;

      case HAL_UART_MSPINIT_CB_ID :
        huart->MspInitCallback = pCallback;
        break;

      case HAL_UART_MSPDEINIT_CB_ID :
        huart->MspDeInitCallback = pCallback;
        break;

      default :

        huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else if (huart->gState == HAL_UART_STATE_RESET)
  {
    switch (CallbackID)
    {
      case HAL_UART_MSPINIT_CB_ID :
        huart->MspInitCallback = pCallback;
        break;

      case HAL_UART_MSPDEINIT_CB_ID :
        huart->MspDeInitCallback = pCallback;
        break;

      default :

        huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  return status;
}

HAL_StatusTypeDef HAL_UART_UnRegisterCallback(UART_HandleTypeDef *huart, HAL_UART_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (HAL_UART_STATE_READY == huart->gState)
  {
    switch (CallbackID)
    {
      case HAL_UART_TX_HALFCOMPLETE_CB_ID :
        huart->TxHalfCpltCallback = HAL_UART_TxHalfCpltCallback;
        break;

      case HAL_UART_TX_COMPLETE_CB_ID :
        huart->TxCpltCallback = HAL_UART_TxCpltCallback;
        break;

      case HAL_UART_RX_HALFCOMPLETE_CB_ID :
        huart->RxHalfCpltCallback = HAL_UART_RxHalfCpltCallback;
        break;

      case HAL_UART_RX_COMPLETE_CB_ID :
        huart->RxCpltCallback = HAL_UART_RxCpltCallback;
        break;

      case HAL_UART_ERROR_CB_ID :
        huart->ErrorCallback = HAL_UART_ErrorCallback;
        break;

      case HAL_UART_ABORT_COMPLETE_CB_ID :
        huart->AbortCpltCallback = HAL_UART_AbortCpltCallback;
        break;

      case HAL_UART_ABORT_TRANSMIT_COMPLETE_CB_ID :
        huart->AbortTransmitCpltCallback = HAL_UART_AbortTransmitCpltCallback;
        break;

      case HAL_UART_ABORT_RECEIVE_COMPLETE_CB_ID :
        huart->AbortReceiveCpltCallback = HAL_UART_AbortReceiveCpltCallback;
        break;

      case HAL_UART_MSPINIT_CB_ID :
        huart->MspInitCallback = HAL_UART_MspInit;
        break;

      case HAL_UART_MSPDEINIT_CB_ID :
        huart->MspDeInitCallback = HAL_UART_MspDeInit;
        break;

      default :

        huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_UART_STATE_RESET == huart->gState)
  {
    switch (CallbackID)
    {
      case HAL_UART_MSPINIT_CB_ID :
        huart->MspInitCallback = HAL_UART_MspInit;
        break;

      case HAL_UART_MSPDEINIT_CB_ID :
        huart->MspDeInitCallback = HAL_UART_MspDeInit;
        break;

      default :

        huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  return status;
}

HAL_StatusTypeDef HAL_UART_RegisterRxEventCallback(UART_HandleTypeDef *huart, pUART_RxEventCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {
    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  __HAL_LOCK(huart);

  if (huart->gState == HAL_UART_STATE_READY)
  {
    huart->RxEventCallback = pCallback;
  }
  else
  {
    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(huart);

  return status;
}

HAL_StatusTypeDef HAL_UART_UnRegisterRxEventCallback(UART_HandleTypeDef *huart)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(huart);

  if (huart->gState == HAL_UART_STATE_READY)
  {
    huart->RxEventCallback = HAL_UARTEx_RxEventCallback;
  }
  else
  {
    huart->ErrorCode |= HAL_UART_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(huart);
  return status;
}
#endif

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  const uint8_t  *pdata8bits;
  const uint16_t *pdata16bits;
  uint32_t tickstart = 0U;

  if (huart->gState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    tickstart = HAL_GetTick();

    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;
      pdata16bits = (const uint16_t *) pData;
    }
    else
    {
      pdata8bits  = pData;
      pdata16bits = NULL;
    }

    while (huart->TxXferCount > 0U)
    {
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)
      {
        huart->gState = HAL_UART_STATE_READY;

        return HAL_TIMEOUT;
      }
      if (pdata8bits == NULL)
      {
        huart->Instance->DR = (uint16_t)(*pdata16bits & 0x01FFU);
        pdata16bits++;
      }
      else
      {
        huart->Instance->DR = (uint8_t)(*pdata8bits & 0xFFU);
        pdata8bits++;
      }
      huart->TxXferCount--;
    }

    if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TC, RESET, tickstart, Timeout) != HAL_OK)
    {
      huart->gState = HAL_UART_STATE_READY;

      return HAL_TIMEOUT;
    }

    huart->gState = HAL_UART_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint8_t  *pdata8bits;
  uint16_t *pdata16bits;
  uint32_t tickstart = 0U;

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    tickstart = HAL_GetTick();

    huart->RxXferSize = Size;
    huart->RxXferCount = Size;

    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;
      pdata16bits = (uint16_t *) pData;
    }
    else
    {
      pdata8bits  = pData;
      pdata16bits = NULL;
    }

    while (huart->RxXferCount > 0U)
    {
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        huart->RxState = HAL_UART_STATE_READY;

        return HAL_TIMEOUT;
      }
      if (pdata8bits == NULL)
      {
        *pdata16bits = (uint16_t)(huart->Instance->DR & 0x01FF);
        pdata16bits++;
      }
      else
      {
        if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
        }
        else
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
        }
        pdata8bits++;
      }
      huart->RxXferCount--;
    }

    huart->RxState = HAL_UART_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{

  if (huart->gState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    __HAL_UART_ENABLE_IT(huart, UART_IT_TXE);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    return (UART_Start_Receive_IT(huart, pData, Size));
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
  const uint32_t *tmp;

  if (huart->gState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    huart->hdmatx->XferCpltCallback = UART_DMATransmitCplt;

    huart->hdmatx->XferHalfCpltCallback = UART_DMATxHalfCplt;

    huart->hdmatx->XferErrorCallback = UART_DMAError;

    huart->hdmatx->XferAbortCallback = NULL;

    tmp = (const uint32_t *)&pData;
    if (HAL_DMA_Start_IT(huart->hdmatx, *(const uint32_t *)tmp, (uint32_t)&huart->Instance->DR, Size) != HAL_OK)
    {

      huart->ErrorCode = HAL_UART_ERROR_DMA;

      huart->gState = HAL_UART_STATE_READY;

      return HAL_ERROR;
    }

    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);

    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    return (UART_Start_Receive_DMA(huart, pData, Size));
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart)
{
  uint32_t dmarequest = 0x00U;

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT);
  if ((huart->gState == HAL_UART_STATE_BUSY_TX) && dmarequest)
  {

    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);
  }

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
  if ((huart->RxState == HAL_UART_STATE_BUSY_RX) && dmarequest)
  {

    ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart)
{

  if (huart->gState == HAL_UART_STATE_BUSY_TX)
  {

    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAT);
  }

  if (huart->RxState == HAL_UART_STATE_BUSY_RX)
  {

    __HAL_UART_CLEAR_OREFLAG(huart);

    if (huart->Init.Parity != UART_PARITY_NONE)
    {
      ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_PEIE);
    }
    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart)
{
  uint32_t dmarequest = 0x00U;

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT);
  if ((huart->gState == HAL_UART_STATE_BUSY_TX) && dmarequest)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    if (huart->hdmatx != NULL)
    {
      HAL_DMA_Abort(huart->hdmatx);
    }
    UART_EndTxTransfer(huart);
  }

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
  if ((huart->RxState == HAL_UART_STATE_BUSY_RX) && dmarequest)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    if (huart->hdmarx != NULL)
    {
      HAL_DMA_Abort(huart->hdmarx);
    }
    UART_EndRxTransfer(huart);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout)
{
  uint8_t  *pdata8bits;
  uint16_t *pdata16bits;
  uint32_t tickstart;

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->RxState = HAL_UART_STATE_BUSY_RX;
    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType = HAL_UART_RXEVENT_TC;

    tickstart = HAL_GetTick();

    huart->RxXferSize  = Size;
    huart->RxXferCount = Size;

    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;
      pdata16bits = (uint16_t *) pData;
    }
    else
    {
      pdata8bits  = pData;
      pdata16bits = NULL;
    }

    *RxLen = 0U;

    while (huart->RxXferCount > 0U)
    {

      if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
      {

        __HAL_UART_CLEAR_IDLEFLAG(huart);

        if (*RxLen > 0U)
        {
          huart->RxEventType = HAL_UART_RXEVENT_IDLE;
          huart->RxState = HAL_UART_STATE_READY;

          return HAL_OK;
        }
      }

      if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE))
      {
        if (pdata8bits == NULL)
        {
          *pdata16bits = (uint16_t)(huart->Instance->DR & (uint16_t)0x01FF);
          pdata16bits++;
        }
        else
        {
          if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
          {
            *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
          }
          else
          {
            *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
          }

          pdata8bits++;
        }

        *RxLen += 1U;
        huart->RxXferCount--;
      }

      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          huart->RxState = HAL_UART_STATE_READY;

          return HAL_TIMEOUT;
        }
      }
    }

    *RxLen = huart->RxXferSize - huart->RxXferCount;

    huart->RxState = HAL_UART_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef status;

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType = HAL_UART_RXEVENT_TC;

    status =  UART_Start_Receive_IT(huart, pData, Size);

    if (status == HAL_OK)
    {
      if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
      {
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
      }
      else
      {

        status = HAL_ERROR;
      }
    }

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef status;

  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType = HAL_UART_RXEVENT_TC;

    status =  UART_Start_Receive_DMA(huart, pData, Size);

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
    {
      __HAL_UART_CLEAR_IDLEFLAG(huart);
      ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
    }
    else
    {

      status = HAL_ERROR;
    }

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_UART_RxEventTypeTypeDef HAL_UARTEx_GetRxEventType(UART_HandleTypeDef *huart)
{

  return(huart->RxEventType);
}

HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE));
  ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_IDLEIE));
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    if (huart->hdmatx != NULL)
    {

      huart->hdmatx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(huart->hdmatx) != HAL_OK)
      {
        if (HAL_DMA_GetError(huart->hdmatx) == HAL_DMA_ERROR_TIMEOUT)
        {

          huart->ErrorCode = HAL_UART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    if (huart->hdmarx != NULL)
    {

      huart->hdmarx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(huart->hdmarx) != HAL_OK)
      {
        if (HAL_DMA_GetError(huart->hdmarx) == HAL_DMA_ERROR_TIMEOUT)
        {

          huart->ErrorCode = HAL_UART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  huart->TxXferCount = 0x00U;
  huart->RxXferCount = 0x00U;

  huart->ErrorCode = HAL_UART_ERROR_NONE;

  huart->RxState = HAL_UART_STATE_READY;
  huart->gState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    if (huart->hdmatx != NULL)
    {

      huart->hdmatx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(huart->hdmatx) != HAL_OK)
      {
        if (HAL_DMA_GetError(huart->hdmatx) == HAL_DMA_ERROR_TIMEOUT)
        {

          huart->ErrorCode = HAL_UART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  huart->TxXferCount = 0x00U;

  huart->gState = HAL_UART_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
  ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_IDLEIE));
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    if (huart->hdmarx != NULL)
    {

      huart->hdmarx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(huart->hdmarx) != HAL_OK)
      {
        if (HAL_DMA_GetError(huart->hdmarx) == HAL_DMA_ERROR_TIMEOUT)
        {

          huart->ErrorCode = HAL_UART_ERROR_DMA;

          return HAL_TIMEOUT;
        }
      }
    }
  }

  huart->RxXferCount = 0x00U;

  huart->RxState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart)
{
  uint32_t AbortCplt = 0x01U;

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE));
  ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_IDLEIE));
  }

  if (huart->hdmatx != NULL)
  {

    if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT))
    {
      huart->hdmatx->XferAbortCallback = UART_DMATxAbortCallback;
    }
    else
    {
      huart->hdmatx->XferAbortCallback = NULL;
    }
  }

  if (huart->hdmarx != NULL)
  {

    if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
    {
      huart->hdmarx->XferAbortCallback = UART_DMARxAbortCallback;
    }
    else
    {
      huart->hdmarx->XferAbortCallback = NULL;
    }
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT))
  {

    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    if (huart->hdmatx != NULL)
    {

      if (HAL_DMA_Abort_IT(huart->hdmatx) != HAL_OK)
      {
        huart->hdmatx->XferAbortCallback = NULL;
      }
      else
      {
        AbortCplt = 0x00U;
      }
    }
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    if (huart->hdmarx != NULL)
    {

      if (HAL_DMA_Abort_IT(huart->hdmarx) != HAL_OK)
      {
        huart->hdmarx->XferAbortCallback = NULL;
        AbortCplt = 0x01U;
      }
      else
      {
        AbortCplt = 0x00U;
      }
    }
  }

  if (AbortCplt == 0x01U)
  {

    huart->TxXferCount = 0x00U;
    huart->RxXferCount = 0x00U;

    huart->ErrorCode = HAL_UART_ERROR_NONE;

    huart->gState  = HAL_UART_STATE_READY;
    huart->RxState = HAL_UART_STATE_READY;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->AbortCpltCallback(huart);
#else

    HAL_UART_AbortCpltCallback(huart);
#endif
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    if (huart->hdmatx != NULL)
    {

      huart->hdmatx->XferAbortCallback = UART_DMATxOnlyAbortCallback;

      if (HAL_DMA_Abort_IT(huart->hdmatx) != HAL_OK)
      {

        huart->hdmatx->XferAbortCallback(huart->hdmatx);
      }
    }
    else
    {

      huart->TxXferCount = 0x00U;

      huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

      huart->AbortTransmitCpltCallback(huart);
#else

      HAL_UART_AbortTransmitCpltCallback(huart);
#endif
    }
  }
  else
  {

    huart->TxXferCount = 0x00U;

    huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->AbortTransmitCpltCallback(huart);
#else

    HAL_UART_AbortTransmitCpltCallback(huart);
#endif
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
  ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_IDLEIE));
  }

  if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    if (huart->hdmarx != NULL)
    {

      huart->hdmarx->XferAbortCallback = UART_DMARxOnlyAbortCallback;

      if (HAL_DMA_Abort_IT(huart->hdmarx) != HAL_OK)
      {

        huart->hdmarx->XferAbortCallback(huart->hdmarx);
      }
    }
    else
    {

      huart->RxXferCount = 0x00U;

      huart->RxState = HAL_UART_STATE_READY;
      huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

      huart->AbortReceiveCpltCallback(huart);
#else

      HAL_UART_AbortReceiveCpltCallback(huart);
#endif
    }
  }
  else
  {

    huart->RxXferCount = 0x00U;

    huart->RxState = HAL_UART_STATE_READY;
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->AbortReceiveCpltCallback(huart);
#else

    HAL_UART_AbortReceiveCpltCallback(huart);
#endif
  }

  return HAL_OK;
}

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart)
{
  uint32_t isrflags   = READ_REG(huart->Instance->SR);
  uint32_t cr1its     = READ_REG(huart->Instance->CR1);
  uint32_t cr3its     = READ_REG(huart->Instance->CR3);
  uint32_t errorflags = 0x00U;
  uint32_t dmarequest = 0x00U;

  errorflags = (isrflags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));
  if (errorflags == RESET)
  {

    if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
    {
      UART_Receive_IT(huart);
      return;
    }
  }

  if ((errorflags != RESET) && (((cr3its & USART_CR3_EIE) != RESET)
                                || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))
  {

    if (((isrflags & USART_SR_PE) != RESET) && ((cr1its & USART_CR1_PEIE) != RESET))
    {
      huart->ErrorCode |= HAL_UART_ERROR_PE;
    }

    if (((isrflags & USART_SR_NE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart->ErrorCode |= HAL_UART_ERROR_NE;
    }

    if (((isrflags & USART_SR_FE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart->ErrorCode |= HAL_UART_ERROR_FE;
    }

    if (((isrflags & USART_SR_ORE) != RESET) && (((cr1its & USART_CR1_RXNEIE) != RESET)
                                                 || ((cr3its & USART_CR3_EIE) != RESET)))
    {
      huart->ErrorCode |= HAL_UART_ERROR_ORE;
    }

    if (huart->ErrorCode != HAL_UART_ERROR_NONE)
    {

      if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
      {
        UART_Receive_IT(huart);
      }

      dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
      if (((huart->ErrorCode & HAL_UART_ERROR_ORE) != RESET) || dmarequest)
      {

        UART_EndRxTransfer(huart);

        if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
        {
          ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

          if (huart->hdmarx != NULL)
          {

            huart->hdmarx->XferAbortCallback = UART_DMAAbortOnError;
            if (HAL_DMA_Abort_IT(huart->hdmarx) != HAL_OK)
            {

              huart->hdmarx->XferAbortCallback(huart->hdmarx);
            }
          }
          else
          {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

            huart->ErrorCallback(huart);
#else

            HAL_UART_ErrorCallback(huart);
#endif
          }
        }
        else
        {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

          huart->ErrorCallback(huart);
#else

          HAL_UART_ErrorCallback(huart);
#endif
        }
      }
      else
      {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

        huart->ErrorCallback(huart);
#else

        HAL_UART_ErrorCallback(huart);
#endif

        huart->ErrorCode = HAL_UART_ERROR_NONE;
      }
    }
    return;
  }

  if ((huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
      && ((isrflags & USART_SR_IDLE) != 0U)
      && ((cr1its & USART_CR1_IDLEIE) != 0U))
  {
    __HAL_UART_CLEAR_IDLEFLAG(huart);

    if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
    {

      uint16_t nb_remaining_rx_data = (uint16_t) __HAL_DMA_GET_COUNTER(huart->hdmarx);
      if ((nb_remaining_rx_data > 0U)
          && (nb_remaining_rx_data < huart->RxXferSize))
      {

        huart->RxXferCount = nb_remaining_rx_data;

        if (huart->hdmarx->Init.Mode != DMA_CIRCULAR)
        {

          ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
          ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

          ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

          huart->RxState = HAL_UART_STATE_READY;
          huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

          ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

          (void)HAL_DMA_Abort(huart->hdmarx);
        }

        huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

        huart->RxEventCallback(huart, (huart->RxXferSize - huart->RxXferCount));
#else

        HAL_UARTEx_RxEventCallback(huart, (huart->RxXferSize - huart->RxXferCount));
#endif
      }
      else
      {

        if (nb_remaining_rx_data == huart->RxXferSize)
        {
          if (huart->hdmarx->Init.Mode == DMA_CIRCULAR)
          {

            huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

            huart->RxEventCallback(huart, huart->RxXferSize);
#else

            HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
#endif
          }
        }
      }
      return;
    }
    else
    {

      uint16_t nb_rx_data = huart->RxXferSize - huart->RxXferCount;
      if ((huart->RxXferCount > 0U)
          && (nb_rx_data > 0U))
      {

        ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));

        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

        huart->RxState = HAL_UART_STATE_READY;
        huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

        huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

        huart->RxEventCallback(huart, nb_rx_data);
#else

        HAL_UARTEx_RxEventCallback(huart, nb_rx_data);
#endif
      }
      return;
    }
  }

  if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
  {
    UART_Transmit_IT(huart);
    return;
  }

  if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
  {
    UART_EndTransmit_IT(huart);
    return;
  }
}

__weak void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart)
{

  UNUSED(huart);

}

__weak void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{

  UNUSED(huart);
  UNUSED(Size);

}

HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart)
{

  assert_param(IS_UART_INSTANCE(huart->Instance));

  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_SBK);

  huart->gState = HAL_UART_STATE_READY;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart)
{

  assert_param(IS_UART_INSTANCE(huart->Instance));

  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_RWU);

  huart->gState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart)
{

  assert_param(IS_UART_INSTANCE(huart->Instance));

  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_RWU);

  huart->gState = HAL_UART_STATE_READY;
  huart->RxEventType = HAL_UART_RXEVENT_TC;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart)
{
  uint32_t tmpreg = 0x00U;

  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  tmpreg = huart->Instance->CR1;

  tmpreg &= (uint32_t)~((uint32_t)(USART_CR1_TE | USART_CR1_RE));

  tmpreg |= (uint32_t)USART_CR1_TE;

  WRITE_REG(huart->Instance->CR1, (uint32_t)tmpreg);

  huart->gState = HAL_UART_STATE_READY;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart)
{
  uint32_t tmpreg = 0x00U;

  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  tmpreg = huart->Instance->CR1;

  tmpreg &= (uint32_t)~((uint32_t)(USART_CR1_TE | USART_CR1_RE));

  tmpreg |= (uint32_t)USART_CR1_RE;

  WRITE_REG(huart->Instance->CR1, (uint32_t)tmpreg);

  huart->gState = HAL_UART_STATE_READY;

  __HAL_UNLOCK(huart);

  return HAL_OK;
}

HAL_UART_StateTypeDef HAL_UART_GetState(const UART_HandleTypeDef *huart)
{
  uint32_t temp1 = 0x00U, temp2 = 0x00U;
  temp1 = huart->gState;
  temp2 = huart->RxState;

  return (HAL_UART_StateTypeDef)(temp1 | temp2);
}

uint32_t HAL_UART_GetError(const UART_HandleTypeDef *huart)
{
  return huart->ErrorCode;
}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
void UART_InitCallbacksToDefault(UART_HandleTypeDef *huart)
{

  huart->TxHalfCpltCallback        = HAL_UART_TxHalfCpltCallback;
  huart->TxCpltCallback            = HAL_UART_TxCpltCallback;
  huart->RxHalfCpltCallback        = HAL_UART_RxHalfCpltCallback;
  huart->RxCpltCallback            = HAL_UART_RxCpltCallback;
  huart->ErrorCallback             = HAL_UART_ErrorCallback;
  huart->AbortCpltCallback         = HAL_UART_AbortCpltCallback;
  huart->AbortTransmitCpltCallback = HAL_UART_AbortTransmitCpltCallback;
  huart->AbortReceiveCpltCallback  = HAL_UART_AbortReceiveCpltCallback;
  huart->RxEventCallback           = HAL_UARTEx_RxEventCallback;

}
#endif

static void UART_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) == 0U)
  {
    huart->TxXferCount = 0x00U;

    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_TCIE);

  }

  else
  {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->TxCpltCallback(huart);
#else

    HAL_UART_TxCpltCallback(huart);
#endif
  }
}

static void UART_DMATxHalfCplt(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->TxHalfCpltCallback(huart);
#else

  HAL_UART_TxHalfCpltCallback(huart);
#endif
}

static void UART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) == 0U)
  {
    huart->RxXferCount = 0U;

    ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

    ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    huart->RxState = HAL_UART_STATE_READY;

    if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
    {
      ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
    }
  }

  huart->RxEventType = HAL_UART_RXEVENT_TC;

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->RxEventCallback(huart, huart->RxXferSize);
#else

    HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
#endif
  }
  else
  {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->RxCpltCallback(huart);
#else

    HAL_UART_RxCpltCallback(huart);
#endif
  }
}

static void UART_DMARxHalfCplt(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  huart->RxEventType = HAL_UART_RXEVENT_HT;

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->RxEventCallback(huart, huart->RxXferSize / 2U);
#else

    HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize / 2U);
#endif
  }
  else
  {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

    huart->RxHalfCpltCallback(huart);
#else

    HAL_UART_RxHalfCpltCallback(huart);
#endif
  }
}

static void UART_DMAError(DMA_HandleTypeDef *hdma)
{
  uint32_t dmarequest = 0x00U;
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAT);
  if ((huart->gState == HAL_UART_STATE_BUSY_TX) && dmarequest)
  {
    huart->TxXferCount = 0x00U;
    UART_EndTxTransfer(huart);
  }

  dmarequest = HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR);
  if ((huart->RxState == HAL_UART_STATE_BUSY_RX) && dmarequest)
  {
    huart->RxXferCount = 0x00U;
    UART_EndRxTransfer(huart);
  }

  huart->ErrorCode |= HAL_UART_ERROR_DMA;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->ErrorCallback(huart);
#else

  HAL_UART_ErrorCallback(huart);
#endif
}

static HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                                     uint32_t Tickstart, uint32_t Timeout)
{

  while ((__HAL_UART_GET_FLAG(huart, Flag) ? SET : RESET) == Status)
  {

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {

        return HAL_TIMEOUT;
      }

      if ((READ_BIT(huart->Instance->CR1, USART_CR1_RE) != 0U) && (Flag != UART_FLAG_TXE) && (Flag != UART_FLAG_TC))
      {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) == SET)
        {

          __HAL_UART_CLEAR_OREFLAG(huart);

          UART_EndRxTransfer(huart);

          huart->ErrorCode = HAL_UART_ERROR_ORE;

          __HAL_UNLOCK(huart);

          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  huart->pRxBuffPtr = pData;
  huart->RxXferSize = Size;
  huart->RxXferCount = Size;

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->RxState = HAL_UART_STATE_BUSY_RX;

  if (huart->Init.Parity != UART_PARITY_NONE)
  {

    __HAL_UART_ENABLE_IT(huart, UART_IT_PE);
  }

  __HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

  __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);

  return HAL_OK;
}

HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  uint32_t *tmp;

  huart->pRxBuffPtr = pData;
  huart->RxXferSize = Size;

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->RxState = HAL_UART_STATE_BUSY_RX;

  huart->hdmarx->XferCpltCallback = UART_DMAReceiveCplt;

  huart->hdmarx->XferHalfCpltCallback = UART_DMARxHalfCplt;

  huart->hdmarx->XferErrorCallback = UART_DMAError;

  huart->hdmarx->XferAbortCallback = NULL;

  tmp = (uint32_t *)&pData;
  if (HAL_DMA_Start_IT(huart->hdmarx, (uint32_t)&huart->Instance->DR, *(uint32_t *)tmp, Size) != HAL_OK)
  {

    huart->ErrorCode = HAL_UART_ERROR_DMA;

    huart->RxState = HAL_UART_STATE_READY;

    return HAL_ERROR;
  }

  __HAL_UART_CLEAR_OREFLAG(huart);

  if (huart->Init.Parity != UART_PARITY_NONE)
  {

    ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_PEIE);
  }

  ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_EIE);

  ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

  return HAL_OK;
}

static void UART_EndTxTransfer(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

  huart->gState = HAL_UART_STATE_READY;
}

static void UART_EndRxTransfer(UART_HandleTypeDef *huart)
{

  ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));
  ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

  if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
  {
    ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
  }

  huart->RxState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;
}

static void UART_DMAAbortOnError(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
  huart->RxXferCount = 0x00U;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->ErrorCallback(huart);
#else

  HAL_UART_ErrorCallback(huart);
#endif
}

static void UART_DMATxAbortCallback(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  huart->hdmatx->XferAbortCallback = NULL;

  if (huart->hdmarx != NULL)
  {
    if (huart->hdmarx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  huart->TxXferCount = 0x00U;
  huart->RxXferCount = 0x00U;

  huart->ErrorCode = HAL_UART_ERROR_NONE;

  huart->gState  = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->AbortCpltCallback(huart);
#else

  HAL_UART_AbortCpltCallback(huart);
#endif
}

static void UART_DMARxAbortCallback(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  huart->hdmarx->XferAbortCallback = NULL;

  if (huart->hdmatx != NULL)
  {
    if (huart->hdmatx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  huart->TxXferCount = 0x00U;
  huart->RxXferCount = 0x00U;

  huart->ErrorCode = HAL_UART_ERROR_NONE;

  huart->gState  = HAL_UART_STATE_READY;
  huart->RxState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->AbortCpltCallback(huart);
#else

  HAL_UART_AbortCpltCallback(huart);
#endif
}

static void UART_DMATxOnlyAbortCallback(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  huart->TxXferCount = 0x00U;

  huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->AbortTransmitCpltCallback(huart);
#else

  HAL_UART_AbortTransmitCpltCallback(huart);
#endif
}

static void UART_DMARxOnlyAbortCallback(DMA_HandleTypeDef *hdma)
{
  UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  huart->RxXferCount = 0x00U;

  huart->RxState = HAL_UART_STATE_READY;
  huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->AbortReceiveCpltCallback(huart);
#else

  HAL_UART_AbortReceiveCpltCallback(huart);
#endif
}

static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart)
{
  const uint16_t *tmp;

  if (huart->gState == HAL_UART_STATE_BUSY_TX)
  {
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      tmp = (const uint16_t *) huart->pTxBuffPtr;
      huart->Instance->DR = (uint16_t)(*tmp & (uint16_t)0x01FF);
      huart->pTxBuffPtr += 2U;
    }
    else
    {
      huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);
    }

    if (--huart->TxXferCount == 0U)
    {

      __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

      __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

static HAL_StatusTypeDef UART_EndTransmit_IT(UART_HandleTypeDef *huart)
{

  __HAL_UART_DISABLE_IT(huart, UART_IT_TC);

  huart->gState = HAL_UART_STATE_READY;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

  huart->TxCpltCallback(huart);
#else

  HAL_UART_TxCpltCallback(huart);
#endif

  return HAL_OK;
}

static HAL_StatusTypeDef UART_Receive_IT(UART_HandleTypeDef *huart)
{
  uint8_t  *pdata8bits = NULL;
  uint16_t *pdata16bits = NULL;

  if (huart->RxState == HAL_UART_STATE_BUSY_RX)
  {
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {

      UNUSED(pdata8bits);
      pdata16bits = (uint16_t *) huart->pRxBuffPtr;
      *pdata16bits = (uint16_t)(huart->Instance->DR & (uint16_t)0x01FF);
      huart->pRxBuffPtr += 2U;
    }
    else
    {
      pdata8bits = (uint8_t *) huart->pRxBuffPtr;

      UNUSED(pdata16bits);

      if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
      {
        *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
      }
      else
      {
        *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
      }
      huart->pRxBuffPtr += 1U;
    }

    if (--huart->RxXferCount == 0U)
    {

      __HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);

      __HAL_UART_DISABLE_IT(huart, UART_IT_PE);

      __HAL_UART_DISABLE_IT(huart, UART_IT_ERR);

      huart->RxState = HAL_UART_STATE_READY;

      huart->RxEventType = HAL_UART_RXEVENT_TC;

      if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
      {

        huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {

          __HAL_UART_CLEAR_IDLEFLAG(huart);
        }

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

        huart->RxEventCallback(huart, huart->RxXferSize);
#else

        HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
#endif
      }
      else
      {

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)

        huart->RxCpltCallback(huart);
#else

        HAL_UART_RxCpltCallback(huart);
#endif
      }

      return HAL_OK;
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

static void UART_SetConfig(UART_HandleTypeDef *huart)
{
  uint32_t tmpreg;
  uint32_t pclk;

  assert_param(IS_UART_BAUDRATE(huart->Init.BaudRate));
  assert_param(IS_UART_STOPBITS(huart->Init.StopBits));
  assert_param(IS_UART_PARITY(huart->Init.Parity));
  assert_param(IS_UART_MODE(huart->Init.Mode));

  MODIFY_REG(huart->Instance->CR2, USART_CR2_STOP, huart->Init.StopBits);

  tmpreg = (uint32_t)huart->Init.WordLength | huart->Init.Parity | huart->Init.Mode | huart->Init.OverSampling;
  MODIFY_REG(huart->Instance->CR1,
             (uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE | USART_CR1_OVER8),
             tmpreg);

  MODIFY_REG(huart->Instance->CR3, (USART_CR3_RTSE | USART_CR3_CTSE), huart->Init.HwFlowCtl);

#if defined(USART6) && defined(UART9) && defined(UART10)
    if ((huart->Instance == USART1) || (huart->Instance == USART6) || (huart->Instance == UART9) || (huart->Instance == UART10))
    {
      pclk = HAL_RCC_GetPCLK2Freq();
    }
#elif defined(USART6)
    if ((huart->Instance == USART1) || (huart->Instance == USART6))
    {
      pclk = HAL_RCC_GetPCLK2Freq();
    }
#else
    if (huart->Instance == USART1)
    {
      pclk = HAL_RCC_GetPCLK2Freq();
    }
#endif
    else
    {
      pclk = HAL_RCC_GetPCLK1Freq();
    }

  if (huart->Init.OverSampling == UART_OVERSAMPLING_8)
  {
    huart->Instance->BRR = UART_BRR_SAMPLING8(pclk, huart->Init.BaudRate);
  }
  else
  {
    huart->Instance->BRR = UART_BRR_SAMPLING16(pclk, huart->Init.BaudRate);
  }
}

#endif
