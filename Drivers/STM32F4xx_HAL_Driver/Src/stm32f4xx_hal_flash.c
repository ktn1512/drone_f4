#include "stm32f4xx_hal.h"

#ifdef HAL_FLASH_MODULE_ENABLED

#define FLASH_TIMEOUT_VALUE       50000U

FLASH_ProcessTypeDef pFlash  = {.ProcedureOnGoing = FLASH_PROC_NONE,
                                .NbSectorsToErase = 0U,
                                .VoltageForErase= FLASH_VOLTAGE_RANGE_1,
                                .Sector = 0U,
                                .Bank = FLASH_BANK_1,
                                .Address = 0U,
                                .Lock = HAL_UNLOCKED,
                                .ErrorCode = HAL_FLASH_ERROR_NONE};

static void   FLASH_Program_DoubleWord(uint32_t Address, uint64_t Data);
static void   FLASH_Program_Word(uint32_t Address, uint32_t Data);
static void   FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);
static void   FLASH_Program_Byte(uint32_t Address, uint8_t Data);
static void   FLASH_SetErrorCode(void);

HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);

HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status;

  __HAL_LOCK(&pFlash);

  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (TypeProgram == FLASH_TYPEPROGRAM_BYTE)
    {

      FLASH_Program_Byte(Address, (uint8_t) Data);
    }
    else if (TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
    {

      FLASH_Program_HalfWord(Address, (uint16_t) Data);
    }
    else if (TypeProgram == FLASH_TYPEPROGRAM_WORD)
    {

      FLASH_Program_Word(Address, (uint32_t) Data);
    }
    else
    {

      FLASH_Program_DoubleWord(Address, Data);
    }

    status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

    FLASH->CR &= (~FLASH_CR_PG);
  }

  __HAL_UNLOCK(&pFlash);

  return status;
}

HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_FLASH_TYPEPROGRAM(TypeProgram));

  __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP);

  __HAL_FLASH_ENABLE_IT(FLASH_IT_ERR);

  pFlash.ProcedureOnGoing = FLASH_PROC_PROGRAM;
  pFlash.Address = Address;

  if (TypeProgram == FLASH_TYPEPROGRAM_BYTE)
  {

    FLASH_Program_Byte(Address, (uint8_t) Data);
  }
  else if (TypeProgram == FLASH_TYPEPROGRAM_HALFWORD)
  {

    FLASH_Program_HalfWord(Address, (uint16_t) Data);
  }
  else if (TypeProgram == FLASH_TYPEPROGRAM_WORD)
  {

    FLASH_Program_Word(Address, (uint32_t) Data);
  }
  else
  {

    FLASH_Program_DoubleWord(Address, Data);
  }

  return status;
}

void HAL_FLASH_IRQHandler(void)
{
  uint32_t addresstmp = 0U;

#if defined(FLASH_SR_RDERR)
  if (__HAL_FLASH_GET_FLAG((FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                            FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR)) != RESET)
#else
  if (__HAL_FLASH_GET_FLAG((FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                            FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR)) != RESET)
#endif
  {
    if (pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE)
    {

      addresstmp = pFlash.Sector;
      pFlash.Sector = 0xFFFFFFFFU;
    }
    else if (pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE)
    {

      addresstmp = pFlash.Bank;
    }
    else
    {

      addresstmp = pFlash.Address;
    }

    FLASH_SetErrorCode();

    HAL_FLASH_OperationErrorCallback(addresstmp);

    pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP) != RESET)
  {

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);

    if (pFlash.ProcedureOnGoing == FLASH_PROC_SECTERASE)
    {

      pFlash.NbSectorsToErase--;

      if (pFlash.NbSectorsToErase != 0U)
      {
        addresstmp = pFlash.Sector;

        HAL_FLASH_EndOfOperationCallback(addresstmp);

        pFlash.Sector++;
        addresstmp = pFlash.Sector;
        FLASH_Erase_Sector(addresstmp, pFlash.VoltageForErase);
      }
      else
      {

        pFlash.Sector = addresstmp = 0xFFFFFFFFU;
        pFlash.ProcedureOnGoing = FLASH_PROC_NONE;

        FLASH_FlushCaches();

        HAL_FLASH_EndOfOperationCallback(addresstmp);
      }
    }
    else
    {
      if (pFlash.ProcedureOnGoing == FLASH_PROC_MASSERASE)
      {

        FLASH_FlushCaches();

        HAL_FLASH_EndOfOperationCallback(pFlash.Bank);
      }
      else
      {

        HAL_FLASH_EndOfOperationCallback(pFlash.Address);
      }
      pFlash.ProcedureOnGoing = FLASH_PROC_NONE;
    }
  }

  if (pFlash.ProcedureOnGoing == FLASH_PROC_NONE)
  {

    CLEAR_BIT(FLASH->CR, (FLASH_CR_PG | FLASH_CR_SER | FLASH_CR_SNB | FLASH_MER_BIT));

    __HAL_FLASH_DISABLE_IT(FLASH_IT_EOP);

    __HAL_FLASH_DISABLE_IT(FLASH_IT_ERR);
  }
}

