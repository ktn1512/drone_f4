#include "stm32f4xx_hal.h"

#ifdef HAL_I2C_MODULE_ENABLED

#define I2C_TIMEOUT_FLAG          35U
#define I2C_TIMEOUT_BUSY_FLAG     25U
#define I2C_TIMEOUT_STOP_FLAG     5U
#define I2C_NO_OPTION_FRAME       0xFFFF0000U

#define I2C_STATE_MSK             ((uint32_t)((uint32_t)((uint32_t)HAL_I2C_STATE_BUSY_TX | (uint32_t)HAL_I2C_STATE_BUSY_RX) & (uint32_t)(~((uint32_t)HAL_I2C_STATE_READY))))
#define I2C_STATE_NONE            ((uint32_t)(HAL_I2C_MODE_NONE))
#define I2C_STATE_MASTER_BUSY_TX  ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))
#define I2C_STATE_MASTER_BUSY_RX  ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))
#define I2C_STATE_SLAVE_BUSY_TX   ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))
#define I2C_STATE_SLAVE_BUSY_RX   ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))

#define I2C_GET_DMA_REMAIN_DATA(__HANDLE__)     __HAL_DMA_GET_COUNTER(__HANDLE__)

static void I2C_DMAXferCplt(DMA_HandleTypeDef *hdma);
static void I2C_DMAError(DMA_HandleTypeDef *hdma);
static void I2C_DMAAbort(DMA_HandleTypeDef *hdma);

static void I2C_ITError(I2C_HandleTypeDef *hi2c);

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_RequestMemoryWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart);

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnTXEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnBTFFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnRXNEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnSTOPFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart);
static HAL_StatusTypeDef I2C_WaitOnSTOPRequestThroughIT(I2C_HandleTypeDef *hi2c);
static HAL_StatusTypeDef I2C_IsAcknowledgeFailed(I2C_HandleTypeDef *hi2c);

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_MasterTransmit_BTF(I2C_HandleTypeDef *hi2c);
static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c);
static void I2C_MasterReceive_BTF(I2C_HandleTypeDef *hi2c);
static void I2C_Master_SB(I2C_HandleTypeDef *hi2c);
static void I2C_Master_ADD10(I2C_HandleTypeDef *hi2c);
static void I2C_Master_ADDR(I2C_HandleTypeDef *hi2c);

static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveTransmit_BTF(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c);
static void I2C_SlaveReceive_BTF(I2C_HandleTypeDef *hi2c);
static void I2C_Slave_ADDR(I2C_HandleTypeDef *hi2c, uint32_t IT2Flags);
static void I2C_Slave_STOPF(I2C_HandleTypeDef *hi2c);
static void I2C_Slave_AF(I2C_HandleTypeDef *hi2c);

static void I2C_MemoryTransmit_TXE_BTF(I2C_HandleTypeDef *hi2c);

static void I2C_ConvertOtherXferOptions(I2C_HandleTypeDef *hi2c);

static void I2C_Flush_DR(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c)
{
  uint32_t freqrange;
  uint32_t pclk1;

  if (hi2c == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  assert_param(IS_I2C_CLOCK_SPEED(hi2c->Init.ClockSpeed));
  assert_param(IS_I2C_DUTY_CYCLE(hi2c->Init.DutyCycle));
  assert_param(IS_I2C_OWN_ADDRESS1(hi2c->Init.OwnAddress1));
  assert_param(IS_I2C_ADDRESSING_MODE(hi2c->Init.AddressingMode));
  assert_param(IS_I2C_DUAL_ADDRESS(hi2c->Init.DualAddressMode));
  assert_param(IS_I2C_OWN_ADDRESS2(hi2c->Init.OwnAddress2));
  assert_param(IS_I2C_GENERAL_CALL(hi2c->Init.GeneralCallMode));
  assert_param(IS_I2C_NO_STRETCH(hi2c->Init.NoStretchMode));

  if (hi2c->State == HAL_I2C_STATE_RESET)
  {

    hi2c->Lock = HAL_UNLOCKED;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)

    hi2c->MasterTxCpltCallback = HAL_I2C_MasterTxCpltCallback;
    hi2c->MasterRxCpltCallback = HAL_I2C_MasterRxCpltCallback;
    hi2c->SlaveTxCpltCallback  = HAL_I2C_SlaveTxCpltCallback;
    hi2c->SlaveRxCpltCallback  = HAL_I2C_SlaveRxCpltCallback;
    hi2c->ListenCpltCallback   = HAL_I2C_ListenCpltCallback;
    hi2c->MemTxCpltCallback    = HAL_I2C_MemTxCpltCallback;
    hi2c->MemRxCpltCallback    = HAL_I2C_MemRxCpltCallback;
    hi2c->ErrorCallback        = HAL_I2C_ErrorCallback;
    hi2c->AbortCpltCallback    = HAL_I2C_AbortCpltCallback;
    hi2c->AddrCallback         = HAL_I2C_AddrCallback;

    if (hi2c->MspInitCallback == NULL)
    {
      hi2c->MspInitCallback = HAL_I2C_MspInit;
    }

    hi2c->MspInitCallback(hi2c);
#else

    HAL_I2C_MspInit(hi2c);
#endif
  }

  hi2c->State = HAL_I2C_STATE_BUSY;

  __HAL_I2C_DISABLE(hi2c);

  hi2c->Instance->CR1 |= I2C_CR1_SWRST;
  hi2c->Instance->CR1 &= ~I2C_CR1_SWRST;

  pclk1 = HAL_RCC_GetPCLK1Freq();

  if (I2C_MIN_PCLK_FREQ(pclk1, hi2c->Init.ClockSpeed) == 1U)
  {
    return HAL_ERROR;
  }

  freqrange = I2C_FREQRANGE(pclk1);

  MODIFY_REG(hi2c->Instance->CR2, I2C_CR2_FREQ, freqrange);

  MODIFY_REG(hi2c->Instance->TRISE, I2C_TRISE_TRISE, I2C_RISE_TIME(freqrange, hi2c->Init.ClockSpeed));

  MODIFY_REG(hi2c->Instance->CCR, (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR), I2C_SPEED(pclk1, hi2c->Init.ClockSpeed, hi2c->Init.DutyCycle));

  MODIFY_REG(hi2c->Instance->CR1, (I2C_CR1_ENGC | I2C_CR1_NOSTRETCH), (hi2c->Init.GeneralCallMode | hi2c->Init.NoStretchMode));

  MODIFY_REG(hi2c->Instance->OAR1, (I2C_OAR1_ADDMODE | I2C_OAR1_ADD8_9 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD0), (hi2c->Init.AddressingMode | hi2c->Init.OwnAddress1));

  MODIFY_REG(hi2c->Instance->OAR2, (I2C_OAR2_ENDUAL | I2C_OAR2_ADD2), (hi2c->Init.DualAddressMode | hi2c->Init.OwnAddress2));

  __HAL_I2C_ENABLE(hi2c);

  hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
  hi2c->State = HAL_I2C_STATE_READY;
  hi2c->PreviousState = I2C_STATE_NONE;
  hi2c->Mode = HAL_I2C_MODE_NONE;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c)
{

  if (hi2c == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));

  hi2c->State = HAL_I2C_STATE_BUSY;

  __HAL_I2C_DISABLE(hi2c);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
  if (hi2c->MspDeInitCallback == NULL)
  {
    hi2c->MspDeInitCallback = HAL_I2C_MspDeInit;
  }

  hi2c->MspDeInitCallback(hi2c);
#else

  HAL_I2C_MspDeInit(hi2c);
#endif

  hi2c->ErrorCode     = HAL_I2C_ERROR_NONE;
  hi2c->State         = HAL_I2C_STATE_RESET;
  hi2c->PreviousState = I2C_STATE_NONE;
  hi2c->Mode          = HAL_I2C_MODE_NONE;

  __HAL_UNLOCK(hi2c);

  return HAL_OK;
}

__weak void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)

