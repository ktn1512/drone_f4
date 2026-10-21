#include "stm32f4xx_hal.h"

#ifdef HAL_FLASH_MODULE_ENABLED

#define FLASH_TIMEOUT_VALUE       50000U

extern FLASH_ProcessTypeDef pFlash;

static void               FLASH_MassErase(uint8_t VoltageRange, uint32_t Banks);
static HAL_StatusTypeDef  FLASH_OB_EnableWRP(uint32_t WRPSector, uint32_t Banks);
static HAL_StatusTypeDef  FLASH_OB_DisableWRP(uint32_t WRPSector, uint32_t Banks);
static HAL_StatusTypeDef  FLASH_OB_RDP_LevelConfig(uint8_t Level);
static HAL_StatusTypeDef  FLASH_OB_UserConfig(uint8_t Iwdg, uint8_t Stop, uint8_t Stdby);
static HAL_StatusTypeDef  FLASH_OB_BOR_LevelConfig(uint8_t Level);
static uint8_t            FLASH_OB_GetUser(void);
static uint16_t           FLASH_OB_GetWRP(void);
static uint8_t            FLASH_OB_GetRDP(void);
static uint8_t            FLASH_OB_GetBOR(void);

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) ||\
    defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
static HAL_StatusTypeDef  FLASH_OB_EnablePCROP(uint32_t Sector);
static HAL_StatusTypeDef  FLASH_OB_DisablePCROP(uint32_t Sector);
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
static HAL_StatusTypeDef FLASH_OB_EnablePCROP(uint32_t SectorBank1, uint32_t SectorBank2, uint32_t Banks);
static HAL_StatusTypeDef FLASH_OB_DisablePCROP(uint32_t SectorBank1, uint32_t SectorBank2, uint32_t Banks);
static HAL_StatusTypeDef FLASH_OB_BootConfig(uint8_t BootConfig);
#endif

extern HAL_StatusTypeDef         FLASH_WaitForLastOperation(uint32_t Timeout);

HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError)
{
  HAL_StatusTypeDef status;
  uint32_t index = 0U;

  __HAL_LOCK(&pFlash);

  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {

    *SectorError = 0xFFFFFFFFU;

    if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
    {

      FLASH_MassErase((uint8_t) pEraseInit->VoltageRange, pEraseInit->Banks);

      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      FLASH->CR &= (~FLASH_MER_BIT);
    }
    else
    {

      assert_param(IS_FLASH_NBSECTORS(pEraseInit->NbSectors + pEraseInit->Sector));

      for (index = pEraseInit->Sector; index < (pEraseInit->NbSectors + pEraseInit->Sector); index++)
      {
        FLASH_Erase_Sector(index, (uint8_t) pEraseInit->VoltageRange);

        status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

        CLEAR_BIT(FLASH->CR, (FLASH_CR_SER | FLASH_CR_SNB));

        if (status != HAL_OK)
        {

          *SectorError = index;
          break;
        }
      }
    }

    FLASH_FlushCaches();
  }

  __HAL_UNLOCK(&pFlash);

  return status;
}

HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_FLASH_TYPEERASE(pEraseInit->TypeErase));

  __HAL_FLASH_ENABLE_IT(FLASH_IT_EOP);

  __HAL_FLASH_ENABLE_IT(FLASH_IT_ERR);

  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | \
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

  if (pEraseInit->TypeErase == FLASH_TYPEERASE_MASSERASE)
  {

    pFlash.ProcedureOnGoing = FLASH_PROC_MASSERASE;
    pFlash.Bank = pEraseInit->Banks;
    FLASH_MassErase((uint8_t) pEraseInit->VoltageRange, pEraseInit->Banks);
  }
  else
  {

    assert_param(IS_FLASH_NBSECTORS(pEraseInit->NbSectors + pEraseInit->Sector));

    pFlash.ProcedureOnGoing = FLASH_PROC_SECTERASE;
    pFlash.NbSectorsToErase = pEraseInit->NbSectors;
    pFlash.Sector = pEraseInit->Sector;
    pFlash.VoltageForErase = (uint8_t)pEraseInit->VoltageRange;

    FLASH_Erase_Sector(pEraseInit->Sector, pEraseInit->VoltageRange);
  }

  return status;
}

HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  __HAL_LOCK(&pFlash);

  assert_param(IS_OPTIONBYTE(pOBInit->OptionType));

  if ((pOBInit->OptionType & OPTIONBYTE_WRP) == OPTIONBYTE_WRP)
  {
    assert_param(IS_WRPSTATE(pOBInit->WRPState));
    if (pOBInit->WRPState == OB_WRPSTATE_ENABLE)
    {

      status = FLASH_OB_EnableWRP(pOBInit->WRPSector, pOBInit->Banks);
    }
    else
    {

      status = FLASH_OB_DisableWRP(pOBInit->WRPSector, pOBInit->Banks);
    }
  }

  if ((pOBInit->OptionType & OPTIONBYTE_RDP) == OPTIONBYTE_RDP)
  {
    status = FLASH_OB_RDP_LevelConfig(pOBInit->RDPLevel);
  }

  if ((pOBInit->OptionType & OPTIONBYTE_USER) == OPTIONBYTE_USER)
  {
    status = FLASH_OB_UserConfig(pOBInit->USERConfig & OB_IWDG_SW,
                                 pOBInit->USERConfig & OB_STOP_NO_RST,
                                 pOBInit->USERConfig & OB_STDBY_NO_RST);
  }

  if ((pOBInit->OptionType & OPTIONBYTE_BOR) == OPTIONBYTE_BOR)
  {
    status = FLASH_OB_BOR_LevelConfig(pOBInit->BORLevel);
  }

  __HAL_UNLOCK(&pFlash);

  return status;
}

void HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit)
{
  pOBInit->OptionType = OPTIONBYTE_WRP | OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_BOR;

  pOBInit->WRPSector = (uint32_t)FLASH_OB_GetWRP();

  pOBInit->RDPLevel = (uint32_t)FLASH_OB_GetRDP();

  pOBInit->USERConfig = (uint8_t)FLASH_OB_GetUser();

  pOBInit->BORLevel = (uint32_t)FLASH_OB_GetBOR();
}

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

HAL_StatusTypeDef HAL_FLASHEx_AdvOBProgram(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit)
{
  HAL_StatusTypeDef status = HAL_ERROR;

  assert_param(IS_OBEX(pAdvOBInit->OptionType));

  if (((pAdvOBInit->OptionType) & OPTIONBYTE_PCROP) == OPTIONBYTE_PCROP)
  {

    assert_param(IS_PCROPSTATE(pAdvOBInit->PCROPState));
    if ((pAdvOBInit->PCROPState) == OB_PCROP_STATE_ENABLE)
    {

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||\
    defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
      status = FLASH_OB_EnablePCROP(pAdvOBInit->Sectors);
#else
      status = FLASH_OB_EnablePCROP(pAdvOBInit->SectorsBank1, pAdvOBInit->SectorsBank2, pAdvOBInit->Banks);
#endif
    }
    else
    {

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||\
    defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
      status = FLASH_OB_DisablePCROP(pAdvOBInit->Sectors);
#else
      status = FLASH_OB_DisablePCROP(pAdvOBInit->SectorsBank1, pAdvOBInit->SectorsBank2, pAdvOBInit->Banks);
#endif
    }
  }

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

  if (((pAdvOBInit->OptionType) & OPTIONBYTE_BOOTCONFIG) == OPTIONBYTE_BOOTCONFIG)
  {
    status = FLASH_OB_BootConfig(pAdvOBInit->BootConfig);
  }
#endif

  return status;
}

void HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit)
{
#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||\
    defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

  pAdvOBInit->Sectors = (*(__IO uint16_t *)(OPTCR_BYTE2_ADDRESS));
#else

  pAdvOBInit->SectorsBank1 = (*(__IO uint16_t *)(OPTCR_BYTE2_ADDRESS));

  pAdvOBInit->SectorsBank2 = (*(__IO uint16_t *)(OPTCR1_BYTE2_ADDRESS));

  pAdvOBInit->BootConfig = *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS;
#endif
}

HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void)
{
  uint8_t optiontmp;

  optiontmp = (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE3_ADDRESS) & (uint8_t)0x7F);

  *(__IO uint8_t *)OPTCR_BYTE3_ADDRESS = (uint8_t)(OB_PCROP_SELECTED | optiontmp);

  return HAL_OK;
}

HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void)
{
  uint8_t optiontmp;

  optiontmp = (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE3_ADDRESS) & (uint8_t)0x7F);

  *(__IO uint8_t *)OPTCR_BYTE3_ADDRESS = (uint8_t)(OB_PCROP_DESELECTED | optiontmp);

  return HAL_OK;
}
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

uint16_t HAL_FLASHEx_OB_GetBank2WRP(void)
{

  return (*(__IO uint16_t *)(OPTCR1_BYTE2_ADDRESS));
}
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

static void FLASH_MassErase(uint8_t VoltageRange, uint32_t Banks)
{

  assert_param(IS_VOLTAGERANGE(VoltageRange));
  assert_param(IS_FLASH_BANK(Banks));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);

  if (Banks == FLASH_BANK_BOTH)
  {

    FLASH->CR |= FLASH_MER_BIT;
  }
  else if (Banks == FLASH_BANK_1)
  {

    FLASH->CR |= FLASH_CR_MER1;
  }
  else
  {

    FLASH->CR |= FLASH_CR_MER2;
  }
  FLASH->CR |= FLASH_CR_STRT | ((uint32_t)VoltageRange << 8U);
}

void FLASH_Erase_Sector(uint32_t Sector, uint8_t VoltageRange)
{
  uint32_t tmp_psize = 0U;

  assert_param(IS_FLASH_SECTOR(Sector));
  assert_param(IS_VOLTAGERANGE(VoltageRange));

  if (VoltageRange == FLASH_VOLTAGE_RANGE_1)
  {
    tmp_psize = FLASH_PSIZE_BYTE;
  }
  else if (VoltageRange == FLASH_VOLTAGE_RANGE_2)
  {
    tmp_psize = FLASH_PSIZE_HALF_WORD;
  }
  else if (VoltageRange == FLASH_VOLTAGE_RANGE_3)
  {
    tmp_psize = FLASH_PSIZE_WORD;
  }
  else
  {
    tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
  }

  if (Sector > FLASH_SECTOR_11)
  {
    Sector += 4U;
  }

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= tmp_psize;
  CLEAR_BIT(FLASH->CR, FLASH_CR_SNB);
  FLASH->CR |= FLASH_CR_SER | (Sector << FLASH_CR_SNB_Pos);
  FLASH->CR |= FLASH_CR_STRT;
}

static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_WRP_SECTOR(WRPSector));
  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (((WRPSector == OB_WRP_SECTOR_All) && ((Banks == FLASH_BANK_1) || (Banks == FLASH_BANK_BOTH))) ||
        (WRPSector < OB_WRP_SECTOR_12))
    {
      if (WRPSector == OB_WRP_SECTOR_All)
      {

        *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS &= (~(WRPSector >> 12));
      }
      else
      {

        *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS &= (~WRPSector);
      }
    }
    else
    {

      *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS &= (~(WRPSector >> 12));
    }

    if ((WRPSector == OB_WRP_SECTOR_All) && (Banks == FLASH_BANK_BOTH))
    {

      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      if (status == HAL_OK)
      {
        *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS &= (~(WRPSector >> 12));
      }
    }

  }
  return status;
}

