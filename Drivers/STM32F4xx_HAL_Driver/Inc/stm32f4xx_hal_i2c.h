#ifndef __STM32F4xx_HAL_I2C_H
#define __STM32F4xx_HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t ClockSpeed;

  uint32_t DutyCycle;

  uint32_t OwnAddress1;

  uint32_t AddressingMode;

  uint32_t DualAddressMode;

  uint32_t OwnAddress2;

  uint32_t GeneralCallMode;

  uint32_t NoStretchMode;

} I2C_InitTypeDef;

typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,
  HAL_I2C_STATE_READY             = 0x20U,
  HAL_I2C_STATE_BUSY              = 0x24U,
  HAL_I2C_STATE_BUSY_TX           = 0x21U,
  HAL_I2C_STATE_BUSY_RX           = 0x22U,
  HAL_I2C_STATE_LISTEN            = 0x28U,
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,
  HAL_I2C_STATE_ABORT             = 0x60U,
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,
  HAL_I2C_STATE_ERROR             = 0xE0U

} HAL_I2C_StateTypeDef;

typedef enum
{
  HAL_I2C_MODE_NONE               = 0x00U,
  HAL_I2C_MODE_MASTER             = 0x10U,
  HAL_I2C_MODE_SLAVE              = 0x20U,
  HAL_I2C_MODE_MEM                = 0x40U

} HAL_I2C_ModeTypeDef;

#define HAL_I2C_ERROR_NONE              0x00000000U
#define HAL_I2C_ERROR_BERR              0x00000001U
#define HAL_I2C_ERROR_ARLO              0x00000002U
#define HAL_I2C_ERROR_AF                0x00000004U
#define HAL_I2C_ERROR_OVR               0x00000008U
#define HAL_I2C_ERROR_DMA               0x00000010U
#define HAL_I2C_ERROR_TIMEOUT           0x00000020U
#define HAL_I2C_ERROR_SIZE              0x00000040U
#define HAL_I2C_ERROR_DMA_PARAM         0x00000080U
#define HAL_I2C_WRONG_START             0x00000200U
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#define HAL_I2C_ERROR_INVALID_CALLBACK  0x00000100U
#endif

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
typedef struct __I2C_HandleTypeDef
#else
typedef struct
#endif
{
  I2C_TypeDef                *Instance;

  I2C_InitTypeDef            Init;

  uint8_t                    *pBuffPtr;

  uint16_t                   XferSize;

  __IO uint16_t              XferCount;

  __IO uint32_t              XferOptions;

  __IO uint32_t              PreviousState;

  DMA_HandleTypeDef          *hdmatx;

  DMA_HandleTypeDef          *hdmarx;

  HAL_LockTypeDef            Lock;

  __IO HAL_I2C_StateTypeDef  State;

  __IO HAL_I2C_ModeTypeDef   Mode;

  __IO uint32_t              ErrorCode;

  __IO uint32_t              Devaddress;

  __IO uint32_t              Memaddress;

  __IO uint32_t              MemaddSize;

  __IO uint32_t              EventCount;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
  void (* MasterTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* MasterRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* SlaveTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* SlaveRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* ListenCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* MemTxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* MemRxCpltCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* ErrorCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* AbortCpltCallback)(struct __I2C_HandleTypeDef *hi2c);

  void (* AddrCallback)(struct __I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);

  void (* MspInitCallback)(struct __I2C_HandleTypeDef *hi2c);
  void (* MspDeInitCallback)(struct __I2C_HandleTypeDef *hi2c);

#endif
} I2C_HandleTypeDef;

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)

typedef enum
{
  HAL_I2C_MASTER_TX_COMPLETE_CB_ID      = 0x00U,
  HAL_I2C_MASTER_RX_COMPLETE_CB_ID      = 0x01U,
  HAL_I2C_SLAVE_TX_COMPLETE_CB_ID       = 0x02U,
  HAL_I2C_SLAVE_RX_COMPLETE_CB_ID       = 0x03U,
  HAL_I2C_LISTEN_COMPLETE_CB_ID         = 0x04U,
  HAL_I2C_MEM_TX_COMPLETE_CB_ID         = 0x05U,
  HAL_I2C_MEM_RX_COMPLETE_CB_ID         = 0x06U,
  HAL_I2C_ERROR_CB_ID                   = 0x07U,
  HAL_I2C_ABORT_CB_ID                   = 0x08U,

  HAL_I2C_MSPINIT_CB_ID                 = 0x09U,
  HAL_I2C_MSPDEINIT_CB_ID               = 0x0AU

} HAL_I2C_CallbackIDTypeDef;

