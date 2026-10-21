#ifndef __STM32F4xx_HAL_RCC_EX_H
#define __STM32F4xx_HAL_RCC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t PLLState;

  uint32_t PLLSource;

  uint32_t PLLM;

  uint32_t PLLN;

  uint32_t PLLP;

  uint32_t PLLQ;
#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)
  uint32_t PLLR;
#endif
} RCC_PLLInitTypeDef;

#if defined(STM32F446xx)

typedef struct
{
  uint32_t PLLI2SM;

  uint32_t PLLI2SN;

  uint32_t PLLI2SP;

  uint32_t PLLI2SQ;

  uint32_t PLLI2SR;
} RCC_PLLI2SInitTypeDef;

typedef struct
{
  uint32_t PLLSAIM;

  uint32_t PLLSAIN;

  uint32_t PLLSAIP;

  uint32_t PLLSAIQ;
} RCC_PLLSAIInitTypeDef;

typedef struct
{
  uint32_t PeriphClockSelection;

  RCC_PLLI2SInitTypeDef PLLI2S;

  RCC_PLLSAIInitTypeDef PLLSAI;

  uint32_t PLLI2SDivQ;

  uint32_t PLLSAIDivQ;

  uint32_t Sai1ClockSelection;

  uint32_t Sai2ClockSelection;

  uint32_t I2sApb1ClockSelection;

  uint32_t I2sApb2ClockSelection;

  uint32_t RTCClockSelection;

  uint32_t SdioClockSelection;

  uint32_t CecClockSelection;

  uint32_t Fmpi2c1ClockSelection;

  uint32_t SpdifClockSelection;

  uint32_t Clk48ClockSelection;

  uint8_t TIMPresSelection;
} RCC_PeriphCLKInitTypeDef;
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

typedef struct
{
  uint32_t PeriphClockSelection;

  uint32_t I2SClockSelection;

  uint32_t RTCClockSelection;

  uint32_t Lptim1ClockSelection;

  uint32_t Fmpi2c1ClockSelection;

  uint8_t TIMPresSelection;
} RCC_PeriphCLKInitTypeDef;
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

typedef struct
{
  uint32_t PLLI2SM;

  uint32_t PLLI2SN;

  uint32_t PLLI2SQ;

  uint32_t PLLI2SR;
} RCC_PLLI2SInitTypeDef;

typedef struct
{
  uint32_t PeriphClockSelection;

  RCC_PLLI2SInitTypeDef PLLI2S;

#if defined(STM32F413xx) || defined(STM32F423xx)
  uint32_t PLLDivR;

  uint32_t PLLI2SDivR;
#endif

  uint32_t I2sApb1ClockSelection;

  uint32_t I2sApb2ClockSelection;

  uint32_t RTCClockSelection;

  uint32_t SdioClockSelection;

  uint32_t Fmpi2c1ClockSelection;

  uint32_t Clk48ClockSelection;

  uint32_t Dfsdm1ClockSelection;

  uint32_t Dfsdm1AudioClockSelection;

#if defined(STM32F413xx) || defined(STM32F423xx)
  uint32_t Dfsdm2ClockSelection;

  uint32_t Dfsdm2AudioClockSelection;

  uint32_t Lptim1ClockSelection;

  uint32_t SaiAClockSelection;

  uint32_t SaiBClockSelection;
#endif

  uint32_t PLLI2SSelection;

  uint8_t TIMPresSelection;
} RCC_PeriphCLKInitTypeDef;
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

typedef struct
{
  uint32_t PLLI2SN;

  uint32_t PLLI2SR;

  uint32_t PLLI2SQ;
} RCC_PLLI2SInitTypeDef;

typedef struct
{
  uint32_t PLLSAIN;
#if defined(STM32F469xx) || defined(STM32F479xx)
  uint32_t PLLSAIP;
#endif

  uint32_t PLLSAIQ;

  uint32_t PLLSAIR;

} RCC_PLLSAIInitTypeDef;

typedef struct
{
  uint32_t PeriphClockSelection;

  RCC_PLLI2SInitTypeDef PLLI2S;

  RCC_PLLSAIInitTypeDef PLLSAI;

  uint32_t PLLI2SDivQ;

  uint32_t PLLSAIDivQ;

  uint32_t PLLSAIDivR;

  uint32_t RTCClockSelection;

  uint8_t TIMPresSelection;
#if defined(STM32F469xx) || defined(STM32F479xx)
  uint32_t Clk48ClockSelection;

  uint32_t SdioClockSelection;
#endif
} RCC_PeriphCLKInitTypeDef;

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)

typedef struct
{
#if defined(STM32F411xE)
  uint32_t PLLI2SM;
#endif

  uint32_t PLLI2SN;

  uint32_t PLLI2SR;

} RCC_PLLI2SInitTypeDef;

typedef struct
{
  uint32_t PeriphClockSelection;

  RCC_PLLI2SInitTypeDef PLLI2S;

  uint32_t RTCClockSelection;
#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
  uint8_t TIMPresSelection;
#endif
} RCC_PeriphCLKInitTypeDef;
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)
#define RCC_PERIPHCLK_I2S_APB1        0x00000001U
#define RCC_PERIPHCLK_I2S_APB2        0x00000002U
#define RCC_PERIPHCLK_TIM             0x00000004U
#define RCC_PERIPHCLK_RTC             0x00000008U
#define RCC_PERIPHCLK_FMPI2C1         0x00000010U
#define RCC_PERIPHCLK_CLK48           0x00000020U
#define RCC_PERIPHCLK_SDIO            0x00000040U
#define RCC_PERIPHCLK_PLLI2S          0x00000080U
#define RCC_PERIPHCLK_DFSDM1          0x00000100U
#define RCC_PERIPHCLK_DFSDM1_AUDIO    0x00000200U
#endif
#if defined(STM32F413xx) || defined(STM32F423xx)
#define RCC_PERIPHCLK_DFSDM2          0x00000400U
#define RCC_PERIPHCLK_DFSDM2_AUDIO    0x00000800U
#define RCC_PERIPHCLK_LPTIM1          0x00001000U
#define RCC_PERIPHCLK_SAIA            0x00002000U
#define RCC_PERIPHCLK_SAIB            0x00004000U
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define RCC_PERIPHCLK_I2S             0x00000001U
#define RCC_PERIPHCLK_TIM             0x00000002U
#define RCC_PERIPHCLK_RTC             0x00000004U
#define RCC_PERIPHCLK_FMPI2C1         0x00000008U
#define RCC_PERIPHCLK_LPTIM1          0x00000010U
#endif

#if defined(STM32F446xx)
#define RCC_PERIPHCLK_I2S_APB1        0x00000001U
#define RCC_PERIPHCLK_I2S_APB2        0x00000002U
#define RCC_PERIPHCLK_SAI1            0x00000004U
#define RCC_PERIPHCLK_SAI2            0x00000008U
#define RCC_PERIPHCLK_TIM             0x00000010U
#define RCC_PERIPHCLK_RTC             0x00000020U
#define RCC_PERIPHCLK_CEC             0x00000040U
#define RCC_PERIPHCLK_FMPI2C1         0x00000080U
#define RCC_PERIPHCLK_CLK48           0x00000100U
#define RCC_PERIPHCLK_SDIO            0x00000200U
#define RCC_PERIPHCLK_SPDIFRX         0x00000400U
#define RCC_PERIPHCLK_PLLI2S          0x00000800U
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define RCC_PERIPHCLK_I2S             0x00000001U
#define RCC_PERIPHCLK_SAI_PLLI2S      0x00000002U
#define RCC_PERIPHCLK_SAI_PLLSAI      0x00000004U
#define RCC_PERIPHCLK_LTDC            0x00000008U
#define RCC_PERIPHCLK_TIM             0x00000010U
#define RCC_PERIPHCLK_RTC             0x00000020U
#define RCC_PERIPHCLK_PLLI2S          0x00000040U
#define RCC_PERIPHCLK_CLK48           0x00000080U
#define RCC_PERIPHCLK_SDIO            0x00000100U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
#define RCC_PERIPHCLK_I2S             0x00000001U
#define RCC_PERIPHCLK_SAI_PLLI2S      0x00000002U
#define RCC_PERIPHCLK_SAI_PLLSAI      0x00000004U
#define RCC_PERIPHCLK_LTDC            0x00000008U
#define RCC_PERIPHCLK_TIM             0x00000010U
#define RCC_PERIPHCLK_RTC             0x00000020U
#define RCC_PERIPHCLK_PLLI2S          0x00000040U
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
#define RCC_PERIPHCLK_I2S             0x00000001U
#define RCC_PERIPHCLK_RTC             0x00000002U
#define RCC_PERIPHCLK_PLLI2S          0x00000004U
#endif
#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
#define RCC_PERIPHCLK_TIM             0x00000008U
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F469xx) || \
    defined(STM32F479xx)

#define RCC_I2SCLKSOURCE_PLLI2S         0x00000000U
#define RCC_I2SCLKSOURCE_EXT            RCC_CFGR_I2SSRC

#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define RCC_PLLSAIDIVR_2                0x00000000U
#define RCC_PLLSAIDIVR_4                0x00010000U
#define RCC_PLLSAIDIVR_8                0x00020000U
#define RCC_PLLSAIDIVR_16               0x00030000U
#endif

#if defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx)
#define RCC_PLLI2SP_DIV2                  0x00000002U
#define RCC_PLLI2SP_DIV4                  0x00000004U
#define RCC_PLLI2SP_DIV6                  0x00000006U
#define RCC_PLLI2SP_DIV8                  0x00000008U
#endif

#if defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define RCC_PLLSAIP_DIV2                  0x00000002U
#define RCC_PLLSAIP_DIV4                  0x00000004U
#define RCC_PLLSAIP_DIV6                  0x00000006U
#define RCC_PLLSAIP_DIV8                  0x00000008U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define RCC_SAIACLKSOURCE_PLLSAI             0x00000000U
#define RCC_SAIACLKSOURCE_PLLI2S             0x00100000U
#define RCC_SAIACLKSOURCE_EXT                0x00200000U

#define RCC_SAIBCLKSOURCE_PLLSAI             0x00000000U
#define RCC_SAIBCLKSOURCE_PLLI2S             0x00400000U
#define RCC_SAIBCLKSOURCE_EXT                0x00800000U

#endif

#if defined(STM32F469xx) || defined(STM32F479xx)

#define RCC_CLK48CLKSOURCE_PLLQ              0x00000000U
#define RCC_CLK48CLKSOURCE_PLLSAIP           ((uint32_t)RCC_DCKCFGR_CK48MSEL)

#define RCC_SDIOCLKSOURCE_CLK48             0x00000000U
#define RCC_SDIOCLKSOURCE_SYSCLK            ((uint32_t)RCC_DCKCFGR_SDIOSEL)

#define RCC_DSICLKSOURCE_DSIPHY             0x00000000U
#define RCC_DSICLKSOURCE_PLLR               ((uint32_t)RCC_DCKCFGR_DSISEL)

#endif

#if defined(STM32F446xx)

#define RCC_SAI1CLKSOURCE_PLLSAI             0x00000000U
#define RCC_SAI1CLKSOURCE_PLLI2S             ((uint32_t)RCC_DCKCFGR_SAI1SRC_0)
#define RCC_SAI1CLKSOURCE_PLLR               ((uint32_t)RCC_DCKCFGR_SAI1SRC_1)
#define RCC_SAI1CLKSOURCE_EXT                ((uint32_t)RCC_DCKCFGR_SAI1SRC)

#define RCC_SAI2CLKSOURCE_PLLSAI             0x00000000U
#define RCC_SAI2CLKSOURCE_PLLI2S             ((uint32_t)RCC_DCKCFGR_SAI2SRC_0)
#define RCC_SAI2CLKSOURCE_PLLR               ((uint32_t)RCC_DCKCFGR_SAI2SRC_1)
#define RCC_SAI2CLKSOURCE_PLLSRC             ((uint32_t)RCC_DCKCFGR_SAI2SRC)

#define RCC_I2SAPB1CLKSOURCE_PLLI2S          0x00000000U
#define RCC_I2SAPB1CLKSOURCE_EXT             ((uint32_t)RCC_DCKCFGR_I2S1SRC_0)
#define RCC_I2SAPB1CLKSOURCE_PLLR            ((uint32_t)RCC_DCKCFGR_I2S1SRC_1)
#define RCC_I2SAPB1CLKSOURCE_PLLSRC          ((uint32_t)RCC_DCKCFGR_I2S1SRC)

#define RCC_I2SAPB2CLKSOURCE_PLLI2S          0x00000000U
#define RCC_I2SAPB2CLKSOURCE_EXT             ((uint32_t)RCC_DCKCFGR_I2S2SRC_0)
#define RCC_I2SAPB2CLKSOURCE_PLLR            ((uint32_t)RCC_DCKCFGR_I2S2SRC_1)
#define RCC_I2SAPB2CLKSOURCE_PLLSRC          ((uint32_t)RCC_DCKCFGR_I2S2SRC)

#define RCC_FMPI2C1CLKSOURCE_PCLK1            0x00000000U
#define RCC_FMPI2C1CLKSOURCE_SYSCLK           ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_0)
#define RCC_FMPI2C1CLKSOURCE_HSI              ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_1)

#define RCC_CECCLKSOURCE_HSI                0x00000000U
#define RCC_CECCLKSOURCE_LSE                ((uint32_t)RCC_DCKCFGR2_CECSEL)

#define RCC_CLK48CLKSOURCE_PLLQ              0x00000000U
#define RCC_CLK48CLKSOURCE_PLLSAIP           ((uint32_t)RCC_DCKCFGR2_CK48MSEL)

#define RCC_SDIOCLKSOURCE_CLK48             0x00000000U
#define RCC_SDIOCLKSOURCE_SYSCLK            ((uint32_t)RCC_DCKCFGR2_SDIOSEL)

#define RCC_SPDIFRXCLKSOURCE_PLLR           0x00000000U
#define RCC_SPDIFRXCLKSOURCE_PLLI2SP        ((uint32_t)RCC_DCKCFGR2_SPDIFRXSEL)

#endif

#if defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_SAIACLKSOURCE_PLLI2SR            0x00000000U
#define RCC_SAIACLKSOURCE_EXT                ((uint32_t)RCC_DCKCFGR_SAI1ASRC_0)
#define RCC_SAIACLKSOURCE_PLLR               ((uint32_t)RCC_DCKCFGR_SAI1ASRC_1)
#define RCC_SAIACLKSOURCE_PLLSRC             ((uint32_t)RCC_DCKCFGR_SAI1ASRC_0 | RCC_DCKCFGR_SAI1ASRC_1)

#define RCC_SAIBCLKSOURCE_PLLI2SR            0x00000000U
#define RCC_SAIBCLKSOURCE_EXT                ((uint32_t)RCC_DCKCFGR_SAI1BSRC_0)
#define RCC_SAIBCLKSOURCE_PLLR               ((uint32_t)RCC_DCKCFGR_SAI1BSRC_1)
#define RCC_SAIBCLKSOURCE_PLLSRC             ((uint32_t)RCC_DCKCFGR_SAI1BSRC_0 | RCC_DCKCFGR_SAI1BSRC_1)

#define RCC_LPTIM1CLKSOURCE_PCLK1           0x00000000U
#define RCC_LPTIM1CLKSOURCE_HSI             ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0)
#define RCC_LPTIM1CLKSOURCE_LSI             ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_1)
#define RCC_LPTIM1CLKSOURCE_LSE             ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0 | RCC_DCKCFGR2_LPTIM1SEL_1)

#define RCC_DFSDM2AUDIOCLKSOURCE_I2S1       0x00000000U
#define RCC_DFSDM2AUDIOCLKSOURCE_I2S2       ((uint32_t)RCC_DCKCFGR_CKDFSDM2ASEL)

