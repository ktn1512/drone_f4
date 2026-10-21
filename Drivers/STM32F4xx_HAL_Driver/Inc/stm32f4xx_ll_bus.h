#ifndef __STM32F4xx_LL_BUS_H
#define __STM32F4xx_LL_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined(RCC)

#define LL_AHB1_GRP1_PERIPH_ALL             0xFFFFFFFFU
#define LL_AHB1_GRP1_PERIPH_GPIOA           RCC_AHB1ENR_GPIOAEN
#define LL_AHB1_GRP1_PERIPH_GPIOB           RCC_AHB1ENR_GPIOBEN
#define LL_AHB1_GRP1_PERIPH_GPIOC           RCC_AHB1ENR_GPIOCEN
#if defined(GPIOD)
#define LL_AHB1_GRP1_PERIPH_GPIOD           RCC_AHB1ENR_GPIODEN
#endif
#if defined(GPIOE)
#define LL_AHB1_GRP1_PERIPH_GPIOE           RCC_AHB1ENR_GPIOEEN
#endif
#if defined(GPIOF)
#define LL_AHB1_GRP1_PERIPH_GPIOF           RCC_AHB1ENR_GPIOFEN
#endif
#if defined(GPIOG)
#define LL_AHB1_GRP1_PERIPH_GPIOG           RCC_AHB1ENR_GPIOGEN
#endif
#if defined(GPIOH)
#define LL_AHB1_GRP1_PERIPH_GPIOH           RCC_AHB1ENR_GPIOHEN
#endif
#if defined(GPIOI)
#define LL_AHB1_GRP1_PERIPH_GPIOI           RCC_AHB1ENR_GPIOIEN
#endif
#if defined(GPIOJ)
#define LL_AHB1_GRP1_PERIPH_GPIOJ           RCC_AHB1ENR_GPIOJEN
#endif
#if defined(GPIOK)
#define LL_AHB1_GRP1_PERIPH_GPIOK           RCC_AHB1ENR_GPIOKEN
#endif
#define LL_AHB1_GRP1_PERIPH_CRC             RCC_AHB1ENR_CRCEN
#if defined(RCC_AHB1ENR_BKPSRAMEN)
#define LL_AHB1_GRP1_PERIPH_BKPSRAM         RCC_AHB1ENR_BKPSRAMEN
#endif
#if defined(RCC_AHB1ENR_CCMDATARAMEN)
#define LL_AHB1_GRP1_PERIPH_CCMDATARAM      RCC_AHB1ENR_CCMDATARAMEN
#endif
#define LL_AHB1_GRP1_PERIPH_DMA1            RCC_AHB1ENR_DMA1EN
#define LL_AHB1_GRP1_PERIPH_DMA2            RCC_AHB1ENR_DMA2EN
#if defined(RCC_AHB1ENR_RNGEN)
#define LL_AHB1_GRP1_PERIPH_RNG             RCC_AHB1ENR_RNGEN
#endif
#if defined(DMA2D)
#define LL_AHB1_GRP1_PERIPH_DMA2D           RCC_AHB1ENR_DMA2DEN
#endif
#if defined(ETH)
#define LL_AHB1_GRP1_PERIPH_ETHMAC          RCC_AHB1ENR_ETHMACEN
#define LL_AHB1_GRP1_PERIPH_ETHMACTX        RCC_AHB1ENR_ETHMACTXEN
#define LL_AHB1_GRP1_PERIPH_ETHMACRX        RCC_AHB1ENR_ETHMACRXEN
#define LL_AHB1_GRP1_PERIPH_ETHMACPTP       RCC_AHB1ENR_ETHMACPTPEN
#endif
#if defined(USB_OTG_HS)
#define LL_AHB1_GRP1_PERIPH_OTGHS           RCC_AHB1ENR_OTGHSEN
#define LL_AHB1_GRP1_PERIPH_OTGHSULPI       RCC_AHB1ENR_OTGHSULPIEN
#endif
#define LL_AHB1_GRP1_PERIPH_FLITF           RCC_AHB1LPENR_FLITFLPEN
#define LL_AHB1_GRP1_PERIPH_SRAM1           RCC_AHB1LPENR_SRAM1LPEN
#if defined(RCC_AHB1LPENR_SRAM2LPEN)
#define LL_AHB1_GRP1_PERIPH_SRAM2           RCC_AHB1LPENR_SRAM2LPEN
#endif
#if defined(RCC_AHB1LPENR_SRAM3LPEN)
#define LL_AHB1_GRP1_PERIPH_SRAM3           RCC_AHB1LPENR_SRAM3LPEN
#endif

