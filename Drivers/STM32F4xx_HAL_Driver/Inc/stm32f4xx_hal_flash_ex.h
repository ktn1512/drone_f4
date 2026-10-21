#ifndef __STM32F4xx_HAL_FLASH_EX_H
#define __STM32F4xx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal_def.h"

typedef struct
{
  uint32_t TypeErase;

  uint32_t Banks;

  uint32_t Sector;

  uint32_t NbSectors;

  uint32_t VoltageRange;

} FLASH_EraseInitTypeDef;

typedef struct
{
  uint32_t OptionType;

  uint32_t WRPState;

  uint32_t WRPSector;

  uint32_t Banks;

  uint32_t RDPLevel;

  uint32_t BORLevel;

  uint8_t  USERConfig;

} FLASH_OBProgramInitTypeDef;

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
typedef struct
{
  uint32_t OptionType;

  uint32_t PCROPState;

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
  uint16_t Sectors;
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
  uint32_t Banks;

  uint16_t SectorsBank1;

  uint16_t SectorsBank2;

  uint8_t BootConfig;

#endif
} FLASH_AdvOBProgramInitTypeDef;
#endif

#define FLASH_TYPEERASE_SECTORS         0x00000000U
#define FLASH_TYPEERASE_MASSERASE       0x00000001U

#define FLASH_VOLTAGE_RANGE_1        0x00000000U
#define FLASH_VOLTAGE_RANGE_2        0x00000001U
#define FLASH_VOLTAGE_RANGE_3        0x00000002U
#define FLASH_VOLTAGE_RANGE_4        0x00000003U

#define OB_WRPSTATE_DISABLE       0x00000000U
#define OB_WRPSTATE_ENABLE        0x00000001U

#define OPTIONBYTE_WRP        0x00000001U
#define OPTIONBYTE_RDP        0x00000002U
#define OPTIONBYTE_USER       0x00000004U
#define OPTIONBYTE_BOR        0x00000008U

#define OB_RDP_LEVEL_0   ((uint8_t)0xAA)
#define OB_RDP_LEVEL_1   ((uint8_t)0x55)
#define OB_RDP_LEVEL_2   ((uint8_t)0xCC)

#define OB_IWDG_SW                     ((uint8_t)0x20)
#define OB_IWDG_HW                     ((uint8_t)0x00)

#define OB_STOP_NO_RST                 ((uint8_t)0x40)
#define OB_STOP_RST                    ((uint8_t)0x00)

#define OB_STDBY_NO_RST                ((uint8_t)0x80)
#define OB_STDBY_RST                   ((uint8_t)0x00)

#define OB_BOR_LEVEL3          ((uint8_t)0x00)
#define OB_BOR_LEVEL2          ((uint8_t)0x04)
#define OB_BOR_LEVEL1          ((uint8_t)0x08)
#define OB_BOR_OFF             ((uint8_t)0x0C)

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define OB_PCROP_STATE_DISABLE       0x00000000U
#define OB_PCROP_STATE_ENABLE        0x00000001U

#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OPTIONBYTE_PCROP        0x00000001U
#define OPTIONBYTE_BOOTCONFIG   0x00000002U
#endif

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define OPTIONBYTE_PCROP        0x00000001U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS
#define FLASH_LATENCY_8                FLASH_ACR_LATENCY_8WS
#define FLASH_LATENCY_9                FLASH_ACR_LATENCY_9WS
#define FLASH_LATENCY_10               FLASH_ACR_LATENCY_10WS
#define FLASH_LATENCY_11               FLASH_ACR_LATENCY_11WS
#define FLASH_LATENCY_12               FLASH_ACR_LATENCY_12WS
#define FLASH_LATENCY_13               FLASH_ACR_LATENCY_13WS
#define FLASH_LATENCY_14               FLASH_ACR_LATENCY_14WS
#define FLASH_LATENCY_15               FLASH_ACR_LATENCY_15WS
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)

