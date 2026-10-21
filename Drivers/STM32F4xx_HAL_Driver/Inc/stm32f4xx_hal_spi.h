#ifndef STM32F4xx_HAL_SPI_H
#define STM32F4xx_HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t Mode;

  uint32_t Direction;

  uint32_t DataSize;

  uint32_t CLKPolarity;

  uint32_t CLKPhase;

  uint32_t NSS;

  uint32_t BaudRatePrescaler;

  uint32_t FirstBit;

  uint32_t TIMode;

  uint32_t CRCCalculation;

  uint32_t CRCPolynomial;
} SPI_InitTypeDef;

typedef enum
{
  HAL_SPI_STATE_RESET      = 0x00U,
  HAL_SPI_STATE_READY      = 0x01U,
  HAL_SPI_STATE_BUSY       = 0x02U,
  HAL_SPI_STATE_BUSY_TX    = 0x03U,
  HAL_SPI_STATE_BUSY_RX    = 0x04U,
  HAL_SPI_STATE_BUSY_TX_RX = 0x05U,
  HAL_SPI_STATE_ERROR      = 0x06U,
  HAL_SPI_STATE_ABORT      = 0x07U
} HAL_SPI_StateTypeDef;

typedef struct __SPI_HandleTypeDef
{
  SPI_TypeDef                *Instance;

  SPI_InitTypeDef            Init;

  const uint8_t              *pTxBuffPtr;

  uint16_t                   TxXferSize;

  __IO uint16_t              TxXferCount;

  uint8_t                    *pRxBuffPtr;

  uint16_t                   RxXferSize;

  __IO uint16_t              RxXferCount;

  void (*RxISR)(struct __SPI_HandleTypeDef *hspi);

  void (*TxISR)(struct __SPI_HandleTypeDef *hspi);

  DMA_HandleTypeDef          *hdmatx;

  DMA_HandleTypeDef          *hdmarx;

  HAL_LockTypeDef            Lock;

  __IO HAL_SPI_StateTypeDef  State;

  __IO uint32_t              ErrorCode;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
  void (* TxCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* RxCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* TxRxCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* TxHalfCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* RxHalfCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* TxRxHalfCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* ErrorCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* AbortCpltCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* MspInitCallback)(struct __SPI_HandleTypeDef *hspi);
  void (* MspDeInitCallback)(struct __SPI_HandleTypeDef *hspi);

#endif
} SPI_HandleTypeDef;

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)

typedef enum
{
  HAL_SPI_TX_COMPLETE_CB_ID             = 0x00U,
  HAL_SPI_RX_COMPLETE_CB_ID             = 0x01U,
  HAL_SPI_TX_RX_COMPLETE_CB_ID          = 0x02U,
  HAL_SPI_TX_HALF_COMPLETE_CB_ID        = 0x03U,
  HAL_SPI_RX_HALF_COMPLETE_CB_ID        = 0x04U,
  HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID     = 0x05U,
  HAL_SPI_ERROR_CB_ID                   = 0x06U,
  HAL_SPI_ABORT_CB_ID                   = 0x07U,
  HAL_SPI_MSPINIT_CB_ID                 = 0x08U,
  HAL_SPI_MSPDEINIT_CB_ID               = 0x09U

} HAL_SPI_CallbackIDTypeDef;

typedef  void (*pSPI_CallbackTypeDef)(SPI_HandleTypeDef *hspi);

#endif

#define HAL_SPI_ERROR_NONE              (0x00000000U)
#define HAL_SPI_ERROR_MODF              (0x00000001U)
#define HAL_SPI_ERROR_CRC               (0x00000002U)
#define HAL_SPI_ERROR_OVR               (0x00000004U)
#define HAL_SPI_ERROR_FRE               (0x00000008U)
#define HAL_SPI_ERROR_DMA               (0x00000010U)
#define HAL_SPI_ERROR_FLAG              (0x00000020U)
#define HAL_SPI_ERROR_ABORT             (0x00000040U)
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
#define HAL_SPI_ERROR_INVALID_CALLBACK  (0x00000080U)
#endif

#define SPI_MODE_SLAVE                  (0x00000000U)
#define SPI_MODE_MASTER                 (SPI_CR1_MSTR | SPI_CR1_SSI)

#define SPI_DIRECTION_2LINES            (0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY     SPI_CR1_RXONLY
#define SPI_DIRECTION_1LINE             SPI_CR1_BIDIMODE

#define SPI_DATASIZE_8BIT               (0x00000000U)
#define SPI_DATASIZE_16BIT              SPI_CR1_DFF

#define SPI_POLARITY_LOW                (0x00000000U)
#define SPI_POLARITY_HIGH               SPI_CR1_CPOL