static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_WRP_SECTOR(WRPSector));
  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if (((WRPSector == OB_WRP_SECTOR_All) && ((Banks == FLASH_BANK_1) || (Banks == FLASH_BANK_BOTH))) ||
        (WRPSector < OB_WRP_SECTOR_12))
    {
      if (WRPSector == OB_WRP_SECTOR_All)
      {

        *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS |= (uint16_t)(WRPSector >> 12);
      }
      else
      {

        *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS |= (uint16_t)WRPSector;
      }
    }
    else
    {

      *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS |= (uint16_t)(WRPSector >> 12);
    }

    if ((WRPSector == OB_WRP_SECTOR_All) && (Banks == FLASH_BANK_BOTH))
    {

      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      if (status == HAL_OK)
      {
        *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS |= (uint16_t)(WRPSector >> 12);
      }
    }

  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_BootConfig(uint8_t BootConfig)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_BOOT(BootConfig));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {

    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS &= (~FLASH_OPTCR_BFB2);
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= BootConfig;
  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_EnablePCROP(uint32_t SectorBank1, uint32_t SectorBank2, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if ((Banks == FLASH_BANK_1) || (Banks == FLASH_BANK_BOTH))
    {
      assert_param(IS_OB_PCROP(SectorBank1));

      *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS |= (uint16_t)SectorBank1;
    }
    else
    {
      assert_param(IS_OB_PCROP(SectorBank2));

      *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS |= (uint16_t)SectorBank2;
    }

    if (Banks == FLASH_BANK_BOTH)
    {
      assert_param(IS_OB_PCROP(SectorBank2));

      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      if (status == HAL_OK)
      {

        *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS |= (uint16_t)SectorBank2;
      }
    }

  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_DisablePCROP(uint32_t SectorBank1, uint32_t SectorBank2, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    if ((Banks == FLASH_BANK_1) || (Banks == FLASH_BANK_BOTH))
    {
      assert_param(IS_OB_PCROP(SectorBank1));

      *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS &= (~SectorBank1);
    }
    else
    {

      assert_param(IS_OB_PCROP(SectorBank2));
      *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS &= (~SectorBank2);
    }

    if (Banks == FLASH_BANK_BOTH)
    {
      assert_param(IS_OB_PCROP(SectorBank2));

      status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

      if (status == HAL_OK)
      {

        *(__IO uint16_t *)OPTCR1_BYTE2_ADDRESS &= (~SectorBank2);
      }
    }

  }

  return status;

}

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)

static void FLASH_MassErase(uint8_t VoltageRange, uint32_t Banks)
{

  assert_param(IS_VOLTAGERANGE(VoltageRange));
  assert_param(IS_FLASH_BANK(Banks));

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= FLASH_CR_MER;
  FLASH->CR |= FLASH_CR_STRT | ((uint32_t)VoltageRange << 8U);
}

void FLASH_Erase_Sector(uint32_t Sector, uint8_t VoltageRange)
{
  uint32_t tmp_psize = 0U;

  assert_param(IS_FLASH_SECTOR(Sector));
  assert_param(IS_VOLTAGERANGE(VoltageRange));

  if (VoltageRange == FLASH_VOLTAGE_RANGE_1)
  {
    tmp_psize = FLASH_PSIZE_BYTE;
  }
  else if (VoltageRange == FLASH_VOLTAGE_RANGE_2)
  {
    tmp_psize = FLASH_PSIZE_HALF_WORD;
  }
  else if (VoltageRange == FLASH_VOLTAGE_RANGE_3)
  {
    tmp_psize = FLASH_PSIZE_WORD;
  }
  else
  {
    tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
  }

  CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
  FLASH->CR |= tmp_psize;
  CLEAR_BIT(FLASH->CR, FLASH_CR_SNB);
  FLASH->CR |= FLASH_CR_SER | (Sector << FLASH_CR_SNB_Pos);
  FLASH->CR |= FLASH_CR_STRT;
}