#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_BANK_1     1U
#define FLASH_BANK_2     2U
#define FLASH_BANK_BOTH  ((uint32_t)FLASH_BANK_1 | FLASH_BANK_2)
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define FLASH_BANK_1     1U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_MER_BIT     (FLASH_CR_MER1 | FLASH_CR_MER2)
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define FLASH_MER_BIT     (FLASH_CR_MER)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#define FLASH_SECTOR_5     5U
#define FLASH_SECTOR_6     6U
#define FLASH_SECTOR_7     7U
#define FLASH_SECTOR_8     8U
#define FLASH_SECTOR_9     9U
#define FLASH_SECTOR_10    10U
#define FLASH_SECTOR_11    11U
#define FLASH_SECTOR_12    12U
#define FLASH_SECTOR_13    13U
#define FLASH_SECTOR_14    14U
#define FLASH_SECTOR_15    15U
#define FLASH_SECTOR_16    16U
#define FLASH_SECTOR_17    17U
#define FLASH_SECTOR_18    18U
#define FLASH_SECTOR_19    19U
#define FLASH_SECTOR_20    20U
#define FLASH_SECTOR_21    21U
#define FLASH_SECTOR_22    22U
#define FLASH_SECTOR_23    23U
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#define FLASH_SECTOR_5     5U
#define FLASH_SECTOR_6     6U
#define FLASH_SECTOR_7     7U
#define FLASH_SECTOR_8     8U
#define FLASH_SECTOR_9     9U
#define FLASH_SECTOR_10    10U
#define FLASH_SECTOR_11    11U
#define FLASH_SECTOR_12    12U
#define FLASH_SECTOR_13    13U
#define FLASH_SECTOR_14    14U
#define FLASH_SECTOR_15    15U
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#define FLASH_SECTOR_5     5U
#define FLASH_SECTOR_6     6U
#define FLASH_SECTOR_7     7U
#define FLASH_SECTOR_8     8U
#define FLASH_SECTOR_9     9U
#define FLASH_SECTOR_10    10U
#define FLASH_SECTOR_11    11U
#endif

#if defined(STM32F401xC)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#define FLASH_SECTOR_5     5U
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define FLASH_SECTOR_0     0U
#define FLASH_SECTOR_1     1U
#define FLASH_SECTOR_2     2U
#define FLASH_SECTOR_3     3U
#define FLASH_SECTOR_4     4U
#define FLASH_SECTOR_5     5U
#define FLASH_SECTOR_6     6U
#define FLASH_SECTOR_7     7U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_5       0x00000020U
#define OB_WRP_SECTOR_6       0x00000040U
#define OB_WRP_SECTOR_7       0x00000080U
#define OB_WRP_SECTOR_8       0x00000100U
#define OB_WRP_SECTOR_9       0x00000200U
#define OB_WRP_SECTOR_10      0x00000400U
#define OB_WRP_SECTOR_11      0x00000800U
#define OB_WRP_SECTOR_12      0x00000001U << 12U
#define OB_WRP_SECTOR_13      0x00000002U << 12U
#define OB_WRP_SECTOR_14      0x00000004U << 12U
#define OB_WRP_SECTOR_15      0x00000008U << 12U
#define OB_WRP_SECTOR_16      0x00000010U << 12U
#define OB_WRP_SECTOR_17      0x00000020U << 12U
#define OB_WRP_SECTOR_18      0x00000040U << 12U
#define OB_WRP_SECTOR_19      0x00000080U << 12U
#define OB_WRP_SECTOR_20      0x00000100U << 12U
#define OB_WRP_SECTOR_21      0x00000200U << 12U
#define OB_WRP_SECTOR_22      0x00000400U << 12U
#define OB_WRP_SECTOR_23      0x00000800U << 12U
#define OB_WRP_SECTOR_All     0x00000FFFU << 12U
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_5       0x00000020U
#define OB_WRP_SECTOR_6       0x00000040U
#define OB_WRP_SECTOR_7       0x00000080U
#define OB_WRP_SECTOR_8       0x00000100U
#define OB_WRP_SECTOR_9       0x00000200U
#define OB_WRP_SECTOR_10      0x00000400U
#define OB_WRP_SECTOR_11      0x00000800U
#define OB_WRP_SECTOR_12      0x00001000U
#define OB_WRP_SECTOR_13      0x00002000U
#define OB_WRP_SECTOR_14      0x00004000U
#define OB_WRP_SECTOR_15      0x00004000U
#define OB_WRP_SECTOR_All     0x00007FFFU
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_5       0x00000020U
#define OB_WRP_SECTOR_6       0x00000040U
#define OB_WRP_SECTOR_7       0x00000080U
#define OB_WRP_SECTOR_8       0x00000100U
#define OB_WRP_SECTOR_9       0x00000200U
#define OB_WRP_SECTOR_10      0x00000400U
#define OB_WRP_SECTOR_11      0x00000800U
#define OB_WRP_SECTOR_All     0x00000FFFU
#endif