#define RCC_DFSDM2CLKSOURCE_PCLK2           0x00000000U
#define RCC_DFSDM2CLKSOURCE_SYSCLK          ((uint32_t)RCC_DCKCFGR_CKDFSDM1SEL)

#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_PLLI2SCLKSOURCE_PLLSRC          0x00000000U
#define RCC_PLLI2SCLKSOURCE_EXT             ((uint32_t)RCC_PLLI2SCFGR_PLLI2SSRC)

#define RCC_DFSDM1AUDIOCLKSOURCE_I2S1       0x00000000U
#define RCC_DFSDM1AUDIOCLKSOURCE_I2S2       ((uint32_t)RCC_DCKCFGR_CKDFSDM1ASEL)

#define RCC_DFSDM1CLKSOURCE_PCLK2           0x00000000U
#define RCC_DFSDM1CLKSOURCE_SYSCLK          ((uint32_t)RCC_DCKCFGR_CKDFSDM1SEL)

#define RCC_I2SAPB1CLKSOURCE_PLLI2S         0x00000000U
#define RCC_I2SAPB1CLKSOURCE_EXT            ((uint32_t)RCC_DCKCFGR_I2S1SRC_0)
#define RCC_I2SAPB1CLKSOURCE_PLLR           ((uint32_t)RCC_DCKCFGR_I2S1SRC_1)
#define RCC_I2SAPB1CLKSOURCE_PLLSRC         ((uint32_t)RCC_DCKCFGR_I2S1SRC)

#define RCC_I2SAPB2CLKSOURCE_PLLI2S         0x00000000U
#define RCC_I2SAPB2CLKSOURCE_EXT            ((uint32_t)RCC_DCKCFGR_I2S2SRC_0)
#define RCC_I2SAPB2CLKSOURCE_PLLR           ((uint32_t)RCC_DCKCFGR_I2S2SRC_1)
#define RCC_I2SAPB2CLKSOURCE_PLLSRC         ((uint32_t)RCC_DCKCFGR_I2S2SRC)

#define RCC_FMPI2C1CLKSOURCE_PCLK1          0x00000000U
#define RCC_FMPI2C1CLKSOURCE_SYSCLK         ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_0)
#define RCC_FMPI2C1CLKSOURCE_HSI            ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_1)

#define RCC_CLK48CLKSOURCE_PLLQ             0x00000000U
#define RCC_CLK48CLKSOURCE_PLLI2SQ          ((uint32_t)RCC_DCKCFGR2_CK48MSEL)

#define RCC_SDIOCLKSOURCE_CLK48             0x00000000U
#define RCC_SDIOCLKSOURCE_SYSCLK            ((uint32_t)RCC_DCKCFGR2_SDIOSEL)

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define RCC_I2SAPBCLKSOURCE_PLLR            0x00000000U
#define RCC_I2SAPBCLKSOURCE_EXT             ((uint32_t)RCC_DCKCFGR_I2SSRC_0)
#define RCC_I2SAPBCLKSOURCE_PLLSRC          ((uint32_t)RCC_DCKCFGR_I2SSRC_1)

#define RCC_FMPI2C1CLKSOURCE_PCLK1              0x00000000U
#define RCC_FMPI2C1CLKSOURCE_SYSCLK             ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_0)
#define RCC_FMPI2C1CLKSOURCE_HSI                ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_1)

#define RCC_LPTIM1CLKSOURCE_PCLK1          0x00000000U
#define RCC_LPTIM1CLKSOURCE_HSI            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0)
#define RCC_LPTIM1CLKSOURCE_LSI            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_1)
#define RCC_LPTIM1CLKSOURCE_LSE            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0 | RCC_DCKCFGR2_LPTIM1SEL_1)

#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_TIMPRES_DESACTIVATED        ((uint8_t)0x00)
#define RCC_TIMPRES_ACTIVATED           ((uint8_t)0x01)

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)

#define RCC_LSE_LOWPOWER_MODE           ((uint8_t)0x00)
#define RCC_LSE_HIGHDRIVE_MODE          ((uint8_t)0x01)

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_MCO2SOURCE_SYSCLK            0x00000000U
#define RCC_MCO2SOURCE_PLLI2SCLK         RCC_CFGR_MCO2_0
#define RCC_MCO2SOURCE_HSE               RCC_CFGR_MCO2_1
#define RCC_MCO2SOURCE_PLLCLK            RCC_CFGR_MCO2

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define RCC_MCO2SOURCE_SYSCLK            0x00000000U
#define RCC_MCO2SOURCE_I2SCLK            RCC_CFGR_MCO2_0
#define RCC_MCO2SOURCE_HSE               RCC_CFGR_MCO2_1
#define RCC_MCO2SOURCE_PLLCLK            RCC_CFGR_MCO2

#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_BKPSRAM_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CCMDATARAMEN_CLK_ENABLE() do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOI_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_GPIOF_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_GPIOG_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_GPIOJ_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_GPIOK_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_DMA2D_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2DEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMAC_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMACTX_CLK_ENABLE() do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMACRX_CLK_ENABLE() do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMACPTP_CLK_ENABLE() do { \
                                              __IO uint32_t tmpreg = 0x00U; \
                                              SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACPTPEN);\
                                                \
                                              tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACPTPEN);\
                                              UNUSED(tmpreg); \
                                            } while(0U)
#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE() do { \
                                               __IO uint32_t tmpreg = 0x00U; \
                                               SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                 \
                                               tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                               UNUSED(tmpreg); \
                                             } while(0U)
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE()   do { \
                                                      __IO uint32_t tmpreg = 0x00U; \
                                                      SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                        \
                                                      tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                      UNUSED(tmpreg); \
                                                    } while(0U)
#define __HAL_RCC_GPIOD_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#define __HAL_RCC_GPIOE_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#define __HAL_RCC_GPIOF_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN))
#define __HAL_RCC_GPIOG_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN))
#define __HAL_RCC_GPIOI_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOIEN))
#define __HAL_RCC_GPIOJ_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOJEN))
#define __HAL_RCC_GPIOK_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOKEN))
#define __HAL_RCC_DMA2D_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA2DEN))
#define __HAL_RCC_ETHMAC_CLK_DISABLE()          (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACEN))
#define __HAL_RCC_ETHMACTX_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACTXEN))
#define __HAL_RCC_ETHMACRX_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACRXEN))
#define __HAL_RCC_ETHMACPTP_CLK_DISABLE()       (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACPTPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_DISABLE()      (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE() (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSULPIEN))
#define __HAL_RCC_BKPSRAM_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_BKPSRAMEN))
#define __HAL_RCC_CCMDATARAMEN_CLK_DISABLE()    (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CCMDATARAMEN))
#define __HAL_RCC_CRC_CLK_DISABLE()             (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))

#define __HAL_RCC_ETH_CLK_ENABLE() do {                                     \
                                        __HAL_RCC_ETHMAC_CLK_ENABLE();      \
                                        __HAL_RCC_ETHMACTX_CLK_ENABLE();    \
                                        __HAL_RCC_ETHMACRX_CLK_ENABLE();    \
                                      } while(0U)

#define __HAL_RCC_ETH_CLK_DISABLE()  do {                                      \
                                          __HAL_RCC_ETHMACTX_CLK_DISABLE();    \
                                          __HAL_RCC_ETHMACRX_CLK_DISABLE();    \
                                          __HAL_RCC_ETHMAC_CLK_DISABLE();      \
                                        } while(0U)

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) != RESET)
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) != RESET)
#define __HAL_RCC_GPIOI_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOIEN)) != RESET)
#define __HAL_RCC_GPIOJ_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOJEN)) != RESET)
#define __HAL_RCC_GPIOK_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOKEN)) != RESET)
#define __HAL_RCC_DMA2D_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA2DEN)) != RESET)
#define __HAL_RCC_ETHMAC_IS_CLK_ENABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACEN)) != RESET)
#define __HAL_RCC_ETHMACTX_IS_CLK_ENABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACTXEN)) != RESET)
#define __HAL_RCC_ETHMACRX_IS_CLK_ENABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACRXEN)) != RESET)
#define __HAL_RCC_ETHMACPTP_IS_CLK_ENABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACPTPEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_ENABLED()      ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_ENABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN)) != RESET)
#define __HAL_RCC_BKPSRAM_IS_CLK_ENABLED()         ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) != RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_ENABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) != RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)
#define __HAL_RCC_ETH_IS_CLK_ENABLED()             (__HAL_RCC_ETHMAC_IS_CLK_ENABLED()   && \
                                                    __HAL_RCC_ETHMACTX_IS_CLK_ENABLED() && \
                                                    __HAL_RCC_ETHMACRX_IS_CLK_ENABLED())

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) == RESET)
#define __HAL_RCC_GPIOG_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) == RESET)
#define __HAL_RCC_GPIOI_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOIEN)) == RESET)
#define __HAL_RCC_GPIOJ_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOJEN)) == RESET)
#define __HAL_RCC_GPIOK_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOKEN)) == RESET)
#define __HAL_RCC_DMA2D_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_DMA2DEN)) == RESET)
#define __HAL_RCC_ETHMAC_IS_CLK_DISABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACEN)) == RESET)
#define __HAL_RCC_ETHMACTX_IS_CLK_DISABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACTXEN)) == RESET)
#define __HAL_RCC_ETHMACRX_IS_CLK_DISABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACRXEN)) == RESET)
#define __HAL_RCC_ETHMACPTP_IS_CLK_DISABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACPTPEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_DISABLED()      ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_DISABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN)) == RESET)
#define __HAL_RCC_BKPSRAM_IS_CLK_DISABLED()         ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) == RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)
#define __HAL_RCC_ETH_IS_CLK_DISABLED()             (__HAL_RCC_ETHMAC_IS_CLK_DISABLED()   && \
                                                     __HAL_RCC_ETHMACTX_IS_CLK_DISABLED() && \
                                                     __HAL_RCC_ETHMACRX_IS_CLK_DISABLED())

#define __HAL_RCC_DCMI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DCMI_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_DCMIEN))

#if defined(STM32F437xx)|| defined(STM32F439xx) || defined(STM32F479xx)
#define __HAL_RCC_CRYP_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CRYPEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CRYPEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_HASH_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)

#define __HAL_RCC_CRYP_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_CRYPEN))
#define __HAL_RCC_HASH_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_HASHEN))
#endif

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#define __HAL_RCC_RNG_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_RNG_CLK_DISABLE()   (RCC->AHB2ENR &= ~(RCC_AHB2ENR_RNGEN))

#define __HAL_RCC_DCMI_IS_CLK_ENABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) != RESET)
#define __HAL_RCC_DCMI_IS_CLK_DISABLED()       ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) == RESET)

#if defined(STM32F437xx)|| defined(STM32F439xx) || defined(STM32F479xx)
#define __HAL_RCC_CRYP_IS_CLK_ENABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_CRYPEN)) != RESET)
#define __HAL_RCC_CRYP_IS_CLK_DISABLED()       ((RCC->AHB2ENR & (RCC_AHB2ENR_CRYPEN)) == RESET)

#define __HAL_RCC_HASH_IS_CLK_ENABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_HASHEN)) != RESET)
#define __HAL_RCC_HASH_IS_CLK_DISABLED()       ((RCC->AHB2ENR & (RCC_AHB2ENR_HASHEN)) == RESET)
#endif

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_RNG_IS_CLK_ENABLED()         ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) != RESET)
#define __HAL_RCC_RNG_IS_CLK_DISABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) == RESET)

#define __HAL_RCC_FMC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_FMC_CLK_DISABLE()  (RCC->AHB3ENR &= ~(RCC_AHB3ENR_FMCEN))
#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_QSPI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_QSPI_CLK_DISABLE()  (RCC->AHB3ENR &= ~(RCC_AHB3ENR_QSPIEN))
#endif

#define __HAL_RCC_FMC_IS_CLK_ENABLED()   ((RCC->AHB3ENR & (RCC_AHB3ENR_FMCEN)) != RESET)
#define __HAL_RCC_FMC_IS_CLK_DISABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_FMCEN)) == RESET)
#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_QSPI_IS_CLK_ENABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) != RESET)
#define __HAL_RCC_QSPI_IS_CLK_DISABLED() ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) == RESET)
#endif

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM7_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM12_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM13_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_USART3_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART4_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART5_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DAC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART7_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART8_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#define __HAL_RCC_TIM6_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __HAL_RCC_TIM7_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __HAL_RCC_TIM12_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN))
#define __HAL_RCC_TIM13_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN))
#define __HAL_RCC_TIM14_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN))
#define __HAL_RCC_USART3_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __HAL_RCC_UART4_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __HAL_RCC_UART5_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))
#define __HAL_RCC_CAN1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN1EN))
#define __HAL_RCC_CAN2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN2EN))
#define __HAL_RCC_DAC_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))
#define __HAL_RCC_UART7_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART7EN))
#define __HAL_RCC_UART8_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART8EN))

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) != RESET)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) != RESET)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) != RESET)
#define __HAL_RCC_TIM13_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) != RESET)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) != RESET)
#define __HAL_RCC_USART3_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) != RESET)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) != RESET)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) != RESET)
#define __HAL_RCC_CAN1_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) != RESET)
#define __HAL_RCC_CAN2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) != RESET)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) != RESET)
#define __HAL_RCC_UART7_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART7EN)) != RESET)
#define __HAL_RCC_UART8_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART8EN)) != RESET)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)
#define __HAL_RCC_TIM6_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) == RESET)
#define __HAL_RCC_TIM7_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) == RESET)
#define __HAL_RCC_TIM12_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) == RESET)
#define __HAL_RCC_TIM13_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) == RESET)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) == RESET)
#define __HAL_RCC_USART3_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) == RESET)
#define __HAL_RCC_UART4_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) == RESET)
#define __HAL_RCC_UART5_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) == RESET)
#define __HAL_RCC_CAN1_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) == RESET)
#define __HAL_RCC_CAN2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) == RESET)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) == RESET)
#define __HAL_RCC_UART7_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART7EN)) == RESET)
#define __HAL_RCC_UART8_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART8EN)) == RESET)

#define __HAL_RCC_TIM8_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SPI5_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SPI6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SAI1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SDIO_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_TIM10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __HAL_RCC_TIM8_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN))
#define __HAL_RCC_ADC2_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC2EN))
#define __HAL_RCC_ADC3_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC3EN))
#define __HAL_RCC_SPI5_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI5EN))
#define __HAL_RCC_SPI6_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI6EN))
#define __HAL_RCC_SAI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SAI1EN))

#if defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_LTDC_CLK_ENABLE()  do { \
                                          __IO uint32_t tmpreg = 0x00U; \
                                          SET_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);\
                                            \
                                          tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_LTDCEN);\
                                          UNUSED(tmpreg); \
                                        } while(0U)

#define __HAL_RCC_LTDC_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_LTDCEN))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_DSI_CLK_ENABLE() do { \
                                        __IO uint32_t tmpreg = 0x00U; \
                                        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_DSIEN);\
                                          \
                                        tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_DSIEN);\
                                        UNUSED(tmpreg); \
                                      } while(0U)

#define __HAL_RCC_DSI_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_DSIEN))
#endif

#define __HAL_RCC_TIM8_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) != RESET)
#define __HAL_RCC_ADC2_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) != RESET)
#define __HAL_RCC_ADC3_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) != RESET)
#define __HAL_RCC_SPI5_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) != RESET)
#define __HAL_RCC_SPI6_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI6EN)) != RESET)
#define __HAL_RCC_SAI1_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) != RESET)
#define __HAL_RCC_SDIO_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN))!= RESET)

