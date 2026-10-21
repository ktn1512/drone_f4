#ifndef __STM32F4xx_HAL_DMA_H
#define __STM32F4xx_HAL_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t Channel;

  uint32_t Direction;

  uint32_t PeriphInc;

  uint32_t MemInc;

  uint32_t PeriphDataAlignment;

  uint32_t MemDataAlignment;

  uint32_t Mode;

  uint32_t Priority;

  uint32_t FIFOMode;

  uint32_t FIFOThreshold;

  uint32_t MemBurst;

  uint32_t PeriphBurst;
}DMA_InitTypeDef;

typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,
  HAL_DMA_STATE_READY             = 0x01U,
  HAL_DMA_STATE_BUSY              = 0x02U,
  HAL_DMA_STATE_TIMEOUT           = 0x03U,
  HAL_DMA_STATE_ERROR             = 0x04U,
  HAL_DMA_STATE_ABORT             = 0x05U,
}HAL_DMA_StateTypeDef;

typedef enum
{
  HAL_DMA_FULL_TRANSFER           = 0x00U,
  HAL_DMA_HALF_TRANSFER           = 0x01U
}HAL_DMA_LevelCompleteTypeDef;

typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID         = 0x00U,
  HAL_DMA_XFER_HALFCPLT_CB_ID     = 0x01U,
  HAL_DMA_XFER_M1CPLT_CB_ID       = 0x02U,
  HAL_DMA_XFER_M1HALFCPLT_CB_ID   = 0x03U,
  HAL_DMA_XFER_ERROR_CB_ID        = 0x04U,
  HAL_DMA_XFER_ABORT_CB_ID        = 0x05U,
  HAL_DMA_XFER_ALL_CB_ID          = 0x06U
}HAL_DMA_CallbackIDTypeDef;

typedef struct __DMA_HandleTypeDef
{
  DMA_Stream_TypeDef         *Instance;

  DMA_InitTypeDef            Init;

  HAL_LockTypeDef            Lock;

  __IO HAL_DMA_StateTypeDef  State;

  void                       *Parent;

  void                       (* XferCpltCallback)( struct __DMA_HandleTypeDef * hdma);

  void                       (* XferHalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);

  void                       (* XferM1CpltCallback)( struct __DMA_HandleTypeDef * hdma);

  void                       (* XferM1HalfCpltCallback)( struct __DMA_HandleTypeDef * hdma);

  void                       (* XferErrorCallback)( struct __DMA_HandleTypeDef * hdma);

  void                       (* XferAbortCallback)( struct __DMA_HandleTypeDef * hdma);

  __IO uint32_t              ErrorCode;

  uint32_t                   StreamBaseAddress;

  uint32_t                   StreamIndex;

}DMA_HandleTypeDef;

#define HAL_DMA_ERROR_NONE            0x00000000U
#define HAL_DMA_ERROR_TE              0x00000001U
#define HAL_DMA_ERROR_FE              0x00000002U
#define HAL_DMA_ERROR_DME             0x00000004U
#define HAL_DMA_ERROR_TIMEOUT         0x00000020U
#define HAL_DMA_ERROR_PARAM           0x00000040U
#define HAL_DMA_ERROR_NO_XFER         0x00000080U
#define HAL_DMA_ERROR_NOT_SUPPORTED   0x00000100U

#define DMA_CHANNEL_0                 0x00000000U
#define DMA_CHANNEL_1                 0x02000000U
#define DMA_CHANNEL_2                 0x04000000U
#define DMA_CHANNEL_3                 0x06000000U
#define DMA_CHANNEL_4                 0x08000000U
#define DMA_CHANNEL_5                 0x0A000000U
#define DMA_CHANNEL_6                 0x0C000000U
#define DMA_CHANNEL_7                 0x0E000000U
#if defined (DMA_SxCR_CHSEL_3)
#define DMA_CHANNEL_8                 0x10000000U
#define DMA_CHANNEL_9                 0x12000000U
#define DMA_CHANNEL_10                0x14000000U
#define DMA_CHANNEL_11                0x16000000U
#define DMA_CHANNEL_12                0x18000000U
#define DMA_CHANNEL_13                0x1A000000U
#define DMA_CHANNEL_14                0x1C000000U
#define DMA_CHANNEL_15                0x1E000000U
#endif

