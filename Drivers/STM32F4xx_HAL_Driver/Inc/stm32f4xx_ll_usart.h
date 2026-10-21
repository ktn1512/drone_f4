#ifndef __STM32F4xx_LL_USART_H
#define __STM32F4xx_LL_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (USART1) || defined (USART2) || defined (USART3) || defined (USART6) || defined (UART4) || defined (UART5) || defined (UART7) || defined (UART8) || defined (UART9) || defined (UART10)

#define USART_POSITION_GTPR_GT                  USART_GTPR_GT_Pos

#if defined(USE_FULL_LL_DRIVER)

#endif

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t BaudRate;

  uint32_t DataWidth;

  uint32_t StopBits;

  uint32_t Parity;

  uint32_t TransferDirection;

  uint32_t HardwareFlowControl;

  uint32_t OverSampling;

} LL_USART_InitTypeDef;

typedef struct
{
  uint32_t ClockOutput;

  uint32_t ClockPolarity;

  uint32_t ClockPhase;

  uint32_t LastBitClockPulse;

} LL_USART_ClockInitTypeDef;

#endif

#define LL_USART_SR_PE                          USART_SR_PE
#define LL_USART_SR_FE                          USART_SR_FE
#define LL_USART_SR_NE                          USART_SR_NE
#define LL_USART_SR_ORE                         USART_SR_ORE
#define LL_USART_SR_IDLE                        USART_SR_IDLE
#define LL_USART_SR_RXNE                        USART_SR_RXNE
#define LL_USART_SR_TC                          USART_SR_TC
#define LL_USART_SR_TXE                         USART_SR_TXE
#define LL_USART_SR_LBD                         USART_SR_LBD
#define LL_USART_SR_CTS                         USART_SR_CTS

#define LL_USART_CR1_IDLEIE                     USART_CR1_IDLEIE
#define LL_USART_CR1_RXNEIE                     USART_CR1_RXNEIE
#define LL_USART_CR1_TCIE                       USART_CR1_TCIE
#define LL_USART_CR1_TXEIE                      USART_CR1_TXEIE
#define LL_USART_CR1_PEIE                       USART_CR1_PEIE
#define LL_USART_CR2_LBDIE                      USART_CR2_LBDIE
#define LL_USART_CR3_EIE                        USART_CR3_EIE
#define LL_USART_CR3_CTSIE                      USART_CR3_CTSIE

#define LL_USART_DIRECTION_NONE                 0x00000000U
#define LL_USART_DIRECTION_RX                   USART_CR1_RE
#define LL_USART_DIRECTION_TX                   USART_CR1_TE
#define LL_USART_DIRECTION_TX_RX                (USART_CR1_TE |USART_CR1_RE)

#define LL_USART_PARITY_NONE                    0x00000000U
#define LL_USART_PARITY_EVEN                    USART_CR1_PCE
#define LL_USART_PARITY_ODD                     (USART_CR1_PCE | USART_CR1_PS)

#define LL_USART_WAKEUP_IDLELINE                0x00000000U
#define LL_USART_WAKEUP_ADDRESSMARK             USART_CR1_WAKE

#define LL_USART_DATAWIDTH_8B                   0x00000000U
#define LL_USART_DATAWIDTH_9B                   USART_CR1_M

#define LL_USART_OVERSAMPLING_16                0x00000000U
#define LL_USART_OVERSAMPLING_8                 USART_CR1_OVER8

#if defined(USE_FULL_LL_DRIVER)

#define LL_USART_CLOCK_DISABLE                  0x00000000U
#define LL_USART_CLOCK_ENABLE                   USART_CR2_CLKEN

#endif

#define LL_USART_LASTCLKPULSE_NO_OUTPUT         0x00000000U
#define LL_USART_LASTCLKPULSE_OUTPUT            USART_CR2_LBCL

#define LL_USART_PHASE_1EDGE                    0x00000000U
#define LL_USART_PHASE_2EDGE                    USART_CR2_CPHA

#define LL_USART_POLARITY_LOW                   0x00000000U
#define LL_USART_POLARITY_HIGH                  USART_CR2_CPOL

#define LL_USART_STOPBITS_0_5                   USART_CR2_STOP_0
#define LL_USART_STOPBITS_1                     0x00000000U
#define LL_USART_STOPBITS_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1)
#define LL_USART_STOPBITS_2                     USART_CR2_STOP_1

