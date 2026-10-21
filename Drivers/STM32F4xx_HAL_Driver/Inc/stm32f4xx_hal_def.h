#ifndef __STM32F4xx_HAL_DEF
#define __STM32F4xx_HAL_DEF

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

#if !defined(UNUSED)
#define UNUSED(X) (void)X
#endif

#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) == (BIT))
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)

#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0U)

#if (USE_RTOS == 1U)

  #error "USE_RTOS should be 0 in the current HAL release"
#else
  #define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)

  #define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = HAL_UNLOCKED;    \
                                    }while (0U)
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed  __attribute__((packed))
  #endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM)
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif
  #ifndef __ALIGN_END
    #define __ALIGN_END      __attribute__ ((aligned (4)))
  #endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM)
  #ifndef __ALIGN_END
#define __ALIGN_END    __attribute__ ((aligned (4)))
  #endif
  #ifndef __ALIGN_BEGIN
    #define __ALIGN_BEGIN
  #endif
#else
  #ifndef __ALIGN_END
    #define __ALIGN_END
  #endif
  #ifndef __ALIGN_BEGIN
    #if defined   (__CC_ARM)
#define __ALIGN_BEGIN    __align(4)
    #elif defined (__ICCARM__)
      #define __ALIGN_BEGIN
    #endif
  #endif
#endif

#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

#define __RAM_FUNC

#elif defined ( __ICCARM__ )

#define __RAM_FUNC __ramfunc

#elif defined   (  __GNUC__  )

#define __RAM_FUNC __attribute__((section(".RamFunc")))

#endif

#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )

#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )

#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifdef __cplusplus
}
#endif

#endif
