#ifndef __STM32F4xx_LL_UTILS_H
#define __STM32F4xx_LL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#define LL_MAX_DELAY                  0xFFFFFFFFU

#define UID_BASE_ADDRESS              UID_BASE

#define FLASHSIZE_BASE_ADDRESS        FLASHSIZE_BASE

#define PACKAGE_BASE_ADDRESS          PACKAGE_BASE

typedef struct
{
  uint32_t PLLM;

  uint32_t PLLN;

  uint32_t PLLP;
} LL_UTILS_PLLInitTypeDef;

typedef struct
{
  uint32_t AHBCLKDivider;

  uint32_t APB1CLKDivider;

  uint32_t APB2CLKDivider;

} LL_UTILS_ClkInitTypeDef;

#define LL_UTILS_HSEBYPASS_OFF        0x00000000U
#define LL_UTILS_HSEBYPASS_ON         0x00000001U

#define LL_UTILS_PACKAGETYPE_WLCSP36_UFQFPN48_LQFP64                        0x00000000U
#define LL_UTILS_PACKAGETYPE_WLCSP168_FBGA169_LQFP100_LQFP64_UFQFPN48       0x00000100U
#define LL_UTILS_PACKAGETYPE_WLCSP64_WLCSP81_LQFP176_UFBGA176               0x00000200U
#define LL_UTILS_PACKAGETYPE_LQFP144_UFBGA144_UFBGA144_UFBGA100             0x00000300U
#define LL_UTILS_PACKAGETYPE_LQFP100_LQFP208_TFBGA216                       0x00000400U
#define LL_UTILS_PACKAGETYPE_LQFP208_TFBGA216                               0x00000500U
#define LL_UTILS_PACKAGETYPE_TQFP64_UFBGA144_LQFP144                        0x00000700U

__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE_ADDRESS)));
}

__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 4U))));
}

__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 8U))));
}

__STATIC_INLINE uint32_t LL_GetFlashSize(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)FLASHSIZE_BASE_ADDRESS)) & 0xFFFF);
}

__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)PACKAGE_BASE_ADDRESS)) & 0x0700U);
}

__STATIC_INLINE void LL_InitTick(uint32_t HCLKFrequency, uint32_t Ticks)
{

  SysTick->LOAD  = (uint32_t)((HCLKFrequency / Ticks) - 1UL);
  SysTick->VAL   = 0UL;
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;
}

void        LL_Init1msTick(uint32_t HCLKFrequency);
void        LL_mDelay(uint32_t Delay);

void        LL_SetSystemCoreClock(uint32_t HCLKFrequency);
ErrorStatus LL_SetFlashLatency(uint32_t HCLK_Frequency);
ErrorStatus LL_PLL_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                         LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
ErrorStatus LL_PLL_ConfigSystemClock_HSE(uint32_t HSEFrequency, uint32_t HSEBypass,
                                         LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct, LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);

#ifdef __cplusplus
}
#endif

#endif