#define LL_USART_HWCONTROL_NONE                 0x00000000U
#define LL_USART_HWCONTROL_RTS                  USART_CR3_RTSE
#define LL_USART_HWCONTROL_CTS                  USART_CR3_CTSE
#define LL_USART_HWCONTROL_RTS_CTS              (USART_CR3_RTSE | USART_CR3_CTSE)

#define LL_USART_IRDA_POWER_NORMAL              0x00000000U
#define LL_USART_IRDA_POWER_LOW                 USART_CR3_IRLP

#define LL_USART_LINBREAK_DETECT_10B            0x00000000U
#define LL_USART_LINBREAK_DETECT_11B            USART_CR2_LBDL

#define LL_USART_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_USART_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

#define __LL_USART_DIV_SAMPLING8_100(__PERIPHCLK__, __BAUDRATE__)      ((uint32_t)((((uint64_t)(__PERIPHCLK__))*25)/(2*((uint64_t)(__BAUDRATE__)))))
#define __LL_USART_DIVMANT_SAMPLING8(__PERIPHCLK__, __BAUDRATE__)      (__LL_USART_DIV_SAMPLING8_100((__PERIPHCLK__), (__BAUDRATE__))/100)
#define __LL_USART_DIVFRAQ_SAMPLING8(__PERIPHCLK__, __BAUDRATE__)      ((((__LL_USART_DIV_SAMPLING8_100((__PERIPHCLK__), (__BAUDRATE__)) - (__LL_USART_DIVMANT_SAMPLING8((__PERIPHCLK__), (__BAUDRATE__)) * 100)) * 8)\
                                                                         + 50) / 100)

#define __LL_USART_DIV_SAMPLING8(__PERIPHCLK__, __BAUDRATE__)             (((__LL_USART_DIVMANT_SAMPLING8((__PERIPHCLK__), (__BAUDRATE__)) << 4) + \
                                                                            ((__LL_USART_DIVFRAQ_SAMPLING8((__PERIPHCLK__), (__BAUDRATE__)) & 0xF8) << 1)) + \
                                                                           (__LL_USART_DIVFRAQ_SAMPLING8((__PERIPHCLK__), (__BAUDRATE__)) & 0x07))

#define __LL_USART_DIV_SAMPLING16_100(__PERIPHCLK__, __BAUDRATE__)     ((uint32_t)((((uint64_t)(__PERIPHCLK__))*25)/(4*((uint64_t)(__BAUDRATE__)))))
#define __LL_USART_DIVMANT_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)     (__LL_USART_DIV_SAMPLING16_100((__PERIPHCLK__), (__BAUDRATE__))/100)
#define __LL_USART_DIVFRAQ_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)     ((((__LL_USART_DIV_SAMPLING16_100((__PERIPHCLK__), (__BAUDRATE__)) - (__LL_USART_DIVMANT_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) * 100)) * 16)\
                                                                         + 50) / 100)

#define __LL_USART_DIV_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)            (((__LL_USART_DIVMANT_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) << 4) + \
                                                                            (__LL_USART_DIVFRAQ_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) & 0xF0)) + \
                                                                           (__LL_USART_DIVFRAQ_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) & 0x0F))

__STATIC_INLINE void LL_USART_Enable(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR1, USART_CR1_UE);
}

__STATIC_INLINE void LL_USART_Disable(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR1, USART_CR1_UE);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabled(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_UE) == (USART_CR1_UE));
}

__STATIC_INLINE void LL_USART_EnableDirectionRx(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_RE);
}

__STATIC_INLINE void LL_USART_DisableDirectionRx(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_RE);
}

__STATIC_INLINE void LL_USART_EnableDirectionTx(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_TE);
}

__STATIC_INLINE void LL_USART_DisableDirectionTx(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_TE);
}

__STATIC_INLINE void LL_USART_SetTransferDirection(USART_TypeDef *USARTx, uint32_t TransferDirection)
{
  ATOMIC_MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);
}

__STATIC_INLINE uint32_t LL_USART_GetTransferDirection(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR1, USART_CR1_RE | USART_CR1_TE));
}

__STATIC_INLINE void LL_USART_SetParity(USART_TypeDef *USARTx, uint32_t Parity)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE, Parity);
}

__STATIC_INLINE uint32_t LL_USART_GetParity(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE));
}

__STATIC_INLINE void LL_USART_SetWakeUpMethod(USART_TypeDef *USARTx, uint32_t Method)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_WAKE, Method);
}

