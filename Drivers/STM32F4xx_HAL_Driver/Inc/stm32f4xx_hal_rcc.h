#ifndef __STM32F4xx_HAL_RCC_H
#define __STM32F4xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

#include "stm32f4xx_hal_rcc_ex.h"

typedef struct
{
  uint32_t OscillatorType;

  uint32_t HSEState;

  uint32_t LSEState;

  uint32_t HSIState;

  uint32_t HSICalibrationValue;

  uint32_t LSIState;

  RCC_PLLInitTypeDef PLL;
} RCC_OscInitTypeDef;

typedef struct
{
  uint32_t ClockType;

  uint32_t SYSCLKSource;

  uint32_t AHBCLKDivider;

  uint32_t APB1CLKDivider;

  uint32_t APB2CLKDivider;

} RCC_ClkInitTypeDef;

#define RCC_OSCILLATORTYPE_NONE            0x00000000U
#define RCC_OSCILLATORTYPE_HSE             0x00000001U
#define RCC_OSCILLATORTYPE_HSI             0x00000002U
#define RCC_OSCILLATORTYPE_LSE             0x00000004U
#define RCC_OSCILLATORTYPE_LSI             0x00000008U

#define RCC_HSE_OFF                      0x00000000U
#define RCC_HSE_ON                       RCC_CR_HSEON
#define RCC_HSE_BYPASS                   ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))

#define RCC_LSE_OFF                    0x00000000U
#define RCC_LSE_ON                     RCC_BDCR_LSEON
#define RCC_LSE_BYPASS                 ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON))

#define RCC_HSI_OFF                      ((uint8_t)0x00)
#define RCC_HSI_ON                       ((uint8_t)0x01)

#define RCC_HSICALIBRATION_DEFAULT       0x10U

#define RCC_LSI_OFF                      ((uint8_t)0x00)
#define RCC_LSI_ON                       ((uint8_t)0x01)

#define RCC_PLL_NONE                      ((uint8_t)0x00)
#define RCC_PLL_OFF                       ((uint8_t)0x01)
#define RCC_PLL_ON                        ((uint8_t)0x02)

#define RCC_PLLP_DIV2                  0x00000002U
#define RCC_PLLP_DIV4                  0x00000004U
#define RCC_PLLP_DIV6                  0x00000006U
#define RCC_PLLP_DIV8                  0x00000008U

#define RCC_PLLSOURCE_HSI                RCC_PLLCFGR_PLLSRC_HSI
#define RCC_PLLSOURCE_HSE                RCC_PLLCFGR_PLLSRC_HSE

#define RCC_CLOCKTYPE_SYSCLK             0x00000001U
#define RCC_CLOCKTYPE_HCLK               0x00000002U
#define RCC_CLOCKTYPE_PCLK1              0x00000004U
#define RCC_CLOCKTYPE_PCLK2              0x00000008U

#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL
#define RCC_SYSCLKSOURCE_PLLRCLK         ((uint32_t)(RCC_CFGR_SW_0 | RCC_CFGR_SW_1))

#define RCC_SYSCLKSOURCE_STATUS_HSI     RCC_CFGR_SWS_HSI
#define RCC_SYSCLKSOURCE_STATUS_HSE     RCC_CFGR_SWS_HSE
#define RCC_SYSCLKSOURCE_STATUS_PLLCLK  RCC_CFGR_SWS_PLL
#define RCC_SYSCLKSOURCE_STATUS_PLLRCLK ((uint32_t)(RCC_CFGR_SWS_0 | RCC_CFGR_SWS_1))

#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512

#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16