typedef  void (*pI2C_CallbackTypeDef)(I2C_HandleTypeDef *hi2c);
typedef  void (*pI2C_AddrCallbackTypeDef)(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);

#endif

#define I2C_DUTYCYCLE_2                 0x00000000U
#define I2C_DUTYCYCLE_16_9              I2C_CCR_DUTY

#define I2C_ADDRESSINGMODE_7BIT         0x00004000U
#define I2C_ADDRESSINGMODE_10BIT        (I2C_OAR1_ADDMODE | 0x00004000U)

#define I2C_DUALADDRESS_DISABLE        0x00000000U
#define I2C_DUALADDRESS_ENABLE         I2C_OAR2_ENDUAL

#define I2C_GENERALCALL_DISABLE        0x00000000U
#define I2C_GENERALCALL_ENABLE         I2C_CR1_ENGC

#define I2C_NOSTRETCH_DISABLE          0x00000000U
#define I2C_NOSTRETCH_ENABLE           I2C_CR1_NOSTRETCH

#define I2C_MEMADD_SIZE_8BIT            0x00000001U
#define I2C_MEMADD_SIZE_16BIT           0x00000010U

#define I2C_DIRECTION_RECEIVE           0x00000000U
#define I2C_DIRECTION_TRANSMIT          0x00000001U

#define  I2C_FIRST_FRAME                0x00000001U
#define  I2C_FIRST_AND_NEXT_FRAME       0x00000002U
#define  I2C_NEXT_FRAME                 0x00000004U
#define  I2C_FIRST_AND_LAST_FRAME       0x00000008U
#define  I2C_LAST_FRAME_NO_STOP         0x00000010U
#define  I2C_LAST_FRAME                 0x00000020U

#define  I2C_OTHER_FRAME                (0x00AA0000U)
#define  I2C_OTHER_AND_LAST_FRAME       (0xAA000000U)

#define I2C_IT_BUF                      I2C_CR2_ITBUFEN
#define I2C_IT_EVT                      I2C_CR2_ITEVTEN
#define I2C_IT_ERR                      I2C_CR2_ITERREN

#define I2C_FLAG_OVR                    0x00010800U
#define I2C_FLAG_AF                     0x00010400U
#define I2C_FLAG_ARLO                   0x00010200U
#define I2C_FLAG_BERR                   0x00010100U
#define I2C_FLAG_TXE                    0x00010080U
#define I2C_FLAG_RXNE                   0x00010040U
#define I2C_FLAG_STOPF                  0x00010010U
#define I2C_FLAG_ADD10                  0x00010008U
#define I2C_FLAG_BTF                    0x00010004U
#define I2C_FLAG_ADDR                   0x00010002U
#define I2C_FLAG_SB                     0x00010001U
#define I2C_FLAG_DUALF                  0x00100080U
#define I2C_FLAG_GENCALL                0x00100010U
#define I2C_FLAG_TRA                    0x00100004U
#define I2C_FLAG_BUSY                   0x00100002U
#define I2C_FLAG_MSL                    0x00100001U

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__)                do{                                                   \
                                                                    (__HANDLE__)->State = HAL_I2C_STATE_RESET;       \
                                                                    (__HANDLE__)->MspInitCallback = NULL;            \
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;          \
                                                                  } while(0)
#else
#define __HAL_I2C_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_I2C_STATE_RESET)
#endif

#define __HAL_I2C_ENABLE_IT(__HANDLE__, __INTERRUPT__)   SET_BIT((__HANDLE__)->Instance->CR2,(__INTERRUPT__))
#define __HAL_I2C_DISABLE_IT(__HANDLE__, __INTERRUPT__)  CLEAR_BIT((__HANDLE__)->Instance->CR2, (__INTERRUPT__))

