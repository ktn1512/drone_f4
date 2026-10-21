#ifndef __STM32F4xx_LL_CORTEX_H
#define __STM32F4xx_LL_CORTEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#define LL_SYSTICK_CLKSOURCE_HCLK_DIV8     0x00000000U
#define LL_SYSTICK_CLKSOURCE_HCLK          SysTick_CTRL_CLKSOURCE_Msk

#define LL_HANDLER_FAULT_USG               SCB_SHCSR_USGFAULTENA_Msk
#define LL_HANDLER_FAULT_BUS               SCB_SHCSR_BUSFAULTENA_Msk
#define LL_HANDLER_FAULT_MEM               SCB_SHCSR_MEMFAULTENA_Msk

#if __MPU_PRESENT

#define LL_MPU_CTRL_HFNMI_PRIVDEF_NONE     0x00000000U
#define LL_MPU_CTRL_HARDFAULT_NMI          MPU_CTRL_HFNMIENA_Msk
#define LL_MPU_CTRL_PRIVILEGED_DEFAULT     MPU_CTRL_PRIVDEFENA_Msk
#define LL_MPU_CTRL_HFNMI_PRIVDEF          (MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk)

#define LL_MPU_REGION_NUMBER0              0x00U
#define LL_MPU_REGION_NUMBER1              0x01U
#define LL_MPU_REGION_NUMBER2              0x02U
#define LL_MPU_REGION_NUMBER3              0x03U
#define LL_MPU_REGION_NUMBER4              0x04U
#define LL_MPU_REGION_NUMBER5              0x05U
#define LL_MPU_REGION_NUMBER6              0x06U
#define LL_MPU_REGION_NUMBER7              0x07U

#define LL_MPU_REGION_SIZE_32B             (0x04U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_64B             (0x05U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_128B            (0x06U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_256B            (0x07U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_512B            (0x08U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_1KB             (0x09U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_2KB             (0x0AU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_4KB             (0x0BU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_8KB             (0x0CU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_16KB            (0x0DU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_32KB            (0x0EU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_64KB            (0x0FU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_128KB           (0x10U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_256KB           (0x11U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_512KB           (0x12U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_1MB             (0x13U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_2MB             (0x14U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_4MB             (0x15U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_8MB             (0x16U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_16MB            (0x17U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_32MB            (0x18U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_64MB            (0x19U << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_128MB           (0x1AU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_256MB           (0x1BU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_512MB           (0x1CU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_1GB             (0x1DU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_2GB             (0x1EU << MPU_RASR_SIZE_Pos)
#define LL_MPU_REGION_SIZE_4GB             (0x1FU << MPU_RASR_SIZE_Pos)

#define LL_MPU_REGION_NO_ACCESS            (0x00U << MPU_RASR_AP_Pos)
#define LL_MPU_REGION_PRIV_RW              (0x01U << MPU_RASR_AP_Pos)
#define LL_MPU_REGION_PRIV_RW_URO          (0x02U << MPU_RASR_AP_Pos)
#define LL_MPU_REGION_FULL_ACCESS          (0x03U << MPU_RASR_AP_Pos)
#define LL_MPU_REGION_PRIV_RO              (0x05U << MPU_RASR_AP_Pos)
#define LL_MPU_REGION_PRIV_RO_URO          (0x06U << MPU_RASR_AP_Pos)

#define LL_MPU_TEX_LEVEL0                  (0x00U << MPU_RASR_TEX_Pos)
#define LL_MPU_TEX_LEVEL1                  (0x01U << MPU_RASR_TEX_Pos)
#define LL_MPU_TEX_LEVEL2                  (0x02U << MPU_RASR_TEX_Pos)
#define LL_MPU_TEX_LEVEL4                  (0x04U << MPU_RASR_TEX_Pos)

#define LL_MPU_INSTRUCTION_ACCESS_ENABLE   0x00U
#define LL_MPU_INSTRUCTION_ACCESS_DISABLE  MPU_RASR_XN_Msk

#define LL_MPU_ACCESS_SHAREABLE            MPU_RASR_S_Msk
#define LL_MPU_ACCESS_NOT_SHAREABLE        0x00U

#define LL_MPU_ACCESS_CACHEABLE            MPU_RASR_C_Msk
#define LL_MPU_ACCESS_NOT_CACHEABLE        0x00U

#define LL_MPU_ACCESS_BUFFERABLE           MPU_RASR_B_Msk
#define LL_MPU_ACCESS_NOT_BUFFERABLE       0x00U

