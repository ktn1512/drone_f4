#ifndef __STM32F4xx_LL_DMA_H
#define __STM32F4xx_LL_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#if defined (DMA1) || defined (DMA2)

static const uint8_t STREAM_OFFSET_TAB[] =
{
  (uint8_t)(DMA1_Stream0_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream1_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream2_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream3_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream4_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream5_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream6_BASE - DMA1_BASE),
  (uint8_t)(DMA1_Stream7_BASE - DMA1_BASE)
};

#if defined(USE_FULL_LL_DRIVER)

typedef struct
{
  uint32_t PeriphOrM2MSrcAddress;

  uint32_t MemoryOrM2MDstAddress;

  uint32_t Direction;

  uint32_t Mode;

  uint32_t PeriphOrM2MSrcIncMode;

  uint32_t MemoryOrM2MDstIncMode;

  uint32_t PeriphOrM2MSrcDataSize;

  uint32_t MemoryOrM2MDstDataSize;

  uint32_t NbData;

  uint32_t Channel;

  uint32_t Priority;

  uint32_t FIFOMode;

  uint32_t FIFOThreshold;

  uint32_t MemBurst;

  uint32_t PeriphBurst;

} LL_DMA_InitTypeDef;

#endif

#define LL_DMA_STREAM_0                   0x00000000U
#define LL_DMA_STREAM_1                   0x00000001U
#define LL_DMA_STREAM_2                   0x00000002U
#define LL_DMA_STREAM_3                   0x00000003U
#define LL_DMA_STREAM_4                   0x00000004U
#define LL_DMA_STREAM_5                   0x00000005U
#define LL_DMA_STREAM_6                   0x00000006U
#define LL_DMA_STREAM_7                   0x00000007U
#define LL_DMA_STREAM_ALL                 0xFFFF0000U

#define LL_DMA_DIRECTION_PERIPH_TO_MEMORY 0x00000000U
#define LL_DMA_DIRECTION_MEMORY_TO_PERIPH DMA_SxCR_DIR_0
#define LL_DMA_DIRECTION_MEMORY_TO_MEMORY DMA_SxCR_DIR_1

#define LL_DMA_MODE_NORMAL                0x00000000U
#define LL_DMA_MODE_CIRCULAR              DMA_SxCR_CIRC
#define LL_DMA_MODE_PFCTRL                DMA_SxCR_PFCTRL

#define LL_DMA_DOUBLEBUFFER_MODE_DISABLE  0x00000000U
#define LL_DMA_DOUBLEBUFFER_MODE_ENABLE   DMA_SxCR_DBM

#define LL_DMA_PERIPH_NOINCREMENT         0x00000000U
#define LL_DMA_PERIPH_INCREMENT           DMA_SxCR_PINC

#define LL_DMA_MEMORY_NOINCREMENT         0x00000000U
#define LL_DMA_MEMORY_INCREMENT           DMA_SxCR_MINC

#define LL_DMA_PDATAALIGN_BYTE            0x00000000U
#define LL_DMA_PDATAALIGN_HALFWORD        DMA_SxCR_PSIZE_0
#define LL_DMA_PDATAALIGN_WORD            DMA_SxCR_PSIZE_1

#define LL_DMA_MDATAALIGN_BYTE            0x00000000U
#define LL_DMA_MDATAALIGN_HALFWORD        DMA_SxCR_MSIZE_0
#define LL_DMA_MDATAALIGN_WORD            DMA_SxCR_MSIZE_1

#define LL_DMA_OFFSETSIZE_PSIZE           0x00000000U
#define LL_DMA_OFFSETSIZE_FIXEDTO4        DMA_SxCR_PINCOS

#define LL_DMA_PRIORITY_LOW               0x00000000U
#define LL_DMA_PRIORITY_MEDIUM            DMA_SxCR_PL_0
#define LL_DMA_PRIORITY_HIGH              DMA_SxCR_PL_1
#define LL_DMA_PRIORITY_VERYHIGH          DMA_SxCR_PL

