#ifndef STM32F4xx_LL_SPI_H
#define STM32F4xx_LL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (SPI1) || defined (SPI2) || defined (SPI3) || defined (SPI4) || defined (SPI5) || defined(SPI6)

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t TransferDirection;

  uint32_t Mode;

  uint32_t DataWidth;

  uint32_t ClockPolarity;

  uint32_t ClockPhase;

  uint32_t NSS;

  uint32_t BaudRate;

  uint32_t BitOrder;

  uint32_t CRCCalculation;

  uint32_t CRCPoly;

} LL_SPI_InitTypeDef;

#endif

#define LL_SPI_SR_RXNE                     SPI_SR_RXNE
#define LL_SPI_SR_TXE                      SPI_SR_TXE
#define LL_SPI_SR_BSY                      SPI_SR_BSY
#define LL_SPI_SR_CRCERR                   SPI_SR_CRCERR
#define LL_SPI_SR_MODF                     SPI_SR_MODF
#define LL_SPI_SR_OVR                      SPI_SR_OVR
#define LL_SPI_SR_FRE                      SPI_SR_FRE

#define LL_SPI_CR2_RXNEIE                  SPI_CR2_RXNEIE
#define LL_SPI_CR2_TXEIE                   SPI_CR2_TXEIE
#define LL_SPI_CR2_ERRIE                   SPI_CR2_ERRIE

#define LL_SPI_MODE_MASTER                 (SPI_CR1_MSTR | SPI_CR1_SSI)
#define LL_SPI_MODE_SLAVE                  0x00000000U

#define LL_SPI_PROTOCOL_MOTOROLA           0x00000000U
#define LL_SPI_PROTOCOL_TI                 (SPI_CR2_FRF)

#define LL_SPI_PHASE_1EDGE                 0x00000000U
#define LL_SPI_PHASE_2EDGE                 (SPI_CR1_CPHA)

#define LL_SPI_POLARITY_LOW                0x00000000U
#define LL_SPI_POLARITY_HIGH               (SPI_CR1_CPOL)

#define LL_SPI_BAUDRATEPRESCALER_DIV2      0x00000000U
#define LL_SPI_BAUDRATEPRESCALER_DIV4      (SPI_CR1_BR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV8      (SPI_CR1_BR_1)
#define LL_SPI_BAUDRATEPRESCALER_DIV16     (SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV32     (SPI_CR1_BR_2)
#define LL_SPI_BAUDRATEPRESCALER_DIV64     (SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define LL_SPI_BAUDRATEPRESCALER_DIV128    (SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define LL_SPI_BAUDRATEPRESCALER_DIV256    (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)

#define LL_SPI_LSB_FIRST                   (SPI_CR1_LSBFIRST)
#define LL_SPI_MSB_FIRST                   0x00000000U

#define LL_SPI_FULL_DUPLEX                 0x00000000U
#define LL_SPI_SIMPLEX_RX                  (SPI_CR1_RXONLY)
#define LL_SPI_HALF_DUPLEX_RX              (SPI_CR1_BIDIMODE)
#define LL_SPI_HALF_DUPLEX_TX              (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE)

#define LL_SPI_NSS_SOFT                    (SPI_CR1_SSM)
#define LL_SPI_NSS_HARD_INPUT              0x00000000U
#define LL_SPI_NSS_HARD_OUTPUT             (((uint32_t)SPI_CR2_SSOE << 16U))

#define LL_SPI_DATAWIDTH_8BIT              0x00000000U
#define LL_SPI_DATAWIDTH_16BIT             (SPI_CR1_DFF)

#if defined(USE_FULL_LL_DRIVER)

#define LL_SPI_CRCCALCULATION_DISABLE      0x00000000U
#define LL_SPI_CRCCALCULATION_ENABLE       (SPI_CR1_CRCEN)

#endif

#define LL_SPI_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_SPI_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

__STATIC_INLINE void LL_SPI_Enable(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}

__STATIC_INLINE void LL_SPI_Disable(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabled(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_SPE) == (SPI_CR1_SPE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_SPI_SetMode(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, Mode);
}

__STATIC_INLINE uint32_t LL_SPI_GetMode(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI));
}

__STATIC_INLINE void LL_SPI_SetStandard(SPI_TypeDef *SPIx, uint32_t Standard)
{
  MODIFY_REG(SPIx->CR2, SPI_CR2_FRF, Standard);
}

__STATIC_INLINE uint32_t LL_SPI_GetStandard(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR2, SPI_CR2_FRF));
}

__STATIC_INLINE void LL_SPI_SetClockPhase(SPI_TypeDef *SPIx, uint32_t ClockPhase)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA, ClockPhase);
}

