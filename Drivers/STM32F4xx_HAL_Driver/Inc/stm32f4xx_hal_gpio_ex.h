#ifndef __STM32F4xx_HAL_GPIO_EX_H
#define __STM32F4xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

#if defined(STM32F429xx) || defined(STM32F439xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_SPI5          ((uint8_t)0x05)
#define GPIO_AF5_SPI6          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)
#define GPIO_AF6_SAI1          ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_UART7         ((uint8_t)0x08)
#define GPIO_AF8_UART8         ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_LTDC          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)

#define GPIO_AF11_ETH           ((uint8_t)0x0B)

#define GPIO_AF12_FMC           ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF13_DCMI          ((uint8_t)0x0D)

#define GPIO_AF14_LTDC          ((uint8_t)0x0E)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_SPI5          ((uint8_t)0x05)
#define GPIO_AF5_SPI6          ((uint8_t)0x05)

#define GPIO_AF5_I2S3ext       GPIO_AF5_SPI3

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)
#define GPIO_AF6_SAI1          ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_UART7         ((uint8_t)0x08)
#define GPIO_AF8_UART8         ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)

#define GPIO_AF11_ETH           ((uint8_t)0x0B)

#define GPIO_AF12_FMC           ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF13_DCMI          ((uint8_t)0x0D)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F407xx) || defined(STM32F417xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)

#define GPIO_AF11_ETH           ((uint8_t)0x0B)

#define GPIO_AF12_FSMC          ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF13_DCMI          ((uint8_t)0x0D)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F405xx) || defined(STM32F415xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)

#define GPIO_AF12_FSMC          ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F401xC) || defined(STM32F401xE)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_USART6        ((uint8_t)0x08)

#define GPIO_AF9_I2C2          ((uint8_t)0x09)
#define GPIO_AF9_I2C3          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)

#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)
#define GPIO_AF4_FMPI2C1       ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI2          ((uint8_t)0x06)
#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_SPI4          ((uint8_t)0x06)
#define GPIO_AF6_SPI5          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)
#define GPIO_AF6_DFSDM1        ((uint8_t)0x06)

#define GPIO_AF7_SPI3          ((uint8_t)0x07)
#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_USART3        ((uint8_t)0x08)
#define GPIO_AF8_DFSDM1        ((uint8_t)0x08)
#define GPIO_AF8_CAN1          ((uint8_t)0x08)

#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_I2C2          ((uint8_t)0x09)
#define GPIO_AF9_I2C3          ((uint8_t)0x09)
#define GPIO_AF9_FMPI2C1       ((uint8_t)0x09)
#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_QSPI          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_DFSDM1        ((uint8_t)0x0A)
#define GPIO_AF10_QSPI          ((uint8_t)0x0A)
#define GPIO_AF10_FMC           ((uint8_t)0x0A)

#define GPIO_AF12_SDIO          ((uint8_t)0x0C)
#define GPIO_AF12_FSMC          ((uint8_t)0x0C)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)
#define GPIO_AF3_DFSDM2        ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)
#define GPIO_AF4_FMPI2C1       ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI2          ((uint8_t)0x06)
#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_SPI4          ((uint8_t)0x06)
#define GPIO_AF6_SPI5          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)
#define GPIO_AF6_DFSDM1        ((uint8_t)0x06)
#define GPIO_AF6_DFSDM2        ((uint8_t)0x06)

#define GPIO_AF7_SPI3          ((uint8_t)0x07)
#define GPIO_AF7_SAI1          ((uint8_t)0x07)
#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)
#define GPIO_AF7_DFSDM2        ((uint8_t)0x07)

#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_USART3        ((uint8_t)0x08)
#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_UART7         ((uint8_t)0x08)
#define GPIO_AF8_UART8         ((uint8_t)0x08)
#define GPIO_AF8_DFSDM1        ((uint8_t)0x08)
#define GPIO_AF8_CAN1          ((uint8_t)0x08)

#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_I2C2          ((uint8_t)0x09)
#define GPIO_AF9_I2C3          ((uint8_t)0x09)
#define GPIO_AF9_FMPI2C1       ((uint8_t)0x09)
#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_QSPI          ((uint8_t)0x09)

#define GPIO_AF10_SAI1          ((uint8_t)0x0A)
#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_DFSDM1        ((uint8_t)0x0A)
#define GPIO_AF10_DFSDM2        ((uint8_t)0x0A)
#define GPIO_AF10_QSPI          ((uint8_t)0x0A)
#define GPIO_AF10_FSMC          ((uint8_t)0x0A)

#define GPIO_AF11_UART4         ((uint8_t)0x0B)
#define GPIO_AF11_UART5         ((uint8_t)0x0B)
#define GPIO_AF11_UART9         ((uint8_t)0x0B)
#define GPIO_AF11_UART10        ((uint8_t)0x0B)
#define GPIO_AF11_CAN3          ((uint8_t)0x0B)

#define GPIO_AF12_SDIO          ((uint8_t)0x0C)
#define GPIO_AF12_FSMC          ((uint8_t)0x0C)