__STATIC_INLINE uint32_t LL_USART_GetWakeUpMethod(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR1, USART_CR1_WAKE));
}

__STATIC_INLINE void LL_USART_SetDataWidth(USART_TypeDef *USARTx, uint32_t DataWidth)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_M, DataWidth);
}

__STATIC_INLINE uint32_t LL_USART_GetDataWidth(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR1, USART_CR1_M));
}

__STATIC_INLINE void LL_USART_SetOverSampling(USART_TypeDef *USARTx, uint32_t OverSampling)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_OVER8, OverSampling);
}

__STATIC_INLINE uint32_t LL_USART_GetOverSampling(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR1, USART_CR1_OVER8));
}

__STATIC_INLINE void LL_USART_SetLastClkPulseOutput(USART_TypeDef *USARTx, uint32_t LastBitClockPulse)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_LBCL, LastBitClockPulse);
}

__STATIC_INLINE uint32_t LL_USART_GetLastClkPulseOutput(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_LBCL));
}

__STATIC_INLINE void LL_USART_SetClockPhase(USART_TypeDef *USARTx, uint32_t ClockPhase)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_CPHA, ClockPhase);
}

__STATIC_INLINE uint32_t LL_USART_GetClockPhase(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_CPHA));
}

__STATIC_INLINE void LL_USART_SetClockPolarity(USART_TypeDef *USARTx, uint32_t ClockPolarity)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_CPOL, ClockPolarity);
}

__STATIC_INLINE uint32_t LL_USART_GetClockPolarity(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_CPOL));
}

__STATIC_INLINE void LL_USART_ConfigClock(USART_TypeDef *USARTx, uint32_t Phase, uint32_t Polarity, uint32_t LBCPOutput)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_LBCL, Phase | Polarity | LBCPOutput);
}

__STATIC_INLINE void LL_USART_EnableSCLKOutput(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR2, USART_CR2_CLKEN);
}

__STATIC_INLINE void LL_USART_DisableSCLKOutput(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR2, USART_CR2_CLKEN);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledSCLKOutput(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR2, USART_CR2_CLKEN) == (USART_CR2_CLKEN));
}

__STATIC_INLINE void LL_USART_SetStopBitsLength(USART_TypeDef *USARTx, uint32_t StopBits)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

__STATIC_INLINE uint32_t LL_USART_GetStopBitsLength(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_STOP));
}

__STATIC_INLINE void LL_USART_ConfigCharacter(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity,
                                              uint32_t StopBits)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);
  MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}

__STATIC_INLINE void LL_USART_SetNodeAddress(USART_TypeDef *USARTx, uint32_t NodeAddress)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_ADD, (NodeAddress & USART_CR2_ADD));
}

__STATIC_INLINE uint32_t LL_USART_GetNodeAddress(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_ADD));
}

__STATIC_INLINE void LL_USART_EnableRTSHWFlowCtrl(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_RTSE);
}

__STATIC_INLINE void LL_USART_DisableRTSHWFlowCtrl(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_RTSE);
}

__STATIC_INLINE void LL_USART_EnableCTSHWFlowCtrl(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_CTSE);
}

__STATIC_INLINE void LL_USART_DisableCTSHWFlowCtrl(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_CTSE);
}

__STATIC_INLINE void LL_USART_SetHWFlowCtrl(USART_TypeDef *USARTx, uint32_t HardwareFlowControl)
{
  MODIFY_REG(USARTx->CR3, USART_CR3_RTSE | USART_CR3_CTSE, HardwareFlowControl);
}

__STATIC_INLINE uint32_t LL_USART_GetHWFlowCtrl(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR3, USART_CR3_RTSE | USART_CR3_CTSE));
}

__STATIC_INLINE void LL_USART_EnableOneBitSamp(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_ONEBIT);
}

__STATIC_INLINE void LL_USART_DisableOneBitSamp(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_ONEBIT);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledOneBitSamp(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_ONEBIT) == (USART_CR3_ONEBIT));
}

__STATIC_INLINE void LL_USART_SetBaudRate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t OverSampling,
                                          uint32_t BaudRate)
{
  if (OverSampling == LL_USART_OVERSAMPLING_8)
  {
    USARTx->BRR = (uint16_t)(__LL_USART_DIV_SAMPLING8(PeriphClk, BaudRate));
  }
  else
  {
    USARTx->BRR = (uint16_t)(__LL_USART_DIV_SAMPLING16(PeriphClk, BaudRate));
  }
}

