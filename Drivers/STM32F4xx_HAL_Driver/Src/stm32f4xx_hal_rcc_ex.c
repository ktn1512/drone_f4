#include "stm32f4xx_hal.h"

#ifdef HAL_RCC_MODULE_ENABLED

#if defined(STM32F446xx)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;
  uint32_t plli2sp = 0U;
  uint32_t plli2sq = 0U;
  uint32_t plli2sr = 0U;
  uint32_t pllsaip = 0U;
  uint32_t pllsaiq = 0U;
  uint32_t plli2sused = 0U;
  uint32_t pllsaiused = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB1) == (RCC_PERIPHCLK_I2S_APB1))
  {

    assert_param(IS_RCC_I2SAPB1CLKSOURCE(PeriphClkInit->I2sApb1ClockSelection));

    __HAL_RCC_I2S_APB1_CONFIG(PeriphClkInit->I2sApb1ClockSelection);

    if (PeriphClkInit->I2sApb1ClockSelection == RCC_I2SAPB1CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB2) == (RCC_PERIPHCLK_I2S_APB2))
  {

    assert_param(IS_RCC_I2SAPB2CLKSOURCE(PeriphClkInit->I2sApb2ClockSelection));

    __HAL_RCC_I2S_APB2_CONFIG(PeriphClkInit->I2sApb2ClockSelection);

    if (PeriphClkInit->I2sApb2ClockSelection == RCC_I2SAPB2CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == (RCC_PERIPHCLK_SAI1))
  {

    assert_param(IS_RCC_SAI1CLKSOURCE(PeriphClkInit->Sai1ClockSelection));

    __HAL_RCC_SAI1_CONFIG(PeriphClkInit->Sai1ClockSelection);

    if (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }

    if (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLLSAI)
    {
      pllsaiused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI2) == (RCC_PERIPHCLK_SAI2))
  {

    assert_param(IS_RCC_SAI2CLKSOURCE(PeriphClkInit->Sai2ClockSelection));

    __HAL_RCC_SAI2_CONFIG(PeriphClkInit->Sai2ClockSelection);

    if (PeriphClkInit->Sai2ClockSelection == RCC_SAI2CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }

    if (PeriphClkInit->Sai2ClockSelection == RCC_SAI2CLKSOURCE_PLLSAI)
    {
      pllsaiused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {

    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FMPI2C1) == RCC_PERIPHCLK_FMPI2C1)
  {

    assert_param(IS_RCC_FMPI2C1CLKSOURCE(PeriphClkInit->Fmpi2c1ClockSelection));

    __HAL_RCC_FMPI2C1_CONFIG(PeriphClkInit->Fmpi2c1ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CEC) == RCC_PERIPHCLK_CEC)
  {

    assert_param(IS_RCC_CECCLKSOURCE(PeriphClkInit->CecClockSelection));

    __HAL_RCC_CEC_CONFIG(PeriphClkInit->CecClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)
  {

    assert_param(IS_RCC_CLK48CLKSOURCE(PeriphClkInit->Clk48ClockSelection));

    __HAL_RCC_CLK48_CONFIG(PeriphClkInit->Clk48ClockSelection);

    if (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLSAIP)
    {
      pllsaiused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDIO) == RCC_PERIPHCLK_SDIO)
  {

    assert_param(IS_RCC_SDIOCLKSOURCE(PeriphClkInit->SdioClockSelection));

    __HAL_RCC_SDIO_CONFIG(PeriphClkInit->SdioClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPDIFRX) == RCC_PERIPHCLK_SPDIFRX)
  {

    assert_param(IS_RCC_SPDIFRXCLKSOURCE(PeriphClkInit->SpdifClockSelection));

    __HAL_RCC_SPDIFRX_CONFIG(PeriphClkInit->SpdifClockSelection);

    if (PeriphClkInit->SpdifClockSelection == RCC_SPDIFRXCLKSOURCE_PLLI2SP)
    {
      plli2sused = 1U;
    }
  }

  if ((plli2sused == 1U) || (PeriphClkInit->PeriphClockSelection == RCC_PERIPHCLK_PLLI2S))
  {

    __HAL_RCC_PLLI2S_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    assert_param(IS_RCC_PLLI2SM_VALUE(PeriphClkInit->PLLI2S.PLLI2SM));
    assert_param(IS_RCC_PLLI2SN_VALUE(PeriphClkInit->PLLI2S.PLLI2SN));

    if (((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB1) == RCC_PERIPHCLK_I2S_APB1)
         && (PeriphClkInit->I2sApb1ClockSelection == RCC_I2SAPB1CLKSOURCE_PLLI2S)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB2) == RCC_PERIPHCLK_I2S_APB2) && (PeriphClkInit->I2sApb2ClockSelection == RCC_I2SAPB2CLKSOURCE_PLLI2S)))
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      plli2sp = ((((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >> RCC_PLLI2SCFGR_PLLI2SP_Pos) + 1U) << 1U);
      plli2sq = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, plli2sp, plli2sq,
                              PeriphClkInit->PLLI2S.PLLI2SR);
    }

    if (((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1)
         && (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLLI2S)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI2) == RCC_PERIPHCLK_SAI2) && (PeriphClkInit->Sai2ClockSelection == RCC_SAI2CLKSOURCE_PLLI2S)))
    {

      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));

      assert_param(IS_RCC_PLLI2S_DIVQ_VALUE(PeriphClkInit->PLLI2SDivQ));

      plli2sp = ((((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >> RCC_PLLI2SCFGR_PLLI2SP_Pos) + 1U) << 1U);
      plli2sr = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, plli2sp,
                              PeriphClkInit->PLLI2S.PLLI2SQ, plli2sr);

      __HAL_RCC_PLLI2S_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLI2SDivQ);
    }

    if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SPDIFRX) == RCC_PERIPHCLK_SPDIFRX)
        && (PeriphClkInit->SpdifClockSelection == RCC_SPDIFRXCLKSOURCE_PLLI2SP))
    {

      assert_param(IS_RCC_PLLI2SP_VALUE(PeriphClkInit->PLLI2S.PLLI2SP));

      plli2sq = ((((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >> RCC_PLLI2SCFGR_PLLI2SP_Pos) + 1U) << 1U);
      plli2sr = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SP,
                              plli2sq, plli2sr);
    }

    if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S)
    {

      assert_param(IS_RCC_PLLI2SP_VALUE(PeriphClkInit->PLLI2S.PLLI2SP));
      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));
      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SP,
                              PeriphClkInit->PLLI2S.PLLI2SQ, PeriphClkInit->PLLI2S.PLLI2SR);
    }

    __HAL_RCC_PLLI2S_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if (pllsaiused == 1U)
  {

    __HAL_RCC_PLLSAI_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    assert_param(IS_RCC_PLLSAIM_VALUE(PeriphClkInit->PLLSAI.PLLSAIM));
    assert_param(IS_RCC_PLLSAIN_VALUE(PeriphClkInit->PLLSAI.PLLSAIN));

    if (((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI1) == RCC_PERIPHCLK_SAI1)
         && (PeriphClkInit->Sai1ClockSelection == RCC_SAI1CLKSOURCE_PLLSAI)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI2) == RCC_PERIPHCLK_SAI2) && (PeriphClkInit->Sai2ClockSelection == RCC_SAI2CLKSOURCE_PLLSAI)))
    {

      assert_param(IS_RCC_PLLSAIQ_VALUE(PeriphClkInit->PLLSAI.PLLSAIQ));

      assert_param(IS_RCC_PLLSAI_DIVQ_VALUE(PeriphClkInit->PLLSAIDivQ));

      pllsaip = ((((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >> RCC_PLLSAICFGR_PLLSAIP_Pos) + 1U) << 1U);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIM, PeriphClkInit->PLLSAI.PLLSAIN, pllsaip,
                              PeriphClkInit->PLLSAI.PLLSAIQ, 0U);

      __HAL_RCC_PLLSAI_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLSAIDivQ);
    }

    if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)
        && (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLSAIP))
    {

      assert_param(IS_RCC_PLLSAIP_VALUE(PeriphClkInit->PLLSAI.PLLSAIP));

      pllsaiq = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIM, PeriphClkInit->PLLSAI.PLLSAIN, PeriphClkInit->PLLSAI.PLLSAIP,
                              pllsaiq, 0U);
    }

    __HAL_RCC_PLLSAI_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S_APB1 | RCC_PERIPHCLK_I2S_APB2 | \
                                        RCC_PERIPHCLK_SAI1     | RCC_PERIPHCLK_SAI2     | \
                                        RCC_PERIPHCLK_TIM      | RCC_PERIPHCLK_RTC      | \
                                        RCC_PERIPHCLK_CEC      | RCC_PERIPHCLK_FMPI2C1  | \
                                        RCC_PERIPHCLK_CLK48     | RCC_PERIPHCLK_SDIO     | \
                                        RCC_PERIPHCLK_SPDIFRX;

  PeriphClkInit->PLLI2S.PLLI2SM = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM) >> RCC_PLLI2SCFGR_PLLI2SM_Pos);
  PeriphClkInit->PLLI2S.PLLI2SN = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> RCC_PLLI2SCFGR_PLLI2SN_Pos);
  PeriphClkInit->PLLI2S.PLLI2SP = (uint32_t)((((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SP) >> RCC_PLLI2SCFGR_PLLI2SP_Pos) + 1U) << 1U);
  PeriphClkInit->PLLI2S.PLLI2SQ = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);
  PeriphClkInit->PLLI2S.PLLI2SR = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);

  PeriphClkInit->PLLSAI.PLLSAIM = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIM) >> RCC_PLLSAICFGR_PLLSAIM_Pos);
  PeriphClkInit->PLLSAI.PLLSAIN = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIN) >> RCC_PLLSAICFGR_PLLSAIN_Pos);
  PeriphClkInit->PLLSAI.PLLSAIP = (uint32_t)((((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >> RCC_PLLSAICFGR_PLLSAIP_Pos) + 1U) << 1U);
  PeriphClkInit->PLLSAI.PLLSAIQ = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

  PeriphClkInit->PLLI2SDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLI2SDIVQ) >> RCC_DCKCFGR_PLLI2SDIVQ_Pos);
  PeriphClkInit->PLLSAIDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVQ) >> RCC_DCKCFGR_PLLSAIDIVQ_Pos);

  PeriphClkInit->Sai1ClockSelection = __HAL_RCC_GET_SAI1_SOURCE();

  PeriphClkInit->Sai2ClockSelection = __HAL_RCC_GET_SAI2_SOURCE();

  PeriphClkInit->I2sApb1ClockSelection = __HAL_RCC_GET_I2S_APB1_SOURCE();

  PeriphClkInit->I2sApb2ClockSelection = __HAL_RCC_GET_I2S_APB2_SOURCE();

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

  PeriphClkInit->CecClockSelection = __HAL_RCC_GET_CEC_SOURCE();

  PeriphClkInit->Fmpi2c1ClockSelection = __HAL_RCC_GET_FMPI2C1_SOURCE();

  PeriphClkInit->Clk48ClockSelection = __HAL_RCC_GET_CLK48_SOURCE();

  PeriphClkInit->SdioClockSelection = __HAL_RCC_GET_SDIO_SOURCE();

  PeriphClkInit->SpdifClockSelection = __HAL_RCC_GET_SPDIFRX_SOURCE();

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }
}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{
  uint32_t tmpreg1 = 0U;

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;

  uint32_t saiclocksource = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_SAI1:
    case RCC_PERIPHCLK_SAI2:
    {
      saiclocksource = RCC->DCKCFGR;
      saiclocksource &= (RCC_DCKCFGR_SAI1SRC | RCC_DCKCFGR_SAI2SRC);
      switch (saiclocksource)
      {
        case 0U:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSI)
          {

            vcoinput = (HSI_VALUE / (uint32_t)(RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIM));
          }
          else
          {

            vcoinput = ((HSE_VALUE / (uint32_t)(RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIM)));
          }

          tmpreg1 = (RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> 24U;
          frequency = (vcoinput * ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIN) >> 6U)) / (tmpreg1);

          tmpreg1 = (((RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVQ) >> 8U) + 1U);
          frequency = frequency / (tmpreg1);
          break;
        }
        case RCC_DCKCFGR_SAI1SRC_0:
        case RCC_DCKCFGR_SAI2SRC_0:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSI)
          {

            vcoinput = (HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            vcoinput = ((HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM)));
          }

          tmpreg1 = (RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> 24U;
          frequency = (vcoinput * ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U)) / (tmpreg1);

          tmpreg1 = ((RCC->DCKCFGR & RCC_DCKCFGR_PLLI2SDIVQ) + 1U);
          frequency = frequency / (tmpreg1);
          break;
        }
        case RCC_DCKCFGR_SAI1SRC_1:
        case RCC_DCKCFGR_SAI2SRC_1:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSI)
          {

            vcoinput = (HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = ((HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM)));
          }

          tmpreg1 = (RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U;
          frequency = (vcoinput * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U)) / (tmpreg1);
          break;
        }
        case RCC_DCKCFGR_SAI1SRC:
        {
          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }
        case RCC_DCKCFGR_SAI2SRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSI)
          {

            frequency = (uint32_t)(HSI_VALUE);
          }
          else
          {

            frequency = (uint32_t)(HSE_VALUE);
          }
          break;
        }
        default :
        {
          break;
        }
      }
      break;
    }
    case RCC_PERIPHCLK_I2S_APB1:
    {

      srcclk = __HAL_RCC_GET_I2S_APB1_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SAPB1CLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLI2S:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLR:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U) & (RCC_PLLCFGR_PLLN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U) & (RCC_PLLCFGR_PLLR >> 28U)));
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLSRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {
            frequency = HSE_VALUE;
          }
          else
          {
            frequency = HSI_VALUE;
          }
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    case RCC_PERIPHCLK_I2S_APB2:
    {

      srcclk = __HAL_RCC_GET_I2S_APB2_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SAPB2CLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLI2S:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLR:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U) & (RCC_PLLCFGR_PLLN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U) & (RCC_PLLCFGR_PLLR >> 28U)));
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLSRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {
            frequency = HSE_VALUE;
          }
          else
          {
            frequency = HSI_VALUE;
          }
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;
  uint32_t pllsaip = 0U;
  uint32_t pllsaiq = 0U;
  uint32_t pllsair = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)
  {

    assert_param(IS_RCC_CLK48CLKSOURCE(PeriphClkInit->Clk48ClockSelection));

    __HAL_RCC_CLK48_CONFIG(PeriphClkInit->Clk48ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDIO) == RCC_PERIPHCLK_SDIO)
  {

    assert_param(IS_RCC_SDIOCLKSOURCE(PeriphClkInit->SdioClockSelection));

    __HAL_RCC_SDIO_CONFIG(PeriphClkInit->SdioClockSelection);
  }

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLI2S) == RCC_PERIPHCLK_SAI_PLLI2S) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S))
  {

    assert_param(IS_RCC_PLLI2SN_VALUE(PeriphClkInit->PLLI2S.PLLI2SN));

    __HAL_RCC_PLLI2S_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == (RCC_PERIPHCLK_I2S))
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SR);
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLI2S) == (RCC_PERIPHCLK_SAI_PLLI2S))
    {

      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));
      assert_param(IS_RCC_PLLI2S_DIVQ_VALUE(PeriphClkInit->PLLI2SDivQ));

      tmpreg1 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);

      __HAL_RCC_PLLI2S_SAICLK_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ, tmpreg1);

      __HAL_RCC_PLLI2S_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLI2SDivQ);
    }

    if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S)
    {

      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));
      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      __HAL_RCC_PLLI2S_SAICLK_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ,
                                     PeriphClkInit->PLLI2S.PLLI2SR);
    }

    __HAL_RCC_PLLI2S_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLSAI) == RCC_PERIPHCLK_SAI_PLLSAI) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LTDC) == RCC_PERIPHCLK_LTDC)             ||
      ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)          &&
       (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLSAIP)))
  {

    assert_param(IS_RCC_PLLSAIN_VALUE(PeriphClkInit->PLLSAI.PLLSAIN));

    __HAL_RCC_PLLSAI_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLSAI) == (RCC_PERIPHCLK_SAI_PLLSAI))
    {
      assert_param(IS_RCC_PLLSAIQ_VALUE(PeriphClkInit->PLLSAI.PLLSAIQ));
      assert_param(IS_RCC_PLLSAI_DIVQ_VALUE(PeriphClkInit->PLLSAIDivQ));

      pllsaip = ((((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >> RCC_PLLSAICFGR_PLLSAIP_Pos) + 1U) << 1U);

      pllsair = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> RCC_PLLSAICFGR_PLLSAIR_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIN, pllsaip, PeriphClkInit->PLLSAI.PLLSAIQ, pllsair);

      __HAL_RCC_PLLSAI_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLSAIDivQ);
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LTDC) == (RCC_PERIPHCLK_LTDC))
    {
      assert_param(IS_RCC_PLLSAIR_VALUE(PeriphClkInit->PLLSAI.PLLSAIR));
      assert_param(IS_RCC_PLLSAI_DIVR_VALUE(PeriphClkInit->PLLSAIDivR));

      pllsaip = ((((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIP) >> RCC_PLLSAICFGR_PLLSAIP_Pos) + 1U) << 1U);

      pllsaiq = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIN, pllsaip, pllsaiq, PeriphClkInit->PLLSAI.PLLSAIR);

      __HAL_RCC_PLLSAI_PLLSAICLKDIVR_CONFIG(PeriphClkInit->PLLSAIDivR);
    }

    if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == (RCC_PERIPHCLK_CLK48)) &&
        (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLSAIP))
    {
      assert_param(IS_RCC_PLLSAIP_VALUE(PeriphClkInit->PLLSAI.PLLSAIP));

      pllsaiq = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

      pllsair = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> RCC_PLLSAICFGR_PLLSAIR_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIN, PeriphClkInit->PLLSAI.PLLSAIP, pllsaiq, pllsair);
    }

    __HAL_RCC_PLLSAI_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {
    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }
  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S        | RCC_PERIPHCLK_SAI_PLLSAI | \
                                        RCC_PERIPHCLK_SAI_PLLI2S | RCC_PERIPHCLK_LTDC       | \
                                        RCC_PERIPHCLK_TIM        | RCC_PERIPHCLK_RTC        | \
                                        RCC_PERIPHCLK_CLK48       | RCC_PERIPHCLK_SDIO;

  PeriphClkInit->PLLI2S.PLLI2SN = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> RCC_PLLI2SCFGR_PLLI2SN_Pos);
  PeriphClkInit->PLLI2S.PLLI2SR = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);
  PeriphClkInit->PLLI2S.PLLI2SQ = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);

  PeriphClkInit->PLLSAI.PLLSAIN = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIN) >> RCC_PLLSAICFGR_PLLSAIN_Pos);
  PeriphClkInit->PLLSAI.PLLSAIR = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> RCC_PLLSAICFGR_PLLSAIR_Pos);
  PeriphClkInit->PLLSAI.PLLSAIQ = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

  PeriphClkInit->PLLI2SDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLI2SDIVQ) >> RCC_DCKCFGR_PLLI2SDIVQ_Pos);
  PeriphClkInit->PLLSAIDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVQ) >> RCC_DCKCFGR_PLLSAIDIVQ_Pos);
  PeriphClkInit->PLLSAIDivR = (uint32_t)(RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVR);

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

  PeriphClkInit->Clk48ClockSelection = __HAL_RCC_GET_CLK48_SOURCE();

  PeriphClkInit->SdioClockSelection = __HAL_RCC_GET_SDIO_SOURCE();

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }
}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_I2S:
    {

      srcclk = __HAL_RCC_GET_I2S_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SCLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SCLKSOURCE_PLLI2S:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;
#if defined(STM32F413xx) || defined(STM32F423xx)
  uint32_t plli2sq = 0U;
#endif
  uint32_t plli2sused = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB1) == (RCC_PERIPHCLK_I2S_APB1))
  {

    assert_param(IS_RCC_I2SAPB1CLKSOURCE(PeriphClkInit->I2sApb1ClockSelection));

    __HAL_RCC_I2S_APB1_CONFIG(PeriphClkInit->I2sApb1ClockSelection);

    if (PeriphClkInit->I2sApb1ClockSelection == RCC_I2SAPB1CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB2) == (RCC_PERIPHCLK_I2S_APB2))
  {

    assert_param(IS_RCC_I2SAPB2CLKSOURCE(PeriphClkInit->I2sApb2ClockSelection));

    __HAL_RCC_I2S_APB2_CONFIG(PeriphClkInit->I2sApb2ClockSelection);

    if (PeriphClkInit->I2sApb2ClockSelection == RCC_I2SAPB2CLKSOURCE_PLLI2S)
    {
      plli2sused = 1U;
    }
  }