#define GPIO_AF14_RNG           ((uint8_t)0x0E)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F411xE)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI2          ((uint8_t)0x06)
#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_SPI4          ((uint8_t)0x06)
#define GPIO_AF6_SPI5          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)

#define GPIO_AF7_SPI3          ((uint8_t)0x07)
#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_USART6        ((uint8_t)0x08)

#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_I2C2          ((uint8_t)0x09)
#define GPIO_AF9_I2C3          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)

#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)

#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_FMPI2C1       ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#if defined(STM32F410Cx) || defined(STM32F410Rx)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#endif

#define GPIO_AF6_SPI1          ((uint8_t)0x06)
#if defined(STM32F410Cx) || defined(STM32F410Rx)
#define GPIO_AF6_SPI2          ((uint8_t)0x06)
#endif
#define GPIO_AF6_SPI5          ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)

#define GPIO_AF8_USART6        ((uint8_t)0x08)

#define GPIO_AF9_I2C2          ((uint8_t)0x09)
#define GPIO_AF9_FMPI2C1       ((uint8_t)0x09)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)
#endif

#if defined(STM32F446xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)
#define GPIO_AF3_CEC           ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)
#define GPIO_AF4_FMPI2C1       ((uint8_t)0x04)
#define GPIO_AF4_CEC           ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)

#define GPIO_AF6_SPI2          ((uint8_t)0x06)
#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_SPI4          ((uint8_t)0x06)
#define GPIO_AF6_SAI1          ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_UART5         ((uint8_t)0x07)
#define GPIO_AF7_SPI2          ((uint8_t)0x07)
#define GPIO_AF7_SPI3          ((uint8_t)0x07)
#define GPIO_AF7_SPDIFRX       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_SPDIFRX       ((uint8_t)0x08)
#define GPIO_AF8_SAI2          ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_QSPI          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)
#define GPIO_AF10_SAI2          ((uint8_t)0x0A)
#define GPIO_AF10_QSPI          ((uint8_t)0x0A)

#define GPIO_AF11_ETH           ((uint8_t)0x0B)

#define GPIO_AF12_FMC           ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF13_DCMI          ((uint8_t)0x0D)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)

#endif

#if defined(STM32F469xx) || defined(STM32F479xx)

#define GPIO_AF0_RTC_50Hz      ((uint8_t)0x00)
#define GPIO_AF0_MCO           ((uint8_t)0x00)
#define GPIO_AF0_TAMPER        ((uint8_t)0x00)
#define GPIO_AF0_SWJ           ((uint8_t)0x00)
#define GPIO_AF0_TRACE         ((uint8_t)0x00)

#define GPIO_AF1_TIM1          ((uint8_t)0x01)
#define GPIO_AF1_TIM2          ((uint8_t)0x01)

#define GPIO_AF2_TIM3          ((uint8_t)0x02)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)

#define GPIO_AF3_TIM8          ((uint8_t)0x03)
#define GPIO_AF3_TIM9          ((uint8_t)0x03)
#define GPIO_AF3_TIM10         ((uint8_t)0x03)
#define GPIO_AF3_TIM11         ((uint8_t)0x03)

#define GPIO_AF4_I2C1          ((uint8_t)0x04)
#define GPIO_AF4_I2C2          ((uint8_t)0x04)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)

#define GPIO_AF5_SPI1          ((uint8_t)0x05)
#define GPIO_AF5_SPI2          ((uint8_t)0x05)
#define GPIO_AF5_SPI3          ((uint8_t)0x05)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)
#define GPIO_AF5_SPI5          ((uint8_t)0x05)
#define GPIO_AF5_SPI6          ((uint8_t)0x05)
#define GPIO_AF5_I2S3ext       ((uint8_t)0x05)

#define GPIO_AF6_SPI3          ((uint8_t)0x06)
#define GPIO_AF6_I2S2ext       ((uint8_t)0x06)
#define GPIO_AF6_SAI1          ((uint8_t)0x06)

#define GPIO_AF7_USART1        ((uint8_t)0x07)
#define GPIO_AF7_USART2        ((uint8_t)0x07)
#define GPIO_AF7_USART3        ((uint8_t)0x07)
#define GPIO_AF7_I2S3ext       ((uint8_t)0x07)

#define GPIO_AF8_UART4         ((uint8_t)0x08)
#define GPIO_AF8_UART5         ((uint8_t)0x08)
#define GPIO_AF8_USART6        ((uint8_t)0x08)
#define GPIO_AF8_UART7         ((uint8_t)0x08)
#define GPIO_AF8_UART8         ((uint8_t)0x08)

#define GPIO_AF9_CAN1          ((uint8_t)0x09)
#define GPIO_AF9_CAN2          ((uint8_t)0x09)
#define GPIO_AF9_TIM12         ((uint8_t)0x09)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)
#define GPIO_AF9_LTDC          ((uint8_t)0x09)
#define GPIO_AF9_QSPI          ((uint8_t)0x09)

#define GPIO_AF10_OTG_FS        ((uint8_t)0x0A)
#define GPIO_AF10_OTG_HS        ((uint8_t)0x0A)
#define GPIO_AF10_QSPI          ((uint8_t)0x0A)