HAL_StatusTypeDef HAL_I2C_RegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID, pI2C_CallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  __HAL_LOCK(hi2c);

  if (HAL_I2C_STATE_READY == hi2c->State)
  {
    switch (CallbackID)
    {
      case HAL_I2C_MASTER_TX_COMPLETE_CB_ID :
        hi2c->MasterTxCpltCallback = pCallback;
        break;

      case HAL_I2C_MASTER_RX_COMPLETE_CB_ID :
        hi2c->MasterRxCpltCallback = pCallback;
        break;

      case HAL_I2C_SLAVE_TX_COMPLETE_CB_ID :
        hi2c->SlaveTxCpltCallback = pCallback;
        break;

      case HAL_I2C_SLAVE_RX_COMPLETE_CB_ID :
        hi2c->SlaveRxCpltCallback = pCallback;
        break;

      case HAL_I2C_LISTEN_COMPLETE_CB_ID :
        hi2c->ListenCpltCallback = pCallback;
        break;

      case HAL_I2C_MEM_TX_COMPLETE_CB_ID :
        hi2c->MemTxCpltCallback = pCallback;
        break;

      case HAL_I2C_MEM_RX_COMPLETE_CB_ID :
        hi2c->MemRxCpltCallback = pCallback;
        break;

      case HAL_I2C_ERROR_CB_ID :
        hi2c->ErrorCallback = pCallback;
        break;

      case HAL_I2C_ABORT_CB_ID :
        hi2c->AbortCpltCallback = pCallback;
        break;

      case HAL_I2C_MSPINIT_CB_ID :
        hi2c->MspInitCallback = pCallback;
        break;

      case HAL_I2C_MSPDEINIT_CB_ID :
        hi2c->MspDeInitCallback = pCallback;
        break;

      default :

        hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_I2C_STATE_RESET == hi2c->State)
  {
    switch (CallbackID)
    {
      case HAL_I2C_MSPINIT_CB_ID :
        hi2c->MspInitCallback = pCallback;
        break;

      case HAL_I2C_MSPDEINIT_CB_ID :
        hi2c->MspDeInitCallback = pCallback;
        break;

      default :

        hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hi2c);
  return status;
}

HAL_StatusTypeDef HAL_I2C_UnRegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hi2c);

  if (HAL_I2C_STATE_READY == hi2c->State)
  {
    switch (CallbackID)
    {
      case HAL_I2C_MASTER_TX_COMPLETE_CB_ID :
        hi2c->MasterTxCpltCallback = HAL_I2C_MasterTxCpltCallback;
        break;

      case HAL_I2C_MASTER_RX_COMPLETE_CB_ID :
        hi2c->MasterRxCpltCallback = HAL_I2C_MasterRxCpltCallback;
        break;

      case HAL_I2C_SLAVE_TX_COMPLETE_CB_ID :
        hi2c->SlaveTxCpltCallback = HAL_I2C_SlaveTxCpltCallback;
        break;

      case HAL_I2C_SLAVE_RX_COMPLETE_CB_ID :
        hi2c->SlaveRxCpltCallback = HAL_I2C_SlaveRxCpltCallback;
        break;

      case HAL_I2C_LISTEN_COMPLETE_CB_ID :
        hi2c->ListenCpltCallback = HAL_I2C_ListenCpltCallback;
        break;

      case HAL_I2C_MEM_TX_COMPLETE_CB_ID :
        hi2c->MemTxCpltCallback = HAL_I2C_MemTxCpltCallback;
        break;

      case HAL_I2C_MEM_RX_COMPLETE_CB_ID :
        hi2c->MemRxCpltCallback = HAL_I2C_MemRxCpltCallback;
        break;

      case HAL_I2C_ERROR_CB_ID :
        hi2c->ErrorCallback = HAL_I2C_ErrorCallback;
        break;

      case HAL_I2C_ABORT_CB_ID :
        hi2c->AbortCpltCallback = HAL_I2C_AbortCpltCallback;
        break;

      case HAL_I2C_MSPINIT_CB_ID :
        hi2c->MspInitCallback = HAL_I2C_MspInit;
        break;

      case HAL_I2C_MSPDEINIT_CB_ID :
        hi2c->MspDeInitCallback = HAL_I2C_MspDeInit;
        break;

      default :

        hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else if (HAL_I2C_STATE_RESET == hi2c->State)
  {
    switch (CallbackID)
    {
      case HAL_I2C_MSPINIT_CB_ID :
        hi2c->MspInitCallback = HAL_I2C_MspInit;
        break;

      case HAL_I2C_MSPDEINIT_CB_ID :
        hi2c->MspDeInitCallback = HAL_I2C_MspDeInit;
        break;

      default :

        hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

        status =  HAL_ERROR;
        break;
    }
  }
  else
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hi2c);
  return status;
}

HAL_StatusTypeDef HAL_I2C_RegisterAddrCallback(I2C_HandleTypeDef *hi2c, pI2C_AddrCallbackTypeDef pCallback)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (pCallback == NULL)
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    return HAL_ERROR;
  }

  __HAL_LOCK(hi2c);

  if (HAL_I2C_STATE_READY == hi2c->State)
  {
    hi2c->AddrCallback = pCallback;
  }
  else
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hi2c);
  return status;
}

HAL_StatusTypeDef HAL_I2C_UnRegisterAddrCallback(I2C_HandleTypeDef *hi2c)
{
  HAL_StatusTypeDef status = HAL_OK;

  __HAL_LOCK(hi2c);

  if (HAL_I2C_STATE_READY == hi2c->State)
  {
    hi2c->AddrCallback = HAL_I2C_AddrCallback;
  }
  else
  {

    hi2c->ErrorCode |= HAL_I2C_ERROR_INVALID_CALLBACK;

    status =  HAL_ERROR;
  }

  __HAL_UNLOCK(hi2c);
  return status;
}

#endif