#define __HAL_RCC_SDIO_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN))== RESET)
#define __HAL_RCC_TIM8_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) == RESET)
#define __HAL_RCC_ADC2_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) == RESET)
#define __HAL_RCC_ADC3_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) == RESET)
#define __HAL_RCC_SPI5_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) == RESET)
#define __HAL_RCC_SPI6_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI6EN)) == RESET)
#define __HAL_RCC_SAI1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) == RESET)

#if defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_LTDC_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_LTDCEN)) != RESET)
#define __HAL_RCC_LTDC_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_LTDCEN)) == RESET)
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_DSI_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_DSIEN)) != RESET)
#define __HAL_RCC_DSI_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_DSIEN)) == RESET)
#endif

#define __HAL_RCC_AHB1_FORCE_RESET()     (RCC->AHB1RSTR = 0x22E017FFU)
#define __HAL_RCC_GPIOD_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_GPIOI_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOIRST))
#define __HAL_RCC_ETHMAC_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_ETHMACRST))
#define __HAL_RCC_USB_OTG_HS_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_GPIOJ_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOJRST))
#define __HAL_RCC_GPIOK_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOKRST))
#define __HAL_RCC_DMA2D_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_DMA2DRST))
#define __HAL_RCC_CRC_FORCE_RESET()      (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_GPIOD_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_GPIOI_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOIRST))
#define __HAL_RCC_ETHMAC_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_ETHMACRST))
#define __HAL_RCC_USB_OTG_HS_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_GPIOJ_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOJRST))
#define __HAL_RCC_GPIOK_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOKRST))
#define __HAL_RCC_DMA2D_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_DMA2DRST))
#define __HAL_RCC_CRC_RELEASE_RESET()    (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#if defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F469xx)
#define __HAL_RCC_AHB2_FORCE_RESET()   (RCC->AHB2RSTR = 0x000000C1U)
#endif
#if defined(STM32F437xx) || defined(STM32F439xx) || defined(STM32F479xx)
#define __HAL_RCC_AHB2_FORCE_RESET()   (RCC->AHB2RSTR = 0x000000F1U)
#endif
#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_RNG_FORCE_RESET()    (RCC->AHB2RSTR |= (RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_DCMI_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_DCMIRST))

#define __HAL_RCC_AHB2_RELEASE_RESET()  (RCC->AHB2RSTR = 0x00U)
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_RNG_RELEASE_RESET()  (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_DCMI_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_DCMIRST))

#if defined(STM32F437xx)|| defined(STM32F439xx) || defined(STM32F479xx)
#define __HAL_RCC_CRYP_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_CRYPRST))
#define __HAL_RCC_HASH_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_HASHRST))

#define __HAL_RCC_CRYP_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_CRYPRST))
#define __HAL_RCC_HASH_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_HASHRST))
#endif

#if defined(STM32F427xx) || defined(STM32F429xx) || defined(STM32F437xx) || defined(STM32F439xx)
#define __HAL_RCC_AHB3_FORCE_RESET()   (RCC->AHB3RSTR = 0x00000001U)
#endif
#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_AHB3_FORCE_RESET()   (RCC->AHB3RSTR = 0x00000003U)
#endif
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)
#define __HAL_RCC_FMC_FORCE_RESET()    (RCC->AHB3RSTR |= (RCC_AHB3RSTR_FMCRST))
#define __HAL_RCC_FMC_RELEASE_RESET()  (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_FMCRST))

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_QSPI_FORCE_RESET()   (RCC->AHB3RSTR |= (RCC_AHB3RSTR_QSPIRST))
#define __HAL_RCC_QSPI_RELEASE_RESET()   (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_QSPIRST))
#endif

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xF6FEC9FFU)
#define __HAL_RCC_TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_CAN1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_DAC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))
#define __HAL_RCC_UART7_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART7RST))
#define __HAL_RCC_UART8_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART8RST))
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#define __HAL_RCC_TIM6_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_USART3_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_CAN1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_DAC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))
#define __HAL_RCC_UART7_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART7RST))
#define __HAL_RCC_UART8_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART8RST))

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_APB2_FORCE_RESET()   (RCC->APB2RSTR = 0x0C777933U)
#endif
#if defined(STM32F429xx) || defined(STM32F439xx)
#define __HAL_RCC_APB2_FORCE_RESET()   (RCC->APB2RSTR = 0x04777933U)
#endif
#if defined(STM32F427xx) || defined(STM32F437xx)
#define __HAL_RCC_APB2_FORCE_RESET()   (RCC->APB2RSTR = 0x00777933U)
#endif
#define __HAL_RCC_TIM8_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM8RST))
#define __HAL_RCC_SPI5_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI5RST))
#define __HAL_RCC_SPI6_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI6RST))
#define __HAL_RCC_SAI1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SAI1RST))
#define __HAL_RCC_SDIO_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()  (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_SDIO_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()(RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_TIM8_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM8RST))
#define __HAL_RCC_SPI5_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI5RST))
#define __HAL_RCC_SPI6_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI6RST))
#define __HAL_RCC_SAI1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SAI1RST))

#if defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_LTDC_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_LTDCRST))
#define __HAL_RCC_LTDC_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_LTDCRST))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_DSI_FORCE_RESET()   (RCC->APB2RSTR |=  (RCC_APB2RSTR_DSIRST))
#define __HAL_RCC_DSI_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_DSIRST))
#endif

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_GPIOI_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOILPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_ETHMAC_CLK_SLEEP_ENABLE()     (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACLPEN))
#define __HAL_RCC_ETHMACTX_CLK_SLEEP_ENABLE()   (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACTXLPEN))
#define __HAL_RCC_ETHMACRX_CLK_SLEEP_ENABLE()   (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACRXLPEN))
#define __HAL_RCC_ETHMACPTP_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACPTPLPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_GPIOJ_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOJLPEN))
#define __HAL_RCC_GPIOK_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOKLPEN))
#define __HAL_RCC_SRAM3_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM3LPEN))
#define __HAL_RCC_DMA2D_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_DMA2DLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()        (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_GPIOI_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOILPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_ETHMAC_CLK_SLEEP_DISABLE()    (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACLPEN))
#define __HAL_RCC_ETHMACTX_CLK_SLEEP_DISABLE()  (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACTXLPEN))
#define __HAL_RCC_ETHMACRX_CLK_SLEEP_DISABLE()  (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACRXLPEN))
#define __HAL_RCC_ETHMACPTP_CLK_SLEEP_DISABLE() (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACPTPLPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_DISABLE() (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_GPIOJ_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOJLPEN))
#define __HAL_RCC_GPIOK_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOKLPEN))
#define __HAL_RCC_DMA2D_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_DMA2DLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()       (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))
#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()   (RCC->AHB2LPENR |= (RCC_AHB2LPENR_RNGLPEN))
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()  (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_RNGLPEN))

#define __HAL_RCC_DCMI_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_DCMILPEN))
#define __HAL_RCC_DCMI_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_DCMILPEN))

#if defined(STM32F437xx)|| defined(STM32F439xx) || defined(STM32F479xx)
#define __HAL_RCC_CRYP_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_CRYPLPEN))
#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_HASHLPEN))

#define __HAL_RCC_CRYP_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_CRYPLPEN))
#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_HASHLPEN))
#endif

#define __HAL_RCC_FMC_CLK_SLEEP_ENABLE()  (RCC->AHB3LPENR |= (RCC_AHB3LPENR_FMCLPEN))
#define __HAL_RCC_FMC_CLK_SLEEP_DISABLE() (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_FMCLPEN))

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_QSPI_CLK_SLEEP_ENABLE()  (RCC->AHB3LPENR |= (RCC_AHB3LPENR_QSPILPEN))
#define __HAL_RCC_QSPI_CLK_SLEEP_DISABLE()  (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_QSPILPEN))
#endif

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_UART7_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART7LPEN))
#define __HAL_RCC_UART8_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART8LPEN))
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_UART7_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART7LPEN))
#define __HAL_RCC_UART8_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART8LPEN))

#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC3LPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI5LPEN))
#define __HAL_RCC_SPI6_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI6LPEN))
#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SAI1LPEN))
#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()(RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()(RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC3LPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI5LPEN))
#define __HAL_RCC_SPI6_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI6LPEN))
#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SAI1LPEN))

#if defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_LTDC_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_LTDCLPEN))

#define __HAL_RCC_LTDC_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_LTDCLPEN))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define __HAL_RCC_DSI_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |=  (RCC_APB2LPENR_DSILPEN))
#define __HAL_RCC_DSI_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_DSILPEN))
#endif

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx)

#define __HAL_RCC_BKPSRAM_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CCMDATARAMEN_CLK_ENABLE() do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOI_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOF_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOG_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE()   do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE()   do { \
                                                      __IO uint32_t tmpreg = 0x00U; \
                                                      SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                        \
                                                      tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                      UNUSED(tmpreg); \
                                                    } while(0U)
#define __HAL_RCC_GPIOD_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#define __HAL_RCC_GPIOE_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#define __HAL_RCC_GPIOF_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN))
#define __HAL_RCC_GPIOG_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN))
#define __HAL_RCC_GPIOI_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOIEN))
#define __HAL_RCC_USB_OTG_HS_CLK_DISABLE()      (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE() (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSULPIEN))
#define __HAL_RCC_BKPSRAM_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_BKPSRAMEN))
#define __HAL_RCC_CCMDATARAMEN_CLK_DISABLE()    (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CCMDATARAMEN))
#define __HAL_RCC_CRC_CLK_DISABLE()             (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))
#if defined(STM32F407xx)|| defined(STM32F417xx)

#define __HAL_RCC_ETHMAC_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_ETHMACTX_CLK_ENABLE() do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACTXEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMACRX_CLK_ENABLE() do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACRXEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ETHMACPTP_CLK_ENABLE() do { \
                                              __IO uint32_t tmpreg = 0x00U; \
                                              SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACPTPEN);\
                                                \
                                              tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_ETHMACPTPEN);\
                                              UNUSED(tmpreg); \
                                            } while(0U)
#define __HAL_RCC_ETH_CLK_ENABLE()      do {                            \
                                             __HAL_RCC_ETHMAC_CLK_ENABLE();      \
                                             __HAL_RCC_ETHMACTX_CLK_ENABLE();    \
                                             __HAL_RCC_ETHMACRX_CLK_ENABLE();    \
                                           } while(0U)

#define __HAL_RCC_ETHMAC_CLK_DISABLE()    (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACEN))
#define __HAL_RCC_ETHMACTX_CLK_DISABLE()  (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACTXEN))
#define __HAL_RCC_ETHMACRX_CLK_DISABLE()  (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACRXEN))
#define __HAL_RCC_ETHMACPTP_CLK_DISABLE() (RCC->AHB1ENR &= ~(RCC_AHB1ENR_ETHMACPTPEN))
#define __HAL_RCC_ETH_CLK_DISABLE()       do {                             \
                                               __HAL_RCC_ETHMACTX_CLK_DISABLE();    \
                                               __HAL_RCC_ETHMACRX_CLK_DISABLE();    \
                                               __HAL_RCC_ETHMAC_CLK_DISABLE();      \
                                             } while(0U)
#endif

#define __HAL_RCC_BKPSRAM_IS_CLK_ENABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) != RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) != RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()              ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#define __HAL_RCC_GPIOI_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOIEN)) != RESET)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) != RESET)
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_ENABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_ENABLED()  ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN)) != RESET)

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) == RESET)
#define __HAL_RCC_GPIOG_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) == RESET)
#define __HAL_RCC_GPIOI_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOIEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_DISABLED()      ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_DISABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN))== RESET)
#define __HAL_RCC_BKPSRAM_IS_CLK_DISABLED()         ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) == RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)
#if defined(STM32F407xx)|| defined(STM32F417xx)

#define __HAL_RCC_ETHMAC_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACEN)) != RESET)
#define __HAL_RCC_ETHMACTX_IS_CLK_ENABLED()   ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACTXEN)) != RESET)
#define __HAL_RCC_ETHMACRX_IS_CLK_ENABLED()   ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACRXEN)) != RESET)
#define __HAL_RCC_ETHMACPTP_IS_CLK_ENABLED()  ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACPTPEN)) != RESET)
#define __HAL_RCC_ETH_IS_CLK_ENABLED()        (__HAL_RCC_ETHMAC_IS_CLK_ENABLED()   && \
                                               __HAL_RCC_ETHMACTX_IS_CLK_ENABLED() && \
                                               __HAL_RCC_ETHMACRX_IS_CLK_ENABLED())

#define __HAL_RCC_ETHMAC_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACEN)) == RESET)
#define __HAL_RCC_ETHMACTX_IS_CLK_DISABLED()  ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACTXEN)) == RESET)
#define __HAL_RCC_ETHMACRX_IS_CLK_DISABLED()  ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACRXEN)) == RESET)
#define __HAL_RCC_ETHMACPTP_IS_CLK_DISABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_ETHMACPTPEN)) == RESET)
#define __HAL_RCC_ETH_IS_CLK_DISABLED()        (__HAL_RCC_ETHMAC_IS_CLK_DISABLED()   && \
                                                __HAL_RCC_ETHMACTX_IS_CLK_DISABLED() && \
                                                __HAL_RCC_ETHMACRX_IS_CLK_DISABLED())
#endif

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#define __HAL_RCC_RNG_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_RNG_CLK_DISABLE()   (RCC->AHB2ENR &= ~(RCC_AHB2ENR_RNGEN))

#if defined(STM32F407xx)|| defined(STM32F417xx)
#define __HAL_RCC_DCMI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DCMI_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_DCMIEN))
#endif

#if defined(STM32F415xx) || defined(STM32F417xx)
#define __HAL_RCC_CRYP_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CRYPEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_CRYPEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_HASH_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_HASHEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CRYP_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_CRYPEN))
#define __HAL_RCC_HASH_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_HASHEN))
#endif

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_RNG_IS_CLK_ENABLED()   ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) != RESET)
#define __HAL_RCC_RNG_IS_CLK_DISABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) == RESET)

#if defined(STM32F407xx)|| defined(STM32F417xx)
#define __HAL_RCC_DCMI_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) != RESET)
#define __HAL_RCC_DCMI_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) == RESET)
#endif

#if defined(STM32F415xx) || defined(STM32F417xx)
#define __HAL_RCC_CRYP_IS_CLK_ENABLED()   ((RCC->AHB2ENR & (RCC_AHB2ENR_CRYPEN)) != RESET)
#define __HAL_RCC_HASH_IS_CLK_ENABLED()   ((RCC->AHB2ENR & (RCC_AHB2ENR_HASHEN)) != RESET)

#define __HAL_RCC_CRYP_IS_CLK_DISABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_CRYPEN)) == RESET)
#define __HAL_RCC_HASH_IS_CLK_DISABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_HASHEN)) == RESET)
#endif

#define __HAL_RCC_FSMC_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FSMCEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FSMCEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_FSMC_CLK_DISABLE() (RCC->AHB3ENR &= ~(RCC_AHB3ENR_FSMCEN))