#if defined(STM32F413xx) || defined(STM32F423xx)

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAIA) == (RCC_PERIPHCLK_SAIA))
  {

    assert_param(IS_RCC_SAIACLKSOURCE(PeriphClkInit->SaiAClockSelection));

    __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(PeriphClkInit->SaiAClockSelection);

    if (PeriphClkInit->SaiAClockSelection == RCC_SAIACLKSOURCE_PLLI2SR)
    {
      plli2sused = 1U;
    }

    if (PeriphClkInit->SaiAClockSelection == RCC_SAIACLKSOURCE_PLLR)
    {

      assert_param(IS_RCC_PLL_DIVR_VALUE(PeriphClkInit->PLLDivR));

      __HAL_RCC_PLL_PLLSAICLKDIVR_CONFIG(PeriphClkInit->PLLDivR);
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAIB) == (RCC_PERIPHCLK_SAIB))
  {

    assert_param(IS_RCC_SAIBCLKSOURCE(PeriphClkInit->SaiBClockSelection));

    __HAL_RCC_SAI_BLOCKBCLKSOURCE_CONFIG(PeriphClkInit->SaiBClockSelection);

    if (PeriphClkInit->SaiBClockSelection == RCC_SAIBCLKSOURCE_PLLI2SR)
    {
      plli2sused = 1U;
    }

    if (PeriphClkInit->SaiBClockSelection == RCC_SAIBCLKSOURCE_PLLR)
    {

      assert_param(IS_RCC_PLL_DIVR_VALUE(PeriphClkInit->PLLDivR));

      __HAL_RCC_PLL_PLLSAICLKDIVR_CONFIG(PeriphClkInit->PLLDivR);
    }
  }