#if defined(STM32F401xC)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_5       0x00000020U
#define OB_WRP_SECTOR_All     0x00000FFFU
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_All     0x00000FFFU
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define OB_WRP_SECTOR_0       0x00000001U
#define OB_WRP_SECTOR_1       0x00000002U
#define OB_WRP_SECTOR_2       0x00000004U
#define OB_WRP_SECTOR_3       0x00000008U
#define OB_WRP_SECTOR_4       0x00000010U
#define OB_WRP_SECTOR_5       0x00000020U
#define OB_WRP_SECTOR_6       0x00000040U
#define OB_WRP_SECTOR_7       0x00000080U
#define OB_WRP_SECTOR_All     0x00000FFFU
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_PCROP_SECTOR_0        0x00000001U
#define OB_PCROP_SECTOR_1        0x00000002U
#define OB_PCROP_SECTOR_2        0x00000004U
#define OB_PCROP_SECTOR_3        0x00000008U
#define OB_PCROP_SECTOR_4        0x00000010U
#define OB_PCROP_SECTOR_5        0x00000020U
#define OB_PCROP_SECTOR_6        0x00000040U
#define OB_PCROP_SECTOR_7        0x00000080U
#define OB_PCROP_SECTOR_8        0x00000100U
#define OB_PCROP_SECTOR_9        0x00000200U
#define OB_PCROP_SECTOR_10       0x00000400U
#define OB_PCROP_SECTOR_11       0x00000800U
#define OB_PCROP_SECTOR_12       0x00000001U
#define OB_PCROP_SECTOR_13       0x00000002U
#define OB_PCROP_SECTOR_14       0x00000004U
#define OB_PCROP_SECTOR_15       0x00000008U
#define OB_PCROP_SECTOR_16       0x00000010U
#define OB_PCROP_SECTOR_17       0x00000020U
#define OB_PCROP_SECTOR_18       0x00000040U
#define OB_PCROP_SECTOR_19       0x00000080U
#define OB_PCROP_SECTOR_20       0x00000100U
#define OB_PCROP_SECTOR_21       0x00000200U
#define OB_PCROP_SECTOR_22       0x00000400U
#define OB_PCROP_SECTOR_23       0x00000800U
#define OB_PCROP_SECTOR_All      0x00000FFFU
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define OB_PCROP_SECTOR_0        0x00000001U
#define OB_PCROP_SECTOR_1        0x00000002U
#define OB_PCROP_SECTOR_2        0x00000004U
#define OB_PCROP_SECTOR_3        0x00000008U
#define OB_PCROP_SECTOR_4        0x00000010U
#define OB_PCROP_SECTOR_5        0x00000020U
#define OB_PCROP_SECTOR_6        0x00000040U
#define OB_PCROP_SECTOR_7        0x00000080U
#define OB_PCROP_SECTOR_8        0x00000100U
#define OB_PCROP_SECTOR_9        0x00000200U
#define OB_PCROP_SECTOR_10       0x00000400U
#define OB_PCROP_SECTOR_11       0x00000800U
#define OB_PCROP_SECTOR_12       0x00001000U
#define OB_PCROP_SECTOR_13       0x00002000U
#define OB_PCROP_SECTOR_14       0x00004000U
#define OB_PCROP_SECTOR_15       0x00004000U
#define OB_PCROP_SECTOR_All      0x00007FFFU
#endif