#define RCC_RTCCLKSOURCE_NO_CLK          0x00000000U
#define RCC_RTCCLKSOURCE_LSE             0x00000100U
#define RCC_RTCCLKSOURCE_LSI             0x00000200U
#define RCC_RTCCLKSOURCE_HSE_DIVX        0x00000300U
#define RCC_RTCCLKSOURCE_HSE_DIV2        0x00020300U
#define RCC_RTCCLKSOURCE_HSE_DIV3        0x00030300U
#define RCC_RTCCLKSOURCE_HSE_DIV4        0x00040300U
#define RCC_RTCCLKSOURCE_HSE_DIV5        0x00050300U
#define RCC_RTCCLKSOURCE_HSE_DIV6        0x00060300U
#define RCC_RTCCLKSOURCE_HSE_DIV7        0x00070300U
#define RCC_RTCCLKSOURCE_HSE_DIV8        0x00080300U
#define RCC_RTCCLKSOURCE_HSE_DIV9        0x00090300U
#define RCC_RTCCLKSOURCE_HSE_DIV10       0x000A0300U
#define RCC_RTCCLKSOURCE_HSE_DIV11       0x000B0300U
#define RCC_RTCCLKSOURCE_HSE_DIV12       0x000C0300U
#define RCC_RTCCLKSOURCE_HSE_DIV13       0x000D0300U
#define RCC_RTCCLKSOURCE_HSE_DIV14       0x000E0300U
#define RCC_RTCCLKSOURCE_HSE_DIV15       0x000F0300U
#define RCC_RTCCLKSOURCE_HSE_DIV16       0x00100300U
#define RCC_RTCCLKSOURCE_HSE_DIV17       0x00110300U
#define RCC_RTCCLKSOURCE_HSE_DIV18       0x00120300U
#define RCC_RTCCLKSOURCE_HSE_DIV19       0x00130300U
#define RCC_RTCCLKSOURCE_HSE_DIV20       0x00140300U
#define RCC_RTCCLKSOURCE_HSE_DIV21       0x00150300U
#define RCC_RTCCLKSOURCE_HSE_DIV22       0x00160300U
#define RCC_RTCCLKSOURCE_HSE_DIV23       0x00170300U
#define RCC_RTCCLKSOURCE_HSE_DIV24       0x00180300U
#define RCC_RTCCLKSOURCE_HSE_DIV25       0x00190300U
#define RCC_RTCCLKSOURCE_HSE_DIV26       0x001A0300U
#define RCC_RTCCLKSOURCE_HSE_DIV27       0x001B0300U
#define RCC_RTCCLKSOURCE_HSE_DIV28       0x001C0300U
#define RCC_RTCCLKSOURCE_HSE_DIV29       0x001D0300U
#define RCC_RTCCLKSOURCE_HSE_DIV30       0x001E0300U
#define RCC_RTCCLKSOURCE_HSE_DIV31       0x001F0300U

#define RCC_MCO1                         0x00000000U
#define RCC_MCO2                         0x00000001U

#define RCC_MCO1SOURCE_HSI               0x00000000U
#define RCC_MCO1SOURCE_LSE               RCC_CFGR_MCO1_0
#define RCC_MCO1SOURCE_HSE               RCC_CFGR_MCO1_1
#define RCC_MCO1SOURCE_PLLCLK            RCC_CFGR_MCO1

#define RCC_MCODIV_1                    0x00000000U
#define RCC_MCODIV_2                    RCC_CFGR_MCO1PRE_2
#define RCC_MCODIV_3                    ((uint32_t)RCC_CFGR_MCO1PRE_0 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCODIV_4                    ((uint32_t)RCC_CFGR_MCO1PRE_1 | RCC_CFGR_MCO1PRE_2)
#define RCC_MCODIV_5                    RCC_CFGR_MCO1PRE

#define RCC_IT_LSIRDY                    ((uint8_t)0x01)
#define RCC_IT_LSERDY                    ((uint8_t)0x02)
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)
#define RCC_IT_HSERDY                    ((uint8_t)0x08)
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)
#define RCC_IT_PLLI2SRDY                 ((uint8_t)0x20)
#define RCC_IT_CSS                       ((uint8_t)0x80)

#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_PLLI2SRDY               ((uint8_t)0x3B)

#define RCC_FLAG_LSERDY                  ((uint8_t)0x41)

#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)
#define RCC_FLAG_BORRST                  ((uint8_t)0x79)
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)

#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);\
                                              \
                                            tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOC_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);\
                                           UNUSED(tmpreg); \
                                          } while(0U)
#define __HAL_RCC_GPIOH_CLK_ENABLE()  do { \
                                           __IO uint32_t tmpreg = 0x00U; \
                                           SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);\
                                             \
                                           tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN);\
                                           UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DMA1_CLK_ENABLE()  do { \
                                          __IO uint32_t tmpreg = 0x00U; \
                                          SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);\
                                            \
                                          tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN);\
                                          UNUSED(tmpreg); \
                                         } while(0U)
#define __HAL_RCC_DMA2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)

#define __HAL_RCC_GPIOA_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN))
#define __HAL_RCC_GPIOB_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOBEN))
#define __HAL_RCC_GPIOC_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOCEN))
#define __HAL_RCC_GPIOH_CLK_DISABLE()        (RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOHEN))
#define __HAL_RCC_DMA1_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA1EN))
#define __HAL_RCC_DMA2_CLK_DISABLE()         (RCC->AHB1ENR &= ~(RCC_AHB1ENR_DMA2EN))