#endif

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {

    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FMPI2C1) == RCC_PERIPHCLK_FMPI2C1)
  {

    assert_param(IS_RCC_FMPI2C1CLKSOURCE(PeriphClkInit->Fmpi2c1ClockSelection));

    __HAL_RCC_FMPI2C1_CONFIG(PeriphClkInit->Fmpi2c1ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48)
  {

    assert_param(IS_RCC_CLK48CLKSOURCE(PeriphClkInit->Clk48ClockSelection));

    __HAL_RCC_CLK48_CONFIG(PeriphClkInit->Clk48ClockSelection);

    if (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLI2SQ)
    {
      plli2sused = 1U;
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDIO) == RCC_PERIPHCLK_SDIO)
  {

    assert_param(IS_RCC_SDIOCLKSOURCE(PeriphClkInit->SdioClockSelection));

    __HAL_RCC_SDIO_CONFIG(PeriphClkInit->SdioClockSelection);
  }

  if ((plli2sused == 1U) || (PeriphClkInit->PeriphClockSelection == RCC_PERIPHCLK_PLLI2S))
  {

    __HAL_RCC_PLLI2S_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    assert_param(IS_RCC_PLLI2SCLKSOURCE(PeriphClkInit->PLLI2SSelection));
    assert_param(IS_RCC_PLLI2SM_VALUE(PeriphClkInit->PLLI2S.PLLI2SM));
    assert_param(IS_RCC_PLLI2SN_VALUE(PeriphClkInit->PLLI2S.PLLI2SN));

    __HAL_RCC_PLL_I2S_CONFIG(PeriphClkInit->PLLI2SSelection);

    if (((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB1) == RCC_PERIPHCLK_I2S_APB1)
         && (PeriphClkInit->I2sApb1ClockSelection == RCC_I2SAPB1CLKSOURCE_PLLI2S)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S_APB2) == RCC_PERIPHCLK_I2S_APB2) && (PeriphClkInit->I2sApb2ClockSelection == RCC_I2SAPB2CLKSOURCE_PLLI2S)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_CLK48) == RCC_PERIPHCLK_CLK48) && (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLI2SQ)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SDIO) == RCC_PERIPHCLK_SDIO) && (PeriphClkInit->SdioClockSelection == RCC_SDIOCLKSOURCE_CLK48) && (PeriphClkInit->Clk48ClockSelection == RCC_CLK48CLKSOURCE_PLLI2SQ)))
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));
      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ,
                              PeriphClkInit->PLLI2S.PLLI2SR);
    }