#if defined(STM32F401xC)
#define OB_PCROP_SECTOR_0        0x00000001U
#define OB_PCROP_SECTOR_1        0x00000002U
#define OB_PCROP_SECTOR_2        0x00000004U
#define OB_PCROP_SECTOR_3        0x00000008U
#define OB_PCROP_SECTOR_4        0x00000010U
#define OB_PCROP_SECTOR_5        0x00000020U
#define OB_PCROP_SECTOR_All      0x00000FFFU
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define OB_PCROP_SECTOR_0        0x00000001U
#define OB_PCROP_SECTOR_1        0x00000002U
#define OB_PCROP_SECTOR_2        0x00000004U
#define OB_PCROP_SECTOR_3        0x00000008U
#define OB_PCROP_SECTOR_4        0x00000010U
#define OB_PCROP_SECTOR_All      0x00000FFFU
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define OB_PCROP_SECTOR_0        0x00000001U
#define OB_PCROP_SECTOR_1        0x00000002U
#define OB_PCROP_SECTOR_2        0x00000004U
#define OB_PCROP_SECTOR_3        0x00000008U
#define OB_PCROP_SECTOR_4        0x00000010U
#define OB_PCROP_SECTOR_5        0x00000020U
#define OB_PCROP_SECTOR_6        0x00000040U
#define OB_PCROP_SECTOR_7        0x00000080U
#define OB_PCROP_SECTOR_All      0x00000FFFU
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define OB_DUAL_BOOT_ENABLE   ((uint8_t)0x10)
#define OB_DUAL_BOOT_DISABLE  ((uint8_t)0x00)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define OB_PCROP_DESELECTED     ((uint8_t)0x00)
#define OB_PCROP_SELECTED       ((uint8_t)0x80)
#endif

HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
HAL_StatusTypeDef HAL_FLASHEx_AdvOBProgram(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
void              HAL_FLASHEx_AdvOBGetConfig(FLASH_AdvOBProgramInitTypeDef *pAdvOBInit);
HAL_StatusTypeDef HAL_FLASHEx_OB_SelectPCROP(void);
HAL_StatusTypeDef HAL_FLASHEx_OB_DeSelectPCROP(void);
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
uint16_t          HAL_FLASHEx_OB_GetBank2WRP(void);
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define FLASH_SECTOR_TOTAL  24U
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define FLASH_SECTOR_TOTAL  16U
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define FLASH_SECTOR_TOTAL  12U
#endif

#if defined(STM32F401xC)
#define FLASH_SECTOR_TOTAL  6U
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define FLASH_SECTOR_TOTAL  5U
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define FLASH_SECTOR_TOTAL  8U
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define OPTCR1_BYTE2_ADDRESS         0x40023C1AU
#endif

#define IS_FLASH_TYPEERASE(VALUE)(((VALUE) == FLASH_TYPEERASE_SECTORS) || \
                                  ((VALUE) == FLASH_TYPEERASE_MASSERASE))

#define IS_VOLTAGERANGE(RANGE)(((RANGE) == FLASH_VOLTAGE_RANGE_1) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_2) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_3) || \
                               ((RANGE) == FLASH_VOLTAGE_RANGE_4))

#define IS_WRPSTATE(VALUE)(((VALUE) == OB_WRPSTATE_DISABLE) || \
                           ((VALUE) == OB_WRPSTATE_ENABLE))