#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOAEN)) != RESET)
#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOBEN)) != RESET)
#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOCEN)) != RESET)
#define __HAL_RCC_GPIOH_IS_CLK_ENABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOHEN)) != RESET)
#define __HAL_RCC_DMA1_IS_CLK_ENABLED()         ((RCC->AHB1ENR &(RCC_AHB1ENR_DMA1EN)) != RESET)
#define __HAL_RCC_DMA2_IS_CLK_ENABLED()         ((RCC->AHB1ENR &(RCC_AHB1ENR_DMA2EN)) != RESET)

#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()       ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOAEN)) == RESET)
#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()       ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOBEN)) == RESET)
#define __HAL_RCC_GPIOC_IS_CLK_DISABLED()       ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOCEN)) == RESET)
#define __HAL_RCC_GPIOH_IS_CLK_DISABLED()       ((RCC->AHB1ENR &(RCC_AHB1ENR_GPIOHEN)) == RESET)
#define __HAL_RCC_DMA1_IS_CLK_DISABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_DMA1EN)) == RESET)
#define __HAL_RCC_DMA2_IS_CLK_DISABLED()        ((RCC->AHB1ENR &(RCC_AHB1ENR_DMA2EN)) == RESET)

#define __HAL_RCC_TIM5_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_WWDG_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_USART2_CLK_ENABLE()     do { \
                                               __IO uint32_t tmpreg = 0x00U; \
                                               SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);\
                                                 \
                                               tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);\
                                               UNUSED(tmpreg); \
                                             } while(0U)
#define __HAL_RCC_I2C1_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_I2C2_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C2EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C2EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_PWR_CLK_ENABLE()     do { \
                                            __IO uint32_t tmpreg = 0x00U; \
                                            SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
                                              \
                                            tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
                                            UNUSED(tmpreg); \
                                          } while(0U)

#define __HAL_RCC_TIM5_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM5EN))
#define __HAL_RCC_WWDG_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_WWDGEN))
#define __HAL_RCC_SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_SPI2EN))
#define __HAL_RCC_USART2_CLK_DISABLE() (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
#define __HAL_RCC_I2C1_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1EN))
#define __HAL_RCC_I2C2_CLK_DISABLE()   (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C2EN))
#define __HAL_RCC_PWR_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))

#define __HAL_RCC_TIM5_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM5EN)) != RESET)
#define __HAL_RCC_WWDG_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) != RESET)
#define __HAL_RCC_SPI2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI2EN)) != RESET)
#define __HAL_RCC_USART2_IS_CLK_ENABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART2EN)) != RESET)
#define __HAL_RCC_I2C1_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C1EN)) != RESET)
#define __HAL_RCC_I2C2_IS_CLK_ENABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C2EN)) != RESET)
#define __HAL_RCC_PWR_IS_CLK_ENABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) != RESET)

#define __HAL_RCC_TIM5_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_TIM5EN)) == RESET)
#define __HAL_RCC_WWDG_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) == RESET)
#define __HAL_RCC_SPI2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_SPI2EN)) == RESET)
#define __HAL_RCC_USART2_IS_CLK_DISABLED() ((RCC->APB1ENR & (RCC_APB1ENR_USART2EN)) == RESET)
#define __HAL_RCC_I2C1_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C1EN)) == RESET)
#define __HAL_RCC_I2C2_IS_CLK_DISABLED()   ((RCC->APB1ENR & (RCC_APB1ENR_I2C2EN)) == RESET)
#define __HAL_RCC_PWR_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) == RESET)

#define __HAL_RCC_TIM1_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_USART1_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_USART6_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART6EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_ADC1_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SPI1_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_SYSCFG_CLK_ENABLE()   do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM9_CLK_ENABLE()     do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)
#define __HAL_RCC_TIM11_CLK_ENABLE()    do { \
                                             __IO uint32_t tmpreg = 0x00U; \
                                             SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);\
                                               \
                                             tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM11EN);\
                                             UNUSED(tmpreg); \
                                           } while(0U)

#define __HAL_RCC_TIM1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN))
#define __HAL_RCC_USART1_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN))
#define __HAL_RCC_USART6_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_USART6EN))
#define __HAL_RCC_ADC1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN))
#define __HAL_RCC_SPI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
#define __HAL_RCC_SYSCFG_CLK_DISABLE() (RCC->APB2ENR &= ~(RCC_APB2ENR_SYSCFGEN))
#define __HAL_RCC_TIM9_CLK_DISABLE()   (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM9EN))
#define __HAL_RCC_TIM11_CLK_DISABLE()  (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM11EN))