#define __HAL_RCC_FSMC_IS_CLK_ENABLED()   ((RCC->AHB3ENR & (RCC_AHB3ENR_FSMCEN)) != RESET)
#define __HAL_RCC_FSMC_IS_CLK_DISABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_FSMCEN)) == RESET)

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM7_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM12_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM13_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_USART3_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART4_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART5_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DAC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#define __HAL_RCC_TIM6_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __HAL_RCC_TIM7_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __HAL_RCC_TIM12_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN))
#define __HAL_RCC_TIM13_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN))
#define __HAL_RCC_TIM14_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN))
#define __HAL_RCC_USART3_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __HAL_RCC_UART4_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __HAL_RCC_UART5_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))
#define __HAL_RCC_CAN1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN1EN))
#define __HAL_RCC_CAN2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN2EN))
#define __HAL_RCC_DAC_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) != RESET)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) != RESET)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) != RESET)
#define __HAL_RCC_TIM13_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) != RESET)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) != RESET)
#define __HAL_RCC_USART3_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) != RESET)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) != RESET)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) != RESET)
#define __HAL_RCC_CAN1_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) != RESET)
#define __HAL_RCC_CAN2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) != RESET)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) != RESET)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)
#define __HAL_RCC_TIM6_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) == RESET)
#define __HAL_RCC_TIM7_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) == RESET)
#define __HAL_RCC_TIM12_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) == RESET)
#define __HAL_RCC_TIM13_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) == RESET)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) == RESET)
#define __HAL_RCC_USART3_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) == RESET)
#define __HAL_RCC_UART4_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) == RESET)
#define __HAL_RCC_UART5_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) == RESET)
#define __HAL_RCC_CAN1_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) == RESET)
#define __HAL_RCC_CAN2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) == RESET)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) == RESET)

#define __HAL_RCC_TIM8_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)

#define __HAL_RCC_SDIO_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_TIM10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __HAL_RCC_TIM8_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN))
#define __HAL_RCC_ADC2_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC2EN))
#define __HAL_RCC_ADC3_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC3EN))

#define __HAL_RCC_SDIO_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) != RESET)
#define __HAL_RCC_TIM8_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) != RESET)
#define __HAL_RCC_ADC2_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) != RESET)
#define __HAL_RCC_ADC3_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) != RESET)

#define __HAL_RCC_SDIO_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) == RESET)
#define __HAL_RCC_TIM8_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) == RESET)
#define __HAL_RCC_ADC2_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) == RESET)
#define __HAL_RCC_ADC3_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) == RESET)

#if defined (STM32F405xx) || defined (STM32F415xx)
#define __HAL_RCC_AHB1_FORCE_RESET()     (RCC->AHB1RSTR = 0x206011FFU)
#endif
#if defined (STM32F407xx) || defined (STM32F417xx)
#define __HAL_RCC_AHB1_FORCE_RESET()     (RCC->AHB1RSTR = 0x226011FFU)
#endif
#define __HAL_RCC_GPIOD_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_GPIOI_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOIRST))
#define __HAL_RCC_ETHMAC_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_ETHMACRST))
#define __HAL_RCC_USB_OTG_HS_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_GPIOD_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_GPIOI_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOIRST))
#define __HAL_RCC_ETHMAC_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_ETHMACRST))
#define __HAL_RCC_USB_OTG_HS_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_CRC_RELEASE_RESET()    (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#if defined (STM32F415xx) || defined (STM32F417xx)
#define __HAL_RCC_AHB2_FORCE_RESET()         (RCC->AHB2RSTR = 0x000000F1U)
#endif
#if defined (STM32F405xx) || defined (STM32F407xx)
#define __HAL_RCC_AHB2_FORCE_RESET()         (RCC->AHB2RSTR = 0x000000C1U)
#endif
#define __HAL_RCC_AHB2_RELEASE_RESET()       (RCC->AHB2RSTR = 0x00U)

#if defined(STM32F407xx)|| defined(STM32F417xx)
#define __HAL_RCC_DCMI_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_DCMIRST))
#define __HAL_RCC_DCMI_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_DCMIRST))
#endif

#if defined(STM32F415xx) || defined(STM32F417xx)
#define __HAL_RCC_CRYP_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_CRYPRST))
#define __HAL_RCC_HASH_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_HASHRST))

#define __HAL_RCC_CRYP_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_CRYPRST))
#define __HAL_RCC_HASH_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_HASHRST))
#endif

#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_RNG_FORCE_RESET()    (RCC->AHB2RSTR |= (RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_RNG_RELEASE_RESET()  (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_RNGRST))

#define __HAL_RCC_AHB3_FORCE_RESET()   (RCC->AHB3RSTR = 0x00000001U)
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)

#define __HAL_RCC_FSMC_FORCE_RESET()   (RCC->AHB3RSTR |= (RCC_AHB3RSTR_FSMCRST))
#define __HAL_RCC_FSMC_RELEASE_RESET() (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_FSMCRST))

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xF6FEC9FFU)
#define __HAL_RCC_TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_CAN1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_DAC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#define __HAL_RCC_TIM6_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_USART3_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_CAN1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_DAC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))

#define __HAL_RCC_APB2_FORCE_RESET()   (RCC->APB2RSTR = 0x04777933U)
#define __HAL_RCC_TIM8_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM8RST))
#define __HAL_RCC_SDIO_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()  (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_SDIO_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()(RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_TIM8_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM8RST))

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_GPIOI_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOILPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_ETHMAC_CLK_SLEEP_ENABLE()     (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACLPEN))
#define __HAL_RCC_ETHMACTX_CLK_SLEEP_ENABLE()   (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACTXLPEN))
#define __HAL_RCC_ETHMACRX_CLK_SLEEP_ENABLE()   (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACRXLPEN))
#define __HAL_RCC_ETHMACPTP_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_ETHMACPTPLPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_GPIOI_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOILPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_ETHMAC_CLK_SLEEP_DISABLE()    (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACLPEN))
#define __HAL_RCC_ETHMACTX_CLK_SLEEP_DISABLE()  (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACTXLPEN))
#define __HAL_RCC_ETHMACRX_CLK_SLEEP_DISABLE()  (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACRXLPEN))
#define __HAL_RCC_ETHMACPTP_CLK_SLEEP_DISABLE() (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_ETHMACPTPLPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_DISABLE() (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()       (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))
#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()   (RCC->AHB2LPENR |= (RCC_AHB2LPENR_RNGLPEN))
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()  (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_RNGLPEN))

#if defined(STM32F407xx)|| defined(STM32F417xx)
#define __HAL_RCC_DCMI_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_DCMILPEN))
#define __HAL_RCC_DCMI_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_DCMILPEN))
#endif

#if defined(STM32F415xx) || defined(STM32F417xx)
#define __HAL_RCC_CRYP_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_CRYPLPEN))
#define __HAL_RCC_HASH_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_HASHLPEN))

#define __HAL_RCC_CRYP_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_CRYPLPEN))
#define __HAL_RCC_HASH_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_HASHLPEN))
#endif

#define __HAL_RCC_FSMC_CLK_SLEEP_ENABLE()  (RCC->AHB3LPENR |= (RCC_AHB3LPENR_FSMCLPEN))
#define __HAL_RCC_FSMC_CLK_SLEEP_DISABLE() (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_FSMCLPEN))

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))

#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC3LPEN))
#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()(RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()(RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC3LPEN))

#endif

#if defined(STM32F401xC) || defined(STM32F401xE)

#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CCMDATARAMEN_CLK_ENABLE()  do { \
                                                  __IO uint32_t tmpreg = 0x00U; \
                                                  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                    \
                                                  tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                  UNUSED(tmpreg); \
                                                } while(0U)

#define __HAL_RCC_GPIOD_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#define __HAL_RCC_GPIOE_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#define __HAL_RCC_CRC_CLK_DISABLE()          (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))
#define __HAL_RCC_CCMDATARAMEN_CLK_DISABLE() (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CCMDATARAMEN))

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_ENABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) != RESET)

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()        ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_DISABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) == RESET)

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)

#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)

#define __HAL_RCC_SDIO_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_TIM10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))

#define __HAL_RCC_SDIO_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) != RESET)

#define __HAL_RCC_SDIO_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED() ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) == RESET)

#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x0060109FU)
#define __HAL_RCC_GPIOD_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_AHB1_RELEASE_RESET()  (RCC->AHB1RSTR = 0x00U)
#define __HAL_RCC_GPIOD_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_CRC_RELEASE_RESET()   (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_AHB2_FORCE_RESET()         (RCC->AHB2RSTR = 0x00000080U)
#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_AHB2_RELEASE_RESET()  (RCC->AHB2RSTR = 0x00U)
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0x10E2C80FU)
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_APB1_RELEASE_RESET()   (RCC->APB1RSTR = 0x00U)
#define __HAL_RCC_TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0x00077931U)
#define __HAL_RCC_SDIO_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_APB2_RELEASE_RESET()   (RCC->APB2RSTR = 0x00U)
#define __HAL_RCC_SDIO_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_AHB3_FORCE_RESET() (RCC->AHB3RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE()   (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_RNG_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RNGEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_RNGEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CRC_CLK_DISABLE()     (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))
#define __HAL_RCC_RNG_CLK_DISABLE()     (RCC->AHB1ENR &= ~(RCC_AHB1ENR_RNGEN))

#define __HAL_RCC_CRC_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)
#define __HAL_RCC_RNG_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_RNGEN)) != RESET)

#define __HAL_RCC_CRC_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)
#define __HAL_RCC_RNG_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_RNGEN)) == RESET)

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_LPTIM1_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_LPTIM1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_LPTIM1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_RTCAPB_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_RTCAPBEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_RTCAPBEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_FMPI2C1_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_DAC_CLK_ENABLE()   do { \
                                          __IO uint32_t tmpreg = 0x00U; \
                                          SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                            \
                                          tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                          UNUSED(tmpreg); \
                                        } while(0U)

#define __HAL_RCC_TIM6_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __HAL_RCC_RTCAPB_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_RTCAPBEN))
#define __HAL_RCC_LPTIM1_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_LPTIM1EN))
#define __HAL_RCC_FMPI2C1_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_FMPI2C1EN))
#define __HAL_RCC_DAC_CLK_DISABLE()     (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))

#define __HAL_RCC_TIM6_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) != RESET)
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_RTCAPBEN)) != RESET)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_LPTIM1EN)) != RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) != RESET)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) != RESET)

#define __HAL_RCC_TIM6_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) == RESET)
#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_RTCAPBEN)) == RESET)
#define __HAL_RCC_LPTIM1_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_LPTIM1EN)) == RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) == RESET)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) == RESET)

#define __HAL_RCC_SPI5_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_EXTIT_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_EXTITEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_EXTITEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SPI5_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI5EN))
#define __HAL_RCC_EXTIT_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_EXTITEN))

#define __HAL_RCC_SPI5_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) != RESET)
#define __HAL_RCC_EXTIT_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_EXTITEN)) != RESET)

#define __HAL_RCC_SPI5_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) == RESET)
#define __HAL_RCC_EXTIT_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_EXTITEN)) == RESET)

#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x80601087U)
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))
#define __HAL_RCC_RNG_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_RNGRST))
#define __HAL_RCC_CRC_RELEASE_RESET()   (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))
#define __HAL_RCC_RNG_RELEASE_RESET()   (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_RNGRST))

#define __HAL_RCC_AHB2_FORCE_RESET()
#define __HAL_RCC_AHB2_RELEASE_RESET()

#define __HAL_RCC_AHB3_FORCE_RESET()
#define __HAL_RCC_AHB3_RELEASE_RESET()

#if defined (STM32F410Rx) || defined (STM32F410Cx)
#define __HAL_RCC_APB1_FORCE_RESET()      (RCC->APB1RSTR = 0x31624A18U)
#endif
#if defined (STM32F410Tx)
#define __HAL_RCC_APB1_FORCE_RESET()      (RCC->APB1RSTR = 0x31620A18U)
#endif
#define __HAL_RCC_TIM6_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_LPTIM1_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_LPTIM1RST))
#define __HAL_RCC_FMPI2C1_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_DAC_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))

#define __HAL_RCC_TIM6_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_LPTIM1_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_LPTIM1RST))
#define __HAL_RCC_FMPI2C1_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_DAC_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))

#if defined (STM32F410Rx) || defined (STM32F410Cx)
#define __HAL_RCC_APB2_FORCE_RESET()      (RCC->APB2RSTR = 0x00155131U)
#endif
#if defined (STM32F410Tx)
#define __HAL_RCC_APB2_FORCE_RESET()      (RCC->APB2RSTR = 0x00055111U)
#endif
#define __HAL_RCC_SPI5_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI5RST))
#define __HAL_RCC_SPI5_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI5RST))

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_RNGLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_RNGLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_LPTIM1LPEN))
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_RTCAPBLPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_ENABLE() (RCC->APB1LPENR |= (RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))

#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_LPTIM1LPEN))
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_RTCAPBLPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()     (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))

#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE()     (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI5LPEN))
#define __HAL_RCC_EXTIT_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_EXTITLPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI5LPEN))
#define __HAL_RCC_EXTIT_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_EXTITLPEN))

#endif

#if defined(STM32F411xE)

#define __HAL_RCC_CCMDATARAMEN_CLK_ENABLE() do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOD_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#define __HAL_RCC_GPIOE_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#define __HAL_RCC_CCMDATARAMEN_CLK_DISABLE()    (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CCMDATARAMEN))
#define __HAL_RCC_CRC_CLK_DISABLE()             (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_ENABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) != RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)

#define __HAL_RCC_SPI5_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SDIO_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_TIM10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __HAL_RCC_SPI5_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI5EN))

#define __HAL_RCC_SDIO_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) != RESET)
#define __HAL_RCC_SPI5_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) != RESET)

#define __HAL_RCC_SDIO_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) == RESET)
#define __HAL_RCC_SPI5_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) == RESET)

#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x0060109FU)
#define __HAL_RCC_GPIOD_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_CRC_FORCE_RESET()     (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_GPIOD_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_CRC_RELEASE_RESET()    (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_AHB2_FORCE_RESET()    (RCC->AHB2RSTR = 0x00000080U)
#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_AHB2_RELEASE_RESET()  (RCC->AHB2RSTR = 0x00U)
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_AHB3_FORCE_RESET() (RCC->AHB3RSTR = 0xFFFFFFFFU)
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0x10E2C80FU)
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0x00177931U)
#define __HAL_RCC_SPI5_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI5RST))
#define __HAL_RCC_SDIO_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_SDIO_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_SPI5_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI5RST))

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))
#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE()   (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI5LPEN))
#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI5LPEN))

#endif

#if defined(STM32F446xx)

#define __HAL_RCC_BKPSRAM_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPSRAMEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CCMDATARAMEN_CLK_ENABLE() do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CCMDATARAMEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_CRC_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOE_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOF_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_GPIOG_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE()   do { \
                                                 __IO uint32_t tmpreg = 0x00U; \
                                                 SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                   \
                                                 tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSEN);\
                                                 UNUSED(tmpreg); \
                                               } while(0U)
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE()   do { \
                                                      __IO uint32_t tmpreg = 0x00U; \
                                                      SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                        \
                                                      tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_OTGHSULPIEN);\
                                                      UNUSED(tmpreg); \
                                                    } while(0U)
#define __HAL_RCC_GPIOD_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#define __HAL_RCC_GPIOE_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#define __HAL_RCC_GPIOF_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN))
#define __HAL_RCC_GPIOG_CLK_DISABLE()           (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN))
#define __HAL_RCC_USB_OTG_HS_CLK_DISABLE()      (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE() (RCC->AHB1ENR &= ~(RCC_AHB1ENR_OTGHSULPIEN))
#define __HAL_RCC_BKPSRAM_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_BKPSRAMEN))
#define __HAL_RCC_CCMDATARAMEN_CLK_DISABLE()    (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CCMDATARAMEN))
#define __HAL_RCC_CRC_CLK_DISABLE()             (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))

#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) != RESET)
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()            ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_ENABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) != RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_ENABLED()  ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN)) != RESET)
#define __HAL_RCC_BKPSRAM_IS_CLK_ENABLED()          ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) != RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN))!= RESET)
#define __HAL_RCC_CRC_IS_CLK_ENABLED()              ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)

