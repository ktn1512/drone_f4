#include "stm32f4xx_hal.h"

#ifdef HAL_SPI_MODULE_ENABLED

#define SPI_DEFAULT_TIMEOUT 100U
#define SPI_BSY_FLAG_WORKAROUND_TIMEOUT 1000U

static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma);
static void SPI_DMAError(DMA_HandleTypeDef *hdma);
static void SPI_DMAAbortOnError(DMA_HandleTypeDef *hdma);
static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *hdma);
static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus State,
                                                       uint32_t Timeout, uint32_t Tickstart);
static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi);
#if (USE_SPI_CRC != 0U)
static void SPI_RxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_RxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi);
static void SPI_2linesRxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi);
#endif
static void SPI_AbortRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_AbortTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi);
static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi);
static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart);

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
{

  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));
  assert_param(IS_SPI_MODE(hspi->Init.Mode));
  assert_param(IS_SPI_DIRECTION(hspi->Init.Direction));
  assert_param(IS_SPI_DATASIZE(hspi->Init.DataSize));
  assert_param(IS_SPI_NSS(hspi->Init.NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(hspi->Init.FirstBit));
  assert_param(IS_SPI_TIMODE(hspi->Init.TIMode));
  if (hspi->Init.TIMode == SPI_TIMODE_DISABLE)
  {
    assert_param(IS_SPI_CPOL(hspi->Init.CLKPolarity));
    assert_param(IS_SPI_CPHA(hspi->Init.CLKPhase));

    if (hspi->Init.Mode == SPI_MODE_MASTER)
    {
      assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));
    }
    else
    {

      hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    }
  }
  else
  {
    assert_param(IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler));

    hspi->Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi->Init.CLKPhase    = SPI_PHASE_1EDGE;
  }
#if (USE_SPI_CRC != 0U)
  assert_param(IS_SPI_CRC_CALCULATION(hspi->Init.CRCCalculation));
  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    assert_param(IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial));
  }
#else
  hspi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
#endif

  if (hspi->State == HAL_SPI_STATE_RESET)
  {

    hspi->Lock = HAL_UNLOCKED;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)

    hspi->TxCpltCallback       = HAL_SPI_TxCpltCallback;
    hspi->RxCpltCallback       = HAL_SPI_RxCpltCallback;
    hspi->TxRxCpltCallback     = HAL_SPI_TxRxCpltCallback;
    hspi->TxHalfCpltCallback   = HAL_SPI_TxHalfCpltCallback;
    hspi->RxHalfCpltCallback   = HAL_SPI_RxHalfCpltCallback;
    hspi->TxRxHalfCpltCallback = HAL_SPI_TxRxHalfCpltCallback;
    hspi->ErrorCallback        = HAL_SPI_ErrorCallback;
    hspi->AbortCpltCallback    = HAL_SPI_AbortCpltCallback;

    if (hspi->MspInitCallback == NULL)
    {
      hspi->MspInitCallback = HAL_SPI_MspInit;
    }

    hspi->MspInitCallback(hspi);
#else

    HAL_SPI_MspInit(hspi);
#endif
  }

  hspi->State = HAL_SPI_STATE_BUSY;

  __HAL_SPI_DISABLE(hspi);

  WRITE_REG(hspi->Instance->CR1, ((hspi->Init.Mode & (SPI_CR1_MSTR | SPI_CR1_SSI)) |
                                  (hspi->Init.Direction & (SPI_CR1_RXONLY | SPI_CR1_BIDIMODE)) |
                                  (hspi->Init.DataSize & SPI_CR1_DFF) |
                                  (hspi->Init.CLKPolarity & SPI_CR1_CPOL) |
                                  (hspi->Init.CLKPhase & SPI_CR1_CPHA) |
                                  (hspi->Init.NSS & SPI_CR1_SSM) |
                                  (hspi->Init.BaudRatePrescaler & SPI_CR1_BR_Msk) |
                                  (hspi->Init.FirstBit  & SPI_CR1_LSBFIRST) |
                                  (hspi->Init.CRCCalculation & SPI_CR1_CRCEN)));

  WRITE_REG(hspi->Instance->CR2, (((hspi->Init.NSS >> 16U) & SPI_CR2_SSOE) | (hspi->Init.TIMode & SPI_CR2_FRF)));

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    WRITE_REG(hspi->Instance->CRCPR, (hspi->Init.CRCPolynomial & SPI_CRCPR_CRCPOLY_Msk));
  }
#endif

#if defined(SPI_I2SCFGR_I2SMOD)

  CLEAR_BIT(hspi->Instance->I2SCFGR, SPI_I2SCFGR_I2SMOD);
#endif

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State     = HAL_SPI_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi)
{

  if (hspi == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_SPI_ALL_INSTANCE(hspi->Instance));

  hspi->State = HAL_SPI_STATE_BUSY;

  __HAL_SPI_DISABLE(hspi);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  if (hspi->MspDeInitCallback == NULL)
  {
    hspi->MspDeInitCallback = HAL_SPI_MspDeInit;
  }

  hspi->MspDeInitCallback(hspi);
#else

  HAL_SPI_MspDeInit(hspi);
#endif

  hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  hspi->State = HAL_SPI_STATE_RESET;

  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

__weak void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)