#if defined(STM32F413xx) || defined(STM32F423xx)

    if (((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAIA) == RCC_PERIPHCLK_SAIA)
         && (PeriphClkInit->SaiAClockSelection == RCC_SAIACLKSOURCE_PLLI2SR)) ||
        ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAIB) == RCC_PERIPHCLK_SAIB) && (PeriphClkInit->SaiBClockSelection == RCC_SAIBCLKSOURCE_PLLI2SR)))
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      assert_param(IS_RCC_PLLI2S_DIVR_VALUE(PeriphClkInit->PLLI2SDivR));

      plli2sq = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, plli2sq,
                              PeriphClkInit->PLLI2S.PLLI2SR);

      __HAL_RCC_PLLI2S_PLLSAICLKDIVR_CONFIG(PeriphClkInit->PLLI2SDivR);
    }
#endif

    if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S)
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));
      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ,
                              PeriphClkInit->PLLI2S.PLLI2SR);
    }

    __HAL_RCC_PLLI2S_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DFSDM1) == RCC_PERIPHCLK_DFSDM1)
  {

    assert_param(IS_RCC_DFSDM1CLKSOURCE(PeriphClkInit->Dfsdm1ClockSelection));

    __HAL_RCC_DFSDM1_CONFIG(PeriphClkInit->Dfsdm1ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DFSDM1_AUDIO) == RCC_PERIPHCLK_DFSDM1_AUDIO)
  {

    assert_param(IS_RCC_DFSDM1AUDIOCLKSOURCE(PeriphClkInit->Dfsdm1AudioClockSelection));

    __HAL_RCC_DFSDM1AUDIO_CONFIG(PeriphClkInit->Dfsdm1AudioClockSelection);
  }

#if defined(STM32F413xx) || defined(STM32F423xx)

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DFSDM2) == RCC_PERIPHCLK_DFSDM2)
  {

    assert_param(IS_RCC_DFSDM2CLKSOURCE(PeriphClkInit->Dfsdm2ClockSelection));

    __HAL_RCC_DFSDM2_CONFIG(PeriphClkInit->Dfsdm2ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_DFSDM2_AUDIO) == RCC_PERIPHCLK_DFSDM2_AUDIO)
  {

    assert_param(IS_RCC_DFSDM2AUDIOCLKSOURCE(PeriphClkInit->Dfsdm2AudioClockSelection));

    __HAL_RCC_DFSDM2AUDIO_CONFIG(PeriphClkInit->Dfsdm2AudioClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == RCC_PERIPHCLK_LPTIM1)
  {

    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

#endif

  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

#if defined(STM32F413xx) || defined(STM32F423xx)
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S_APB1     | RCC_PERIPHCLK_I2S_APB2 | \
                                        RCC_PERIPHCLK_TIM          | RCC_PERIPHCLK_RTC      | \
                                        RCC_PERIPHCLK_FMPI2C1      | RCC_PERIPHCLK_CLK48    | \
                                        RCC_PERIPHCLK_SDIO         | RCC_PERIPHCLK_DFSDM1   | \
                                        RCC_PERIPHCLK_DFSDM1_AUDIO | RCC_PERIPHCLK_DFSDM2   | \
                                        RCC_PERIPHCLK_DFSDM2_AUDIO | RCC_PERIPHCLK_LPTIM1   | \
                                        RCC_PERIPHCLK_SAIA         | RCC_PERIPHCLK_SAIB;
#else
  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S_APB1 | RCC_PERIPHCLK_I2S_APB2 | \
                                        RCC_PERIPHCLK_TIM      | RCC_PERIPHCLK_RTC      | \
                                        RCC_PERIPHCLK_FMPI2C1  | RCC_PERIPHCLK_CLK48    | \
                                        RCC_PERIPHCLK_SDIO     | RCC_PERIPHCLK_DFSDM1   | \
                                        RCC_PERIPHCLK_DFSDM1_AUDIO;
#endif

  PeriphClkInit->PLLI2S.PLLI2SM = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM) >> RCC_PLLI2SCFGR_PLLI2SM_Pos);
  PeriphClkInit->PLLI2S.PLLI2SN = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> RCC_PLLI2SCFGR_PLLI2SN_Pos);
  PeriphClkInit->PLLI2S.PLLI2SQ = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);
  PeriphClkInit->PLLI2S.PLLI2SR = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);
#if defined(STM32F413xx) || defined(STM32F423xx)

  PeriphClkInit->PLLI2SDivR = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLI2SDIVR) >> RCC_DCKCFGR_PLLI2SDIVR_Pos);
  PeriphClkInit->PLLDivR = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLDIVR) >> RCC_DCKCFGR_PLLDIVR_Pos);
#endif

  PeriphClkInit->I2sApb1ClockSelection = __HAL_RCC_GET_I2S_APB1_SOURCE();

  PeriphClkInit->I2sApb2ClockSelection = __HAL_RCC_GET_I2S_APB2_SOURCE();

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

  PeriphClkInit->Fmpi2c1ClockSelection = __HAL_RCC_GET_FMPI2C1_SOURCE();

  PeriphClkInit->Clk48ClockSelection = __HAL_RCC_GET_CLK48_SOURCE();

  PeriphClkInit->SdioClockSelection = __HAL_RCC_GET_SDIO_SOURCE();

  PeriphClkInit->Dfsdm1ClockSelection = __HAL_RCC_GET_DFSDM1_SOURCE();

  PeriphClkInit->Dfsdm1AudioClockSelection = __HAL_RCC_GET_DFSDM1AUDIO_SOURCE();

#if defined(STM32F413xx) || defined(STM32F423xx)

  PeriphClkInit->Dfsdm2ClockSelection = __HAL_RCC_GET_DFSDM2_SOURCE();

  PeriphClkInit->Dfsdm2AudioClockSelection = __HAL_RCC_GET_DFSDM2AUDIO_SOURCE();

  PeriphClkInit->Lptim1ClockSelection = __HAL_RCC_GET_LPTIM1_SOURCE();

  PeriphClkInit->SaiAClockSelection = __HAL_RCC_GET_SAI_BLOCKA_SOURCE();

  PeriphClkInit->SaiBClockSelection = __HAL_RCC_GET_SAI_BLOCKB_SOURCE();