#define __HAL_I2C_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR2 & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

#define __HAL_I2C_GET_FLAG(__HANDLE__, __FLAG__) ((((uint8_t)((__FLAG__) >> 16U)) == 0x01U) ? \
                                                  (((((__HANDLE__)->Instance->SR1) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET) : \
                                                  (((((__HANDLE__)->Instance->SR2) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET))

#define __HAL_I2C_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->SR1 = ~((__FLAG__) & I2C_FLAG_MASK))

#define __HAL_I2C_CLEAR_ADDRFLAG(__HANDLE__)    \
  do{                                           \
    __IO uint32_t tmpreg = 0x00U;               \
    tmpreg = (__HANDLE__)->Instance->SR1;       \
    tmpreg = (__HANDLE__)->Instance->SR2;       \
    UNUSED(tmpreg);                             \
  } while(0)

#define __HAL_I2C_CLEAR_STOPFLAG(__HANDLE__)           \
  do{                                                  \
    __IO uint32_t tmpreg = 0x00U;                      \
    tmpreg = (__HANDLE__)->Instance->SR1;              \
    SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE);  \
    UNUSED(tmpreg);                                    \
  } while(0)

#define __HAL_I2C_ENABLE(__HANDLE__)                  SET_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)

#define __HAL_I2C_DISABLE(__HANDLE__)                 CLEAR_BIT((__HANDLE__)->Instance->CR1, I2C_CR1_PE)

#include "stm32f4xx_hal_i2c_ex.h"

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c);

#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_I2C_RegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID, pI2C_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2C_UnRegisterCallback(I2C_HandleTypeDef *hi2c, HAL_I2C_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_I2C_RegisterAddrCallback(I2C_HandleTypeDef *hi2c, pI2C_AddrCallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_I2C_UnRegisterAddrCallback(I2C_HandleTypeDef *hi2c);
#endif

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_EnableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DisableListen_IT(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_Master_Abort_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress);

HAL_StatusTypeDef HAL_I2C_Master_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Master_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Slave_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Write_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_I2C_Mem_Read_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);

HAL_StatusTypeDef HAL_I2C_Master_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Master_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Transmit_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);
HAL_StatusTypeDef HAL_I2C_Slave_Seq_Receive_DMA(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t Size, uint32_t XferOptions);

void HAL_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ER_IRQHandler(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode);
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c);
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c);

HAL_I2C_StateTypeDef HAL_I2C_GetState(I2C_HandleTypeDef *hi2c);
HAL_I2C_ModeTypeDef HAL_I2C_GetMode(I2C_HandleTypeDef *hi2c);
uint32_t HAL_I2C_GetError(I2C_HandleTypeDef *hi2c);

#define I2C_FLAG_MASK                    0x0000FFFFU
#define I2C_MIN_PCLK_FREQ_STANDARD       2000000U
#define I2C_MIN_PCLK_FREQ_FAST           4000000U

#define I2C_MIN_PCLK_FREQ(__PCLK__, __SPEED__)             (((__SPEED__) <= 100000U) ? ((__PCLK__) < I2C_MIN_PCLK_FREQ_STANDARD) : ((__PCLK__) < I2C_MIN_PCLK_FREQ_FAST))
#define I2C_CCR_CALCULATION(__PCLK__, __SPEED__, __COEFF__)     (((((__PCLK__) - 1U)/((__SPEED__) * (__COEFF__))) + 1U) & I2C_CCR_CCR)
#define I2C_FREQRANGE(__PCLK__)                            ((__PCLK__)/1000000U)
#define I2C_RISE_TIME(__FREQRANGE__, __SPEED__)            (((__SPEED__) <= 100000U) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))
#define I2C_SPEED_STANDARD(__PCLK__, __SPEED__)            ((I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U) < 4U)? 4U:I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 2U))
#define I2C_SPEED_FAST(__PCLK__, __SPEED__, __DUTYCYCLE__) (((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 3U) : (I2C_CCR_CALCULATION((__PCLK__), (__SPEED__), 25U) | I2C_DUTYCYCLE_16_9))
#define I2C_SPEED(__PCLK__, __SPEED__, __DUTYCYCLE__)      (((__SPEED__) <= 100000U)? (I2C_SPEED_STANDARD((__PCLK__), (__SPEED__))) : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__)) & I2C_CCR_CCR) == 0U)? 1U : \
                                                                  ((I2C_SPEED_FAST((__PCLK__), (__SPEED__), (__DUTYCYCLE__))) | I2C_CCR_FS))

