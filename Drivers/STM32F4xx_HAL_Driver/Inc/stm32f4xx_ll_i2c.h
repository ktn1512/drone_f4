#ifndef __STM32F4xx_LL_I2C_H
#define __STM32F4xx_LL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (I2C1) || defined (I2C2) || defined (I2C3)

#define LL_I2C_MAX_SPEED_STANDARD           100000U
#define LL_I2C_MAX_SPEED_FAST               400000U

#if defined(USE_FULL_LL_DRIVER)

#endif

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t PeripheralMode;

  uint32_t ClockSpeed;

  uint32_t DutyCycle;

#if  defined(I2C_FLTR_ANOFF)&&defined(I2C_FLTR_DNF)
  uint32_t AnalogFilter;

  uint32_t DigitalFilter;

#endif
  uint32_t OwnAddress1;

  uint32_t TypeAcknowledge;

  uint32_t OwnAddrSize;
} LL_I2C_InitTypeDef;

#endif

#define LL_I2C_SR1_SB                       I2C_SR1_SB
#define LL_I2C_SR1_ADDR                     I2C_SR1_ADDR
#define LL_I2C_SR1_BTF                      I2C_SR1_BTF
#define LL_I2C_SR1_ADD10                    I2C_SR1_ADD10
#define LL_I2C_SR1_STOPF                    I2C_SR1_STOPF
#define LL_I2C_SR1_RXNE                     I2C_SR1_RXNE
#define LL_I2C_SR1_TXE                      I2C_SR1_TXE
#define LL_I2C_SR1_BERR                     I2C_SR1_BERR
#define LL_I2C_SR1_ARLO                     I2C_SR1_ARLO
#define LL_I2C_SR1_AF                       I2C_SR1_AF
#define LL_I2C_SR1_OVR                      I2C_SR1_OVR
#define LL_I2C_SR1_PECERR                   I2C_ISR_PECERR
#define LL_I2C_SR1_TIMEOUT                  I2C_ISR_TIMEOUT
#define LL_I2C_SR1_SMALERT                  I2C_ISR_SMALERT
#define LL_I2C_SR2_MSL                      I2C_SR2_MSL
#define LL_I2C_SR2_BUSY                     I2C_SR2_BUSY
#define LL_I2C_SR2_TRA                      I2C_SR2_TRA
#define LL_I2C_SR2_GENCALL                  I2C_SR2_GENCALL
#define LL_I2C_SR2_SMBDEFAULT               I2C_SR2_SMBDEFAULT
#define LL_I2C_SR2_SMBHOST                  I2C_SR2_SMBHOST
#define LL_I2C_SR2_DUALF                    I2C_SR2_DUALF

#define LL_I2C_CR2_ITEVTEN                  I2C_CR2_ITEVTEN
#define LL_I2C_CR2_ITBUFEN                  I2C_CR2_ITBUFEN
#define LL_I2C_CR2_ITERREN                  I2C_CR2_ITERREN

#if defined(I2C_FLTR_ANOFF)

#define LL_I2C_ANALOGFILTER_ENABLE          0x00000000U
#define LL_I2C_ANALOGFILTER_DISABLE         I2C_FLTR_ANOFF

#endif

#define LL_I2C_OWNADDRESS1_7BIT             0x00004000U
#define LL_I2C_OWNADDRESS1_10BIT            (uint32_t)(I2C_OAR1_ADDMODE | 0x00004000U)

#define LL_I2C_DUTYCYCLE_2                  0x00000000U
#define LL_I2C_DUTYCYCLE_16_9               I2C_CCR_DUTY

#define LL_I2C_CLOCK_SPEED_STANDARD_MODE    0x00000000U
#define LL_I2C_CLOCK_SPEED_FAST_MODE        I2C_CCR_FS

#define LL_I2C_MODE_I2C                     0x00000000U
#define LL_I2C_MODE_SMBUS_HOST              (uint32_t)(I2C_CR1_SMBUS | I2C_CR1_SMBTYPE | I2C_CR1_ENARP)
#define LL_I2C_MODE_SMBUS_DEVICE            I2C_CR1_SMBUS
#define LL_I2C_MODE_SMBUS_DEVICE_ARP        (uint32_t)(I2C_CR1_SMBUS | I2C_CR1_ENARP)

#define LL_I2C_ACK                          I2C_CR1_ACK
#define LL_I2C_NACK                         0x00000000U

