#ifndef __STM32F4xx_HAL_FLASH_H
#define __STM32F4xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef enum
{
  FLASH_PROC_NONE = 0U,
  FLASH_PROC_SECTERASE,
  FLASH_PROC_MASSERASE,
  FLASH_PROC_PROGRAM
} FLASH_ProcedureTypeDef;

typedef struct
{
  __IO FLASH_ProcedureTypeDef ProcedureOnGoing;

  __IO uint32_t               NbSectorsToErase;

  __IO uint8_t                VoltageForErase;

  __IO uint32_t               Sector;

  __IO uint32_t               Bank;

  __IO uint32_t               Address;

  HAL_LockTypeDef             Lock;

  __IO uint32_t               ErrorCode;

} FLASH_ProcessTypeDef;

#define HAL_FLASH_ERROR_NONE         0x00000000U
#define HAL_FLASH_ERROR_RD           0x00000001U
#define HAL_FLASH_ERROR_PGS          0x00000002U
#define HAL_FLASH_ERROR_PGP          0x00000004U
#define HAL_FLASH_ERROR_PGA          0x00000008U
#define HAL_FLASH_ERROR_WRP          0x00000010U
#define HAL_FLASH_ERROR_OPERATION    0x00000020U

#define FLASH_TYPEPROGRAM_BYTE        0x00000000U
#define FLASH_TYPEPROGRAM_HALFWORD    0x00000001U
#define FLASH_TYPEPROGRAM_WORD        0x00000002U
#define FLASH_TYPEPROGRAM_DOUBLEWORD  0x00000003U

#define FLASH_FLAG_EOP                 FLASH_SR_EOP
#define FLASH_FLAG_OPERR               FLASH_SR_SOP
#define FLASH_FLAG_WRPERR              FLASH_SR_WRPERR
#define FLASH_FLAG_PGAERR              FLASH_SR_PGAERR
#define FLASH_FLAG_PGPERR              FLASH_SR_PGPERR
#define FLASH_FLAG_PGSERR              FLASH_SR_PGSERR
#if defined(FLASH_SR_RDERR)
#define FLASH_FLAG_RDERR               FLASH_SR_RDERR
#endif
#define FLASH_FLAG_BSY                 FLASH_SR_BSY

#define FLASH_IT_EOP                   FLASH_CR_EOPIE
#define FLASH_IT_ERR                   0x02000000U

#define FLASH_PSIZE_BYTE           0x00000000U
#define FLASH_PSIZE_HALF_WORD      0x00000100U
#define FLASH_PSIZE_WORD           0x00000200U
#define FLASH_PSIZE_DOUBLE_WORD    0x00000300U
#define CR_PSIZE_MASK              0xFFFFFCFFU

#define RDP_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               0x45670123U
#define FLASH_KEY2               0xCDEF89ABU
#define FLASH_OPT_KEY1           0x08192A3BU
#define FLASH_OPT_KEY2           0x4C5D6E7FU

#define __HAL_FLASH_SET_LATENCY(__LATENCY__) (*(__IO uint8_t *)ACR_BYTE0_ADDRESS = (uint8_t)(__LATENCY__))

#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))

#define __HAL_FLASH_PREFETCH_BUFFER_ENABLE()  (FLASH->ACR |= FLASH_ACR_PRFTEN)

#define __HAL_FLASH_PREFETCH_BUFFER_DISABLE()   (FLASH->ACR &= (~FLASH_ACR_PRFTEN))

#define __HAL_FLASH_INSTRUCTION_CACHE_ENABLE()  (FLASH->ACR |= FLASH_ACR_ICEN)

#define __HAL_FLASH_INSTRUCTION_CACHE_DISABLE()   (FLASH->ACR &= (~FLASH_ACR_ICEN))

#define __HAL_FLASH_DATA_CACHE_ENABLE()  (FLASH->ACR |= FLASH_ACR_DCEN)

#define __HAL_FLASH_DATA_CACHE_DISABLE()   (FLASH->ACR &= (~FLASH_ACR_DCEN))

#define __HAL_FLASH_INSTRUCTION_CACHE_RESET() do {FLASH->ACR |= FLASH_ACR_ICRST;  \
                                                   FLASH->ACR &= ~FLASH_ACR_ICRST; \
                                                 }while(0U)

#define __HAL_FLASH_DATA_CACHE_RESET() do {FLASH->ACR |= FLASH_ACR_DCRST;  \
                                            FLASH->ACR &= ~FLASH_ACR_DCRST; \
                                          }while(0U)

#define __HAL_FLASH_ENABLE_IT(__INTERRUPT__)  (FLASH->CR |= (__INTERRUPT__))

#define __HAL_FLASH_DISABLE_IT(__INTERRUPT__)  (FLASH->CR &= ~(uint32_t)(__INTERRUPT__))

#define __HAL_FLASH_GET_FLAG(__FLAG__)   ((FLASH->SR & (__FLAG__)))

#define __HAL_FLASH_CLEAR_FLAG(__FLAG__)   (FLASH->SR = (__FLAG__))

#include "stm32f4xx_hal_flash_ex.h"
#include "stm32f4xx_hal_flash_ramfunc.h"

HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);

void HAL_FLASH_IRQHandler(void);

void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);

HAL_StatusTypeDef HAL_FLASH_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_Lock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef HAL_FLASH_OB_Lock(void);

HAL_StatusTypeDef HAL_FLASH_OB_Launch(void);

uint32_t HAL_FLASH_GetError(void);
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);

#define ACR_BYTE0_ADDRESS           0x40023C00U

#define OPTCR_BYTE0_ADDRESS         0x40023C14U

#define OPTCR_BYTE1_ADDRESS         0x40023C15U

#define OPTCR_BYTE2_ADDRESS         0x40023C16U

#define OPTCR_BYTE3_ADDRESS         0x40023C17U

#define IS_FLASH_TYPEPROGRAM(VALUE)(((VALUE) == FLASH_TYPEPROGRAM_BYTE) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_HALFWORD) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_WORD) || \
                                    ((VALUE) == FLASH_TYPEPROGRAM_DOUBLEWORD))

#ifdef __cplusplus
}
#endif

#endif
