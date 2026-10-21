#include "stm32f4xx_hal.h"

#ifdef HAL_DMA_MODULE_ENABLED

typedef struct
{
  __IO uint32_t ISR;
  __IO uint32_t Reserved0;
  __IO uint32_t IFCR;
} DMA_Base_Registers;

 #define HAL_TIMEOUT_DMA_ABORT    5U

static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef *hdma);
static HAL_StatusTypeDef DMA_CheckFifoParam(DMA_HandleTypeDef *hdma);

HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma)
{
  uint32_t tmp = 0U;
  uint32_t tickstart = HAL_GetTick();
  DMA_Base_Registers *regs;

  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_DMA_STREAM_ALL_INSTANCE(hdma->Instance));
  assert_param(IS_DMA_CHANNEL(hdma->Init.Channel));
  assert_param(IS_DMA_DIRECTION(hdma->Init.Direction));
  assert_param(IS_DMA_PERIPHERAL_INC_STATE(hdma->Init.PeriphInc));
  assert_param(IS_DMA_MEMORY_INC_STATE(hdma->Init.MemInc));
  assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(hdma->Init.PeriphDataAlignment));
  assert_param(IS_DMA_MEMORY_DATA_SIZE(hdma->Init.MemDataAlignment));
  assert_param(IS_DMA_MODE(hdma->Init.Mode));
  assert_param(IS_DMA_PRIORITY(hdma->Init.Priority));
  assert_param(IS_DMA_FIFO_MODE_STATE(hdma->Init.FIFOMode));

  if(hdma->Init.FIFOMode != DMA_FIFOMODE_DISABLE)
  {
    assert_param(IS_DMA_FIFO_THRESHOLD(hdma->Init.FIFOThreshold));
    assert_param(IS_DMA_MEMORY_BURST(hdma->Init.MemBurst));
    assert_param(IS_DMA_PERIPHERAL_BURST(hdma->Init.PeriphBurst));
  }

  hdma->State = HAL_DMA_STATE_BUSY;

  __HAL_UNLOCK(hdma);

  __HAL_DMA_DISABLE(hdma);

  while((hdma->Instance->CR & DMA_SxCR_EN) != RESET)
  {

    if((HAL_GetTick() - tickstart ) > HAL_TIMEOUT_DMA_ABORT)
    {

      hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

      hdma->State = HAL_DMA_STATE_TIMEOUT;

      return HAL_TIMEOUT;
    }
  }

  tmp = hdma->Instance->CR;

  tmp &= ((uint32_t)~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | \
                      DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  | \
                      DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   | \
                      DMA_SxCR_DIR   | DMA_SxCR_CT     | DMA_SxCR_DBM));

  tmp |=  hdma->Init.Channel             | hdma->Init.Direction        |
          hdma->Init.PeriphInc           | hdma->Init.MemInc           |
          hdma->Init.PeriphDataAlignment | hdma->Init.MemDataAlignment |
          hdma->Init.Mode                | hdma->Init.Priority;

  if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE)
  {

    tmp |=  hdma->Init.MemBurst | hdma->Init.PeriphBurst;
  }

  hdma->Instance->CR = tmp;

  tmp = hdma->Instance->FCR;

  tmp &= (uint32_t)~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

  tmp |= hdma->Init.FIFOMode;

  if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE)
  {

    tmp |= hdma->Init.FIFOThreshold;

    if (hdma->Init.MemBurst != DMA_MBURST_SINGLE)
    {
      if (DMA_CheckFifoParam(hdma) != HAL_OK)
      {

        hdma->ErrorCode = HAL_DMA_ERROR_PARAM;

        hdma->State = HAL_DMA_STATE_READY;

        return HAL_ERROR;
      }
    }
  }

  hdma->Instance->FCR = tmp;

  regs = (DMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

  regs->IFCR = 0x3FU << hdma->StreamIndex;

  hdma->ErrorCode = HAL_DMA_ERROR_NONE;

  hdma->State = HAL_DMA_STATE_READY;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma)
{
  DMA_Base_Registers *regs;

  if(hdma == NULL)
  {
    return HAL_ERROR;
  }

  if(hdma->State == HAL_DMA_STATE_BUSY)
  {

    return HAL_BUSY;
  }

  assert_param(IS_DMA_STREAM_ALL_INSTANCE(hdma->Instance));

  __HAL_DMA_DISABLE(hdma);

  hdma->Instance->CR   = 0U;

  hdma->Instance->NDTR = 0U;

  hdma->Instance->PAR  = 0U;

  hdma->Instance->M0AR = 0U;

  hdma->Instance->M1AR = 0U;

  hdma->Instance->FCR  = 0x00000021U;

  regs = (DMA_Base_Registers *)DMA_CalcBaseAndBitshift(hdma);

  hdma->XferCpltCallback = NULL;
  hdma->XferHalfCpltCallback = NULL;
  hdma->XferM1CpltCallback = NULL;
  hdma->XferM1HalfCpltCallback = NULL;
  hdma->XferErrorCallback = NULL;
  hdma->XferAbortCallback = NULL;

  regs->IFCR = 0x3FU << hdma->StreamIndex;

  hdma->ErrorCode = HAL_DMA_ERROR_NONE;

  hdma->State = HAL_DMA_STATE_RESET;

  __HAL_UNLOCK(hdma);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_DMA_Start(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_DMA_BUFFER_SIZE(DataLength));

  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {

    hdma->State = HAL_DMA_STATE_BUSY;

    hdma->ErrorCode = HAL_DMA_ERROR_NONE;

    DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);

    __HAL_DMA_ENABLE(hdma);
  }
  else
  {

    __HAL_UNLOCK(hdma);

    status = HAL_BUSY;
  }
  return status;
}

HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;

  DMA_Base_Registers *regs = (DMA_Base_Registers *)hdma->StreamBaseAddress;

  assert_param(IS_DMA_BUFFER_SIZE(DataLength));

  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {

    hdma->State = HAL_DMA_STATE_BUSY;

    hdma->ErrorCode = HAL_DMA_ERROR_NONE;

    DMA_SetConfig(hdma, SrcAddress, DstAddress, DataLength);

    regs->IFCR = 0x3FU << hdma->StreamIndex;

    hdma->Instance->CR  |= DMA_IT_TC | DMA_IT_TE | DMA_IT_DME;

    if(hdma->XferHalfCpltCallback != NULL)
    {
      hdma->Instance->CR  |= DMA_IT_HT;
    }

    __HAL_DMA_ENABLE(hdma);
  }
  else
  {

    __HAL_UNLOCK(hdma);

    status = HAL_BUSY;
  }

  return status;
}

HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma)
{

  DMA_Base_Registers *regs = (DMA_Base_Registers *)hdma->StreamBaseAddress;

  uint32_t tickstart = HAL_GetTick();

  if(hdma->State != HAL_DMA_STATE_BUSY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;

    __HAL_UNLOCK(hdma);

    return HAL_ERROR;
  }
  else
  {

    hdma->Instance->CR  &= ~(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
    hdma->Instance->FCR &= ~(DMA_IT_FE);

    if((hdma->XferHalfCpltCallback != NULL) || (hdma->XferM1HalfCpltCallback != NULL))
    {
      hdma->Instance->CR  &= ~(DMA_IT_HT);
    }

    __HAL_DMA_DISABLE(hdma);

    while((hdma->Instance->CR & DMA_SxCR_EN) != RESET)
    {

      if((HAL_GetTick() - tickstart ) > HAL_TIMEOUT_DMA_ABORT)
      {

        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        hdma->State = HAL_DMA_STATE_TIMEOUT;

        __HAL_UNLOCK(hdma);

        return HAL_TIMEOUT;
      }
    }

    regs->IFCR = 0x3FU << hdma->StreamIndex;

    hdma->State = HAL_DMA_STATE_READY;

    __HAL_UNLOCK(hdma);
  }
  return HAL_OK;
}

HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma)
{
  if(hdma->State != HAL_DMA_STATE_BUSY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;
    return HAL_ERROR;
  }
  else
  {

    hdma->State = HAL_DMA_STATE_ABORT;

    __HAL_DMA_DISABLE(hdma);
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t mask_cpltlevel;
  uint32_t tickstart = HAL_GetTick();
  uint32_t tmpisr;

  DMA_Base_Registers *regs;

  if(HAL_DMA_STATE_BUSY != hdma->State)
  {

    hdma->ErrorCode = HAL_DMA_ERROR_NO_XFER;
    __HAL_UNLOCK(hdma);
    return HAL_ERROR;
  }

  if ((hdma->Instance->CR & DMA_SxCR_CIRC) != RESET)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NOT_SUPPORTED;
    return HAL_ERROR;
  }

  if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
  {

    mask_cpltlevel = DMA_FLAG_TCIF0_4 << hdma->StreamIndex;
  }
  else
  {

    mask_cpltlevel = DMA_FLAG_HTIF0_4 << hdma->StreamIndex;
  }

  regs = (DMA_Base_Registers *)hdma->StreamBaseAddress;
  tmpisr = regs->ISR;

  while(((tmpisr & mask_cpltlevel) == RESET) && ((hdma->ErrorCode & HAL_DMA_ERROR_TE) == RESET))
  {

    if(Timeout != HAL_MAX_DELAY)
    {
      if((Timeout == 0U)||((HAL_GetTick() - tickstart ) > Timeout))
      {

        hdma->ErrorCode = HAL_DMA_ERROR_TIMEOUT;

        hdma->State = HAL_DMA_STATE_READY;

        __HAL_UNLOCK(hdma);

        return HAL_TIMEOUT;
      }
    }

    tmpisr = regs->ISR;

    if((tmpisr & (DMA_FLAG_TEIF0_4 << hdma->StreamIndex)) != RESET)
    {

      hdma->ErrorCode |= HAL_DMA_ERROR_TE;

      regs->IFCR = DMA_FLAG_TEIF0_4 << hdma->StreamIndex;
    }

    if((tmpisr & (DMA_FLAG_FEIF0_4 << hdma->StreamIndex)) != RESET)
    {

      hdma->ErrorCode |= HAL_DMA_ERROR_FE;

      regs->IFCR = DMA_FLAG_FEIF0_4 << hdma->StreamIndex;
    }

    if((tmpisr & (DMA_FLAG_DMEIF0_4 << hdma->StreamIndex)) != RESET)
    {

      hdma->ErrorCode |= HAL_DMA_ERROR_DME;

      regs->IFCR = DMA_FLAG_DMEIF0_4 << hdma->StreamIndex;
    }
  }

  if(hdma->ErrorCode != HAL_DMA_ERROR_NONE)
  {
    if((hdma->ErrorCode & HAL_DMA_ERROR_TE) != RESET)
    {
      HAL_DMA_Abort(hdma);

      regs->IFCR = (DMA_FLAG_HTIF0_4 | DMA_FLAG_TCIF0_4) << hdma->StreamIndex;

      hdma->State= HAL_DMA_STATE_READY;

      __HAL_UNLOCK(hdma);

      return HAL_ERROR;
   }
  }

  if(CompleteLevel == HAL_DMA_FULL_TRANSFER)
  {

    regs->IFCR = (DMA_FLAG_HTIF0_4 | DMA_FLAG_TCIF0_4) << hdma->StreamIndex;

    hdma->State = HAL_DMA_STATE_READY;

    __HAL_UNLOCK(hdma);
  }
  else
  {

    regs->IFCR = (DMA_FLAG_HTIF0_4) << hdma->StreamIndex;
  }

  return status;
}