#define LL_DMA_CHANNEL_0                  0x00000000U
#define LL_DMA_CHANNEL_1                  DMA_SxCR_CHSEL_0
#define LL_DMA_CHANNEL_2                  DMA_SxCR_CHSEL_1
#define LL_DMA_CHANNEL_3                  (DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1)
#define LL_DMA_CHANNEL_4                  DMA_SxCR_CHSEL_2
#define LL_DMA_CHANNEL_5                  (DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_0)
#define LL_DMA_CHANNEL_6                  (DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1)
#define LL_DMA_CHANNEL_7                  (DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0)
#if defined (DMA_SxCR_CHSEL_3)
#define LL_DMA_CHANNEL_8                  DMA_SxCR_CHSEL_3
#define LL_DMA_CHANNEL_9                  (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_0)
#define LL_DMA_CHANNEL_10                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_1)
#define LL_DMA_CHANNEL_11                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0)
#define LL_DMA_CHANNEL_12                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_2)
#define LL_DMA_CHANNEL_13                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_0)
#define LL_DMA_CHANNEL_14                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1)
#define LL_DMA_CHANNEL_15                 (DMA_SxCR_CHSEL_3 | DMA_SxCR_CHSEL_2 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_0)
#endif

#define LL_DMA_MBURST_SINGLE              0x00000000U
#define LL_DMA_MBURST_INC4                DMA_SxCR_MBURST_0
#define LL_DMA_MBURST_INC8                DMA_SxCR_MBURST_1
#define LL_DMA_MBURST_INC16               (DMA_SxCR_MBURST_0 | DMA_SxCR_MBURST_1)

#define LL_DMA_PBURST_SINGLE              0x00000000U
#define LL_DMA_PBURST_INC4                DMA_SxCR_PBURST_0
#define LL_DMA_PBURST_INC8                DMA_SxCR_PBURST_1
#define LL_DMA_PBURST_INC16               (DMA_SxCR_PBURST_0 | DMA_SxCR_PBURST_1)

#define LL_DMA_FIFOMODE_DISABLE           0x00000000U
#define LL_DMA_FIFOMODE_ENABLE            DMA_SxFCR_DMDIS

#define LL_DMA_FIFOSTATUS_0_25            0x00000000U
#define LL_DMA_FIFOSTATUS_25_50           DMA_SxFCR_FS_0
#define LL_DMA_FIFOSTATUS_50_75           DMA_SxFCR_FS_1
#define LL_DMA_FIFOSTATUS_75_100          (DMA_SxFCR_FS_1 | DMA_SxFCR_FS_0)
#define LL_DMA_FIFOSTATUS_EMPTY           DMA_SxFCR_FS_2
#define LL_DMA_FIFOSTATUS_FULL            (DMA_SxFCR_FS_2 | DMA_SxFCR_FS_0)

#define LL_DMA_FIFOTHRESHOLD_1_4          0x00000000U
#define LL_DMA_FIFOTHRESHOLD_1_2          DMA_SxFCR_FTH_0
#define LL_DMA_FIFOTHRESHOLD_3_4          DMA_SxFCR_FTH_1
#define LL_DMA_FIFOTHRESHOLD_FULL         DMA_SxFCR_FTH

#define LL_DMA_CURRENTTARGETMEM0          0x00000000U
#define LL_DMA_CURRENTTARGETMEM1          DMA_SxCR_CT

#define LL_DMA_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

#define LL_DMA_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

#define __LL_DMA_GET_INSTANCE(__STREAM_INSTANCE__)   \
(((uint32_t)(__STREAM_INSTANCE__) > ((uint32_t)DMA1_Stream7)) ?  DMA2 : DMA1)

#define __LL_DMA_GET_STREAM(__STREAM_INSTANCE__)   \
(((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream0)) ? LL_DMA_STREAM_0 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream0)) ? LL_DMA_STREAM_0 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream1)) ? LL_DMA_STREAM_1 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream1)) ? LL_DMA_STREAM_1 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream2)) ? LL_DMA_STREAM_2 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream2)) ? LL_DMA_STREAM_2 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream3)) ? LL_DMA_STREAM_3 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream3)) ? LL_DMA_STREAM_3 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream4)) ? LL_DMA_STREAM_4 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream4)) ? LL_DMA_STREAM_4 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream5)) ? LL_DMA_STREAM_5 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream5)) ? LL_DMA_STREAM_5 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA1_Stream6)) ? LL_DMA_STREAM_6 : \
 ((uint32_t)(__STREAM_INSTANCE__) == ((uint32_t)DMA2_Stream6)) ? LL_DMA_STREAM_6 : \
 LL_DMA_STREAM_7)

#define __LL_DMA_GET_STREAM_INSTANCE(__DMA_INSTANCE__, __STREAM__)   \
((((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_0))) ? DMA1_Stream0 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_0))) ? DMA2_Stream0 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_1))) ? DMA1_Stream1 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_1))) ? DMA2_Stream1 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_2))) ? DMA1_Stream2 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_2))) ? DMA2_Stream2 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_3))) ? DMA1_Stream3 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_3))) ? DMA2_Stream3 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_4))) ? DMA1_Stream4 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_4))) ? DMA2_Stream4 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_5))) ? DMA1_Stream5 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_5))) ? DMA2_Stream5 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_6))) ? DMA1_Stream6 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA2)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_6))) ? DMA2_Stream6 : \
 (((uint32_t)(__DMA_INSTANCE__) == ((uint32_t)DMA1)) && ((uint32_t)(__STREAM__) == ((uint32_t)LL_DMA_STREAM_7))) ? DMA1_Stream7 : \
 DMA2_Stream7)