#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) == RESET)
#define __HAL_RCC_GPIOG_IS_CLK_DISABLED()           ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_IS_CLK_DISABLED()      ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSEN)) == RESET)
#define __HAL_RCC_USB_OTG_HS_ULPI_IS_CLK_DISABLED() ((RCC->AHB1ENR & (RCC_AHB1ENR_OTGHSULPIEN)) == RESET)
#define __HAL_RCC_BKPSRAM_IS_CLK_DISABLED()         ((RCC->AHB1ENR & (RCC_AHB1ENR_BKPSRAMEN)) == RESET)
#define __HAL_RCC_CCMDATARAMEN_IS_CLK_DISABLED()    ((RCC->AHB1ENR & (RCC_AHB1ENR_CCMDATARAMEN)) == RESET)
#define __HAL_RCC_CRC_IS_CLK_DISABLED()             ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)

#define __HAL_RCC_DCMI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_DCMIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DCMI_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_DCMIEN))
#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#define __HAL_RCC_RNG_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_RNG_CLK_DISABLE()   (RCC->AHB2ENR &= ~(RCC_AHB2ENR_RNGEN))

#define __HAL_RCC_DCMI_IS_CLK_ENABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) != RESET)
#define __HAL_RCC_DCMI_IS_CLK_DISABLED()       ((RCC->AHB2ENR & (RCC_AHB2ENR_DCMIEN)) == RESET)

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_RNG_IS_CLK_ENABLED()    ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) != RESET)
#define __HAL_RCC_RNG_IS_CLK_DISABLED()   ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) == RESET)

#define __HAL_RCC_FMC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_QSPI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)

#define __HAL_RCC_FMC_CLK_DISABLE()    (RCC->AHB3ENR &= ~(RCC_AHB3ENR_FMCEN))
#define __HAL_RCC_QSPI_CLK_DISABLE()   (RCC->AHB3ENR &= ~(RCC_AHB3ENR_QSPIEN))

#define __HAL_RCC_FMC_IS_CLK_ENABLED()   ((RCC->AHB3ENR & (RCC_AHB3ENR_FMCEN)) != RESET)
#define __HAL_RCC_QSPI_IS_CLK_ENABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) != RESET)

#define __HAL_RCC_FMC_IS_CLK_DISABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_FMCEN)) == RESET)
#define __HAL_RCC_QSPI_IS_CLK_DISABLED() ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) == RESET)

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM7_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM12_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM13_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SPDIFRX_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPDIFRXEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPDIFRXEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_USART3_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART4_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART5_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_FMPI2C1_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CAN1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CEC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CECEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CECEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DAC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_I2C3_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#define __HAL_RCC_TIM6_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __HAL_RCC_TIM7_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __HAL_RCC_TIM12_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN))
#define __HAL_RCC_TIM13_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN))
#define __HAL_RCC_TIM14_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN))
#define __HAL_RCC_SPDIFRX_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPDIFRXEN))
#define __HAL_RCC_USART3_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#define __HAL_RCC_UART4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __HAL_RCC_UART5_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))
#define __HAL_RCC_FMPI2C1_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_FMPI2C1EN))
#define __HAL_RCC_CAN1_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN1EN))
#define __HAL_RCC_CAN2_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN2EN))
#define __HAL_RCC_CEC_CLK_DISABLE()     (RCC->APB1ENR &= ~(RCC_APB1ENR_CECEN))
#define __HAL_RCC_DAC_CLK_DISABLE()     (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) != RESET)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) != RESET)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) != RESET)
#define __HAL_RCC_TIM13_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) != RESET)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) != RESET)
#define __HAL_RCC_SPDIFRX_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_SPDIFRXEN)) != RESET)
#define __HAL_RCC_USART3_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) != RESET)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) != RESET)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) != RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) != RESET)
#define __HAL_RCC_CAN1_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) != RESET)
#define __HAL_RCC_CAN2_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) != RESET)
#define __HAL_RCC_CEC_IS_CLK_ENABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_CECEN)) != RESET)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) != RESET)

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)
#define __HAL_RCC_TIM6_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) == RESET)
#define __HAL_RCC_TIM7_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) == RESET)
#define __HAL_RCC_TIM12_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) == RESET)
#define __HAL_RCC_TIM13_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) == RESET)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) == RESET)
#define __HAL_RCC_SPDIFRX_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_SPDIFRXEN)) == RESET)
#define __HAL_RCC_USART3_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) == RESET)
#define __HAL_RCC_UART4_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) == RESET)
#define __HAL_RCC_UART5_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) == RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) == RESET)
#define __HAL_RCC_CAN1_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) == RESET)
#define __HAL_RCC_CAN2_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) == RESET)
#define __HAL_RCC_CEC_IS_CLK_DISABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_CECEN)) == RESET)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) == RESET)

#define __HAL_RCC_TIM8_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_ADC3_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SAI1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SAI2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SDIO_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_TIM10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __HAL_RCC_TIM8_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN))
#define __HAL_RCC_ADC2_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC2EN))
#define __HAL_RCC_ADC3_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC3EN))
#define __HAL_RCC_SAI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SAI1EN))
#define __HAL_RCC_SAI2_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SAI2EN))

#define __HAL_RCC_SDIO_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) != RESET)
#define __HAL_RCC_TIM8_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) != RESET)
#define __HAL_RCC_ADC2_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) != RESET)
#define __HAL_RCC_ADC3_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) != RESET)
#define __HAL_RCC_SAI1_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) != RESET)
#define __HAL_RCC_SAI2_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SAI2EN)) != RESET)

#define __HAL_RCC_SDIO_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) == RESET)
#define __HAL_RCC_TIM8_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) == RESET)
#define __HAL_RCC_ADC2_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC2EN)) == RESET)
#define __HAL_RCC_ADC3_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC3EN)) == RESET)
#define __HAL_RCC_SAI1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) == RESET)
#define __HAL_RCC_SAI2_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SAI2EN)) == RESET)

#define __HAL_RCC_AHB1_FORCE_RESET()     (RCC->AHB1RSTR = 0x206010FFU)
#define __HAL_RCC_GPIOD_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_USB_OTG_HS_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_CRC_FORCE_RESET()      (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_GPIOD_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#define __HAL_RCC_GPIOE_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#define __HAL_RCC_GPIOF_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOGRST))
#define __HAL_RCC_USB_OTG_HS_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_OTGHRST))
#define __HAL_RCC_CRC_RELEASE_RESET()    (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#define __HAL_RCC_AHB2_FORCE_RESET()   (RCC->AHB2RSTR = 0x00000081U)
#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_RNG_FORCE_RESET()    (RCC->AHB2RSTR |= (RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_DCMI_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_DCMIRST))

#define __HAL_RCC_AHB2_RELEASE_RESET()  (RCC->AHB2RSTR = 0x00U)
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_RNG_RELEASE_RESET()  (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_DCMI_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_DCMIRST))

#define __HAL_RCC_AHB3_FORCE_RESET()   (RCC->AHB3RSTR = 0x00000003U)
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)

#define __HAL_RCC_FMC_FORCE_RESET()    (RCC->AHB3RSTR |= (RCC_AHB3RSTR_FMCRST))
#define __HAL_RCC_QSPI_FORCE_RESET()   (RCC->AHB3RSTR |= (RCC_AHB3RSTR_QSPIRST))

#define __HAL_RCC_FMC_RELEASE_RESET()    (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_FMCRST))
#define __HAL_RCC_QSPI_RELEASE_RESET()   (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_QSPIRST))

#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0x3FFFC9FFU)
#define __HAL_RCC_TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_SPDIFRX_FORCE_RESET()  (RCC->APB1RSTR |= (RCC_APB1RSTR_SPDIFRXRST))
#define __HAL_RCC_USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_FMPI2C1_FORCE_RESET()  (RCC->APB1RSTR |= (RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_CAN1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_CEC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_CECRST))
#define __HAL_RCC_DAC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))

#define __HAL_RCC_TIM2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_SPI3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_I2C3_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#define __HAL_RCC_TIM6_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST))
#define __HAL_RCC_SPDIFRX_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPDIFRXRST))
#define __HAL_RCC_USART3_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#define __HAL_RCC_UART4_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))
#define __HAL_RCC_FMPI2C1_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_CAN1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN2RST))
#define __HAL_RCC_CEC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CECRST))
#define __HAL_RCC_DAC_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))

#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0x00C77933U)
#define __HAL_RCC_TIM8_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM8RST))
#define __HAL_RCC_SAI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SAI1RST))
#define __HAL_RCC_SAI2_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SAI2RST))
#define __HAL_RCC_SDIO_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))

#define __HAL_RCC_SDIO_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_TIM8_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM8RST))
#define __HAL_RCC_SAI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SAI1RST))
#define __HAL_RCC_SAI2_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SAI2RST))

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_ENABLE()  (RCC->AHB1LPENR |= (RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()        (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM2LPEN))
#define __HAL_RCC_USB_OTG_HS_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSLPEN))
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_SLEEP_DISABLE() (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_OTGHSULPILPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()       (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))
#define __HAL_RCC_BKPSRAM_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_BKPSRAMLPEN))

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))
#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()   (RCC->AHB2LPENR |= (RCC_AHB2LPENR_RNGLPEN))
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()  (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_RNGLPEN))

#define __HAL_RCC_DCMI_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_DCMILPEN))
#define __HAL_RCC_DCMI_CLK_SLEEP_DISABLE() (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_DCMILPEN))

#define __HAL_RCC_FMC_CLK_SLEEP_ENABLE()   (RCC->AHB3LPENR |= (RCC_AHB3LPENR_FMCLPEN))
#define __HAL_RCC_QSPI_CLK_SLEEP_ENABLE()  (RCC->AHB3LPENR |= (RCC_AHB3LPENR_QSPILPEN))

#define __HAL_RCC_FMC_CLK_SLEEP_DISABLE()   (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_FMCLPEN))
#define __HAL_RCC_QSPI_CLK_SLEEP_DISABLE()  (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_QSPILPEN))

#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_SPDIFRX_CLK_SLEEP_ENABLE() (RCC->APB1LPENR |= (RCC_APB1LPENR_SPDIFRXLPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_ENABLE() (RCC->APB1LPENR |= (RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_CEC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_CECLPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM14LPEN))
#define __HAL_RCC_SPDIFRX_CLK_SLEEP_DISABLE()(RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPDIFRXLPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART3LPEN))
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART5LPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_DISABLE()(RCC->APB1LPENR &= ~(RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN2LPEN))
#define __HAL_RCC_CEC_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CECLPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))

#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC3LPEN))
#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SAI1LPEN))
#define __HAL_RCC_SAI2_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SAI2LPEN))
#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE() (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()(RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))

#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()(RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM8LPEN))
#define __HAL_RCC_ADC2_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC2LPEN))
#define __HAL_RCC_ADC3_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC3LPEN))
#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SAI1LPEN))
#define __HAL_RCC_SAI2_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SAI2LPEN))

#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_GPIOG_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#endif
#define __HAL_RCC_CRC_CLK_ENABLE()  do { \
                                         __IO uint32_t tmpreg = 0x00U; \
                                         SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                           \
                                         tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);\
                                         UNUSED(tmpreg); \
                                       } while(0U)
#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN))
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN))
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN))
#define __HAL_RCC_GPIOG_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN))
#endif
#define __HAL_RCC_CRC_CLK_DISABLE()          (RCC->AHB1ENR &= ~(RCC_AHB1ENR_CRCEN))

#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) != RESET)
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) != RESET)
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) != RESET)
#define __HAL_RCC_GPIOG_IS_CLK_ENABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) != RESET)
#endif
#define __HAL_RCC_CRC_IS_CLK_ENABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) != RESET)

#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIODEN)) == RESET)
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_IS_CLK_DISABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOEEN)) == RESET)
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_IS_CLK_DISABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOFEN)) == RESET)
#define __HAL_RCC_GPIOG_IS_CLK_DISABLED()     ((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOGEN)) == RESET)
#endif
#define __HAL_RCC_CRC_IS_CLK_DISABLED()       ((RCC->AHB1ENR & (RCC_AHB1ENR_CRCEN)) == RESET)

#if defined(STM32F423xx)
#define __HAL_RCC_AES_CLK_ENABLE()   do { \
                                          __IO uint32_t tmpreg = 0x00U; \
                                          SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN);\
                                            \
                                          tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_AESEN);\
                                          UNUSED(tmpreg); \
                                        } while(0U)

#define __HAL_RCC_AES_CLK_DISABLE()  (RCC->AHB2ENR &= ~(RCC_AHB2ENR_AESEN))
#endif

#define __HAL_RCC_RNG_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_RNG_CLK_DISABLE()   (RCC->AHB2ENR &= ~(RCC_AHB2ENR_RNGEN))

#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  do {(RCC->AHB2ENR |= (RCC_AHB2ENR_OTGFSEN));\
                                                __HAL_RCC_SYSCFG_CLK_ENABLE();\
                                              }while(0U)

#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() (RCC->AHB2ENR &= ~(RCC_AHB2ENR_OTGFSEN))

#if defined(STM32F423xx)
#define __HAL_RCC_AES_IS_CLK_ENABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_AESEN)) != RESET)
#define __HAL_RCC_AES_IS_CLK_DISABLED()       ((RCC->AHB2ENR & (RCC_AHB2ENR_AESEN)) == RESET)
#endif

#define __HAL_RCC_USB_OTG_FS_IS_CLK_ENABLED()  ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) != RESET)
#define __HAL_RCC_USB_OTG_FS_IS_CLK_DISABLED() ((RCC->AHB2ENR & (RCC_AHB2ENR_OTGFSEN)) == RESET)

#define __HAL_RCC_RNG_IS_CLK_ENABLED()         ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) != RESET)
#define __HAL_RCC_RNG_IS_CLK_DISABLED()        ((RCC->AHB2ENR & (RCC_AHB2ENR_RNGEN)) == RESET)

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_FSMC_CLK_ENABLE()    do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FSMCEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FSMCEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_QSPI_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_QSPIEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)

#define __HAL_RCC_FSMC_CLK_DISABLE()    (RCC->AHB3ENR &= ~(RCC_AHB3ENR_FSMCEN))
#define __HAL_RCC_QSPI_CLK_DISABLE()    (RCC->AHB3ENR &= ~(RCC_AHB3ENR_QSPIEN))
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_FSMC_IS_CLK_ENABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_FSMCEN)) != RESET)
#define __HAL_RCC_QSPI_IS_CLK_ENABLED()  ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) != RESET)

#define __HAL_RCC_FSMC_IS_CLK_DISABLED() ((RCC->AHB3ENR & (RCC_AHB3ENR_FSMCEN)) == RESET)
#define __HAL_RCC_QSPI_IS_CLK_DISABLED() ((RCC->AHB3ENR & (RCC_AHB3ENR_QSPIEN)) == RESET)
#endif

#define __HAL_RCC_TIM6_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM7_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM12_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM12EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM13_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM13EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM14_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM14EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_LPTIM1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_LPTIM1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#endif
#define __HAL_RCC_RTCAPB_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_RTCAPBEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_RTCAPBEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_USART3_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART3EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)

#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART4EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART5_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#endif

#define __HAL_RCC_FMPI2C1_CLK_ENABLE() do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_FMPI2C1EN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_CAN1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_CAN2_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_CLK_ENABLE()  do { \
                                          __IO uint32_t tmpreg = 0x00U; \
                                          SET_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN3EN);\
                                            \
                                          tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_CAN3EN);\
                                          UNUSED(tmpreg); \
                                        } while(0U)
#endif
#define __HAL_RCC_TIM2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C3_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C3EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DAC_CLK_ENABLE()    do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_DACEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART7_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART7EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART7EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_UART8_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB1ENR, RCC_APB1ENR_UART8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_UART8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#endif