#define DMA_PERIPH_TO_MEMORY          0x00000000U
#define DMA_MEMORY_TO_PERIPH          ((uint32_t)DMA_SxCR_DIR_0)
#define DMA_MEMORY_TO_MEMORY          ((uint32_t)DMA_SxCR_DIR_1)

#define DMA_PINC_ENABLE               ((uint32_t)DMA_SxCR_PINC)
#define DMA_PINC_DISABLE              0x00000000U

#define DMA_MINC_ENABLE               ((uint32_t)DMA_SxCR_MINC)
#define DMA_MINC_DISABLE              0x00000000U

#define DMA_PDATAALIGN_BYTE           0x00000000U
#define DMA_PDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_PSIZE_0)
#define DMA_PDATAALIGN_WORD           ((uint32_t)DMA_SxCR_PSIZE_1)

#define DMA_MDATAALIGN_BYTE           0x00000000U
#define DMA_MDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_MSIZE_0)
#define DMA_MDATAALIGN_WORD           ((uint32_t)DMA_SxCR_MSIZE_1)

#define DMA_NORMAL                    0x00000000U
#define DMA_CIRCULAR                  ((uint32_t)DMA_SxCR_CIRC)
#define DMA_PFCTRL                    ((uint32_t)DMA_SxCR_PFCTRL)

#define DMA_PRIORITY_LOW              0x00000000U
#define DMA_PRIORITY_MEDIUM           ((uint32_t)DMA_SxCR_PL_0)
#define DMA_PRIORITY_HIGH             ((uint32_t)DMA_SxCR_PL_1)
#define DMA_PRIORITY_VERY_HIGH        ((uint32_t)DMA_SxCR_PL)

#define DMA_FIFOMODE_DISABLE          0x00000000U
#define DMA_FIFOMODE_ENABLE           ((uint32_t)DMA_SxFCR_DMDIS)

#define DMA_FIFO_THRESHOLD_1QUARTERFULL       0x00000000U
#define DMA_FIFO_THRESHOLD_HALFFULL           ((uint32_t)DMA_SxFCR_FTH_0)
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL      ((uint32_t)DMA_SxFCR_FTH_1)
#define DMA_FIFO_THRESHOLD_FULL               ((uint32_t)DMA_SxFCR_FTH)

#define DMA_MBURST_SINGLE             0x00000000U
#define DMA_MBURST_INC4               ((uint32_t)DMA_SxCR_MBURST_0)
#define DMA_MBURST_INC8               ((uint32_t)DMA_SxCR_MBURST_1)
#define DMA_MBURST_INC16              ((uint32_t)DMA_SxCR_MBURST)

#define DMA_PBURST_SINGLE             0x00000000U
#define DMA_PBURST_INC4               ((uint32_t)DMA_SxCR_PBURST_0)
#define DMA_PBURST_INC8               ((uint32_t)DMA_SxCR_PBURST_1)
#define DMA_PBURST_INC16              ((uint32_t)DMA_SxCR_PBURST)

#define DMA_IT_TC                     ((uint32_t)DMA_SxCR_TCIE)
#define DMA_IT_HT                     ((uint32_t)DMA_SxCR_HTIE)
#define DMA_IT_TE                     ((uint32_t)DMA_SxCR_TEIE)
#define DMA_IT_DME                    ((uint32_t)DMA_SxCR_DMEIE)
#define DMA_IT_FE                     0x00000080U