#if defined(RCC_AHB2_SUPPORT)

#define LL_AHB2_GRP1_PERIPH_ALL            0xFFFFFFFFU
#if defined(DCMI)
#define LL_AHB2_GRP1_PERIPH_DCMI           RCC_AHB2ENR_DCMIEN
#endif
#if defined(CRYP)
#define LL_AHB2_GRP1_PERIPH_CRYP           RCC_AHB2ENR_CRYPEN
#endif
#if defined(AES)
#define LL_AHB2_GRP1_PERIPH_AES            RCC_AHB2ENR_AESEN
#endif
#if defined(HASH)
#define LL_AHB2_GRP1_PERIPH_HASH           RCC_AHB2ENR_HASHEN
#endif
#if defined(RCC_AHB2ENR_RNGEN)
#define LL_AHB2_GRP1_PERIPH_RNG            RCC_AHB2ENR_RNGEN
#endif
#if defined(USB_OTG_FS)
#define LL_AHB2_GRP1_PERIPH_OTGFS          RCC_AHB2ENR_OTGFSEN
#endif

#endif

#if defined(RCC_AHB3_SUPPORT)

#define LL_AHB3_GRP1_PERIPH_ALL            0xFFFFFFFFU
#if defined(FSMC_Bank1)
#define LL_AHB3_GRP1_PERIPH_FSMC           RCC_AHB3ENR_FSMCEN
#endif
#if defined(FMC_Bank1)
#define LL_AHB3_GRP1_PERIPH_FMC            RCC_AHB3ENR_FMCEN
#endif
#if defined(QUADSPI)
#define LL_AHB3_GRP1_PERIPH_QSPI           RCC_AHB3ENR_QSPIEN
#endif

#endif

#define LL_APB1_GRP1_PERIPH_ALL            0xFFFFFFFFU
#if defined(TIM2)
#define LL_APB1_GRP1_PERIPH_TIM2           RCC_APB1ENR_TIM2EN
#endif
#if defined(TIM3)
#define LL_APB1_GRP1_PERIPH_TIM3           RCC_APB1ENR_TIM3EN
#endif
#if defined(TIM4)
#define LL_APB1_GRP1_PERIPH_TIM4           RCC_APB1ENR_TIM4EN
#endif
#define LL_APB1_GRP1_PERIPH_TIM5           RCC_APB1ENR_TIM5EN
#if defined(TIM6)
#define LL_APB1_GRP1_PERIPH_TIM6           RCC_APB1ENR_TIM6EN
#endif
#if defined(TIM7)
#define LL_APB1_GRP1_PERIPH_TIM7           RCC_APB1ENR_TIM7EN
#endif
#if defined(TIM12)
#define LL_APB1_GRP1_PERIPH_TIM12          RCC_APB1ENR_TIM12EN
#endif
#if defined(TIM13)
#define LL_APB1_GRP1_PERIPH_TIM13          RCC_APB1ENR_TIM13EN
#endif
#if defined(TIM14)
#define LL_APB1_GRP1_PERIPH_TIM14          RCC_APB1ENR_TIM14EN
#endif
#if defined(LPTIM1)
#define LL_APB1_GRP1_PERIPH_LPTIM1         RCC_APB1ENR_LPTIM1EN
#endif
#if defined(RCC_APB1ENR_RTCAPBEN)
#define LL_APB1_GRP1_PERIPH_RTCAPB         RCC_APB1ENR_RTCAPBEN
#endif
#define LL_APB1_GRP1_PERIPH_WWDG           RCC_APB1ENR_WWDGEN
#if defined(SPI2)
#define LL_APB1_GRP1_PERIPH_SPI2           RCC_APB1ENR_SPI2EN
#endif
#if defined(SPI3)
#define LL_APB1_GRP1_PERIPH_SPI3           RCC_APB1ENR_SPI3EN
#endif
#if defined(SPDIFRX)
#define LL_APB1_GRP1_PERIPH_SPDIFRX        RCC_APB1ENR_SPDIFRXEN
#endif
#define LL_APB1_GRP1_PERIPH_USART2         RCC_APB1ENR_USART2EN
#if defined(USART3)
#define LL_APB1_GRP1_PERIPH_USART3         RCC_APB1ENR_USART3EN
#endif
#if defined(UART4)
#define LL_APB1_GRP1_PERIPH_UART4          RCC_APB1ENR_UART4EN
#endif
#if defined(UART5)
#define LL_APB1_GRP1_PERIPH_UART5          RCC_APB1ENR_UART5EN
#endif
#define LL_APB1_GRP1_PERIPH_I2C1           RCC_APB1ENR_I2C1EN
#define LL_APB1_GRP1_PERIPH_I2C2           RCC_APB1ENR_I2C2EN
#if defined(I2C3)
#define LL_APB1_GRP1_PERIPH_I2C3           RCC_APB1ENR_I2C3EN
#endif
#if defined(FMPI2C1)
#define LL_APB1_GRP1_PERIPH_FMPI2C1        RCC_APB1ENR_FMPI2C1EN
#endif
#if defined(CAN1)
#define LL_APB1_GRP1_PERIPH_CAN1           RCC_APB1ENR_CAN1EN
#endif
#if defined(CAN2)
#define LL_APB1_GRP1_PERIPH_CAN2           RCC_APB1ENR_CAN2EN
#endif
#if defined(CAN3)
#define LL_APB1_GRP1_PERIPH_CAN3           RCC_APB1ENR_CAN3EN
#endif
#if defined(CEC)
#define LL_APB1_GRP1_PERIPH_CEC            RCC_APB1ENR_CECEN
#endif
#define LL_APB1_GRP1_PERIPH_PWR            RCC_APB1ENR_PWREN
#if defined(DAC1)
#define LL_APB1_GRP1_PERIPH_DAC1           RCC_APB1ENR_DACEN
#endif
#if defined(UART7)
#define LL_APB1_GRP1_PERIPH_UART7          RCC_APB1ENR_UART7EN
#endif
#if defined(UART8)
#define LL_APB1_GRP1_PERIPH_UART8          RCC_APB1ENR_UART8EN
#endif

