#ifndef __STM32F4xx_LL_PWR_H
#define __STM32F4xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined(PWR)

#define LL_PWR_CR_CSBF                     PWR_CR_CSBF
#define LL_PWR_CR_CWUF                     PWR_CR_CWUF

#define LL_PWR_CSR_WUF                     PWR_CSR_WUF
#define LL_PWR_CSR_SBF                     PWR_CSR_SBF
#define LL_PWR_CSR_PVDO                    PWR_CSR_PVDO
#define LL_PWR_CSR_VOS                     PWR_CSR_VOSRDY
#if defined(PWR_CSR_EWUP)
#define LL_PWR_CSR_EWUP1                   PWR_CSR_EWUP
#elif defined(PWR_CSR_EWUP1)
#define LL_PWR_CSR_EWUP1                   PWR_CSR_EWUP1
#endif
#if defined(PWR_CSR_EWUP2)
#define LL_PWR_CSR_EWUP2                   PWR_CSR_EWUP2
#endif
#if defined(PWR_CSR_EWUP3)
#define LL_PWR_CSR_EWUP3                   PWR_CSR_EWUP3
#endif

#if defined(PWR_CR_VOS_0)
#define LL_PWR_REGU_VOLTAGE_SCALE3         (PWR_CR_VOS_0)
#define LL_PWR_REGU_VOLTAGE_SCALE2         (PWR_CR_VOS_1)
#define LL_PWR_REGU_VOLTAGE_SCALE1         (PWR_CR_VOS_0 | PWR_CR_VOS_1)
#else
#define LL_PWR_REGU_VOLTAGE_SCALE1         (PWR_CR_VOS)
#define LL_PWR_REGU_VOLTAGE_SCALE2         0x00000000U
#endif

#define LL_PWR_MODE_STOP_MAINREGU             0x00000000U
#define LL_PWR_MODE_STOP_LPREGU               (PWR_CR_LPDS)
#if defined(PWR_CR_MRUDS) && defined(PWR_CR_LPUDS) && defined(PWR_CR_FPDS)
#define LL_PWR_MODE_STOP_MAINREGU_UNDERDRIVE  (PWR_CR_MRUDS | PWR_CR_FPDS)
#define LL_PWR_MODE_STOP_LPREGU_UNDERDRIVE    (PWR_CR_LPDS | PWR_CR_LPUDS | PWR_CR_FPDS)
#endif
#if defined(PWR_CR_MRLVDS) && defined(PWR_CR_LPLVDS) && defined(PWR_CR_FPDS)
#define LL_PWR_MODE_STOP_MAINREGU_DEEPSLEEP  (PWR_CR_MRLVDS | PWR_CR_FPDS)
#define LL_PWR_MODE_STOP_LPREGU_DEEPSLEEP    (PWR_CR_LPDS | PWR_CR_LPLVDS | PWR_CR_FPDS)
#endif
#define LL_PWR_MODE_STANDBY                   (PWR_CR_PDDS)

#define LL_PWR_REGU_DSMODE_MAIN        0x00000000U
#define LL_PWR_REGU_DSMODE_LOW_POWER   (PWR_CR_LPDS)

#define LL_PWR_PVDLEVEL_0                  (PWR_CR_PLS_LEV0)
#define LL_PWR_PVDLEVEL_1                  (PWR_CR_PLS_LEV1)
#define LL_PWR_PVDLEVEL_2                  (PWR_CR_PLS_LEV2)
#define LL_PWR_PVDLEVEL_3                  (PWR_CR_PLS_LEV3)
#define LL_PWR_PVDLEVEL_4                  (PWR_CR_PLS_LEV4)
#define LL_PWR_PVDLEVEL_5                  (PWR_CR_PLS_LEV5)
#define LL_PWR_PVDLEVEL_6                  (PWR_CR_PLS_LEV6)
#define LL_PWR_PVDLEVEL_7                  (PWR_CR_PLS_LEV7)