#define __HAL_RCC_TIM2_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
#define __HAL_RCC_TIM3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
#define __HAL_RCC_TIM4_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN))
#define __HAL_RCC_TIM6_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM6EN))
#define __HAL_RCC_TIM7_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM7EN))
#define __HAL_RCC_TIM12_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM12EN))
#define __HAL_RCC_TIM13_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM13EN))
#define __HAL_RCC_TIM14_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM14EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_LPTIM1EN))
#endif
#define __HAL_RCC_RTCAPB_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_RTCAPBEN))
#define __HAL_RCC_SPI3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI3EN))
#define __HAL_RCC_USART3_CLK_DISABLE()  (RCC->APB1ENR &= ~(RCC_APB1ENR_USART3EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART4EN))
#define __HAL_RCC_UART5_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART5EN))
#endif
#define __HAL_RCC_I2C3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C3EN))
#define __HAL_RCC_FMPI2C1_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_FMPI2C1EN))
#define __HAL_RCC_CAN1_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN1EN))
#define __HAL_RCC_CAN2_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN2EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_CAN3EN))
#define __HAL_RCC_DAC_CLK_DISABLE()     (RCC->APB1ENR &= ~(RCC_APB1ENR_DACEN))
#define __HAL_RCC_UART7_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART7EN))
#define __HAL_RCC_UART8_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_UART8EN))
#endif

#define __HAL_RCC_TIM2_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
#define __HAL_RCC_TIM3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
#define __HAL_RCC_TIM4_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) != RESET)
#define __HAL_RCC_TIM6_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) != RESET)
#define __HAL_RCC_TIM7_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) != RESET)
#define __HAL_RCC_TIM12_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) != RESET)
#define __HAL_RCC_TIM13_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) != RESET)
#define __HAL_RCC_TIM14_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_LPTIM1EN)) != RESET)
#endif
#define __HAL_RCC_RTCAPB_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_RTCAPBEN)) != RESET)
#define __HAL_RCC_SPI3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) != RESET)
#define __HAL_RCC_USART3_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) != RESET)
#define __HAL_RCC_UART5_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) != RESET)
#endif
#define __HAL_RCC_I2C3_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) != RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) != RESET)
#define __HAL_RCC_CAN1_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN))!= RESET)
#define __HAL_RCC_CAN2_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN3EN)) != RESET)
#define __HAL_RCC_DAC_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) != RESET)
#define __HAL_RCC_UART7_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART7EN)) != RESET)
#define __HAL_RCC_UART8_IS_CLK_ENABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART8EN)) != RESET)
#endif

#define __HAL_RCC_TIM2_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
#define __HAL_RCC_TIM3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
#define __HAL_RCC_TIM4_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM4EN)) == RESET)
#define __HAL_RCC_TIM6_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM6EN)) == RESET)
#define __HAL_RCC_TIM7_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_TIM7EN)) == RESET)
#define __HAL_RCC_TIM12_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM12EN)) == RESET)
#define __HAL_RCC_TIM13_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM13EN)) == RESET)
#define __HAL_RCC_TIM14_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM14EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_LPTIM1EN)) == RESET)
#endif
#define __HAL_RCC_RTCAPB_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_RTCAPBEN)) == RESET)
#define __HAL_RCC_SPI3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_SPI3EN)) == RESET)
#define __HAL_RCC_USART3_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_USART3EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART4EN)) == RESET)
#define __HAL_RCC_UART5_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART5EN)) == RESET)
#endif
#define __HAL_RCC_I2C3_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_I2C3EN)) == RESET)
#define __HAL_RCC_FMPI2C1_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_FMPI2C1EN)) == RESET)
#define __HAL_RCC_CAN1_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN1EN)) == RESET)
#define __HAL_RCC_CAN2_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_CAN2EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_CAN3EN)) == RESET)
#define __HAL_RCC_DAC_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_DACEN)) == RESET)
#define __HAL_RCC_UART7_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART7EN)) == RESET)
#define __HAL_RCC_UART8_IS_CLK_DISABLED()  ((RCC->APB1ENR & (RCC_APB1ENR_UART8EN)) == RESET)
#endif

#define __HAL_RCC_TIM8_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_UART9EN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_UART9EN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_UART10_CLK_ENABLE()  do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_UART10EN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_UART10EN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#endif
#define __HAL_RCC_SDIO_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SDIOEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI4_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI4EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_EXTIT_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_EXTITEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_EXTITEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_TIM10_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM10EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI5_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI5EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_CLK_ENABLE()   do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SAI1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#endif
#define __HAL_RCC_DFSDM1_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_DFSDM1EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_DFSDM1EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_CLK_ENABLE() do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->APB2ENR, RCC_APB2ENR_DFSDM2EN);\
                                             \
                                           tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_DFSDM2EN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#endif

#define __HAL_RCC_TIM8_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM8EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_UART9EN))
#define __HAL_RCC_UART10_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_UART10EN))
#endif
#define __HAL_RCC_SDIO_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SDIOEN))
#define __HAL_RCC_SPI4_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI4EN))
#define __HAL_RCC_EXTIT_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_EXTITEN))
#define __HAL_RCC_TIM10_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM10EN))
#define __HAL_RCC_SPI5_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI5EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_SAI1EN))
#endif
#define __HAL_RCC_DFSDM1_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_DFSDM1EN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_DFSDM2EN))
#endif

#define __HAL_RCC_TIM8_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_UART9EN)) != RESET)
#define __HAL_RCC_UART10_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_UART10EN)) != RESET)
#endif
#define __HAL_RCC_SDIO_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) != RESET)
#define __HAL_RCC_SPI4_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) != RESET)
#define __HAL_RCC_EXTIT_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_EXTITEN)) != RESET)
#define __HAL_RCC_TIM10_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) != RESET)
#define __HAL_RCC_SPI5_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) != RESET)
#endif
#define __HAL_RCC_DFSDM1_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_DFSDM1EN)) != RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_IS_CLK_ENABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_DFSDM2EN)) != RESET)
#endif

#define __HAL_RCC_TIM8_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_TIM8EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_UART9EN)) == RESET)
#define __HAL_RCC_UART10_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_UART10EN)) == RESET)
#endif
#define __HAL_RCC_SDIO_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SDIOEN)) == RESET)
#define __HAL_RCC_SPI4_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SPI4EN)) == RESET)
#define __HAL_RCC_EXTIT_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_EXTITEN)) == RESET)
#define __HAL_RCC_TIM10_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_TIM10EN)) == RESET)
#define __HAL_RCC_SPI5_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SPI5EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_SAI1EN)) == RESET)
#endif
#define __HAL_RCC_DFSDM1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_DFSDM1EN)) == RESET)
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_DFSDM2EN)) == RESET)
#endif

#if defined (STM32F412Zx) || defined(STM32F413xx) || defined (STM32F423xx)
#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x006010FFU)
#endif
#if defined (STM32F412Cx)
#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x00601087U)
#endif
#if defined (STM32F412Vx)
#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x0060109FU)
#endif
#if defined (STM32F412Rx)
#define __HAL_RCC_AHB1_FORCE_RESET()    (RCC->AHB1RSTR = 0x0060108FU)
#endif
#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIODRST))
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOERST))
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOGRST))
#endif
#define __HAL_RCC_CRC_FORCE_RESET()      (RCC->AHB1RSTR |= (RCC_AHB1RSTR_CRCRST))

#if defined(STM32F412Rx) || defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOD_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST))
#endif
#if defined(STM32F412Vx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOE_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOERST))
#endif
#if defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_GPIOF_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOFRST))
#define __HAL_RCC_GPIOG_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOGRST))
#endif
#define __HAL_RCC_CRC_RELEASE_RESET()    (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_CRCRST))

#if defined(STM32F423xx)
#define __HAL_RCC_AHB2_FORCE_RESET()   (RCC->AHB2RSTR = 0x000000D0U)
#define __HAL_RCC_AES_FORCE_RESET()    (RCC->AHB2RSTR |= (RCC_AHB2RSTR_AESRST))
#define __HAL_RCC_AES_RELEASE_RESET()  (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_AESRST))
#else
#define __HAL_RCC_AHB2_FORCE_RESET()   (RCC->AHB2RSTR = 0x000000C0U)
#endif
#define __HAL_RCC_AHB2_RELEASE_RESET() (RCC->AHB2RSTR = 0x00U)

#define __HAL_RCC_USB_OTG_FS_FORCE_RESET()   (RCC->AHB2RSTR |= (RCC_AHB2RSTR_OTGFSRST))
#define __HAL_RCC_USB_OTG_FS_RELEASE_RESET() (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_OTGFSRST))

#define __HAL_RCC_RNG_FORCE_RESET()    (RCC->AHB2RSTR |= (RCC_AHB2RSTR_RNGRST))
#define __HAL_RCC_RNG_RELEASE_RESET()  (RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_RNGRST))

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_AHB3_FORCE_RESET()   (RCC->AHB3RSTR = 0x00000003U)
#define __HAL_RCC_AHB3_RELEASE_RESET() (RCC->AHB3RSTR = 0x00U)

#define __HAL_RCC_FSMC_FORCE_RESET()    (RCC->AHB3RSTR |= (RCC_AHB3RSTR_FSMCRST))
#define __HAL_RCC_QSPI_FORCE_RESET()   (RCC->AHB3RSTR |= (RCC_AHB3RSTR_QSPIRST))

#define __HAL_RCC_FSMC_RELEASE_RESET()    (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_FSMCRST))
#define __HAL_RCC_QSPI_RELEASE_RESET()   (RCC->AHB3RSTR &= ~(RCC_AHB3RSTR_QSPIRST))
#endif
#if defined(STM32F412Cx)
#define __HAL_RCC_AHB3_FORCE_RESET()
#define __HAL_RCC_AHB3_RELEASE_RESET()

#define __HAL_RCC_FSMC_FORCE_RESET()
#define __HAL_RCC_QSPI_FORCE_RESET()

#define __HAL_RCC_FSMC_RELEASE_RESET()
#define __HAL_RCC_QSPI_RELEASE_RESET()
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0xFFFECBFFU)
#endif
#if defined (STM32F412Zx) || defined (STM32F412Vx) || defined (STM32F412Rx) || defined (STM32F412Cx)
#define __HAL_RCC_APB1_FORCE_RESET()     (RCC->APB1RSTR = 0x17E6C9FFU)
#endif
#define __HAL_RCC_TIM2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_TIM6_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM14RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_LPTIM1RST))
#endif
#define __HAL_RCC_SPI3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_USART3_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART3RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART5RST))
#endif
#define __HAL_RCC_I2C3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C3RST))
#define __HAL_RCC_FMPI2C1_FORCE_RESET()  (RCC->APB1RSTR |= (RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_CAN1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN2RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_CAN3RST))
#define __HAL_RCC_DAC_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_DACRST))
#define __HAL_RCC_UART7_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART7RST))
#define __HAL_RCC_UART8_FORCE_RESET()    (RCC->APB1RSTR |= (RCC_APB1RSTR_UART8RST))
#endif

#define __HAL_RCC_TIM2_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
#define __HAL_RCC_TIM3_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
#define __HAL_RCC_TIM4_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST))
#define __HAL_RCC_TIM6_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM6RST))
#define __HAL_RCC_TIM7_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM7RST))
#define __HAL_RCC_TIM12_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM12RST))
#define __HAL_RCC_TIM13_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM13RST))
#define __HAL_RCC_TIM14_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM14RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_LPTIM1RST))
#endif
#define __HAL_RCC_SPI3_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI3RST))
#define __HAL_RCC_USART3_RELEASE_RESET()  (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART3RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART4RST))
#define __HAL_RCC_UART5_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART5RST))
#endif
#define __HAL_RCC_I2C3_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C3RST))
#define __HAL_RCC_FMPI2C1_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_FMPI2C1RST))
#define __HAL_RCC_CAN1_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN1RST))
#define __HAL_RCC_CAN2_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN2RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_CAN3RST))
#define __HAL_RCC_DAC_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_DACRST))
#define __HAL_RCC_UART7_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART7RST))
#define __HAL_RCC_UART8_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_UART8RST))
#endif

#if defined(STM32F413xx)|| defined(STM32F423xx)
#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0x035779F3U)
#endif
#if defined (STM32F412Zx) || defined (STM32F412Vx) || defined (STM32F412Rx) || defined (STM32F412Cx)
#define __HAL_RCC_APB2_FORCE_RESET()     (RCC->APB2RSTR = 0x01177933U)
#endif
#define __HAL_RCC_TIM8_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM8RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_UART9RST))
#define __HAL_RCC_UART10_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_UART10RST))
#endif
#define __HAL_RCC_SDIO_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_SPI5_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI5RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SAI1RST))
#endif
#define __HAL_RCC_DFSDM1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_DFSDM1RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_DFSDM2RST))
#endif

#define __HAL_RCC_TIM8_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM8RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_UART9RST))
#define __HAL_RCC_UART10_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_UART10RST))
#endif
#define __HAL_RCC_SDIO_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SDIORST))
#define __HAL_RCC_SPI4_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI4RST))
#define __HAL_RCC_TIM10_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM10RST))
#define __HAL_RCC_SPI5_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI5RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SAI1RST))
#endif
#define __HAL_RCC_DFSDM1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_DFSDM1RST))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_DFSDM2RST))
#endif

#define __HAL_RCC_GPIOD_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_ENABLE()        (RCC->AHB1LPENR |= (RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM1LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SRAM2_CLK_SLEEP_ENABLE()      (RCC->AHB1LPENR |= (RCC_AHB1LPENR_SRAM2LPEN))
#endif

#define __HAL_RCC_GPIOD_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIODLPEN))
#define __HAL_RCC_GPIOE_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOELPEN))
#define __HAL_RCC_GPIOF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOFLPEN))
#define __HAL_RCC_GPIOG_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOGLPEN))
#define __HAL_RCC_CRC_CLK_SLEEP_DISABLE()       (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_CRCLPEN))
#define __HAL_RCC_FLITF_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_FLITFLPEN))
#define __HAL_RCC_SRAM1_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM1LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SRAM2_CLK_SLEEP_DISABLE()     (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_SRAM2LPEN))
#endif

#if defined(STM32F423xx)
#define __HAL_RCC_AES_CLK_SLEEP_ENABLE()      (RCC->AHB2LPENR |= (RCC_AHB2LPENR_AESLPEN))
#define __HAL_RCC_AES_CLK_SLEEP_DISABLE()     (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_AESLPEN))
#endif

#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_ENABLE()  (RCC->AHB2LPENR |= (RCC_AHB2LPENR_OTGFSLPEN))
#define __HAL_RCC_USB_OTG_FS_CLK_SLEEP_DISABLE()   (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_OTGFSLPEN))

#define __HAL_RCC_RNG_CLK_SLEEP_ENABLE()   (RCC->AHB2LPENR |= (RCC_AHB2LPENR_RNGLPEN))
#define __HAL_RCC_RNG_CLK_SLEEP_DISABLE()  (RCC->AHB2LPENR &= ~(RCC_AHB2LPENR_RNGLPEN))

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_FSMC_CLK_SLEEP_ENABLE()   (RCC->AHB3LPENR |= (RCC_AHB3LPENR_FSMCLPEN))
#define __HAL_RCC_QSPI_CLK_SLEEP_ENABLE()  (RCC->AHB3LPENR |= (RCC_AHB3LPENR_QSPILPEN))

#define __HAL_RCC_FSMC_CLK_SLEEP_DISABLE()   (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_FSMCLPEN))
#define __HAL_RCC_QSPI_CLK_SLEEP_DISABLE()  (RCC->AHB3LPENR &= ~(RCC_AHB3LPENR_QSPILPEN))
#endif