#endif

__STATIC_INLINE uint32_t LL_SYSTICK_IsActiveCounterFlag(void)
{
  return ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk));
}

__STATIC_INLINE void LL_SYSTICK_SetClkSource(uint32_t Source)
{
  if (Source == LL_SYSTICK_CLKSOURCE_HCLK)
  {
    SET_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
  else
  {
    CLEAR_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
  }
}

__STATIC_INLINE uint32_t LL_SYSTICK_GetClkSource(void)
{
  return READ_BIT(SysTick->CTRL, LL_SYSTICK_CLKSOURCE_HCLK);
}

__STATIC_INLINE void LL_SYSTICK_EnableIT(void)
{
  SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

__STATIC_INLINE void LL_SYSTICK_DisableIT(void)
{
  CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}

__STATIC_INLINE uint32_t LL_SYSTICK_IsEnabledIT(void)
{
  return (READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk) == (SysTick_CTRL_TICKINT_Msk));
}

__STATIC_INLINE void LL_LPM_EnableSleep(void)
{

  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

__STATIC_INLINE void LL_LPM_EnableDeepSleep(void)
{

  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));
}

__STATIC_INLINE void LL_LPM_EnableSleepOnExit(void)
{

  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

__STATIC_INLINE void LL_LPM_DisableSleepOnExit(void)
{

  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

__STATIC_INLINE void LL_LPM_EnableEventOnPend(void)
{

  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

__STATIC_INLINE void LL_LPM_DisableEventOnPend(void)
{

  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

__STATIC_INLINE void LL_LPM_ClearEvent(void)
{
  __SEV();
  __WFE();
}

__STATIC_INLINE void LL_HANDLER_EnableFault(uint32_t Fault)
{

  SET_BIT(SCB->SHCSR, Fault);
}

__STATIC_INLINE void LL_HANDLER_DisableFault(uint32_t Fault)
{

  CLEAR_BIT(SCB->SHCSR, Fault);
}

__STATIC_INLINE uint32_t LL_CPUID_GetImplementer(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_IMPLEMENTER_Msk) >> SCB_CPUID_IMPLEMENTER_Pos);
}

__STATIC_INLINE uint32_t LL_CPUID_GetVariant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_VARIANT_Msk) >> SCB_CPUID_VARIANT_Pos);
}

__STATIC_INLINE uint32_t LL_CPUID_GetConstant(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_ARCHITECTURE_Msk) >> SCB_CPUID_ARCHITECTURE_Pos);
}

__STATIC_INLINE uint32_t LL_CPUID_GetParNo(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_PARTNO_Msk) >> SCB_CPUID_PARTNO_Pos);
}

__STATIC_INLINE uint32_t LL_CPUID_GetRevision(void)
{
  return (uint32_t)(READ_BIT(SCB->CPUID, SCB_CPUID_REVISION_Msk) >> SCB_CPUID_REVISION_Pos);
}

#if __MPU_PRESENT

__STATIC_INLINE void LL_MPU_Enable(uint32_t Options)
{

  WRITE_REG(MPU->CTRL, (MPU_CTRL_ENABLE_Msk | Options));

  __DSB();

  __ISB();
}

__STATIC_INLINE void LL_MPU_Disable(void)
{

  __DMB();

  WRITE_REG(MPU->CTRL, 0U);
}

__STATIC_INLINE uint32_t LL_MPU_IsEnabled(void)
{
  return (READ_BIT(MPU->CTRL, MPU_CTRL_ENABLE_Msk) == (MPU_CTRL_ENABLE_Msk));
}

__STATIC_INLINE void LL_MPU_EnableRegion(uint32_t Region)
{

  WRITE_REG(MPU->RNR, Region);

  SET_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

__STATIC_INLINE void LL_MPU_ConfigRegion(uint32_t Region, uint32_t SubRegionDisable, uint32_t Address, uint32_t Attributes)
{

  WRITE_REG(MPU->RNR, Region);

  WRITE_REG(MPU->RBAR, (Address & 0xFFFFFFE0U));

  WRITE_REG(MPU->RASR, (MPU_RASR_ENABLE_Msk | Attributes | (SubRegionDisable << MPU_RASR_SRD_Pos)));
}

__STATIC_INLINE void LL_MPU_DisableRegion(uint32_t Region)
{

  WRITE_REG(MPU->RNR, Region);

  CLEAR_BIT(MPU->RASR, MPU_RASR_ENABLE_Msk);
}

#endif

#ifdef __cplusplus
}
#endif

#endif