__STATIC_INLINE uint32_t LL_USART_GetBaudRate(const USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t OverSampling)
{
  uint32_t usartdiv = 0x0U;
  uint32_t brrresult = 0x0U;

  usartdiv = USARTx->BRR;

  if (OverSampling == LL_USART_OVERSAMPLING_8)
  {
    if ((usartdiv & 0xFFF7U) != 0U)
    {
      usartdiv = (uint16_t)((usartdiv & 0xFFF0U) | ((usartdiv & 0x0007U) << 1U)) ;
      brrresult = (PeriphClk * 2U) / usartdiv;
    }
  }
  else
  {
    if ((usartdiv & 0xFFFFU) != 0U)
    {
      brrresult = PeriphClk / usartdiv;
    }
  }
  return (brrresult);
}

__STATIC_INLINE void LL_USART_EnableIrda(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_IREN);
}

__STATIC_INLINE void LL_USART_DisableIrda(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_IREN);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIrda(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_IREN) == (USART_CR3_IREN));
}

__STATIC_INLINE void LL_USART_SetIrdaPowerMode(USART_TypeDef *USARTx, uint32_t PowerMode)
{
  MODIFY_REG(USARTx->CR3, USART_CR3_IRLP, PowerMode);
}

__STATIC_INLINE uint32_t LL_USART_GetIrdaPowerMode(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR3, USART_CR3_IRLP));
}

__STATIC_INLINE void LL_USART_SetIrdaPrescaler(USART_TypeDef *USARTx, uint32_t PrescalerValue)
{
  MODIFY_REG(USARTx->GTPR, USART_GTPR_PSC, PrescalerValue);
}

__STATIC_INLINE uint32_t LL_USART_GetIrdaPrescaler(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->GTPR, USART_GTPR_PSC));
}

__STATIC_INLINE void LL_USART_EnableSmartcardNACK(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_NACK);
}

__STATIC_INLINE void LL_USART_DisableSmartcardNACK(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_NACK);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledSmartcardNACK(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_NACK) == (USART_CR3_NACK));
}

__STATIC_INLINE void LL_USART_EnableSmartcard(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_SCEN);
}

__STATIC_INLINE void LL_USART_DisableSmartcard(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_SCEN);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledSmartcard(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_SCEN) == (USART_CR3_SCEN));
}

__STATIC_INLINE void LL_USART_SetSmartcardPrescaler(USART_TypeDef *USARTx, uint32_t PrescalerValue)
{
  MODIFY_REG(USARTx->GTPR, USART_GTPR_PSC, PrescalerValue);
}

__STATIC_INLINE uint32_t LL_USART_GetSmartcardPrescaler(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->GTPR, USART_GTPR_PSC));
}

__STATIC_INLINE void LL_USART_SetSmartcardGuardTime(USART_TypeDef *USARTx, uint32_t GuardTime)
{
  MODIFY_REG(USARTx->GTPR, USART_GTPR_GT, GuardTime << USART_POSITION_GTPR_GT);
}

__STATIC_INLINE uint32_t LL_USART_GetSmartcardGuardTime(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->GTPR, USART_GTPR_GT) >> USART_POSITION_GTPR_GT);
}

__STATIC_INLINE void LL_USART_EnableHalfDuplex(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR3, USART_CR3_HDSEL);
}

__STATIC_INLINE void LL_USART_DisableHalfDuplex(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR3, USART_CR3_HDSEL);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledHalfDuplex(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_HDSEL) == (USART_CR3_HDSEL));
}

__STATIC_INLINE void LL_USART_SetLINBrkDetectionLen(USART_TypeDef *USARTx, uint32_t LINBDLength)
{
  MODIFY_REG(USARTx->CR2, USART_CR2_LBDL, LINBDLength);
}

__STATIC_INLINE uint32_t LL_USART_GetLINBrkDetectionLen(const USART_TypeDef *USARTx)
{
  return (uint32_t)(READ_BIT(USARTx->CR2, USART_CR2_LBDL));
}

__STATIC_INLINE void LL_USART_EnableLIN(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR2, USART_CR2_LINEN);
}

__STATIC_INLINE void LL_USART_DisableLIN(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR2, USART_CR2_LINEN);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledLIN(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR2, USART_CR2_LINEN) == (USART_CR2_LINEN));
}

__STATIC_INLINE void LL_USART_ConfigAsyncMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));
}