HAL_StatusTypeDef HAL_SPI_RegisterCallback(SPI_HandleTypeDef *hspi, HAL_SPI_CallbackIDTypeDef CallbackID,
                                           pSPI_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {

    hspi->ErrorCode |= HAL_SPI_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  if (HAL_SPI_STATE_READY == hspi->State)
  {
    switch (CallbackID)
    {
      case HAL_SPI_TX_COMPLETE_CB_ID :
        hspi->TxCpltCallback = pCallback;
        break;

      case HAL_SPI_RX_COMPLETE_CB_ID :
        hspi->RxCpltCallback = pCallback;
        break;

      case HAL_SPI_TX_RX_COMPLETE_CB_ID :
        hspi->TxRxCpltCallback = pCallback;
        break;

      case HAL_SPI_TX_HALF_COMPLETE_CB_ID :
        hspi->TxHalfCpltCallback = pCallback;
        break;

      case HAL_SPI_RX_HALF_COMPLETE_CB_ID :
        hspi->RxHalfCpltCallback = pCallback;
        break;

      case HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID :
        hspi->TxRxHalfCpltCallback = pCallback;
        break;

      case HAL_SPI_ERROR_CB_ID :
        hspi->ErrorCallback = pCallback;
        break;

      case HAL_SPI_ABORT_CB_ID :
        hspi->AbortCpltCallback = pCallback;
        break;

      case HAL_SPI_MSPINIT_CB_ID :
        hspi->MspInitCallback = pCallback;
        break;

      case HAL_SPI_MSPDEINIT_CB_ID :
        hspi->MspDeInitCallback = pCallback;
        break;

      default :

        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_SPI_STATE_RESET == hspi->State)
  {
    switch (CallbackID)
    {
      case HAL_SPI_MSPINIT_CB_ID :
        hspi->MspInitCallback = pCallback;
        break;

      case HAL_SPI_MSPDEINIT_CB_ID :
        hspi->MspDeInitCallback = pCallback;
        break;

      default :

        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hspi);
  return status;
}

HAL_StatusTypeDef HAL_SPI_UnRegisterCallback(SPI_HandleTypeDef *hspi, HAL_SPI_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hspi);

  if (HAL_SPI_STATE_READY == hspi->State)
  {
    switch (CallbackID)
    {
      case HAL_SPI_TX_COMPLETE_CB_ID :
        hspi->TxCpltCallback = HAL_SPI_TxCpltCallback;
        break;

      case HAL_SPI_RX_COMPLETE_CB_ID :
        hspi->RxCpltCallback = HAL_SPI_RxCpltCallback;
        break;

      case HAL_SPI_TX_RX_COMPLETE_CB_ID :
        hspi->TxRxCpltCallback = HAL_SPI_TxRxCpltCallback;
        break;

      case HAL_SPI_TX_HALF_COMPLETE_CB_ID :
        hspi->TxHalfCpltCallback = HAL_SPI_TxHalfCpltCallback;
        break;

      case HAL_SPI_RX_HALF_COMPLETE_CB_ID :
        hspi->RxHalfCpltCallback = HAL_SPI_RxHalfCpltCallback;
        break;

      case HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID :
        hspi->TxRxHalfCpltCallback = HAL_SPI_TxRxHalfCpltCallback;
        break;

      case HAL_SPI_ERROR_CB_ID :
        hspi->ErrorCallback = HAL_SPI_ErrorCallback;
        break;

      case HAL_SPI_ABORT_CB_ID :
        hspi->AbortCpltCallback = HAL_SPI_AbortCpltCallback;
        break;

      case HAL_SPI_MSPINIT_CB_ID :
        hspi->MspInitCallback = HAL_SPI_MspInit;
        break;

      case HAL_SPI_MSPDEINIT_CB_ID :
        hspi->MspDeInitCallback = HAL_SPI_MspDeInit;
        break;

      default :

        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_SPI_STATE_RESET == hspi->State)
  {
    switch (CallbackID)
    {
      case HAL_SPI_MSPINIT_CB_ID :
        hspi->MspInitCallback = HAL_SPI_MspInit;
        break;

      case HAL_SPI_MSPDEINIT_CB_ID :
        hspi->MspDeInitCallback = HAL_SPI_MspDeInit;
        break;

      default :

        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_INVALID_CALLBACK);

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hspi);
  return status;
}
#endif

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart;
  uint16_t initial_TxXferCount;

  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  tickstart = HAL_GetTick();
  initial_TxXferCount = Size;

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (const uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  hspi->pRxBuffPtr  = (uint8_t *)NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->TxISR       = NULL;
  hspi->RxISR       = NULL;

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_TX(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint16_t);
      hspi->TxXferCount--;
    }

    while (hspi->TxXferCount > 0U)
    {

      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint16_t);
        hspi->TxXferCount--;
      }
      else
      {

        if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
        {
          hspi->State = HAL_SPI_STATE_READY;
          __HAL_UNLOCK(hspi);
          return HAL_TIMEOUT;
        }
      }
    }
  }

  else
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      *((__IO uint8_t *)&hspi->Instance->DR) = *((const uint8_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint8_t);
      hspi->TxXferCount--;
    }
    while (hspi->TxXferCount > 0U)
    {

      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
      {
        *((__IO uint8_t *)&hspi->Instance->DR) = *((const uint8_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint8_t);
        hspi->TxXferCount--;
      }
      else
      {

        if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
        {
          hspi->State = HAL_SPI_STATE_READY;
          __HAL_UNLOCK(hspi);
          return HAL_TIMEOUT;
        }
      }
    }
  }
#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
  }
#endif

  if (SPI_EndRxTxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;

  __HAL_UNLOCK(hspi);

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
#if (USE_SPI_CRC != 0U)
  __IO uint32_t tmpreg = 0U;
#endif
  uint32_t tickstart;

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  if ((hspi->Init.Mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;

    return HAL_SPI_TransmitReceive(hspi, pData, pData, Size, Timeout);
  }

  tickstart = HAL_GetTick();

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  hspi->pTxBuffPtr  = (uint8_t *)NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);

    hspi->RxXferCount--;
  }
#endif

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_RX(hspi);
  }

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.DataSize == SPI_DATASIZE_8BIT)
  {

    while (hspi->RxXferCount > 0U)
    {

      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
      {

        (* (uint8_t *)hspi->pRxBuffPtr) = *(__IO uint8_t *)&hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint8_t);
        hspi->RxXferCount--;
      }
      else
      {

        if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
        {
          hspi->State = HAL_SPI_STATE_READY;
          __HAL_UNLOCK(hspi);
          return HAL_TIMEOUT;
        }
      }
    }
  }
  else
  {

    while (hspi->RxXferCount > 0U)
    {

      if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE))
      {
        *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;
      }
      else
      {

        if ((((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
        {
          hspi->State = HAL_SPI_STATE_READY;
          __HAL_UNLOCK(hspi);
          return HAL_TIMEOUT;
        }
      }
    }
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {

    SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);

    if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SET, Timeout, tickstart) != HAL_OK)
    {

      __HAL_UNLOCK(hspi);
      return HAL_TIMEOUT;
    }

    if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
    {
      *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)hspi->Instance->DR;
    }

    else
    {
      (*(uint8_t *)hspi->pRxBuffPtr) = *(__IO uint8_t *)&hspi->Instance->DR;
    }

    if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SET, Timeout, tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      hspi->State = HAL_SPI_STATE_READY;
      __HAL_UNLOCK(hspi);
      return HAL_TIMEOUT;
    }

    tmpreg = READ_REG(hspi->Instance->DR);

    UNUSED(tmpreg);
  }