#define LL_I2C_DIRECTION_WRITE              I2C_SR2_TRA
#define LL_I2C_DIRECTION_READ               0x00000000U

#define LL_I2C_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_I2C_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

#define __LL_I2C_FREQ_HZ_TO_MHZ(__PCLK__)                               (uint32_t)((__PCLK__)/1000000U)

#define __LL_I2C_FREQ_MHZ_TO_HZ(__PCLK__)                               (uint32_t)((__PCLK__)*1000000U)

#define __LL_I2C_RISE_TIME(__FREQRANGE__, __SPEED__)                    (uint32_t)(((__SPEED__) <= LL_I2C_MAX_SPEED_STANDARD) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))

#define __LL_I2C_SPEED_TO_CCR(__PCLK__, __SPEED__, __DUTYCYCLE__)       (uint32_t)(((__SPEED__) <= LL_I2C_MAX_SPEED_STANDARD)? \
                                                                                  (__LL_I2C_SPEED_STANDARD_TO_CCR((__PCLK__), (__SPEED__))) : \
                                                                                  (__LL_I2C_SPEED_FAST_TO_CCR((__PCLK__), (__SPEED__), (__DUTYCYCLE__))))

#define __LL_I2C_SPEED_STANDARD_TO_CCR(__PCLK__, __SPEED__)             (uint32_t)(((((__PCLK__)/((__SPEED__) << 1U)) & I2C_CCR_CCR) < 4U)? 4U:((__PCLK__) / ((__SPEED__) << 1U)))

#define __LL_I2C_SPEED_FAST_TO_CCR(__PCLK__, __SPEED__, __DUTYCYCLE__)  (uint32_t)(((__DUTYCYCLE__) == LL_I2C_DUTYCYCLE_2)? \
                                                                            (((((__PCLK__) / ((__SPEED__) * 3U)) & I2C_CCR_CCR) == 0U)? 1U:((__PCLK__) / ((__SPEED__) * 3U))) : \
                                                                            (((((__PCLK__) / ((__SPEED__) * 25U)) & I2C_CCR_CCR) == 0U)? 1U:((__PCLK__) / ((__SPEED__) * 25U))))

#define __LL_I2C_10BIT_ADDRESS(__ADDRESS__)                             ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FF))))

#define __LL_I2C_10BIT_HEADER_WRITE(__ADDRESS__)                        ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF0))))

#define __LL_I2C_10BIT_HEADER_READ(__ADDRESS__)                         ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)(0x0300))) >> 7) | (uint16_t)(0xF1))))

__STATIC_INLINE void LL_I2C_Enable(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_PE);
}

__STATIC_INLINE void LL_I2C_Disable(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabled(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_PE) == (I2C_CR1_PE));
}

#if  defined(I2C_FLTR_ANOFF)&&defined(I2C_FLTR_DNF)

__STATIC_INLINE void LL_I2C_ConfigFilters(I2C_TypeDef *I2Cx, uint32_t AnalogFilter, uint32_t DigitalFilter)
{
  MODIFY_REG(I2Cx->FLTR, I2C_FLTR_ANOFF | I2C_FLTR_DNF, AnalogFilter | DigitalFilter);
}
#endif
#if defined(I2C_FLTR_DNF)

__STATIC_INLINE void LL_I2C_SetDigitalFilter(I2C_TypeDef *I2Cx, uint32_t DigitalFilter)
{
  MODIFY_REG(I2Cx->FLTR, I2C_FLTR_DNF, DigitalFilter);
}

__STATIC_INLINE uint32_t LL_I2C_GetDigitalFilter(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->FLTR, I2C_FLTR_DNF));
}
#endif
#if defined(I2C_FLTR_ANOFF)

__STATIC_INLINE void LL_I2C_EnableAnalogFilter(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->FLTR, I2C_FLTR_ANOFF);
}

__STATIC_INLINE void LL_I2C_DisableAnalogFilter(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->FLTR, I2C_FLTR_ANOFF);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledAnalogFilter(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->FLTR, I2C_FLTR_ANOFF) == (I2C_FLTR_ANOFF));
}
#endif

__STATIC_INLINE void LL_I2C_EnableDMAReq_TX(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_DMAEN);
}

__STATIC_INLINE void LL_I2C_DisableDMAReq_TX(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_DMAEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledDMAReq_TX(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_DMAEN) == (I2C_CR2_DMAEN));
}

__STATIC_INLINE void LL_I2C_EnableDMAReq_RX(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_DMAEN);
}