__weak void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{

  UNUSED(ReturnValue);

}

__weak void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue)
{

  UNUSED(ReturnValue);

}

HAL_StatusTypeDef HAL_FLASH_Unlock(void)
{
  HAL_StatusTypeDef status = HAL_OK;

  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
  {

    WRITE_REG(FLASH->KEYR, FLASH_KEY1);
    WRITE_REG(FLASH->KEYR, FLASH_KEY2);

    if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET)
    {
      status = HAL_ERROR;
    }
  }

  return status;
}

HAL_StatusTypeDef HAL_FLASH_Lock(void)
{

  FLASH->CR |= FLASH_CR_LOCK;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void)
{
  if ((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) != RESET)
  {

    FLASH->OPTKEYR = FLASH_OPT_KEY1;
    FLASH->OPTKEYR = FLASH_OPT_KEY2;
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_FLASH_OB_Lock(void)
{

  FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;

  return HAL_OK;
}

HAL_StatusTypeDef HAL_FLASH_OB_Launch(void)
{

  *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;

  return (FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE));
}

uint32_t HAL_FLASH_GetError(void)
{
  return pFlash.ErrorCode;
}

HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout)
{
  uint32_t tickstart = 0U;

  pFlash.ErrorCode = HAL_FLASH_ERROR_NONE;

  tickstart = HAL_GetTick();

  while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET)
  {
    if (Timeout != HAL_MAX_DELAY)
    {
      if ((Timeout == 0U) || ((HAL_GetTick() - tickstart) > Timeout))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP) != RESET)
  {

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
  }
#if defined(FLASH_SR_RDERR)
  if (__HAL_FLASH_GET_FLAG((FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                            FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR | FLASH_FLAG_RDERR)) != RESET)
#else
  if (__HAL_FLASH_GET_FLAG((FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | \
                            FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR)) != RESET)
#endif
  {

    FLASH_SetErrorCode();
    return HAL_ERROR;
  }

  return HAL_OK;

}

static void FLASH_Program_DoubleWord(uint32_t Address, uint64_t Data)
{

  assert_param(IS_FLASH_ADDRESS(Address));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t *)Address = (uint32_t)Data;

  __ISB();

  *(__IO uint32_t *)(Address + 4) = (uint32_t)(Data >> 32);
}

static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{

  assert_param(IS_FLASH_ADDRESS(Address));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint32_t *)Address = Data;
}

static void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{

  assert_param(IS_FLASH_ADDRESS(Address));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_HALF_WORD;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint16_t *)Address = Data;
}

static void FLASH_Program_Byte(uint32_t Address, uint8_t Data)
{

  assert_param(IS_FLASH_ADDRESS(Address));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_PSIZE_BYTE;
  FLASH->CR |= FLASH_CR_PG;

  *(__IO uint8_t *)Address = Data;
}

static void FLASH_SetErrorCode(void)
{
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_WRPERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_WRP;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_WRPERR);
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGAERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_PGA;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGAERR);
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGPERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_PGP;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGPERR);
  }

  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_PGSERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_PGS;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_PGSERR);
  }
#if defined(FLASH_SR_RDERR)
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_RDERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_RD;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_RDERR);
  }
#endif
  if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_OPERR) != RESET)
  {
    pFlash.ErrorCode |= HAL_FLASH_ERROR_OPERATION;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPERR);
  }
}

#endif
