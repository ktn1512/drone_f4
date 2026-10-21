#ifndef __STM32F4xx_LL_GPIO_H
#define __STM32F4xx_LL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (GPIOA) || defined (GPIOB) || defined (GPIOC) || defined (GPIOD) || defined (GPIOE) || defined (GPIOF) || defined (GPIOG) || defined (GPIOH) || defined (GPIOI) || defined (GPIOJ) || defined (GPIOK)

#if defined(USE_FULL_LL_DRIVER)

#endif

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t Pin;

  uint32_t Mode;

  uint32_t Speed;

  uint32_t OutputType;

  uint32_t Pull;

  uint32_t Alternate;
} LL_GPIO_InitTypeDef;

#endif

#define LL_GPIO_PIN_0                      GPIO_BSRR_BS_0
#define LL_GPIO_PIN_1                      GPIO_BSRR_BS_1
#define LL_GPIO_PIN_2                      GPIO_BSRR_BS_2
#define LL_GPIO_PIN_3                      GPIO_BSRR_BS_3
#define LL_GPIO_PIN_4                      GPIO_BSRR_BS_4
#define LL_GPIO_PIN_5                      GPIO_BSRR_BS_5
#define LL_GPIO_PIN_6                      GPIO_BSRR_BS_6
#define LL_GPIO_PIN_7                      GPIO_BSRR_BS_7
#define LL_GPIO_PIN_8                      GPIO_BSRR_BS_8
#define LL_GPIO_PIN_9                      GPIO_BSRR_BS_9
#define LL_GPIO_PIN_10                     GPIO_BSRR_BS_10
#define LL_GPIO_PIN_11                     GPIO_BSRR_BS_11
#define LL_GPIO_PIN_12                     GPIO_BSRR_BS_12
#define LL_GPIO_PIN_13                     GPIO_BSRR_BS_13
#define LL_GPIO_PIN_14                     GPIO_BSRR_BS_14
#define LL_GPIO_PIN_15                     GPIO_BSRR_BS_15
#define LL_GPIO_PIN_ALL                    (GPIO_BSRR_BS_0 | GPIO_BSRR_BS_1  | GPIO_BSRR_BS_2  | \
                                           GPIO_BSRR_BS_3  | GPIO_BSRR_BS_4  | GPIO_BSRR_BS_5  | \
                                           GPIO_BSRR_BS_6  | GPIO_BSRR_BS_7  | GPIO_BSRR_BS_8  | \
                                           GPIO_BSRR_BS_9  | GPIO_BSRR_BS_10 | GPIO_BSRR_BS_11 | \
                                           GPIO_BSRR_BS_12 | GPIO_BSRR_BS_13 | GPIO_BSRR_BS_14 | \
                                           GPIO_BSRR_BS_15)

#define LL_GPIO_MODE_INPUT                 (0x00000000U)
#define LL_GPIO_MODE_OUTPUT                GPIO_MODER_MODER0_0
#define LL_GPIO_MODE_ALTERNATE             GPIO_MODER_MODER0_1
#define LL_GPIO_MODE_ANALOG                GPIO_MODER_MODER0

#define LL_GPIO_OUTPUT_PUSHPULL            (0x00000000U)
#define LL_GPIO_OUTPUT_OPENDRAIN           GPIO_OTYPER_OT_0

#define LL_GPIO_SPEED_FREQ_LOW             (0x00000000U)
#define LL_GPIO_SPEED_FREQ_MEDIUM          GPIO_OSPEEDER_OSPEEDR0_0
#define LL_GPIO_SPEED_FREQ_HIGH            GPIO_OSPEEDER_OSPEEDR0_1
#define LL_GPIO_SPEED_FREQ_VERY_HIGH       GPIO_OSPEEDER_OSPEEDR0

#define LL_GPIO_PULL_NO                    (0x00000000U)
#define LL_GPIO_PULL_UP                    GPIO_PUPDR_PUPDR0_0
#define LL_GPIO_PULL_DOWN                  GPIO_PUPDR_PUPDR0_1

#define LL_GPIO_AF_0                       (0x0000000U)
#define LL_GPIO_AF_1                       (0x0000001U)
#define LL_GPIO_AF_2                       (0x0000002U)
#define LL_GPIO_AF_3                       (0x0000003U)
#define LL_GPIO_AF_4                       (0x0000004U)
#define LL_GPIO_AF_5                       (0x0000005U)
#define LL_GPIO_AF_6                       (0x0000006U)
#define LL_GPIO_AF_7                       (0x0000007U)
#define LL_GPIO_AF_8                       (0x0000008U)
#define LL_GPIO_AF_9                       (0x0000009U)
#define LL_GPIO_AF_10                      (0x000000AU)
#define LL_GPIO_AF_11                      (0x000000BU)
#define LL_GPIO_AF_12                      (0x000000CU)
#define LL_GPIO_AF_13                      (0x000000DU)
#define LL_GPIO_AF_14                      (0x000000EU)
#define LL_GPIO_AF_15                      (0x000000FU)