#define GPIO_AF11_ETH           ((uint8_t)0x0B)

#define GPIO_AF12_FMC           ((uint8_t)0x0C)
#define GPIO_AF12_OTG_HS_FS     ((uint8_t)0x0C)
#define GPIO_AF12_SDIO          ((uint8_t)0x0C)

#define GPIO_AF13_DCMI          ((uint8_t)0x0D)
#define GPIO_AF13_DSI           ((uint8_t)0x0D)

#define GPIO_AF14_LTDC          ((uint8_t)0x0E)

#define GPIO_AF15_EVENTOUT      ((uint8_t)0x0F)

#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U :\
                                               ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U :\
                                               ((__GPIOx__) == (GPIOH))? 7U :\
                                               ((__GPIOx__) == (GPIOI))? 8U :\
                                               ((__GPIOx__) == (GPIOJ))? 9U : 10U)
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U : 7U)
#endif

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U : 7U)
#endif

#if defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F413xx) || defined(STM32F423xx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U : 7U)
#endif
#if defined(STM32F412Vx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U : 7U)
#endif
#if defined(STM32F412Rx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U : 7U)
#endif
#if defined(STM32F412Cx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U : 7U)
#endif

#if defined(STM32F429xx) || defined(STM32F439xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)      || \
                          ((AF) == GPIO_AF12_FMC)       ||  ((AF) == GPIO_AF6_SAI1)      || \
                          ((AF) == GPIO_AF14_LTDC))

#endif

#if defined(STM32F427xx) || defined(STM32F437xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)      || \
                          ((AF) == GPIO_AF12_FMC)       ||  ((AF) == GPIO_AF6_SAI1))

#endif

#if defined(STM32F407xx) || defined(STM32F417xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF12_FSMC)      || ((AF) == GPIO_AF15_EVENTOUT))

#endif

#if defined(STM32F405xx) || defined(STM32F415xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF12_OTG_HS_FS) || ((AF) == GPIO_AF12_SDIO)      || \
                          ((AF) == GPIO_AF12_FSMC)      || ((AF) == GPIO_AF15_EVENTOUT))

#endif

#if defined(STM32F401xC) || defined(STM32F401xE)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF12_SDIO)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM9)       || \
                          ((AF) == GPIO_AF3_TIM10)      || ((AF) == GPIO_AF3_TIM11)      || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF7_USART1)     || \
                          ((AF) == GPIO_AF7_USART2)     || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_I2C2)       || ((AF) == GPIO_AF9_I2C3)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF15_EVENTOUT))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_GPIO_AF(AF)   (((AF) < 10U) || ((AF) == 15U))
#endif

#if defined(STM32F411xE)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF4_I2C1)       || \
                          ((AF) == GPIO_AF4_I2C2)       || ((AF) == GPIO_AF4_I2C3)       || \
                          ((AF) == GPIO_AF5_SPI1)       || ((AF) == GPIO_AF5_SPI2)       || \
                          ((AF) == GPIO_AF5_SPI3)       || ((AF) == GPIO_AF6_SPI4)       || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF6_SPI5)       || ((AF) == GPIO_AF7_SPI3)       || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF8_USART6)     || ((AF) == GPIO_AF10_OTG_FS)    || \
                          ((AF) == GPIO_AF9_I2C2)       || ((AF) == GPIO_AF9_I2C3)       || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF15_EVENTOUT))

#endif

#if defined(STM32F446xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF12_FMC)       ||  ((AF) == GPIO_AF6_SAI1)      || \
                          ((AF) == GPIO_AF3_CEC)        ||  ((AF) == GPIO_AF4_CEC)       || \
                          ((AF) == GPIO_AF5_SPI3)       ||  ((AF) == GPIO_AF6_SPI2)      || \
                          ((AF) == GPIO_AF6_SPI4)       ||  ((AF) == GPIO_AF7_UART5)     || \
                          ((AF) == GPIO_AF7_SPI2)       ||  ((AF) == GPIO_AF7_SPI3)      || \
                          ((AF) == GPIO_AF7_SPDIFRX)    ||  ((AF) == GPIO_AF8_SPDIFRX)   || \
                          ((AF) == GPIO_AF8_SAI2)       ||  ((AF) == GPIO_AF9_QSPI)      || \
                          ((AF) == GPIO_AF10_SAI2)      ||  ((AF) == GPIO_AF10_QSPI))

#endif

#if defined(STM32F469xx) || defined(STM32F479xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)      || \
                          ((AF) == GPIO_AF12_FMC)       || ((AF) == GPIO_AF6_SAI1)       || \
                          ((AF) == GPIO_AF14_LTDC)      || ((AF) == GPIO_AF13_DSI)      || \
                          ((AF) == GPIO_AF9_QSPI)       || ((AF) == GPIO_AF10_QSPI))

#endif

#if defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define IS_GPIO_AF(AF)   (((AF) < 16U) && ((AF) != 11U) && ((AF) != 14U) && ((AF) != 13U))
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_GPIO_AF(AF)   (((AF) < 16U) && ((AF) != 13U))
#endif

#ifdef __cplusplus
}
#endif

#endif