__STATIC_INLINE void LL_DMA_EnableStream(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_EN);
}

__STATIC_INLINE void LL_DMA_DisableStream(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_EN);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledStream(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_EN) == (DMA_SxCR_EN));
}

__STATIC_INLINE void LL_DMA_ConfigTransfer(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Configuration)
{
  MODIFY_REG(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR,
             DMA_SxCR_DIR | DMA_SxCR_CIRC | DMA_SxCR_PINC | DMA_SxCR_MINC | DMA_SxCR_PSIZE | DMA_SxCR_MSIZE | DMA_SxCR_PL | DMA_SxCR_PFCTRL,
             Configuration);
}

__STATIC_INLINE void LL_DMA_SetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t  Direction)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DIR, Direction);
}

__STATIC_INLINE uint32_t LL_DMA_GetDataTransferDirection(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DIR));
}

__STATIC_INLINE void LL_DMA_SetMode(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Mode)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CIRC | DMA_SxCR_PFCTRL, Mode);
}

__STATIC_INLINE uint32_t LL_DMA_GetMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CIRC | DMA_SxCR_PFCTRL));
}

__STATIC_INLINE void LL_DMA_SetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t IncrementMode)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PINC, IncrementMode);
}

__STATIC_INLINE uint32_t LL_DMA_GetPeriphIncMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PINC));
}

__STATIC_INLINE void LL_DMA_SetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t IncrementMode)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MINC, IncrementMode);
}

__STATIC_INLINE uint32_t LL_DMA_GetMemoryIncMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MINC));
}

__STATIC_INLINE void LL_DMA_SetPeriphSize(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t  Size)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PSIZE, Size);
}

__STATIC_INLINE uint32_t LL_DMA_GetPeriphSize(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PSIZE));
}

__STATIC_INLINE void LL_DMA_SetMemorySize(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t  Size)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MSIZE, Size);
}

__STATIC_INLINE uint32_t LL_DMA_GetMemorySize(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MSIZE));
}

__STATIC_INLINE void LL_DMA_SetIncOffsetSize(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t OffsetSize)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PINCOS, OffsetSize);
}

__STATIC_INLINE uint32_t LL_DMA_GetIncOffsetSize(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PINCOS));
}

__STATIC_INLINE void LL_DMA_SetStreamPriorityLevel(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t  Priority)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PL, Priority);
}

__STATIC_INLINE uint32_t LL_DMA_GetStreamPriorityLevel(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PL));
}

__STATIC_INLINE void LL_DMA_SetDataLength(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t NbData)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->NDTR, DMA_SxNDT, NbData);
}

__STATIC_INLINE uint32_t LL_DMA_GetDataLength(DMA_TypeDef* DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->NDTR, DMA_SxNDT));
}

__STATIC_INLINE void LL_DMA_SetChannelSelection(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Channel)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CHSEL, Channel);
}

__STATIC_INLINE uint32_t LL_DMA_GetChannelSelection(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CHSEL));
}

__STATIC_INLINE void LL_DMA_SetMemoryBurstxfer(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Mburst)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MBURST, Mburst);
}

__STATIC_INLINE uint32_t LL_DMA_GetMemoryBurstxfer(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_MBURST));
}

__STATIC_INLINE void LL_DMA_SetPeriphBurstxfer(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Pburst)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PBURST, Pburst);
}

__STATIC_INLINE uint32_t LL_DMA_GetPeriphBurstxfer(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_PBURST));
}

__STATIC_INLINE void LL_DMA_SetCurrentTargetMem(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t CurrentMemory)
{
   MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CT, CurrentMemory);
}

__STATIC_INLINE uint32_t LL_DMA_GetCurrentTargetMem(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_CT));
}

__STATIC_INLINE void LL_DMA_EnableDoubleBufferMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DBM);
}

__STATIC_INLINE void LL_DMA_DisableDoubleBufferMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DBM);
}

__STATIC_INLINE uint32_t LL_DMA_GetFIFOStatus(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FS));
}

__STATIC_INLINE void LL_DMA_DisableFifoMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_DMDIS);
}

__STATIC_INLINE void LL_DMA_EnableFifoMode(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_DMDIS);
}

