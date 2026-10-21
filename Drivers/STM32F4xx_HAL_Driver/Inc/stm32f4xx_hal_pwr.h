#ifndef __STM32F4xx_HAL_PWR_H
#define __STM32F4xx_HAL_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t PVDLevel;

  uint32_t Mode;
}PWR_PVDTypeDef;

#define PWR_WAKEUP_PIN1                 0x00000100U

#define PWR_PVDLEVEL_0                  PWR_CR_PLS_LEV0
#define PWR_PVDLEVEL_1                  PWR_CR_PLS_LEV1
#define PWR_PVDLEVEL_2                  PWR_CR_PLS_LEV2
#define PWR_PVDLEVEL_3                  PWR_CR_PLS_LEV3
#define PWR_PVDLEVEL_4                  PWR_CR_PLS_LEV4
#define PWR_PVDLEVEL_5                  PWR_CR_PLS_LEV5
#define PWR_PVDLEVEL_6                  PWR_CR_PLS_LEV6
#define PWR_PVDLEVEL_7                  PWR_CR_PLS_LEV7

#define PWR_PVD_MODE_NORMAL                 0x00000000U
#define PWR_PVD_MODE_IT_RISING              0x00010001U
#define PWR_PVD_MODE_IT_FALLING             0x00010002U
#define PWR_PVD_MODE_IT_RISING_FALLING      0x00010003U
#define PWR_PVD_MODE_EVENT_RISING           0x00020001U
#define PWR_PVD_MODE_EVENT_FALLING          0x00020002U
#define PWR_PVD_MODE_EVENT_RISING_FALLING   0x00020003U

#define PWR_MAINREGULATOR_ON                        0x00000000U
#define PWR_LOWPOWERREGULATOR_ON                    PWR_CR_LPDS

#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)
#define PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR ((uint8_t)0x03)

#define PWR_STOPENTRY_WFI               ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE               ((uint8_t)0x02)
#define PWR_STOPENTRY_WFE_NO_EVT_CLEAR  ((uint8_t)0x03)

#define PWR_FLAG_WU                     PWR_CSR_WUF
#define PWR_FLAG_SB                     PWR_CSR_SBF
#define PWR_FLAG_PVDO                   PWR_CSR_PVDO
#define PWR_FLAG_BRR                    PWR_CSR_BRR
#define PWR_FLAG_VOSRDY                 PWR_CSR_VOSRDY

#define __HAL_PWR_GET_FLAG(__FLAG__) ((PWR->CSR & (__FLAG__)) == (__FLAG__))

#define __HAL_PWR_CLEAR_FLAG(__FLAG__) (PWR->CR |=  (__FLAG__) << 2U)

#define __HAL_PWR_PVD_EXTI_ENABLE_IT()   (EXTI->IMR |= (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_DISABLE_IT()  (EXTI->IMR &= ~(PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()   (EXTI->EMR |= (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()  (EXTI->EMR &= ~(PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR, PWR_EXTI_LINE_PVD)

#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)

#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR, PWR_EXTI_LINE_PVD)

#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE()   do{__HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();\
                                                             __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();\
                                                            }while(0U)

#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE()  do{__HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();\
                                                             __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();\
                                                            }while(0U)

#define __HAL_PWR_PVD_EXTI_GET_FLAG()  (EXTI->PR & (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()  (EXTI->PR = (PWR_EXTI_LINE_PVD))

#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() (EXTI->SWIER |= (PWR_EXTI_LINE_PVD))

#include "stm32f4xx_hal_pwr_ex.h"

void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);

void HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinx);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

void HAL_PWR_PVD_IRQHandler(void);
void HAL_PWR_PVDCallback(void);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

#define PWR_EXTI_LINE_PVD  ((uint32_t)EXTI_IMR_MR16)

#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)
#define PWR_CR_OFFSET            0x00U
#define PWR_CSR_OFFSET           0x04U
#define PWR_CR_OFFSET_BB         (PWR_OFFSET + PWR_CR_OFFSET)
#define PWR_CSR_OFFSET_BB        (PWR_OFFSET + PWR_CSR_OFFSET)

#define DBP_BIT_NUMBER   PWR_CR_DBP_Pos
#define CR_DBP_BB        (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (DBP_BIT_NUMBER * 4U))

#define PVDE_BIT_NUMBER  PWR_CR_PVDE_Pos
#define CR_PVDE_BB       (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (PVDE_BIT_NUMBER * 4U))

#define VOS_BIT_NUMBER  PWR_CR_VOS_Pos
#define CR_VOS_BB      (uint32_t)(PERIPH_BB_BASE + (PWR_CR_OFFSET_BB * 32U) + (VOS_BIT_NUMBER * 4U))

#define EWUP_BIT_NUMBER  PWR_CSR_EWUP_Pos
#define CSR_EWUP_BB      (PERIPH_BB_BASE + (PWR_CSR_OFFSET_BB * 32U) + (EWUP_BIT_NUMBER * 4U))

#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_0) || ((LEVEL) == PWR_PVDLEVEL_1)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_2) || ((LEVEL) == PWR_PVDLEVEL_3)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_4) || ((LEVEL) == PWR_PVDLEVEL_5)|| \
                                 ((LEVEL) == PWR_PVDLEVEL_6) || ((LEVEL) == PWR_PVDLEVEL_7))
#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_IT_RISING)|| ((MODE) == PWR_PVD_MODE_IT_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING) || \
                              ((MODE) == PWR_PVD_MODE_EVENT_FALLING) || ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING) || \
                              ((MODE) == PWR_PVD_MODE_NORMAL))
#define IS_PWR_REGULATOR(REGULATOR) (((REGULATOR) == PWR_MAINREGULATOR_ON) || \
                                     ((REGULATOR) == PWR_LOWPOWERREGULATOR_ON))

#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || \
                                   ((ENTRY) == PWR_SLEEPENTRY_WFE) || \
                                   ((ENTRY) == PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR))

#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) || \
                                  ((ENTRY) == PWR_STOPENTRY_WFE) || \
                                  ((ENTRY) == PWR_STOPENTRY_WFE_NO_EVT_CLEAR))

#ifdef __cplusplus
}
#endif

#endif