#define __HAL_RCC_TIM2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_TIM6_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM14LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_LPTIM1LPEN))
#endif
#define __HAL_RCC_RTCAPB_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_RTCAPBLPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_USART3LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART5LPEN))
#endif
#define __HAL_RCC_I2C3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C3LPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_ENABLE() (RCC->APB1LPENR |= (RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN2LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_CAN3LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_UART7_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART7LPEN))
#define __HAL_RCC_UART8_CLK_SLEEP_ENABLE()   (RCC->APB1LPENR |= (RCC_APB1LPENR_UART8LPEN))
#endif

#define __HAL_RCC_TIM2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM2LPEN))
#define __HAL_RCC_TIM3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM3LPEN))
#define __HAL_RCC_TIM4_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM4LPEN))
#define __HAL_RCC_TIM6_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM6LPEN))
#define __HAL_RCC_TIM7_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM7LPEN))
#define __HAL_RCC_TIM12_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM12LPEN))
#define __HAL_RCC_TIM13_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM13LPEN))
#define __HAL_RCC_TIM14_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM14LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_LPTIM1_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_LPTIM1LPEN))
#endif
#define __HAL_RCC_RTCAPB_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_RTCAPBLPEN))
#define __HAL_RCC_SPI3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI3LPEN))
#define __HAL_RCC_USART3_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART3LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART4_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART4LPEN))
#define __HAL_RCC_UART5_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART5LPEN))
#endif
#define __HAL_RCC_I2C3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C3LPEN))
#define __HAL_RCC_FMPI2C1_CLK_SLEEP_DISABLE()(RCC->APB1LPENR &= ~(RCC_APB1LPENR_FMPI2C1LPEN))
#define __HAL_RCC_CAN1_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN1LPEN))
#define __HAL_RCC_CAN2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN2LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_CAN3_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_CAN3LPEN))
#define __HAL_RCC_DAC_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_DACLPEN))
#define __HAL_RCC_UART7_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART7LPEN))
#define __HAL_RCC_UART8_CLK_SLEEP_DISABLE()  (RCC->APB1LPENR &= ~(RCC_APB1LPENR_UART8LPEN))
#endif

#define __HAL_RCC_TIM8_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM8LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_UART9LPEN))
#define __HAL_RCC_UART10_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_UART10LPEN))
#endif
#define __HAL_RCC_SDIO_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_EXTIT_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_EXTITLPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI5LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SAI1LPEN))
#endif
#define __HAL_RCC_DFSDM1_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_DFSDM1LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_DFSDM2LPEN))
#endif

#define __HAL_RCC_TIM8_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM8LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_UART9_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_UART9LPEN))
#define __HAL_RCC_UART10_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_UART10LPEN))
#endif
#define __HAL_RCC_SDIO_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SDIOLPEN))
#define __HAL_RCC_SPI4_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI4LPEN))
#define __HAL_RCC_EXTIT_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_EXTITLPEN))
#define __HAL_RCC_TIM10_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM10LPEN))
#define __HAL_RCC_SPI5_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI5LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_SAI1_CLK_SLEEP_DISABLE()    (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SAI1LPEN))
#endif
#define __HAL_RCC_DFSDM1_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_DFSDM1LPEN))
#if defined(STM32F413xx) || defined(STM32F423xx)
#define __HAL_RCC_DFSDM2_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_DFSDM2LPEN))
#endif

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__,__PLLR__)  \
  (RCC->PLLCFGR = ((__RCC_PLLSource__) | (__PLLM__)                   | \
                   ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos)                      | \
                   ((((__PLLP__) >> 1U) -1U) << RCC_PLLCFGR_PLLP_Pos)          | \
                   ((__PLLQ__) << RCC_PLLCFGR_PLLQ_Pos)                      | \
                   ((__PLLR__) << RCC_PLLCFGR_PLLR_Pos)))
#else

#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__)     \
  (RCC->PLLCFGR = (0x20000000U | (__RCC_PLLSource__) | (__PLLM__)| \
                   ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos)                | \
                   ((((__PLLP__) >> 1U) -1U) << RCC_PLLCFGR_PLLP_Pos)    | \
                   ((__PLLQ__) << RCC_PLLCFGR_PLLQ_Pos)))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_PLLI2S_ENABLE() (*(__IO uint32_t *) RCC_CR_PLLI2SON_BB = ENABLE)
#define __HAL_RCC_PLLI2S_DISABLE() (*(__IO uint32_t *) RCC_CR_PLLI2SON_BB = DISABLE)

#endif
#if defined(STM32F446xx)

#define __HAL_RCC_PLLI2S_CONFIG(__PLLI2SM__, __PLLI2SN__, __PLLI2SP__, __PLLI2SQ__, __PLLI2SR__)    \
  (RCC->PLLI2SCFGR = ((__PLLI2SM__)                                   |\
                      ((__PLLI2SN__) << RCC_PLLI2SCFGR_PLLI2SN_Pos)             |\
                      ((((__PLLI2SP__) >> 1U) -1U) << RCC_PLLI2SCFGR_PLLI2SP_Pos) |\
                      ((__PLLI2SQ__) << RCC_PLLI2SCFGR_PLLI2SQ_Pos)             |\
                      ((__PLLI2SR__) << RCC_PLLI2SCFGR_PLLI2SR_Pos)))
#elif defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
      defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_PLLI2S_CONFIG(__PLLI2SM__, __PLLI2SN__, __PLLI2SQ__, __PLLI2SR__)    \
  (RCC->PLLI2SCFGR = ((__PLLI2SM__)                                   |\
                      ((__PLLI2SN__) << RCC_PLLI2SCFGR_PLLI2SN_Pos)             |\
                      ((__PLLI2SQ__) << RCC_PLLI2SCFGR_PLLI2SQ_Pos)             |\
                      ((__PLLI2SR__) << RCC_PLLI2SCFGR_PLLI2SR_Pos)))
#else

#define __HAL_RCC_PLLI2S_CONFIG(__PLLI2SN__, __PLLI2SR__)                                                    \
  (RCC->PLLI2SCFGR = (((__PLLI2SN__) << RCC_PLLI2SCFGR_PLLI2SN_Pos)  |\
                      ((__PLLI2SR__) << RCC_PLLI2SCFGR_PLLI2SR_Pos)))
#endif

#if defined(STM32F411xE)

#define __HAL_RCC_PLLI2S_I2SCLK_CONFIG(__PLLI2SM__, __PLLI2SN__, __PLLI2SR__) (RCC->PLLI2SCFGR = ((__PLLI2SM__)                                                       |\
                                                                               ((__PLLI2SN__) << RCC_PLLI2SCFGR_PLLI2SN_Pos)             |\
                                                                               ((__PLLI2SR__) << RCC_PLLI2SCFGR_PLLI2SR_Pos)))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLI2S_SAICLK_CONFIG(__PLLI2SN__, __PLLI2SQ__, __PLLI2SR__) (RCC->PLLI2SCFGR = ((__PLLI2SN__) << 6U)  |\
                                                                               ((__PLLI2SQ__) << 24U) |\
                                                                               ((__PLLI2SR__) << 28U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLSAI_ENABLE() (*(__IO uint32_t *) RCC_CR_PLLSAION_BB = ENABLE)
#define __HAL_RCC_PLLSAI_DISABLE() (*(__IO uint32_t *) RCC_CR_PLLSAION_BB = DISABLE)

#if defined(STM32F446xx)

#define __HAL_RCC_PLLSAI_CONFIG(__PLLSAIM__, __PLLSAIN__, __PLLSAIP__, __PLLSAIQ__, __PLLSAIR__)     \
  (RCC->PLLSAICFGR = ((__PLLSAIM__)                                   | \
                      ((__PLLSAIN__) << RCC_PLLSAICFGR_PLLSAIN_Pos)             | \
                      ((((__PLLSAIP__) >> 1U) -1U) << RCC_PLLSAICFGR_PLLSAIP_Pos) | \
                      ((__PLLSAIQ__) << RCC_PLLSAICFGR_PLLSAIQ_Pos)))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLSAI_CONFIG(__PLLSAIN__, __PLLSAIP__, __PLLSAIQ__, __PLLSAIR__) \
  (RCC->PLLSAICFGR = (((__PLLSAIN__) << RCC_PLLSAICFGR_PLLSAIN_Pos)             |\
                      ((((__PLLSAIP__) >> 1U) -1U) << RCC_PLLSAICFGR_PLLSAIP_Pos) |\
                      ((__PLLSAIQ__) << RCC_PLLSAICFGR_PLLSAIQ_Pos)             |\
                      ((__PLLSAIR__) << RCC_PLLSAICFGR_PLLSAIR_Pos)))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)

#define __HAL_RCC_PLLSAI_CONFIG(__PLLSAIN__, __PLLSAIQ__, __PLLSAIR__)                                        \
  (RCC->PLLSAICFGR = (((__PLLSAIN__) << RCC_PLLSAICFGR_PLLSAIN_Pos)  | \
                      ((__PLLSAIQ__) << RCC_PLLSAICFGR_PLLSAIQ_Pos)                      | \
                      ((__PLLSAIR__) << RCC_PLLSAICFGR_PLLSAIR_Pos)))
#endif

#endif

#if defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_PLLI2S_PLLSAICLKDIVR_CONFIG(__PLLI2SDivR__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLI2SDIVR, (__PLLI2SDivR__)-1U))

#define __HAL_RCC_PLL_PLLSAICLKDIVR_CONFIG(__PLLDivR__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLDIVR, ((__PLLDivR__)-1U)<<8U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)  || defined(STM32F446xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLI2S_PLLSAICLKDIVQ_CONFIG(__PLLI2SDivQ__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLI2SDIVQ, (__PLLI2SDivQ__)-1U))

#define __HAL_RCC_PLLSAI_PLLSAICLKDIVQ_CONFIG(__PLLSAIDivQ__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVQ, ((__PLLSAIDivQ__)-1U)<<8U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLSAI_PLLSAICLKDIVR_CONFIG(__PLLSAIDivR__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVR, (__PLLSAIDivR__)))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F469xx) ||\
    defined(STM32F479xx)

#define __HAL_RCC_I2S_CONFIG(__SOURCE__) (MODIFY_REG(RCC->CFGR, RCC_CFGR_I2SSRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_I2SSRC)))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI1ASRC, (__SOURCE__)))

#define __HAL_RCC_SAI_BLOCKBCLKSOURCE_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI1BSRC, (__SOURCE__)))
#endif

#if defined(STM32F446xx)

#define __HAL_RCC_SAI1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI1SRC, (__SOURCE__)))

#define __HAL_RCC_GET_SAI1_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_SAI1SRC))

#define __HAL_RCC_SAI2_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI2SRC, (__SOURCE__)))

#define __HAL_RCC_GET_SAI2_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_SAI2SRC))

#define __HAL_RCC_I2S_APB1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_I2S1SRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_APB1_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_I2S1SRC))

#define __HAL_RCC_I2S_APB2_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_I2S2SRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_APB2_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_I2S2SRC))

#define __HAL_RCC_CEC_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_CECSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_CEC_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_CECSEL))

#define __HAL_RCC_FMPI2C1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_FMPI2C1_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL))

#define __HAL_RCC_CLK48_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_CK48MSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_CLK48_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_CK48MSEL))

#define __HAL_RCC_SDIO_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_SDIOSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_SDIO_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_SDIOSEL))

#define __HAL_RCC_SPDIFRX_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_SPDIFRXSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_SPDIFRX_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_SPDIFRXSEL))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_CLK48_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_CK48MSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_CLK48_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_CK48MSEL))

#define __HAL_RCC_SDIO_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SDIOSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_SDIO_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_SDIOSEL))

#define __HAL_RCC_DSI_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_DSISEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_DSI_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_DSISEL))

#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_DFSDM1_CONFIG(__DFSDM1_CLKSOURCE__)  MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1SEL, (__DFSDM1_CLKSOURCE__))

#define __HAL_RCC_GET_DFSDM1_SOURCE() ((uint32_t)(READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1SEL)))

#define __HAL_RCC_DFSDM1AUDIO_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1ASEL, (__SOURCE__)))

#define __HAL_RCC_GET_DFSDM1AUDIO_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1ASEL))

#if defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_DFSDM2_CONFIG(__DFSDM2_CLKSOURCE__)  MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1SEL, (__DFSDM2_CLKSOURCE__))

#define __HAL_RCC_GET_DFSDM2_SOURCE() ((uint32_t)(READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM1SEL)))

#define __HAL_RCC_DFSDM2AUDIO_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM2ASEL, (__SOURCE__)))

#define __HAL_RCC_GET_DFSDM2AUDIO_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_CKDFSDM2ASEL))

#define __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI1ASRC, (__SOURCE__)))

#define __HAL_RCC_GET_SAI_BLOCKA_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_SAI1ASRC))

#define __HAL_RCC_SAI_BLOCKBCLKSOURCE_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_SAI1BSRC, (__SOURCE__)))

#define __HAL_RCC_GET_SAI_BLOCKB_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_SAI1BSRC))

#define __HAL_RCC_LPTIM1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_LPTIM1SEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_LPTIM1_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_LPTIM1SEL))
#endif

#define __HAL_RCC_I2S_APB1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_I2S1SRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_APB1_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_I2S1SRC))

#define __HAL_RCC_I2S_APB2_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_I2S2SRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_APB2_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_I2S2SRC))

#define __HAL_RCC_PLL_I2S_CONFIG(__SOURCE__) (*(__IO uint32_t *) RCC_PLLI2SCFGR_PLLI2SSRC_BB = (__SOURCE__))

#define __HAL_RCC_FMPI2C1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_FMPI2C1_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL))

#define __HAL_RCC_CLK48_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_CK48MSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_CLK48_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_CK48MSEL))

#define __HAL_RCC_SDIO_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_SDIOSEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_SDIO_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_SDIOSEL))

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define __HAL_RCC_I2S_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR, RCC_DCKCFGR_I2SSRC, (__SOURCE__)))

#define __HAL_RCC_GET_I2S_SOURCE() (READ_BIT(RCC->DCKCFGR, RCC_DCKCFGR_I2SSRC))

#define __HAL_RCC_FMPI2C1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_FMPI2C1_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_FMPI2C1SEL))

#define __HAL_RCC_LPTIM1_CONFIG(__SOURCE__) (MODIFY_REG(RCC->DCKCFGR2, RCC_DCKCFGR2_LPTIM1SEL, (uint32_t)(__SOURCE__)))

#define __HAL_RCC_GET_LPTIM1_SOURCE() (READ_BIT(RCC->DCKCFGR2, RCC_DCKCFGR2_LPTIM1SEL))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define __HAL_RCC_TIMCLKPRESCALER(__PRESC__) (*(__IO uint32_t *) RCC_DCKCFGR_TIMPRE_BB = (__PRESC__))

#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_RCC_PLLSAI_ENABLE_IT() (RCC->CIR |= (RCC_CIR_PLLSAIRDYIE))

#define __HAL_RCC_PLLSAI_DISABLE_IT() (RCC->CIR &= ~(RCC_CIR_PLLSAIRDYIE))

#define __HAL_RCC_PLLSAI_CLEAR_IT() (RCC->CIR |= (RCC_CIR_PLLSAIRDYF))

#define __HAL_RCC_PLLSAI_GET_IT() ((RCC->CIR & (RCC_CIR_PLLSAIRDYIE)) == (RCC_CIR_PLLSAIRDYIE))