__STATIC_INLINE uint32_t LL_SPI_GetClockPhase(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA));
}

__STATIC_INLINE void LL_SPI_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL, ClockPolarity);
}

__STATIC_INLINE uint32_t LL_SPI_GetClockPolarity(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL));
}

__STATIC_INLINE void LL_SPI_SetBaudRatePrescaler(SPI_TypeDef *SPIx, uint32_t BaudRate)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_BR, BaudRate);
}

__STATIC_INLINE uint32_t LL_SPI_GetBaudRatePrescaler(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BR));
}

__STATIC_INLINE void LL_SPI_SetTransferBitOrder(SPI_TypeDef *SPIx, uint32_t BitOrder)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_LSBFIRST, BitOrder);
}

__STATIC_INLINE uint32_t LL_SPI_GetTransferBitOrder(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_LSBFIRST));
}

__STATIC_INLINE void LL_SPI_SetTransferDirection(SPI_TypeDef *SPIx, uint32_t TransferDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE, TransferDirection);
}

__STATIC_INLINE uint32_t LL_SPI_GetTransferDirection(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE));
}

__STATIC_INLINE void LL_SPI_SetDataWidth(SPI_TypeDef *SPIx, uint32_t DataWidth)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_DFF, DataWidth);
}

__STATIC_INLINE uint32_t LL_SPI_GetDataWidth(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_DFF));
}

__STATIC_INLINE void LL_SPI_EnableCRC(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CRCEN);
}

__STATIC_INLINE void LL_SPI_DisableCRC(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_CRCEN);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledCRC(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_CRCEN) == (SPI_CR1_CRCEN)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_SPI_SetCRCNext(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_CRCNEXT);
}

__STATIC_INLINE void LL_SPI_SetCRCPolynomial(SPI_TypeDef *SPIx, uint32_t CRCPoly)
{
  WRITE_REG(SPIx->CRCPR, (uint16_t)CRCPoly);
}

__STATIC_INLINE uint32_t LL_SPI_GetCRCPolynomial(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CRCPR));
}

__STATIC_INLINE uint32_t LL_SPI_GetRxCRC(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->RXCRCR));
}

__STATIC_INLINE uint32_t LL_SPI_GetTxCRC(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->TXCRCR));
}

__STATIC_INLINE void LL_SPI_SetNSSMode(SPI_TypeDef *SPIx, uint32_t NSS)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_SSM,  NSS);
  MODIFY_REG(SPIx->CR2, SPI_CR2_SSOE, ((uint32_t)(NSS >> 16U)));
}

__STATIC_INLINE uint32_t LL_SPI_GetNSSMode(const SPI_TypeDef *SPIx)
{
  uint32_t Ssm  = (READ_BIT(SPIx->CR1, SPI_CR1_SSM));
  uint32_t Ssoe = (READ_BIT(SPIx->CR2,  SPI_CR2_SSOE) << 16U);
  return (Ssm | Ssoe);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_RXNE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_RXNE) == (SPI_SR_RXNE)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_TXE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_TXE) == (SPI_SR_TXE)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_CRCERR(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_CRCERR) == (SPI_SR_CRCERR)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_MODF(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_MODF) == (SPI_SR_MODF)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_OVR(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_OVR) == (SPI_SR_OVR)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_BSY(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_BSY) == (SPI_SR_BSY)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsActiveFlag_FRE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_FRE) == (SPI_SR_FRE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_SPI_ClearFlag_CRCERR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->SR, SPI_SR_CRCERR);
}

__STATIC_INLINE void LL_SPI_ClearFlag_MODF(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg_sr;
  tmpreg_sr = SPIx->SR;
  (void) tmpreg_sr;
  CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
}

__STATIC_INLINE void LL_SPI_ClearFlag_OVR(const SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->DR;
  (void) tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_SPI_ClearFlag_FRE(const SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

__STATIC_INLINE void LL_SPI_EnableIT_ERR(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_ERRIE);
}

__STATIC_INLINE void LL_SPI_EnableIT_RXNE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_RXNEIE);
}

__STATIC_INLINE void LL_SPI_EnableIT_TXE(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_TXEIE);
}

__STATIC_INLINE void LL_SPI_DisableIT_ERR(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_ERRIE);
}

__STATIC_INLINE void LL_SPI_DisableIT_RXNE(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_RXNEIE);
}