static void I2C_Flush_DR(I2C_HandleTypeDef *hi2c)
{

  if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) != RESET)
  {
    hi2c->Instance->DR = 0x00U;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (I2C_MasterRequestWrite(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    while (hi2c->XferSize > 0U)
    {

      if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
      {
        if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
        }
        return HAL_ERROR;
      }

      hi2c->Instance->DR = *hi2c->pBuffPtr;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
      hi2c->XferSize--;

      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U))
      {

        hi2c->Instance->DR = *hi2c->pBuffPtr;

        hi2c->pBuffPtr++;

        hi2c->XferCount--;
        hi2c->XferSize--;
      }

      if (I2C_WaitOnBTFFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
      {
        if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
        }
        return HAL_ERROR;
      }
    }

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (I2C_MasterRequestRead(hi2c, DevAddress, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (hi2c->XferSize == 0U)
    {

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    else if (hi2c->XferSize == 1U)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    else if (hi2c->XferSize == 2U)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }

    while (hi2c->XferSize > 0U)
    {
      if (hi2c->XferSize <= 3U)
      {

        if (hi2c->XferSize == 1U)
        {

          if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }

        else if (hi2c->XferSize == 2U)
        {

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }

        else
        {

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }
      }
      else
      {

        if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
          return HAL_ERROR;
        }

        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

        hi2c->pBuffPtr++;

        hi2c->XferSize--;
        hi2c->XferCount--;

        if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
        {

          if (hi2c->XferSize == 3U)
          {

            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
          }

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }
      }
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State       = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode        = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_10BIT)
    {

      if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout, tickstart) != HAL_OK)
      {
        return HAL_ERROR;
      }

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }

    while (hi2c->XferSize > 0U)
    {

      if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
      {

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        return HAL_ERROR;
      }

      hi2c->Instance->DR = *hi2c->pBuffPtr;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
      hi2c->XferSize--;

      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U))
      {

        hi2c->Instance->DR = *hi2c->pBuffPtr;

        hi2c->pBuffPtr++;

        hi2c->XferCount--;
        hi2c->XferSize--;
      }
    }

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_AF, RESET, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == (uint16_t)0))
    {
      return HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State       = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode        = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode   = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, RESET, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    while (hi2c->XferSize > 0U)
    {

      if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
      {

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        return HAL_ERROR;
      }

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;

      hi2c->XferSize--;
      hi2c->XferCount--;

      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U))
      {

        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

        hi2c->pBuffPtr++;

        hi2c->XferSize--;
        hi2c->XferCount--;
      }
    }

    if (I2C_WaitOnSTOPFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_STOPFLAG(hi2c);

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;
  HAL_StatusTypeDef dmaxferstatus;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;

    if (hi2c->XferSize > 0U)
    {
      if (hi2c->hdmatx != NULL)
      {

        hi2c->hdmatx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmatx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmatx->XferHalfCpltCallback = NULL;
        hi2c->hdmatx->XferM1CpltCallback = NULL;
        hi2c->hdmatx->XferM1HalfCpltCallback = NULL;
        hi2c->hdmatx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t)hi2c->pBuffPtr, (uint32_t)&hi2c->Instance->DR, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }

      if (dmaxferstatus == HAL_OK)
      {

        __HAL_UNLOCK(hi2c);

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

        SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;
  HAL_StatusTypeDef dmaxferstatus;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;

    if (hi2c->XferSize > 0U)
    {
      if (hi2c->hdmarx != NULL)
      {

        hi2c->hdmarx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmarx->XferHalfCpltCallback = NULL;
        hi2c->hdmarx->XferM1CpltCallback = NULL;
        hi2c->hdmarx->XferM1HalfCpltCallback = NULL;
        hi2c->hdmarx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->pBuffPtr, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }

      if (dmaxferstatus == HAL_OK)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

        __HAL_UNLOCK(hi2c);

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

        SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef dmaxferstatus;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (hi2c->hdmatx != NULL)
    {

      hi2c->hdmatx->XferCpltCallback = I2C_DMAXferCplt;

      hi2c->hdmatx->XferErrorCallback = I2C_DMAError;

      hi2c->hdmatx->XferHalfCpltCallback = NULL;
      hi2c->hdmatx->XferM1CpltCallback = NULL;
      hi2c->hdmatx->XferM1HalfCpltCallback = NULL;
      hi2c->hdmatx->XferAbortCallback = NULL;

      dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t)hi2c->pBuffPtr, (uint32_t)&hi2c->Instance->DR, hi2c->XferSize);
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_LISTEN;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (dmaxferstatus == HAL_OK)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

      hi2c->Instance->CR2 |= I2C_CR2_DMAEN;

      return HAL_OK;
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_READY;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef dmaxferstatus;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (hi2c->hdmarx != NULL)
    {

      hi2c->hdmarx->XferCpltCallback = I2C_DMAXferCplt;

      hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

      hi2c->hdmarx->XferHalfCpltCallback = NULL;
      hi2c->hdmarx->XferM1CpltCallback = NULL;
      hi2c->hdmarx->XferM1HalfCpltCallback = NULL;
      hi2c->hdmarx->XferAbortCallback = NULL;

      dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->pBuffPtr, hi2c->XferSize);
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_LISTEN;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (dmaxferstatus == HAL_OK)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

      SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

      return HAL_OK;
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_READY;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (I2C_RequestMemoryWrite(hi2c, DevAddress, MemAddress, MemAddSize, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    while (hi2c->XferSize > 0U)
    {

      if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
      {
        if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
        }
        return HAL_ERROR;
      }

      hi2c->Instance->DR = *hi2c->pBuffPtr;

      hi2c->pBuffPtr++;

      hi2c->XferSize--;
      hi2c->XferCount--;

      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET) && (hi2c->XferSize != 0U))
      {

        hi2c->Instance->DR = *hi2c->pBuffPtr;

        hi2c->pBuffPtr++;

        hi2c->XferSize--;
        hi2c->XferCount--;
      }
    }

    if (I2C_WaitOnBTFFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
    {
      if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
      }
      return HAL_ERROR;
    }

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    if (I2C_RequestMemoryRead(hi2c, DevAddress, MemAddress, MemAddSize, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (hi2c->XferSize == 0U)
    {

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    else if (hi2c->XferSize == 1U)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    else if (hi2c->XferSize == 2U)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }
    else
    {

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }

    while (hi2c->XferSize > 0U)
    {
      if (hi2c->XferSize <= 3U)
      {

        if (hi2c->XferSize == 1U)
        {

          if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }

        else if (hi2c->XferSize == 2U)
        {

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }

        else
        {

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BTF, RESET, Timeout, tickstart) != HAL_OK)
          {
            return HAL_ERROR;
          }

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }
      }
      else
      {

        if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
        {
          return HAL_ERROR;
        }

        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

        hi2c->pBuffPtr++;

        hi2c->XferSize--;
        hi2c->XferCount--;

        if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
        {
          if (hi2c->XferSize == 3U)
          {

            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
          }

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;

          hi2c->XferSize--;
          hi2c->XferCount--;
        }
      }
    }

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;
    hi2c->Memaddress  = MemAddress;
    hi2c->MemaddSize  = MemAddSize;
    hi2c->EventCount  = 0U;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;
    hi2c->Memaddress  = MemAddress;
    hi2c->MemaddSize  = MemAddSize;
    hi2c->EventCount  = 0U;

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    __HAL_UNLOCK(hi2c);

    if (hi2c->XferSize > 0U)
    {

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
  __IO uint32_t count = 0U;
  HAL_StatusTypeDef dmaxferstatus;

  uint32_t tickstart = HAL_GetTick();

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;
    hi2c->Memaddress  = MemAddress;
    hi2c->MemaddSize  = MemAddSize;
    hi2c->EventCount  = 0U;

    if (hi2c->XferSize > 0U)
    {
      if (hi2c->hdmatx != NULL)
      {

        hi2c->hdmatx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmatx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmatx->XferHalfCpltCallback = NULL;
        hi2c->hdmatx->XferM1CpltCallback = NULL;
        hi2c->hdmatx->XferM1HalfCpltCallback = NULL;
        hi2c->hdmatx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t)hi2c->pBuffPtr, (uint32_t)&hi2c->Instance->DR, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }

      if (dmaxferstatus == HAL_OK)
      {

        if (I2C_RequestMemoryWrite(hi2c, DevAddress, MemAddress, MemAddSize, I2C_TIMEOUT_FLAG, tickstart) != HAL_OK)
        {

          dmaxferstatus = HAL_DMA_Abort_IT(hi2c->hdmatx);

          UNUSED(dmaxferstatus);

          hi2c->hdmatx->XferCpltCallback = NULL;

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          hi2c->XferSize = 0U;
          hi2c->XferCount = 0U;

          __HAL_I2C_DISABLE(hi2c);

          return HAL_ERROR;
        }

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

        __HAL_UNLOCK(hi2c);

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_ERR);

        SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

        return HAL_OK;
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_READY;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_SIZE;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{

  uint32_t tickstart = HAL_GetTick();
  __IO uint32_t count = 0U;
  HAL_StatusTypeDef dmaxferstatus;

  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
    do
    {
      count--;
      if (count == 0U)
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        return HAL_BUSY;
      }
    }
    while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;
    hi2c->Devaddress  = DevAddress;
    hi2c->Memaddress  = MemAddress;
    hi2c->MemaddSize  = MemAddSize;
    hi2c->EventCount  = 0U;

    if (hi2c->XferSize > 0U)
    {
      if (hi2c->hdmarx != NULL)
      {

        hi2c->hdmarx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmarx->XferHalfCpltCallback = NULL;
        hi2c->hdmarx->XferM1CpltCallback = NULL;
        hi2c->hdmarx->XferM1HalfCpltCallback = NULL;
        hi2c->hdmarx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->pBuffPtr, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }

      if (dmaxferstatus == HAL_OK)
      {

        if (I2C_RequestMemoryRead(hi2c, DevAddress, MemAddress, MemAddSize, I2C_TIMEOUT_FLAG, tickstart) != HAL_OK)
        {

          dmaxferstatus = HAL_DMA_Abort_IT(hi2c->hdmarx);

          UNUSED(dmaxferstatus);

          hi2c->hdmarx->XferCpltCallback = NULL;

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          hi2c->XferSize = 0U;
          hi2c->XferCount = 0U;

          __HAL_I2C_DISABLE(hi2c);

          return HAL_ERROR;
        }

        if (hi2c->XferSize == 1U)
        {

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        }
        else
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);
        }

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

        __HAL_UNLOCK(hi2c);

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_ERR);

        hi2c->Instance->CR2 |= I2C_CR2_DMAEN;
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      if (I2C_RequestMemoryRead(hi2c, DevAddress, MemAddress, MemAddSize, I2C_TIMEOUT_FLAG, tickstart) != HAL_OK)
      {
        return HAL_ERROR;
      }

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

      hi2c->State = HAL_I2C_STATE_READY;

      __HAL_UNLOCK(hi2c);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout)
{

  uint32_t tickstart = HAL_GetTick();
  uint32_t I2C_Trials = 0U;
  FlagStatus tmp1;
  FlagStatus tmp2;

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
    {
      return HAL_BUSY;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State = HAL_I2C_STATE_BUSY;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    do
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

      if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, tickstart) != HAL_OK)
      {
        if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
        {
          hi2c->ErrorCode = HAL_I2C_WRONG_START;
        }
        return HAL_TIMEOUT;
      }

      hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);

      tickstart = HAL_GetTick();

      tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR);
      tmp2 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF);
      while ((hi2c->State != HAL_I2C_STATE_TIMEOUT) && (tmp1 == RESET) && (tmp2 == RESET))
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          hi2c->State = HAL_I2C_STATE_TIMEOUT;
        }
        tmp1 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR);
        tmp2 = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF);
      }

      hi2c->State = HAL_I2C_STATE_READY;

      if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR) == SET)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        {
          return HAL_ERROR;
        }

        hi2c->State = HAL_I2C_STATE_READY;

        __HAL_UNLOCK(hi2c);

        return HAL_OK;
      }
      else
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG, tickstart) != HAL_OK)
        {
          return HAL_ERROR;
        }
      }

      I2C_Trials++;
    }
    while (I2C_Trials < Trials);

    hi2c->State = HAL_I2C_STATE_READY;

    __HAL_UNLOCK(hi2c);

    return HAL_ERROR;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  __IO uint32_t Prev_State = 0x00U;
  __IO uint32_t count      = 0x00U;

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if ((READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP) || (XferOptions == I2C_FIRST_AND_LAST_FRAME) || (XferOptions == I2C_FIRST_FRAME))
    {

      count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
      do
      {
        count--;
        if (count == 0U)
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          return HAL_BUSY;
        }
      }
      while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;
    hi2c->Devaddress  = DevAddress;

    Prev_State = hi2c->PreviousState;

    if ((Prev_State != I2C_STATE_MASTER_BUSY_TX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
    }

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  __IO uint32_t Prev_State = 0x00U;
  __IO uint32_t count      = 0x00U;
  HAL_StatusTypeDef dmaxferstatus;

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if ((READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP) || (XferOptions == I2C_FIRST_AND_LAST_FRAME) || (XferOptions == I2C_FIRST_FRAME))
    {

      count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
      do
      {
        count--;
        if (count == 0U)
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          return HAL_BUSY;
        }
      }
      while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;
    hi2c->Devaddress  = DevAddress;

    Prev_State = hi2c->PreviousState;

    if (hi2c->XferSize > 0U)
    {
      if (hi2c->hdmatx != NULL)
      {

        hi2c->hdmatx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmatx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmatx->XferHalfCpltCallback = NULL;
        hi2c->hdmatx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t)hi2c->pBuffPtr, (uint32_t)&hi2c->Instance->DR, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }

      if (dmaxferstatus == HAL_OK)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        if ((Prev_State != I2C_STATE_MASTER_BUSY_TX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
        }

        __HAL_UNLOCK(hi2c);

        if ((XferOptions == I2C_NEXT_FRAME) || (XferOptions == I2C_LAST_FRAME) || (XferOptions == I2C_LAST_FRAME_NO_STOP))
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);
        }

        __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      if ((Prev_State != I2C_STATE_MASTER_BUSY_TX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
      }

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);
    }

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  __IO uint32_t Prev_State = 0x00U;
  __IO uint32_t count = 0U;
  uint32_t enableIT = (I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if ((READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP) || (XferOptions == I2C_FIRST_AND_LAST_FRAME) || (XferOptions == I2C_FIRST_FRAME))
    {

      count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
      do
      {
        count--;
        if (count == 0U)
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          return HAL_BUSY;
        }
      }
      while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;
    hi2c->Devaddress  = DevAddress;

    Prev_State = hi2c->PreviousState;

    if ((hi2c->XferCount == 2U) && ((XferOptions == I2C_LAST_FRAME) || (XferOptions == I2C_LAST_FRAME_NO_STOP)))
    {
      if (Prev_State == I2C_STATE_MASTER_BUSY_RX)
      {

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

        enableIT &= ~I2C_IT_BUF;
      }
      else
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
      }
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
    }

    if ((Prev_State != I2C_STATE_MASTER_BUSY_RX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
    }

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, enableIT);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  __IO uint32_t Prev_State = 0x00U;
  __IO uint32_t count = 0U;
  uint32_t enableIT = (I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);
  HAL_StatusTypeDef dmaxferstatus;

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {

    if ((READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP) || (XferOptions == I2C_FIRST_AND_LAST_FRAME) || (XferOptions == I2C_FIRST_FRAME))
    {

      count = I2C_TIMEOUT_BUSY_FLAG * (SystemCoreClock / 25U / 1000U);
      do
      {
        count--;
        if (count == 0U)
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          return HAL_BUSY;
        }
      }
      while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET);
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MASTER;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;
    hi2c->Devaddress  = DevAddress;

    Prev_State = hi2c->PreviousState;

    if (hi2c->XferSize > 0U)
    {
      if ((hi2c->XferCount == 2U) && ((XferOptions == I2C_LAST_FRAME) || (XferOptions == I2C_LAST_FRAME_NO_STOP)))
      {
        if (Prev_State == I2C_STATE_MASTER_BUSY_RX)
        {

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);
        }
        else
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        }
      }
      else
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        if ((XferOptions == I2C_LAST_FRAME) || (XferOptions == I2C_OTHER_AND_LAST_FRAME) || (XferOptions == I2C_LAST_FRAME_NO_STOP))
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);
        }
      }
      if (hi2c->hdmarx != NULL)
      {

        hi2c->hdmarx->XferCpltCallback = I2C_DMAXferCplt;

        hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

        hi2c->hdmarx->XferHalfCpltCallback = NULL;
        hi2c->hdmarx->XferAbortCallback = NULL;

        dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->pBuffPtr, hi2c->XferSize);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
      if (dmaxferstatus == HAL_OK)
      {

        if ((Prev_State != I2C_STATE_MASTER_BUSY_RX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

          enableIT = (I2C_IT_EVT | I2C_IT_ERR);
        }
        else
        {

          enableIT = I2C_IT_ERR;
        }

        __HAL_UNLOCK(hi2c);

        if ((XferOptions == I2C_NEXT_FRAME) || (XferOptions == I2C_LAST_FRAME) || (XferOptions == I2C_LAST_FRAME_NO_STOP))
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);
        }

        __HAL_I2C_ENABLE_IT(hi2c, enableIT);
      }
      else
      {

        hi2c->State     = HAL_I2C_STATE_READY;
        hi2c->Mode      = HAL_I2C_MODE_NONE;

        hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      if ((Prev_State != I2C_STATE_MASTER_BUSY_RX) || (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(XferOptions) == 1))
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
      }

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, enableIT);
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (((uint32_t)hi2c->State & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX_LISTEN;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  HAL_StatusTypeDef dmaxferstatus;

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (((uint32_t)hi2c->State & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    if (hi2c->State == HAL_I2C_STATE_BUSY_RX_LISTEN)
    {
      if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
      {

        if (hi2c->hdmarx != NULL)
        {
          CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

          hi2c->hdmarx->XferAbortCallback = I2C_DMAAbort;

          if (HAL_DMA_Abort_IT(hi2c->hdmarx) != HAL_OK)
          {

            hi2c->hdmarx->XferAbortCallback(hi2c->hdmarx);
          }
        }
      }
    }
    else if (hi2c->State == HAL_I2C_STATE_BUSY_TX_LISTEN)
    {
      if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
      {
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

        if (hi2c->hdmatx != NULL)
        {

          hi2c->hdmatx->XferAbortCallback = I2C_DMAAbort;

          if (HAL_DMA_Abort_IT(hi2c->hdmatx) != HAL_OK)
          {

            hi2c->hdmatx->XferAbortCallback(hi2c->hdmatx);
          }
        }
      }
    }
    else
    {

    }

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_TX_LISTEN;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;

    if (hi2c->hdmatx != NULL)
    {

      hi2c->hdmatx->XferCpltCallback = I2C_DMAXferCplt;

      hi2c->hdmatx->XferErrorCallback = I2C_DMAError;

      hi2c->hdmatx->XferHalfCpltCallback = NULL;
      hi2c->hdmatx->XferAbortCallback = NULL;

      dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmatx, (uint32_t)hi2c->pBuffPtr, (uint32_t)&hi2c->Instance->DR, hi2c->XferSize);
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_LISTEN;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (dmaxferstatus == HAL_OK)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      __HAL_UNLOCK(hi2c);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

      hi2c->Instance->CR2 |= I2C_CR2_DMAEN;

      return HAL_OK;
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_READY;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (((uint32_t)hi2c->State & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX_LISTEN;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    __HAL_UNLOCK(hi2c);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions)
{
  HAL_StatusTypeDef dmaxferstatus;

  assert_param(IS_I2C_TRANSFER_OPTIONS_REQUEST(XferOptions));

  if (((uint32_t)hi2c->State & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return  HAL_ERROR;
    }

    __HAL_LOCK(hi2c);

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    if (hi2c->State == HAL_I2C_STATE_BUSY_RX_LISTEN)
    {
      if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
      {

        if (hi2c->hdmarx != NULL)
        {
          CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

          hi2c->hdmarx->XferAbortCallback = I2C_DMAAbort;

          if (HAL_DMA_Abort_IT(hi2c->hdmarx) != HAL_OK)
          {

            hi2c->hdmarx->XferAbortCallback(hi2c->hdmarx);
          }
        }
      }
    }
    else if (hi2c->State == HAL_I2C_STATE_BUSY_TX_LISTEN)
    {
      if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
      {
        CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

        if (hi2c->hdmatx != NULL)
        {

          hi2c->hdmatx->XferAbortCallback = I2C_DMAAbort;

          if (HAL_DMA_Abort_IT(hi2c->hdmatx) != HAL_OK)
          {

            hi2c->hdmatx->XferAbortCallback(hi2c->hdmatx);
          }
        }
      }
    }
    else
    {

    }

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    hi2c->State     = HAL_I2C_STATE_BUSY_RX_LISTEN;
    hi2c->Mode      = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    hi2c->pBuffPtr    = pData;
    hi2c->XferCount   = Size;
    hi2c->XferSize    = hi2c->XferCount;
    hi2c->XferOptions = XferOptions;

    if (hi2c->hdmarx != NULL)
    {

      hi2c->hdmarx->XferCpltCallback = I2C_DMAXferCplt;

      hi2c->hdmarx->XferErrorCallback = I2C_DMAError;

      hi2c->hdmarx->XferHalfCpltCallback = NULL;
      hi2c->hdmarx->XferAbortCallback = NULL;

      dmaxferstatus = HAL_DMA_Start_IT(hi2c->hdmarx, (uint32_t)&hi2c->Instance->DR, (uint32_t)hi2c->pBuffPtr, hi2c->XferSize);
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_LISTEN;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA_PARAM;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (dmaxferstatus == HAL_OK)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      __HAL_UNLOCK(hi2c);

      SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

      __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

      return HAL_OK;
    }
    else
    {

      hi2c->State     = HAL_I2C_STATE_READY;
      hi2c->Mode      = HAL_I2C_MODE_NONE;

      hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    hi2c->State = HAL_I2C_STATE_LISTEN;

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {

      __HAL_I2C_ENABLE(hi2c);
    }

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c)
{

  uint32_t tmp;

  if (hi2c->State == HAL_I2C_STATE_LISTEN)
  {
    tmp = (uint32_t)(hi2c->State) & I2C_STATE_MSK;
    hi2c->PreviousState = tmp | (uint32_t)(hi2c->Mode);
    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{

  HAL_I2C_ModeTypeDef CurrentMode   = hi2c->Mode;

  UNUSED(DevAddress);

  if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BUSY) != RESET) && ((CurrentMode == HAL_I2C_MODE_MASTER) ||
                                                             (CurrentMode == HAL_I2C_MODE_MEM)))
  {

    __HAL_LOCK(hi2c);

    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->State = HAL_I2C_STATE_ABORT;

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

    hi2c->XferCount = 0U;

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    __HAL_UNLOCK(hi2c);

    I2C_ITError(hi2c);

    return HAL_OK;
  }
  else
  {

    return HAL_ERROR;
  }
}

void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c)
{
  uint32_t sr1itflags;
  uint32_t sr2itflags               = 0U;
  uint32_t itsources                = READ_REG(hi2c->Instance->CR2);
  uint32_t CurrentXferOptions       = hi2c->XferOptions;
  HAL_I2C_ModeTypeDef CurrentMode   = hi2c->Mode;
  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  if ((CurrentMode == HAL_I2C_MODE_MASTER) || (CurrentMode == HAL_I2C_MODE_MEM))
  {
    sr2itflags   = READ_REG(hi2c->Instance->SR2);
    sr1itflags   = READ_REG(hi2c->Instance->SR1);

    if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_SB) == RESET) && (IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(CurrentXferOptions) == 1U))
    {
      return;
    }

    if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_SB) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
    {

      I2C_ConvertOtherXferOptions(hi2c);

      I2C_Master_SB(hi2c);
    }

    else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_ADD10) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
    {
      I2C_Master_ADD10(hi2c);
    }

    else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_ADDR) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
    {
      I2C_Master_ADDR(hi2c);
    }

    else if (I2C_CHECK_FLAG(sr2itflags, I2C_FLAG_TRA) != RESET)
    {

      if (READ_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN) != I2C_CR2_DMAEN)
      {

        if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_TXE) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_BUF) != RESET) && (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) == RESET))
        {
          I2C_MasterTransmit_TXE(hi2c);
        }

        else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
        {
          if (CurrentState == HAL_I2C_STATE_BUSY_TX)
          {
            I2C_MasterTransmit_BTF(hi2c);
          }
          else
          {
            if (CurrentMode == HAL_I2C_MODE_MEM)
            {
              I2C_MemoryTransmit_TXE_BTF(hi2c);
            }
          }
        }
        else
        {

        }
      }
    }

    else
    {

      if (READ_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN) != I2C_CR2_DMAEN)
      {

        if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_RXNE) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_BUF) != RESET) && (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) == RESET))
        {
          I2C_MasterReceive_RXNE(hi2c);
        }

        else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
        {
          I2C_MasterReceive_BTF(hi2c);
        }
        else
        {

        }
      }
    }
  }

  else
  {

    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
    {
      sr1itflags   = READ_REG(hi2c->Instance->SR1);
    }
    else
    {
      sr2itflags   = READ_REG(hi2c->Instance->SR2);
      sr1itflags   = READ_REG(hi2c->Instance->SR1);
    }

    if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_ADDR) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
    {

      if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
      {
        sr2itflags   = READ_REG(hi2c->Instance->SR2);
      }
      I2C_Slave_ADDR(hi2c, sr2itflags);
    }

    else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_STOPF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
    {
      I2C_Slave_STOPF(hi2c);
    }

    else if ((CurrentState == HAL_I2C_STATE_BUSY_TX) || (CurrentState == HAL_I2C_STATE_BUSY_TX_LISTEN))
    {

      if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_TXE) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_BUF) != RESET) && (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) == RESET))
      {
        I2C_SlaveTransmit_TXE(hi2c);
      }

      else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
      {
        I2C_SlaveTransmit_BTF(hi2c);
      }
      else
      {

      }
    }

    else
    {

      if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_RXNE) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_BUF) != RESET) && (I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) == RESET))
      {
        I2C_SlaveReceive_RXNE(hi2c);
      }

      else if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BTF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_EVT) != RESET))
      {
        I2C_SlaveReceive_BTF(hi2c);
      }
      else
      {

      }
    }
  }
}