#endif

  if (SPI_EndRxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
  }

#if (USE_SPI_CRC != 0U)

  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
  }
#endif

  hspi->State = HAL_SPI_STATE_READY;

  __HAL_UNLOCK(hspi);
  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                          uint16_t Size, uint32_t Timeout)
{
  uint16_t             initial_TxXferCount;
  uint32_t             tmp_mode;
  HAL_SPI_StateTypeDef tmp_state;
  uint32_t             tickstart;
#if (USE_SPI_CRC != 0U)
  __IO uint32_t tmpreg = 0U;
#endif

  uint32_t             txallowed = 1U;

  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  tickstart = HAL_GetTick();

  tmp_state           = hspi->State;
  tmp_mode            = hspi->Init.Mode;
  initial_TxXferCount = Size;

  if (!((tmp_state == HAL_SPI_STATE_READY) || \
        ((tmp_mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) &&
         (tmp_state == HAL_SPI_STATE_BUSY_RX))))
  {
    return HAL_BUSY;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferCount = Size;
  hspi->RxXferSize  = Size;
  hspi->pTxBuffPtr  = (const uint8_t *)pTxData;
  hspi->TxXferCount = Size;
  hspi->TxXferSize  = Size;

  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  if (hspi->Init.DataSize == SPI_DATASIZE_16BIT)
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint16_t);
      hspi->TxXferCount--;

#if (USE_SPI_CRC != 0U)

      if ((hspi->TxXferCount == 0U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
      {
        SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
      }
#endif

    }
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {

      if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)) && (hspi->TxXferCount > 0U) && (txallowed == 1U))
      {
        hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr += sizeof(uint16_t);
        hspi->TxXferCount--;

        txallowed = 0U;

#if (USE_SPI_CRC != 0U)

        if ((hspi->TxXferCount == 0U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
        {
          SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
        }
#endif
      }

      if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)) && (hspi->RxXferCount > 0U))
      {
        *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)hspi->Instance->DR;
        hspi->pRxBuffPtr += sizeof(uint16_t);
        hspi->RxXferCount--;

        txallowed = 1U;
      }
      if (((HAL_GetTick() - tickstart) >=  Timeout) && (Timeout != HAL_MAX_DELAY))
      {
        hspi->State = HAL_SPI_STATE_READY;
        __HAL_UNLOCK(hspi);
        return HAL_TIMEOUT;
      }
    }
  }

  else
  {
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (initial_TxXferCount == 0x01U))
    {
      *((__IO uint8_t *)&hspi->Instance->DR) = *((const uint8_t *)hspi->pTxBuffPtr);
      hspi->pTxBuffPtr += sizeof(uint8_t);
      hspi->TxXferCount--;

#if (USE_SPI_CRC != 0U)

      if ((hspi->TxXferCount == 0U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
      {
        SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
      }
#endif
    }
    while ((hspi->TxXferCount > 0U) || (hspi->RxXferCount > 0U))
    {

      if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE)) && (hspi->TxXferCount > 0U) && (txallowed == 1U))
      {
        *(__IO uint8_t *)&hspi->Instance->DR = *((const uint8_t *)hspi->pTxBuffPtr);
        hspi->pTxBuffPtr++;
        hspi->TxXferCount--;

        txallowed = 0U;

#if (USE_SPI_CRC != 0U)

        if ((hspi->TxXferCount == 0U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
        {
          SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
        }
#endif
      }

      if ((__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_RXNE)) && (hspi->RxXferCount > 0U))
      {
        (*(uint8_t *)hspi->pRxBuffPtr) = hspi->Instance->DR;
        hspi->pRxBuffPtr++;
        hspi->RxXferCount--;

        txallowed = 1U;
      }
      if ((((HAL_GetTick() - tickstart) >=  Timeout) && ((Timeout != HAL_MAX_DELAY))) || (Timeout == 0U))
      {
        hspi->State = HAL_SPI_STATE_READY;
        __HAL_UNLOCK(hspi);
        return HAL_TIMEOUT;
      }
    }
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {

    if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SET, Timeout, tickstart) != HAL_OK)
    {

      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      hspi->State = HAL_SPI_STATE_READY;
      __HAL_UNLOCK(hspi);
      return HAL_TIMEOUT;
    }

    tmpreg = READ_REG(hspi->Instance->DR);

    UNUSED(tmpreg);
  }

  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);

    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }
#endif

  if (SPI_EndRxTxTransaction(hspi, Timeout, tickstart) != HAL_OK)
  {
    hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }

  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;

  __HAL_UNLOCK(hspi);

  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{

  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (const uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  hspi->pRxBuffPtr  = (uint8_t *)NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;
  hspi->RxISR       = NULL;

  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->TxISR = SPI_TxISR_16BIT;
  }
  else
  {
    hspi->TxISR = SPI_TxISR_8BIT;
  }

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_TX(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;

    return HAL_SPI_TransmitReceive_IT(hspi, pData, pData, Size);
  }

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  hspi->pTxBuffPtr  = (uint8_t *)NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;
  hspi->TxISR       = NULL;

  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR = SPI_RxISR_16BIT;
  }
  else
  {
    hspi->RxISR = SPI_RxISR_8BIT;
  }

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_RX(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                             uint16_t Size)
{
  uint32_t             tmp_mode;
  HAL_SPI_StateTypeDef tmp_state;

  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  tmp_state           = hspi->State;
  tmp_mode            = hspi->Init.Mode;

  if (!((tmp_state == HAL_SPI_STATE_READY) || \
        ((tmp_mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) &&
         (tmp_state == HAL_SPI_STATE_BUSY_RX))))
  {
    return HAL_BUSY;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (const uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  if (hspi->Init.DataSize > SPI_DATASIZE_8BIT)
  {
    hspi->RxISR     = SPI_2linesRxISR_16BIT;
    hspi->TxISR     = SPI_2linesTxISR_16BIT;
  }
  else
  {
    hspi->RxISR     = SPI_2linesRxISR_8BIT;
    hspi->TxISR     = SPI_2linesTxISR_8BIT;
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size)
{

  assert_param(IS_SPI_DMA_HANDLE(hspi->hdmatx));

  assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE(hspi->Init.Direction));

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_TX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (const uint8_t *)pData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;

  hspi->pRxBuffPtr  = (uint8_t *)NULL;
  hspi->TxISR       = NULL;
  hspi->RxISR       = NULL;
  hspi->RxXferSize  = 0U;
  hspi->RxXferCount = 0U;

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_TX(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  hspi->hdmatx->XferHalfCpltCallback = SPI_DMAHalfTransmitCplt;

  hspi->hdmatx->XferCpltCallback = SPI_DMATransmitCplt;

  hspi->hdmatx->XferErrorCallback = SPI_DMAError;

  hspi->hdmatx->XferAbortCallback = NULL;

  if (HAL_OK != HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->DR,
                                 hspi->TxXferCount))
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);

    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{

  assert_param(IS_SPI_DMA_HANDLE(hspi->hdmarx));

  if (hspi->State != HAL_SPI_STATE_READY)
  {
    return HAL_BUSY;
  }

  if ((pData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
  {
    hspi->State = HAL_SPI_STATE_BUSY_RX;

    assert_param(IS_SPI_DMA_HANDLE(hspi->hdmatx));

    return HAL_SPI_TransmitReceive_DMA(hspi, pData, pData, Size);
  }

  __HAL_LOCK(hspi);

  hspi->State       = HAL_SPI_STATE_BUSY_RX;
  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pRxBuffPtr  = (uint8_t *)pData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;
  hspi->TxXferSize  = 0U;
  hspi->TxXferCount = 0U;

  if (hspi->Init.Direction == SPI_DIRECTION_1LINE)
  {

    __HAL_SPI_DISABLE(hspi);
    SPI_1LINE_RX(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;

  hspi->hdmarx->XferCpltCallback = SPI_DMAReceiveCplt;

  hspi->hdmarx->XferErrorCallback = SPI_DMAError;

  hspi->hdmarx->XferAbortCallback = NULL;

  if (HAL_OK != HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->DR, (uint32_t)hspi->pRxBuffPtr,
                                 hspi->RxXferCount))
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);

    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  SET_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                              uint16_t Size)
{
  uint32_t             tmp_mode;
  HAL_SPI_StateTypeDef tmp_state;

  assert_param(IS_SPI_DMA_HANDLE(hspi->hdmarx));
  assert_param(IS_SPI_DMA_HANDLE(hspi->hdmatx));

  assert_param(IS_SPI_DIRECTION_2LINES(hspi->Init.Direction));

  tmp_state           = hspi->State;
  tmp_mode            = hspi->Init.Mode;

  if (!((tmp_state == HAL_SPI_STATE_READY) ||
        ((tmp_mode == SPI_MODE_MASTER) && (hspi->Init.Direction == SPI_DIRECTION_2LINES) &&
         (tmp_state == HAL_SPI_STATE_BUSY_RX))))
  {
    return HAL_BUSY;
  }

  if ((pTxData == NULL) || (pRxData == NULL) || (Size == 0U))
  {
    return HAL_ERROR;
  }

  __HAL_LOCK(hspi);

  if (hspi->State != HAL_SPI_STATE_BUSY_RX)
  {
    hspi->State = HAL_SPI_STATE_BUSY_TX_RX;
  }

  hspi->ErrorCode   = HAL_SPI_ERROR_NONE;
  hspi->pTxBuffPtr  = (const uint8_t *)pTxData;
  hspi->TxXferSize  = Size;
  hspi->TxXferCount = Size;
  hspi->pRxBuffPtr  = (uint8_t *)pRxData;
  hspi->RxXferSize  = Size;
  hspi->RxXferCount = Size;

  hspi->RxISR       = NULL;
  hspi->TxISR       = NULL;

#if (USE_SPI_CRC != 0U)

  if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
  {
    SPI_RESET_CRC(hspi);
  }
#endif

  if (hspi->State == HAL_SPI_STATE_BUSY_RX)
  {

    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfReceiveCplt;
    hspi->hdmarx->XferCpltCallback     = SPI_DMAReceiveCplt;
  }
  else
  {

    hspi->hdmarx->XferHalfCpltCallback = SPI_DMAHalfTransmitReceiveCplt;
    hspi->hdmarx->XferCpltCallback     = SPI_DMATransmitReceiveCplt;
  }

  hspi->hdmarx->XferErrorCallback = SPI_DMAError;

  hspi->hdmarx->XferAbortCallback = NULL;

  if (HAL_OK != HAL_DMA_Start_IT(hspi->hdmarx, (uint32_t)&hspi->Instance->DR, (uint32_t)hspi->pRxBuffPtr,
                                 hspi->RxXferCount))
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);

    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }

  SET_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);

  hspi->hdmatx->XferHalfCpltCallback = NULL;
  hspi->hdmatx->XferCpltCallback     = NULL;
  hspi->hdmatx->XferErrorCallback    = NULL;
  hspi->hdmatx->XferAbortCallback    = NULL;

  if (HAL_OK != HAL_DMA_Start_IT(hspi->hdmatx, (uint32_t)hspi->pTxBuffPtr, (uint32_t)&hspi->Instance->DR,
                                 hspi->TxXferCount))
  {

    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);

    __HAL_UNLOCK(hspi);
    return HAL_ERROR;
  }

  if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
  {

    __HAL_SPI_ENABLE(hspi);
  }

  __HAL_UNLOCK(hspi);

  __HAL_SPI_ENABLE_IT(hspi, (SPI_IT_ERR));

  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_Abort(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode;
  __IO uint32_t count;
  __IO uint32_t resetcount;

  errorcode = HAL_OK;
  resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
  count = resetcount;

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_ERRIE);

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_TXEIE))
  {
    hspi->TxISR = SPI_AbortTx_ISR;

    do
    {
      if (count == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
      count--;
    } while (hspi->State != HAL_SPI_STATE_ABORT);

    count = resetcount;
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_RXNEIE))
  {
    hspi->RxISR = SPI_AbortRx_ISR;

    do
    {
      if (count == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
      count--;
    } while (hspi->State != HAL_SPI_STATE_ABORT);

    count = resetcount;
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_TXDMAEN))
  {

    if (hspi->hdmatx != NULL)
    {

      hspi->hdmatx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(hspi->hdmatx) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }

      CLEAR_BIT(hspi->Instance->CR2, (SPI_CR2_TXDMAEN));

      do
      {
        if (count == 0U)
        {
          SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
          break;
        }
        count--;
      } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);
    }
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_RXDMAEN))
  {

    if (hspi->hdmarx != NULL)
    {

      hspi->hdmarx->XferAbortCallback = NULL;

      if (HAL_DMA_Abort(hspi->hdmarx) != HAL_OK)
      {
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }

      __HAL_SPI_DISABLE(hspi);

      CLEAR_BIT(hspi->Instance->CR2, (SPI_CR2_RXDMAEN));
    }
  }

  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  if (hspi->ErrorCode == HAL_SPI_ERROR_ABORT)
  {

    errorcode = HAL_ERROR;
  }
  else
  {

    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);

  hspi->State = HAL_SPI_STATE_READY;

  return errorcode;
}