#define __HAL_RCC_TIM1_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM1EN)) != RESET)
#define __HAL_RCC_USART1_IS_CLK_ENABLED() ((RCC->APB2ENR & (RCC_APB2ENR_USART1EN)) != RESET)
#define __HAL_RCC_USART6_IS_CLK_ENABLED() ((RCC->APB2ENR & (RCC_APB2ENR_USART6EN)) != RESET)
#define __HAL_RCC_ADC1_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC1EN)) != RESET)
#define __HAL_RCC_SPI1_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI1EN)) != RESET)
#define __HAL_RCC_SYSCFG_IS_CLK_ENABLED() ((RCC->APB2ENR & (RCC_APB2ENR_SYSCFGEN)) != RESET)
#define __HAL_RCC_TIM9_IS_CLK_ENABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM9EN)) != RESET)
#define __HAL_RCC_TIM11_IS_CLK_ENABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM11EN)) != RESET)

#define __HAL_RCC_TIM1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM1EN)) == RESET)
#define __HAL_RCC_USART1_IS_CLK_DISABLED() ((RCC->APB2ENR & (RCC_APB2ENR_USART1EN)) == RESET)
#define __HAL_RCC_USART6_IS_CLK_DISABLED() ((RCC->APB2ENR & (RCC_APB2ENR_USART6EN)) == RESET)
#define __HAL_RCC_ADC1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_ADC1EN)) == RESET)
#define __HAL_RCC_SPI1_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_SPI1EN)) == RESET)
#define __HAL_RCC_SYSCFG_IS_CLK_DISABLED() ((RCC->APB2ENR & (RCC_APB2ENR_SYSCFGEN)) == RESET)
#define __HAL_RCC_TIM9_IS_CLK_DISABLED()   ((RCC->APB2ENR & (RCC_APB2ENR_TIM9EN)) == RESET)
#define __HAL_RCC_TIM11_IS_CLK_DISABLED()  ((RCC->APB2ENR & (RCC_APB2ENR_TIM11EN)) == RESET)

#define __HAL_RCC_GPIOA_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOARST))
#define __HAL_RCC_GPIOB_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOBRST))
#define __HAL_RCC_GPIOC_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOCRST))
#define __HAL_RCC_GPIOH_FORCE_RESET()   (RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOHRST))
#define __HAL_RCC_DMA1_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_DMA1RST))
#define __HAL_RCC_DMA2_FORCE_RESET()    (RCC->AHB1RSTR |= (RCC_AHB1RSTR_DMA2RST))

#define __HAL_RCC_AHB1_RELEASE_RESET()  (RCC->AHB1RSTR = 0x00U)
#define __HAL_RCC_GPIOA_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOARST))
#define __HAL_RCC_GPIOB_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOBRST))
#define __HAL_RCC_GPIOC_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOCRST))
#define __HAL_RCC_GPIOH_RELEASE_RESET() (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOHRST))
#define __HAL_RCC_DMA1_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_DMA1RST))
#define __HAL_RCC_DMA2_RELEASE_RESET()  (RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_DMA2RST))

#define __HAL_RCC_TIM5_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM5RST))
#define __HAL_RCC_WWDG_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_SPI2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_SPI2RST))
#define __HAL_RCC_USART2_FORCE_RESET()   (RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST))
#define __HAL_RCC_I2C1_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST))
#define __HAL_RCC_I2C2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C2RST))
#define __HAL_RCC_PWR_FORCE_RESET()      (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))

#define __HAL_RCC_APB1_RELEASE_RESET()   (RCC->APB1RSTR = 0x00U)
#define __HAL_RCC_TIM5_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM5RST))
#define __HAL_RCC_WWDG_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_WWDGRST))
#define __HAL_RCC_SPI2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_SPI2RST))
#define __HAL_RCC_USART2_RELEASE_RESET() (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST))
#define __HAL_RCC_I2C1_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST))
#define __HAL_RCC_I2C2_RELEASE_RESET()   (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C2RST))
#define __HAL_RCC_PWR_RELEASE_RESET()    (RCC->APB1RSTR &= ~(RCC_APB1RSTR_PWRRST))