#define IS_OPTIONBYTE(VALUE)(((VALUE) <= (OPTIONBYTE_WRP|OPTIONBYTE_RDP|OPTIONBYTE_USER|OPTIONBYTE_BOR)))

#define IS_OB_RDP_LEVEL(LEVEL) (((LEVEL) == OB_RDP_LEVEL_0) ||\
                                ((LEVEL) == OB_RDP_LEVEL_1) ||\
                                ((LEVEL) == OB_RDP_LEVEL_2))

#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NO_RST) || ((SOURCE) == OB_STOP_RST))

#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NO_RST) || ((SOURCE) == OB_STDBY_RST))

#define IS_OB_BOR_LEVEL(LEVEL) (((LEVEL) == OB_BOR_LEVEL1) || ((LEVEL) == OB_BOR_LEVEL2) ||\
                                ((LEVEL) == OB_BOR_LEVEL3) || ((LEVEL) == OB_BOR_OFF))

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define IS_PCROPSTATE(VALUE)(((VALUE) == OB_PCROP_STATE_DISABLE) || \
                             ((VALUE) == OB_PCROP_STATE_ENABLE))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define IS_OBEX(VALUE)(((VALUE) == OPTIONBYTE_PCROP) || \
                       ((VALUE) == OPTIONBYTE_BOOTCONFIG))
#endif

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define IS_OBEX(VALUE)(((VALUE) == OPTIONBYTE_PCROP))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx)|| defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_0)  || \
                                   ((LATENCY) == FLASH_LATENCY_1)  || \
                                   ((LATENCY) == FLASH_LATENCY_2)  || \
                                   ((LATENCY) == FLASH_LATENCY_3)  || \
                                   ((LATENCY) == FLASH_LATENCY_4)  || \
                                   ((LATENCY) == FLASH_LATENCY_5)  || \
                                   ((LATENCY) == FLASH_LATENCY_6)  || \
                                   ((LATENCY) == FLASH_LATENCY_7)  || \
                                   ((LATENCY) == FLASH_LATENCY_8)  || \
                                   ((LATENCY) == FLASH_LATENCY_9)  || \
                                   ((LATENCY) == FLASH_LATENCY_10) || \
                                   ((LATENCY) == FLASH_LATENCY_11) || \
                                   ((LATENCY) == FLASH_LATENCY_12) || \
                                   ((LATENCY) == FLASH_LATENCY_13) || \
                                   ((LATENCY) == FLASH_LATENCY_14) || \
                                   ((LATENCY) == FLASH_LATENCY_15))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_LATENCY_0)  || \
                                   ((LATENCY) == FLASH_LATENCY_1)  || \
                                   ((LATENCY) == FLASH_LATENCY_2)  || \
                                   ((LATENCY) == FLASH_LATENCY_3)  || \
                                   ((LATENCY) == FLASH_LATENCY_4)  || \
                                   ((LATENCY) == FLASH_LATENCY_5)  || \
                                   ((LATENCY) == FLASH_LATENCY_6)  || \
                                   ((LATENCY) == FLASH_LATENCY_7))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_FLASH_BANK(BANK) (((BANK) == FLASH_BANK_1)  || \
                             ((BANK) == FLASH_BANK_2)  || \
                             ((BANK) == FLASH_BANK_BOTH))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx) || defined(STM32F413xx) ||\
    defined(STM32F423xx)