__STATIC_INLINE void LL_DMA_SetFIFOThreshold(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Threshold)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FTH, Threshold);
}

__STATIC_INLINE uint32_t LL_DMA_GetFIFOThreshold(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FTH));
}

__STATIC_INLINE void LL_DMA_ConfigFifo(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t FifoMode, uint32_t FifoThreshold)
{
  MODIFY_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FTH|DMA_SxFCR_DMDIS, FifoMode|FifoThreshold);
}

__STATIC_INLINE void LL_DMA_ConfigAddresses(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t SrcAddress, uint32_t DstAddress, uint32_t Direction)
{

  if (Direction == LL_DMA_DIRECTION_MEMORY_TO_PERIPH)
  {
    WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR, SrcAddress);
    WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR, DstAddress);
  }

  else
  {
    WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR, SrcAddress);
    WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR, DstAddress);
  }
}

__STATIC_INLINE void LL_DMA_SetMemoryAddress(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t MemoryAddress)
{
  WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR, MemoryAddress);
}

__STATIC_INLINE void LL_DMA_SetPeriphAddress(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t PeriphAddress)
{
  WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR, PeriphAddress);
}

__STATIC_INLINE uint32_t LL_DMA_GetMemoryAddress(DMA_TypeDef* DMAx, uint32_t Stream)
{
  return (READ_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR));
}

__STATIC_INLINE uint32_t LL_DMA_GetPeriphAddress(DMA_TypeDef* DMAx, uint32_t Stream)
{
  return (READ_REG(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR));
}

__STATIC_INLINE void LL_DMA_SetM2MSrcAddress(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t MemoryAddress)
{
  WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR, MemoryAddress);
}

__STATIC_INLINE void LL_DMA_SetM2MDstAddress(DMA_TypeDef* DMAx, uint32_t Stream, uint32_t MemoryAddress)
  {
    WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR, MemoryAddress);
  }

__STATIC_INLINE uint32_t LL_DMA_GetM2MSrcAddress(DMA_TypeDef* DMAx, uint32_t Stream)
  {
   return (READ_REG(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->PAR));
  }

__STATIC_INLINE uint32_t LL_DMA_GetM2MDstAddress(DMA_TypeDef* DMAx, uint32_t Stream)
{
 return (READ_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M0AR));
}

__STATIC_INLINE void LL_DMA_SetMemory1Address(DMA_TypeDef *DMAx, uint32_t Stream, uint32_t Address)
{
  WRITE_REG(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M1AR, Address);
}

__STATIC_INLINE uint32_t LL_DMA_GetMemory1Address(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->M1AR);
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT0(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_HTIF0)==(DMA_LISR_HTIF0));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_HTIF1)==(DMA_LISR_HTIF1));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_HTIF2)==(DMA_LISR_HTIF2));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_HTIF3)==(DMA_LISR_HTIF3));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT4(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_HTIF4)==(DMA_HISR_HTIF4));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT5(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_HTIF5)==(DMA_HISR_HTIF5));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT6(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_HTIF6)==(DMA_HISR_HTIF6));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_HT7(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_HTIF7)==(DMA_HISR_HTIF7));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC0(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TCIF0)==(DMA_LISR_TCIF0));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TCIF1)==(DMA_LISR_TCIF1));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TCIF2)==(DMA_LISR_TCIF2));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TCIF3)==(DMA_LISR_TCIF3));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC4(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TCIF4)==(DMA_HISR_TCIF4));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC5(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TCIF5)==(DMA_HISR_TCIF5));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC6(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TCIF6)==(DMA_HISR_TCIF6));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TC7(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TCIF7)==(DMA_HISR_TCIF7));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE0(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TEIF0)==(DMA_LISR_TEIF0));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TEIF1)==(DMA_LISR_TEIF1));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TEIF2)==(DMA_LISR_TEIF2));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_TEIF3)==(DMA_LISR_TEIF3));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE4(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TEIF4)==(DMA_HISR_TEIF4));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE5(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TEIF5)==(DMA_HISR_TEIF5));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE6(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TEIF6)==(DMA_HISR_TEIF6));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_TE7(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_TEIF7)==(DMA_HISR_TEIF7));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME0(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_DMEIF0)==(DMA_LISR_DMEIF0));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_DMEIF1)==(DMA_LISR_DMEIF1));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_DMEIF2)==(DMA_LISR_DMEIF2));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_DMEIF3)==(DMA_LISR_DMEIF3));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME4(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_DMEIF4)==(DMA_HISR_DMEIF4));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME5(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_DMEIF5)==(DMA_HISR_DMEIF5));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME6(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_DMEIF6)==(DMA_HISR_DMEIF6));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_DME7(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_DMEIF7)==(DMA_HISR_DMEIF7));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE0(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_FEIF0)==(DMA_LISR_FEIF0));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE1(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_FEIF1)==(DMA_LISR_FEIF1));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE2(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_FEIF2)==(DMA_LISR_FEIF2));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE3(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->LISR ,DMA_LISR_FEIF3)==(DMA_LISR_FEIF3));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE4(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_FEIF4)==(DMA_HISR_FEIF4));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE5(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_FEIF5)==(DMA_HISR_FEIF5));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE6(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_FEIF6)==(DMA_HISR_FEIF6));
}