__STATIC_INLINE void LL_I2C_DisableDMAReq_RX(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_DMAEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledDMAReq_RX(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_DMAEN) == (I2C_CR2_DMAEN));
}

__STATIC_INLINE uint32_t LL_I2C_DMA_GetRegAddr(I2C_TypeDef *I2Cx)
{
  return (uint32_t) & (I2Cx->DR);
}

__STATIC_INLINE void LL_I2C_EnableClockStretching(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH);
}

__STATIC_INLINE void LL_I2C_DisableClockStretching(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledClockStretching(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH) != (I2C_CR1_NOSTRETCH));
}

__STATIC_INLINE void LL_I2C_EnableGeneralCall(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_ENGC);
}

__STATIC_INLINE void LL_I2C_DisableGeneralCall(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_ENGC);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledGeneralCall(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_ENGC) == (I2C_CR1_ENGC));
}

__STATIC_INLINE void LL_I2C_SetOwnAddress1(I2C_TypeDef *I2Cx, uint32_t OwnAddress1, uint32_t OwnAddrSize)
{
  MODIFY_REG(I2Cx->OAR1, I2C_OAR1_ADD0 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD8_9 | I2C_OAR1_ADDMODE, OwnAddress1 | OwnAddrSize);
}

__STATIC_INLINE void LL_I2C_SetOwnAddress2(I2C_TypeDef *I2Cx, uint32_t OwnAddress2)
{
  MODIFY_REG(I2Cx->OAR2, I2C_OAR2_ADD2, OwnAddress2);
}

__STATIC_INLINE void LL_I2C_EnableOwnAddress2(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL);
}

__STATIC_INLINE void LL_I2C_DisableOwnAddress2(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledOwnAddress2(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL) == (I2C_OAR2_ENDUAL));
}

__STATIC_INLINE void LL_I2C_SetPeriphClock(I2C_TypeDef *I2Cx, uint32_t PeriphClock)
{
  MODIFY_REG(I2Cx->CR2, I2C_CR2_FREQ, __LL_I2C_FREQ_HZ_TO_MHZ(PeriphClock));
}

__STATIC_INLINE uint32_t LL_I2C_GetPeriphClock(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(__LL_I2C_FREQ_MHZ_TO_HZ(READ_BIT(I2Cx->CR2, I2C_CR2_FREQ)));
}

__STATIC_INLINE void LL_I2C_SetDutyCycle(I2C_TypeDef *I2Cx, uint32_t DutyCycle)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_DUTY, DutyCycle);
}

__STATIC_INLINE uint32_t LL_I2C_GetDutyCycle(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_DUTY));
}

__STATIC_INLINE void LL_I2C_SetClockSpeedMode(I2C_TypeDef *I2Cx, uint32_t ClockSpeedMode)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_FS, ClockSpeedMode);
}

__STATIC_INLINE uint32_t LL_I2C_GetClockSpeedMode(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_FS));
}

__STATIC_INLINE void LL_I2C_SetRiseTime(I2C_TypeDef *I2Cx, uint32_t RiseTime)
{
  MODIFY_REG(I2Cx->TRISE, I2C_TRISE_TRISE, RiseTime);
}

__STATIC_INLINE uint32_t LL_I2C_GetRiseTime(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->TRISE, I2C_TRISE_TRISE));
}

__STATIC_INLINE void LL_I2C_SetClockPeriod(I2C_TypeDef *I2Cx, uint32_t ClockPeriod)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_CCR, ClockPeriod);
}

__STATIC_INLINE uint32_t LL_I2C_GetClockPeriod(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_CCR));
}

__STATIC_INLINE void LL_I2C_ConfigSpeed(I2C_TypeDef *I2Cx, uint32_t PeriphClock, uint32_t ClockSpeed,
                                        uint32_t DutyCycle)
{
  uint32_t freqrange = 0x0U;
  uint32_t clockconfig = 0x0U;

  freqrange = __LL_I2C_FREQ_HZ_TO_MHZ(PeriphClock);

  MODIFY_REG(I2Cx->CR2, I2C_CR2_FREQ, freqrange);

  MODIFY_REG(I2Cx->TRISE, I2C_TRISE_TRISE, __LL_I2C_RISE_TIME(freqrange, ClockSpeed));

  if (ClockSpeed > LL_I2C_MAX_SPEED_STANDARD)
  {

    clockconfig = LL_I2C_CLOCK_SPEED_FAST_MODE                                          | \
                  __LL_I2C_SPEED_FAST_TO_CCR(PeriphClock, ClockSpeed, DutyCycle)        | \
                  DutyCycle;
  }
  else
  {

    clockconfig = LL_I2C_CLOCK_SPEED_STANDARD_MODE                                      | \
                  __LL_I2C_SPEED_STANDARD_TO_CCR(PeriphClock, ClockSpeed);
  }

  MODIFY_REG(I2Cx->CCR, (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR), clockconfig);
}