#define SPI_PHASE_1EDGE                 (0x00000000U)
#define SPI_PHASE_2EDGE                 SPI_CR1_CPHA

#define SPI_NSS_SOFT                    SPI_CR1_SSM
#define SPI_NSS_HARD_INPUT              (0x00000000U)
#define SPI_NSS_HARD_OUTPUT             (SPI_CR2_SSOE << 16U)

#define SPI_BAUDRATEPRESCALER_2         (0x00000000U)
#define SPI_BAUDRATEPRESCALER_4         (SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_8         (SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_16        (SPI_CR1_BR_1 | SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_32        (SPI_CR1_BR_2)
#define SPI_BAUDRATEPRESCALER_64        (SPI_CR1_BR_2 | SPI_CR1_BR_0)
#define SPI_BAUDRATEPRESCALER_128       (SPI_CR1_BR_2 | SPI_CR1_BR_1)
#define SPI_BAUDRATEPRESCALER_256       (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)

#define SPI_FIRSTBIT_MSB                (0x00000000U)
#define SPI_FIRSTBIT_LSB                SPI_CR1_LSBFIRST

#define SPI_TIMODE_DISABLE              (0x00000000U)
#define SPI_TIMODE_ENABLE               SPI_CR2_FRF

#define SPI_CRCCALCULATION_DISABLE      (0x00000000U)
#define SPI_CRCCALCULATION_ENABLE       SPI_CR1_CRCEN

#define SPI_IT_TXE                      SPI_CR2_TXEIE
#define SPI_IT_RXNE                     SPI_CR2_RXNEIE
#define SPI_IT_ERR                      SPI_CR2_ERRIE

#define SPI_FLAG_RXNE                   SPI_SR_RXNE
#define SPI_FLAG_TXE                    SPI_SR_TXE
#define SPI_FLAG_BSY                    SPI_SR_BSY
#define SPI_FLAG_CRCERR                 SPI_SR_CRCERR
#define SPI_FLAG_MODF                   SPI_SR_MODF
#define SPI_FLAG_OVR                    SPI_SR_OVR
#define SPI_FLAG_FRE                    SPI_SR_FRE
#define SPI_FLAG_MASK                   (SPI_SR_RXNE | SPI_SR_TXE | SPI_SR_BSY | SPI_SR_CRCERR\
                                         | SPI_SR_MODF | SPI_SR_OVR | SPI_SR_FRE)

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
#define __HAL_SPI_RESET_HANDLE_STATE(__HANDLE__)      \
  do{                                                 \
    (__HANDLE__)->State = HAL_SPI_STATE_RESET;        \
    (__HANDLE__)->MspInitCallback = NULL;             \
    (__HANDLE__)->MspDeInitCallback = NULL;           \
  } while(0)
#else
#define __HAL_SPI_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_SPI_STATE_RESET)
#endif

#define __HAL_SPI_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))

#define __HAL_SPI_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))

#define __HAL_SPI_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR2\
                                                              & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

#define __HAL_SPI_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

#define __HAL_SPI_CLEAR_CRCERRFLAG(__HANDLE__) ((__HANDLE__)->Instance->SR = (uint16_t)(~SPI_FLAG_CRCERR))

#define __HAL_SPI_CLEAR_MODFFLAG(__HANDLE__)             \
  do{                                                    \
    __IO uint32_t tmpreg_modf = 0x00U;                   \
    tmpreg_modf = (__HANDLE__)->Instance->SR;            \
    CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE); \
    UNUSED(tmpreg_modf);                                 \
  } while(0U)

#define __HAL_SPI_CLEAR_OVRFLAG(__HANDLE__)        \
  do{                                              \
    __IO uint32_t tmpreg_ovr = 0x00U;              \
    tmpreg_ovr = (__HANDLE__)->Instance->DR;       \
    tmpreg_ovr = (__HANDLE__)->Instance->SR;       \
    UNUSED(tmpreg_ovr);                            \
  } while(0U)

#define __HAL_SPI_CLEAR_FREFLAG(__HANDLE__)        \
  do{                                              \
    __IO uint32_t tmpreg_fre = 0x00U;              \
    tmpreg_fre = (__HANDLE__)->Instance->SR;       \
    UNUSED(tmpreg_fre);                            \
  } while(0U)

#define __HAL_SPI_ENABLE(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)

#define __HAL_SPI_DISABLE(__HANDLE__) CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_SPE)

#define SPI_1LINE_TX(__HANDLE__)  SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_BIDIOE)

#define SPI_1LINE_RX(__HANDLE__)  CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_BIDIOE)