#define LL_GPIO_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_GPIO_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

__STATIC_INLINE void LL_GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
  MODIFY_REG(GPIOx->MODER, (GPIO_MODER_MODER0 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}

__STATIC_INLINE uint32_t LL_GPIO_GetPinMode(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->MODER,
                             (GPIO_MODER_MODER0 << (POSITION_VAL(Pin) * 2U))) >> (POSITION_VAL(Pin) * 2U));
}

__STATIC_INLINE void LL_GPIO_SetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t PinMask, uint32_t OutputType)
{
  MODIFY_REG(GPIOx->OTYPER, PinMask, (PinMask * OutputType));
}

__STATIC_INLINE uint32_t LL_GPIO_GetPinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OTYPER, Pin) >> POSITION_VAL(Pin));
}

__STATIC_INLINE void LL_GPIO_SetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t  Speed)
{
  MODIFY_REG(GPIOx->OSPEEDR, (GPIO_OSPEEDER_OSPEEDR0 << (POSITION_VAL(Pin) * 2U)),
             (Speed << (POSITION_VAL(Pin) * 2U)));
}

__STATIC_INLINE uint32_t LL_GPIO_GetPinSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OSPEEDR,
                             (GPIO_OSPEEDER_OSPEEDR0 << (POSITION_VAL(Pin) * 2U))) >> (POSITION_VAL(Pin) * 2U));
}

__STATIC_INLINE void LL_GPIO_SetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->PUPDR, (GPIO_PUPDR_PUPDR0 << (POSITION_VAL(Pin) * 2U)), (Pull << (POSITION_VAL(Pin) * 2U)));
}

__STATIC_INLINE uint32_t LL_GPIO_GetPinPull(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->PUPDR,
                             (GPIO_PUPDR_PUPDR0 << (POSITION_VAL(Pin) * 2U))) >> (POSITION_VAL(Pin) * 2U));
}

__STATIC_INLINE void LL_GPIO_SetAFPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
  MODIFY_REG(GPIOx->AFR[0], (GPIO_AFRL_AFSEL0 << (POSITION_VAL(Pin) * 4U)),
             (Alternate << (POSITION_VAL(Pin) * 4U)));
}

__STATIC_INLINE uint32_t LL_GPIO_GetAFPin_0_7(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFR[0],
                             (GPIO_AFRL_AFSEL0 << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));
}

__STATIC_INLINE void LL_GPIO_SetAFPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
  MODIFY_REG(GPIOx->AFR[1], (GPIO_AFRH_AFSEL8 << (POSITION_VAL(Pin >> 8U) * 4U)),
             (Alternate << (POSITION_VAL(Pin >> 8U) * 4U)));
}

__STATIC_INLINE uint32_t LL_GPIO_GetAFPin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->AFR[1],
                             (GPIO_AFRH_AFSEL8 << (POSITION_VAL(Pin >> 8U) * 4U))) >> (POSITION_VAL(Pin >> 8U) * 4U));
}

__STATIC_INLINE void LL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  __IO uint32_t temp;
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  WRITE_REG(GPIOx->LCKR, PinMask);
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | PinMask);
  temp = READ_REG(GPIOx->LCKR);
  (void) temp;
}

__STATIC_INLINE uint32_t LL_GPIO_IsPinLocked(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->LCKR, PinMask) == (PinMask));
}

__STATIC_INLINE uint32_t LL_GPIO_IsAnyPinLocked(GPIO_TypeDef *GPIOx)
{
  return (READ_BIT(GPIOx->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK));
}

__STATIC_INLINE uint32_t LL_GPIO_ReadInputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDR));
}

__STATIC_INLINE uint32_t LL_GPIO_IsInputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->IDR, PinMask) == (PinMask));
}

__STATIC_INLINE void LL_GPIO_WriteOutputPort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
  WRITE_REG(GPIOx->ODR, PortValue);
}

__STATIC_INLINE uint32_t LL_GPIO_ReadOutputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->ODR));
}

__STATIC_INLINE uint32_t LL_GPIO_IsOutputPinSet(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  return (READ_BIT(GPIOx->ODR, PinMask) == (PinMask));
}

__STATIC_INLINE void LL_GPIO_SetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSRR, PinMask);
}

__STATIC_INLINE void LL_GPIO_ResetOutputPin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  WRITE_REG(GPIOx->BSRR, (PinMask << 16));
}

__STATIC_INLINE void LL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
  uint32_t odr = READ_REG(GPIOx->ODR);
  WRITE_REG(GPIOx->BSRR, ((odr & PinMask) << 16u) | (~odr & PinMask));
}

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_GPIO_DeInit(GPIO_TypeDef *GPIOx);
ErrorStatus LL_GPIO_Init(GPIO_TypeDef *GPIOx, LL_GPIO_InitTypeDef *GPIO_InitStruct);
void        LL_GPIO_StructInit(LL_GPIO_InitTypeDef *GPIO_InitStruct);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