__STATIC_INLINE void LL_USART_ConfigSyncMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL));

  SET_BIT(USARTx->CR2, USART_CR2_CLKEN);
}

__STATIC_INLINE void LL_USART_ConfigLINMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_CLKEN | USART_CR2_STOP));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_IREN | USART_CR3_SCEN | USART_CR3_HDSEL));

  SET_BIT(USARTx->CR2, USART_CR2_LINEN);
}

__STATIC_INLINE void LL_USART_ConfigHalfDuplexMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_SCEN | USART_CR3_IREN));

  SET_BIT(USARTx->CR3, USART_CR3_HDSEL);
}

__STATIC_INLINE void LL_USART_ConfigSmartcardMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_IREN | USART_CR3_HDSEL));

  SET_BIT(USARTx->CR2, (USART_CR2_STOP_0 | USART_CR2_STOP_1 | USART_CR2_CLKEN));

  SET_BIT(USARTx->CR3, USART_CR3_SCEN);
}

__STATIC_INLINE void LL_USART_ConfigIrdaMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN | USART_CR2_STOP));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL));

  SET_BIT(USARTx->CR3, USART_CR3_IREN);
}

__STATIC_INLINE void LL_USART_ConfigMultiProcessMode(USART_TypeDef *USARTx)
{

  CLEAR_BIT(USARTx->CR2, (USART_CR2_LINEN | USART_CR2_CLKEN));
  CLEAR_BIT(USARTx->CR3, (USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_PE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_PE) == (USART_SR_PE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_FE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_FE) == (USART_SR_FE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_NE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_NE) == (USART_SR_NE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_ORE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_ORE) == (USART_SR_ORE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_IDLE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_IDLE) == (USART_SR_IDLE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_RXNE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_RXNE) == (USART_SR_RXNE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_TC(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_TC) == (USART_SR_TC));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_TXE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_TXE) == (USART_SR_TXE));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_LBD(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_LBD) == (USART_SR_LBD));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_nCTS(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->SR, USART_SR_CTS) == (USART_SR_CTS));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_SBK(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_SBK) == (USART_CR1_SBK));
}

__STATIC_INLINE uint32_t LL_USART_IsActiveFlag_RWU(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_RWU) == (USART_CR1_RWU));
}

__STATIC_INLINE void LL_USART_ClearFlag_PE(USART_TypeDef *USARTx)
{
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_USART_ClearFlag_FE(USART_TypeDef *USARTx)
{
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_USART_ClearFlag_NE(USART_TypeDef *USARTx)
{
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_USART_ClearFlag_ORE(USART_TypeDef *USARTx)
{
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_USART_ClearFlag_IDLE(USART_TypeDef *USARTx)
{
  __IO uint32_t tmpreg;
  tmpreg = USARTx->SR;
  (void) tmpreg;
  tmpreg = USARTx->DR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_USART_ClearFlag_TC(USART_TypeDef *USARTx)
{
  WRITE_REG(USARTx->SR, ~(USART_SR_TC));
}

__STATIC_INLINE void LL_USART_ClearFlag_RXNE(USART_TypeDef *USARTx)
{
  WRITE_REG(USARTx->SR, ~(USART_SR_RXNE));
}

__STATIC_INLINE void LL_USART_ClearFlag_LBD(USART_TypeDef *USARTx)
{
  WRITE_REG(USARTx->SR, ~(USART_SR_LBD));
}

__STATIC_INLINE void LL_USART_ClearFlag_nCTS(USART_TypeDef *USARTx)
{
  WRITE_REG(USARTx->SR, ~(USART_SR_CTS));
}

__STATIC_INLINE void LL_USART_EnableIT_IDLE(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_IDLEIE);
}

__STATIC_INLINE void LL_USART_EnableIT_RXNE(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_RXNEIE);
}

__STATIC_INLINE void LL_USART_EnableIT_TC(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_TCIE);
}

__STATIC_INLINE void LL_USART_EnableIT_TXE(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_TXEIE);
}

__STATIC_INLINE void LL_USART_EnableIT_PE(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR1, USART_CR1_PEIE);
}

__STATIC_INLINE void LL_USART_EnableIT_LBD(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR2, USART_CR2_LBDIE);
}

__STATIC_INLINE void LL_USART_EnableIT_ERROR(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR3, USART_CR3_EIE);
}

__STATIC_INLINE void LL_USART_EnableIT_CTS(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR3, USART_CR3_CTSIE);
}

__STATIC_INLINE void LL_USART_DisableIT_IDLE(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_IDLEIE);
}