#define __HAL_RCC_TIM1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM1RST))
#define __HAL_RCC_USART1_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST))
#define __HAL_RCC_USART6_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_USART6RST))
#define __HAL_RCC_ADC_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_ADCRST))
#define __HAL_RCC_SPI1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))
#define __HAL_RCC_SYSCFG_FORCE_RESET()   (RCC->APB2RSTR |= (RCC_APB2RSTR_SYSCFGRST))
#define __HAL_RCC_TIM9_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM9RST))
#define __HAL_RCC_TIM11_FORCE_RESET()    (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM11RST))

#define __HAL_RCC_APB2_RELEASE_RESET()   (RCC->APB2RSTR = 0x00U)
#define __HAL_RCC_TIM1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM1RST))
#define __HAL_RCC_USART1_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST))
#define __HAL_RCC_USART6_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART6RST))
#define __HAL_RCC_ADC_RELEASE_RESET()    (RCC->APB2RSTR &= ~(RCC_APB2RSTR_ADCRST))
#define __HAL_RCC_SPI1_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
#define __HAL_RCC_SYSCFG_RELEASE_RESET() (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SYSCFGRST))
#define __HAL_RCC_TIM9_RELEASE_RESET()   (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM9RST))
#define __HAL_RCC_TIM11_RELEASE_RESET()  (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM11RST))

#define __HAL_RCC_GPIOA_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOALPEN))
#define __HAL_RCC_GPIOB_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOBLPEN))
#define __HAL_RCC_GPIOC_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOCLPEN))
#define __HAL_RCC_GPIOH_CLK_SLEEP_ENABLE()    (RCC->AHB1LPENR |= (RCC_AHB1LPENR_GPIOHLPEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_ENABLE()     (RCC->AHB1LPENR |= (RCC_AHB1LPENR_DMA1LPEN))
#define __HAL_RCC_DMA2_CLK_SLEEP_ENABLE()     (RCC->AHB1LPENR |= (RCC_AHB1LPENR_DMA2LPEN))

#define __HAL_RCC_GPIOA_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOALPEN))
#define __HAL_RCC_GPIOB_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOBLPEN))
#define __HAL_RCC_GPIOC_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOCLPEN))
#define __HAL_RCC_GPIOH_CLK_SLEEP_DISABLE()   (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_GPIOHLPEN))
#define __HAL_RCC_DMA1_CLK_SLEEP_DISABLE()    (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_DMA1LPEN))
#define __HAL_RCC_DMA2_CLK_SLEEP_DISABLE()    (RCC->AHB1LPENR &= ~(RCC_AHB1LPENR_DMA2LPEN))

#define __HAL_RCC_TIM5_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_TIM5LPEN))
#define __HAL_RCC_WWDG_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_WWDGLPEN))
#define __HAL_RCC_SPI2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_SPI2LPEN))
#define __HAL_RCC_USART2_CLK_SLEEP_ENABLE()  (RCC->APB1LPENR |= (RCC_APB1LPENR_USART2LPEN))
#define __HAL_RCC_I2C1_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C1LPEN))
#define __HAL_RCC_I2C2_CLK_SLEEP_ENABLE()    (RCC->APB1LPENR |= (RCC_APB1LPENR_I2C2LPEN))
#define __HAL_RCC_PWR_CLK_SLEEP_ENABLE()     (RCC->APB1LPENR |= (RCC_APB1LPENR_PWRLPEN))

#define __HAL_RCC_TIM5_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_TIM5LPEN))
#define __HAL_RCC_WWDG_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_WWDGLPEN))
#define __HAL_RCC_SPI2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_SPI2LPEN))
#define __HAL_RCC_USART2_CLK_SLEEP_DISABLE() (RCC->APB1LPENR &= ~(RCC_APB1LPENR_USART2LPEN))
#define __HAL_RCC_I2C1_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C1LPEN))
#define __HAL_RCC_I2C2_CLK_SLEEP_DISABLE()   (RCC->APB1LPENR &= ~(RCC_APB1LPENR_I2C2LPEN))
#define __HAL_RCC_PWR_CLK_SLEEP_DISABLE()    (RCC->APB1LPENR &= ~(RCC_APB1LPENR_PWRLPEN))

#define __HAL_RCC_TIM1_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM1LPEN))
#define __HAL_RCC_USART1_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_USART1LPEN))
#define __HAL_RCC_USART6_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_USART6LPEN))
#define __HAL_RCC_ADC1_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_ADC1LPEN))
#define __HAL_RCC_SPI1_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_SPI1LPEN))
#define __HAL_RCC_SYSCFG_CLK_SLEEP_ENABLE()  (RCC->APB2LPENR |= (RCC_APB2LPENR_SYSCFGLPEN))
#define __HAL_RCC_TIM9_CLK_SLEEP_ENABLE()    (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM9LPEN))
#define __HAL_RCC_TIM11_CLK_SLEEP_ENABLE()   (RCC->APB2LPENR |= (RCC_APB2LPENR_TIM11LPEN))