__STATIC_INLINE void LL_I2C_SetMode(I2C_TypeDef *I2Cx, uint32_t PeripheralMode)
{
  MODIFY_REG(I2Cx->CR1, I2C_CR1_SMBUS | I2C_CR1_SMBTYPE | I2C_CR1_ENARP, PeripheralMode);
}

__STATIC_INLINE uint32_t LL_I2C_GetMode(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CR1, I2C_CR1_SMBUS | I2C_CR1_SMBTYPE | I2C_CR1_ENARP));
}

__STATIC_INLINE void LL_I2C_EnableSMBusAlert(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_ALERT);
}

__STATIC_INLINE void LL_I2C_DisableSMBusAlert(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_ALERT);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledSMBusAlert(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_ALERT) == (I2C_CR1_ALERT));
}

__STATIC_INLINE void LL_I2C_EnableSMBusPEC(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_ENPEC);
}

__STATIC_INLINE void LL_I2C_DisableSMBusPEC(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_ENPEC);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledSMBusPEC(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_ENPEC) == (I2C_CR1_ENPEC));
}

__STATIC_INLINE void LL_I2C_EnableIT_TX(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN);
}

__STATIC_INLINE void LL_I2C_DisableIT_TX(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledIT_TX(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN) == (I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN));
}

__STATIC_INLINE void LL_I2C_EnableIT_RX(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN);
}

__STATIC_INLINE void LL_I2C_DisableIT_RX(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledIT_RX(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN) == (I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN));
}

__STATIC_INLINE void LL_I2C_EnableIT_EVT(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN);
}

__STATIC_INLINE void LL_I2C_DisableIT_EVT(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledIT_EVT(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_ITEVTEN) == (I2C_CR2_ITEVTEN));
}

__STATIC_INLINE void LL_I2C_EnableIT_BUF(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_ITBUFEN);
}

__STATIC_INLINE void LL_I2C_DisableIT_BUF(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_ITBUFEN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledIT_BUF(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_ITBUFEN) == (I2C_CR2_ITBUFEN));
}

__STATIC_INLINE void LL_I2C_EnableIT_ERR(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_ITERREN);
}

__STATIC_INLINE void LL_I2C_DisableIT_ERR(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_ITERREN);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledIT_ERR(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_ITERREN) == (I2C_CR2_ITERREN));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_TXE(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_TXE) == (I2C_SR1_TXE));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_BTF(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_BTF) == (I2C_SR1_BTF));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_RXNE(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_RXNE) == (I2C_SR1_RXNE));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_SB(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_SB) == (I2C_SR1_SB));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_ADDR(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_ADDR) == (I2C_SR1_ADDR));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_ADD10(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_ADD10) == (I2C_SR1_ADD10));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_AF(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_AF) == (I2C_SR1_AF));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_STOP(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_STOPF) == (I2C_SR1_STOPF));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_BERR(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_BERR) == (I2C_SR1_BERR));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_ARLO(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_ARLO) == (I2C_SR1_ARLO));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_OVR(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_OVR) == (I2C_SR1_OVR));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveSMBusFlag_PECERR(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_PECERR) == (I2C_SR1_PECERR));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveSMBusFlag_TIMEOUT(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_TIMEOUT) == (I2C_SR1_TIMEOUT));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveSMBusFlag_ALERT(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR1, I2C_SR1_SMBALERT) == (I2C_SR1_SMBALERT));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_BUSY(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_BUSY) == (I2C_SR2_BUSY));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_DUAL(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_DUALF) == (I2C_SR2_DUALF));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveSMBusFlag_SMBHOST(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_SMBHOST) == (I2C_SR2_SMBHOST));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveSMBusFlag_SMBDEFAULT(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_SMBDEFAULT) == (I2C_SR2_SMBDEFAULT));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_GENCALL(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_GENCALL) == (I2C_SR2_GENCALL));
}