__STATIC_INLINE void LL_SPI_DisableIT_TXE(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_TXEIE);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_ERR(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR2, SPI_CR2_ERRIE) == (SPI_CR2_ERRIE)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_RXNE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR2, SPI_CR2_RXNEIE) == (SPI_CR2_RXNEIE)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledIT_TXE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR2, SPI_CR2_TXEIE) == (SPI_CR2_TXEIE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_SPI_EnableDMAReq_RX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_RXDMAEN);
}

__STATIC_INLINE void LL_SPI_DisableDMAReq_RX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_RXDMAEN);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_RX(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR2, SPI_CR2_RXDMAEN) == (SPI_CR2_RXDMAEN)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_SPI_EnableDMAReq_TX(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR2, SPI_CR2_TXDMAEN);
}

__STATIC_INLINE void LL_SPI_DisableDMAReq_TX(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR2, SPI_CR2_TXDMAEN);
}

__STATIC_INLINE uint32_t LL_SPI_IsEnabledDMAReq_TX(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR2, SPI_CR2_TXDMAEN) == (SPI_CR2_TXDMAEN)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_SPI_DMA_GetRegAddr(const SPI_TypeDef *SPIx)
{
  return (uint32_t) &(SPIx->DR);
}

__STATIC_INLINE uint8_t LL_SPI_ReceiveData8(SPI_TypeDef *SPIx)
{
  return (*((__IO uint8_t *)&SPIx->DR));
}

__STATIC_INLINE uint16_t LL_SPI_ReceiveData16(SPI_TypeDef *SPIx)
{
  return (uint16_t)(READ_REG(SPIx->DR));
}

__STATIC_INLINE void LL_SPI_TransmitData8(SPI_TypeDef *SPIx, uint8_t TxData)
{
#if defined (__GNUC__)
  __IO uint8_t *spidr = ((__IO uint8_t *)&SPIx->DR);
  *spidr = TxData;
#else
  *((__IO uint8_t *)&SPIx->DR) = TxData;
#endif
}

__STATIC_INLINE void LL_SPI_TransmitData16(SPI_TypeDef *SPIx, uint16_t TxData)
{
#if defined (__GNUC__)
  __IO uint16_t *spidr = ((__IO uint16_t *)&SPIx->DR);
  *spidr = TxData;
#else
  SPIx->DR = TxData;
#endif
}

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_SPI_DeInit(const SPI_TypeDef *SPIx);
ErrorStatus LL_SPI_Init(SPI_TypeDef *SPIx, LL_SPI_InitTypeDef *SPI_InitStruct);
void        LL_SPI_StructInit(LL_SPI_InitTypeDef *SPI_InitStruct);

#endif

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t Mode;

  uint32_t Standard;

  uint32_t DataFormat;

  uint32_t MCLKOutput;

  uint32_t AudioFreq;

  uint32_t ClockPolarity;

} LL_I2S_InitTypeDef;

#endif

#define LL_I2S_SR_RXNE                     LL_SPI_SR_RXNE
#define LL_I2S_SR_TXE                      LL_SPI_SR_TXE
#define LL_I2S_SR_BSY                      LL_SPI_SR_BSY
#define LL_I2S_SR_UDR                      SPI_SR_UDR
#define LL_I2S_SR_OVR                      LL_SPI_SR_OVR
#define LL_I2S_SR_FRE                      LL_SPI_SR_FRE

#define LL_I2S_CR2_RXNEIE                  LL_SPI_CR2_RXNEIE
#define LL_I2S_CR2_TXEIE                   LL_SPI_CR2_TXEIE
#define LL_I2S_CR2_ERRIE                   LL_SPI_CR2_ERRIE

#define LL_I2S_DATAFORMAT_16B              0x00000000U
#define LL_I2S_DATAFORMAT_16B_EXTENDED     (SPI_I2SCFGR_CHLEN)
#define LL_I2S_DATAFORMAT_24B              (SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN_0)
#define LL_I2S_DATAFORMAT_32B              (SPI_I2SCFGR_CHLEN | SPI_I2SCFGR_DATLEN_1)

#define LL_I2S_POLARITY_LOW                0x00000000U
#define LL_I2S_POLARITY_HIGH               (SPI_I2SCFGR_CKPOL)

#define LL_I2S_STANDARD_PHILIPS            0x00000000U
#define LL_I2S_STANDARD_MSB                (SPI_I2SCFGR_I2SSTD_0)
#define LL_I2S_STANDARD_LSB                (SPI_I2SCFGR_I2SSTD_1)
#define LL_I2S_STANDARD_PCM_SHORT          (SPI_I2SCFGR_I2SSTD_0 | SPI_I2SCFGR_I2SSTD_1)
#define LL_I2S_STANDARD_PCM_LONG           (SPI_I2SCFGR_I2SSTD_0 | SPI_I2SCFGR_I2SSTD_1 | SPI_I2SCFGR_PCMSYNC)