void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c)
{
  HAL_I2C_ModeTypeDef tmp1;
  uint32_t tmp2;
  HAL_I2C_StateTypeDef tmp3;
  uint32_t tmp4;
  uint32_t sr1itflags = READ_REG(hi2c->Instance->SR1);
  uint32_t itsources  = READ_REG(hi2c->Instance->CR2);
  uint32_t error      = HAL_I2C_ERROR_NONE;
  HAL_I2C_ModeTypeDef CurrentMode   = hi2c->Mode;

  if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_BERR) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_ERR) != RESET))
  {
    error |= HAL_I2C_ERROR_BERR;

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_BERR);
  }

  if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_ARLO) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_ERR) != RESET))
  {
    error |= HAL_I2C_ERROR_ARLO;

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ARLO);
  }

  if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_AF) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_ERR) != RESET))
  {
    tmp1 = CurrentMode;
    tmp2 = hi2c->XferCount;
    tmp3 = hi2c->State;
    tmp4 = hi2c->PreviousState;
    if ((tmp1 == HAL_I2C_MODE_SLAVE) && (tmp2 == 0U) && \
        ((tmp3 == HAL_I2C_STATE_BUSY_TX) || (tmp3 == HAL_I2C_STATE_BUSY_TX_LISTEN) || \
         ((tmp3 == HAL_I2C_STATE_LISTEN) && (tmp4 == I2C_STATE_SLAVE_BUSY_TX))))
    {
      I2C_Slave_AF(hi2c);
    }
    else
    {

      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

      error |= HAL_I2C_ERROR_AF;

      if ((CurrentMode == HAL_I2C_MODE_MASTER) || (CurrentMode == HAL_I2C_MODE_MEM))
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
      }
    }
  }

  if ((I2C_CHECK_FLAG(sr1itflags, I2C_FLAG_OVR) != RESET) && (I2C_CHECK_IT_SOURCE(itsources, I2C_IT_ERR) != RESET))
  {
    error |= HAL_I2C_ERROR_OVR;

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_OVR);
  }

  if (error != HAL_I2C_ERROR_NONE)
  {
    hi2c->ErrorCode |= error;
    I2C_ITError(hi2c);
  }
}