static HAL_StatusTypeDef FLASH_OB_EnableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_WRP_SECTOR(WRPSector));
  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS &= (~WRPSector);
  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_DisableWRP(uint32_t WRPSector, uint32_t Banks)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_WRP_SECTOR(WRPSector));
  assert_param(IS_FLASH_BANK(Banks));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS |= (uint16_t)WRPSector;
  }

  return status;
}
#endif

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) ||\
    defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

static HAL_StatusTypeDef FLASH_OB_EnablePCROP(uint32_t Sector)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_PCROP(Sector));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS |= (uint16_t)Sector;
  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_DisablePCROP(uint32_t Sector)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_PCROP(Sector));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    *(__IO uint16_t *)OPTCR_BYTE2_ADDRESS &= (~Sector);
  }

  return status;

}
#endif

static HAL_StatusTypeDef FLASH_OB_RDP_LevelConfig(uint8_t Level)
{
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_RDP_LEVEL(Level));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {
    *(__IO uint8_t *)OPTCR_BYTE1_ADDRESS = Level;
  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_UserConfig(uint8_t Iwdg, uint8_t Stop, uint8_t Stdby)
{
  uint8_t optiontmp;
  HAL_StatusTypeDef status = HAL_OK;

  assert_param(IS_OB_IWDG_SOURCE(Iwdg));
  assert_param(IS_OB_STOP_SOURCE(Stop));
  assert_param(IS_OB_STDBY_SOURCE(Stdby));

  status = FLASH_WaitForLastOperation((uint32_t)FLASH_TIMEOUT_VALUE);

  if (status == HAL_OK)
  {

    optiontmp = (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE0_ADDRESS) & (uint8_t)0x1F);

    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS = Iwdg | (uint8_t)(Stdby | (uint8_t)(Stop | ((uint8_t)optiontmp)));
  }

  return status;
}

static HAL_StatusTypeDef FLASH_OB_BOR_LevelConfig(uint8_t Level)
{

  assert_param(IS_OB_BOR_LEVEL(Level));

  *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS &= (~FLASH_OPTCR_BOR_LEV);
  *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= Level;

  return HAL_OK;

}

static uint8_t FLASH_OB_GetUser(void)
{

  return ((uint8_t)(FLASH->OPTCR & 0xE0));
}

static uint16_t FLASH_OB_GetWRP(void)
{

  return (*(__IO uint16_t *)(OPTCR_BYTE2_ADDRESS));
}

static uint8_t FLASH_OB_GetRDP(void)
{
  uint8_t readstatus = OB_RDP_LEVEL_0;

  if (*(__IO uint8_t *)(OPTCR_BYTE1_ADDRESS) == (uint8_t)OB_RDP_LEVEL_2)
  {
    readstatus = OB_RDP_LEVEL_2;
  }
  else if (*(__IO uint8_t *)(OPTCR_BYTE1_ADDRESS) == (uint8_t)OB_RDP_LEVEL_0)
  {
    readstatus = OB_RDP_LEVEL_0;
  }
  else
  {
    readstatus = OB_RDP_LEVEL_1;
  }

  return readstatus;
}

static uint8_t FLASH_OB_GetBOR(void)
{

  return (uint8_t)(*(__IO uint8_t *)(OPTCR_BYTE0_ADDRESS) & (uint8_t)0x0C);
}

void FLASH_FlushCaches(void)
{

  if (READ_BIT(FLASH->ACR, FLASH_ACR_ICEN) != RESET)
  {

    __HAL_FLASH_INSTRUCTION_CACHE_DISABLE();

    __HAL_FLASH_INSTRUCTION_CACHE_RESET();

    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
  }

  if (READ_BIT(FLASH->ACR, FLASH_ACR_DCEN) != RESET)
  {

    __HAL_FLASH_DATA_CACHE_DISABLE();

    __HAL_FLASH_DATA_CACHE_RESET();

    __HAL_FLASH_DATA_CACHE_ENABLE();
  }
}

#endif