#endif

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }
}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_I2S_APB1:
    {

      srcclk = __HAL_RCC_GET_I2S_APB1_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SAPB1CLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLI2S:
        {
          if ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SSRC) == RCC_PLLI2SCFGR_PLLI2SSRC)
          {

            vcoinput = (uint32_t)(EXTERNAL_CLOCK_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
            {

              vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
            }
            else
            {

              vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
            }
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLR:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U) & (RCC_PLLCFGR_PLLN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U) & (RCC_PLLCFGR_PLLR >> 28U)));
          break;
        }

        case RCC_I2SAPB1CLKSOURCE_PLLSRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {
            frequency = HSE_VALUE;
          }
          else
          {
            frequency = HSI_VALUE;
          }
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    case RCC_PERIPHCLK_I2S_APB2:
    {

      srcclk = __HAL_RCC_GET_I2S_APB2_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SAPB2CLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLI2S:
        {
          if ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SSRC) == RCC_PLLI2SCFGR_PLLI2SSRC)
          {

            vcoinput = (uint32_t)(EXTERNAL_CLOCK_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
            {

              vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
            }
            else
            {

              vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
            }
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLR:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U) & (RCC_PLLCFGR_PLLN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U) & (RCC_PLLCFGR_PLLR >> 28U)));
          break;
        }

        case RCC_I2SAPB2CLKSOURCE_PLLSRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {
            frequency = HSE_VALUE;
          }
          else
          {
            frequency = HSI_VALUE;
          }
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {
    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_FMPI2C1) == RCC_PERIPHCLK_FMPI2C1)
  {

    assert_param(IS_RCC_FMPI2C1CLKSOURCE(PeriphClkInit->Fmpi2c1ClockSelection));

    __HAL_RCC_FMPI2C1_CONFIG(PeriphClkInit->Fmpi2c1ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LPTIM1) == RCC_PERIPHCLK_LPTIM1)
  {

    assert_param(IS_RCC_LPTIM1CLKSOURCE(PeriphClkInit->Lptim1ClockSelection));

    __HAL_RCC_LPTIM1_CONFIG(PeriphClkInit->Lptim1ClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S)
  {

    assert_param(IS_RCC_I2SAPBCLKSOURCE(PeriphClkInit->I2SClockSelection));

    __HAL_RCC_I2S_CONFIG(PeriphClkInit->I2SClockSelection);
  }

  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_FMPI2C1 | RCC_PERIPHCLK_LPTIM1 | RCC_PERIPHCLK_TIM | RCC_PERIPHCLK_RTC;

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }

  PeriphClkInit->Fmpi2c1ClockSelection = __HAL_RCC_GET_FMPI2C1_SOURCE();

  PeriphClkInit->I2SClockSelection = __HAL_RCC_GET_I2S_SOURCE();

}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_I2S:
    {

      srcclk = __HAL_RCC_GET_I2S_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SAPBCLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SAPBCLKSOURCE_PLLR:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6U) & (RCC_PLLCFGR_PLLN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 28U) & (RCC_PLLCFGR_PLLR >> 28U)));
          break;
        }

        case RCC_I2SAPBCLKSOURCE_PLLSRC:
        {
          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {
            frequency = HSE_VALUE;
          }
          else
          {
            frequency = HSI_VALUE;
          }
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLI2S) == RCC_PERIPHCLK_SAI_PLLI2S) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S))
  {

    assert_param(IS_RCC_PLLI2SN_VALUE(PeriphClkInit->PLLI2S.PLLI2SN));

    __HAL_RCC_PLLI2S_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == (RCC_PERIPHCLK_I2S))
    {

      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SR);
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLI2S) == (RCC_PERIPHCLK_SAI_PLLI2S))
    {

      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));
      assert_param(IS_RCC_PLLI2S_DIVQ_VALUE(PeriphClkInit->PLLI2SDivQ));

      tmpreg1 = ((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);

      __HAL_RCC_PLLI2S_SAICLK_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ, tmpreg1);

      __HAL_RCC_PLLI2S_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLI2SDivQ);
    }

    if ((PeriphClkInit->PeriphClockSelection & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S)
    {

      assert_param(IS_RCC_PLLI2SQ_VALUE(PeriphClkInit->PLLI2S.PLLI2SQ));
      assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));

      __HAL_RCC_PLLI2S_SAICLK_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SQ,
                                     PeriphClkInit->PLLI2S.PLLI2SR);
    }

    __HAL_RCC_PLLI2S_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLSAI) == RCC_PERIPHCLK_SAI_PLLSAI) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LTDC) == RCC_PERIPHCLK_LTDC))
  {

    assert_param(IS_RCC_PLLSAIN_VALUE(PeriphClkInit->PLLSAI.PLLSAIN));

    __HAL_RCC_PLLSAI_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_SAI_PLLSAI) == (RCC_PERIPHCLK_SAI_PLLSAI))
    {
      assert_param(IS_RCC_PLLSAIQ_VALUE(PeriphClkInit->PLLSAI.PLLSAIQ));
      assert_param(IS_RCC_PLLSAI_DIVQ_VALUE(PeriphClkInit->PLLSAIDivQ));

      tmpreg1 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> RCC_PLLSAICFGR_PLLSAIR_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIN, PeriphClkInit->PLLSAI.PLLSAIQ, tmpreg1);

      __HAL_RCC_PLLSAI_PLLSAICLKDIVQ_CONFIG(PeriphClkInit->PLLSAIDivQ);
    }

    if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_LTDC) == (RCC_PERIPHCLK_LTDC))
    {
      assert_param(IS_RCC_PLLSAIR_VALUE(PeriphClkInit->PLLSAI.PLLSAIR));
      assert_param(IS_RCC_PLLSAI_DIVR_VALUE(PeriphClkInit->PLLSAIDivR));

      tmpreg1 = ((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

      __HAL_RCC_PLLSAI_CONFIG(PeriphClkInit->PLLSAI.PLLSAIN, tmpreg1, PeriphClkInit->PLLSAI.PLLSAIR);

      __HAL_RCC_PLLSAI_PLLSAICLKDIVR_CONFIG(PeriphClkInit->PLLSAIDivR);
    }

    __HAL_RCC_PLLSAI_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_PLLSAI_GET_FLAG() == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {
    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }
  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S | RCC_PERIPHCLK_SAI_PLLSAI | RCC_PERIPHCLK_SAI_PLLI2S | RCC_PERIPHCLK_LTDC | RCC_PERIPHCLK_TIM | RCC_PERIPHCLK_RTC;

  PeriphClkInit->PLLI2S.PLLI2SN = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> RCC_PLLI2SCFGR_PLLI2SN_Pos);
  PeriphClkInit->PLLI2S.PLLI2SR = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);
  PeriphClkInit->PLLI2S.PLLI2SQ = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SQ) >> RCC_PLLI2SCFGR_PLLI2SQ_Pos);

  PeriphClkInit->PLLSAI.PLLSAIN = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIN) >> RCC_PLLSAICFGR_PLLSAIN_Pos);
  PeriphClkInit->PLLSAI.PLLSAIR = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> RCC_PLLSAICFGR_PLLSAIR_Pos);
  PeriphClkInit->PLLSAI.PLLSAIQ = (uint32_t)((RCC->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> RCC_PLLSAICFGR_PLLSAIQ_Pos);

  PeriphClkInit->PLLI2SDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLI2SDIVQ) >> RCC_DCKCFGR_PLLI2SDIVQ_Pos);
  PeriphClkInit->PLLSAIDivQ = (uint32_t)((RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVQ) >> RCC_DCKCFGR_PLLSAIDIVQ_Pos);
  PeriphClkInit->PLLSAIDivR = (uint32_t)(RCC->DCKCFGR & RCC_DCKCFGR_PLLSAIDIVR);

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }
}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_I2S:
    {

      srcclk = __HAL_RCC_GET_I2S_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SCLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SCLKSOURCE_PLLI2S:
        {

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tickstart = 0U;
  uint32_t tmpreg1 = 0U;

  assert_param(IS_RCC_PERIPHCLOCK(PeriphClkInit->PeriphClockSelection));

  if ((((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_I2S) == RCC_PERIPHCLK_I2S) ||
      (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_PLLI2S) == RCC_PERIPHCLK_PLLI2S))
  {

    assert_param(IS_RCC_PLLI2SR_VALUE(PeriphClkInit->PLLI2S.PLLI2SR));
    assert_param(IS_RCC_PLLI2SN_VALUE(PeriphClkInit->PLLI2S.PLLI2SN));
#if defined(STM32F411xE)
    assert_param(IS_RCC_PLLI2SM_VALUE(PeriphClkInit->PLLI2S.PLLI2SM));
#endif

    __HAL_RCC_PLLI2S_DISABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }

#if defined(STM32F411xE)

    __HAL_RCC_PLLI2S_I2SCLK_CONFIG(PeriphClkInit->PLLI2S.PLLI2SM, PeriphClkInit->PLLI2S.PLLI2SN,
                                   PeriphClkInit->PLLI2S.PLLI2SR);
#else

    __HAL_RCC_PLLI2S_CONFIG(PeriphClkInit->PLLI2S.PLLI2SN, PeriphClkInit->PLLI2S.PLLI2SR);
#endif

    __HAL_RCC_PLLI2S_ENABLE();

    tickstart = HAL_GetTick();

    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)
    {
      if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
      {

        return HAL_TIMEOUT;
      }
    }
  }

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_RTC) == (RCC_PERIPHCLK_RTC))
  {

    assert_param(IS_RCC_RTCCLKSOURCE(PeriphClkInit->RTCClockSelection));

    __HAL_RCC_PWR_CLK_ENABLE();

    PWR->CR |= PWR_CR_DBP;

    tickstart = HAL_GetTick();

    while ((PWR->CR & PWR_CR_DBP) == RESET)
    {
      if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
      {
        return HAL_TIMEOUT;
      }
    }

    tmpreg1 = (RCC->BDCR & RCC_BDCR_RTCSEL);
    if ((tmpreg1 != 0x00000000U) && ((tmpreg1) != (PeriphClkInit->RTCClockSelection & RCC_BDCR_RTCSEL)))
    {

      tmpreg1 = (RCC->BDCR & ~(RCC_BDCR_RTCSEL));

      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();

      RCC->BDCR = tmpreg1;

      if (HAL_IS_BIT_SET(RCC->BDCR, RCC_BDCR_LSEON))
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    __HAL_RCC_RTC_CONFIG(PeriphClkInit->RTCClockSelection);
  }
#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)

  if (((PeriphClkInit->PeriphClockSelection) & RCC_PERIPHCLK_TIM) == (RCC_PERIPHCLK_TIM))
  {
    __HAL_RCC_TIMCLKPRESCALER(PeriphClkInit->TIMPresSelection);
  }
#endif
  return HAL_OK;
}