__weak void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{

  UNUSED(hi2c);
  UNUSED(TransferDirection);
  UNUSED(AddrMatchCode);

}

__weak void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

__weak void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c)
{

  UNUSED(hi2c);

}

HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c)
{

  return hi2c->State;
}

HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c)
{
  return hi2c->Mode;
}

uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c)
{
  return hi2c->ErrorCode;
}

static void I2C_MasterTransmit_TXE(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;
  HAL_I2C_ModeTypeDef CurrentMode   = hi2c->Mode;
  uint32_t CurrentXferOptions       = hi2c->XferOptions;

  if ((hi2c->XferSize == 0U) && (CurrentState == HAL_I2C_STATE_BUSY_TX))
  {

    if ((CurrentXferOptions != I2C_FIRST_AND_LAST_FRAME) && (CurrentXferOptions != I2C_LAST_FRAME) && (CurrentXferOptions != I2C_NO_OPTION_FRAME))
    {
      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

      hi2c->PreviousState = I2C_STATE_MASTER_BUSY_TX;
      hi2c->Mode = HAL_I2C_MODE_NONE;
      hi2c->State = HAL_I2C_STATE_READY;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->MasterTxCpltCallback(hi2c);
#else
      HAL_I2C_MasterTxCpltCallback(hi2c);
#endif
    }
    else
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

      hi2c->PreviousState = I2C_STATE_NONE;
      hi2c->State = HAL_I2C_STATE_READY;

      if (hi2c->Mode == HAL_I2C_MODE_MEM)
      {
        hi2c->Mode = HAL_I2C_MODE_NONE;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->MemTxCpltCallback(hi2c);
#else
        HAL_I2C_MemTxCpltCallback(hi2c);
#endif
      }
      else
      {
        hi2c->Mode = HAL_I2C_MODE_NONE;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->MasterTxCpltCallback(hi2c);
#else
        HAL_I2C_MasterTxCpltCallback(hi2c);
#endif
      }
    }
  }
  else if ((CurrentState == HAL_I2C_STATE_BUSY_TX) || \
           ((CurrentMode == HAL_I2C_MODE_MEM) && (CurrentState == HAL_I2C_STATE_BUSY_RX)))
  {
    if (hi2c->XferCount == 0U)
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);
    }
    else
    {
      if (hi2c->Mode == HAL_I2C_MODE_MEM)
      {
        I2C_MemoryTransmit_TXE_BTF(hi2c);
      }
      else
      {

        hi2c->Instance->DR = *hi2c->pBuffPtr;

        hi2c->pBuffPtr++;

        hi2c->XferCount--;
      }
    }
  }
  else
  {

  }
}

static void I2C_MasterTransmit_BTF(I2C_HandleTypeDef *hi2c)
{

  uint32_t CurrentXferOptions = hi2c->XferOptions;

  if (hi2c->State == HAL_I2C_STATE_BUSY_TX)
  {
    if (hi2c->XferCount != 0U)
    {

      hi2c->Instance->DR = *hi2c->pBuffPtr;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
    }
    else
    {

      if ((CurrentXferOptions != I2C_FIRST_AND_LAST_FRAME) && (CurrentXferOptions != I2C_LAST_FRAME) && (CurrentXferOptions != I2C_NO_OPTION_FRAME))
      {
        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

        hi2c->PreviousState = I2C_STATE_MASTER_BUSY_TX;
        hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->State = HAL_I2C_STATE_READY;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->MasterTxCpltCallback(hi2c);
#else
        HAL_I2C_MasterTxCpltCallback(hi2c);
#endif
      }
      else
      {

        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

        hi2c->PreviousState = I2C_STATE_NONE;
        hi2c->State = HAL_I2C_STATE_READY;
        if (hi2c->Mode == HAL_I2C_MODE_MEM)
        {
          hi2c->Mode = HAL_I2C_MODE_NONE;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
          hi2c->MemTxCpltCallback(hi2c);
#else
          HAL_I2C_MemTxCpltCallback(hi2c);
#endif
        }
        else
        {
          hi2c->Mode = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
          hi2c->MasterTxCpltCallback(hi2c);
#else
          HAL_I2C_MasterTxCpltCallback(hi2c);
#endif
        }
      }
    }
  }
  else
  {

  }
}

static void I2C_MemoryTransmit_TXE_BTF(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  if (hi2c->EventCount == 0U)
  {

    if (hi2c->MemaddSize == I2C_MEMADD_SIZE_8BIT)
    {

      hi2c->Instance->DR = I2C_MEM_ADD_LSB(hi2c->Memaddress);

      hi2c->EventCount += 2U;
    }

    else
    {

      hi2c->Instance->DR = I2C_MEM_ADD_MSB(hi2c->Memaddress);

      hi2c->EventCount++;
    }
  }
  else if (hi2c->EventCount == 1U)
  {

    hi2c->Instance->DR = I2C_MEM_ADD_LSB(hi2c->Memaddress);

    hi2c->EventCount++;
  }
  else if (hi2c->EventCount == 2U)
  {
    if (CurrentState == HAL_I2C_STATE_BUSY_RX)
    {

      hi2c->Instance->CR1 |= I2C_CR1_START;

      hi2c->EventCount++;
    }
    else if ((hi2c->XferCount > 0U) && (CurrentState == HAL_I2C_STATE_BUSY_TX))
    {

      hi2c->Instance->DR = *hi2c->pBuffPtr;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
    }
    else if ((hi2c->XferCount == 0U) && (CurrentState == HAL_I2C_STATE_BUSY_TX))
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

      hi2c->PreviousState = I2C_STATE_NONE;
      hi2c->State = HAL_I2C_STATE_READY;
      hi2c->Mode = HAL_I2C_MODE_NONE;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->MemTxCpltCallback(hi2c);
#else
      HAL_I2C_MemTxCpltCallback(hi2c);
#endif
    }
    else
    {

    }
  }
  else
  {

    I2C_Flush_DR(hi2c);
  }
}

static void I2C_MasterReceive_RXNE(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->State == HAL_I2C_STATE_BUSY_RX)
  {
    uint32_t tmp;
    uint32_t CurrentXferOptions;

    CurrentXferOptions = hi2c->XferOptions;
    tmp = hi2c->XferCount;
    if (tmp > 3U)
    {

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;

      if (hi2c->XferCount == (uint16_t)3)
      {

        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);
      }
    }
    else if ((hi2c->XferOptions != I2C_FIRST_AND_NEXT_FRAME) && ((tmp == 1U) || (tmp == 0U)))
    {
      if (I2C_WaitOnSTOPRequestThroughIT(hi2c) == HAL_OK)
      {

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

        hi2c->pBuffPtr++;

        hi2c->XferCount--;

        hi2c->State = HAL_I2C_STATE_READY;

        if (hi2c->Mode == HAL_I2C_MODE_MEM)
        {
          hi2c->Mode = HAL_I2C_MODE_NONE;
          hi2c->PreviousState = I2C_STATE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
          hi2c->MemRxCpltCallback(hi2c);
#else
          HAL_I2C_MemRxCpltCallback(hi2c);
#endif
        }
        else
        {
          hi2c->Mode = HAL_I2C_MODE_NONE;
          if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME))
          {
            hi2c->PreviousState = I2C_STATE_NONE;
          }
          else
          {
            hi2c->PreviousState = I2C_STATE_MASTER_BUSY_RX;
          }

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
          hi2c->MasterRxCpltCallback(hi2c);
#else
          HAL_I2C_MasterRxCpltCallback(hi2c);
#endif
        }
      }
      else
      {

        __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

        hi2c->pBuffPtr++;

        hi2c->XferCount--;

        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->ErrorCallback(hi2c);
#else
        HAL_I2C_ErrorCallback(hi2c);
#endif
      }
    }
    else
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);
    }
  }
}