#define SPI_RESET_CRC(__HANDLE__)                           \
  do{                                                       \
    CLEAR_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_CRCEN);  \
    SET_BIT((__HANDLE__)->Instance->CR1, SPI_CR1_CRCEN);    \
  } while(0U)

#define SPI_CHECK_FLAG(__SR__, __FLAG__) ((((__SR__) & ((__FLAG__) & SPI_FLAG_MASK)) == \
                                           ((__FLAG__) & SPI_FLAG_MASK)) ? SET : RESET)

#define SPI_CHECK_IT_SOURCE(__CR2__, __INTERRUPT__) ((((__CR2__) & (__INTERRUPT__)) == \
                                                      (__INTERRUPT__)) ? SET : RESET)

#define IS_SPI_MODE(__MODE__)      (((__MODE__) == SPI_MODE_SLAVE)   || \
                                    ((__MODE__) == SPI_MODE_MASTER))

#define IS_SPI_DIRECTION(__MODE__) (((__MODE__) == SPI_DIRECTION_2LINES)        || \
                                    ((__MODE__) == SPI_DIRECTION_2LINES_RXONLY) || \
                                    ((__MODE__) == SPI_DIRECTION_1LINE))

#define IS_SPI_DIRECTION_2LINES(__MODE__) ((__MODE__) == SPI_DIRECTION_2LINES)

#define IS_SPI_DIRECTION_2LINES_OR_1LINE(__MODE__) (((__MODE__) == SPI_DIRECTION_2LINES) || \
                                                    ((__MODE__) == SPI_DIRECTION_1LINE))

#define IS_SPI_DATASIZE(__DATASIZE__) (((__DATASIZE__) == SPI_DATASIZE_16BIT) || \
                                       ((__DATASIZE__) == SPI_DATASIZE_8BIT))

#define IS_SPI_CPOL(__CPOL__)      (((__CPOL__) == SPI_POLARITY_LOW) || \
                                    ((__CPOL__) == SPI_POLARITY_HIGH))

#define IS_SPI_CPHA(__CPHA__)      (((__CPHA__) == SPI_PHASE_1EDGE) || \
                                    ((__CPHA__) == SPI_PHASE_2EDGE))

#define IS_SPI_NSS(__NSS__)        (((__NSS__) == SPI_NSS_SOFT)       || \
                                    ((__NSS__) == SPI_NSS_HARD_INPUT) || \
                                    ((__NSS__) == SPI_NSS_HARD_OUTPUT))

#define IS_SPI_BAUDRATE_PRESCALER(__PRESCALER__) (((__PRESCALER__) == SPI_BAUDRATEPRESCALER_2)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_4)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_8)   || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_16)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_32)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_64)  || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_128) || \
                                                  ((__PRESCALER__) == SPI_BAUDRATEPRESCALER_256))

#define IS_SPI_FIRST_BIT(__BIT__)  (((__BIT__) == SPI_FIRSTBIT_MSB) || \
                                    ((__BIT__) == SPI_FIRSTBIT_LSB))

#define IS_SPI_TIMODE(__MODE__)    (((__MODE__) == SPI_TIMODE_DISABLE) || \
                                    ((__MODE__) == SPI_TIMODE_ENABLE))

#define IS_SPI_CRC_CALCULATION(__CALCULATION__) (((__CALCULATION__) == SPI_CRCCALCULATION_DISABLE) || \
                                                 ((__CALCULATION__) == SPI_CRCCALCULATION_ENABLE))

#define IS_SPI_CRC_POLYNOMIAL(__POLYNOMIAL__) (((__POLYNOMIAL__) >= 0x1U)    && \
                                               ((__POLYNOMIAL__) <= 0xFFFFU) && \
                                               (((__POLYNOMIAL__)&0x1U) != 0U))

#define IS_SPI_DMA_HANDLE(__HANDLE__) ((__HANDLE__) != NULL)

HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
HAL_StatusTypeDef HAL_SPI_RegisterCallback(SPI_HandleTypeDef *hspi, HAL_SPI_CallbackIDTypeDef CallbackID,
                                           pSPI_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_SPI_UnRegisterCallback(SPI_HandleTypeDef *hspi, HAL_SPI_CallbackIDTypeDef CallbackID);
#endif

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                          uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                             uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, const uint8_t *pTxData, uint8_t *pRxData,
                                              uint16_t Size);
HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi);

HAL_StatusTypeDef HAL_SPI_Abort(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_Abort_IT(SPI_HandleTypeDef *hspi);

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);

HAL_SPI_StateTypeDef HAL_SPI_GetState(const SPI_HandleTypeDef *hspi);
uint32_t             HAL_SPI_GetError(const SPI_HandleTypeDef *hspi);

#ifdef __cplusplus
}
#endif

#endif