void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit)
{
  uint32_t tempreg;

  PeriphClkInit->PeriphClockSelection = RCC_PERIPHCLK_I2S | RCC_PERIPHCLK_RTC;

  PeriphClkInit->PLLI2S.PLLI2SN = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> RCC_PLLI2SCFGR_PLLI2SN_Pos);
  PeriphClkInit->PLLI2S.PLLI2SR = (uint32_t)((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> RCC_PLLI2SCFGR_PLLI2SR_Pos);
#if defined(STM32F411xE)
  PeriphClkInit->PLLI2S.PLLI2SM = (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM);
#endif

  tempreg = (RCC->CFGR & RCC_CFGR_RTCPRE);
  PeriphClkInit->RTCClockSelection = (uint32_t)((tempreg) | (RCC->BDCR & RCC_BDCR_RTCSEL));

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)

  if ((RCC->DCKCFGR & RCC_DCKCFGR_TIMPRE) == RESET)
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_DESACTIVATED;
  }
  else
  {
    PeriphClkInit->TIMPresSelection = RCC_TIMPRES_ACTIVATED;
  }
#endif
}

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk)
{

  uint32_t frequency = 0U;

  uint32_t vcoinput = 0U;
  uint32_t srcclk = 0U;

  uint32_t vcooutput = 0U;
  switch (PeriphClk)
  {
    case RCC_PERIPHCLK_I2S:
    {

      srcclk = __HAL_RCC_GET_I2S_SOURCE();
      switch (srcclk)
      {

        case RCC_I2SCLKSOURCE_EXT:
        {

          frequency = EXTERNAL_CLOCK_VALUE;
          break;
        }

        case RCC_I2SCLKSOURCE_PLLI2S:
        {
#if defined(STM32F411xE)

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SM));
          }
#else

          if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLSOURCE_HSE)
          {

            vcoinput = (uint32_t)(HSE_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
          else
          {

            vcoinput = (uint32_t)(HSI_VALUE / (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM));
          }
#endif

          vcooutput = (uint32_t)(vcoinput * (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6U) & (RCC_PLLI2SCFGR_PLLI2SN >> 6U)));

          frequency = (uint32_t)(vcooutput / (((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28U) & (RCC_PLLI2SCFGR_PLLI2SR >> 28U)));
          break;
        }

        default:
        {
          frequency = 0U;
          break;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return frequency;
}
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

void HAL_RCCEx_SelectLSEMode(uint8_t Mode)
{

  assert_param(IS_RCC_LSE_MODE(Mode));
  if (Mode == RCC_LSE_HIGHDRIVE_MODE)
  {
    SET_BIT(RCC->BDCR, RCC_BDCR_LSEMOD);
  }
  else
  {
    CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEMOD);
  }
}

#endif

#if defined(RCC_PLLI2S_SUPPORT)

HAL_StatusTypeDef HAL_RCCEx_EnablePLLI2S(RCC_PLLI2SInitTypeDef  *PLLI2SInit)
{
  uint32_t tickstart;

  assert_param(IS_RCC_PLLI2SN_VALUE(PLLI2SInit->PLLI2SN));
  assert_param(IS_RCC_PLLI2SR_VALUE(PLLI2SInit->PLLI2SR));
#if defined(RCC_PLLI2SCFGR_PLLI2SM)
  assert_param(IS_RCC_PLLI2SM_VALUE(PLLI2SInit->PLLI2SM));
#endif
#if defined(RCC_PLLI2SCFGR_PLLI2SP)
  assert_param(IS_RCC_PLLI2SP_VALUE(PLLI2SInit->PLLI2SP));
#endif
#if defined(RCC_PLLI2SCFGR_PLLI2SQ)
  assert_param(IS_RCC_PLLI2SQ_VALUE(PLLI2SInit->PLLI2SQ));
#endif

  __HAL_RCC_PLLI2S_DISABLE();

  tickstart = HAL_GetTick();
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

#if defined(STM32F446xx)

  __HAL_RCC_PLLI2S_CONFIG(PLLI2SInit->PLLI2SM, PLLI2SInit->PLLI2SN, \
                          PLLI2SInit->PLLI2SP, PLLI2SInit->PLLI2SQ, PLLI2SInit->PLLI2SR);
#elif defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
      defined(STM32F413xx) || defined(STM32F423xx)

  __HAL_RCC_PLLI2S_CONFIG(PLLI2SInit->PLLI2SM, PLLI2SInit->PLLI2SN, \
                          PLLI2SInit->PLLI2SQ, PLLI2SInit->PLLI2SR);
#elif defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
      defined(STM32F469xx) || defined(STM32F479xx)

  __HAL_RCC_PLLI2S_SAICLK_CONFIG(PLLI2SInit->PLLI2SN, PLLI2SInit->PLLI2SQ, PLLI2SInit->PLLI2SR);
#elif defined(STM32F411xE)

  __HAL_RCC_PLLI2S_I2SCLK_CONFIG(PLLI2SInit->PLLI2SM, PLLI2SInit->PLLI2SN, PLLI2SInit->PLLI2SR);
#else

  __HAL_RCC_PLLI2S_CONFIG(PLLI2SInit->PLLI2SN, PLLI2SInit->PLLI2SR);
#endif

  __HAL_RCC_PLLI2S_ENABLE();

  tickstart = HAL_GetTick();
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY) == RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_RCCEx_DisablePLLI2S(void)
{
  uint32_t tickstart;

  __HAL_RCC_PLLI2S_DISABLE();

  tickstart = HAL_GetTick();
  while (READ_BIT(RCC->CR, RCC_CR_PLLI2SRDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

#endif

#if defined(RCC_PLLSAI_SUPPORT)

HAL_StatusTypeDef HAL_RCCEx_EnablePLLSAI(RCC_PLLSAIInitTypeDef  *PLLSAIInit)
{
  uint32_t tickstart;

  assert_param(IS_RCC_PLLSAIN_VALUE(PLLSAIInit->PLLSAIN));
  assert_param(IS_RCC_PLLSAIQ_VALUE(PLLSAIInit->PLLSAIQ));
#if defined(RCC_PLLSAICFGR_PLLSAIM)
  assert_param(IS_RCC_PLLSAIM_VALUE(PLLSAIInit->PLLSAIM));
#endif
#if defined(RCC_PLLSAICFGR_PLLSAIP)
  assert_param(IS_RCC_PLLSAIP_VALUE(PLLSAIInit->PLLSAIP));
#endif
#if defined(RCC_PLLSAICFGR_PLLSAIR)
  assert_param(IS_RCC_PLLSAIR_VALUE(PLLSAIInit->PLLSAIR));
#endif

  __HAL_RCC_PLLSAI_DISABLE();

  tickstart = HAL_GetTick();
  while (__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

#if defined(STM32F446xx)

  __HAL_RCC_PLLSAI_CONFIG(PLLSAIInit->PLLSAIM, PLLSAIInit->PLLSAIN, \
                          PLLSAIInit->PLLSAIP, PLLSAIInit->PLLSAIQ, 0U);
#elif defined(STM32F469xx) || defined(STM32F479xx)

  __HAL_RCC_PLLSAI_CONFIG(PLLSAIInit->PLLSAIN, PLLSAIInit->PLLSAIP, \
                          PLLSAIInit->PLLSAIQ, PLLSAIInit->PLLSAIR);
#else

  __HAL_RCC_PLLSAI_CONFIG(PLLSAIInit->PLLSAIN, PLLSAIInit->PLLSAIQ, PLLSAIInit->PLLSAIR);
#endif

  __HAL_RCC_PLLSAI_ENABLE();

  tickstart = HAL_GetTick();
  while (__HAL_RCC_PLLSAI_GET_FLAG() == RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_RCCEx_DisablePLLSAI(void)
{
  uint32_t tickstart;

  __HAL_RCC_PLLSAI_DISABLE();

  tickstart = HAL_GetTick();
  while (__HAL_RCC_PLLSAI_GET_FLAG() != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
    {

      return HAL_TIMEOUT;
    }
  }

  return HAL_OK;
}

#endif

#if defined(STM32F446xx)

uint32_t HAL_RCC_GetSysClockFreq(void)
{
  uint32_t pllm = 0U;
  uint32_t pllvco = 0U;
  uint32_t pllp = 0U;
  uint32_t pllr = 0U;
  uint32_t sysclockfreq = 0U;

  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_CFGR_SWS_HSI:
    {
      sysclockfreq = HSI_VALUE;
      break;
    }
    case RCC_CFGR_SWS_HSE:
    {
      sysclockfreq = HSE_VALUE;
      break;
    }
    case RCC_CFGR_SWS_PLL:
    {

      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      if (__HAL_RCC_GET_PLL_OSCSOURCE() != RCC_PLLSOURCE_HSI)
      {

        pllvco = (uint32_t)((((uint64_t) HSE_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      else
      {

        pllvco = (uint32_t)((((uint64_t) HSI_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      pllp = ((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> RCC_PLLCFGR_PLLP_Pos) + 1U) * 2U);

      sysclockfreq = pllvco / pllp;
      break;
    }
    case RCC_CFGR_SWS_PLLR:
    {

      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
      if (__HAL_RCC_GET_PLL_OSCSOURCE() != RCC_PLLSOURCE_HSI)
      {

        pllvco = (uint32_t)((((uint64_t) HSE_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      else
      {

        pllvco = (uint32_t)((((uint64_t) HSI_VALUE * ((uint64_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos)))) / (uint64_t)pllm);
      }
      pllr = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos);

      sysclockfreq = pllvco / pllr;
      break;
    }
    default:
    {
      sysclockfreq = HSI_VALUE;
      break;
    }
  }
  return sysclockfreq;
}
#endif

HAL_StatusTypeDef HAL_RCC_DeInit(void)
{
  uint32_t tickstart;

  tickstart = HAL_GetTick();

  SET_BIT(RCC->CR, RCC_CR_HSION);

  while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET)
  {
    if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  SET_BIT(RCC->CR, RCC_CR_HSITRIM_4);

  tickstart = HAL_GetTick();

  CLEAR_REG(RCC->CFGR);

  while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > CLOCKSWITCH_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  tickstart = HAL_GetTick();

  CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_CSSON);

  while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

  tickstart = HAL_GetTick();

  CLEAR_BIT(RCC->CR, RCC_CR_PLLON);

  while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }

#if defined(RCC_PLLI2S_SUPPORT)

  tickstart = HAL_GetTick();

  CLEAR_BIT(RCC->CR, RCC_CR_PLLI2SON);

  while (READ_BIT(RCC->CR, RCC_CR_PLLI2SRDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLI2S_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
#endif

#if defined(RCC_PLLSAI_SUPPORT)

  tickstart = HAL_GetTick();

  CLEAR_BIT(RCC->CR, RCC_CR_PLLSAION);

  while (READ_BIT(RCC->CR, RCC_CR_PLLSAIRDY) != RESET)
  {
    if ((HAL_GetTick() - tickstart) > PLLSAI_TIMEOUT_VALUE)
    {
      return HAL_TIMEOUT;
    }
  }
#endif

#if defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || \
    defined(STM32F423xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
  RCC->PLLCFGR = RCC_PLLCFGR_PLLM_4 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLR_1;
#elif defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
  RCC->PLLCFGR = RCC_PLLCFGR_PLLR_0 | RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLR_2 | RCC_PLLCFGR_PLLM_4 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_3;
#else
  RCC->PLLCFGR = RCC_PLLCFGR_PLLM_4 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLQ_2;
#endif

#if defined(STM32F412Cx) || defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || \
    defined(STM32F423xx) || defined(STM32F446xx)
  RCC->PLLI2SCFGR = RCC_PLLI2SCFGR_PLLI2SM_4 | RCC_PLLI2SCFGR_PLLI2SN_6 | RCC_PLLI2SCFGR_PLLI2SN_7 | RCC_PLLI2SCFGR_PLLI2SQ_2 | RCC_PLLI2SCFGR_PLLI2SR_1;
#elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)
  RCC->PLLI2SCFGR = RCC_PLLI2SCFGR_PLLI2SN_6 | RCC_PLLI2SCFGR_PLLI2SN_7 | RCC_PLLI2SCFGR_PLLI2SR_1;
#elif defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  RCC->PLLI2SCFGR = RCC_PLLI2SCFGR_PLLI2SN_6 | RCC_PLLI2SCFGR_PLLI2SN_7 | RCC_PLLI2SCFGR_PLLI2SQ_2 | RCC_PLLI2SCFGR_PLLI2SR_1;
#elif defined(STM32F411xE)
  RCC->PLLI2SCFGR = RCC_PLLI2SCFGR_PLLI2SM_4 | RCC_PLLI2SCFGR_PLLI2SN_6 | RCC_PLLI2SCFGR_PLLI2SN_7 | RCC_PLLI2SCFGR_PLLI2SR_1;
#endif

#if defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIN_6 | RCC_PLLSAICFGR_PLLSAIN_7 | RCC_PLLSAICFGR_PLLSAIQ_2 | RCC_PLLSAICFGR_PLLSAIR_1;
#elif defined(STM32F446xx)
  RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIM_4 | RCC_PLLSAICFGR_PLLSAIN_6 | RCC_PLLSAICFGR_PLLSAIN_7 | RCC_PLLSAICFGR_PLLSAIQ_2;
#endif

  CLEAR_BIT(RCC->CIR, RCC_CIR_LSIRDYIE | RCC_CIR_LSERDYIE | RCC_CIR_HSIRDYIE | RCC_CIR_HSERDYIE | RCC_CIR_PLLRDYIE);

#if defined(RCC_CIR_PLLI2SRDYIE)
  CLEAR_BIT(RCC->CIR, RCC_CIR_PLLI2SRDYIE);
#endif

#if defined(RCC_CIR_PLLSAIRDYIE)
  CLEAR_BIT(RCC->CIR, RCC_CIR_PLLSAIRDYIE);
#endif

  SET_BIT(RCC->CIR, RCC_CIR_LSIRDYC | RCC_CIR_LSERDYC | RCC_CIR_HSIRDYC | RCC_CIR_HSERDYC | RCC_CIR_PLLRDYC |
          RCC_CIR_CSSC);

#if defined(RCC_CIR_PLLI2SRDYC)
  SET_BIT(RCC->CIR, RCC_CIR_PLLI2SRDYC);
#endif

#if defined(RCC_CIR_PLLSAIRDYC)
  SET_BIT(RCC->CIR, RCC_CIR_PLLSAIRDYC);
#endif

  CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);

  SET_BIT(RCC->CSR, RCC_CSR_RMVF);

  SystemCoreClock = HSI_VALUE;

  if (HAL_InitTick(uwTickPrio) != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;
  }
}

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
  uint32_t tickstart;
  uint32_t pll_config;

  if (RCC_OscInitStruct == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_RCC_OSCILLATORTYPE(RCC_OscInitStruct->OscillatorType));

  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE)
  {

    assert_param(IS_RCC_HSE(RCC_OscInitStruct->HSEState));

#if defined(STM32F446xx)
    if ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_HSE)
        || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLL) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE)) || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLLR) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE)))
#else
    if ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_HSE)
        || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLL) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE)))
#endif
    {
      if ((__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET) && (RCC_OscInitStruct->HSEState == RCC_HSE_OFF))
      {
        return HAL_ERROR;
      }
    }
    else
    {

      __HAL_RCC_HSE_CONFIG(RCC_OscInitStruct->HSEState);

      if ((RCC_OscInitStruct->HSEState) != RCC_HSE_OFF)
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSE_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI)
  {

    assert_param(IS_RCC_HSI(RCC_OscInitStruct->HSIState));
    assert_param(IS_RCC_CALIBRATION_VALUE(RCC_OscInitStruct->HSICalibrationValue));

#if defined(STM32F446xx)
    if ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_HSI)
        || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLL) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI)) || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLLR) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI)))