static void I2C_MasterReceive_BTF(I2C_HandleTypeDef *hi2c)
{

  uint32_t CurrentXferOptions = hi2c->XferOptions;

  if (hi2c->XferCount == 4U)
  {

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }
  else if (hi2c->XferCount == 3U)
  {

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);

    if ((CurrentXferOptions != I2C_NEXT_FRAME) && (CurrentXferOptions != I2C_FIRST_AND_NEXT_FRAME))
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
    }

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }
  else if (hi2c->XferCount == 2U)
  {

    if ((CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME_NO_STOP))
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
    }
    else if ((CurrentXferOptions == I2C_NEXT_FRAME) || (CurrentXferOptions == I2C_FIRST_AND_NEXT_FRAME))
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
    }
    else
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    hi2c->State = HAL_I2C_STATE_READY;
    if (hi2c->Mode == HAL_I2C_MODE_MEM)
    {
      hi2c->Mode = HAL_I2C_MODE_NONE;
      hi2c->PreviousState = I2C_STATE_NONE;
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->MemRxCpltCallback(hi2c);
#else
      HAL_I2C_MemRxCpltCallback(hi2c);
#endif
    }
    else
    {
      hi2c->Mode = HAL_I2C_MODE_NONE;
      if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME))
      {
        hi2c->PreviousState = I2C_STATE_NONE;
      }
      else
      {
        hi2c->PreviousState = I2C_STATE_MASTER_BUSY_RX;
      }
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->MasterRxCpltCallback(hi2c);
#else
      HAL_I2C_MasterRxCpltCallback(hi2c);
#endif
    }
  }
  else
  {

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }
}

static void I2C_Master_SB(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->Mode == HAL_I2C_MODE_MEM)
  {
    if (hi2c->EventCount == 0U)
    {

      hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(hi2c->Devaddress);
    }
    else
    {
      hi2c->Instance->DR = I2C_7BIT_ADD_READ(hi2c->Devaddress);
    }
  }
  else
  {
    if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
    {

      if (hi2c->State == HAL_I2C_STATE_BUSY_TX)
      {
        hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(hi2c->Devaddress);
      }
      else
      {
        hi2c->Instance->DR = I2C_7BIT_ADD_READ(hi2c->Devaddress);
      }

      if (((hi2c->hdmatx != NULL) && (hi2c->hdmatx->XferCpltCallback != NULL))
          || ((hi2c->hdmarx != NULL) && (hi2c->hdmarx->XferCpltCallback != NULL)))
      {

        SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);
      }
    }
    else
    {
      if (hi2c->EventCount == 0U)
      {

        hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(hi2c->Devaddress);
      }
      else if (hi2c->EventCount == 1U)
      {

        hi2c->Instance->DR = I2C_10BIT_HEADER_READ(hi2c->Devaddress);
      }
      else
      {

      }
    }
  }
}

static void I2C_Master_ADD10(I2C_HandleTypeDef *hi2c)
{

  hi2c->Instance->DR = I2C_10BIT_ADDRESS(hi2c->Devaddress);

  if (((hi2c->hdmatx != NULL) && (hi2c->hdmatx->XferCpltCallback != NULL))
      || ((hi2c->hdmarx != NULL) && (hi2c->hdmarx->XferCpltCallback != NULL)))
  {

    SET_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);
  }
}

static void I2C_Master_ADDR(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_ModeTypeDef CurrentMode       = hi2c->Mode;
  uint32_t CurrentXferOptions           = hi2c->XferOptions;
  uint32_t Prev_State                   = hi2c->PreviousState;

  if (hi2c->State == HAL_I2C_STATE_BUSY_RX)
  {
    if ((hi2c->EventCount == 0U) && (CurrentMode == HAL_I2C_MODE_MEM))
    {

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }
    else if ((hi2c->EventCount == 0U) && (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_10BIT))
    {

      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

      hi2c->EventCount++;
    }
    else
    {
      if (hi2c->XferCount == 0U)
      {

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
      }
      else if (hi2c->XferCount == 1U)
      {
        if (CurrentXferOptions == I2C_NO_OPTION_FRAME)
        {

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
          {

            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

            __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
          }
          else
          {

            __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
          }
        }

        else if ((CurrentXferOptions != I2C_FIRST_AND_LAST_FRAME) && (CurrentXferOptions != I2C_LAST_FRAME) \
                 && ((Prev_State != I2C_STATE_MASTER_BUSY_RX) || (CurrentXferOptions == I2C_FIRST_FRAME)))
        {
          if ((CurrentXferOptions != I2C_NEXT_FRAME) && (CurrentXferOptions != I2C_FIRST_AND_NEXT_FRAME) && (CurrentXferOptions != I2C_LAST_FRAME_NO_STOP))
          {

            CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
          }
          else
          {

            SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
          }

          __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
        }
        else
        {

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
        }
      }
      else if (hi2c->XferCount == 2U)
      {
        if ((CurrentXferOptions != I2C_NEXT_FRAME) && (CurrentXferOptions != I2C_FIRST_AND_NEXT_FRAME) && (CurrentXferOptions != I2C_LAST_FRAME_NO_STOP))
        {

          CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_POS);
        }
        else
        {

          SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
        }

        if (((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN) && ((CurrentXferOptions == I2C_NO_OPTION_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME_NO_STOP) || (CurrentXferOptions == I2C_LAST_FRAME)))
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);
        }

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
      }
      else
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

        if (((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN) && ((CurrentXferOptions == I2C_NO_OPTION_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME_NO_STOP) || (CurrentXferOptions == I2C_LAST_FRAME)))
        {

          SET_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);
        }

        __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
      }

      hi2c->EventCount = 0U;
    }
  }
  else
  {

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
  }
}

static void I2C_SlaveTransmit_TXE(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  if (hi2c->XferCount != 0U)
  {

    hi2c->Instance->DR = *hi2c->pBuffPtr;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;

    if ((hi2c->XferCount == 0U) && (CurrentState == HAL_I2C_STATE_BUSY_TX_LISTEN))
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);

      hi2c->PreviousState = I2C_STATE_SLAVE_BUSY_TX;
      hi2c->State = HAL_I2C_STATE_LISTEN;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->SlaveTxCpltCallback(hi2c);
#else
      HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif
    }
  }
}

static void I2C_SlaveTransmit_BTF(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->XferCount != 0U)
  {

    hi2c->Instance->DR = *hi2c->pBuffPtr;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }
}

static void I2C_SlaveReceive_RXNE(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  if (hi2c->XferCount != 0U)
  {

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;

    if ((hi2c->XferCount == 0U) && (CurrentState == HAL_I2C_STATE_BUSY_RX_LISTEN))
    {

      __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_BUF);

      hi2c->PreviousState = I2C_STATE_SLAVE_BUSY_RX;
      hi2c->State = HAL_I2C_STATE_LISTEN;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->SlaveRxCpltCallback(hi2c);
#else
      HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
    }
  }
}

static void I2C_SlaveReceive_BTF(I2C_HandleTypeDef *hi2c)
{
  if (hi2c->XferCount != 0U)
  {

    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }
}