#if defined(PWR_CSR_EWUP)
#define LL_PWR_WAKEUP_PIN1                 (PWR_CSR_EWUP)
#endif
#if defined(PWR_CSR_EWUP1)
#define LL_PWR_WAKEUP_PIN1                 (PWR_CSR_EWUP1)
#endif
#if defined(PWR_CSR_EWUP2)
#define LL_PWR_WAKEUP_PIN2                 (PWR_CSR_EWUP2)
#endif
#if defined(PWR_CSR_EWUP3)
#define LL_PWR_WAKEUP_PIN3                 (PWR_CSR_EWUP3)
#endif

#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)

#if defined(PWR_CR_FISSR)

__STATIC_INLINE void LL_PWR_EnableFLASHInterfaceSTOP(void)
{
  SET_BIT(PWR->CR, PWR_CR_FISSR);
}

__STATIC_INLINE void LL_PWR_DisableFLASHInterfaceSTOP(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_FISSR);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledFLASHInterfaceSTOP(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_FISSR) == (PWR_CR_FISSR));
}
#endif

#if defined(PWR_CR_FMSSR)

__STATIC_INLINE void LL_PWR_EnableFLASHMemorySTOP(void)
{
  SET_BIT(PWR->CR, PWR_CR_FMSSR);
}

__STATIC_INLINE void LL_PWR_DisableFLASHMemorySTOP(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_FMSSR);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledFLASHMemorySTOP(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_FMSSR) == (PWR_CR_FMSSR));
}
#endif
#if defined(PWR_CR_UDEN)

__STATIC_INLINE void LL_PWR_EnableUnderDriveMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_UDEN);
}

__STATIC_INLINE void LL_PWR_DisableUnderDriveMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_UDEN);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledUnderDriveMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_UDEN) == (PWR_CR_UDEN));
}
#endif

#if defined(PWR_CR_ODSWEN)

__STATIC_INLINE void LL_PWR_EnableOverDriveSwitching(void)
{
  SET_BIT(PWR->CR, PWR_CR_ODSWEN);
}

__STATIC_INLINE void LL_PWR_DisableOverDriveSwitching(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_ODSWEN);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledOverDriveSwitching(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_ODSWEN) == (PWR_CR_ODSWEN));
}
#endif
#if defined(PWR_CR_ODEN)

__STATIC_INLINE void LL_PWR_EnableOverDriveMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_ODEN);
}

__STATIC_INLINE void LL_PWR_DisableOverDriveMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_ODEN);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledOverDriveMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_ODEN) == (PWR_CR_ODEN));
}
#endif
#if defined(PWR_CR_MRUDS)

__STATIC_INLINE void LL_PWR_EnableMainRegulatorDeepSleepUDMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_MRUDS);
}

__STATIC_INLINE void LL_PWR_DisableMainRegulatorDeepSleepUDMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_MRUDS);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledMainRegulatorDeepSleepUDMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_MRUDS) == (PWR_CR_MRUDS));
}
#endif

#if defined(PWR_CR_LPUDS)

__STATIC_INLINE void LL_PWR_EnableLowPowerRegulatorDeepSleepUDMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_LPUDS);
}

__STATIC_INLINE void LL_PWR_DisableLowPowerRegulatorDeepSleepUDMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_LPUDS);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledLowPowerRegulatorDeepSleepUDMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_LPUDS) == (PWR_CR_LPUDS));
}
#endif

#if defined(PWR_CR_MRLVDS)

__STATIC_INLINE void LL_PWR_EnableMainRegulatorLowVoltageMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_MRLVDS);
}

__STATIC_INLINE void LL_PWR_DisableMainRegulatorLowVoltageMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_MRLVDS);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledMainRegulatorLowVoltageMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_MRLVDS) == (PWR_CR_MRLVDS));
}
#endif

#if defined(PWR_CR_LPLVDS)

__STATIC_INLINE void LL_PWR_EnableLowPowerRegulatorLowVoltageMode(void)
{
  SET_BIT(PWR->CR, PWR_CR_LPLVDS);
}

__STATIC_INLINE void LL_PWR_DisableLowPowerRegulatorLowVoltageMode(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_LPLVDS);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledLowPowerRegulatorLowVoltageMode(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_LPLVDS) == (PWR_CR_LPLVDS));
}
#endif