#define LL_APB2_GRP1_PERIPH_ALL          0xFFFFFFFFU
#define LL_APB2_GRP1_PERIPH_TIM1         RCC_APB2ENR_TIM1EN
#if defined(TIM8)
#define LL_APB2_GRP1_PERIPH_TIM8         RCC_APB2ENR_TIM8EN
#endif
#define LL_APB2_GRP1_PERIPH_USART1       RCC_APB2ENR_USART1EN
#if defined(USART6)
#define LL_APB2_GRP1_PERIPH_USART6       RCC_APB2ENR_USART6EN
#endif
#if defined(UART9)
#define LL_APB2_GRP1_PERIPH_UART9        RCC_APB2ENR_UART9EN
#endif
#if defined(UART10)
#define LL_APB2_GRP1_PERIPH_UART10       RCC_APB2ENR_UART10EN
#endif
#define LL_APB2_GRP1_PERIPH_ADC1         RCC_APB2ENR_ADC1EN
#if defined(ADC2)
#define LL_APB2_GRP1_PERIPH_ADC2         RCC_APB2ENR_ADC2EN
#endif
#if defined(ADC3)
#define LL_APB2_GRP1_PERIPH_ADC3         RCC_APB2ENR_ADC3EN
#endif
#if defined(SDIO)
#define LL_APB2_GRP1_PERIPH_SDIO         RCC_APB2ENR_SDIOEN
#endif
#define LL_APB2_GRP1_PERIPH_SPI1         RCC_APB2ENR_SPI1EN
#if defined(SPI4)
#define LL_APB2_GRP1_PERIPH_SPI4         RCC_APB2ENR_SPI4EN
#endif
#define LL_APB2_GRP1_PERIPH_SYSCFG       RCC_APB2ENR_SYSCFGEN
#if defined(RCC_APB2ENR_EXTITEN)
#define LL_APB2_GRP1_PERIPH_EXTI         RCC_APB2ENR_EXTITEN
#endif
#define LL_APB2_GRP1_PERIPH_TIM9         RCC_APB2ENR_TIM9EN
#if defined(TIM10)
#define LL_APB2_GRP1_PERIPH_TIM10        RCC_APB2ENR_TIM10EN
#endif
#define LL_APB2_GRP1_PERIPH_TIM11        RCC_APB2ENR_TIM11EN
#if defined(SPI5)
#define LL_APB2_GRP1_PERIPH_SPI5         RCC_APB2ENR_SPI5EN
#endif
#if defined(SPI6)
#define LL_APB2_GRP1_PERIPH_SPI6         RCC_APB2ENR_SPI6EN
#endif
#if defined(SAI1)
#define LL_APB2_GRP1_PERIPH_SAI1         RCC_APB2ENR_SAI1EN
#endif
#if defined(SAI2)
#define LL_APB2_GRP1_PERIPH_SAI2         RCC_APB2ENR_SAI2EN
#endif
#if defined(LTDC)
#define LL_APB2_GRP1_PERIPH_LTDC         RCC_APB2ENR_LTDCEN
#endif
#if defined(DSI)
#define LL_APB2_GRP1_PERIPH_DSI          RCC_APB2ENR_DSIEN
#endif
#if defined(DFSDM1_Channel0)
#define LL_APB2_GRP1_PERIPH_DFSDM1       RCC_APB2ENR_DFSDM1EN
#endif
#if defined(DFSDM2_Channel0)
#define LL_APB2_GRP1_PERIPH_DFSDM2       RCC_APB2ENR_DFSDM2EN
#endif
#define LL_APB2_GRP1_PERIPH_ADC          RCC_APB2RSTR_ADCRST