#else
    if ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_HSI)
        || \
        ((__HAL_RCC_GET_SYSCLK_SOURCE() == RCC_CFGR_SWS_PLL) && ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI)))
#endif
    {

      if ((__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET) && (RCC_OscInitStruct->HSIState != RCC_HSI_ON))
      {
        return HAL_ERROR;
      }

      else
      {

        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
    }
    else
    {

      if ((RCC_OscInitStruct->HSIState) != RCC_HSI_OFF)
      {

        __HAL_RCC_HSI_ENABLE();

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);
      }
      else
      {

        __HAL_RCC_HSI_DISABLE();

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > HSI_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
  }

  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI)
  {

    assert_param(IS_RCC_LSI(RCC_OscInitStruct->LSIState));

    if ((RCC_OscInitStruct->LSIState) != RCC_LSI_OFF)
    {

      __HAL_RCC_LSI_ENABLE();

      tickstart = HAL_GetTick();

      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {

      __HAL_RCC_LSI_DISABLE();

      tickstart = HAL_GetTick();

      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) != RESET)
      {
        if ((HAL_GetTick() - tickstart) > LSI_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
  }

  if (((RCC_OscInitStruct->OscillatorType) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE)
  {
    FlagStatus       pwrclkchanged = RESET;

    assert_param(IS_RCC_LSE(RCC_OscInitStruct->LSEState));

    if (__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      pwrclkchanged = SET;
    }

    if (HAL_IS_BIT_CLR(PWR->CR, PWR_CR_DBP))
    {

      SET_BIT(PWR->CR, PWR_CR_DBP);

      tickstart = HAL_GetTick();

      while (HAL_IS_BIT_CLR(PWR->CR, PWR_CR_DBP))
      {
        if ((HAL_GetTick() - tickstart) > RCC_DBP_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    __HAL_RCC_LSE_CONFIG(RCC_OscInitStruct->LSEState);

    if ((RCC_OscInitStruct->LSEState) != RCC_LSE_OFF)
    {

      tickstart = HAL_GetTick();

      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == RESET)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }
    else
    {

      tickstart = HAL_GetTick();

      while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) != RESET)
      {
        if ((HAL_GetTick() - tickstart) > RCC_LSE_TIMEOUT_VALUE)
        {
          return HAL_TIMEOUT;
        }
      }
    }

    if (pwrclkchanged == SET)
    {
      __HAL_RCC_PWR_CLK_DISABLE();
    }
  }

  assert_param(IS_RCC_PLL(RCC_OscInitStruct->PLL.PLLState));
  if ((RCC_OscInitStruct->PLL.PLLState) != RCC_PLL_NONE)
  {

    if (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL)
    {
      if ((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_ON)
      {

        assert_param(IS_RCC_PLLSOURCE(RCC_OscInitStruct->PLL.PLLSource));
        assert_param(IS_RCC_PLLM_VALUE(RCC_OscInitStruct->PLL.PLLM));
        assert_param(IS_RCC_PLLN_VALUE(RCC_OscInitStruct->PLL.PLLN));
        assert_param(IS_RCC_PLLP_VALUE(RCC_OscInitStruct->PLL.PLLP));
        assert_param(IS_RCC_PLLQ_VALUE(RCC_OscInitStruct->PLL.PLLQ));
        assert_param(IS_RCC_PLLR_VALUE(RCC_OscInitStruct->PLL.PLLR));

        __HAL_RCC_PLL_DISABLE();

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }

        WRITE_REG(RCC->PLLCFGR, (RCC_OscInitStruct->PLL.PLLSource                                            | \
                                 RCC_OscInitStruct->PLL.PLLM                                                 | \
                                 (RCC_OscInitStruct->PLL.PLLN << RCC_PLLCFGR_PLLN_Pos)                       | \
                                 (((RCC_OscInitStruct->PLL.PLLP >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos)        | \
                                 (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)                       | \
                                 (RCC_OscInitStruct->PLL.PLLR << RCC_PLLCFGR_PLLR_Pos)));

        __HAL_RCC_PLL_ENABLE();

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
      else
      {

        __HAL_RCC_PLL_DISABLE();

        tickstart = HAL_GetTick();

        while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET)
        {
          if ((HAL_GetTick() - tickstart) > PLL_TIMEOUT_VALUE)
          {
            return HAL_TIMEOUT;
          }
        }
      }
    }
    else
    {

      if ((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF)
      {
        return HAL_ERROR;
      }
      else
      {

        pll_config = RCC->PLLCFGR;
#if defined (RCC_PLLCFGR_PLLR)
        if (((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLM) != (RCC_OscInitStruct->PLL.PLLM) << RCC_PLLCFGR_PLLM_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLN) != (RCC_OscInitStruct->PLL.PLLN) << RCC_PLLCFGR_PLLN_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLP) != (((RCC_OscInitStruct->PLL.PLLP >> 1U) - 1U)) << RCC_PLLCFGR_PLLP_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLQ) != (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLR) != (RCC_OscInitStruct->PLL.PLLR << RCC_PLLCFGR_PLLR_Pos)))
#else
        if (((RCC_OscInitStruct->PLL.PLLState) == RCC_PLL_OFF) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLSRC) != RCC_OscInitStruct->PLL.PLLSource) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLM) != (RCC_OscInitStruct->PLL.PLLM) << RCC_PLLCFGR_PLLM_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLN) != (RCC_OscInitStruct->PLL.PLLN) << RCC_PLLCFGR_PLLN_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLP) != (((RCC_OscInitStruct->PLL.PLLP >> 1U) - 1U)) << RCC_PLLCFGR_PLLP_Pos) ||
            (READ_BIT(pll_config, RCC_PLLCFGR_PLLQ) != (RCC_OscInitStruct->PLL.PLLQ << RCC_PLLCFGR_PLLQ_Pos)))