__STATIC_INLINE void LL_PWR_SetRegulVoltageScaling(uint32_t VoltageScaling)
{
  MODIFY_REG(PWR->CR, PWR_CR_VOS, VoltageScaling);
}

__STATIC_INLINE uint32_t LL_PWR_GetRegulVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_VOS));
}

__STATIC_INLINE void LL_PWR_EnableFlashPowerDown(void)
{
  SET_BIT(PWR->CR, PWR_CR_FPDS);
}

__STATIC_INLINE void LL_PWR_DisableFlashPowerDown(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_FPDS);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashPowerDown(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_FPDS) == (PWR_CR_FPDS));
}

__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR, PWR_CR_DBP);
}

__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_DBP) == (PWR_CR_DBP));
}

__STATIC_INLINE void LL_PWR_EnableBkUpRegulator(void)
{
  SET_BIT(PWR->CSR, PWR_CSR_BRE);
}

__STATIC_INLINE void LL_PWR_DisableBkUpRegulator(void)
{
  CLEAR_BIT(PWR->CSR, PWR_CSR_BRE);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpRegulator(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_BRE) == (PWR_CSR_BRE));
}

__STATIC_INLINE void LL_PWR_SetRegulModeDS(uint32_t RegulMode)
{
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, RegulMode);
}

__STATIC_INLINE uint32_t LL_PWR_GetRegulModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_LPDS));
}

__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t PDMode)
{
#if defined(PWR_CR_MRUDS) && defined(PWR_CR_LPUDS) && defined(PWR_CR_FPDS)
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_FPDS | PWR_CR_LPUDS | PWR_CR_MRUDS), PDMode);
#elif defined(PWR_CR_MRLVDS) && defined(PWR_CR_LPLVDS) && defined(PWR_CR_FPDS)
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_FPDS | PWR_CR_LPLVDS | PWR_CR_MRLVDS), PDMode);
#else
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS), PDMode);
#endif
}

__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
#if defined(PWR_CR_MRUDS) && defined(PWR_CR_LPUDS) && defined(PWR_CR_FPDS)
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_FPDS | PWR_CR_LPUDS | PWR_CR_MRUDS)));
#elif defined(PWR_CR_MRLVDS) && defined(PWR_CR_LPLVDS) && defined(PWR_CR_FPDS)
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_FPDS | PWR_CR_LPLVDS | PWR_CR_MRLVDS)));
#else
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS)));
#endif
}

__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR, PWR_CR_PLS, PVDLevel);
}

__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_PLS));
}

__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR, PWR_CR_PVDE);
}

__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_PVDE);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_PVDE) == (PWR_CR_PVDE));
}

__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CSR, WakeUpPin);
}

__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CSR, WakeUpPin);
}

__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return (READ_BIT(PWR->CSR, WakeUpPin) == (WakeUpPin));
}

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_WUF) == (PWR_CSR_WUF));
}

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_SBF) == (PWR_CSR_SBF));
}

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRR(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_BRR) == (PWR_CSR_BRR));
}

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_PVDO) == (PWR_CSR_PVDO));
}

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return (READ_BIT(PWR->CSR, LL_PWR_CSR_VOS) == (LL_PWR_CSR_VOS));
}
#if defined(PWR_CR_ODEN)

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_OD(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_ODRDY) == (PWR_CSR_ODRDY));
}
#endif

#if defined(PWR_CR_ODSWEN)

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ODSW(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_ODSWRDY) == (PWR_CSR_ODSWRDY));
}
#endif

#if defined(PWR_CR_UDEN)

__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_UD(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_UDRDY) == (PWR_CSR_UDRDY));
}
#endif

__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  SET_BIT(PWR->CR, PWR_CR_CSBF);
}

__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  SET_BIT(PWR->CR, PWR_CR_CWUF);
}
#if defined(PWR_CSR_UDRDY)

__STATIC_INLINE void LL_PWR_ClearFlag_UD(void)
{
  WRITE_REG(PWR->CSR, PWR_CSR_UDRDY);
}
#endif

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_PWR_DeInit(void);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