#define __HAL_RCC_TIM1_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM1LPEN))
#define __HAL_RCC_USART1_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_USART1LPEN))
#define __HAL_RCC_USART6_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_USART6LPEN))
#define __HAL_RCC_ADC1_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_ADC1LPEN))
#define __HAL_RCC_SPI1_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SPI1LPEN))
#define __HAL_RCC_SYSCFG_CLK_SLEEP_DISABLE() (RCC->APB2LPENR &= ~(RCC_APB2LPENR_SYSCFGLPEN))
#define __HAL_RCC_TIM9_CLK_SLEEP_DISABLE()   (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM9LPEN))
#define __HAL_RCC_TIM11_CLK_SLEEP_DISABLE()  (RCC->APB2LPENR &= ~(RCC_APB2LPENR_TIM11LPEN))

#define __HAL_RCC_HSI_ENABLE() (*(__IO uint32_t *) RCC_CR_HSION_BB = ENABLE)
#define __HAL_RCC_HSI_DISABLE() (*(__IO uint32_t *) RCC_CR_HSION_BB = DISABLE)

#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(__HSICalibrationValue__) (MODIFY_REG(RCC->CR,\
                                                                        RCC_CR_HSITRIM, (uint32_t)(__HSICalibrationValue__) << RCC_CR_HSITRIM_Pos))

#define __HAL_RCC_LSI_ENABLE() (*(__IO uint32_t *) RCC_CSR_LSION_BB = ENABLE)
#define __HAL_RCC_LSI_DISABLE() (*(__IO uint32_t *) RCC_CSR_LSION_BB = DISABLE)

#define __HAL_RCC_HSE_CONFIG(__STATE__)                         \
  do {                                        \
    if ((__STATE__) == RCC_HSE_ON)            \
    {                                         \
      SET_BIT(RCC->CR, RCC_CR_HSEON);         \
    }                                         \
    else if ((__STATE__) == RCC_HSE_BYPASS)   \
    {                                         \
      SET_BIT(RCC->CR, RCC_CR_HSEBYP);        \
      SET_BIT(RCC->CR, RCC_CR_HSEON);         \
    }                                         \
    else                                      \
    {                                         \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEON);       \
      CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);      \
    }                                         \
  } while(0U)

#define __HAL_RCC_LSE_CONFIG(__STATE__) \
  do {                                       \
    if((__STATE__) == RCC_LSE_ON)            \
    {                                        \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
    }                                        \
    else if((__STATE__) == RCC_LSE_BYPASS)   \
    {                                        \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);   \
      SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);    \
    }                                        \
    else                                     \
    {                                        \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);  \
      CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP); \
    }                                        \
  } while(0U)

#define __HAL_RCC_RTC_ENABLE() (*(__IO uint32_t *) RCC_BDCR_RTCEN_BB = ENABLE)
#define __HAL_RCC_RTC_DISABLE() (*(__IO uint32_t *) RCC_BDCR_RTCEN_BB = DISABLE)

#define __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__) (((__RTCCLKSource__) & RCC_BDCR_RTCSEL) == RCC_BDCR_RTCSEL) ?    \
  MODIFY_REG(RCC->CFGR, RCC_CFGR_RTCPRE, ((__RTCCLKSource__) & 0xFFFFCFFU)) : CLEAR_BIT(RCC->CFGR, RCC_CFGR_RTCPRE)

#define __HAL_RCC_RTC_CONFIG(__RTCCLKSource__) do { __HAL_RCC_RTC_CLKPRESCALER(__RTCCLKSource__);    \
                                                    RCC->BDCR |= ((__RTCCLKSource__) & 0x00000FFFU);  \
                                                   } while(0U)

#define __HAL_RCC_GET_RTC_SOURCE() (READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL))

#define  __HAL_RCC_GET_RTC_HSE_PRESCALER() (READ_BIT(RCC->CFGR, RCC_CFGR_RTCPRE) | RCC_BDCR_RTCSEL)

#define __HAL_RCC_BACKUPRESET_FORCE() (*(__IO uint32_t *) RCC_BDCR_BDRST_BB = ENABLE)
#define __HAL_RCC_BACKUPRESET_RELEASE() (*(__IO uint32_t *) RCC_BDCR_BDRST_BB = DISABLE)