#define LL_I2S_MODE_SLAVE_TX               0x00000000U
#define LL_I2S_MODE_SLAVE_RX               (SPI_I2SCFGR_I2SCFG_0)
#define LL_I2S_MODE_MASTER_TX              (SPI_I2SCFGR_I2SCFG_1)
#define LL_I2S_MODE_MASTER_RX              (SPI_I2SCFGR_I2SCFG_0 | SPI_I2SCFGR_I2SCFG_1)

#define LL_I2S_PRESCALER_PARITY_EVEN       0x00000000U
#define LL_I2S_PRESCALER_PARITY_ODD        (SPI_I2SPR_ODD >> 8U)

#if defined(USE_FULL_LL_DRIVER)

#define LL_I2S_MCLK_OUTPUT_DISABLE         0x00000000U
#define LL_I2S_MCLK_OUTPUT_ENABLE          (SPI_I2SPR_MCKOE)

#define LL_I2S_AUDIOFREQ_192K              192000U
#define LL_I2S_AUDIOFREQ_96K               96000U
#define LL_I2S_AUDIOFREQ_48K               48000U
#define LL_I2S_AUDIOFREQ_44K               44100U
#define LL_I2S_AUDIOFREQ_32K               32000U
#define LL_I2S_AUDIOFREQ_22K               22050U
#define LL_I2S_AUDIOFREQ_16K               16000U
#define LL_I2S_AUDIOFREQ_11K               11025U
#define LL_I2S_AUDIOFREQ_8K                8000U
#define LL_I2S_AUDIOFREQ_DEFAULT           2U

#endif

#define LL_I2S_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_I2S_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

__STATIC_INLINE void LL_I2S_Enable(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SE);
}

__STATIC_INLINE void LL_I2S_Disable(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SMOD | SPI_I2SCFGR_I2SE);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabled(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SE) == (SPI_I2SCFGR_I2SE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_I2S_SetDataFormat(SPI_TypeDef *SPIx, uint32_t DataFormat)
{
  MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN, DataFormat);
}

__STATIC_INLINE uint32_t LL_I2S_GetDataFormat(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_DATLEN | SPI_I2SCFGR_CHLEN));
}

__STATIC_INLINE void LL_I2S_SetClockPolarity(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  SET_BIT(SPIx->I2SCFGR, ClockPolarity);
}

__STATIC_INLINE uint32_t LL_I2S_GetClockPolarity(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_CKPOL));
}

__STATIC_INLINE void LL_I2S_SetStandard(SPI_TypeDef *SPIx, uint32_t Standard)
{
  MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC, Standard);
}

__STATIC_INLINE uint32_t LL_I2S_GetStandard(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SSTD | SPI_I2SCFGR_PCMSYNC));
}

__STATIC_INLINE void LL_I2S_SetTransferMode(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->I2SCFGR, SPI_I2SCFGR_I2SCFG, Mode);
}

__STATIC_INLINE uint32_t LL_I2S_GetTransferMode(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_I2SCFG));
}

__STATIC_INLINE void LL_I2S_SetPrescalerLinear(SPI_TypeDef *SPIx, uint8_t PrescalerLinear)
{
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_I2SDIV, PrescalerLinear);
}

__STATIC_INLINE uint32_t LL_I2S_GetPrescalerLinear(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_I2SDIV));
}

__STATIC_INLINE void LL_I2S_SetPrescalerParity(SPI_TypeDef *SPIx, uint32_t PrescalerParity)
{
  MODIFY_REG(SPIx->I2SPR, SPI_I2SPR_ODD, PrescalerParity << 8U);
}

__STATIC_INLINE uint32_t LL_I2S_GetPrescalerParity(const SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->I2SPR, SPI_I2SPR_ODD) >> 8U);
}

__STATIC_INLINE void LL_I2S_EnableMasterClock(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE);
}

__STATIC_INLINE void LL_I2S_DisableMasterClock(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledMasterClock(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->I2SPR, SPI_I2SPR_MCKOE) == (SPI_I2SPR_MCKOE)) ? 1UL : 0UL);
}

#if defined(SPI_I2SCFGR_ASTRTEN)

__STATIC_INLINE void LL_I2S_EnableAsyncStart(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_ASTRTEN);
}