#define __HAL_RCC_PLLSAI_GET_FLAG() ((RCC->CR & (RCC_CR_PLLSAIRDY)) == (RCC_CR_PLLSAIRDY))

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define __HAL_RCC_MCO1_ENABLE() (*(__IO uint32_t *) RCC_CFGR_MCO1EN_BB = ENABLE)
#define __HAL_RCC_MCO1_DISABLE() (*(__IO uint32_t *) RCC_CFGR_MCO1EN_BB = DISABLE)

#define __HAL_RCC_MCO2_ENABLE() (*(__IO uint32_t *) RCC_CFGR_MCO2EN_BB = ENABLE)
#define __HAL_RCC_MCO2_DISABLE() (*(__IO uint32_t *) RCC_CFGR_MCO2EN_BB = DISABLE)

#endif

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);

uint32_t HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
void HAL_RCCEx_SelectLSEMode(uint8_t Mode);
#endif
#if defined(RCC_PLLI2S_SUPPORT)
HAL_StatusTypeDef HAL_RCCEx_EnablePLLI2S(RCC_PLLI2SInitTypeDef  *PLLI2SInit);
HAL_StatusTypeDef HAL_RCCEx_DisablePLLI2S(void);
#endif
#if defined(RCC_PLLSAI_SUPPORT)
HAL_StatusTypeDef HAL_RCCEx_EnablePLLSAI(RCC_PLLSAIInitTypeDef  *PLLSAIInit);
HAL_StatusTypeDef HAL_RCCEx_DisablePLLSAI(void);
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define RCC_PLLSAION_BIT_NUMBER       0x1CU
#define RCC_CR_PLLSAION_BB            (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32U) + (RCC_PLLSAION_BIT_NUMBER * 4U))

#define PLLSAI_TIMEOUT_VALUE          2U
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_PLLI2SON_BIT_NUMBER    0x1AU
#define RCC_CR_PLLI2SON_BB         (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32U) + (RCC_PLLI2SON_BIT_NUMBER * 4U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F401xC) ||\
    defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_DCKCFGR_OFFSET            (RCC_OFFSET + 0x8CU)
#define RCC_TIMPRE_BIT_NUMBER          0x18U
#define RCC_DCKCFGR_TIMPRE_BB         (PERIPH_BB_BASE + (RCC_DCKCFGR_OFFSET * 32U) + (RCC_TIMPRE_BIT_NUMBER * 4U))
#endif

#define RCC_CFGR_OFFSET            (RCC_OFFSET + 0x08U)
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx)

#define RCC_I2SSRC_BIT_NUMBER      0x17U
#define RCC_CFGR_I2SSRC_BB         (PERIPH_BB_BASE + (RCC_CFGR_OFFSET * 32U) + (RCC_I2SSRC_BIT_NUMBER * 4U))

#define PLLI2S_TIMEOUT_VALUE       2U
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)

#define RCC_PLLI2SCFGR_OFFSET         (RCC_OFFSET + 0x84U)

#define RCC_PLLI2SSRC_BIT_NUMBER      0x16U
#define RCC_PLLI2SCFGR_PLLI2SSRC_BB         (PERIPH_BB_BASE\
                                             + (RCC_PLLI2SCFGR_OFFSET * 32U) + (RCC_PLLI2SSRC_BIT_NUMBER * 4U))

#define PLLI2S_TIMEOUT_VALUE          2U
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define RCC_MCO1EN_BIT_NUMBER      0x8U
#define RCC_CFGR_MCO1EN_BB         (PERIPH_BB_BASE + (RCC_CFGR_OFFSET * 32U) + (RCC_MCO1EN_BIT_NUMBER * 4U))

#define RCC_MCO2EN_BIT_NUMBER      0x9U
#define RCC_CFGR_MCO2EN_BB         (PERIPH_BB_BASE + (RCC_CFGR_OFFSET * 32U) + (RCC_MCO2EN_BIT_NUMBER * 4U))
#endif

#define PLL_TIMEOUT_VALUE          2U

#define IS_RCC_PLLN_VALUE(VALUE) ((50U <= (VALUE)) && ((VALUE) <= 432U))
#define IS_RCC_PLLI2SN_VALUE(VALUE) ((50U <= (VALUE)) && ((VALUE) <= 432U))

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x0000007FU))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x00000007U))
#endif

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x0000000FU))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x0000001FU))
#endif

#if defined(STM32F446xx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x00000FFFU))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x000001FFU))
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x000003FFU))
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_RCC_PERIPHCLOCK(SELECTION) ((1U <= (SELECTION)) && ((SELECTION) <= 0x00007FFFU))
#endif

#define IS_RCC_PLLI2SR_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 7U))

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_RCC_PLLI2SQ_VALUE(VALUE)     ((2U <= (VALUE)) && ((VALUE) <= 15U))

#define IS_RCC_PLLSAIN_VALUE(VALUE)     ((50U <= (VALUE)) && ((VALUE) <= 432U))

#define IS_RCC_PLLSAIQ_VALUE(VALUE)     ((2U <= (VALUE)) && ((VALUE) <= 15U))

#define IS_RCC_PLLSAIR_VALUE(VALUE)     ((2U <= (VALUE)) && ((VALUE) <= 7U))

#define IS_RCC_PLLSAI_DIVQ_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 32U))

#define IS_RCC_PLLI2S_DIVQ_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 32U))

#define IS_RCC_PLLSAI_DIVR_VALUE(VALUE) (((VALUE) == RCC_PLLSAIDIVR_2)  ||\
                                         ((VALUE) == RCC_PLLSAIDIVR_4)  ||\
                                         ((VALUE) == RCC_PLLSAIDIVR_8)  ||\
                                         ((VALUE) == RCC_PLLSAIDIVR_16))
#endif

#if defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define IS_RCC_PLLI2SM_VALUE(VALUE)   ((2U <= (VALUE)) && ((VALUE) <= 63U))

#define IS_RCC_LSE_MODE(MODE)           (((MODE) == RCC_LSE_LOWPOWER_MODE) ||\
                                         ((MODE) == RCC_LSE_HIGHDRIVE_MODE))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_RCC_PLLR_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 7U))

#define IS_RCC_LSE_MODE(MODE)           (((MODE) == RCC_LSE_LOWPOWER_MODE) ||\
                                         ((MODE) == RCC_LSE_HIGHDRIVE_MODE))

#define IS_RCC_FMPI2C1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_FMPI2C1CLKSOURCE_PCLK1)    ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_SYSCLK) ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_HSI))

#define IS_RCC_LPTIM1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_LPTIM1CLKSOURCE_PCLK1) ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_HSI) ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSI) ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_I2SAPBCLKSOURCE(SOURCE)      (((SOURCE) == RCC_I2SAPBCLKSOURCE_PLLR)    ||\
                                             ((SOURCE) == RCC_I2SAPBCLKSOURCE_EXT)    ||\
                                             ((SOURCE) == RCC_I2SAPBCLKSOURCE_PLLSRC))
#endif

#if defined(STM32F446xx)
#define IS_RCC_PLLR_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 7U))

#define IS_RCC_PLLI2SP_VALUE(VALUE)       (((VALUE) == RCC_PLLI2SP_DIV2) ||\
                                           ((VALUE) == RCC_PLLI2SP_DIV4) ||\
                                           ((VALUE) == RCC_PLLI2SP_DIV6) ||\
                                           ((VALUE) == RCC_PLLI2SP_DIV8))

#define IS_RCC_PLLSAIM_VALUE(VALUE)       ((VALUE) <= 63U)

#define IS_RCC_PLLSAIP_VALUE(VALUE)       (((VALUE) == RCC_PLLSAIP_DIV2) ||\
                                           ((VALUE) == RCC_PLLSAIP_DIV4) ||\
                                           ((VALUE) == RCC_PLLSAIP_DIV6) ||\
                                           ((VALUE) == RCC_PLLSAIP_DIV8))

#define IS_RCC_SAI1CLKSOURCE(SOURCE)      (((SOURCE) == RCC_SAI1CLKSOURCE_PLLSAI) ||\
                                           ((SOURCE) == RCC_SAI1CLKSOURCE_PLLI2S) ||\
                                           ((SOURCE) == RCC_SAI1CLKSOURCE_PLLR)   ||\
                                           ((SOURCE) == RCC_SAI1CLKSOURCE_EXT))

#define IS_RCC_SAI2CLKSOURCE(SOURCE)      (((SOURCE) == RCC_SAI2CLKSOURCE_PLLSAI) ||\
                                           ((SOURCE) == RCC_SAI2CLKSOURCE_PLLI2S) ||\
                                           ((SOURCE) == RCC_SAI2CLKSOURCE_PLLR)   ||\
                                           ((SOURCE) == RCC_SAI2CLKSOURCE_PLLSRC))

#define IS_RCC_I2SAPB1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLI2S) ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_EXT)    ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLR)   ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLSRC))

#define IS_RCC_I2SAPB2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLI2S) ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_EXT)    ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLR)   ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLSRC))

#define IS_RCC_FMPI2C1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_FMPI2C1CLKSOURCE_PCLK1)    ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_SYSCLK) ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_HSI))

#define IS_RCC_CECCLKSOURCE(SOURCE)       (((SOURCE) == RCC_CECCLKSOURCE_HSI)   ||\
                                           ((SOURCE) == RCC_CECCLKSOURCE_LSE))

#define IS_RCC_CLK48CLKSOURCE(SOURCE)      (((SOURCE) == RCC_CLK48CLKSOURCE_PLLQ) ||\
                                            ((SOURCE) == RCC_CLK48CLKSOURCE_PLLSAIP))

#define IS_RCC_SDIOCLKSOURCE(SOURCE)      (((SOURCE) == RCC_SDIOCLKSOURCE_CLK48) ||\
                                           ((SOURCE) == RCC_SDIOCLKSOURCE_SYSCLK))

#define IS_RCC_SPDIFRXCLKSOURCE(SOURCE)   (((SOURCE) == RCC_SPDIFRXCLKSOURCE_PLLR) ||\
                                           ((SOURCE) == RCC_SPDIFRXCLKSOURCE_PLLI2SP))
#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define IS_RCC_PLLR_VALUE(VALUE)            ((2U <= (VALUE)) && ((VALUE) <= 7U))

#define IS_RCC_PLLSAIP_VALUE(VALUE)         (((VALUE) == RCC_PLLSAIP_DIV2) ||\
                                             ((VALUE) == RCC_PLLSAIP_DIV4) ||\
                                             ((VALUE) == RCC_PLLSAIP_DIV6) ||\
                                             ((VALUE) == RCC_PLLSAIP_DIV8))

#define IS_RCC_CLK48CLKSOURCE(SOURCE)        (((SOURCE) == RCC_CLK48CLKSOURCE_PLLQ) ||\
                                              ((SOURCE) == RCC_CLK48CLKSOURCE_PLLSAIP))

#define IS_RCC_SDIOCLKSOURCE(SOURCE)        (((SOURCE) == RCC_SDIOCLKSOURCE_CLK48) ||\
                                             ((SOURCE) == RCC_SDIOCLKSOURCE_SYSCLK))

#define IS_RCC_DSIBYTELANECLKSOURCE(SOURCE) (((SOURCE) == RCC_DSICLKSOURCE_PLLR)  ||\
                                             ((SOURCE) == RCC_DSICLKSOURCE_DSIPHY))

#define IS_RCC_LSE_MODE(MODE)               (((MODE) == RCC_LSE_LOWPOWER_MODE) ||\
                                             ((MODE) == RCC_LSE_HIGHDRIVE_MODE))
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) ||\
    defined(STM32F413xx) || defined(STM32F423xx)
#define IS_RCC_PLLI2SQ_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 15U))

#define IS_RCC_PLLR_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 7U))

#define IS_RCC_PLLI2SCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLI2SCLKSOURCE_PLLSRC) || \
                                            ((__SOURCE__) == RCC_PLLI2SCLKSOURCE_EXT))

#define IS_RCC_I2SAPB1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLI2S) ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_EXT)    ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLR)   ||\
                                           ((SOURCE) == RCC_I2SAPB1CLKSOURCE_PLLSRC))

#define IS_RCC_I2SAPB2CLKSOURCE(SOURCE)  (((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLI2S) ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_EXT)    ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLR)   ||\
                                          ((SOURCE) == RCC_I2SAPB2CLKSOURCE_PLLSRC))

#define IS_RCC_FMPI2C1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_FMPI2C1CLKSOURCE_PCLK1)    ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_SYSCLK) ||\
                                           ((SOURCE) == RCC_FMPI2C1CLKSOURCE_HSI))

#define IS_RCC_CLK48CLKSOURCE(SOURCE)      (((SOURCE) == RCC_CLK48CLKSOURCE_PLLQ) ||\
                                            ((SOURCE) == RCC_CLK48CLKSOURCE_PLLI2SQ))

#define IS_RCC_SDIOCLKSOURCE(SOURCE)      (((SOURCE) == RCC_SDIOCLKSOURCE_CLK48) ||\
                                           ((SOURCE) == RCC_SDIOCLKSOURCE_SYSCLK))

#define IS_RCC_DFSDM1CLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_DFSDM1CLKSOURCE_PCLK2) || \
                                            ((__SOURCE__) == RCC_DFSDM1CLKSOURCE_SYSCLK))

#define IS_RCC_DFSDM1AUDIOCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_DFSDM1AUDIOCLKSOURCE_I2S1) || \
                                                 ((__SOURCE__) == RCC_DFSDM1AUDIOCLKSOURCE_I2S2))

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_RCC_DFSDM2CLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_DFSDM2CLKSOURCE_PCLK2) || \
                                            ((__SOURCE__) == RCC_DFSDM2CLKSOURCE_SYSCLK))

#define IS_RCC_DFSDM2AUDIOCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_DFSDM2AUDIOCLKSOURCE_I2S1) || \
                                                 ((__SOURCE__) == RCC_DFSDM2AUDIOCLKSOURCE_I2S2))

#define IS_RCC_LPTIM1CLKSOURCE(SOURCE)   (((SOURCE) == RCC_LPTIM1CLKSOURCE_PCLK1) ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_HSI)  ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSI)  ||\
                                          ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSE))

#define IS_RCC_SAIACLKSOURCE(SOURCE)     (((SOURCE) == RCC_SAIACLKSOURCE_PLLI2SR) ||\
                                          ((SOURCE) == RCC_SAIACLKSOURCE_EXT)     ||\
                                          ((SOURCE) == RCC_SAIACLKSOURCE_PLLR)    ||\
                                          ((SOURCE) == RCC_SAIACLKSOURCE_PLLSRC))

#define IS_RCC_SAIBCLKSOURCE(SOURCE)     (((SOURCE) == RCC_SAIBCLKSOURCE_PLLI2SR) ||\
                                          ((SOURCE) == RCC_SAIBCLKSOURCE_EXT)     ||\
                                          ((SOURCE) == RCC_SAIBCLKSOURCE_PLLR)    ||\
                                          ((SOURCE) == RCC_SAIBCLKSOURCE_PLLSRC))

#define IS_RCC_PLL_DIVR_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 32U))

#define IS_RCC_PLLI2S_DIVR_VALUE(VALUE) ((1U <= (VALUE)) && ((VALUE) <= 32U))

#endif
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
    defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || \
    defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == RCC_MCO2SOURCE_SYSCLK) || ((SOURCE) == RCC_MCO2SOURCE_PLLI2SCLK)|| \
                                   ((SOURCE) == RCC_MCO2SOURCE_HSE)    || ((SOURCE) == RCC_MCO2SOURCE_PLLCLK))

#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == RCC_MCO2SOURCE_SYSCLK) || ((SOURCE) == RCC_MCO2SOURCE_I2SCLK)|| \
                                   ((SOURCE) == RCC_MCO2SOURCE_HSE)    || ((SOURCE) == RCC_MCO2SOURCE_PLLCLK))
#endif

#ifdef __cplusplus
}
#endif

#endif