#define I2C_7BIT_ADD_WRITE(__ADDRESS__)                    ((uint8_t)((__ADDRESS__) & (uint8_t)(~I2C_OAR1_ADD0)))
#define I2C_7BIT_ADD_READ(__ADDRESS__)                     ((uint8_t)((__ADDRESS__) | I2C_OAR1_ADD0))

#define I2C_10BIT_ADDRESS(__ADDRESS__)                     ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))
#define I2C_10BIT_HEADER_WRITE(__ADDRESS__)                ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0x0300)) >> 7) | (uint16_t)0x00F0)))
#define I2C_10BIT_HEADER_READ(__ADDRESS__)                 ((uint8_t)((uint16_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0x0300)) >> 7) | (uint16_t)(0x00F1))))

#define I2C_MEM_ADD_MSB(__ADDRESS__)                       ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & (uint16_t)0xFF00)) >> 8)))
#define I2C_MEM_ADD_LSB(__ADDRESS__)                       ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)0x00FF)))

#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DUTYCYCLE_2) || \
                                  ((CYCLE) == I2C_DUTYCYCLE_16_9))
#define IS_I2C_ADDRESSING_MODE(ADDRESS) (((ADDRESS) == I2C_ADDRESSINGMODE_7BIT) || \
                                         ((ADDRESS) == I2C_ADDRESSINGMODE_10BIT))
#define IS_I2C_DUAL_ADDRESS(ADDRESS) (((ADDRESS) == I2C_DUALADDRESS_DISABLE) || \
                                      ((ADDRESS) == I2C_DUALADDRESS_ENABLE))
#define IS_I2C_GENERAL_CALL(CALL) (((CALL) == I2C_GENERALCALL_DISABLE) || \
                                   ((CALL) == I2C_GENERALCALL_ENABLE))
#define IS_I2C_NO_STRETCH(STRETCH) (((STRETCH) == I2C_NOSTRETCH_DISABLE) || \
                                    ((STRETCH) == I2C_NOSTRETCH_ENABLE))
#define IS_I2C_MEMADD_SIZE(SIZE) (((SIZE) == I2C_MEMADD_SIZE_8BIT) || \
                                  ((SIZE) == I2C_MEMADD_SIZE_16BIT))
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) > 0U) && ((SPEED) <= 400000U))
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) (((ADDRESS1) & 0xFFFFFC00U) == 0U)
#define IS_I2C_OWN_ADDRESS2(ADDRESS2) (((ADDRESS2) & 0xFFFFFF01U) == 0U)
#define IS_I2C_TRANSFER_OPTIONS_REQUEST(REQUEST)      (((REQUEST) == I2C_FIRST_FRAME)              || \
                                                       ((REQUEST) == I2C_FIRST_AND_NEXT_FRAME)     || \
                                                       ((REQUEST) == I2C_NEXT_FRAME)               || \
                                                       ((REQUEST) == I2C_FIRST_AND_LAST_FRAME)     || \
                                                       ((REQUEST) == I2C_LAST_FRAME)               || \
                                                       ((REQUEST) == I2C_LAST_FRAME_NO_STOP)       || \
                                                       IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST))

#define IS_I2C_TRANSFER_OTHER_OPTIONS_REQUEST(REQUEST) (((REQUEST) == I2C_OTHER_FRAME)     || \
                                                        ((REQUEST) == I2C_OTHER_AND_LAST_FRAME))

#define I2C_CHECK_FLAG(__ISR__, __FLAG__)         ((((__ISR__) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET)
#define I2C_CHECK_IT_SOURCE(__CR1__, __IT__)      ((((__CR1__) & (__IT__)) == (__IT__)) ? SET : RESET)

#ifdef __cplusplus
}
#endif

#endif