__STATIC_INLINE void LL_AHB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1ENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB1ENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE uint32_t LL_AHB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB1ENR, Periphs) == Periphs);
}

__STATIC_INLINE void LL_AHB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1ENR, Periphs);
}

__STATIC_INLINE void LL_AHB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB1RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB1_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB1LPENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB1LPENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE void LL_AHB1_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB1LPENR, Periphs);
}

#if defined(RCC_AHB2_SUPPORT)

__STATIC_INLINE void LL_AHB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2ENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB2ENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE uint32_t LL_AHB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB2ENR, Periphs) == Periphs);
}

__STATIC_INLINE void LL_AHB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2ENR, Periphs);
}

__STATIC_INLINE void LL_AHB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB2RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB2_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB2LPENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB2LPENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE void LL_AHB2_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB2LPENR, Periphs);
}

#endif

#if defined(RCC_AHB3_SUPPORT)

__STATIC_INLINE void LL_AHB3_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3ENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB3ENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE uint32_t LL_AHB3_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->AHB3ENR, Periphs) == Periphs);
}

__STATIC_INLINE void LL_AHB3_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3ENR, Periphs);
}

__STATIC_INLINE void LL_AHB3_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->AHB3RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB3_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3RSTR, Periphs);
}

__STATIC_INLINE void LL_AHB3_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->AHB3LPENR, Periphs);

  tmpreg = READ_BIT(RCC->AHB3LPENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE void LL_AHB3_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->AHB3LPENR, Periphs);
}

#endif

__STATIC_INLINE void LL_APB1_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1ENR, Periphs);

  tmpreg = READ_BIT(RCC->APB1ENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE uint32_t LL_APB1_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->APB1ENR, Periphs) == Periphs);
}

__STATIC_INLINE void LL_APB1_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1ENR, Periphs);
}

__STATIC_INLINE void LL_APB1_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB1RSTR, Periphs);
}

__STATIC_INLINE void LL_APB1_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1RSTR, Periphs);
}

__STATIC_INLINE void LL_APB1_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB1LPENR, Periphs);

  tmpreg = READ_BIT(RCC->APB1LPENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE void LL_APB1_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB1LPENR, Periphs);
}

__STATIC_INLINE void LL_APB2_GRP1_EnableClock(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2ENR, Periphs);

  tmpreg = READ_BIT(RCC->APB2ENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE uint32_t LL_APB2_GRP1_IsEnabledClock(uint32_t Periphs)
{
  return (READ_BIT(RCC->APB2ENR, Periphs) == Periphs);
}

__STATIC_INLINE void LL_APB2_GRP1_DisableClock(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2ENR, Periphs);
}

__STATIC_INLINE void LL_APB2_GRP1_ForceReset(uint32_t Periphs)
{
  SET_BIT(RCC->APB2RSTR, Periphs);
}

__STATIC_INLINE void LL_APB2_GRP1_ReleaseReset(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2RSTR, Periphs);
}

__STATIC_INLINE void LL_APB2_GRP1_EnableClockLowPower(uint32_t Periphs)
{
  __IO uint32_t tmpreg;
  SET_BIT(RCC->APB2LPENR, Periphs);

  tmpreg = READ_BIT(RCC->APB2LPENR, Periphs);
  (void)tmpreg;
}

__STATIC_INLINE void LL_APB2_GRP1_DisableClockLowPower(uint32_t Periphs)
{
  CLEAR_BIT(RCC->APB2LPENR, Periphs);
}

#endif

#ifdef __cplusplus
}
#endif

#endif