#define DMA_FLAG_FEIF0_4              0x00000001U
#define DMA_FLAG_DMEIF0_4             0x00000004U
#define DMA_FLAG_TEIF0_4              0x00000008U
#define DMA_FLAG_HTIF0_4              0x00000010U
#define DMA_FLAG_TCIF0_4              0x00000020U
#define DMA_FLAG_FEIF1_5              0x00000040U
#define DMA_FLAG_DMEIF1_5             0x00000100U
#define DMA_FLAG_TEIF1_5              0x00000200U
#define DMA_FLAG_HTIF1_5              0x00000400U
#define DMA_FLAG_TCIF1_5              0x00000800U
#define DMA_FLAG_FEIF2_6              0x00010000U
#define DMA_FLAG_DMEIF2_6             0x00040000U
#define DMA_FLAG_TEIF2_6              0x00080000U
#define DMA_FLAG_HTIF2_6              0x00100000U
#define DMA_FLAG_TCIF2_6              0x00200000U
#define DMA_FLAG_FEIF3_7              0x00400000U
#define DMA_FLAG_DMEIF3_7             0x01000000U
#define DMA_FLAG_TEIF3_7              0x02000000U
#define DMA_FLAG_HTIF3_7              0x04000000U
#define DMA_FLAG_TCIF3_7              0x08000000U

#define __HAL_DMA_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_DMA_STATE_RESET)

#define __HAL_DMA_GET_FS(__HANDLE__)      (((__HANDLE__)->Instance->FCR & (DMA_SxFCR_FS)))

#define __HAL_DMA_ENABLE(__HANDLE__)      ((__HANDLE__)->Instance->CR |=  DMA_SxCR_EN)

#define __HAL_DMA_DISABLE(__HANDLE__)     ((__HANDLE__)->Instance->CR &=  ~DMA_SxCR_EN)

#define __HAL_DMA_GET_TC_FLAG_INDEX(__HANDLE__) \
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TCIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TCIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TCIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TCIF2_6 :\
   DMA_FLAG_TCIF3_7)

#define __HAL_DMA_GET_HT_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_HTIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_HTIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_HTIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_HTIF2_6 :\
   DMA_FLAG_HTIF3_7)

#define __HAL_DMA_GET_TE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TEIF2_6 :\
   DMA_FLAG_TEIF3_7)

#define __HAL_DMA_GET_FE_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_FEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_FEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_FEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_FEIF2_6 :\
   DMA_FLAG_FEIF3_7)

#define __HAL_DMA_GET_DME_FLAG_INDEX(__HANDLE__)\
(((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream0))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream4))? DMA_FLAG_DMEIF0_4 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream1))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream5))? DMA_FLAG_DMEIF1_5 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream2))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA1_Stream6))? DMA_FLAG_DMEIF2_6 :\
 ((uint32_t)((__HANDLE__)->Instance) == ((uint32_t)DMA2_Stream6))? DMA_FLAG_DMEIF2_6 :\
   DMA_FLAG_DMEIF3_7)

#define __HAL_DMA_GET_FLAG(__HANDLE__, __FLAG__)\
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LISR & (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HISR & (__FLAG__)) : (DMA1->LISR & (__FLAG__)))

#define __HAL_DMA_CLEAR_FLAG(__HANDLE__, __FLAG__) \
(((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA2_Stream3)? (DMA2->HIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream7)? (DMA2->LIFCR = (__FLAG__)) :\
 ((uint32_t)((__HANDLE__)->Instance) > (uint32_t)DMA1_Stream3)? (DMA1->HIFCR = (__FLAG__)) : (DMA1->LIFCR = (__FLAG__)))

#define __HAL_DMA_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((__INTERRUPT__) != DMA_IT_FE)? \
((__HANDLE__)->Instance->CR |= (__INTERRUPT__)) : ((__HANDLE__)->Instance->FCR |= (__INTERRUPT__)))

#define __HAL_DMA_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__)) : ((__HANDLE__)->Instance->FCR &= ~(__INTERRUPT__)))

#define __HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  (((__INTERRUPT__) != DMA_IT_FE)? \
                                                        ((__HANDLE__)->Instance->CR & (__INTERRUPT__)) : \
                                                        ((__HANDLE__)->Instance->FCR & (__INTERRUPT__)))

#define __HAL_DMA_SET_COUNTER(__HANDLE__, __COUNTER__) ((__HANDLE__)->Instance->NDTR = (uint16_t)(__COUNTER__))

#define __HAL_DMA_GET_COUNTER(__HANDLE__) ((__HANDLE__)->Instance->NDTR)