void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)
{
  uint32_t tmpisr;
  __IO uint32_t count = 0U;
  uint32_t timeout = SystemCoreClock / 9600U;

  DMA_Base_Registers *regs = (DMA_Base_Registers *)hdma->StreamBaseAddress;

  tmpisr = regs->ISR;

  if ((tmpisr & (DMA_FLAG_TEIF0_4 << hdma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TE) != RESET)
    {

      hdma->Instance->CR  &= ~(DMA_IT_TE);

      regs->IFCR = DMA_FLAG_TEIF0_4 << hdma->StreamIndex;

      hdma->ErrorCode |= HAL_DMA_ERROR_TE;
    }
  }

  if ((tmpisr & (DMA_FLAG_FEIF0_4 << hdma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_FE) != RESET)
    {

      regs->IFCR = DMA_FLAG_FEIF0_4 << hdma->StreamIndex;

      hdma->ErrorCode |= HAL_DMA_ERROR_FE;
    }
  }

  if ((tmpisr & (DMA_FLAG_DMEIF0_4 << hdma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_DME) != RESET)
    {

      regs->IFCR = DMA_FLAG_DMEIF0_4 << hdma->StreamIndex;

      hdma->ErrorCode |= HAL_DMA_ERROR_DME;
    }
  }

  if ((tmpisr & (DMA_FLAG_HTIF0_4 << hdma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_HT) != RESET)
    {

      regs->IFCR = DMA_FLAG_HTIF0_4 << hdma->StreamIndex;

      if(((hdma->Instance->CR) & (uint32_t)(DMA_SxCR_DBM)) != RESET)
      {

        if((hdma->Instance->CR & DMA_SxCR_CT) == RESET)
        {
          if(hdma->XferHalfCpltCallback != NULL)
          {

            hdma->XferHalfCpltCallback(hdma);
          }
        }

        else
        {
          if(hdma->XferM1HalfCpltCallback != NULL)
          {

            hdma->XferM1HalfCpltCallback(hdma);
          }
        }
      }
      else
      {

        if((hdma->Instance->CR & DMA_SxCR_CIRC) == RESET)
        {

          hdma->Instance->CR  &= ~(DMA_IT_HT);
        }

        if(hdma->XferHalfCpltCallback != NULL)
        {

          hdma->XferHalfCpltCallback(hdma);
        }
      }
    }
  }

  if ((tmpisr & (DMA_FLAG_TCIF0_4 << hdma->StreamIndex)) != RESET)
  {
    if(__HAL_DMA_GET_IT_SOURCE(hdma, DMA_IT_TC) != RESET)
    {

      regs->IFCR = DMA_FLAG_TCIF0_4 << hdma->StreamIndex;

      if(HAL_DMA_STATE_ABORT == hdma->State)
      {

        hdma->Instance->CR  &= ~(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
        hdma->Instance->FCR &= ~(DMA_IT_FE);

        if((hdma->XferHalfCpltCallback != NULL) || (hdma->XferM1HalfCpltCallback != NULL))
        {
          hdma->Instance->CR  &= ~(DMA_IT_HT);
        }

        regs->IFCR = 0x3FU << hdma->StreamIndex;

        hdma->State = HAL_DMA_STATE_READY;

        __HAL_UNLOCK(hdma);

        if(hdma->XferAbortCallback != NULL)
        {
          hdma->XferAbortCallback(hdma);
        }
        return;
      }

      if(((hdma->Instance->CR) & (uint32_t)(DMA_SxCR_DBM)) != RESET)
      {

        if((hdma->Instance->CR & DMA_SxCR_CT) == RESET)
        {
          if(hdma->XferM1CpltCallback != NULL)
          {

            hdma->XferM1CpltCallback(hdma);
          }
        }

        else
        {
          if(hdma->XferCpltCallback != NULL)
          {

            hdma->XferCpltCallback(hdma);
          }
        }
      }

      else
      {
        if((hdma->Instance->CR & DMA_SxCR_CIRC) == RESET)
        {

          hdma->Instance->CR  &= ~(DMA_IT_TC);

          hdma->State = HAL_DMA_STATE_READY;

          __HAL_UNLOCK(hdma);
        }

        if(hdma->XferCpltCallback != NULL)
        {

          hdma->XferCpltCallback(hdma);
        }
      }
    }
  }

  if(hdma->ErrorCode != HAL_DMA_ERROR_NONE)
  {
    if((hdma->ErrorCode & HAL_DMA_ERROR_TE) != RESET)
    {
      hdma->State = HAL_DMA_STATE_ABORT;

      __HAL_DMA_DISABLE(hdma);

      do
      {
        if (++count > timeout)
        {
          break;
        }
      }
      while((hdma->Instance->CR & DMA_SxCR_EN) != RESET);

      hdma->State = HAL_DMA_STATE_READY;

      __HAL_UNLOCK(hdma);
    }

    if(hdma->XferErrorCallback != NULL)
    {

      hdma->XferErrorCallback(hdma);
    }
  }
}

HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma))
{

  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_DMA_XFER_CPLT_CB_ID:
      hdma->XferCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_HALFCPLT_CB_ID:
      hdma->XferHalfCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_M1CPLT_CB_ID:
      hdma->XferM1CpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_M1HALFCPLT_CB_ID:
      hdma->XferM1HalfCpltCallback = pCallback;
      break;

    case  HAL_DMA_XFER_ERROR_CB_ID:
      hdma->XferErrorCallback = pCallback;
      break;

    case  HAL_DMA_XFER_ABORT_CB_ID:
      hdma->XferAbortCallback = pCallback;
      break;

    default:

      status =  HAL_ERROR;
      break;
    }
  }
  else
  {

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hdma);

  return status;
}

HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hdma);

  if(HAL_DMA_STATE_READY == hdma->State)
  {
    switch (CallbackID)
    {
    case  HAL_DMA_XFER_CPLT_CB_ID:
      hdma->XferCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_HALFCPLT_CB_ID:
      hdma->XferHalfCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_M1CPLT_CB_ID:
      hdma->XferM1CpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_M1HALFCPLT_CB_ID:
      hdma->XferM1HalfCpltCallback = NULL;
      break;

    case  HAL_DMA_XFER_ERROR_CB_ID:
      hdma->XferErrorCallback = NULL;
      break;

    case  HAL_DMA_XFER_ABORT_CB_ID:
      hdma->XferAbortCallback = NULL;
      break;

    case   HAL_DMA_XFER_ALL_CB_ID:
      hdma->XferCpltCallback = NULL;
      hdma->XferHalfCpltCallback = NULL;
      hdma->XferM1CpltCallback = NULL;
      hdma->XferM1HalfCpltCallback = NULL;
      hdma->XferErrorCallback = NULL;
      hdma->XferAbortCallback = NULL;
      break;

    default:
      status = HAL_ERROR;
      break;
    }
  }
  else
  {
    status = HAL_ERROR;
  }

  __HAL_UNLOCK(hdma);

  return status;
}

HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma)
{
  return hdma->State;
}

uint32_t HAL_DMA_GetError(DMA_HandleTypeDef *hdma)
{
  return hdma->ErrorCode;
}

static void DMA_SetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{

  hdma->Instance->CR &= (uint32_t)(~DMA_SxCR_DBM);

  hdma->Instance->NDTR = DataLength;

  if((hdma->Init.Direction) == DMA_MEMORY_TO_PERIPH)
  {

    hdma->Instance->PAR = DstAddress;

    hdma->Instance->M0AR = SrcAddress;
  }

  else
  {

    hdma->Instance->PAR = SrcAddress;

    hdma->Instance->M0AR = DstAddress;
  }
}

static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef *hdma)
{
  uint32_t stream_number = (((uint32_t)hdma->Instance & 0xFFU) - 16U) / 24U;

  static const uint8_t flagBitshiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
  hdma->StreamIndex = flagBitshiftOffset[stream_number];

  if (stream_number > 3U)
  {

    hdma->StreamBaseAddress = (((uint32_t)hdma->Instance & (uint32_t)(~0x3FFU)) + 4U);
  }
  else
  {

    hdma->StreamBaseAddress = ((uint32_t)hdma->Instance & (uint32_t)(~0x3FFU));
  }

  return hdma->StreamBaseAddress;
}

static HAL_StatusTypeDef DMA_CheckFifoParam(DMA_HandleTypeDef *hdma)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t tmp = hdma->Init.FIFOThreshold;

  if(hdma->Init.MemDataAlignment == DMA_MDATAALIGN_BYTE)
  {
    switch (tmp)
    {
    case DMA_FIFO_THRESHOLD_1QUARTERFULL:
    case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
      if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
      {
        status = HAL_ERROR;
      }
      break;
    case DMA_FIFO_THRESHOLD_HALFFULL:
      if (hdma->Init.MemBurst == DMA_MBURST_INC16)
      {
        status = HAL_ERROR;
      }
      break;
    case DMA_FIFO_THRESHOLD_FULL:
      break;
    default:
      break;
    }
  }

  else if (hdma->Init.MemDataAlignment == DMA_MDATAALIGN_HALFWORD)
  {
    switch (tmp)
    {
    case DMA_FIFO_THRESHOLD_1QUARTERFULL:
    case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
      status = HAL_ERROR;
      break;
    case DMA_FIFO_THRESHOLD_HALFFULL:
      if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
      {
        status = HAL_ERROR;
      }
      break;
    case DMA_FIFO_THRESHOLD_FULL:
      if (hdma->Init.MemBurst == DMA_MBURST_INC16)
      {
        status = HAL_ERROR;
      }
      break;
    default:
      break;
    }
  }

  else
  {
    switch (tmp)
    {
    case DMA_FIFO_THRESHOLD_1QUARTERFULL:
    case DMA_FIFO_THRESHOLD_HALFFULL:
    case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
      status = HAL_ERROR;
      break;
    case DMA_FIFO_THRESHOLD_FULL:
      if ((hdma->Init.MemBurst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
      {
        status = HAL_ERROR;
      }
      break;
    default:
      break;
    }
  }

  return status;
}

#endif
