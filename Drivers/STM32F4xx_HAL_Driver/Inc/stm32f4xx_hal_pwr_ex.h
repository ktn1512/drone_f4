#ifndef __STM32F4xx_HAL_PWR_EX_H
#define __STM32F4xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define PWR_MAINREGULATOR_UNDERDRIVE_ON                       PWR_CR_MRUDS
#define PWR_LOWPOWERREGULATOR_UNDERDRIVE_ON                   ((uint32_t)(PWR_CR_LPDS | PWR_CR_LPUDS))

#define PWR_FLAG_ODRDY                  PWR_CSR_ODRDY
#define PWR_FLAG_ODSWRDY                PWR_CSR_ODSWRDY
#define PWR_FLAG_UDRDY                  PWR_CSR_UDSWRDY

#endif

#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
#define PWR_REGULATOR_VOLTAGE_SCALE1         PWR_CR_VOS
#define PWR_REGULATOR_VOLTAGE_SCALE2         0x00000000U
#else
#define PWR_REGULATOR_VOLTAGE_SCALE1         PWR_CR_VOS
#define PWR_REGULATOR_VOLTAGE_SCALE2         PWR_CR_VOS_1
#define PWR_REGULATOR_VOLTAGE_SCALE3         PWR_CR_VOS_0
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define PWR_WAKEUP_PIN2                 0x00000080U
#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define PWR_WAKEUP_PIN3                 0x00000040U
#endif

#endif

#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)

#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg = 0x00U;                        \
                                                            MODIFY_REG(PWR->CR, PWR_CR_VOS, (__REGULATOR__));   \
                                                               \
                                                            tmpreg = READ_BIT(PWR->CR, PWR_CR_VOS);             \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0U)
#else

#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg = 0x00U;                        \
                                                            MODIFY_REG(PWR->CR, PWR_CR_VOS, (__REGULATOR__));   \
                                                               \
                                                            tmpreg = READ_BIT(PWR->CR, PWR_CR_VOS);             \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0U)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)

#define __HAL_PWR_OVERDRIVE_ENABLE() (*(__IO uint32_t *) CR_ODEN_BB = ENABLE)
#define __HAL_PWR_OVERDRIVE_DISABLE() (*(__IO uint32_t *) CR_ODEN_BB = DISABLE)

#define __HAL_PWR_OVERDRIVESWITCHING_ENABLE() (*(__IO uint32_t *) CR_ODSWEN_BB = ENABLE)
#define __HAL_PWR_OVERDRIVESWITCHING_DISABLE() (*(__IO uint32_t *) CR_ODSWEN_BB = DISABLE)

#define __HAL_PWR_UNDERDRIVE_ENABLE() (PWR->CR |= (uint32_t)PWR_CR_UDEN)
#define __HAL_PWR_UNDERDRIVE_DISABLE() (PWR->CR &= (uint32_t)(~PWR_CR_UDEN))

#define __HAL_PWR_GET_ODRUDR_FLAG(__FLAG__) ((PWR->CSR & (__FLAG__)) == (__FLAG__))

#define __HAL_PWR_CLEAR_ODRUDR_FLAG() (PWR->CSR |= PWR_FLAG_UDRDY)

#endif

void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void);
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void);
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void);
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F401xC) ||\
    defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
void HAL_PWREx_EnableMainRegulatorLowVoltage(void);
void HAL_PWREx_DisableMainRegulatorLowVoltage(void);
void HAL_PWREx_EnableLowRegulatorLowVoltage(void);
void HAL_PWREx_DisableLowRegulatorLowVoltage(void);
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
HAL_StatusTypeDef HAL_PWREx_EnableOverDrive(void);
HAL_StatusTypeDef HAL_PWREx_DisableOverDrive(void);
HAL_StatusTypeDef HAL_PWREx_EnterUnderDriveSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
#endif

#define FPDS_BIT_NUMBER          PWR_CR_FPDS_Pos
#define CR_FPDS_BB               (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (FPDS_BIT_NUMBER * 4U))

#define ODEN_BIT_NUMBER          PWR_CR_ODEN_Pos
#define CR_ODEN_BB               (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (ODEN_BIT_NUMBER * 4U))

#define ODSWEN_BIT_NUMBER        PWR_CR_ODSWEN_Pos
#define CR_ODSWEN_BB             (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (ODSWEN_BIT_NUMBER * 4U))

#define MRLVDS_BIT_NUMBER        PWR_CR_MRLVDS_Pos
#define CR_MRLVDS_BB             (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (MRLVDS_BIT_NUMBER * 4U))

#define LPLVDS_BIT_NUMBER        PWR_CR_LPLVDS_Pos
#define CR_LPLVDS_BB             (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (LPLVDS_BIT_NUMBER * 4U))

#define BRE_BIT_NUMBER   PWR_CSR_BRE_Pos
#define CSR_BRE_BB      (uint32_t)(PERIPH_BB_BASE + (PWR_CSR_OFFSET_BB * 32U) + (BRE_BIT_NUMBER * 4U))

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_PWR_REGULATOR_UNDERDRIVE(REGULATOR) (((REGULATOR) == PWR_MAINREGULATOR_UNDERDRIVE_ON) || \
                                                ((REGULATOR) == PWR_LOWPOWERREGULATOR_UNDERDRIVE_ON))
#endif

#if defined(STM32F405xx) || defined(STM32F407xx) || defined(STM32F415xx) || defined(STM32F417xx)
#define IS_PWR_VOLTAGE_SCALING_RANGE(VOLTAGE) (((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                               ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE2))
#else
#define IS_PWR_VOLTAGE_SCALING_RANGE(VOLTAGE) (((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                               ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE2) || \
                                               ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE3))
#endif

#if defined(STM32F446xx)
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || ((PIN) == PWR_WAKEUP_PIN2))
#elif defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F412Zx) ||\
      defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
      defined(STM32F423xx)
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3))
#else
#define IS_PWR_WAKEUP_PIN(PIN) ((PIN) == PWR_WAKEUP_PIN1)
#endif

#ifdef __cplusplus
}
#endif

#endif