__STATIC_INLINE uint32_t LL_DMA_IsActiveFlag_FE7(DMA_TypeDef *DMAx)
{
  return (READ_BIT(DMAx->HISR ,DMA_HISR_FEIF7)==(DMA_HISR_FEIF7));
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT0(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CHTIF0);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CHTIF1);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CHTIF2);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CHTIF3);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT4(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CHTIF4);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT5(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CHTIF5);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT6(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CHTIF6);
}

__STATIC_INLINE void LL_DMA_ClearFlag_HT7(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CHTIF7);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC0(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTCIF0);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTCIF1);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTCIF2);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTCIF3);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC4(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTCIF4);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC5(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTCIF5);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC6(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTCIF6);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TC7(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTCIF7);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE0(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTEIF0);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTEIF1);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTEIF2);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CTEIF3);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE4(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTEIF4);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE5(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTEIF5);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE6(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTEIF6);
}

__STATIC_INLINE void LL_DMA_ClearFlag_TE7(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CTEIF7);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME0(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CDMEIF0);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CDMEIF1);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CDMEIF2);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CDMEIF3);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME4(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CDMEIF4);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME5(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CDMEIF5);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME6(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CDMEIF6);
}

__STATIC_INLINE void LL_DMA_ClearFlag_DME7(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CDMEIF7);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE0(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CFEIF0);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE1(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CFEIF1);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE2(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CFEIF2);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE3(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->LIFCR , DMA_LIFCR_CFEIF3);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE4(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CFEIF4);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE5(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CFEIF5);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE6(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CFEIF6);
}

__STATIC_INLINE void LL_DMA_ClearFlag_FE7(DMA_TypeDef *DMAx)
{
  WRITE_REG(DMAx->HIFCR , DMA_HIFCR_CFEIF7);
}

__STATIC_INLINE void LL_DMA_EnableIT_HT(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_HTIE);
}

__STATIC_INLINE void LL_DMA_EnableIT_TE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TEIE);
}

__STATIC_INLINE void LL_DMA_EnableIT_TC(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TCIE);
}

__STATIC_INLINE void LL_DMA_EnableIT_DME(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DMEIE);
}

__STATIC_INLINE void LL_DMA_EnableIT_FE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  SET_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FEIE);
}

__STATIC_INLINE void LL_DMA_DisableIT_HT(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_HTIE);
}

__STATIC_INLINE void LL_DMA_DisableIT_TE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TEIE);
}

__STATIC_INLINE void LL_DMA_DisableIT_TC(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TCIE);
}

__STATIC_INLINE void LL_DMA_DisableIT_DME(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DMEIE);
}

__STATIC_INLINE void LL_DMA_DisableIT_FE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  CLEAR_BIT(((DMA_Stream_TypeDef *)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FEIE);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_HT(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_HTIE) == DMA_SxCR_HTIE);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TEIE) == DMA_SxCR_TEIE);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_TC(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_TCIE) == DMA_SxCR_TCIE);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_DME(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->CR, DMA_SxCR_DMEIE) == DMA_SxCR_DMEIE);
}

__STATIC_INLINE uint32_t LL_DMA_IsEnabledIT_FE(DMA_TypeDef *DMAx, uint32_t Stream)
{
  return (READ_BIT(((DMA_Stream_TypeDef*)((uint32_t)((uint32_t)DMAx + STREAM_OFFSET_TAB[Stream])))->FCR, DMA_SxFCR_FEIE) == DMA_SxFCR_FEIE);
}

#if defined(USE_FULL_LL_DRIVER)

uint32_t LL_DMA_Init(DMA_TypeDef *DMAx, uint32_t Stream, LL_DMA_InitTypeDef *DMA_InitStruct);
uint32_t LL_DMA_DeInit(DMA_TypeDef *DMAx, uint32_t Stream);
void LL_DMA_StructInit(LL_DMA_InitTypeDef *DMA_InitStruct);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