#include "stm32f4xx_hal_dma_ex.h"

HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit(DMA_HandleTypeDef *hdma);

HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void              HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_CleanCallbacks(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)(DMA_HandleTypeDef *_hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);

HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);

#if defined (DMA_SxCR_CHSEL_3)
#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_CHANNEL_0) || \
                                 ((CHANNEL) == DMA_CHANNEL_1) || \
                                 ((CHANNEL) == DMA_CHANNEL_2) || \
                                 ((CHANNEL) == DMA_CHANNEL_3) || \
                                 ((CHANNEL) == DMA_CHANNEL_4) || \
                                 ((CHANNEL) == DMA_CHANNEL_5) || \
                                 ((CHANNEL) == DMA_CHANNEL_6) || \
                                 ((CHANNEL) == DMA_CHANNEL_7) || \
                                 ((CHANNEL) == DMA_CHANNEL_8) || \
                                 ((CHANNEL) == DMA_CHANNEL_9) || \
                                 ((CHANNEL) == DMA_CHANNEL_10)|| \
                                 ((CHANNEL) == DMA_CHANNEL_11)|| \
                                 ((CHANNEL) == DMA_CHANNEL_12)|| \
                                 ((CHANNEL) == DMA_CHANNEL_13)|| \
                                 ((CHANNEL) == DMA_CHANNEL_14)|| \
                                 ((CHANNEL) == DMA_CHANNEL_15))
#else
#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_CHANNEL_0) || \
                                 ((CHANNEL) == DMA_CHANNEL_1) || \
                                 ((CHANNEL) == DMA_CHANNEL_2) || \
                                 ((CHANNEL) == DMA_CHANNEL_3) || \
                                 ((CHANNEL) == DMA_CHANNEL_4) || \
                                 ((CHANNEL) == DMA_CHANNEL_5) || \
                                 ((CHANNEL) == DMA_CHANNEL_6) || \
                                 ((CHANNEL) == DMA_CHANNEL_7))
#endif

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY ) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH)  || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x01U) && ((SIZE) < 0x10000U))

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PINC_ENABLE) || \
                                            ((STATE) == DMA_PINC_DISABLE))

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MINC_ENABLE)  || \
                                        ((STATE) == DMA_MINC_DISABLE))

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PDATAALIGN_BYTE)     || \
                                           ((SIZE) == DMA_PDATAALIGN_HALFWORD) || \
                                           ((SIZE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MDATAALIGN_BYTE)     || \
                                       ((SIZE) == DMA_MDATAALIGN_HALFWORD) || \
                                       ((SIZE) == DMA_MDATAALIGN_WORD ))

#define IS_DMA_MODE(MODE) (((MODE) == DMA_NORMAL )  || \
                           ((MODE) == DMA_CIRCULAR) || \
                           ((MODE) == DMA_PFCTRL))

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW )   || \
                                   ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                   ((PRIORITY) == DMA_PRIORITY_HIGH)   || \
                                   ((PRIORITY) == DMA_PRIORITY_VERY_HIGH))

#define IS_DMA_FIFO_MODE_STATE(STATE) (((STATE) == DMA_FIFOMODE_DISABLE ) || \
                                       ((STATE) == DMA_FIFOMODE_ENABLE))

#define IS_DMA_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == DMA_FIFO_THRESHOLD_1QUARTERFULL ) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_HALFFULL)      || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_3QUARTERSFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_FULL))

#define IS_DMA_MEMORY_BURST(BURST) (((BURST) == DMA_MBURST_SINGLE) || \
                                    ((BURST) == DMA_MBURST_INC4)   || \
                                    ((BURST) == DMA_MBURST_INC8)   || \
                                    ((BURST) == DMA_MBURST_INC16))

#define IS_DMA_PERIPHERAL_BURST(BURST) (((BURST) == DMA_PBURST_SINGLE) || \
                                        ((BURST) == DMA_PBURST_INC4)   || \
                                        ((BURST) == DMA_PBURST_INC8)   || \
                                        ((BURST) == DMA_PBURST_INC16))

#ifdef __cplusplus
}
#endif

#endif