HAL_StatusTypeDef HAL_SPI_Abort_IT(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode;
  uint32_t abortcplt ;
  __IO uint32_t count;
  __IO uint32_t resetcount;

  errorcode = HAL_OK;
  abortcplt = 1U;
  resetcount = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);
  count = resetcount;

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_ERRIE);

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_TXEIE))
  {
    hspi->TxISR = SPI_AbortTx_ISR;

    do
    {
      if (count == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
      count--;
    } while (hspi->State != HAL_SPI_STATE_ABORT);

    count = resetcount;
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_RXNEIE))
  {
    hspi->RxISR = SPI_AbortRx_ISR;

    do
    {
      if (count == 0U)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
        break;
      }
      count--;
    } while (hspi->State != HAL_SPI_STATE_ABORT);

    count = resetcount;
  }

  if (hspi->hdmatx != NULL)
  {

    if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_TXDMAEN))
    {
      hspi->hdmatx->XferAbortCallback = SPI_DMATxAbortCallback;
    }
    else
    {
      hspi->hdmatx->XferAbortCallback = NULL;
    }
  }

  if (hspi->hdmarx != NULL)
  {

    if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_RXDMAEN))
    {
      hspi->hdmarx->XferAbortCallback = SPI_DMARxAbortCallback;
    }
    else
    {
      hspi->hdmarx->XferAbortCallback = NULL;
    }
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_TXDMAEN))
  {

    if (hspi->hdmatx != NULL)
    {

      if (HAL_DMA_Abort_IT(hspi->hdmatx) != HAL_OK)
      {
        hspi->hdmatx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  if (HAL_IS_BIT_SET(hspi->Instance->CR2, SPI_CR2_RXDMAEN))
  {

    if (hspi->hdmarx != NULL)
    {

      if (HAL_DMA_Abort_IT(hspi->hdmarx) !=  HAL_OK)
      {
        hspi->hdmarx->XferAbortCallback = NULL;
        hspi->ErrorCode = HAL_SPI_ERROR_ABORT;
      }
      else
      {
        abortcplt = 0U;
      }
    }
  }

  if (abortcplt == 1U)
  {

    hspi->RxXferCount = 0U;
    hspi->TxXferCount = 0U;

    if (hspi->ErrorCode == HAL_SPI_ERROR_ABORT)
    {

      errorcode = HAL_ERROR;
    }
    else
    {

      hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    }

    __HAL_SPI_CLEAR_OVRFLAG(hspi);
    __HAL_SPI_CLEAR_FREFLAG(hspi);

    hspi->State = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    hspi->AbortCpltCallback(hspi);
#else
    HAL_SPI_AbortCpltCallback(hspi);
#endif
  }

  return errorcode;
}

HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi)
{

  __HAL_LOCK(hspi);

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi)
{

  __HAL_LOCK(hspi);

  SET_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

  __HAL_UNLOCK(hspi);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi)
{
  HAL_StatusTypeDef errorcode = HAL_OK;

  if (hspi->hdmatx != NULL)
  {
    if (HAL_OK != HAL_DMA_Abort(hspi->hdmatx))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);
      errorcode = HAL_ERROR;
    }
  }

  if (hspi->hdmarx != NULL)
  {
    if (HAL_OK != HAL_DMA_Abort(hspi->hdmarx))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);
      errorcode = HAL_ERROR;
    }
  }

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
  hspi->State = HAL_SPI_STATE_READY;
  return errorcode;
}

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi)
{
  uint32_t itsource = hspi->Instance->CR2;
  uint32_t itflag   = hspi->Instance->SR;

  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) == RESET) &&
      (SPI_CHECK_FLAG(itflag, SPI_FLAG_RXNE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_RXNE) != RESET))
  {
    hspi->RxISR(hspi);
    return;
  }

  if ((SPI_CHECK_FLAG(itflag, SPI_FLAG_TXE) != RESET) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_TXE) != RESET))
  {
    hspi->TxISR(hspi);
    return;
  }

  if (((SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET) || (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET)
       || (SPI_CHECK_FLAG(itflag, SPI_FLAG_FRE) != RESET)) && (SPI_CHECK_IT_SOURCE(itsource, SPI_IT_ERR) != RESET))
  {

    if (SPI_CHECK_FLAG(itflag, SPI_FLAG_OVR) != RESET)
    {
      if (hspi->State != HAL_SPI_STATE_BUSY_TX)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_OVR);
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
      }
      else
      {
        __HAL_SPI_CLEAR_OVRFLAG(hspi);
        return;
      }
    }

    if (SPI_CHECK_FLAG(itflag, SPI_FLAG_MODF) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_MODF);
      __HAL_SPI_CLEAR_MODFFLAG(hspi);
    }

    if (SPI_CHECK_FLAG(itflag, SPI_FLAG_FRE) != RESET)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FRE);
      __HAL_SPI_CLEAR_FREFLAG(hspi);
    }

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {

      __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE | SPI_IT_TXE | SPI_IT_ERR);

      hspi->State = HAL_SPI_STATE_READY;

      if ((HAL_IS_BIT_SET(itsource, SPI_CR2_TXDMAEN)) || (HAL_IS_BIT_SET(itsource, SPI_CR2_RXDMAEN)))
      {
        CLEAR_BIT(hspi->Instance->CR2, (SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN));

        if (hspi->hdmarx != NULL)
        {

          hspi->hdmarx->XferAbortCallback = SPI_DMAAbortOnError;
          if (HAL_OK != HAL_DMA_Abort_IT(hspi->hdmarx))
          {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
          }
        }

        if (hspi->hdmatx != NULL)
        {

          hspi->hdmatx->XferAbortCallback = SPI_DMAAbortOnError;
          if (HAL_OK != HAL_DMA_Abort_IT(hspi->hdmatx))
          {
            SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
          }
        }
      }
      else
      {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
        hspi->ErrorCallback(hspi);
#else
        HAL_SPI_ErrorCallback(hspi);
#endif
      }
    }
    return;
  }
}