#define IS_FLASH_BANK(BANK) (((BANK) == FLASH_BANK_1))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_FLASH_SECTOR(SECTOR) ( ((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                  ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                  ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                  ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7)   ||\
                                  ((SECTOR) == FLASH_SECTOR_8)   || ((SECTOR) == FLASH_SECTOR_9)   ||\
                                  ((SECTOR) == FLASH_SECTOR_10)  || ((SECTOR) == FLASH_SECTOR_11)  ||\
                                  ((SECTOR) == FLASH_SECTOR_12)  || ((SECTOR) == FLASH_SECTOR_13)  ||\
                                  ((SECTOR) == FLASH_SECTOR_14)  || ((SECTOR) == FLASH_SECTOR_15)  ||\
                                  ((SECTOR) == FLASH_SECTOR_16)  || ((SECTOR) == FLASH_SECTOR_17)  ||\
                                  ((SECTOR) == FLASH_SECTOR_18)  || ((SECTOR) == FLASH_SECTOR_19)  ||\
                                  ((SECTOR) == FLASH_SECTOR_20)  || ((SECTOR) == FLASH_SECTOR_21)  ||\
                                  ((SECTOR) == FLASH_SECTOR_22)  || ((SECTOR) == FLASH_SECTOR_23))
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_FLASH_SECTOR(SECTOR) ( ((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                  ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                  ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                  ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7)   ||\
                                  ((SECTOR) == FLASH_SECTOR_8)   || ((SECTOR) == FLASH_SECTOR_9)   ||\
                                  ((SECTOR) == FLASH_SECTOR_10)  || ((SECTOR) == FLASH_SECTOR_11)  ||\
                                  ((SECTOR) == FLASH_SECTOR_12)  || ((SECTOR) == FLASH_SECTOR_13)  ||\
                                  ((SECTOR) == FLASH_SECTOR_14)  || ((SECTOR) == FLASH_SECTOR_15))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || defined(STM32F412Zx) ||\
    defined(STM32F412Vx) || defined(STM32F412Rx) || defined(STM32F412Cx)
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                 ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                 ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7)   ||\
                                 ((SECTOR) == FLASH_SECTOR_8)   || ((SECTOR) == FLASH_SECTOR_9)   ||\
                                 ((SECTOR) == FLASH_SECTOR_10)  || ((SECTOR) == FLASH_SECTOR_11))
#endif

#if defined(STM32F401xC)
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                 ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                 ((SECTOR) == FLASH_SECTOR_4))
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx)
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_SECTOR_0)   || ((SECTOR) == FLASH_SECTOR_1)   ||\
                                 ((SECTOR) == FLASH_SECTOR_2)   || ((SECTOR) == FLASH_SECTOR_3)   ||\
                                 ((SECTOR) == FLASH_SECTOR_4)   || ((SECTOR) == FLASH_SECTOR_5)   ||\
                                 ((SECTOR) == FLASH_SECTOR_6)   || ((SECTOR) == FLASH_SECTOR_7))
#endif

#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= FLASH_BASE) && ((ADDRESS) <= FLASH_END)) || \
                                   (((ADDRESS) >= FLASH_OTP_BASE) && ((ADDRESS) <= FLASH_OTP_END)))

#define IS_FLASH_NBSECTORS(NBSECTORS) (((NBSECTORS) != 0) && ((NBSECTORS) <= FLASH_SECTOR_TOTAL))

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFF000000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFFFF8000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F401xC)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx)
#define IS_OB_WRP_SECTOR(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
#define IS_OB_PCROP(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F413xx) || defined(STM32F423xx)
#define IS_OB_PCROP(SECTOR)((((SECTOR) & 0xFFFF8000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F401xC)
#define IS_OB_PCROP(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx)
#define IS_OB_PCROP(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F401xE) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) ||\
    defined(STM32F412Rx) || defined(STM32F412Cx)
#define IS_OB_PCROP(SECTOR)((((SECTOR) & 0xFFFFF000U) == 0x00000000U) && ((SECTOR) != 0x00000000U))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define IS_OB_BOOT(BOOT) (((BOOT) == OB_DUAL_BOOT_ENABLE) || ((BOOT) == OB_DUAL_BOOT_DISABLE))
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
#define IS_OB_PCROP_SELECT(PCROP) (((PCROP) == OB_PCROP_SELECTED) || ((PCROP) == OB_PCROP_DESELECTED))
#endif

void FLASH_Erase_Sector(uint32_t Sector, uint8_t VoltageRange);
void FLASH_FlushCaches(void);

#ifdef __cplusplus
}
#endif

#endif