__STATIC_INLINE void LL_USART_DisableIT_RXNE(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_RXNEIE);
}

__STATIC_INLINE void LL_USART_DisableIT_TC(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_TCIE);
}

__STATIC_INLINE void LL_USART_DisableIT_TXE(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_TXEIE);
}

__STATIC_INLINE void LL_USART_DisableIT_PE(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR1, USART_CR1_PEIE);
}

__STATIC_INLINE void LL_USART_DisableIT_LBD(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR2, USART_CR2_LBDIE);
}

__STATIC_INLINE void LL_USART_DisableIT_ERROR(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR3, USART_CR3_EIE);
}

__STATIC_INLINE void LL_USART_DisableIT_CTS(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR3, USART_CR3_CTSIE);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_IDLE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_IDLEIE) == (USART_CR1_IDLEIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_RXNE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_RXNEIE) == (USART_CR1_RXNEIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_TC(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_TCIE) == (USART_CR1_TCIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_TXE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_TXEIE) == (USART_CR1_TXEIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_PE(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR1, USART_CR1_PEIE) == (USART_CR1_PEIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_LBD(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR2, USART_CR2_LBDIE) == (USART_CR2_LBDIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_ERROR(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_EIE) == (USART_CR3_EIE));
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledIT_CTS(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_CTSIE) == (USART_CR3_CTSIE));
}

__STATIC_INLINE void LL_USART_EnableDMAReq_RX(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR3, USART_CR3_DMAR);
}

__STATIC_INLINE void LL_USART_DisableDMAReq_RX(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR3, USART_CR3_DMAR);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledDMAReq_RX(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_DMAR) == (USART_CR3_DMAR));
}

__STATIC_INLINE void LL_USART_EnableDMAReq_TX(USART_TypeDef *USARTx)
{
  ATOMIC_SET_BIT(USARTx->CR3, USART_CR3_DMAT);
}

__STATIC_INLINE void LL_USART_DisableDMAReq_TX(USART_TypeDef *USARTx)
{
  ATOMIC_CLEAR_BIT(USARTx->CR3, USART_CR3_DMAT);
}

__STATIC_INLINE uint32_t LL_USART_IsEnabledDMAReq_TX(const USART_TypeDef *USARTx)
{
  return (READ_BIT(USARTx->CR3, USART_CR3_DMAT) == (USART_CR3_DMAT));
}

__STATIC_INLINE uint32_t LL_USART_DMA_GetRegAddr(const USART_TypeDef *USARTx)
{

  return ((uint32_t) &(USARTx->DR));
}

__STATIC_INLINE uint8_t LL_USART_ReceiveData8(const USART_TypeDef *USARTx)
{
  return (uint8_t)(READ_BIT(USARTx->DR, USART_DR_DR));
}

__STATIC_INLINE uint16_t LL_USART_ReceiveData9(const USART_TypeDef *USARTx)
{
  return (uint16_t)(READ_BIT(USARTx->DR, USART_DR_DR));
}

__STATIC_INLINE void LL_USART_TransmitData8(USART_TypeDef *USARTx, uint8_t Value)
{
  USARTx->DR = Value;
}

__STATIC_INLINE void LL_USART_TransmitData9(USART_TypeDef *USARTx, uint16_t Value)
{
  USARTx->DR = Value & 0x1FFU;
}

__STATIC_INLINE void LL_USART_RequestBreakSending(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR1, USART_CR1_SBK);
}

__STATIC_INLINE void LL_USART_RequestEnterMuteMode(USART_TypeDef *USARTx)
{
  SET_BIT(USARTx->CR1, USART_CR1_RWU);
}

__STATIC_INLINE void LL_USART_RequestExitMuteMode(USART_TypeDef *USARTx)
{
  CLEAR_BIT(USARTx->CR1, USART_CR1_RWU);
}

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_USART_DeInit(const USART_TypeDef *USARTx);
ErrorStatus LL_USART_Init(USART_TypeDef *USARTx, const LL_USART_InitTypeDef *USART_InitStruct);
void        LL_USART_StructInit(LL_USART_InitTypeDef *USART_InitStruct);
ErrorStatus LL_USART_ClockInit(USART_TypeDef *USARTx, const LL_USART_ClockInitTypeDef *USART_ClockInitStruct);
void        LL_USART_ClockStructInit(LL_USART_ClockInitTypeDef *USART_ClockInitStruct);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