__weak void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

__weak void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi)
{

  UNUSED(hspi);

}

HAL_SPI_StateTypeDef HAL_SPI_GetState(const SPI_HandleTypeDef *hspi)
{

  return hspi->State;
}

uint32_t HAL_SPI_GetError(const SPI_HandleTypeDef *hspi)
{

  return hspi->ErrorCode;
}

static void SPI_DMATransmitCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);
  uint32_t tickstart;

  tickstart = HAL_GetTick();

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) != DMA_SxCR_CIRC)
  {

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);

    if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
    {
      __HAL_SPI_CLEAR_OVRFLAG(hspi);
    }

    hspi->TxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->ErrorCallback(hspi);
#else
      HAL_SPI_ErrorCallback(hspi);
#endif
      return;
    }
  }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->TxCpltCallback(hspi);
#else
  HAL_SPI_TxCpltCallback(hspi);
#endif
}

static void SPI_DMAReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);
  uint32_t tickstart;
#if (USE_SPI_CRC != 0U)
  __IO uint32_t tmpreg = 0U;
#endif

  tickstart = HAL_GetTick();

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) != DMA_SxCR_CIRC)
  {

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

#if (USE_SPI_CRC != 0U)

    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SET, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
      {

        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      }

      tmpreg = READ_REG(hspi->Instance->DR);

      UNUSED(tmpreg);
    }
#endif

    if ((hspi->Init.Direction == SPI_DIRECTION_2LINES) && (hspi->Init.Mode == SPI_MODE_MASTER))
    {

      CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);
    }
    else
    {

      CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);
    }

    if (SPI_EndRxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
    {
      hspi->ErrorCode = HAL_SPI_ERROR_FLAG;
    }

    hspi->RxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

#if (USE_SPI_CRC != 0U)

    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
#endif

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->ErrorCallback(hspi);
#else
      HAL_SPI_ErrorCallback(hspi);
#endif
      return;
    }
  }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->RxCpltCallback(hspi);
#else
  HAL_SPI_RxCpltCallback(hspi);
#endif
}

static void SPI_DMATransmitReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);
  uint32_t tickstart;
#if (USE_SPI_CRC != 0U)
  __IO uint32_t tmpreg = 0U;
#endif

  tickstart = HAL_GetTick();

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) != DMA_SxCR_CIRC)
  {

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

#if (USE_SPI_CRC != 0U)

    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, SET, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      }

      tmpreg = READ_REG(hspi->Instance->DR);

      UNUSED(tmpreg);
    }
#endif

    if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    }

    CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

    hspi->TxXferCount = 0U;
    hspi->RxXferCount = 0U;
    hspi->State = HAL_SPI_STATE_READY;

#if (USE_SPI_CRC != 0U)

    if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR))
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
      __HAL_SPI_CLEAR_CRCERRFLAG(hspi);
    }
#endif

    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->ErrorCallback(hspi);
#else
      HAL_SPI_ErrorCallback(hspi);
#endif
      return;
    }
  }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->TxRxCpltCallback(hspi);
#else
  HAL_SPI_TxRxCpltCallback(hspi);
#endif
}

static void SPI_DMAHalfTransmitCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->TxHalfCpltCallback(hspi);
#else
  HAL_SPI_TxHalfCpltCallback(hspi);
#endif
}

static void SPI_DMAHalfReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->RxHalfCpltCallback(hspi);
#else
  HAL_SPI_RxHalfCpltCallback(hspi);
#endif
}

static void SPI_DMAHalfTransmitReceiveCplt(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->TxRxHalfCpltCallback(hspi);
#else
  HAL_SPI_TxRxHalfCpltCallback(hspi);
#endif
}

static void SPI_DMAError(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN);

  SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_DMA);
  hspi->State = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->ErrorCallback(hspi);
#else
  HAL_SPI_ErrorCallback(hspi);
#endif
}

static void SPI_DMAAbortOnError(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);
  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->ErrorCallback(hspi);
#else
  HAL_SPI_ErrorCallback(hspi);
#endif
}