static void I2C_Slave_ADDR(I2C_HandleTypeDef *hi2c, uint32_t IT2Flags)
{
  uint8_t TransferDirection = I2C_DIRECTION_RECEIVE;
  uint16_t SlaveAddrCode;

  if (((uint32_t)hi2c->State & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {

    __HAL_I2C_DISABLE_IT(hi2c, (I2C_IT_BUF));

    if (I2C_CHECK_FLAG(IT2Flags, I2C_FLAG_TRA) == RESET)
    {
      TransferDirection = I2C_DIRECTION_TRANSMIT;
    }

    if (I2C_CHECK_FLAG(IT2Flags, I2C_FLAG_DUALF) == RESET)
    {
      SlaveAddrCode = (uint16_t)hi2c->Init.OwnAddress1;
    }
    else
    {
      SlaveAddrCode = (uint16_t)hi2c->Init.OwnAddress2;
    }

    __HAL_UNLOCK(hi2c);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->AddrCallback(hi2c, TransferDirection, SlaveAddrCode);
#else
    HAL_I2C_AddrCallback(hi2c, TransferDirection, SlaveAddrCode);
#endif
  }
  else
  {

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    __HAL_UNLOCK(hi2c);
  }
}

static void I2C_Slave_STOPF(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

  __HAL_I2C_CLEAR_STOPFLAG(hi2c);

  CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

  if ((hi2c->Instance->CR2 & I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
  {
    if ((CurrentState == HAL_I2C_STATE_BUSY_RX) || (CurrentState == HAL_I2C_STATE_BUSY_RX_LISTEN))
    {
      hi2c->XferCount = (uint16_t)(I2C_GET_DMA_REMAIN_DATA(hi2c->hdmarx));

      if (hi2c->XferCount != 0U)
      {

        hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
      }

      CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

      if (HAL_DMA_GetState(hi2c->hdmarx) != HAL_DMA_STATE_READY)
      {

        hi2c->hdmarx->XferAbortCallback = I2C_DMAAbort;

        if (HAL_DMA_Abort_IT(hi2c->hdmarx) != HAL_OK)
        {

          hi2c->hdmarx->XferAbortCallback(hi2c->hdmarx);
        }
      }
    }
    else
    {
      hi2c->XferCount = (uint16_t)(I2C_GET_DMA_REMAIN_DATA(hi2c->hdmatx));

      if (hi2c->XferCount != 0U)
      {

        hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
      }

      CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

      if (HAL_DMA_GetState(hi2c->hdmatx) != HAL_DMA_STATE_READY)
      {

        hi2c->hdmatx->XferAbortCallback = I2C_DMAAbort;

        if (HAL_DMA_Abort_IT(hi2c->hdmatx) != HAL_OK)
        {

          hi2c->hdmatx->XferAbortCallback(hi2c->hdmatx);
        }
      }
    }
  }

  if (hi2c->XferCount != 0U)
  {

    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
    {

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
    }

    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET)
    {

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;

      hi2c->XferCount--;
    }

    if (hi2c->XferCount != 0U)
    {

      hi2c->ErrorCode |= HAL_I2C_ERROR_AF;
    }
  }

  if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
  {

    I2C_ITError(hi2c);
  }
  else
  {
    if (CurrentState == HAL_I2C_STATE_BUSY_RX_LISTEN)
    {

      hi2c->PreviousState = I2C_STATE_NONE;
      hi2c->State = HAL_I2C_STATE_LISTEN;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->SlaveRxCpltCallback(hi2c);
#else
      HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
    }

    if (hi2c->State == HAL_I2C_STATE_LISTEN)
    {
      hi2c->XferOptions = I2C_NO_OPTION_FRAME;
      hi2c->PreviousState = I2C_STATE_NONE;
      hi2c->State = HAL_I2C_STATE_READY;
      hi2c->Mode = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->ListenCpltCallback(hi2c);
#else
      HAL_I2C_ListenCpltCallback(hi2c);
#endif
    }
    else
    {
      if ((hi2c->PreviousState  == I2C_STATE_SLAVE_BUSY_RX) || (CurrentState == HAL_I2C_STATE_BUSY_RX))
      {
        hi2c->PreviousState = I2C_STATE_NONE;
        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->SlaveRxCpltCallback(hi2c);
#else
        HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
      }
    }
  }
}

static void I2C_Slave_AF(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;
  uint32_t CurrentXferOptions       = hi2c->XferOptions;

  if (((CurrentXferOptions ==  I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME)) && \
      (CurrentState == HAL_I2C_STATE_LISTEN))
  {
    hi2c->XferOptions = I2C_NO_OPTION_FRAME;

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->State         = HAL_I2C_STATE_READY;
    hi2c->Mode          = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ListenCpltCallback(hi2c);
#else
    HAL_I2C_ListenCpltCallback(hi2c);
#endif
  }
  else if (CurrentState == HAL_I2C_STATE_BUSY_TX)
  {
    hi2c->XferOptions   = I2C_NO_OPTION_FRAME;
    hi2c->PreviousState = I2C_STATE_SLAVE_BUSY_TX;
    hi2c->State         = HAL_I2C_STATE_READY;
    hi2c->Mode          = HAL_I2C_MODE_NONE;

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

    I2C_Flush_DR(hi2c);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->SlaveTxCpltCallback(hi2c);
#else
    HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif
  }
  else
  {

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
  }
}

static void I2C_ITError(I2C_HandleTypeDef *hi2c)
{

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;
  HAL_I2C_ModeTypeDef CurrentMode = hi2c->Mode;
  uint32_t CurrentError;

  if (((CurrentMode == HAL_I2C_MODE_MASTER) || (CurrentMode == HAL_I2C_MODE_MEM)) && (CurrentState == HAL_I2C_STATE_BUSY_RX))
  {

    hi2c->Instance->CR1 &= ~I2C_CR1_POS;
  }

  if (((uint32_t)CurrentState & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
  {

    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->State = HAL_I2C_STATE_LISTEN;
  }
  else
  {

    if ((READ_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN) != I2C_CR2_DMAEN) && (CurrentState != HAL_I2C_STATE_ABORT))
    {
      hi2c->State = HAL_I2C_STATE_READY;
      hi2c->Mode = HAL_I2C_MODE_NONE;
    }
    hi2c->PreviousState = I2C_STATE_NONE;
  }

  if (READ_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN) == I2C_CR2_DMAEN)
  {
    hi2c->Instance->CR2 &= ~I2C_CR2_DMAEN;

    if (hi2c->hdmatx->State != HAL_DMA_STATE_READY)
    {

      hi2c->hdmatx->XferAbortCallback = I2C_DMAAbort;

      if (HAL_DMA_Abort_IT(hi2c->hdmatx) != HAL_OK)
      {

        __HAL_I2C_DISABLE(hi2c);

        hi2c->State = HAL_I2C_STATE_READY;

        hi2c->hdmatx->XferAbortCallback(hi2c->hdmatx);
      }
    }
    else
    {

      hi2c->hdmarx->XferAbortCallback = I2C_DMAAbort;

      if (HAL_DMA_Abort_IT(hi2c->hdmarx) != HAL_OK)
      {

        if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET)
        {

          *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

          hi2c->pBuffPtr++;
        }

        __HAL_I2C_DISABLE(hi2c);

        hi2c->State = HAL_I2C_STATE_READY;

        hi2c->hdmarx->XferAbortCallback(hi2c->hdmarx);
      }
    }
  }
  else if (hi2c->State == HAL_I2C_STATE_ABORT)
  {
    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET)
    {

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;
    }

    __HAL_I2C_DISABLE(hi2c);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->AbortCpltCallback(hi2c);
#else
    HAL_I2C_AbortCpltCallback(hi2c);
#endif
  }
  else
  {

    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET)
    {

      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->DR;

      hi2c->pBuffPtr++;
    }

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ErrorCallback(hi2c);
#else
    HAL_I2C_ErrorCallback(hi2c);
#endif
  }

  CurrentError = hi2c->ErrorCode;

  if (((CurrentError & HAL_I2C_ERROR_BERR) == HAL_I2C_ERROR_BERR) || \
      ((CurrentError & HAL_I2C_ERROR_ARLO) == HAL_I2C_ERROR_ARLO) || \
      ((CurrentError & HAL_I2C_ERROR_AF) == HAL_I2C_ERROR_AF)     || \
      ((CurrentError & HAL_I2C_ERROR_OVR) == HAL_I2C_ERROR_OVR))
  {

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR);
  }

  CurrentState = hi2c->State;
  if (((hi2c->ErrorCode & HAL_I2C_ERROR_AF) == HAL_I2C_ERROR_AF) && (CurrentState == HAL_I2C_STATE_LISTEN))
  {
    hi2c->XferOptions   = I2C_NO_OPTION_FRAME;
    hi2c->PreviousState = I2C_STATE_NONE;
    hi2c->State         = HAL_I2C_STATE_READY;
    hi2c->Mode          = HAL_I2C_MODE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ListenCpltCallback(hi2c);
#else
    HAL_I2C_ListenCpltCallback(hi2c);
#endif
  }
}

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart)
{

  uint32_t CurrentXferOptions = hi2c->XferOptions;

  if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME) || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
  {

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
  }
  else if (hi2c->PreviousState == I2C_STATE_MASTER_BUSY_RX)
  {

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
  }
  else
  {

  }

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  {
    if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
    {
      hi2c->ErrorCode = HAL_I2C_WRONG_START;
    }
    return HAL_TIMEOUT;
  }

  if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
  {

    hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);
  }
  else
  {

    hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(DevAddress);

    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10, Timeout, Tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    hi2c->Instance->DR = I2C_10BIT_ADDRESS(DevAddress);
  }

  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_MasterRequestRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout, uint32_t Tickstart)
{

  uint32_t CurrentXferOptions = hi2c->XferOptions;

  SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

  if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_FIRST_FRAME)  || (CurrentXferOptions == I2C_NO_OPTION_FRAME))
  {

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
  }
  else if (hi2c->PreviousState == I2C_STATE_MASTER_BUSY_TX)
  {

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);
  }
  else
  {

  }

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  {
    if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
    {
      hi2c->ErrorCode = HAL_I2C_WRONG_START;
    }
    return HAL_TIMEOUT;
  }

  if (hi2c->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
  {

    hi2c->Instance->DR = I2C_7BIT_ADD_READ(DevAddress);
  }
  else
  {

    hi2c->Instance->DR = I2C_10BIT_HEADER_WRITE(DevAddress);

    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADD10, Timeout, Tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    hi2c->Instance->DR = I2C_10BIT_ADDRESS(DevAddress);

    if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
    {
      if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
      {
        hi2c->ErrorCode = HAL_I2C_WRONG_START;
      }
      return HAL_TIMEOUT;
    }

    hi2c->Instance->DR = I2C_10BIT_HEADER_READ(DevAddress);
  }

  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_RequestMemoryWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart)
{

  SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  {
    if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
    {
      hi2c->ErrorCode = HAL_I2C_WRONG_START;
    }
    return HAL_TIMEOUT;
  }

  hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);

  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

  if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    return HAL_ERROR;
  }

  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {

    hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
  }

  else
  {

    hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);

    if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
      if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
      }
      return HAL_ERROR;
    }

    hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
  }

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint32_t Timeout, uint32_t Tickstart)
{

  SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

  SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  {
    if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
    {
      hi2c->ErrorCode = HAL_I2C_WRONG_START;
    }
    return HAL_TIMEOUT;
  }

  hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);

  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

  if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    return HAL_ERROR;
  }

  if (MemAddSize == I2C_MEMADD_SIZE_8BIT)
  {

    hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
  }

  else
  {

    hi2c->Instance->DR = I2C_MEM_ADD_MSB(MemAddress);

    if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
      if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
      {

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
      }
      return HAL_ERROR;
    }

    hi2c->Instance->DR = I2C_MEM_ADD_LSB(MemAddress);
  }

  if (I2C_WaitOnTXEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }
    return HAL_ERROR;
  }

  SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_SB, RESET, Timeout, Tickstart) != HAL_OK)
  {
    if (READ_BIT(hi2c->Instance->CR1, I2C_CR1_START) == I2C_CR1_START)
    {
      hi2c->ErrorCode = HAL_I2C_WRONG_START;
    }
    return HAL_TIMEOUT;
  }

  hi2c->Instance->DR = I2C_7BIT_ADD_READ(DevAddress);

  if (I2C_WaitOnMasterAddressFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

static void I2C_DMAXferCplt(DMA_HandleTypeDef *hdma)
{
  I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;
  HAL_I2C_ModeTypeDef CurrentMode   = hi2c->Mode;
  uint32_t CurrentXferOptions       = hi2c->XferOptions;

  __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

  if (hi2c->hdmatx != NULL)
  {
    hi2c->hdmatx->XferCpltCallback = NULL;
  }
  if (hi2c->hdmarx != NULL)
  {
    hi2c->hdmarx->XferCpltCallback = NULL;
  }

  if ((((uint32_t)CurrentState & (uint32_t)HAL_I2C_STATE_BUSY_TX) == (uint32_t)HAL_I2C_STATE_BUSY_TX) || ((((uint32_t)CurrentState & (uint32_t)HAL_I2C_STATE_BUSY_RX) == (uint32_t)HAL_I2C_STATE_BUSY_RX) && (CurrentMode == HAL_I2C_MODE_SLAVE)))
  {

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

    hi2c->XferCount = 0U;

    if (CurrentState == HAL_I2C_STATE_BUSY_TX_LISTEN)
    {

      hi2c->PreviousState = I2C_STATE_SLAVE_BUSY_TX;
      hi2c->State = HAL_I2C_STATE_LISTEN;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->SlaveTxCpltCallback(hi2c);
#else
      HAL_I2C_SlaveTxCpltCallback(hi2c);
#endif
    }
    else if (CurrentState == HAL_I2C_STATE_BUSY_RX_LISTEN)
    {

      hi2c->PreviousState = I2C_STATE_SLAVE_BUSY_RX;
      hi2c->State = HAL_I2C_STATE_LISTEN;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->SlaveRxCpltCallback(hi2c);
#else
      HAL_I2C_SlaveRxCpltCallback(hi2c);
#endif
    }
    else
    {

    }

    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);
  }

  else if (hi2c->Mode != HAL_I2C_MODE_NONE)
  {
    if (hi2c->XferCount == (uint16_t)1)
    {

      CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);
    }

    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_EVT | I2C_IT_ERR);

    if ((CurrentXferOptions == I2C_NO_OPTION_FRAME) || (CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_OTHER_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME))
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
    }

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_LAST);

    CLEAR_BIT(hi2c->Instance->CR2, I2C_CR2_DMAEN);

    hi2c->XferCount = 0U;

    if (hi2c->ErrorCode != HAL_I2C_ERROR_NONE)
    {
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
      hi2c->ErrorCallback(hi2c);
#else
      HAL_I2C_ErrorCallback(hi2c);
#endif
    }
    else
    {
      hi2c->State = HAL_I2C_STATE_READY;

      if (hi2c->Mode == HAL_I2C_MODE_MEM)
      {
        hi2c->Mode = HAL_I2C_MODE_NONE;
        hi2c->PreviousState = I2C_STATE_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->MemRxCpltCallback(hi2c);
#else
        HAL_I2C_MemRxCpltCallback(hi2c);
#endif
      }
      else
      {
        hi2c->Mode = HAL_I2C_MODE_NONE;
        if ((CurrentXferOptions == I2C_FIRST_AND_LAST_FRAME) || (CurrentXferOptions == I2C_LAST_FRAME))
        {
          hi2c->PreviousState = I2C_STATE_NONE;
        }
        else
        {
          hi2c->PreviousState = I2C_STATE_MASTER_BUSY_RX;
        }

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
        hi2c->MasterRxCpltCallback(hi2c);
#else
        HAL_I2C_MasterRxCpltCallback(hi2c);
#endif
      }
    }
  }
  else
  {

  }
}