__STATIC_INLINE uint32_t LL_I2C_IsActiveFlag_MSL(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->SR2, I2C_SR2_MSL) == (I2C_SR2_MSL));
}

__STATIC_INLINE void LL_I2C_ClearFlag_ADDR(I2C_TypeDef *I2Cx)
{
  __IO uint32_t tmpreg;
  tmpreg = I2Cx->SR1;
  (void) tmpreg;
  tmpreg = I2Cx->SR2;
  (void) tmpreg;
}

__STATIC_INLINE void LL_I2C_ClearFlag_AF(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_AF);
}

__STATIC_INLINE void LL_I2C_ClearFlag_STOP(I2C_TypeDef *I2Cx)
{
  __IO uint32_t tmpreg;
  tmpreg = I2Cx->SR1;
  (void) tmpreg;
  SET_BIT(I2Cx->CR1, I2C_CR1_PE);
}

__STATIC_INLINE void LL_I2C_ClearFlag_BERR(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_BERR);
}

__STATIC_INLINE void LL_I2C_ClearFlag_ARLO(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_ARLO);
}

__STATIC_INLINE void LL_I2C_ClearFlag_OVR(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_OVR);
}

__STATIC_INLINE void LL_I2C_ClearSMBusFlag_PECERR(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_PECERR);
}

__STATIC_INLINE void LL_I2C_ClearSMBusFlag_TIMEOUT(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_TIMEOUT);
}

__STATIC_INLINE void LL_I2C_ClearSMBusFlag_ALERT(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->SR1, I2C_SR1_SMBALERT);
}

__STATIC_INLINE void LL_I2C_EnableReset(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_SWRST);
}

__STATIC_INLINE void LL_I2C_DisableReset(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_SWRST);
}

__STATIC_INLINE uint32_t LL_I2C_IsResetEnabled(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_SWRST) == (I2C_CR1_SWRST));
}

__STATIC_INLINE void LL_I2C_AcknowledgeNextData(I2C_TypeDef *I2Cx, uint32_t TypeAcknowledge)
{
  MODIFY_REG(I2Cx->CR1, I2C_CR1_ACK, TypeAcknowledge);
}

__STATIC_INLINE void LL_I2C_GenerateStartCondition(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_START);
}

__STATIC_INLINE void LL_I2C_GenerateStopCondition(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_STOP);
}

__STATIC_INLINE void LL_I2C_EnableBitPOS(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_POS);
}

__STATIC_INLINE void LL_I2C_DisableBitPOS(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_POS);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledBitPOS(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_POS) == (I2C_CR1_POS));
}

__STATIC_INLINE uint32_t LL_I2C_GetTransferDirection(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->SR2, I2C_SR2_TRA));
}

__STATIC_INLINE void LL_I2C_EnableLastDMA(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR2, I2C_CR2_LAST);
}

__STATIC_INLINE void LL_I2C_DisableLastDMA(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR2, I2C_CR2_LAST);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledLastDMA(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR2, I2C_CR2_LAST) == (I2C_CR2_LAST));
}

__STATIC_INLINE void LL_I2C_EnableSMBusPECCompare(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_PEC);
}

__STATIC_INLINE void LL_I2C_DisableSMBusPECCompare(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_PEC);
}

__STATIC_INLINE uint32_t LL_I2C_IsEnabledSMBusPECCompare(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_PEC) == (I2C_CR1_PEC));
}

__STATIC_INLINE uint32_t LL_I2C_GetSMBusPEC(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->SR2, I2C_SR2_PEC) >> I2C_SR2_PEC_Pos);
}

__STATIC_INLINE uint8_t LL_I2C_ReceiveData8(I2C_TypeDef *I2Cx)
{
  return (uint8_t)(READ_BIT(I2Cx->DR, I2C_DR_DR));
}

__STATIC_INLINE void LL_I2C_TransmitData8(I2C_TypeDef *I2Cx, uint8_t Data)
{
  MODIFY_REG(I2Cx->DR, I2C_DR_DR, Data);
}

#if defined(USE_FULL_LL_DRIVER)

uint32_t LL_I2C_Init(I2C_TypeDef *I2Cx, LL_I2C_InitTypeDef *I2C_InitStruct);
uint32_t LL_I2C_DeInit(I2C_TypeDef *I2Cx);
void LL_I2C_StructInit(LL_I2C_InitTypeDef *I2C_InitStruct);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