#define __HAL_RCC_PLL_ENABLE() (*(__IO uint32_t *) RCC_CR_PLLON_BB = ENABLE)
#define __HAL_RCC_PLL_DISABLE() (*(__IO uint32_t *) RCC_CR_PLLON_BB = DISABLE)

#define __HAL_RCC_PLL_PLLSOURCE_CONFIG(__PLLSOURCE__) MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC, (__PLLSOURCE__))

#define __HAL_RCC_PLL_PLLM_CONFIG(__PLLM__) MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLM, (__PLLM__))

#define __HAL_RCC_SYSCLK_CONFIG(__RCC_SYSCLKSOURCE__) MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__RCC_SYSCLKSOURCE__))

#define __HAL_RCC_GET_SYSCLK_SOURCE() (RCC->CFGR & RCC_CFGR_SWS)

#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC))

#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO1 | RCC_CFGR_MCO1PRE), ((__MCOCLKSOURCE__) | (__MCODIV__)))

#define __HAL_RCC_MCO2_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
  MODIFY_REG(RCC->CFGR, (RCC_CFGR_MCO2 | RCC_CFGR_MCO2PRE), ((__MCOCLKSOURCE__) | ((__MCODIV__) << 3U)));

#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE1_ADDRESS |= (__INTERRUPT__))

#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE1_ADDRESS &= (uint8_t)(~(__INTERRUPT__)))

#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE2_ADDRESS = (__INTERRUPT__))

#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIR & (__INTERRUPT__)) == (__INTERRUPT__))

#define __HAL_RCC_CLEAR_RESET_FLAGS() (RCC->CSR |= RCC_CSR_RMVF)

#define RCC_FLAG_MASK  ((uint8_t)0x1FU)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5U)\
                                          == 1U)? RCC->CR :((((__FLAG__) >> 5U) == 2U) ? RCC->BDCR :((((__FLAG__) >> 5U) == 3U)? RCC->CSR :RCC->CIR))) &\
                                        (1U << ((__FLAG__) & RCC_FLAG_MASK)))!= 0U)? 1U : 0U)

HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(const RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(const RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

void     HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void     HAL_RCC_EnableCSS(void);
void     HAL_RCC_DisableCSS(void);
uint32_t HAL_RCC_GetSysClockFreq(void);
uint32_t HAL_RCC_GetHCLKFreq(void);
uint32_t HAL_RCC_GetPCLK1Freq(void);
uint32_t HAL_RCC_GetPCLK2Freq(void);
void     HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void     HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

void HAL_RCC_NMI_IRQHandler(void);

void HAL_RCC_CSSCallback(void);

#define RCC_OFFSET                 (RCC_BASE - PERIPH_BASE)

#define RCC_CR_OFFSET              (RCC_OFFSET + 0x00U)
#define RCC_HSION_BIT_NUMBER       0x00U
#define RCC_CR_HSION_BB            (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32U) + (RCC_HSION_BIT_NUMBER * 4U))

#define RCC_CSSON_BIT_NUMBER       0x13U
#define RCC_CR_CSSON_BB            (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32U) + (RCC_CSSON_BIT_NUMBER * 4U))

#define RCC_PLLON_BIT_NUMBER       0x18U
#define RCC_CR_PLLON_BB            (PERIPH_BB_BASE + (RCC_CR_OFFSET * 32U) + (RCC_PLLON_BIT_NUMBER * 4U))

#define RCC_BDCR_OFFSET            (RCC_OFFSET + 0x70U)
#define RCC_RTCEN_BIT_NUMBER       0x0FU
#define RCC_BDCR_RTCEN_BB          (PERIPH_BB_BASE + (RCC_BDCR_OFFSET * 32U) + (RCC_RTCEN_BIT_NUMBER * 4U))

#define RCC_BDRST_BIT_NUMBER       0x10U
#define RCC_BDCR_BDRST_BB          (PERIPH_BB_BASE + (RCC_BDCR_OFFSET * 32U) + (RCC_BDRST_BIT_NUMBER * 4U))

#define RCC_CSR_OFFSET             (RCC_OFFSET + 0x74U)
#define RCC_LSION_BIT_NUMBER        0x00U
#define RCC_CSR_LSION_BB           (PERIPH_BB_BASE + (RCC_CSR_OFFSET * 32U) + (RCC_LSION_BIT_NUMBER * 4U))

#define RCC_CR_BYTE2_ADDRESS       0x40023802U

#define RCC_CIR_BYTE1_ADDRESS      ((uint32_t)(RCC_BASE + 0x0CU + 0x01U))

#define RCC_CIR_BYTE2_ADDRESS      ((uint32_t)(RCC_BASE + 0x0CU + 0x02U))

#define RCC_BDCR_BYTE0_ADDRESS     (PERIPH_BASE + RCC_BDCR_OFFSET)

#define RCC_DBP_TIMEOUT_VALUE      2U
#define RCC_LSE_TIMEOUT_VALUE      LSE_STARTUP_TIMEOUT

#define HSE_TIMEOUT_VALUE          HSE_STARTUP_TIMEOUT
#define HSI_TIMEOUT_VALUE          2U
#define LSI_TIMEOUT_VALUE          2U
#define CLOCKSWITCH_TIMEOUT_VALUE  5000U

#define IS_RCC_OSCILLATORTYPE(OSCILLATOR) ((OSCILLATOR) <= 15U)

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS))

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS))