static void SPI_DMATxAbortCallback(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);
  __IO uint32_t count;

  hspi->hdmatx->XferAbortCallback = NULL;
  count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_TXDMAEN);

  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  if (hspi->hdmarx != NULL)
  {
    if (hspi->hdmarx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  if (hspi->ErrorCode != HAL_SPI_ERROR_ABORT)
  {

    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);

  hspi->State  = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->AbortCpltCallback(hspi);
#else
  HAL_SPI_AbortCpltCallback(hspi);
#endif
}

static void SPI_DMARxAbortCallback(DMA_HandleTypeDef *hdma)
{
  SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)(((DMA_HandleTypeDef *)hdma)->Parent);

  __HAL_SPI_DISABLE(hspi);

  hspi->hdmarx->XferAbortCallback = NULL;

  CLEAR_BIT(hspi->Instance->CR2, SPI_CR2_RXDMAEN);

  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
  }

  if (hspi->hdmatx != NULL)
  {
    if (hspi->hdmatx->XferAbortCallback != NULL)
    {
      return;
    }
  }

  hspi->RxXferCount = 0U;
  hspi->TxXferCount = 0U;

  if (hspi->ErrorCode != HAL_SPI_ERROR_ABORT)
  {

    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
  }

  __HAL_SPI_CLEAR_OVRFLAG(hspi);
  __HAL_SPI_CLEAR_FREFLAG(hspi);

  hspi->State  = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  hspi->AbortCpltCallback(hspi);
#else
  HAL_SPI_AbortCpltCallback(hspi);
#endif
}

static void SPI_2linesRxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{

  *hspi->pRxBuffPtr = *((__IO uint8_t *)&hspi->Instance->DR);
  hspi->pRxBuffPtr++;
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      hspi->RxISR =  SPI_2linesRxISR_8BITCRC;
      return;
    }
#endif

    __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

#if (USE_SPI_CRC != 0U)

static void SPI_2linesRxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint8_t  *ptmpreg8;
  __IO uint8_t  tmpreg8 = 0;

  ptmpreg8 = (__IO uint8_t *)&hspi->Instance->DR;

  tmpreg8 = *ptmpreg8;

  UNUSED(tmpreg8);

  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

  if (hspi->TxXferCount == 0U)
  {
    SPI_CloseRxTx_ISR(hspi);
  }
}
#endif

static void SPI_2linesTxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(__IO uint8_t *)&hspi->Instance->DR = *((const uint8_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr++;
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);

      __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);
      return;
    }
#endif

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

static void SPI_2linesRxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{

  *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)(hspi->Instance->DR);
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

  if (hspi->RxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      hspi->RxISR =  SPI_2linesRxISR_16BITCRC;
      return;
    }
#endif

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE);

    if (hspi->TxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

#if (USE_SPI_CRC != 0U)

static void SPI_2linesRxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint32_t tmpreg = 0U;

  tmpreg = READ_REG(hspi->Instance->DR);

  UNUSED(tmpreg);

  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_RXNE);

  SPI_CloseRxTx_ISR(hspi);
}
#endif

static void SPI_2linesTxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{

  hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);

      __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);
      return;
    }
#endif

    __HAL_SPI_DISABLE_IT(hspi, SPI_IT_TXE);

    if (hspi->RxXferCount == 0U)
    {
      SPI_CloseRxTx_ISR(hspi);
    }
  }
}

#if (USE_SPI_CRC != 0U)

static void SPI_RxISR_8BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint8_t  *ptmpreg8;
  __IO uint8_t  tmpreg8 = 0;

  ptmpreg8 = (__IO uint8_t *)&hspi->Instance->DR;

  tmpreg8 = *ptmpreg8;

  UNUSED(tmpreg8);

  SPI_CloseRx_ISR(hspi);
}
#endif

static void SPI_RxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *hspi->pRxBuffPtr = (*(__IO uint8_t *)&hspi->Instance->DR);
  hspi->pRxBuffPtr++;
  hspi->RxXferCount--;

#if (USE_SPI_CRC != 0U)

  if ((hspi->RxXferCount == 1U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
  {
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
  }
#endif

  if (hspi->RxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      hspi->RxISR =  SPI_RxISR_8BITCRC;
      return;
    }
#endif
    SPI_CloseRx_ISR(hspi);
  }
}

#if (USE_SPI_CRC != 0U)

static void SPI_RxISR_16BITCRC(struct __SPI_HandleTypeDef *hspi)
{
  __IO uint32_t tmpreg = 0U;

  tmpreg = READ_REG(hspi->Instance->DR);

  UNUSED(tmpreg);

  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

  SPI_CloseRx_ISR(hspi);
}
#endif

static void SPI_RxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{
  *((uint16_t *)hspi->pRxBuffPtr) = (uint16_t)(hspi->Instance->DR);
  hspi->pRxBuffPtr += sizeof(uint16_t);
  hspi->RxXferCount--;

#if (USE_SPI_CRC != 0U)

  if ((hspi->RxXferCount == 1U) && (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE))
  {
    SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
  }
#endif

  if (hspi->RxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
      hspi->RxISR = SPI_RxISR_16BITCRC;
      return;
    }
#endif
    SPI_CloseRx_ISR(hspi);
  }
}

static void SPI_TxISR_8BIT(struct __SPI_HandleTypeDef *hspi)
{
  *(__IO uint8_t *)&hspi->Instance->DR = *((const uint8_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr++;
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
    }
#endif
    SPI_CloseTx_ISR(hspi);
  }
}

static void SPI_TxISR_16BIT(struct __SPI_HandleTypeDef *hspi)
{

  hspi->Instance->DR = *((const uint16_t *)hspi->pTxBuffPtr);
  hspi->pTxBuffPtr += sizeof(uint16_t);
  hspi->TxXferCount--;

  if (hspi->TxXferCount == 0U)
  {
#if (USE_SPI_CRC != 0U)
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {

      SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
    }
#endif
    SPI_CloseTx_ISR(hspi);
  }
}

static HAL_StatusTypeDef SPI_WaitFlagStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Flag, FlagStatus State,
                                                       uint32_t Timeout, uint32_t Tickstart)
{
  __IO uint32_t count;
  uint32_t tmp_timeout;
  uint32_t tmp_tickstart;

  tmp_timeout   = Timeout - (HAL_GetTick() - Tickstart);
  tmp_tickstart = HAL_GetTick();

  count = tmp_timeout * ((SystemCoreClock * 32U) >> 20U);

  while ((__HAL_SPI_GET_FLAG(hspi, Flag) ? SET : RESET) != State)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tmp_tickstart) >= tmp_timeout) || (tmp_timeout == 0U))
      {

        __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

        if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
                                                     || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
        {

          __HAL_SPI_DISABLE(hspi);
        }

        if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
        {
          SPI_RESET_CRC(hspi);
        }

        hspi->State = HAL_SPI_STATE_READY;

        __HAL_UNLOCK(hspi);

        return HAL_TIMEOUT;
      }

      if (count == 0U)
      {
        tmp_timeout = 0U;
      }
      else
      {
        count--;
      }
    }
  }

  return HAL_OK;
}