#endif
        {
          return HAL_ERROR;
        }
      }
    }
  }
  return HAL_OK;
}

void HAL_RCC_GetOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{

  RCC_OscInitStruct->OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI;

  if ((RCC->CR & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_BYPASS;
  }
  else if ((RCC->CR & RCC_CR_HSEON) == RCC_CR_HSEON)
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_ON;
  }
  else
  {
    RCC_OscInitStruct->HSEState = RCC_HSE_OFF;
  }

  if ((RCC->CR & RCC_CR_HSION) == RCC_CR_HSION)
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_ON;
  }
  else
  {
    RCC_OscInitStruct->HSIState = RCC_HSI_OFF;
  }

  RCC_OscInitStruct->HSICalibrationValue = (uint32_t)((RCC->CR & RCC_CR_HSITRIM) >> RCC_CR_HSITRIM_Pos);

  if ((RCC->BDCR & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_BYPASS;
  }
  else if ((RCC->BDCR & RCC_BDCR_LSEON) == RCC_BDCR_LSEON)
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_ON;
  }
  else
  {
    RCC_OscInitStruct->LSEState = RCC_LSE_OFF;
  }

  if ((RCC->CSR & RCC_CSR_LSION) == RCC_CSR_LSION)
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_ON;
  }
  else
  {
    RCC_OscInitStruct->LSIState = RCC_LSI_OFF;
  }

  if ((RCC->CR & RCC_CR_PLLON) == RCC_CR_PLLON)
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_ON;
  }
  else
  {
    RCC_OscInitStruct->PLL.PLLState = RCC_PLL_OFF;
  }
  RCC_OscInitStruct->PLL.PLLSource = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
  RCC_OscInitStruct->PLL.PLLM = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM);
  RCC_OscInitStruct->PLL.PLLN = (uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> RCC_PLLCFGR_PLLN_Pos);
  RCC_OscInitStruct->PLL.PLLP = (uint32_t)((((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) + RCC_PLLCFGR_PLLP_0) << 1U) >> RCC_PLLCFGR_PLLP_Pos);
  RCC_OscInitStruct->PLL.PLLQ = (uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLQ) >> RCC_PLLCFGR_PLLQ_Pos);
  RCC_OscInitStruct->PLL.PLLR = (uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos);
}
#endif

#endif