#define IS_RCC_HSI(HSI) (((HSI) == RCC_HSI_OFF) || ((HSI) == RCC_HSI_ON))

#define IS_RCC_LSI(LSI) (((LSI) == RCC_LSI_OFF) || ((LSI) == RCC_LSI_ON))

#define IS_RCC_PLL(PLL) (((PLL) == RCC_PLL_NONE) ||((PLL) == RCC_PLL_OFF) || ((PLL) == RCC_PLL_ON))

#define IS_RCC_PLLSOURCE(SOURCE) (((SOURCE) == RCC_PLLSOURCE_HSI) || \
                                  ((SOURCE) == RCC_PLLSOURCE_HSE))

#define IS_RCC_SYSCLKSOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSOURCE_HSI) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_HSE) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_PLLCLK) || \
                                     ((SOURCE) == RCC_SYSCLKSOURCE_PLLRCLK))

#define IS_RCC_RTCCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_RTCCLKSOURCE_LSE) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV2) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV3) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV4) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV5) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV6) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV7) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV8) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV9) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV10) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV11) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV12) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV13) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV14) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV15) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV16) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV17) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV18) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV19) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV20) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV21) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV22) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV23) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV24) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV25) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV26) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV27) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV28) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV29) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV30) || \
                                         ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV31))

#define IS_RCC_PLLM_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 63U))

#define IS_RCC_PLLP_VALUE(VALUE) (((VALUE) == 2U) || ((VALUE) == 4U) || ((VALUE) == 6U) || ((VALUE) == 8U))

#define IS_RCC_PLLQ_VALUE(VALUE) ((2U <= (VALUE)) && ((VALUE) <= 15U))

#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_DIV1)   || ((HCLK) == RCC_SYSCLK_DIV2)   || \
                           ((HCLK) == RCC_SYSCLK_DIV4)   || ((HCLK) == RCC_SYSCLK_DIV8)   || \
                           ((HCLK) == RCC_SYSCLK_DIV16)  || ((HCLK) == RCC_SYSCLK_DIV64)  || \
                           ((HCLK) == RCC_SYSCLK_DIV128) || ((HCLK) == RCC_SYSCLK_DIV256) || \
                           ((HCLK) == RCC_SYSCLK_DIV512))

#define IS_RCC_CLOCKTYPE(CLK) ((1U <= (CLK)) && ((CLK) <= 15U))

#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_DIV1) || ((PCLK) == RCC_HCLK_DIV2) || \
                           ((PCLK) == RCC_HCLK_DIV4) || ((PCLK) == RCC_HCLK_DIV8) || \
                           ((PCLK) == RCC_HCLK_DIV16))

#define IS_RCC_MCO(MCOx) (((MCOx) == RCC_MCO1) || ((MCOx) == RCC_MCO2))

#define IS_RCC_MCO1SOURCE(SOURCE) (((SOURCE) == RCC_MCO1SOURCE_HSI) || ((SOURCE) == RCC_MCO1SOURCE_LSE) || \
                                   ((SOURCE) == RCC_MCO1SOURCE_HSE) || ((SOURCE) == RCC_MCO1SOURCE_PLLCLK))

#define IS_RCC_MCODIV(DIV) (((DIV) == RCC_MCODIV_1)  || ((DIV) == RCC_MCODIV_2) || \
                            ((DIV) == RCC_MCODIV_3) || ((DIV) == RCC_MCODIV_4) || \
                            ((DIV) == RCC_MCODIV_5))
#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1FU)

#ifdef __cplusplus
}
#endif

#endif