static void I2C_DMAError(DMA_HandleTypeDef *hdma)
{
  I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hi2c->hdmatx != NULL)
  {
    hi2c->hdmatx->XferCpltCallback = NULL;
  }
  if (hi2c->hdmarx != NULL)
  {
    hi2c->hdmarx->XferCpltCallback = NULL;
  }

  if (HAL_DMA_GetError(hdma) != HAL_DMA_ERROR_FE)
  {

    hi2c->Instance->CR1 &= ~I2C_CR1_ACK;

    hi2c->XferCount = 0U;

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode = HAL_I2C_MODE_NONE;

    hi2c->ErrorCode |= HAL_I2C_ERROR_DMA;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ErrorCallback(hi2c);
#else
    HAL_I2C_ErrorCallback(hi2c);
#endif
  }
}

static void I2C_DMAAbort(DMA_HandleTypeDef *hdma)
{
  __IO uint32_t count = 0U;
  I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  HAL_I2C_StateTypeDef CurrentState = hi2c->State;

  count = I2C_TIMEOUT_FLAG * (SystemCoreClock / 25U / 1000U);
  do
  {
    if (count == 0U)
    {
      hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
      break;
    }
    count--;
  }
  while (READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP);

  if (hi2c->hdmatx != NULL)
  {
    hi2c->hdmatx->XferCpltCallback = NULL;
  }
  if (hi2c->hdmarx != NULL)
  {
    hi2c->hdmarx->XferCpltCallback = NULL;
  }

  CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

  hi2c->XferCount = 0U;

  if (hi2c->hdmatx != NULL)
  {
    hi2c->hdmatx->XferAbortCallback = NULL;
  }
  if (hi2c->hdmarx != NULL)
  {
    hi2c->hdmarx->XferAbortCallback = NULL;
  }

  __HAL_I2C_DISABLE(hi2c);

  if (hi2c->State == HAL_I2C_STATE_ABORT)
  {
    hi2c->State         = HAL_I2C_STATE_READY;
    hi2c->Mode          = HAL_I2C_MODE_NONE;
    hi2c->ErrorCode     = HAL_I2C_ERROR_NONE;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->AbortCpltCallback(hi2c);
#else
    HAL_I2C_AbortCpltCallback(hi2c);
#endif
  }
  else
  {
    if (((uint32_t)CurrentState & (uint32_t)HAL_I2C_STATE_LISTEN) == (uint32_t)HAL_I2C_STATE_LISTEN)
    {

      __HAL_I2C_ENABLE(hi2c);

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_ACK);

      hi2c->PreviousState = I2C_STATE_NONE;
      hi2c->State = HAL_I2C_STATE_LISTEN;
    }
    else
    {
      hi2c->State = HAL_I2C_STATE_READY;
      hi2c->Mode = HAL_I2C_MODE_NONE;
    }

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
    hi2c->ErrorCallback(hi2c);
#else
    HAL_I2C_ErrorCallback(hi2c);
#endif
  }
}

static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout, uint32_t Tickstart)
{

  while (__HAL_I2C_GET_FLAG(hi2c, Flag) == Status)
  {

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        if ((__HAL_I2C_GET_FLAG(hi2c, Flag) == Status))
        {
          hi2c->PreviousState     = I2C_STATE_NONE;
          hi2c->State             = HAL_I2C_STATE_READY;
          hi2c->Mode              = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode         |= HAL_I2C_ERROR_TIMEOUT;

          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout, uint32_t Tickstart)
{
  while (__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET)
  {
    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
    {

      SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

      hi2c->PreviousState       = I2C_STATE_NONE;
      hi2c->State               = HAL_I2C_STATE_READY;
      hi2c->Mode                = HAL_I2C_MODE_NONE;
      hi2c->ErrorCode           |= HAL_I2C_ERROR_AF;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        if ((__HAL_I2C_GET_FLAG(hi2c, Flag) == RESET))
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnTXEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
  while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == RESET)
  {

    if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_TXE) == RESET))
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnBTFFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
  while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == RESET)
  {

    if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
      {
        if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == RESET))
        {
          hi2c->PreviousState       = I2C_STATE_NONE;
          hi2c->State               = HAL_I2C_STATE_READY;
          hi2c->Mode                = HAL_I2C_MODE_NONE;
          hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

          __HAL_UNLOCK(hi2c);

          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnSTOPFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{
  while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF) == RESET)
  {

    if (I2C_IsAcknowledgeFailed(hi2c) != HAL_OK)
    {
      return HAL_ERROR;
    }

    if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
    {
      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF) == RESET))
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnSTOPRequestThroughIT(I2C_HandleTypeDef *hi2c)
{
  __IO uint32_t count = 0U;

  count = I2C_TIMEOUT_STOP_FLAG * (SystemCoreClock / 25U / 1000U);
  do
  {
    count--;
    if (count == 0U)
    {
      hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

      return HAL_ERROR;
    }
  }
  while (READ_BIT(hi2c->Instance->CR1, I2C_CR1_STOP) == I2C_CR1_STOP);

  return HAL_OK;
}

static HAL_StatusTypeDef I2C_WaitOnRXNEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout, uint32_t Tickstart)
{

  while (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == RESET)
  {

    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF) == SET)
    {

      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);

      hi2c->PreviousState       = I2C_STATE_NONE;
      hi2c->State               = HAL_I2C_STATE_READY;
      hi2c->Mode                = HAL_I2C_MODE_NONE;
      hi2c->ErrorCode           |= HAL_I2C_ERROR_NONE;

      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
    {
      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == RESET))
      {
        hi2c->PreviousState       = I2C_STATE_NONE;
        hi2c->State               = HAL_I2C_STATE_READY;
        hi2c->Mode                = HAL_I2C_MODE_NONE;
        hi2c->ErrorCode           |= HAL_I2C_ERROR_TIMEOUT;

        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }
  }
  return HAL_OK;
}

static HAL_StatusTypeDef I2C_IsAcknowledgeFailed(I2C_HandleTypeDef *hi2c)
{
  if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
  {

    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

    hi2c->PreviousState       = I2C_STATE_NONE;
    hi2c->State               = HAL_I2C_STATE_READY;
    hi2c->Mode                = HAL_I2C_MODE_NONE;
    hi2c->ErrorCode           |= HAL_I2C_ERROR_AF;

    __HAL_UNLOCK(hi2c);

    return HAL_ERROR;
  }
  return HAL_OK;
}

static void I2C_ConvertOtherXferOptions(I2C_HandleTypeDef *hi2c)
{

  if (hi2c->XferOptions == I2C_OTHER_FRAME)
  {
    hi2c->XferOptions = I2C_FIRST_FRAME;
  }

  else if (hi2c->XferOptions == I2C_OTHER_AND_LAST_FRAME)
  {
    hi2c->XferOptions = I2C_FIRST_AND_LAST_FRAME;
  }
  else
  {

  }
}

#endif