static HAL_StatusTypeDef SPI_EndRxTransaction(SPI_HandleTypeDef *hspi,  uint32_t Timeout, uint32_t Tickstart)
{
  if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE)
                                               || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
  {

    __HAL_SPI_DISABLE(hspi);
  }

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {
    if (hspi->Init.Direction != SPI_DIRECTION_2LINES_RXONLY)
    {

      if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_BSY, RESET, Timeout, Tickstart) != HAL_OK)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
        return HAL_TIMEOUT;
      }
    }
    else
    {

      if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, RESET, Timeout, Tickstart) != HAL_OK)
      {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {

    if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_RXNE, RESET, Timeout, Tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      return HAL_TIMEOUT;
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef SPI_EndRxTxTransaction(SPI_HandleTypeDef *hspi, uint32_t Timeout, uint32_t Tickstart)
{
  __IO uint32_t count;

  if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_TXE, SET, Timeout, Tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
    return HAL_TIMEOUT;
  }

  count = SPI_BSY_FLAG_WORKAROUND_TIMEOUT * (SystemCoreClock / 24U / 1000000U);

  if (hspi->Init.Mode == SPI_MODE_MASTER)
  {

    if (SPI_WaitFlagStateUntilTimeout(hspi, SPI_FLAG_BSY, RESET, Timeout, Tickstart) != HAL_OK)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      return HAL_TIMEOUT;
    }
  }
  else
  {

    do
    {
      if (count == 0U)
      {
        break;
      }
      count--;
    } while (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_BSY) != RESET);
  }

  return HAL_OK;
}

static void SPI_CloseRxTx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart;
  __IO uint32_t count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  tickstart = HAL_GetTick();

  __HAL_SPI_DISABLE_IT(hspi, SPI_IT_ERR);

  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

#if (USE_SPI_CRC != 0U)

  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    hspi->State = HAL_SPI_STATE_READY;
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    hspi->ErrorCallback(hspi);
#else
    HAL_SPI_ErrorCallback(hspi);
#endif
  }
  else
  {
#endif
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {
      if (hspi->State == HAL_SPI_STATE_BUSY_RX)
      {
        hspi->State = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
        hspi->RxCpltCallback(hspi);
#else
        HAL_SPI_RxCpltCallback(hspi);
#endif
      }
      else
      {
        hspi->State = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
        hspi->TxRxCpltCallback(hspi);
#else
        HAL_SPI_TxRxCpltCallback(hspi);
#endif
      }
    }
    else
    {
      hspi->State = HAL_SPI_STATE_READY;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->ErrorCallback(hspi);
#else
      HAL_SPI_ErrorCallback(hspi);
#endif
    }
#if (USE_SPI_CRC != 0U)
  }
#endif
}

static void SPI_CloseRx_ISR(SPI_HandleTypeDef *hspi)
{

  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_RXNE | SPI_IT_ERR));

  if (SPI_EndRxTransaction(hspi, SPI_DEFAULT_TIMEOUT, HAL_GetTick()) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }
  hspi->State = HAL_SPI_STATE_READY;

#if (USE_SPI_CRC != 0U)

  if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_CRCERR) != RESET)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_CRC);
    __HAL_SPI_CLEAR_CRCERRFLAG(hspi);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    hspi->ErrorCallback(hspi);
#else
    HAL_SPI_ErrorCallback(hspi);
#endif
  }
  else
  {
#endif
    if (hspi->ErrorCode == HAL_SPI_ERROR_NONE)
    {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->RxCpltCallback(hspi);
#else
      HAL_SPI_RxCpltCallback(hspi);
#endif
    }
    else
    {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
      hspi->ErrorCallback(hspi);
#else
      HAL_SPI_ErrorCallback(hspi);
#endif
    }
#if (USE_SPI_CRC != 0U)
  }
#endif
}

static void SPI_CloseTx_ISR(SPI_HandleTypeDef *hspi)
{
  uint32_t tickstart;
  __IO uint32_t count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  tickstart = HAL_GetTick();

  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_ERR));

  if (SPI_EndRxTxTransaction(hspi, SPI_DEFAULT_TIMEOUT, tickstart) != HAL_OK)
  {
    SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
  }

  if (hspi->Init.Direction == SPI_DIRECTION_2LINES)
  {
    __HAL_SPI_CLEAR_OVRFLAG(hspi);
  }

  hspi->State = HAL_SPI_STATE_READY;
  if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
  {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    hspi->ErrorCallback(hspi);
#else
    HAL_SPI_ErrorCallback(hspi);
#endif
  }
  else
  {

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    hspi->TxCpltCallback(hspi);
#else
    HAL_SPI_TxCpltCallback(hspi);
#endif
  }
}

static void SPI_AbortRx_ISR(SPI_HandleTypeDef *hspi)
{
  __IO uint32_t tmpreg = 0U;
  __IO uint32_t count = SPI_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  do
  {
    if (count == 0U)
    {
      SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_ABORT);
      break;
    }
    count--;
  } while ((hspi->Instance->SR & SPI_FLAG_TXE) == RESET);

  __HAL_SPI_DISABLE(hspi);

  CLEAR_BIT(hspi->Instance->CR2, (SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE));

  tmpreg = READ_REG(hspi->Instance->DR);

  UNUSED(tmpreg);

  hspi->State = HAL_SPI_STATE_ABORT;
}

static void SPI_AbortTx_ISR(SPI_HandleTypeDef *hspi)
{

  CLEAR_BIT(hspi->Instance->CR2, (SPI_CR2_TXEIE));

  __HAL_SPI_DISABLE(hspi);

  hspi->State = HAL_SPI_STATE_ABORT;
}

#endif