__STATIC_INLINE void LL_I2S_DisableAsyncStart(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_ASTRTEN);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledAsyncStart(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->I2SCFGR, SPI_I2SCFGR_ASTRTEN) == (SPI_I2SCFGR_ASTRTEN)) ? 1UL : 0UL);
}
#endif

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_RXNE(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsActiveFlag_RXNE(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_TXE(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsActiveFlag_TXE(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_BSY(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsActiveFlag_BSY(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_OVR(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsActiveFlag_OVR(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_UDR(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_UDR) == (SPI_SR_UDR)) ? 1UL : 0UL);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_FRE(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsActiveFlag_FRE(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsActiveFlag_CHSIDE(const SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->SR, SPI_SR_CHSIDE) == (SPI_SR_CHSIDE)) ? 1UL : 0UL);
}

__STATIC_INLINE void LL_I2S_ClearFlag_OVR(SPI_TypeDef *SPIx)
{
  LL_SPI_ClearFlag_OVR(SPIx);
}

__STATIC_INLINE void LL_I2S_ClearFlag_UDR(const SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void)tmpreg;
}

__STATIC_INLINE void LL_I2S_ClearFlag_FRE(const SPI_TypeDef *SPIx)
{
  LL_SPI_ClearFlag_FRE(SPIx);
}

__STATIC_INLINE void LL_I2S_EnableIT_ERR(SPI_TypeDef *SPIx)
{
  LL_SPI_EnableIT_ERR(SPIx);
}

__STATIC_INLINE void LL_I2S_EnableIT_RXNE(SPI_TypeDef *SPIx)
{
  LL_SPI_EnableIT_RXNE(SPIx);
}

__STATIC_INLINE void LL_I2S_EnableIT_TXE(SPI_TypeDef *SPIx)
{
  LL_SPI_EnableIT_TXE(SPIx);
}

__STATIC_INLINE void LL_I2S_DisableIT_ERR(SPI_TypeDef *SPIx)
{
  LL_SPI_DisableIT_ERR(SPIx);
}

__STATIC_INLINE void LL_I2S_DisableIT_RXNE(SPI_TypeDef *SPIx)
{
  LL_SPI_DisableIT_RXNE(SPIx);
}

__STATIC_INLINE void LL_I2S_DisableIT_TXE(SPI_TypeDef *SPIx)
{
  LL_SPI_DisableIT_TXE(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledIT_ERR(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsEnabledIT_ERR(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledIT_RXNE(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsEnabledIT_RXNE(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledIT_TXE(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsEnabledIT_TXE(SPIx);
}

__STATIC_INLINE void LL_I2S_EnableDMAReq_RX(SPI_TypeDef *SPIx)
{
  LL_SPI_EnableDMAReq_RX(SPIx);
}

__STATIC_INLINE void LL_I2S_DisableDMAReq_RX(SPI_TypeDef *SPIx)
{
  LL_SPI_DisableDMAReq_RX(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledDMAReq_RX(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsEnabledDMAReq_RX(SPIx);
}

__STATIC_INLINE void LL_I2S_EnableDMAReq_TX(SPI_TypeDef *SPIx)
{
  LL_SPI_EnableDMAReq_TX(SPIx);
}

__STATIC_INLINE void LL_I2S_DisableDMAReq_TX(SPI_TypeDef *SPIx)
{
  LL_SPI_DisableDMAReq_TX(SPIx);
}

__STATIC_INLINE uint32_t LL_I2S_IsEnabledDMAReq_TX(const SPI_TypeDef *SPIx)
{
  return LL_SPI_IsEnabledDMAReq_TX(SPIx);
}

__STATIC_INLINE uint16_t LL_I2S_ReceiveData16(SPI_TypeDef *SPIx)
{
  return LL_SPI_ReceiveData16(SPIx);
}

__STATIC_INLINE void LL_I2S_TransmitData16(SPI_TypeDef *SPIx, uint16_t TxData)
{
  LL_SPI_TransmitData16(SPIx, TxData);
}

#if defined(USE_FULL_LL_DRIVER)

ErrorStatus LL_I2S_DeInit(const SPI_TypeDef *SPIx);
ErrorStatus LL_I2S_Init(SPI_TypeDef *SPIx, LL_I2S_InitTypeDef *I2S_InitStruct);
void        LL_I2S_StructInit(LL_I2S_InitTypeDef *I2S_InitStruct);
void        LL_I2S_ConfigPrescaler(SPI_TypeDef *SPIx, uint32_t PrescalerLinear, uint32_t PrescalerParity);
#if defined (SPI_I2S_FULLDUPLEX_SUPPORT)
ErrorStatus LL_I2S_InitFullDuplex(SPI_TypeDef *I2Sxext, LL_I2S_InitTypeDef *I2S_InitStruct);
#endif

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
