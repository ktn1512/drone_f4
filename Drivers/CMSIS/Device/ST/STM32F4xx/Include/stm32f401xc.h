#ifndef __STM32F401xC_H
#define __STM32F401xC_H

#ifdef __cplusplus
extern "C" {
#endif

#define __CM4_REV                 0x0001U
#define __MPU_PRESENT             1U
#define __NVIC_PRIO_BITS          4U
#define __Vendor_SysTickConfig    0U
#define __FPU_PRESENT             1U

typedef enum
{

  NonMaskableInt_IRQn         = -14,
  MemoryManagement_IRQn       = -12,
  BusFault_IRQn               = -11,
  UsageFault_IRQn             = -10,
  SVCall_IRQn                 = -5,
  DebugMonitor_IRQn           = -4,
  PendSV_IRQn                 = -2,
  SysTick_IRQn                = -1,

  WWDG_IRQn                   = 0,
  PVD_IRQn                    = 1,
  TAMP_STAMP_IRQn             = 2,
  RTC_WKUP_IRQn               = 3,
  FLASH_IRQn                  = 4,
  RCC_IRQn                    = 5,
  EXTI0_IRQn                  = 6,
  EXTI1_IRQn                  = 7,
  EXTI2_IRQn                  = 8,
  EXTI3_IRQn                  = 9,
  EXTI4_IRQn                  = 10,
  DMA1_Stream0_IRQn           = 11,
  DMA1_Stream1_IRQn           = 12,
  DMA1_Stream2_IRQn           = 13,
  DMA1_Stream3_IRQn           = 14,
  DMA1_Stream4_IRQn           = 15,
  DMA1_Stream5_IRQn           = 16,
  DMA1_Stream6_IRQn           = 17,
  ADC_IRQn                    = 18,
  EXTI9_5_IRQn                = 23,
  TIM1_BRK_TIM9_IRQn          = 24,
  TIM1_UP_TIM10_IRQn          = 25,
  TIM1_TRG_COM_TIM11_IRQn     = 26,
  TIM1_CC_IRQn                = 27,
  TIM2_IRQn                   = 28,
  TIM3_IRQn                   = 29,
  TIM4_IRQn                   = 30,
  I2C1_EV_IRQn                = 31,
  I2C1_ER_IRQn                = 32,
  I2C2_EV_IRQn                = 33,
  I2C2_ER_IRQn                = 34,
  SPI1_IRQn                   = 35,
  SPI2_IRQn                   = 36,
  USART1_IRQn                 = 37,
  USART2_IRQn                 = 38,
  EXTI15_10_IRQn              = 40,
  RTC_Alarm_IRQn              = 41,
  OTG_FS_WKUP_IRQn            = 42,
  DMA1_Stream7_IRQn           = 47,
  SDIO_IRQn                   = 49,
  TIM5_IRQn                   = 50,
  SPI3_IRQn                   = 51,
  DMA2_Stream0_IRQn           = 56,
  DMA2_Stream1_IRQn           = 57,
  DMA2_Stream2_IRQn           = 58,
  DMA2_Stream3_IRQn           = 59,
  DMA2_Stream4_IRQn           = 60,
  OTG_FS_IRQn                 = 67,
  DMA2_Stream5_IRQn           = 68,
  DMA2_Stream6_IRQn           = 69,
  DMA2_Stream7_IRQn           = 70,
  USART6_IRQn                 = 71,
  I2C3_EV_IRQn                = 72,
  I2C3_ER_IRQn                = 73,
  FPU_IRQn                    = 81,
                                SPI4_IRQn                   = 84
} IRQn_Type;

#include "core_cm4.h"
#include "system_stm32f4xx.h"
#include <stdint.h>

typedef struct
{
  __IO uint32_t SR;
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMPR1;
  __IO uint32_t SMPR2;
  __IO uint32_t JOFR1;
  __IO uint32_t JOFR2;
  __IO uint32_t JOFR3;
  __IO uint32_t JOFR4;
  __IO uint32_t HTR;
  __IO uint32_t LTR;
  __IO uint32_t SQR1;
  __IO uint32_t SQR2;
  __IO uint32_t SQR3;
  __IO uint32_t JSQR;
  __IO uint32_t JDR1;
  __IO uint32_t JDR2;
  __IO uint32_t JDR3;
  __IO uint32_t JDR4;
  __IO uint32_t DR;
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;
  __IO uint32_t CCR;
  __IO uint32_t CDR;
} ADC_Common_TypeDef;

typedef struct
{
  __IO uint32_t DR;
  __IO uint8_t  IDR;
  uint8_t       RESERVED0;
  uint16_t      RESERVED1;
  __IO uint32_t CR;
} CRC_TypeDef;

typedef struct
{
  __IO uint32_t IDCODE;
  __IO uint32_t CR;
  __IO uint32_t APB1FZ;
  __IO uint32_t APB2FZ;
} DBGMCU_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t NDTR;
  __IO uint32_t PAR;
  __IO uint32_t M0AR;
  __IO uint32_t M1AR;
  __IO uint32_t FCR;
} DMA_Stream_TypeDef;

typedef struct
{
  __IO uint32_t LISR;
  __IO uint32_t HISR;
  __IO uint32_t LIFCR;
  __IO uint32_t HIFCR;
} DMA_TypeDef;

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;

typedef struct
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t OPTCR;
  __IO uint32_t OPTCR1;
} FLASH_TypeDef;

typedef struct
{
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t LCKR;
  __IO uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t MEMRMP;
  __IO uint32_t PMC;
  __IO uint32_t EXTICR[4];
  uint32_t      RESERVED[2];
  __IO uint32_t CMPCR;
} SYSCFG_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t OAR1;
  __IO uint32_t OAR2;
  __IO uint32_t DR;
  __IO uint32_t SR1;
  __IO uint32_t SR2;
  __IO uint32_t CCR;
  __IO uint32_t TRISE;
  __IO uint32_t FLTR;
} I2C_TypeDef;

typedef struct
{
  __IO uint32_t KR;
  __IO uint32_t PR;
  __IO uint32_t RLR;
  __IO uint32_t SR;
} IWDG_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CSR;
} PWR_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t PLLCFGR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t AHB1RSTR;
  __IO uint32_t AHB2RSTR;
  __IO uint32_t AHB3RSTR;
  uint32_t      RESERVED0;
  __IO uint32_t APB1RSTR;
  __IO uint32_t APB2RSTR;
  uint32_t      RESERVED1[2];
  __IO uint32_t AHB1ENR;
  __IO uint32_t AHB2ENR;
  __IO uint32_t AHB3ENR;
  uint32_t      RESERVED2;
  __IO uint32_t APB1ENR;
  __IO uint32_t APB2ENR;
  uint32_t      RESERVED3[2];
  __IO uint32_t AHB1LPENR;
  __IO uint32_t AHB2LPENR;
  __IO uint32_t AHB3LPENR;
  uint32_t      RESERVED4;
  __IO uint32_t APB1LPENR;
  __IO uint32_t APB2LPENR;
  uint32_t      RESERVED5[2];
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
  uint32_t      RESERVED6[2];
  __IO uint32_t SSCGR;
  __IO uint32_t PLLI2SCFGR;
  uint32_t      RESERVED7[1];
  __IO uint32_t DCKCFGR;
} RCC_TypeDef;

typedef struct
{
  __IO uint32_t TR;
  __IO uint32_t DR;
  __IO uint32_t CR;
  __IO uint32_t ISR;
  __IO uint32_t PRER;
  __IO uint32_t WUTR;
  __IO uint32_t CALIBR;
  __IO uint32_t ALRMAR;
  __IO uint32_t ALRMBR;
  __IO uint32_t WPR;
  __IO uint32_t SSR;
  __IO uint32_t SHIFTR;
  __IO uint32_t TSTR;
  __IO uint32_t TSDR;
  __IO uint32_t TSSSR;
  __IO uint32_t CALR;
  __IO uint32_t TAFCR;
  __IO uint32_t ALRMASSR;
  __IO uint32_t ALRMBSSR;
  uint32_t RESERVED7;
  __IO uint32_t BKP0R;
  __IO uint32_t BKP1R;
  __IO uint32_t BKP2R;
  __IO uint32_t BKP3R;
  __IO uint32_t BKP4R;
  __IO uint32_t BKP5R;
  __IO uint32_t BKP6R;
  __IO uint32_t BKP7R;
  __IO uint32_t BKP8R;
  __IO uint32_t BKP9R;
  __IO uint32_t BKP10R;
  __IO uint32_t BKP11R;
  __IO uint32_t BKP12R;
  __IO uint32_t BKP13R;
  __IO uint32_t BKP14R;
  __IO uint32_t BKP15R;
  __IO uint32_t BKP16R;
  __IO uint32_t BKP17R;
  __IO uint32_t BKP18R;
  __IO uint32_t BKP19R;
} RTC_TypeDef;

typedef struct
{
  __IO uint32_t POWER;
  __IO uint32_t CLKCR;
  __IO uint32_t ARG;
  __IO uint32_t CMD;
  __IO const uint32_t  RESPCMD;
  __IO const uint32_t  RESP1;
  __IO const uint32_t  RESP2;
  __IO const uint32_t  RESP3;
  __IO const uint32_t  RESP4;
  __IO uint32_t DTIMER;
  __IO uint32_t DLEN;
  __IO uint32_t DCTRL;
  __IO const uint32_t  DCOUNT;
  __IO const uint32_t  STA;
  __IO uint32_t ICR;
  __IO uint32_t MASK;
  uint32_t      RESERVED0[2];
  __IO const uint32_t  FIFOCNT;
  uint32_t      RESERVED1[13];
  __IO uint32_t FIFO;
} SDIO_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t CRCPR;
  __IO uint32_t RXCRCR;
  __IO uint32_t TXCRCR;
  __IO uint32_t I2SCFGR;
  __IO uint32_t I2SPR;
} SPI_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMCR;
  __IO uint32_t DIER;
  __IO uint32_t SR;
  __IO uint32_t EGR;
  __IO uint32_t CCMR1;
  __IO uint32_t CCMR2;
  __IO uint32_t CCER;
  __IO uint32_t CNT;
  __IO uint32_t PSC;
  __IO uint32_t ARR;
  __IO uint32_t RCR;
  __IO uint32_t CCR1;
  __IO uint32_t CCR2;
  __IO uint32_t CCR3;
  __IO uint32_t CCR4;
  __IO uint32_t BDTR;
  __IO uint32_t DCR;
  __IO uint32_t DMAR;
  __IO uint32_t OR;
} TIM_TypeDef;

typedef struct
{
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t BRR;
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t CR3;
  __IO uint32_t GTPR;
} USART_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFR;
  __IO uint32_t SR;
} WWDG_TypeDef;

typedef struct
{
  __IO uint32_t GOTGCTL;
  __IO uint32_t GOTGINT;
  __IO uint32_t GAHBCFG;
  __IO uint32_t GUSBCFG;
  __IO uint32_t GRSTCTL;
  __IO uint32_t GINTSTS;
  __IO uint32_t GINTMSK;
  __IO uint32_t GRXSTSR;
  __IO uint32_t GRXSTSP;
  __IO uint32_t GRXFSIZ;
  __IO uint32_t DIEPTXF0_HNPTXFSIZ;
  __IO uint32_t HNPTXSTS;
  uint32_t Reserved30[2];
  __IO uint32_t GCCFG;
  __IO uint32_t CID;
  uint32_t  Reserved40[48];
  __IO uint32_t HPTXFSIZ;
  __IO uint32_t DIEPTXF[0x0F];
} USB_OTG_GlobalTypeDef;

typedef struct
{
  __IO uint32_t DCFG;
  __IO uint32_t DCTL;
  __IO uint32_t DSTS;
  uint32_t Reserved0C;
  __IO uint32_t DIEPMSK;
  __IO uint32_t DOEPMSK;
  __IO uint32_t DAINT;
  __IO uint32_t DAINTMSK;
  uint32_t  Reserved20;
  uint32_t Reserved9;
  __IO uint32_t DVBUSDIS;
  __IO uint32_t DVBUSPULSE;
  __IO uint32_t DTHRCTL;
  __IO uint32_t DIEPEMPMSK;
  __IO uint32_t DEACHINT;
  __IO uint32_t DEACHMSK;
  uint32_t Reserved40;
  __IO uint32_t DINEP1MSK;
  uint32_t  Reserved44[15];
  __IO uint32_t DOUTEP1MSK;
} USB_OTG_DeviceTypeDef;

typedef struct
{
  __IO uint32_t DIEPCTL;
  uint32_t Reserved04;
  __IO uint32_t DIEPINT;
  uint32_t Reserved0C;
  __IO uint32_t DIEPTSIZ;
  __IO uint32_t DIEPDMA;
  __IO uint32_t DTXFSTS;
  uint32_t Reserved18;
} USB_OTG_INEndpointTypeDef;

typedef struct
{
  __IO uint32_t DOEPCTL;
  uint32_t Reserved04;
  __IO uint32_t DOEPINT;
  uint32_t Reserved0C;
  __IO uint32_t DOEPTSIZ;
  __IO uint32_t DOEPDMA;
  uint32_t Reserved18[2];
} USB_OTG_OUTEndpointTypeDef;

typedef struct
{
  __IO uint32_t HCFG;
  __IO uint32_t HFIR;
  __IO uint32_t HFNUM;
  uint32_t Reserved40C;
  __IO uint32_t HPTXSTS;
  __IO uint32_t HAINT;
  __IO uint32_t HAINTMSK;
} USB_OTG_HostTypeDef;

typedef struct
{
  __IO uint32_t HCCHAR;
  __IO uint32_t HCSPLT;
  __IO uint32_t HCINT;
  __IO uint32_t HCINTMSK;
  __IO uint32_t HCTSIZ;
  __IO uint32_t HCDMA;
  uint32_t Reserved[2];
} USB_OTG_HostChannelTypeDef;

#define FLASH_BASE            0x08000000UL
#define SRAM1_BASE            0x20000000UL
#define PERIPH_BASE           0x40000000UL
#define SRAM1_BB_BASE         0x22000000UL
#define PERIPH_BB_BASE        0x42000000UL
#define BKPSRAM_BB_BASE       0x42480000UL
#define FLASH_END             0x0803FFFFUL
#define FLASH_OTP_BASE        0x1FFF7800UL
#define FLASH_OTP_END         0x1FFF7A0FUL

#define SRAM_BASE             SRAM1_BASE
#define SRAM_BB_BASE          SRAM1_BB_BASE

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000UL)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00UL)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800UL)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00UL)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000UL)
#define I2S2ext_BASE          (APB1PERIPH_BASE + 0x3400UL)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)
#define I2S3ext_BASE          (APB1PERIPH_BASE + 0x4000UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL)
#define I2C3_BASE             (APB1PERIPH_BASE + 0x5C00UL)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)

#define TIM1_BASE             (APB2PERIPH_BASE + 0x0000UL)
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000UL)
#define USART6_BASE           (APB2PERIPH_BASE + 0x1400UL)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2000UL)
#define ADC1_COMMON_BASE      (APB2PERIPH_BASE + 0x2300UL)

#define ADC_BASE               ADC1_COMMON_BASE
#define SDIO_BASE             (APB2PERIPH_BASE + 0x2C00UL)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL)
#define SPI4_BASE             (APB2PERIPH_BASE + 0x3400UL)
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800UL)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00UL)
#define TIM9_BASE             (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x4800UL)

#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00UL)
#define CRC_BASE              (AHB1PERIPH_BASE + 0x3000UL)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x3C00UL)
#define DMA1_BASE             (AHB1PERIPH_BASE + 0x6000UL)
#define DMA1_Stream0_BASE     (DMA1_BASE + 0x010UL)
#define DMA1_Stream1_BASE     (DMA1_BASE + 0x028UL)
#define DMA1_Stream2_BASE     (DMA1_BASE + 0x040UL)
#define DMA1_Stream3_BASE     (DMA1_BASE + 0x058UL)
#define DMA1_Stream4_BASE     (DMA1_BASE + 0x070UL)
#define DMA1_Stream5_BASE     (DMA1_BASE + 0x088UL)
#define DMA1_Stream6_BASE     (DMA1_BASE + 0x0A0UL)
#define DMA1_Stream7_BASE     (DMA1_BASE + 0x0B8UL)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x6400UL)
#define DMA2_Stream0_BASE     (DMA2_BASE + 0x010UL)
#define DMA2_Stream1_BASE     (DMA2_BASE + 0x028UL)
#define DMA2_Stream2_BASE     (DMA2_BASE + 0x040UL)
#define DMA2_Stream3_BASE     (DMA2_BASE + 0x058UL)
#define DMA2_Stream4_BASE     (DMA2_BASE + 0x070UL)
#define DMA2_Stream5_BASE     (DMA2_BASE + 0x088UL)
#define DMA2_Stream6_BASE     (DMA2_BASE + 0x0A0UL)
#define DMA2_Stream7_BASE     (DMA2_BASE + 0x0B8UL)

#define DBGMCU_BASE           0xE0042000UL

#define USB_OTG_FS_PERIPH_BASE               0x50000000UL

#define USB_OTG_GLOBAL_BASE                  0x000UL
#define USB_OTG_DEVICE_BASE                  0x800UL
#define USB_OTG_IN_ENDPOINT_BASE             0x900UL
#define USB_OTG_OUT_ENDPOINT_BASE            0xB00UL
#define USB_OTG_EP_REG_SIZE                  0x20UL
#define USB_OTG_HOST_BASE                    0x400UL
#define USB_OTG_HOST_PORT_BASE               0x440UL
#define USB_OTG_HOST_CHANNEL_BASE            0x500UL
#define USB_OTG_HOST_CHANNEL_SIZE            0x20UL
#define USB_OTG_PCGCCTL_BASE                 0xE00UL
#define USB_OTG_FIFO_BASE                    0x1000UL
#define USB_OTG_FIFO_SIZE                    0x1000UL

#define UID_BASE                     0x1FFF7A10UL
#define FLASHSIZE_BASE               0x1FFF7A22UL
#define PACKAGE_BASE                 0x1FFF7BF0UL

#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define I2S2ext             ((SPI_TypeDef *) I2S2ext_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define I2S3ext             ((SPI_TypeDef *) I2S3ext_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define I2C3                ((I2C_TypeDef *) I2C3_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART6              ((USART_TypeDef *) USART6_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC1_COMMON         ((ADC_Common_TypeDef *) ADC1_COMMON_BASE)

#define ADC                  ADC1_COMMON
#define SDIO                ((SDIO_TypeDef *) SDIO_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define SPI4                ((SPI_TypeDef *) SPI4_BASE)
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define TIM9                ((TIM_TypeDef *) TIM9_BASE)
#define TIM10               ((TIM_TypeDef *) TIM10_BASE)
#define TIM11               ((TIM_TypeDef *) TIM11_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Stream0        ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
#define DMA1_Stream1        ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
#define DMA1_Stream2        ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
#define DMA1_Stream3        ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
#define DMA1_Stream4        ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
#define DMA1_Stream5        ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
#define DMA1_Stream6        ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
#define DMA1_Stream7        ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)
#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Stream0        ((DMA_Stream_TypeDef *) DMA2_Stream0_BASE)
#define DMA2_Stream1        ((DMA_Stream_TypeDef *) DMA2_Stream1_BASE)
#define DMA2_Stream2        ((DMA_Stream_TypeDef *) DMA2_Stream2_BASE)
#define DMA2_Stream3        ((DMA_Stream_TypeDef *) DMA2_Stream3_BASE)
#define DMA2_Stream4        ((DMA_Stream_TypeDef *) DMA2_Stream4_BASE)
#define DMA2_Stream5        ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE)
#define DMA2_Stream6        ((DMA_Stream_TypeDef *) DMA2_Stream6_BASE)
#define DMA2_Stream7        ((DMA_Stream_TypeDef *) DMA2_Stream7_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)
#define USB_OTG_FS          ((USB_OTG_GlobalTypeDef *) USB_OTG_FS_PERIPH_BASE)

#define LSI_STARTUP_TIME                40U

#define ADC_SR_AWD_Pos            (0U)
#define ADC_SR_AWD_Msk            (0x1UL << ADC_SR_AWD_Pos)
#define ADC_SR_AWD                ADC_SR_AWD_Msk
#define ADC_SR_EOC_Pos            (1U)
#define ADC_SR_EOC_Msk            (0x1UL << ADC_SR_EOC_Pos)
#define ADC_SR_EOC                ADC_SR_EOC_Msk
#define ADC_SR_JEOC_Pos           (2U)
#define ADC_SR_JEOC_Msk           (0x1UL << ADC_SR_JEOC_Pos)
#define ADC_SR_JEOC               ADC_SR_JEOC_Msk
#define ADC_SR_JSTRT_Pos          (3U)
#define ADC_SR_JSTRT_Msk          (0x1UL << ADC_SR_JSTRT_Pos)
#define ADC_SR_JSTRT              ADC_SR_JSTRT_Msk
#define ADC_SR_STRT_Pos           (4U)
#define ADC_SR_STRT_Msk           (0x1UL << ADC_SR_STRT_Pos)
#define ADC_SR_STRT               ADC_SR_STRT_Msk
#define ADC_SR_OVR_Pos            (5U)
#define ADC_SR_OVR_Msk            (0x1UL << ADC_SR_OVR_Pos)
#define ADC_SR_OVR                ADC_SR_OVR_Msk

#define ADC_CR1_AWDCH_Pos         (0U)
#define ADC_CR1_AWDCH_Msk         (0x1FUL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_AWDCH             ADC_CR1_AWDCH_Msk
#define ADC_CR1_AWDCH_0           (0x01UL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_AWDCH_1           (0x02UL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_AWDCH_2           (0x04UL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_AWDCH_3           (0x08UL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_AWDCH_4           (0x10UL << ADC_CR1_AWDCH_Pos)
#define ADC_CR1_EOCIE_Pos         (5U)
#define ADC_CR1_EOCIE_Msk         (0x1UL << ADC_CR1_EOCIE_Pos)
#define ADC_CR1_EOCIE             ADC_CR1_EOCIE_Msk
#define ADC_CR1_AWDIE_Pos         (6U)
#define ADC_CR1_AWDIE_Msk         (0x1UL << ADC_CR1_AWDIE_Pos)
#define ADC_CR1_AWDIE             ADC_CR1_AWDIE_Msk
#define ADC_CR1_JEOCIE_Pos        (7U)
#define ADC_CR1_JEOCIE_Msk        (0x1UL << ADC_CR1_JEOCIE_Pos)
#define ADC_CR1_JEOCIE            ADC_CR1_JEOCIE_Msk
#define ADC_CR1_SCAN_Pos          (8U)
#define ADC_CR1_SCAN_Msk          (0x1UL << ADC_CR1_SCAN_Pos)
#define ADC_CR1_SCAN              ADC_CR1_SCAN_Msk
#define ADC_CR1_AWDSGL_Pos        (9U)
#define ADC_CR1_AWDSGL_Msk        (0x1UL << ADC_CR1_AWDSGL_Pos)
#define ADC_CR1_AWDSGL            ADC_CR1_AWDSGL_Msk
#define ADC_CR1_JAUTO_Pos         (10U)
#define ADC_CR1_JAUTO_Msk         (0x1UL << ADC_CR1_JAUTO_Pos)
#define ADC_CR1_JAUTO             ADC_CR1_JAUTO_Msk
#define ADC_CR1_DISCEN_Pos        (11U)
#define ADC_CR1_DISCEN_Msk        (0x1UL << ADC_CR1_DISCEN_Pos)
#define ADC_CR1_DISCEN            ADC_CR1_DISCEN_Msk
#define ADC_CR1_JDISCEN_Pos       (12U)
#define ADC_CR1_JDISCEN_Msk       (0x1UL << ADC_CR1_JDISCEN_Pos)
#define ADC_CR1_JDISCEN           ADC_CR1_JDISCEN_Msk
#define ADC_CR1_DISCNUM_Pos       (13U)
#define ADC_CR1_DISCNUM_Msk       (0x7UL << ADC_CR1_DISCNUM_Pos)
#define ADC_CR1_DISCNUM           ADC_CR1_DISCNUM_Msk
#define ADC_CR1_DISCNUM_0         (0x1UL << ADC_CR1_DISCNUM_Pos)
#define ADC_CR1_DISCNUM_1         (0x2UL << ADC_CR1_DISCNUM_Pos)
#define ADC_CR1_DISCNUM_2         (0x4UL << ADC_CR1_DISCNUM_Pos)
#define ADC_CR1_JAWDEN_Pos        (22U)
#define ADC_CR1_JAWDEN_Msk        (0x1UL << ADC_CR1_JAWDEN_Pos)
#define ADC_CR1_JAWDEN            ADC_CR1_JAWDEN_Msk
#define ADC_CR1_AWDEN_Pos         (23U)
#define ADC_CR1_AWDEN_Msk         (0x1UL << ADC_CR1_AWDEN_Pos)
#define ADC_CR1_AWDEN             ADC_CR1_AWDEN_Msk
#define ADC_CR1_RES_Pos           (24U)
#define ADC_CR1_RES_Msk           (0x3UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES               ADC_CR1_RES_Msk
#define ADC_CR1_RES_0             (0x1UL << ADC_CR1_RES_Pos)
#define ADC_CR1_RES_1             (0x2UL << ADC_CR1_RES_Pos)
#define ADC_CR1_OVRIE_Pos         (26U)
#define ADC_CR1_OVRIE_Msk         (0x1UL << ADC_CR1_OVRIE_Pos)
#define ADC_CR1_OVRIE             ADC_CR1_OVRIE_Msk

#define ADC_CR2_ADON_Pos          (0U)
#define ADC_CR2_ADON_Msk          (0x1UL << ADC_CR2_ADON_Pos)
#define ADC_CR2_ADON              ADC_CR2_ADON_Msk
#define ADC_CR2_CONT_Pos          (1U)
#define ADC_CR2_CONT_Msk          (0x1UL << ADC_CR2_CONT_Pos)
#define ADC_CR2_CONT              ADC_CR2_CONT_Msk
#define ADC_CR2_DMA_Pos           (8U)
#define ADC_CR2_DMA_Msk           (0x1UL << ADC_CR2_DMA_Pos)
#define ADC_CR2_DMA               ADC_CR2_DMA_Msk
#define ADC_CR2_DDS_Pos           (9U)
#define ADC_CR2_DDS_Msk           (0x1UL << ADC_CR2_DDS_Pos)
#define ADC_CR2_DDS               ADC_CR2_DDS_Msk
#define ADC_CR2_EOCS_Pos          (10U)
#define ADC_CR2_EOCS_Msk          (0x1UL << ADC_CR2_EOCS_Pos)
#define ADC_CR2_EOCS              ADC_CR2_EOCS_Msk
#define ADC_CR2_ALIGN_Pos         (11U)
#define ADC_CR2_ALIGN_Msk         (0x1UL << ADC_CR2_ALIGN_Pos)
#define ADC_CR2_ALIGN             ADC_CR2_ALIGN_Msk
#define ADC_CR2_JEXTSEL_Pos       (16U)
#define ADC_CR2_JEXTSEL_Msk       (0xFUL << ADC_CR2_JEXTSEL_Pos)
#define ADC_CR2_JEXTSEL           ADC_CR2_JEXTSEL_Msk
#define ADC_CR2_JEXTSEL_0         (0x1UL << ADC_CR2_JEXTSEL_Pos)
#define ADC_CR2_JEXTSEL_1         (0x2UL << ADC_CR2_JEXTSEL_Pos)
#define ADC_CR2_JEXTSEL_2         (0x4UL << ADC_CR2_JEXTSEL_Pos)
#define ADC_CR2_JEXTSEL_3         (0x8UL << ADC_CR2_JEXTSEL_Pos)
#define ADC_CR2_JEXTEN_Pos        (20U)
#define ADC_CR2_JEXTEN_Msk        (0x3UL << ADC_CR2_JEXTEN_Pos)
#define ADC_CR2_JEXTEN            ADC_CR2_JEXTEN_Msk
#define ADC_CR2_JEXTEN_0          (0x1UL << ADC_CR2_JEXTEN_Pos)
#define ADC_CR2_JEXTEN_1          (0x2UL << ADC_CR2_JEXTEN_Pos)
#define ADC_CR2_JSWSTART_Pos      (22U)
#define ADC_CR2_JSWSTART_Msk      (0x1UL << ADC_CR2_JSWSTART_Pos)
#define ADC_CR2_JSWSTART          ADC_CR2_JSWSTART_Msk
#define ADC_CR2_EXTSEL_Pos        (24U)
#define ADC_CR2_EXTSEL_Msk        (0xFUL << ADC_CR2_EXTSEL_Pos)
#define ADC_CR2_EXTSEL            ADC_CR2_EXTSEL_Msk
#define ADC_CR2_EXTSEL_0          (0x1UL << ADC_CR2_EXTSEL_Pos)
#define ADC_CR2_EXTSEL_1          (0x2UL << ADC_CR2_EXTSEL_Pos)
#define ADC_CR2_EXTSEL_2          (0x4UL << ADC_CR2_EXTSEL_Pos)
#define ADC_CR2_EXTSEL_3          (0x8UL << ADC_CR2_EXTSEL_Pos)
#define ADC_CR2_EXTEN_Pos         (28U)
#define ADC_CR2_EXTEN_Msk         (0x3UL << ADC_CR2_EXTEN_Pos)
#define ADC_CR2_EXTEN             ADC_CR2_EXTEN_Msk
#define ADC_CR2_EXTEN_0           (0x1UL << ADC_CR2_EXTEN_Pos)
#define ADC_CR2_EXTEN_1           (0x2UL << ADC_CR2_EXTEN_Pos)
#define ADC_CR2_SWSTART_Pos       (30U)
#define ADC_CR2_SWSTART_Msk       (0x1UL << ADC_CR2_SWSTART_Pos)
#define ADC_CR2_SWSTART           ADC_CR2_SWSTART_Msk

#define ADC_SMPR1_SMP10_Pos       (0U)
#define ADC_SMPR1_SMP10_Msk       (0x7UL << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10           ADC_SMPR1_SMP10_Msk
#define ADC_SMPR1_SMP10_0         (0x1UL << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_1         (0x2UL << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP10_2         (0x4UL << ADC_SMPR1_SMP10_Pos)
#define ADC_SMPR1_SMP11_Pos       (3U)
#define ADC_SMPR1_SMP11_Msk       (0x7UL << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11           ADC_SMPR1_SMP11_Msk
#define ADC_SMPR1_SMP11_0         (0x1UL << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_1         (0x2UL << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP11_2         (0x4UL << ADC_SMPR1_SMP11_Pos)
#define ADC_SMPR1_SMP12_Pos       (6U)
#define ADC_SMPR1_SMP12_Msk       (0x7UL << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12           ADC_SMPR1_SMP12_Msk
#define ADC_SMPR1_SMP12_0         (0x1UL << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_1         (0x2UL << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP12_2         (0x4UL << ADC_SMPR1_SMP12_Pos)
#define ADC_SMPR1_SMP13_Pos       (9U)
#define ADC_SMPR1_SMP13_Msk       (0x7UL << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13           ADC_SMPR1_SMP13_Msk
#define ADC_SMPR1_SMP13_0         (0x1UL << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_1         (0x2UL << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP13_2         (0x4UL << ADC_SMPR1_SMP13_Pos)
#define ADC_SMPR1_SMP14_Pos       (12U)
#define ADC_SMPR1_SMP14_Msk       (0x7UL << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14           ADC_SMPR1_SMP14_Msk
#define ADC_SMPR1_SMP14_0         (0x1UL << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_1         (0x2UL << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP14_2         (0x4UL << ADC_SMPR1_SMP14_Pos)
#define ADC_SMPR1_SMP15_Pos       (15U)
#define ADC_SMPR1_SMP15_Msk       (0x7UL << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15           ADC_SMPR1_SMP15_Msk
#define ADC_SMPR1_SMP15_0         (0x1UL << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_1         (0x2UL << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP15_2         (0x4UL << ADC_SMPR1_SMP15_Pos)
#define ADC_SMPR1_SMP16_Pos       (18U)
#define ADC_SMPR1_SMP16_Msk       (0x7UL << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16           ADC_SMPR1_SMP16_Msk
#define ADC_SMPR1_SMP16_0         (0x1UL << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_1         (0x2UL << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP16_2         (0x4UL << ADC_SMPR1_SMP16_Pos)
#define ADC_SMPR1_SMP17_Pos       (21U)
#define ADC_SMPR1_SMP17_Msk       (0x7UL << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17           ADC_SMPR1_SMP17_Msk
#define ADC_SMPR1_SMP17_0         (0x1UL << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_1         (0x2UL << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP17_2         (0x4UL << ADC_SMPR1_SMP17_Pos)
#define ADC_SMPR1_SMP18_Pos       (24U)
#define ADC_SMPR1_SMP18_Msk       (0x7UL << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18           ADC_SMPR1_SMP18_Msk
#define ADC_SMPR1_SMP18_0         (0x1UL << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_1         (0x2UL << ADC_SMPR1_SMP18_Pos)
#define ADC_SMPR1_SMP18_2         (0x4UL << ADC_SMPR1_SMP18_Pos)

#define ADC_SMPR2_SMP0_Pos        (0U)
#define ADC_SMPR2_SMP0_Msk        (0x7UL << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0            ADC_SMPR2_SMP0_Msk
#define ADC_SMPR2_SMP0_0          (0x1UL << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_1          (0x2UL << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP0_2          (0x4UL << ADC_SMPR2_SMP0_Pos)
#define ADC_SMPR2_SMP1_Pos        (3U)
#define ADC_SMPR2_SMP1_Msk        (0x7UL << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1            ADC_SMPR2_SMP1_Msk
#define ADC_SMPR2_SMP1_0          (0x1UL << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_1          (0x2UL << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP1_2          (0x4UL << ADC_SMPR2_SMP1_Pos)
#define ADC_SMPR2_SMP2_Pos        (6U)
#define ADC_SMPR2_SMP2_Msk        (0x7UL << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2            ADC_SMPR2_SMP2_Msk
#define ADC_SMPR2_SMP2_0          (0x1UL << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_1          (0x2UL << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP2_2          (0x4UL << ADC_SMPR2_SMP2_Pos)
#define ADC_SMPR2_SMP3_Pos        (9U)
#define ADC_SMPR2_SMP3_Msk        (0x7UL << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3            ADC_SMPR2_SMP3_Msk
#define ADC_SMPR2_SMP3_0          (0x1UL << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_1          (0x2UL << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP3_2          (0x4UL << ADC_SMPR2_SMP3_Pos)
#define ADC_SMPR2_SMP4_Pos        (12U)
#define ADC_SMPR2_SMP4_Msk        (0x7UL << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4            ADC_SMPR2_SMP4_Msk
#define ADC_SMPR2_SMP4_0          (0x1UL << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_1          (0x2UL << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP4_2          (0x4UL << ADC_SMPR2_SMP4_Pos)
#define ADC_SMPR2_SMP5_Pos        (15U)
#define ADC_SMPR2_SMP5_Msk        (0x7UL << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5            ADC_SMPR2_SMP5_Msk
#define ADC_SMPR2_SMP5_0          (0x1UL << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_1          (0x2UL << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP5_2          (0x4UL << ADC_SMPR2_SMP5_Pos)
#define ADC_SMPR2_SMP6_Pos        (18U)
#define ADC_SMPR2_SMP6_Msk        (0x7UL << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6            ADC_SMPR2_SMP6_Msk
#define ADC_SMPR2_SMP6_0          (0x1UL << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_1          (0x2UL << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP6_2          (0x4UL << ADC_SMPR2_SMP6_Pos)
#define ADC_SMPR2_SMP7_Pos        (21U)
#define ADC_SMPR2_SMP7_Msk        (0x7UL << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7            ADC_SMPR2_SMP7_Msk
#define ADC_SMPR2_SMP7_0          (0x1UL << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_1          (0x2UL << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP7_2          (0x4UL << ADC_SMPR2_SMP7_Pos)
#define ADC_SMPR2_SMP8_Pos        (24U)
#define ADC_SMPR2_SMP8_Msk        (0x7UL << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8            ADC_SMPR2_SMP8_Msk
#define ADC_SMPR2_SMP8_0          (0x1UL << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_1          (0x2UL << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP8_2          (0x4UL << ADC_SMPR2_SMP8_Pos)
#define ADC_SMPR2_SMP9_Pos        (27U)
#define ADC_SMPR2_SMP9_Msk        (0x7UL << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9            ADC_SMPR2_SMP9_Msk
#define ADC_SMPR2_SMP9_0          (0x1UL << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_1          (0x2UL << ADC_SMPR2_SMP9_Pos)
#define ADC_SMPR2_SMP9_2          (0x4UL << ADC_SMPR2_SMP9_Pos)

#define ADC_JOFR1_JOFFSET1_Pos    (0U)
#define ADC_JOFR1_JOFFSET1_Msk    (0xFFFUL << ADC_JOFR1_JOFFSET1_Pos)
#define ADC_JOFR1_JOFFSET1        ADC_JOFR1_JOFFSET1_Msk

#define ADC_JOFR2_JOFFSET2_Pos    (0U)
#define ADC_JOFR2_JOFFSET2_Msk    (0xFFFUL << ADC_JOFR2_JOFFSET2_Pos)
#define ADC_JOFR2_JOFFSET2        ADC_JOFR2_JOFFSET2_Msk

#define ADC_JOFR3_JOFFSET3_Pos    (0U)
#define ADC_JOFR3_JOFFSET3_Msk    (0xFFFUL << ADC_JOFR3_JOFFSET3_Pos)
#define ADC_JOFR3_JOFFSET3        ADC_JOFR3_JOFFSET3_Msk

#define ADC_JOFR4_JOFFSET4_Pos    (0U)
#define ADC_JOFR4_JOFFSET4_Msk    (0xFFFUL << ADC_JOFR4_JOFFSET4_Pos)
#define ADC_JOFR4_JOFFSET4        ADC_JOFR4_JOFFSET4_Msk

#define ADC_HTR_HT_Pos            (0U)
#define ADC_HTR_HT_Msk            (0xFFFUL << ADC_HTR_HT_Pos)
#define ADC_HTR_HT                ADC_HTR_HT_Msk

#define ADC_LTR_LT_Pos            (0U)
#define ADC_LTR_LT_Msk            (0xFFFUL << ADC_LTR_LT_Pos)
#define ADC_LTR_LT                ADC_LTR_LT_Msk

#define ADC_SQR1_SQ13_Pos         (0U)
#define ADC_SQR1_SQ13_Msk         (0x1FUL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13             ADC_SQR1_SQ13_Msk
#define ADC_SQR1_SQ13_0           (0x01UL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_1           (0x02UL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_2           (0x04UL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_3           (0x08UL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ13_4           (0x10UL << ADC_SQR1_SQ13_Pos)
#define ADC_SQR1_SQ14_Pos         (5U)
#define ADC_SQR1_SQ14_Msk         (0x1FUL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14             ADC_SQR1_SQ14_Msk
#define ADC_SQR1_SQ14_0           (0x01UL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_1           (0x02UL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_2           (0x04UL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_3           (0x08UL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ14_4           (0x10UL << ADC_SQR1_SQ14_Pos)
#define ADC_SQR1_SQ15_Pos         (10U)
#define ADC_SQR1_SQ15_Msk         (0x1FUL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15             ADC_SQR1_SQ15_Msk
#define ADC_SQR1_SQ15_0           (0x01UL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_1           (0x02UL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_2           (0x04UL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_3           (0x08UL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ15_4           (0x10UL << ADC_SQR1_SQ15_Pos)
#define ADC_SQR1_SQ16_Pos         (15U)
#define ADC_SQR1_SQ16_Msk         (0x1FUL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16             ADC_SQR1_SQ16_Msk
#define ADC_SQR1_SQ16_0           (0x01UL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_1           (0x02UL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_2           (0x04UL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_3           (0x08UL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_SQ16_4           (0x10UL << ADC_SQR1_SQ16_Pos)
#define ADC_SQR1_L_Pos            (20U)
#define ADC_SQR1_L_Msk            (0xFUL << ADC_SQR1_L_Pos)
#define ADC_SQR1_L                ADC_SQR1_L_Msk
#define ADC_SQR1_L_0              (0x1UL << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_1              (0x2UL << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_2              (0x4UL << ADC_SQR1_L_Pos)
#define ADC_SQR1_L_3              (0x8UL << ADC_SQR1_L_Pos)

#define ADC_SQR2_SQ7_Pos          (0U)
#define ADC_SQR2_SQ7_Msk          (0x1FUL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7              ADC_SQR2_SQ7_Msk
#define ADC_SQR2_SQ7_0            (0x01UL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_1            (0x02UL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_2            (0x04UL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_3            (0x08UL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ7_4            (0x10UL << ADC_SQR2_SQ7_Pos)
#define ADC_SQR2_SQ8_Pos          (5U)
#define ADC_SQR2_SQ8_Msk          (0x1FUL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8              ADC_SQR2_SQ8_Msk
#define ADC_SQR2_SQ8_0            (0x01UL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_1            (0x02UL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_2            (0x04UL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_3            (0x08UL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ8_4            (0x10UL << ADC_SQR2_SQ8_Pos)
#define ADC_SQR2_SQ9_Pos          (10U)
#define ADC_SQR2_SQ9_Msk          (0x1FUL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9              ADC_SQR2_SQ9_Msk
#define ADC_SQR2_SQ9_0            (0x01UL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_1            (0x02UL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_2            (0x04UL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_3            (0x08UL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ9_4            (0x10UL << ADC_SQR2_SQ9_Pos)
#define ADC_SQR2_SQ10_Pos         (15U)
#define ADC_SQR2_SQ10_Msk         (0x1FUL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10             ADC_SQR2_SQ10_Msk
#define ADC_SQR2_SQ10_0           (0x01UL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_1           (0x02UL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_2           (0x04UL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_3           (0x08UL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ10_4           (0x10UL << ADC_SQR2_SQ10_Pos)
#define ADC_SQR2_SQ11_Pos         (20U)
#define ADC_SQR2_SQ11_Msk         (0x1FUL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11             ADC_SQR2_SQ11_Msk
#define ADC_SQR2_SQ11_0           (0x01UL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_1           (0x02UL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_2           (0x04UL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_3           (0x08UL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ11_4           (0x10UL << ADC_SQR2_SQ11_Pos)
#define ADC_SQR2_SQ12_Pos         (25U)
#define ADC_SQR2_SQ12_Msk         (0x1FUL << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12             ADC_SQR2_SQ12_Msk
#define ADC_SQR2_SQ12_0           (0x01UL << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_1           (0x02UL << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_2           (0x04UL << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_3           (0x08UL << ADC_SQR2_SQ12_Pos)
#define ADC_SQR2_SQ12_4           (0x10UL << ADC_SQR2_SQ12_Pos)

#define ADC_SQR3_SQ1_Pos          (0U)
#define ADC_SQR3_SQ1_Msk          (0x1FUL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1              ADC_SQR3_SQ1_Msk
#define ADC_SQR3_SQ1_0            (0x01UL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_1            (0x02UL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_2            (0x04UL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_3            (0x08UL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ1_4            (0x10UL << ADC_SQR3_SQ1_Pos)
#define ADC_SQR3_SQ2_Pos          (5U)
#define ADC_SQR3_SQ2_Msk          (0x1FUL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2              ADC_SQR3_SQ2_Msk
#define ADC_SQR3_SQ2_0            (0x01UL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_1            (0x02UL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_2            (0x04UL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_3            (0x08UL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ2_4            (0x10UL << ADC_SQR3_SQ2_Pos)
#define ADC_SQR3_SQ3_Pos          (10U)
#define ADC_SQR3_SQ3_Msk          (0x1FUL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3              ADC_SQR3_SQ3_Msk
#define ADC_SQR3_SQ3_0            (0x01UL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_1            (0x02UL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_2            (0x04UL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_3            (0x08UL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ3_4            (0x10UL << ADC_SQR3_SQ3_Pos)
#define ADC_SQR3_SQ4_Pos          (15U)
#define ADC_SQR3_SQ4_Msk          (0x1FUL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4              ADC_SQR3_SQ4_Msk
#define ADC_SQR3_SQ4_0            (0x01UL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_1            (0x02UL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_2            (0x04UL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_3            (0x08UL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ4_4            (0x10UL << ADC_SQR3_SQ4_Pos)
#define ADC_SQR3_SQ5_Pos          (20U)
#define ADC_SQR3_SQ5_Msk          (0x1FUL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5              ADC_SQR3_SQ5_Msk
#define ADC_SQR3_SQ5_0            (0x01UL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_1            (0x02UL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_2            (0x04UL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_3            (0x08UL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ5_4            (0x10UL << ADC_SQR3_SQ5_Pos)
#define ADC_SQR3_SQ6_Pos          (25U)
#define ADC_SQR3_SQ6_Msk          (0x1FUL << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6              ADC_SQR3_SQ6_Msk
#define ADC_SQR3_SQ6_0            (0x01UL << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_1            (0x02UL << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_2            (0x04UL << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_3            (0x08UL << ADC_SQR3_SQ6_Pos)
#define ADC_SQR3_SQ6_4            (0x10UL << ADC_SQR3_SQ6_Pos)

#define ADC_JSQR_JSQ1_Pos         (0U)
#define ADC_JSQR_JSQ1_Msk         (0x1FUL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1             ADC_JSQR_JSQ1_Msk
#define ADC_JSQR_JSQ1_0           (0x01UL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_1           (0x02UL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_2           (0x04UL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_3           (0x08UL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ1_4           (0x10UL << ADC_JSQR_JSQ1_Pos)
#define ADC_JSQR_JSQ2_Pos         (5U)
#define ADC_JSQR_JSQ2_Msk         (0x1FUL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2             ADC_JSQR_JSQ2_Msk
#define ADC_JSQR_JSQ2_0           (0x01UL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_1           (0x02UL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_2           (0x04UL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_3           (0x08UL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ2_4           (0x10UL << ADC_JSQR_JSQ2_Pos)
#define ADC_JSQR_JSQ3_Pos         (10U)
#define ADC_JSQR_JSQ3_Msk         (0x1FUL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3             ADC_JSQR_JSQ3_Msk
#define ADC_JSQR_JSQ3_0           (0x01UL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_1           (0x02UL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_2           (0x04UL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_3           (0x08UL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ3_4           (0x10UL << ADC_JSQR_JSQ3_Pos)
#define ADC_JSQR_JSQ4_Pos         (15U)
#define ADC_JSQR_JSQ4_Msk         (0x1FUL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4             ADC_JSQR_JSQ4_Msk
#define ADC_JSQR_JSQ4_0           (0x01UL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_1           (0x02UL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_2           (0x04UL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_3           (0x08UL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JSQ4_4           (0x10UL << ADC_JSQR_JSQ4_Pos)
#define ADC_JSQR_JL_Pos           (20U)
#define ADC_JSQR_JL_Msk           (0x3UL << ADC_JSQR_JL_Pos)
#define ADC_JSQR_JL               ADC_JSQR_JL_Msk
#define ADC_JSQR_JL_0             (0x1UL << ADC_JSQR_JL_Pos)
#define ADC_JSQR_JL_1             (0x2UL << ADC_JSQR_JL_Pos)

#define ADC_JDR1_JDATA_Pos        (0U)
#define ADC_JDR1_JDATA_Msk        (0xFFFFUL << ADC_JDR1_JDATA_Pos)
#define ADC_JDR1_JDATA            ADC_JDR1_JDATA_Msk

#define ADC_JDR2_JDATA_Pos        (0U)
#define ADC_JDR2_JDATA_Msk        (0xFFFFUL << ADC_JDR2_JDATA_Pos)
#define ADC_JDR2_JDATA            ADC_JDR2_JDATA_Msk

#define ADC_JDR3_JDATA_Pos        (0U)
#define ADC_JDR3_JDATA_Msk        (0xFFFFUL << ADC_JDR3_JDATA_Pos)
#define ADC_JDR3_JDATA            ADC_JDR3_JDATA_Msk

#define ADC_JDR4_JDATA_Pos        (0U)
#define ADC_JDR4_JDATA_Msk        (0xFFFFUL << ADC_JDR4_JDATA_Pos)
#define ADC_JDR4_JDATA            ADC_JDR4_JDATA_Msk

#define ADC_DR_DATA_Pos           (0U)
#define ADC_DR_DATA_Msk           (0xFFFFUL << ADC_DR_DATA_Pos)
#define ADC_DR_DATA               ADC_DR_DATA_Msk
#define ADC_DR_ADC2DATA_Pos       (16U)
#define ADC_DR_ADC2DATA_Msk       (0xFFFFUL << ADC_DR_ADC2DATA_Pos)
#define ADC_DR_ADC2DATA           ADC_DR_ADC2DATA_Msk

#define ADC_CSR_AWD1_Pos          (0U)
#define ADC_CSR_AWD1_Msk          (0x1UL << ADC_CSR_AWD1_Pos)
#define ADC_CSR_AWD1              ADC_CSR_AWD1_Msk
#define ADC_CSR_EOC1_Pos          (1U)
#define ADC_CSR_EOC1_Msk          (0x1UL << ADC_CSR_EOC1_Pos)
#define ADC_CSR_EOC1              ADC_CSR_EOC1_Msk
#define ADC_CSR_JEOC1_Pos         (2U)
#define ADC_CSR_JEOC1_Msk         (0x1UL << ADC_CSR_JEOC1_Pos)
#define ADC_CSR_JEOC1             ADC_CSR_JEOC1_Msk
#define ADC_CSR_JSTRT1_Pos        (3U)
#define ADC_CSR_JSTRT1_Msk        (0x1UL << ADC_CSR_JSTRT1_Pos)
#define ADC_CSR_JSTRT1            ADC_CSR_JSTRT1_Msk
#define ADC_CSR_STRT1_Pos         (4U)
#define ADC_CSR_STRT1_Msk         (0x1UL << ADC_CSR_STRT1_Pos)
#define ADC_CSR_STRT1             ADC_CSR_STRT1_Msk
#define ADC_CSR_OVR1_Pos          (5U)
#define ADC_CSR_OVR1_Msk          (0x1UL << ADC_CSR_OVR1_Pos)
#define ADC_CSR_OVR1              ADC_CSR_OVR1_Msk

#define  ADC_CSR_DOVR1                        ADC_CSR_OVR1

#define ADC_CCR_MULTI_Pos         (0U)
#define ADC_CCR_MULTI_Msk         (0x1FUL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_MULTI             ADC_CCR_MULTI_Msk
#define ADC_CCR_MULTI_0           (0x01UL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_MULTI_1           (0x02UL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_MULTI_2           (0x04UL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_MULTI_3           (0x08UL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_MULTI_4           (0x10UL << ADC_CCR_MULTI_Pos)
#define ADC_CCR_DELAY_Pos         (8U)
#define ADC_CCR_DELAY_Msk         (0xFUL << ADC_CCR_DELAY_Pos)
#define ADC_CCR_DELAY             ADC_CCR_DELAY_Msk
#define ADC_CCR_DELAY_0           (0x1UL << ADC_CCR_DELAY_Pos)
#define ADC_CCR_DELAY_1           (0x2UL << ADC_CCR_DELAY_Pos)
#define ADC_CCR_DELAY_2           (0x4UL << ADC_CCR_DELAY_Pos)
#define ADC_CCR_DELAY_3           (0x8UL << ADC_CCR_DELAY_Pos)
#define ADC_CCR_DDS_Pos           (13U)
#define ADC_CCR_DDS_Msk           (0x1UL << ADC_CCR_DDS_Pos)
#define ADC_CCR_DDS               ADC_CCR_DDS_Msk
#define ADC_CCR_DMA_Pos           (14U)
#define ADC_CCR_DMA_Msk           (0x3UL << ADC_CCR_DMA_Pos)
#define ADC_CCR_DMA               ADC_CCR_DMA_Msk
#define ADC_CCR_DMA_0             (0x1UL << ADC_CCR_DMA_Pos)
#define ADC_CCR_DMA_1             (0x2UL << ADC_CCR_DMA_Pos)
#define ADC_CCR_ADCPRE_Pos        (16U)
#define ADC_CCR_ADCPRE_Msk        (0x3UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_ADCPRE            ADC_CCR_ADCPRE_Msk
#define ADC_CCR_ADCPRE_0          (0x1UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_ADCPRE_1          (0x2UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CCR_VBATE_Pos         (22U)
#define ADC_CCR_VBATE_Msk         (0x1UL << ADC_CCR_VBATE_Pos)
#define ADC_CCR_VBATE             ADC_CCR_VBATE_Msk
#define ADC_CCR_TSVREFE_Pos       (23U)
#define ADC_CCR_TSVREFE_Msk       (0x1UL << ADC_CCR_TSVREFE_Pos)
#define ADC_CCR_TSVREFE           ADC_CCR_TSVREFE_Msk

#define ADC_CDR_DATA1_Pos         (0U)
#define ADC_CDR_DATA1_Msk         (0xFFFFUL << ADC_CDR_DATA1_Pos)
#define ADC_CDR_DATA1             ADC_CDR_DATA1_Msk
#define ADC_CDR_DATA2_Pos         (16U)
#define ADC_CDR_DATA2_Msk         (0xFFFFUL << ADC_CDR_DATA2_Pos)
#define ADC_CDR_DATA2             ADC_CDR_DATA2_Msk

#define ADC_CDR_RDATA_MST         ADC_CDR_DATA1
#define ADC_CDR_RDATA_SLV         ADC_CDR_DATA2

#define CRC_DR_DR_Pos       (0U)
#define CRC_DR_DR_Msk       (0xFFFFFFFFUL << CRC_DR_DR_Pos)
#define CRC_DR_DR           CRC_DR_DR_Msk

#define CRC_IDR_IDR_Pos     (0U)
#define CRC_IDR_IDR_Msk     (0xFFUL << CRC_IDR_IDR_Pos)
#define CRC_IDR_IDR         CRC_IDR_IDR_Msk

#define CRC_CR_RESET_Pos    (0U)
#define CRC_CR_RESET_Msk    (0x1UL << CRC_CR_RESET_Pos)
#define CRC_CR_RESET        CRC_CR_RESET_Msk

#define DMA_SxCR_CHSEL_Pos       (25U)
#define DMA_SxCR_CHSEL_Msk       (0x7UL << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL           DMA_SxCR_CHSEL_Msk
#define DMA_SxCR_CHSEL_0         (0x1UL << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_1         (0x2UL << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_CHSEL_2         (0x4UL << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_MBURST_Pos      (23U)
#define DMA_SxCR_MBURST_Msk      (0x3UL << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_MBURST          DMA_SxCR_MBURST_Msk
#define DMA_SxCR_MBURST_0        (0x1UL << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_MBURST_1        (0x2UL << DMA_SxCR_MBURST_Pos)
#define DMA_SxCR_PBURST_Pos      (21U)
#define DMA_SxCR_PBURST_Msk      (0x3UL << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PBURST          DMA_SxCR_PBURST_Msk
#define DMA_SxCR_PBURST_0        (0x1UL << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_PBURST_1        (0x2UL << DMA_SxCR_PBURST_Pos)
#define DMA_SxCR_CT_Pos          (19U)
#define DMA_SxCR_CT_Msk          (0x1UL << DMA_SxCR_CT_Pos)
#define DMA_SxCR_CT              DMA_SxCR_CT_Msk
#define DMA_SxCR_DBM_Pos         (18U)
#define DMA_SxCR_DBM_Msk         (0x1UL << DMA_SxCR_DBM_Pos)
#define DMA_SxCR_DBM             DMA_SxCR_DBM_Msk
#define DMA_SxCR_PL_Pos          (16U)
#define DMA_SxCR_PL_Msk          (0x3UL << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PL              DMA_SxCR_PL_Msk
#define DMA_SxCR_PL_0            (0x1UL << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PL_1            (0x2UL << DMA_SxCR_PL_Pos)
#define DMA_SxCR_PINCOS_Pos      (15U)
#define DMA_SxCR_PINCOS_Msk      (0x1UL << DMA_SxCR_PINCOS_Pos)
#define DMA_SxCR_PINCOS          DMA_SxCR_PINCOS_Msk
#define DMA_SxCR_MSIZE_Pos       (13U)
#define DMA_SxCR_MSIZE_Msk       (0x3UL << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_MSIZE           DMA_SxCR_MSIZE_Msk
#define DMA_SxCR_MSIZE_0         (0x1UL << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_MSIZE_1         (0x2UL << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_PSIZE_Pos       (11U)
#define DMA_SxCR_PSIZE_Msk       (0x3UL << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_PSIZE           DMA_SxCR_PSIZE_Msk
#define DMA_SxCR_PSIZE_0         (0x1UL << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_PSIZE_1         (0x2UL << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_MINC_Pos        (10U)
#define DMA_SxCR_MINC_Msk        (0x1UL << DMA_SxCR_MINC_Pos)
#define DMA_SxCR_MINC            DMA_SxCR_MINC_Msk
#define DMA_SxCR_PINC_Pos        (9U)
#define DMA_SxCR_PINC_Msk        (0x1UL << DMA_SxCR_PINC_Pos)
#define DMA_SxCR_PINC            DMA_SxCR_PINC_Msk
#define DMA_SxCR_CIRC_Pos        (8U)
#define DMA_SxCR_CIRC_Msk        (0x1UL << DMA_SxCR_CIRC_Pos)
#define DMA_SxCR_CIRC            DMA_SxCR_CIRC_Msk
#define DMA_SxCR_DIR_Pos         (6U)
#define DMA_SxCR_DIR_Msk         (0x3UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR             DMA_SxCR_DIR_Msk
#define DMA_SxCR_DIR_0           (0x1UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_DIR_1           (0x2UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_PFCTRL_Pos      (5U)
#define DMA_SxCR_PFCTRL_Msk      (0x1UL << DMA_SxCR_PFCTRL_Pos)
#define DMA_SxCR_PFCTRL          DMA_SxCR_PFCTRL_Msk
#define DMA_SxCR_TCIE_Pos        (4U)
#define DMA_SxCR_TCIE_Msk        (0x1UL << DMA_SxCR_TCIE_Pos)
#define DMA_SxCR_TCIE            DMA_SxCR_TCIE_Msk
#define DMA_SxCR_HTIE_Pos        (3U)
#define DMA_SxCR_HTIE_Msk        (0x1UL << DMA_SxCR_HTIE_Pos)
#define DMA_SxCR_HTIE            DMA_SxCR_HTIE_Msk
#define DMA_SxCR_TEIE_Pos        (2U)
#define DMA_SxCR_TEIE_Msk        (0x1UL << DMA_SxCR_TEIE_Pos)
#define DMA_SxCR_TEIE            DMA_SxCR_TEIE_Msk
#define DMA_SxCR_DMEIE_Pos       (1U)
#define DMA_SxCR_DMEIE_Msk       (0x1UL << DMA_SxCR_DMEIE_Pos)
#define DMA_SxCR_DMEIE           DMA_SxCR_DMEIE_Msk
#define DMA_SxCR_EN_Pos          (0U)
#define DMA_SxCR_EN_Msk          (0x1UL << DMA_SxCR_EN_Pos)
#define DMA_SxCR_EN              DMA_SxCR_EN_Msk

#define DMA_SxCR_ACK_Pos         (20U)
#define DMA_SxCR_ACK_Msk         (0x1UL << DMA_SxCR_ACK_Pos)
#define DMA_SxCR_ACK             DMA_SxCR_ACK_Msk

#define DMA_SxNDT_Pos            (0U)
#define DMA_SxNDT_Msk            (0xFFFFUL << DMA_SxNDT_Pos)
#define DMA_SxNDT                DMA_SxNDT_Msk
#define DMA_SxNDT_0              (0x0001UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_1              (0x0002UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_2              (0x0004UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_3              (0x0008UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_4              (0x0010UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_5              (0x0020UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_6              (0x0040UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_7              (0x0080UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_8              (0x0100UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_9              (0x0200UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_10             (0x0400UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_11             (0x0800UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_12             (0x1000UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_13             (0x2000UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_14             (0x4000UL << DMA_SxNDT_Pos)
#define DMA_SxNDT_15             (0x8000UL << DMA_SxNDT_Pos)

#define DMA_SxFCR_FEIE_Pos       (7U)
#define DMA_SxFCR_FEIE_Msk       (0x1UL << DMA_SxFCR_FEIE_Pos)
#define DMA_SxFCR_FEIE           DMA_SxFCR_FEIE_Msk
#define DMA_SxFCR_FS_Pos         (3U)
#define DMA_SxFCR_FS_Msk         (0x7UL << DMA_SxFCR_FS_Pos)
#define DMA_SxFCR_FS             DMA_SxFCR_FS_Msk
#define DMA_SxFCR_FS_0           (0x1UL << DMA_SxFCR_FS_Pos)
#define DMA_SxFCR_FS_1           (0x2UL << DMA_SxFCR_FS_Pos)
#define DMA_SxFCR_FS_2           (0x4UL << DMA_SxFCR_FS_Pos)
#define DMA_SxFCR_DMDIS_Pos      (2U)
#define DMA_SxFCR_DMDIS_Msk      (0x1UL << DMA_SxFCR_DMDIS_Pos)
#define DMA_SxFCR_DMDIS          DMA_SxFCR_DMDIS_Msk
#define DMA_SxFCR_FTH_Pos        (0U)
#define DMA_SxFCR_FTH_Msk        (0x3UL << DMA_SxFCR_FTH_Pos)
#define DMA_SxFCR_FTH            DMA_SxFCR_FTH_Msk
#define DMA_SxFCR_FTH_0          (0x1UL << DMA_SxFCR_FTH_Pos)
#define DMA_SxFCR_FTH_1          (0x2UL << DMA_SxFCR_FTH_Pos)

#define DMA_LISR_TCIF3_Pos       (27U)
#define DMA_LISR_TCIF3_Msk       (0x1UL << DMA_LISR_TCIF3_Pos)
#define DMA_LISR_TCIF3           DMA_LISR_TCIF3_Msk
#define DMA_LISR_HTIF3_Pos       (26U)
#define DMA_LISR_HTIF3_Msk       (0x1UL << DMA_LISR_HTIF3_Pos)
#define DMA_LISR_HTIF3           DMA_LISR_HTIF3_Msk
#define DMA_LISR_TEIF3_Pos       (25U)
#define DMA_LISR_TEIF3_Msk       (0x1UL << DMA_LISR_TEIF3_Pos)
#define DMA_LISR_TEIF3           DMA_LISR_TEIF3_Msk
#define DMA_LISR_DMEIF3_Pos      (24U)
#define DMA_LISR_DMEIF3_Msk      (0x1UL << DMA_LISR_DMEIF3_Pos)
#define DMA_LISR_DMEIF3          DMA_LISR_DMEIF3_Msk
#define DMA_LISR_FEIF3_Pos       (22U)
#define DMA_LISR_FEIF3_Msk       (0x1UL << DMA_LISR_FEIF3_Pos)
#define DMA_LISR_FEIF3           DMA_LISR_FEIF3_Msk
#define DMA_LISR_TCIF2_Pos       (21U)
#define DMA_LISR_TCIF2_Msk       (0x1UL << DMA_LISR_TCIF2_Pos)
#define DMA_LISR_TCIF2           DMA_LISR_TCIF2_Msk
#define DMA_LISR_HTIF2_Pos       (20U)
#define DMA_LISR_HTIF2_Msk       (0x1UL << DMA_LISR_HTIF2_Pos)
#define DMA_LISR_HTIF2           DMA_LISR_HTIF2_Msk
#define DMA_LISR_TEIF2_Pos       (19U)
#define DMA_LISR_TEIF2_Msk       (0x1UL << DMA_LISR_TEIF2_Pos)
#define DMA_LISR_TEIF2           DMA_LISR_TEIF2_Msk
#define DMA_LISR_DMEIF2_Pos      (18U)
#define DMA_LISR_DMEIF2_Msk      (0x1UL << DMA_LISR_DMEIF2_Pos)
#define DMA_LISR_DMEIF2          DMA_LISR_DMEIF2_Msk
#define DMA_LISR_FEIF2_Pos       (16U)
#define DMA_LISR_FEIF2_Msk       (0x1UL << DMA_LISR_FEIF2_Pos)
#define DMA_LISR_FEIF2           DMA_LISR_FEIF2_Msk
#define DMA_LISR_TCIF1_Pos       (11U)
#define DMA_LISR_TCIF1_Msk       (0x1UL << DMA_LISR_TCIF1_Pos)
#define DMA_LISR_TCIF1           DMA_LISR_TCIF1_Msk
#define DMA_LISR_HTIF1_Pos       (10U)
#define DMA_LISR_HTIF1_Msk       (0x1UL << DMA_LISR_HTIF1_Pos)
#define DMA_LISR_HTIF1           DMA_LISR_HTIF1_Msk
#define DMA_LISR_TEIF1_Pos       (9U)
#define DMA_LISR_TEIF1_Msk       (0x1UL << DMA_LISR_TEIF1_Pos)
#define DMA_LISR_TEIF1           DMA_LISR_TEIF1_Msk
#define DMA_LISR_DMEIF1_Pos      (8U)
#define DMA_LISR_DMEIF1_Msk      (0x1UL << DMA_LISR_DMEIF1_Pos)
#define DMA_LISR_DMEIF1          DMA_LISR_DMEIF1_Msk
#define DMA_LISR_FEIF1_Pos       (6U)
#define DMA_LISR_FEIF1_Msk       (0x1UL << DMA_LISR_FEIF1_Pos)
#define DMA_LISR_FEIF1           DMA_LISR_FEIF1_Msk
#define DMA_LISR_TCIF0_Pos       (5U)
#define DMA_LISR_TCIF0_Msk       (0x1UL << DMA_LISR_TCIF0_Pos)
#define DMA_LISR_TCIF0           DMA_LISR_TCIF0_Msk
#define DMA_LISR_HTIF0_Pos       (4U)
#define DMA_LISR_HTIF0_Msk       (0x1UL << DMA_LISR_HTIF0_Pos)
#define DMA_LISR_HTIF0           DMA_LISR_HTIF0_Msk
#define DMA_LISR_TEIF0_Pos       (3U)
#define DMA_LISR_TEIF0_Msk       (0x1UL << DMA_LISR_TEIF0_Pos)
#define DMA_LISR_TEIF0           DMA_LISR_TEIF0_Msk
#define DMA_LISR_DMEIF0_Pos      (2U)
#define DMA_LISR_DMEIF0_Msk      (0x1UL << DMA_LISR_DMEIF0_Pos)
#define DMA_LISR_DMEIF0          DMA_LISR_DMEIF0_Msk
#define DMA_LISR_FEIF0_Pos       (0U)
#define DMA_LISR_FEIF0_Msk       (0x1UL << DMA_LISR_FEIF0_Pos)
#define DMA_LISR_FEIF0           DMA_LISR_FEIF0_Msk

#define DMA_HISR_TCIF7_Pos       (27U)
#define DMA_HISR_TCIF7_Msk       (0x1UL << DMA_HISR_TCIF7_Pos)
#define DMA_HISR_TCIF7           DMA_HISR_TCIF7_Msk
#define DMA_HISR_HTIF7_Pos       (26U)
#define DMA_HISR_HTIF7_Msk       (0x1UL << DMA_HISR_HTIF7_Pos)
#define DMA_HISR_HTIF7           DMA_HISR_HTIF7_Msk
#define DMA_HISR_TEIF7_Pos       (25U)
#define DMA_HISR_TEIF7_Msk       (0x1UL << DMA_HISR_TEIF7_Pos)
#define DMA_HISR_TEIF7           DMA_HISR_TEIF7_Msk
#define DMA_HISR_DMEIF7_Pos      (24U)
#define DMA_HISR_DMEIF7_Msk      (0x1UL << DMA_HISR_DMEIF7_Pos)
#define DMA_HISR_DMEIF7          DMA_HISR_DMEIF7_Msk
#define DMA_HISR_FEIF7_Pos       (22U)
#define DMA_HISR_FEIF7_Msk       (0x1UL << DMA_HISR_FEIF7_Pos)
#define DMA_HISR_FEIF7           DMA_HISR_FEIF7_Msk
#define DMA_HISR_TCIF6_Pos       (21U)
#define DMA_HISR_TCIF6_Msk       (0x1UL << DMA_HISR_TCIF6_Pos)
#define DMA_HISR_TCIF6           DMA_HISR_TCIF6_Msk
#define DMA_HISR_HTIF6_Pos       (20U)
#define DMA_HISR_HTIF6_Msk       (0x1UL << DMA_HISR_HTIF6_Pos)
#define DMA_HISR_HTIF6           DMA_HISR_HTIF6_Msk
#define DMA_HISR_TEIF6_Pos       (19U)
#define DMA_HISR_TEIF6_Msk       (0x1UL << DMA_HISR_TEIF6_Pos)
#define DMA_HISR_TEIF6           DMA_HISR_TEIF6_Msk
#define DMA_HISR_DMEIF6_Pos      (18U)
#define DMA_HISR_DMEIF6_Msk      (0x1UL << DMA_HISR_DMEIF6_Pos)
#define DMA_HISR_DMEIF6          DMA_HISR_DMEIF6_Msk
#define DMA_HISR_FEIF6_Pos       (16U)
#define DMA_HISR_FEIF6_Msk       (0x1UL << DMA_HISR_FEIF6_Pos)
#define DMA_HISR_FEIF6           DMA_HISR_FEIF6_Msk
#define DMA_HISR_TCIF5_Pos       (11U)
#define DMA_HISR_TCIF5_Msk       (0x1UL << DMA_HISR_TCIF5_Pos)
#define DMA_HISR_TCIF5           DMA_HISR_TCIF5_Msk
#define DMA_HISR_HTIF5_Pos       (10U)
#define DMA_HISR_HTIF5_Msk       (0x1UL << DMA_HISR_HTIF5_Pos)
#define DMA_HISR_HTIF5           DMA_HISR_HTIF5_Msk
#define DMA_HISR_TEIF5_Pos       (9U)
#define DMA_HISR_TEIF5_Msk       (0x1UL << DMA_HISR_TEIF5_Pos)
#define DMA_HISR_TEIF5           DMA_HISR_TEIF5_Msk
#define DMA_HISR_DMEIF5_Pos      (8U)
#define DMA_HISR_DMEIF5_Msk      (0x1UL << DMA_HISR_DMEIF5_Pos)
#define DMA_HISR_DMEIF5          DMA_HISR_DMEIF5_Msk
#define DMA_HISR_FEIF5_Pos       (6U)
#define DMA_HISR_FEIF5_Msk       (0x1UL << DMA_HISR_FEIF5_Pos)
#define DMA_HISR_FEIF5           DMA_HISR_FEIF5_Msk
#define DMA_HISR_TCIF4_Pos       (5U)
#define DMA_HISR_TCIF4_Msk       (0x1UL << DMA_HISR_TCIF4_Pos)
#define DMA_HISR_TCIF4           DMA_HISR_TCIF4_Msk
#define DMA_HISR_HTIF4_Pos       (4U)
#define DMA_HISR_HTIF4_Msk       (0x1UL << DMA_HISR_HTIF4_Pos)
#define DMA_HISR_HTIF4           DMA_HISR_HTIF4_Msk
#define DMA_HISR_TEIF4_Pos       (3U)
#define DMA_HISR_TEIF4_Msk       (0x1UL << DMA_HISR_TEIF4_Pos)
#define DMA_HISR_TEIF4           DMA_HISR_TEIF4_Msk
#define DMA_HISR_DMEIF4_Pos      (2U)
#define DMA_HISR_DMEIF4_Msk      (0x1UL << DMA_HISR_DMEIF4_Pos)
#define DMA_HISR_DMEIF4          DMA_HISR_DMEIF4_Msk
#define DMA_HISR_FEIF4_Pos       (0U)
#define DMA_HISR_FEIF4_Msk       (0x1UL << DMA_HISR_FEIF4_Pos)
#define DMA_HISR_FEIF4           DMA_HISR_FEIF4_Msk

#define DMA_LIFCR_CTCIF3_Pos     (27U)
#define DMA_LIFCR_CTCIF3_Msk     (0x1UL << DMA_LIFCR_CTCIF3_Pos)
#define DMA_LIFCR_CTCIF3         DMA_LIFCR_CTCIF3_Msk
#define DMA_LIFCR_CHTIF3_Pos     (26U)
#define DMA_LIFCR_CHTIF3_Msk     (0x1UL << DMA_LIFCR_CHTIF3_Pos)
#define DMA_LIFCR_CHTIF3         DMA_LIFCR_CHTIF3_Msk
#define DMA_LIFCR_CTEIF3_Pos     (25U)
#define DMA_LIFCR_CTEIF3_Msk     (0x1UL << DMA_LIFCR_CTEIF3_Pos)
#define DMA_LIFCR_CTEIF3         DMA_LIFCR_CTEIF3_Msk
#define DMA_LIFCR_CDMEIF3_Pos    (24U)
#define DMA_LIFCR_CDMEIF3_Msk    (0x1UL << DMA_LIFCR_CDMEIF3_Pos)
#define DMA_LIFCR_CDMEIF3        DMA_LIFCR_CDMEIF3_Msk
#define DMA_LIFCR_CFEIF3_Pos     (22U)
#define DMA_LIFCR_CFEIF3_Msk     (0x1UL << DMA_LIFCR_CFEIF3_Pos)
#define DMA_LIFCR_CFEIF3         DMA_LIFCR_CFEIF3_Msk
#define DMA_LIFCR_CTCIF2_Pos     (21U)
#define DMA_LIFCR_CTCIF2_Msk     (0x1UL << DMA_LIFCR_CTCIF2_Pos)
#define DMA_LIFCR_CTCIF2         DMA_LIFCR_CTCIF2_Msk
#define DMA_LIFCR_CHTIF2_Pos     (20U)
#define DMA_LIFCR_CHTIF2_Msk     (0x1UL << DMA_LIFCR_CHTIF2_Pos)
#define DMA_LIFCR_CHTIF2         DMA_LIFCR_CHTIF2_Msk
#define DMA_LIFCR_CTEIF2_Pos     (19U)
#define DMA_LIFCR_CTEIF2_Msk     (0x1UL << DMA_LIFCR_CTEIF2_Pos)
#define DMA_LIFCR_CTEIF2         DMA_LIFCR_CTEIF2_Msk
#define DMA_LIFCR_CDMEIF2_Pos    (18U)
#define DMA_LIFCR_CDMEIF2_Msk    (0x1UL << DMA_LIFCR_CDMEIF2_Pos)
#define DMA_LIFCR_CDMEIF2        DMA_LIFCR_CDMEIF2_Msk
#define DMA_LIFCR_CFEIF2_Pos     (16U)
#define DMA_LIFCR_CFEIF2_Msk     (0x1UL << DMA_LIFCR_CFEIF2_Pos)
#define DMA_LIFCR_CFEIF2         DMA_LIFCR_CFEIF2_Msk
#define DMA_LIFCR_CTCIF1_Pos     (11U)
#define DMA_LIFCR_CTCIF1_Msk     (0x1UL << DMA_LIFCR_CTCIF1_Pos)
#define DMA_LIFCR_CTCIF1         DMA_LIFCR_CTCIF1_Msk
#define DMA_LIFCR_CHTIF1_Pos     (10U)
#define DMA_LIFCR_CHTIF1_Msk     (0x1UL << DMA_LIFCR_CHTIF1_Pos)
#define DMA_LIFCR_CHTIF1         DMA_LIFCR_CHTIF1_Msk
#define DMA_LIFCR_CTEIF1_Pos     (9U)
#define DMA_LIFCR_CTEIF1_Msk     (0x1UL << DMA_LIFCR_CTEIF1_Pos)
#define DMA_LIFCR_CTEIF1         DMA_LIFCR_CTEIF1_Msk
#define DMA_LIFCR_CDMEIF1_Pos    (8U)
#define DMA_LIFCR_CDMEIF1_Msk    (0x1UL << DMA_LIFCR_CDMEIF1_Pos)
#define DMA_LIFCR_CDMEIF1        DMA_LIFCR_CDMEIF1_Msk
#define DMA_LIFCR_CFEIF1_Pos     (6U)
#define DMA_LIFCR_CFEIF1_Msk     (0x1UL << DMA_LIFCR_CFEIF1_Pos)
#define DMA_LIFCR_CFEIF1         DMA_LIFCR_CFEIF1_Msk
#define DMA_LIFCR_CTCIF0_Pos     (5U)
#define DMA_LIFCR_CTCIF0_Msk     (0x1UL << DMA_LIFCR_CTCIF0_Pos)
#define DMA_LIFCR_CTCIF0         DMA_LIFCR_CTCIF0_Msk
#define DMA_LIFCR_CHTIF0_Pos     (4U)
#define DMA_LIFCR_CHTIF0_Msk     (0x1UL << DMA_LIFCR_CHTIF0_Pos)
#define DMA_LIFCR_CHTIF0         DMA_LIFCR_CHTIF0_Msk
#define DMA_LIFCR_CTEIF0_Pos     (3U)
#define DMA_LIFCR_CTEIF0_Msk     (0x1UL << DMA_LIFCR_CTEIF0_Pos)
#define DMA_LIFCR_CTEIF0         DMA_LIFCR_CTEIF0_Msk
#define DMA_LIFCR_CDMEIF0_Pos    (2U)
#define DMA_LIFCR_CDMEIF0_Msk    (0x1UL << DMA_LIFCR_CDMEIF0_Pos)
#define DMA_LIFCR_CDMEIF0        DMA_LIFCR_CDMEIF0_Msk
#define DMA_LIFCR_CFEIF0_Pos     (0U)
#define DMA_LIFCR_CFEIF0_Msk     (0x1UL << DMA_LIFCR_CFEIF0_Pos)
#define DMA_LIFCR_CFEIF0         DMA_LIFCR_CFEIF0_Msk

#define DMA_HIFCR_CTCIF7_Pos     (27U)
#define DMA_HIFCR_CTCIF7_Msk     (0x1UL << DMA_HIFCR_CTCIF7_Pos)
#define DMA_HIFCR_CTCIF7         DMA_HIFCR_CTCIF7_Msk
#define DMA_HIFCR_CHTIF7_Pos     (26U)
#define DMA_HIFCR_CHTIF7_Msk     (0x1UL << DMA_HIFCR_CHTIF7_Pos)
#define DMA_HIFCR_CHTIF7         DMA_HIFCR_CHTIF7_Msk
#define DMA_HIFCR_CTEIF7_Pos     (25U)
#define DMA_HIFCR_CTEIF7_Msk     (0x1UL << DMA_HIFCR_CTEIF7_Pos)
#define DMA_HIFCR_CTEIF7         DMA_HIFCR_CTEIF7_Msk
#define DMA_HIFCR_CDMEIF7_Pos    (24U)
#define DMA_HIFCR_CDMEIF7_Msk    (0x1UL << DMA_HIFCR_CDMEIF7_Pos)
#define DMA_HIFCR_CDMEIF7        DMA_HIFCR_CDMEIF7_Msk
#define DMA_HIFCR_CFEIF7_Pos     (22U)
#define DMA_HIFCR_CFEIF7_Msk     (0x1UL << DMA_HIFCR_CFEIF7_Pos)
#define DMA_HIFCR_CFEIF7         DMA_HIFCR_CFEIF7_Msk
#define DMA_HIFCR_CTCIF6_Pos     (21U)
#define DMA_HIFCR_CTCIF6_Msk     (0x1UL << DMA_HIFCR_CTCIF6_Pos)
#define DMA_HIFCR_CTCIF6         DMA_HIFCR_CTCIF6_Msk
#define DMA_HIFCR_CHTIF6_Pos     (20U)
#define DMA_HIFCR_CHTIF6_Msk     (0x1UL << DMA_HIFCR_CHTIF6_Pos)
#define DMA_HIFCR_CHTIF6         DMA_HIFCR_CHTIF6_Msk
#define DMA_HIFCR_CTEIF6_Pos     (19U)
#define DMA_HIFCR_CTEIF6_Msk     (0x1UL << DMA_HIFCR_CTEIF6_Pos)
#define DMA_HIFCR_CTEIF6         DMA_HIFCR_CTEIF6_Msk
#define DMA_HIFCR_CDMEIF6_Pos    (18U)
#define DMA_HIFCR_CDMEIF6_Msk    (0x1UL << DMA_HIFCR_CDMEIF6_Pos)
#define DMA_HIFCR_CDMEIF6        DMA_HIFCR_CDMEIF6_Msk
#define DMA_HIFCR_CFEIF6_Pos     (16U)
#define DMA_HIFCR_CFEIF6_Msk     (0x1UL << DMA_HIFCR_CFEIF6_Pos)
#define DMA_HIFCR_CFEIF6         DMA_HIFCR_CFEIF6_Msk
#define DMA_HIFCR_CTCIF5_Pos     (11U)
#define DMA_HIFCR_CTCIF5_Msk     (0x1UL << DMA_HIFCR_CTCIF5_Pos)
#define DMA_HIFCR_CTCIF5         DMA_HIFCR_CTCIF5_Msk
#define DMA_HIFCR_CHTIF5_Pos     (10U)
#define DMA_HIFCR_CHTIF5_Msk     (0x1UL << DMA_HIFCR_CHTIF5_Pos)
#define DMA_HIFCR_CHTIF5         DMA_HIFCR_CHTIF5_Msk
#define DMA_HIFCR_CTEIF5_Pos     (9U)
#define DMA_HIFCR_CTEIF5_Msk     (0x1UL << DMA_HIFCR_CTEIF5_Pos)
#define DMA_HIFCR_CTEIF5         DMA_HIFCR_CTEIF5_Msk
#define DMA_HIFCR_CDMEIF5_Pos    (8U)
#define DMA_HIFCR_CDMEIF5_Msk    (0x1UL << DMA_HIFCR_CDMEIF5_Pos)
#define DMA_HIFCR_CDMEIF5        DMA_HIFCR_CDMEIF5_Msk
#define DMA_HIFCR_CFEIF5_Pos     (6U)
#define DMA_HIFCR_CFEIF5_Msk     (0x1UL << DMA_HIFCR_CFEIF5_Pos)
#define DMA_HIFCR_CFEIF5         DMA_HIFCR_CFEIF5_Msk
#define DMA_HIFCR_CTCIF4_Pos     (5U)
#define DMA_HIFCR_CTCIF4_Msk     (0x1UL << DMA_HIFCR_CTCIF4_Pos)
#define DMA_HIFCR_CTCIF4         DMA_HIFCR_CTCIF4_Msk
#define DMA_HIFCR_CHTIF4_Pos     (4U)
#define DMA_HIFCR_CHTIF4_Msk     (0x1UL << DMA_HIFCR_CHTIF4_Pos)
#define DMA_HIFCR_CHTIF4         DMA_HIFCR_CHTIF4_Msk
#define DMA_HIFCR_CTEIF4_Pos     (3U)
#define DMA_HIFCR_CTEIF4_Msk     (0x1UL << DMA_HIFCR_CTEIF4_Pos)
#define DMA_HIFCR_CTEIF4         DMA_HIFCR_CTEIF4_Msk
#define DMA_HIFCR_CDMEIF4_Pos    (2U)
#define DMA_HIFCR_CDMEIF4_Msk    (0x1UL << DMA_HIFCR_CDMEIF4_Pos)
#define DMA_HIFCR_CDMEIF4        DMA_HIFCR_CDMEIF4_Msk
#define DMA_HIFCR_CFEIF4_Pos     (0U)
#define DMA_HIFCR_CFEIF4_Msk     (0x1UL << DMA_HIFCR_CFEIF4_Pos)
#define DMA_HIFCR_CFEIF4         DMA_HIFCR_CFEIF4_Msk

#define DMA_SxPAR_PA_Pos         (0U)
#define DMA_SxPAR_PA_Msk         (0xFFFFFFFFUL << DMA_SxPAR_PA_Pos)
#define DMA_SxPAR_PA             DMA_SxPAR_PA_Msk

#define DMA_SxM0AR_M0A_Pos       (0U)
#define DMA_SxM0AR_M0A_Msk       (0xFFFFFFFFUL << DMA_SxM0AR_M0A_Pos)
#define DMA_SxM0AR_M0A           DMA_SxM0AR_M0A_Msk

#define DMA_SxM1AR_M1A_Pos       (0U)
#define DMA_SxM1AR_M1A_Msk       (0xFFFFFFFFUL << DMA_SxM1AR_M1A_Pos)
#define DMA_SxM1AR_M1A           DMA_SxM1AR_M1A_Msk

#define EXTI_IMR_MR0_Pos          (0U)
#define EXTI_IMR_MR0_Msk          (0x1UL << EXTI_IMR_MR0_Pos)
#define EXTI_IMR_MR0              EXTI_IMR_MR0_Msk
#define EXTI_IMR_MR1_Pos          (1U)
#define EXTI_IMR_MR1_Msk          (0x1UL << EXTI_IMR_MR1_Pos)
#define EXTI_IMR_MR1              EXTI_IMR_MR1_Msk
#define EXTI_IMR_MR2_Pos          (2U)
#define EXTI_IMR_MR2_Msk          (0x1UL << EXTI_IMR_MR2_Pos)
#define EXTI_IMR_MR2              EXTI_IMR_MR2_Msk
#define EXTI_IMR_MR3_Pos          (3U)
#define EXTI_IMR_MR3_Msk          (0x1UL << EXTI_IMR_MR3_Pos)
#define EXTI_IMR_MR3              EXTI_IMR_MR3_Msk
#define EXTI_IMR_MR4_Pos          (4U)
#define EXTI_IMR_MR4_Msk          (0x1UL << EXTI_IMR_MR4_Pos)
#define EXTI_IMR_MR4              EXTI_IMR_MR4_Msk
#define EXTI_IMR_MR5_Pos          (5U)
#define EXTI_IMR_MR5_Msk          (0x1UL << EXTI_IMR_MR5_Pos)
#define EXTI_IMR_MR5              EXTI_IMR_MR5_Msk
#define EXTI_IMR_MR6_Pos          (6U)
#define EXTI_IMR_MR6_Msk          (0x1UL << EXTI_IMR_MR6_Pos)
#define EXTI_IMR_MR6              EXTI_IMR_MR6_Msk
#define EXTI_IMR_MR7_Pos          (7U)
#define EXTI_IMR_MR7_Msk          (0x1UL << EXTI_IMR_MR7_Pos)
#define EXTI_IMR_MR7              EXTI_IMR_MR7_Msk
#define EXTI_IMR_MR8_Pos          (8U)
#define EXTI_IMR_MR8_Msk          (0x1UL << EXTI_IMR_MR8_Pos)
#define EXTI_IMR_MR8              EXTI_IMR_MR8_Msk
#define EXTI_IMR_MR9_Pos          (9U)
#define EXTI_IMR_MR9_Msk          (0x1UL << EXTI_IMR_MR9_Pos)
#define EXTI_IMR_MR9              EXTI_IMR_MR9_Msk
#define EXTI_IMR_MR10_Pos         (10U)
#define EXTI_IMR_MR10_Msk         (0x1UL << EXTI_IMR_MR10_Pos)
#define EXTI_IMR_MR10             EXTI_IMR_MR10_Msk
#define EXTI_IMR_MR11_Pos         (11U)
#define EXTI_IMR_MR11_Msk         (0x1UL << EXTI_IMR_MR11_Pos)
#define EXTI_IMR_MR11             EXTI_IMR_MR11_Msk
#define EXTI_IMR_MR12_Pos         (12U)
#define EXTI_IMR_MR12_Msk         (0x1UL << EXTI_IMR_MR12_Pos)
#define EXTI_IMR_MR12             EXTI_IMR_MR12_Msk
#define EXTI_IMR_MR13_Pos         (13U)
#define EXTI_IMR_MR13_Msk         (0x1UL << EXTI_IMR_MR13_Pos)
#define EXTI_IMR_MR13             EXTI_IMR_MR13_Msk
#define EXTI_IMR_MR14_Pos         (14U)
#define EXTI_IMR_MR14_Msk         (0x1UL << EXTI_IMR_MR14_Pos)
#define EXTI_IMR_MR14             EXTI_IMR_MR14_Msk
#define EXTI_IMR_MR15_Pos         (15U)
#define EXTI_IMR_MR15_Msk         (0x1UL << EXTI_IMR_MR15_Pos)
#define EXTI_IMR_MR15             EXTI_IMR_MR15_Msk
#define EXTI_IMR_MR16_Pos         (16U)
#define EXTI_IMR_MR16_Msk         (0x1UL << EXTI_IMR_MR16_Pos)
#define EXTI_IMR_MR16             EXTI_IMR_MR16_Msk
#define EXTI_IMR_MR17_Pos         (17U)
#define EXTI_IMR_MR17_Msk         (0x1UL << EXTI_IMR_MR17_Pos)
#define EXTI_IMR_MR17             EXTI_IMR_MR17_Msk
#define EXTI_IMR_MR18_Pos         (18U)
#define EXTI_IMR_MR18_Msk         (0x1UL << EXTI_IMR_MR18_Pos)
#define EXTI_IMR_MR18             EXTI_IMR_MR18_Msk
#define EXTI_IMR_MR19_Pos         (19U)
#define EXTI_IMR_MR19_Msk         (0x1UL << EXTI_IMR_MR19_Pos)
#define EXTI_IMR_MR19             EXTI_IMR_MR19_Msk
#define EXTI_IMR_MR20_Pos         (20U)
#define EXTI_IMR_MR20_Msk         (0x1UL << EXTI_IMR_MR20_Pos)
#define EXTI_IMR_MR20             EXTI_IMR_MR20_Msk
#define EXTI_IMR_MR21_Pos         (21U)
#define EXTI_IMR_MR21_Msk         (0x1UL << EXTI_IMR_MR21_Pos)
#define EXTI_IMR_MR21             EXTI_IMR_MR21_Msk
#define EXTI_IMR_MR22_Pos         (22U)
#define EXTI_IMR_MR22_Msk         (0x1UL << EXTI_IMR_MR22_Pos)
#define EXTI_IMR_MR22             EXTI_IMR_MR22_Msk

#define  EXTI_IMR_IM0                        EXTI_IMR_MR0
#define  EXTI_IMR_IM1                        EXTI_IMR_MR1
#define  EXTI_IMR_IM2                        EXTI_IMR_MR2
#define  EXTI_IMR_IM3                        EXTI_IMR_MR3
#define  EXTI_IMR_IM4                        EXTI_IMR_MR4
#define  EXTI_IMR_IM5                        EXTI_IMR_MR5
#define  EXTI_IMR_IM6                        EXTI_IMR_MR6
#define  EXTI_IMR_IM7                        EXTI_IMR_MR7
#define  EXTI_IMR_IM8                        EXTI_IMR_MR8
#define  EXTI_IMR_IM9                        EXTI_IMR_MR9
#define  EXTI_IMR_IM10                       EXTI_IMR_MR10
#define  EXTI_IMR_IM11                       EXTI_IMR_MR11
#define  EXTI_IMR_IM12                       EXTI_IMR_MR12
#define  EXTI_IMR_IM13                       EXTI_IMR_MR13
#define  EXTI_IMR_IM14                       EXTI_IMR_MR14
#define  EXTI_IMR_IM15                       EXTI_IMR_MR15
#define  EXTI_IMR_IM16                       EXTI_IMR_MR16
#define  EXTI_IMR_IM17                       EXTI_IMR_MR17
#define  EXTI_IMR_IM18                       EXTI_IMR_MR18
#define  EXTI_IMR_IM19                       EXTI_IMR_MR19
#define  EXTI_IMR_IM20                       EXTI_IMR_MR20
#define  EXTI_IMR_IM21                       EXTI_IMR_MR21
#define  EXTI_IMR_IM22                       EXTI_IMR_MR22
#define EXTI_IMR_IM_Pos           (0U)
#define EXTI_IMR_IM_Msk           (0x7FFFFFUL << EXTI_IMR_IM_Pos)
#define EXTI_IMR_IM               EXTI_IMR_IM_Msk

#define EXTI_EMR_MR0_Pos          (0U)
#define EXTI_EMR_MR0_Msk          (0x1UL << EXTI_EMR_MR0_Pos)
#define EXTI_EMR_MR0              EXTI_EMR_MR0_Msk
#define EXTI_EMR_MR1_Pos          (1U)
#define EXTI_EMR_MR1_Msk          (0x1UL << EXTI_EMR_MR1_Pos)
#define EXTI_EMR_MR1              EXTI_EMR_MR1_Msk
#define EXTI_EMR_MR2_Pos          (2U)
#define EXTI_EMR_MR2_Msk          (0x1UL << EXTI_EMR_MR2_Pos)
#define EXTI_EMR_MR2              EXTI_EMR_MR2_Msk
#define EXTI_EMR_MR3_Pos          (3U)
#define EXTI_EMR_MR3_Msk          (0x1UL << EXTI_EMR_MR3_Pos)
#define EXTI_EMR_MR3              EXTI_EMR_MR3_Msk
#define EXTI_EMR_MR4_Pos          (4U)
#define EXTI_EMR_MR4_Msk          (0x1UL << EXTI_EMR_MR4_Pos)
#define EXTI_EMR_MR4              EXTI_EMR_MR4_Msk
#define EXTI_EMR_MR5_Pos          (5U)
#define EXTI_EMR_MR5_Msk          (0x1UL << EXTI_EMR_MR5_Pos)
#define EXTI_EMR_MR5              EXTI_EMR_MR5_Msk
#define EXTI_EMR_MR6_Pos          (6U)
#define EXTI_EMR_MR6_Msk          (0x1UL << EXTI_EMR_MR6_Pos)
#define EXTI_EMR_MR6              EXTI_EMR_MR6_Msk
#define EXTI_EMR_MR7_Pos          (7U)
#define EXTI_EMR_MR7_Msk          (0x1UL << EXTI_EMR_MR7_Pos)
#define EXTI_EMR_MR7              EXTI_EMR_MR7_Msk
#define EXTI_EMR_MR8_Pos          (8U)
#define EXTI_EMR_MR8_Msk          (0x1UL << EXTI_EMR_MR8_Pos)
#define EXTI_EMR_MR8              EXTI_EMR_MR8_Msk
#define EXTI_EMR_MR9_Pos          (9U)
#define EXTI_EMR_MR9_Msk          (0x1UL << EXTI_EMR_MR9_Pos)
#define EXTI_EMR_MR9              EXTI_EMR_MR9_Msk
#define EXTI_EMR_MR10_Pos         (10U)
#define EXTI_EMR_MR10_Msk         (0x1UL << EXTI_EMR_MR10_Pos)
#define EXTI_EMR_MR10             EXTI_EMR_MR10_Msk
#define EXTI_EMR_MR11_Pos         (11U)
#define EXTI_EMR_MR11_Msk         (0x1UL << EXTI_EMR_MR11_Pos)
#define EXTI_EMR_MR11             EXTI_EMR_MR11_Msk
#define EXTI_EMR_MR12_Pos         (12U)
#define EXTI_EMR_MR12_Msk         (0x1UL << EXTI_EMR_MR12_Pos)
#define EXTI_EMR_MR12             EXTI_EMR_MR12_Msk
#define EXTI_EMR_MR13_Pos         (13U)
#define EXTI_EMR_MR13_Msk         (0x1UL << EXTI_EMR_MR13_Pos)
#define EXTI_EMR_MR13             EXTI_EMR_MR13_Msk
#define EXTI_EMR_MR14_Pos         (14U)
#define EXTI_EMR_MR14_Msk         (0x1UL << EXTI_EMR_MR14_Pos)
#define EXTI_EMR_MR14             EXTI_EMR_MR14_Msk
#define EXTI_EMR_MR15_Pos         (15U)
#define EXTI_EMR_MR15_Msk         (0x1UL << EXTI_EMR_MR15_Pos)
#define EXTI_EMR_MR15             EXTI_EMR_MR15_Msk
#define EXTI_EMR_MR16_Pos         (16U)
#define EXTI_EMR_MR16_Msk         (0x1UL << EXTI_EMR_MR16_Pos)
#define EXTI_EMR_MR16             EXTI_EMR_MR16_Msk
#define EXTI_EMR_MR17_Pos         (17U)
#define EXTI_EMR_MR17_Msk         (0x1UL << EXTI_EMR_MR17_Pos)
#define EXTI_EMR_MR17             EXTI_EMR_MR17_Msk
#define EXTI_EMR_MR18_Pos         (18U)
#define EXTI_EMR_MR18_Msk         (0x1UL << EXTI_EMR_MR18_Pos)
#define EXTI_EMR_MR18             EXTI_EMR_MR18_Msk
#define EXTI_EMR_MR19_Pos         (19U)
#define EXTI_EMR_MR19_Msk         (0x1UL << EXTI_EMR_MR19_Pos)
#define EXTI_EMR_MR19             EXTI_EMR_MR19_Msk
#define EXTI_EMR_MR20_Pos         (20U)
#define EXTI_EMR_MR20_Msk         (0x1UL << EXTI_EMR_MR20_Pos)
#define EXTI_EMR_MR20             EXTI_EMR_MR20_Msk
#define EXTI_EMR_MR21_Pos         (21U)
#define EXTI_EMR_MR21_Msk         (0x1UL << EXTI_EMR_MR21_Pos)
#define EXTI_EMR_MR21             EXTI_EMR_MR21_Msk
#define EXTI_EMR_MR22_Pos         (22U)
#define EXTI_EMR_MR22_Msk         (0x1UL << EXTI_EMR_MR22_Pos)
#define EXTI_EMR_MR22             EXTI_EMR_MR22_Msk

#define  EXTI_EMR_EM0                        EXTI_EMR_MR0
#define  EXTI_EMR_EM1                        EXTI_EMR_MR1
#define  EXTI_EMR_EM2                        EXTI_EMR_MR2
#define  EXTI_EMR_EM3                        EXTI_EMR_MR3
#define  EXTI_EMR_EM4                        EXTI_EMR_MR4
#define  EXTI_EMR_EM5                        EXTI_EMR_MR5
#define  EXTI_EMR_EM6                        EXTI_EMR_MR6
#define  EXTI_EMR_EM7                        EXTI_EMR_MR7
#define  EXTI_EMR_EM8                        EXTI_EMR_MR8
#define  EXTI_EMR_EM9                        EXTI_EMR_MR9
#define  EXTI_EMR_EM10                       EXTI_EMR_MR10
#define  EXTI_EMR_EM11                       EXTI_EMR_MR11
#define  EXTI_EMR_EM12                       EXTI_EMR_MR12
#define  EXTI_EMR_EM13                       EXTI_EMR_MR13
#define  EXTI_EMR_EM14                       EXTI_EMR_MR14
#define  EXTI_EMR_EM15                       EXTI_EMR_MR15
#define  EXTI_EMR_EM16                       EXTI_EMR_MR16
#define  EXTI_EMR_EM17                       EXTI_EMR_MR17
#define  EXTI_EMR_EM18                       EXTI_EMR_MR18
#define  EXTI_EMR_EM19                       EXTI_EMR_MR19
#define  EXTI_EMR_EM20                       EXTI_EMR_MR20
#define  EXTI_EMR_EM21                       EXTI_EMR_MR21
#define  EXTI_EMR_EM22                       EXTI_EMR_MR22

#define EXTI_RTSR_TR0_Pos         (0U)
#define EXTI_RTSR_TR0_Msk         (0x1UL << EXTI_RTSR_TR0_Pos)
#define EXTI_RTSR_TR0             EXTI_RTSR_TR0_Msk
#define EXTI_RTSR_TR1_Pos         (1U)
#define EXTI_RTSR_TR1_Msk         (0x1UL << EXTI_RTSR_TR1_Pos)
#define EXTI_RTSR_TR1             EXTI_RTSR_TR1_Msk
#define EXTI_RTSR_TR2_Pos         (2U)
#define EXTI_RTSR_TR2_Msk         (0x1UL << EXTI_RTSR_TR2_Pos)
#define EXTI_RTSR_TR2             EXTI_RTSR_TR2_Msk
#define EXTI_RTSR_TR3_Pos         (3U)
#define EXTI_RTSR_TR3_Msk         (0x1UL << EXTI_RTSR_TR3_Pos)
#define EXTI_RTSR_TR3             EXTI_RTSR_TR3_Msk
#define EXTI_RTSR_TR4_Pos         (4U)
#define EXTI_RTSR_TR4_Msk         (0x1UL << EXTI_RTSR_TR4_Pos)
#define EXTI_RTSR_TR4             EXTI_RTSR_TR4_Msk
#define EXTI_RTSR_TR5_Pos         (5U)
#define EXTI_RTSR_TR5_Msk         (0x1UL << EXTI_RTSR_TR5_Pos)
#define EXTI_RTSR_TR5             EXTI_RTSR_TR5_Msk
#define EXTI_RTSR_TR6_Pos         (6U)
#define EXTI_RTSR_TR6_Msk         (0x1UL << EXTI_RTSR_TR6_Pos)
#define EXTI_RTSR_TR6             EXTI_RTSR_TR6_Msk
#define EXTI_RTSR_TR7_Pos         (7U)
#define EXTI_RTSR_TR7_Msk         (0x1UL << EXTI_RTSR_TR7_Pos)
#define EXTI_RTSR_TR7             EXTI_RTSR_TR7_Msk
#define EXTI_RTSR_TR8_Pos         (8U)
#define EXTI_RTSR_TR8_Msk         (0x1UL << EXTI_RTSR_TR8_Pos)
#define EXTI_RTSR_TR8             EXTI_RTSR_TR8_Msk
#define EXTI_RTSR_TR9_Pos         (9U)
#define EXTI_RTSR_TR9_Msk         (0x1UL << EXTI_RTSR_TR9_Pos)
#define EXTI_RTSR_TR9             EXTI_RTSR_TR9_Msk
#define EXTI_RTSR_TR10_Pos        (10U)
#define EXTI_RTSR_TR10_Msk        (0x1UL << EXTI_RTSR_TR10_Pos)
#define EXTI_RTSR_TR10            EXTI_RTSR_TR10_Msk
#define EXTI_RTSR_TR11_Pos        (11U)
#define EXTI_RTSR_TR11_Msk        (0x1UL << EXTI_RTSR_TR11_Pos)
#define EXTI_RTSR_TR11            EXTI_RTSR_TR11_Msk
#define EXTI_RTSR_TR12_Pos        (12U)
#define EXTI_RTSR_TR12_Msk        (0x1UL << EXTI_RTSR_TR12_Pos)
#define EXTI_RTSR_TR12            EXTI_RTSR_TR12_Msk
#define EXTI_RTSR_TR13_Pos        (13U)
#define EXTI_RTSR_TR13_Msk        (0x1UL << EXTI_RTSR_TR13_Pos)
#define EXTI_RTSR_TR13            EXTI_RTSR_TR13_Msk
#define EXTI_RTSR_TR14_Pos        (14U)
#define EXTI_RTSR_TR14_Msk        (0x1UL << EXTI_RTSR_TR14_Pos)
#define EXTI_RTSR_TR14            EXTI_RTSR_TR14_Msk
#define EXTI_RTSR_TR15_Pos        (15U)
#define EXTI_RTSR_TR15_Msk        (0x1UL << EXTI_RTSR_TR15_Pos)
#define EXTI_RTSR_TR15            EXTI_RTSR_TR15_Msk
#define EXTI_RTSR_TR16_Pos        (16U)
#define EXTI_RTSR_TR16_Msk        (0x1UL << EXTI_RTSR_TR16_Pos)
#define EXTI_RTSR_TR16            EXTI_RTSR_TR16_Msk
#define EXTI_RTSR_TR17_Pos        (17U)
#define EXTI_RTSR_TR17_Msk        (0x1UL << EXTI_RTSR_TR17_Pos)
#define EXTI_RTSR_TR17            EXTI_RTSR_TR17_Msk
#define EXTI_RTSR_TR18_Pos        (18U)
#define EXTI_RTSR_TR18_Msk        (0x1UL << EXTI_RTSR_TR18_Pos)
#define EXTI_RTSR_TR18            EXTI_RTSR_TR18_Msk
#define EXTI_RTSR_TR19_Pos        (19U)
#define EXTI_RTSR_TR19_Msk        (0x1UL << EXTI_RTSR_TR19_Pos)
#define EXTI_RTSR_TR19            EXTI_RTSR_TR19_Msk
#define EXTI_RTSR_TR20_Pos        (20U)
#define EXTI_RTSR_TR20_Msk        (0x1UL << EXTI_RTSR_TR20_Pos)
#define EXTI_RTSR_TR20            EXTI_RTSR_TR20_Msk
#define EXTI_RTSR_TR21_Pos        (21U)
#define EXTI_RTSR_TR21_Msk        (0x1UL << EXTI_RTSR_TR21_Pos)
#define EXTI_RTSR_TR21            EXTI_RTSR_TR21_Msk
#define EXTI_RTSR_TR22_Pos        (22U)
#define EXTI_RTSR_TR22_Msk        (0x1UL << EXTI_RTSR_TR22_Pos)
#define EXTI_RTSR_TR22            EXTI_RTSR_TR22_Msk

#define EXTI_FTSR_TR0_Pos         (0U)
#define EXTI_FTSR_TR0_Msk         (0x1UL << EXTI_FTSR_TR0_Pos)
#define EXTI_FTSR_TR0             EXTI_FTSR_TR0_Msk
#define EXTI_FTSR_TR1_Pos         (1U)
#define EXTI_FTSR_TR1_Msk         (0x1UL << EXTI_FTSR_TR1_Pos)
#define EXTI_FTSR_TR1             EXTI_FTSR_TR1_Msk
#define EXTI_FTSR_TR2_Pos         (2U)
#define EXTI_FTSR_TR2_Msk         (0x1UL << EXTI_FTSR_TR2_Pos)
#define EXTI_FTSR_TR2             EXTI_FTSR_TR2_Msk
#define EXTI_FTSR_TR3_Pos         (3U)
#define EXTI_FTSR_TR3_Msk         (0x1UL << EXTI_FTSR_TR3_Pos)
#define EXTI_FTSR_TR3             EXTI_FTSR_TR3_Msk
#define EXTI_FTSR_TR4_Pos         (4U)
#define EXTI_FTSR_TR4_Msk         (0x1UL << EXTI_FTSR_TR4_Pos)
#define EXTI_FTSR_TR4             EXTI_FTSR_TR4_Msk
#define EXTI_FTSR_TR5_Pos         (5U)
#define EXTI_FTSR_TR5_Msk         (0x1UL << EXTI_FTSR_TR5_Pos)
#define EXTI_FTSR_TR5             EXTI_FTSR_TR5_Msk
#define EXTI_FTSR_TR6_Pos         (6U)
#define EXTI_FTSR_TR6_Msk         (0x1UL << EXTI_FTSR_TR6_Pos)
#define EXTI_FTSR_TR6             EXTI_FTSR_TR6_Msk
#define EXTI_FTSR_TR7_Pos         (7U)
#define EXTI_FTSR_TR7_Msk         (0x1UL << EXTI_FTSR_TR7_Pos)
#define EXTI_FTSR_TR7             EXTI_FTSR_TR7_Msk
#define EXTI_FTSR_TR8_Pos         (8U)
#define EXTI_FTSR_TR8_Msk         (0x1UL << EXTI_FTSR_TR8_Pos)
#define EXTI_FTSR_TR8             EXTI_FTSR_TR8_Msk
#define EXTI_FTSR_TR9_Pos         (9U)
#define EXTI_FTSR_TR9_Msk         (0x1UL << EXTI_FTSR_TR9_Pos)
#define EXTI_FTSR_TR9             EXTI_FTSR_TR9_Msk
#define EXTI_FTSR_TR10_Pos        (10U)
#define EXTI_FTSR_TR10_Msk        (0x1UL << EXTI_FTSR_TR10_Pos)
#define EXTI_FTSR_TR10            EXTI_FTSR_TR10_Msk
#define EXTI_FTSR_TR11_Pos        (11U)
#define EXTI_FTSR_TR11_Msk        (0x1UL << EXTI_FTSR_TR11_Pos)
#define EXTI_FTSR_TR11            EXTI_FTSR_TR11_Msk
#define EXTI_FTSR_TR12_Pos        (12U)
#define EXTI_FTSR_TR12_Msk        (0x1UL << EXTI_FTSR_TR12_Pos)
#define EXTI_FTSR_TR12            EXTI_FTSR_TR12_Msk
#define EXTI_FTSR_TR13_Pos        (13U)
#define EXTI_FTSR_TR13_Msk        (0x1UL << EXTI_FTSR_TR13_Pos)
#define EXTI_FTSR_TR13            EXTI_FTSR_TR13_Msk
#define EXTI_FTSR_TR14_Pos        (14U)
#define EXTI_FTSR_TR14_Msk        (0x1UL << EXTI_FTSR_TR14_Pos)
#define EXTI_FTSR_TR14            EXTI_FTSR_TR14_Msk
#define EXTI_FTSR_TR15_Pos        (15U)
#define EXTI_FTSR_TR15_Msk        (0x1UL << EXTI_FTSR_TR15_Pos)
#define EXTI_FTSR_TR15            EXTI_FTSR_TR15_Msk
#define EXTI_FTSR_TR16_Pos        (16U)
#define EXTI_FTSR_TR16_Msk        (0x1UL << EXTI_FTSR_TR16_Pos)
#define EXTI_FTSR_TR16            EXTI_FTSR_TR16_Msk
#define EXTI_FTSR_TR17_Pos        (17U)
#define EXTI_FTSR_TR17_Msk        (0x1UL << EXTI_FTSR_TR17_Pos)
#define EXTI_FTSR_TR17            EXTI_FTSR_TR17_Msk
#define EXTI_FTSR_TR18_Pos        (18U)
#define EXTI_FTSR_TR18_Msk        (0x1UL << EXTI_FTSR_TR18_Pos)
#define EXTI_FTSR_TR18            EXTI_FTSR_TR18_Msk
#define EXTI_FTSR_TR19_Pos        (19U)
#define EXTI_FTSR_TR19_Msk        (0x1UL << EXTI_FTSR_TR19_Pos)
#define EXTI_FTSR_TR19            EXTI_FTSR_TR19_Msk
#define EXTI_FTSR_TR20_Pos        (20U)
#define EXTI_FTSR_TR20_Msk        (0x1UL << EXTI_FTSR_TR20_Pos)
#define EXTI_FTSR_TR20            EXTI_FTSR_TR20_Msk
#define EXTI_FTSR_TR21_Pos        (21U)
#define EXTI_FTSR_TR21_Msk        (0x1UL << EXTI_FTSR_TR21_Pos)
#define EXTI_FTSR_TR21            EXTI_FTSR_TR21_Msk
#define EXTI_FTSR_TR22_Pos        (22U)
#define EXTI_FTSR_TR22_Msk        (0x1UL << EXTI_FTSR_TR22_Pos)
#define EXTI_FTSR_TR22            EXTI_FTSR_TR22_Msk

#define EXTI_SWIER_SWIER0_Pos     (0U)
#define EXTI_SWIER_SWIER0_Msk     (0x1UL << EXTI_SWIER_SWIER0_Pos)
#define EXTI_SWIER_SWIER0         EXTI_SWIER_SWIER0_Msk
#define EXTI_SWIER_SWIER1_Pos     (1U)
#define EXTI_SWIER_SWIER1_Msk     (0x1UL << EXTI_SWIER_SWIER1_Pos)
#define EXTI_SWIER_SWIER1         EXTI_SWIER_SWIER1_Msk
#define EXTI_SWIER_SWIER2_Pos     (2U)
#define EXTI_SWIER_SWIER2_Msk     (0x1UL << EXTI_SWIER_SWIER2_Pos)
#define EXTI_SWIER_SWIER2         EXTI_SWIER_SWIER2_Msk
#define EXTI_SWIER_SWIER3_Pos     (3U)
#define EXTI_SWIER_SWIER3_Msk     (0x1UL << EXTI_SWIER_SWIER3_Pos)
#define EXTI_SWIER_SWIER3         EXTI_SWIER_SWIER3_Msk
#define EXTI_SWIER_SWIER4_Pos     (4U)
#define EXTI_SWIER_SWIER4_Msk     (0x1UL << EXTI_SWIER_SWIER4_Pos)
#define EXTI_SWIER_SWIER4         EXTI_SWIER_SWIER4_Msk
#define EXTI_SWIER_SWIER5_Pos     (5U)
#define EXTI_SWIER_SWIER5_Msk     (0x1UL << EXTI_SWIER_SWIER5_Pos)
#define EXTI_SWIER_SWIER5         EXTI_SWIER_SWIER5_Msk
#define EXTI_SWIER_SWIER6_Pos     (6U)
#define EXTI_SWIER_SWIER6_Msk     (0x1UL << EXTI_SWIER_SWIER6_Pos)
#define EXTI_SWIER_SWIER6         EXTI_SWIER_SWIER6_Msk
#define EXTI_SWIER_SWIER7_Pos     (7U)
#define EXTI_SWIER_SWIER7_Msk     (0x1UL << EXTI_SWIER_SWIER7_Pos)
#define EXTI_SWIER_SWIER7         EXTI_SWIER_SWIER7_Msk
#define EXTI_SWIER_SWIER8_Pos     (8U)
#define EXTI_SWIER_SWIER8_Msk     (0x1UL << EXTI_SWIER_SWIER8_Pos)
#define EXTI_SWIER_SWIER8         EXTI_SWIER_SWIER8_Msk
#define EXTI_SWIER_SWIER9_Pos     (9U)
#define EXTI_SWIER_SWIER9_Msk     (0x1UL << EXTI_SWIER_SWIER9_Pos)
#define EXTI_SWIER_SWIER9         EXTI_SWIER_SWIER9_Msk
#define EXTI_SWIER_SWIER10_Pos    (10U)
#define EXTI_SWIER_SWIER10_Msk    (0x1UL << EXTI_SWIER_SWIER10_Pos)
#define EXTI_SWIER_SWIER10        EXTI_SWIER_SWIER10_Msk
#define EXTI_SWIER_SWIER11_Pos    (11U)
#define EXTI_SWIER_SWIER11_Msk    (0x1UL << EXTI_SWIER_SWIER11_Pos)
#define EXTI_SWIER_SWIER11        EXTI_SWIER_SWIER11_Msk
#define EXTI_SWIER_SWIER12_Pos    (12U)
#define EXTI_SWIER_SWIER12_Msk    (0x1UL << EXTI_SWIER_SWIER12_Pos)
#define EXTI_SWIER_SWIER12        EXTI_SWIER_SWIER12_Msk
#define EXTI_SWIER_SWIER13_Pos    (13U)
#define EXTI_SWIER_SWIER13_Msk    (0x1UL << EXTI_SWIER_SWIER13_Pos)
#define EXTI_SWIER_SWIER13        EXTI_SWIER_SWIER13_Msk
#define EXTI_SWIER_SWIER14_Pos    (14U)
#define EXTI_SWIER_SWIER14_Msk    (0x1UL << EXTI_SWIER_SWIER14_Pos)
#define EXTI_SWIER_SWIER14        EXTI_SWIER_SWIER14_Msk
#define EXTI_SWIER_SWIER15_Pos    (15U)
#define EXTI_SWIER_SWIER15_Msk    (0x1UL << EXTI_SWIER_SWIER15_Pos)
#define EXTI_SWIER_SWIER15        EXTI_SWIER_SWIER15_Msk
#define EXTI_SWIER_SWIER16_Pos    (16U)
#define EXTI_SWIER_SWIER16_Msk    (0x1UL << EXTI_SWIER_SWIER16_Pos)
#define EXTI_SWIER_SWIER16        EXTI_SWIER_SWIER16_Msk
#define EXTI_SWIER_SWIER17_Pos    (17U)
#define EXTI_SWIER_SWIER17_Msk    (0x1UL << EXTI_SWIER_SWIER17_Pos)
#define EXTI_SWIER_SWIER17        EXTI_SWIER_SWIER17_Msk
#define EXTI_SWIER_SWIER18_Pos    (18U)
#define EXTI_SWIER_SWIER18_Msk    (0x1UL << EXTI_SWIER_SWIER18_Pos)
#define EXTI_SWIER_SWIER18        EXTI_SWIER_SWIER18_Msk
#define EXTI_SWIER_SWIER19_Pos    (19U)
#define EXTI_SWIER_SWIER19_Msk    (0x1UL << EXTI_SWIER_SWIER19_Pos)
#define EXTI_SWIER_SWIER19        EXTI_SWIER_SWIER19_Msk
#define EXTI_SWIER_SWIER20_Pos    (20U)
#define EXTI_SWIER_SWIER20_Msk    (0x1UL << EXTI_SWIER_SWIER20_Pos)
#define EXTI_SWIER_SWIER20        EXTI_SWIER_SWIER20_Msk
#define EXTI_SWIER_SWIER21_Pos    (21U)
#define EXTI_SWIER_SWIER21_Msk    (0x1UL << EXTI_SWIER_SWIER21_Pos)
#define EXTI_SWIER_SWIER21        EXTI_SWIER_SWIER21_Msk
#define EXTI_SWIER_SWIER22_Pos    (22U)
#define EXTI_SWIER_SWIER22_Msk    (0x1UL << EXTI_SWIER_SWIER22_Pos)
#define EXTI_SWIER_SWIER22        EXTI_SWIER_SWIER22_Msk

#define EXTI_PR_PR0_Pos           (0U)
#define EXTI_PR_PR0_Msk           (0x1UL << EXTI_PR_PR0_Pos)
#define EXTI_PR_PR0               EXTI_PR_PR0_Msk
#define EXTI_PR_PR1_Pos           (1U)
#define EXTI_PR_PR1_Msk           (0x1UL << EXTI_PR_PR1_Pos)
#define EXTI_PR_PR1               EXTI_PR_PR1_Msk
#define EXTI_PR_PR2_Pos           (2U)
#define EXTI_PR_PR2_Msk           (0x1UL << EXTI_PR_PR2_Pos)
#define EXTI_PR_PR2               EXTI_PR_PR2_Msk
#define EXTI_PR_PR3_Pos           (3U)
#define EXTI_PR_PR3_Msk           (0x1UL << EXTI_PR_PR3_Pos)
#define EXTI_PR_PR3               EXTI_PR_PR3_Msk
#define EXTI_PR_PR4_Pos           (4U)
#define EXTI_PR_PR4_Msk           (0x1UL << EXTI_PR_PR4_Pos)
#define EXTI_PR_PR4               EXTI_PR_PR4_Msk
#define EXTI_PR_PR5_Pos           (5U)
#define EXTI_PR_PR5_Msk           (0x1UL << EXTI_PR_PR5_Pos)
#define EXTI_PR_PR5               EXTI_PR_PR5_Msk
#define EXTI_PR_PR6_Pos           (6U)
#define EXTI_PR_PR6_Msk           (0x1UL << EXTI_PR_PR6_Pos)
#define EXTI_PR_PR6               EXTI_PR_PR6_Msk
#define EXTI_PR_PR7_Pos           (7U)
#define EXTI_PR_PR7_Msk           (0x1UL << EXTI_PR_PR7_Pos)
#define EXTI_PR_PR7               EXTI_PR_PR7_Msk
#define EXTI_PR_PR8_Pos           (8U)
#define EXTI_PR_PR8_Msk           (0x1UL << EXTI_PR_PR8_Pos)
#define EXTI_PR_PR8               EXTI_PR_PR8_Msk
#define EXTI_PR_PR9_Pos           (9U)
#define EXTI_PR_PR9_Msk           (0x1UL << EXTI_PR_PR9_Pos)
#define EXTI_PR_PR9               EXTI_PR_PR9_Msk
#define EXTI_PR_PR10_Pos          (10U)
#define EXTI_PR_PR10_Msk          (0x1UL << EXTI_PR_PR10_Pos)
#define EXTI_PR_PR10              EXTI_PR_PR10_Msk
#define EXTI_PR_PR11_Pos          (11U)
#define EXTI_PR_PR11_Msk          (0x1UL << EXTI_PR_PR11_Pos)
#define EXTI_PR_PR11              EXTI_PR_PR11_Msk
#define EXTI_PR_PR12_Pos          (12U)
#define EXTI_PR_PR12_Msk          (0x1UL << EXTI_PR_PR12_Pos)
#define EXTI_PR_PR12              EXTI_PR_PR12_Msk
#define EXTI_PR_PR13_Pos          (13U)
#define EXTI_PR_PR13_Msk          (0x1UL << EXTI_PR_PR13_Pos)
#define EXTI_PR_PR13              EXTI_PR_PR13_Msk
#define EXTI_PR_PR14_Pos          (14U)
#define EXTI_PR_PR14_Msk          (0x1UL << EXTI_PR_PR14_Pos)
#define EXTI_PR_PR14              EXTI_PR_PR14_Msk
#define EXTI_PR_PR15_Pos          (15U)
#define EXTI_PR_PR15_Msk          (0x1UL << EXTI_PR_PR15_Pos)
#define EXTI_PR_PR15              EXTI_PR_PR15_Msk
#define EXTI_PR_PR16_Pos          (16U)
#define EXTI_PR_PR16_Msk          (0x1UL << EXTI_PR_PR16_Pos)
#define EXTI_PR_PR16              EXTI_PR_PR16_Msk
#define EXTI_PR_PR17_Pos          (17U)
#define EXTI_PR_PR17_Msk          (0x1UL << EXTI_PR_PR17_Pos)
#define EXTI_PR_PR17              EXTI_PR_PR17_Msk
#define EXTI_PR_PR18_Pos          (18U)
#define EXTI_PR_PR18_Msk          (0x1UL << EXTI_PR_PR18_Pos)
#define EXTI_PR_PR18              EXTI_PR_PR18_Msk
#define EXTI_PR_PR19_Pos          (19U)
#define EXTI_PR_PR19_Msk          (0x1UL << EXTI_PR_PR19_Pos)
#define EXTI_PR_PR19              EXTI_PR_PR19_Msk
#define EXTI_PR_PR20_Pos          (20U)
#define EXTI_PR_PR20_Msk          (0x1UL << EXTI_PR_PR20_Pos)
#define EXTI_PR_PR20              EXTI_PR_PR20_Msk
#define EXTI_PR_PR21_Pos          (21U)
#define EXTI_PR_PR21_Msk          (0x1UL << EXTI_PR_PR21_Pos)
#define EXTI_PR_PR21              EXTI_PR_PR21_Msk
#define EXTI_PR_PR22_Pos          (22U)
#define EXTI_PR_PR22_Msk          (0x1UL << EXTI_PR_PR22_Pos)
#define EXTI_PR_PR22              EXTI_PR_PR22_Msk

#define FLASH_ACR_LATENCY_Pos          (0U)
#define FLASH_ACR_LATENCY_Msk          (0x7UL << FLASH_ACR_LATENCY_Pos)
#define FLASH_ACR_LATENCY              FLASH_ACR_LATENCY_Msk
#define FLASH_ACR_LATENCY_0WS          0x00000000U
#define FLASH_ACR_LATENCY_1WS          0x00000001U
#define FLASH_ACR_LATENCY_2WS          0x00000002U
#define FLASH_ACR_LATENCY_3WS          0x00000003U
#define FLASH_ACR_LATENCY_4WS          0x00000004U
#define FLASH_ACR_LATENCY_5WS          0x00000005U
#define FLASH_ACR_LATENCY_6WS          0x00000006U
#define FLASH_ACR_LATENCY_7WS          0x00000007U

#define FLASH_ACR_PRFTEN_Pos           (8U)
#define FLASH_ACR_PRFTEN_Msk           (0x1UL << FLASH_ACR_PRFTEN_Pos)
#define FLASH_ACR_PRFTEN               FLASH_ACR_PRFTEN_Msk
#define FLASH_ACR_ICEN_Pos             (9U)
#define FLASH_ACR_ICEN_Msk             (0x1UL << FLASH_ACR_ICEN_Pos)
#define FLASH_ACR_ICEN                 FLASH_ACR_ICEN_Msk
#define FLASH_ACR_DCEN_Pos             (10U)
#define FLASH_ACR_DCEN_Msk             (0x1UL << FLASH_ACR_DCEN_Pos)
#define FLASH_ACR_DCEN                 FLASH_ACR_DCEN_Msk
#define FLASH_ACR_ICRST_Pos            (11U)
#define FLASH_ACR_ICRST_Msk            (0x1UL << FLASH_ACR_ICRST_Pos)
#define FLASH_ACR_ICRST                FLASH_ACR_ICRST_Msk
#define FLASH_ACR_DCRST_Pos            (12U)
#define FLASH_ACR_DCRST_Msk            (0x1UL << FLASH_ACR_DCRST_Pos)
#define FLASH_ACR_DCRST                FLASH_ACR_DCRST_Msk

#define FLASH_SR_EOP_Pos               (0U)
#define FLASH_SR_EOP_Msk               (0x1UL << FLASH_SR_EOP_Pos)
#define FLASH_SR_EOP                   FLASH_SR_EOP_Msk
#define FLASH_SR_OPERR_Pos             (1U)
#define FLASH_SR_OPERR_Msk             (0x1UL << FLASH_SR_OPERR_Pos)
#define FLASH_SR_OPERR                 FLASH_SR_OPERR_Msk
#define FLASH_SR_WRPERR_Pos            (4U)
#define FLASH_SR_WRPERR_Msk            (0x1UL << FLASH_SR_WRPERR_Pos)
#define FLASH_SR_WRPERR                FLASH_SR_WRPERR_Msk
#define FLASH_SR_PGAERR_Pos            (5U)
#define FLASH_SR_PGAERR_Msk            (0x1UL << FLASH_SR_PGAERR_Pos)
#define FLASH_SR_PGAERR                FLASH_SR_PGAERR_Msk
#define FLASH_SR_PGPERR_Pos            (6U)
#define FLASH_SR_PGPERR_Msk            (0x1UL << FLASH_SR_PGPERR_Pos)
#define FLASH_SR_PGPERR                FLASH_SR_PGPERR_Msk
#define FLASH_SR_PGSERR_Pos            (7U)
#define FLASH_SR_PGSERR_Msk            (0x1UL << FLASH_SR_PGSERR_Pos)
#define FLASH_SR_PGSERR                FLASH_SR_PGSERR_Msk
#define FLASH_SR_RDERR_Pos            (8U)
#define FLASH_SR_RDERR_Msk            (0x1UL << FLASH_SR_RDERR_Pos)
#define FLASH_SR_RDERR                FLASH_SR_RDERR_Msk
#define FLASH_SR_BSY_Pos               (16U)
#define FLASH_SR_BSY_Msk               (0x1UL << FLASH_SR_BSY_Pos)
#define FLASH_SR_BSY                   FLASH_SR_BSY_Msk

#define FLASH_CR_PG_Pos                (0U)
#define FLASH_CR_PG_Msk                (0x1UL << FLASH_CR_PG_Pos)
#define FLASH_CR_PG                    FLASH_CR_PG_Msk
#define FLASH_CR_SER_Pos               (1U)
#define FLASH_CR_SER_Msk               (0x1UL << FLASH_CR_SER_Pos)
#define FLASH_CR_SER                   FLASH_CR_SER_Msk
#define FLASH_CR_MER_Pos               (2U)
#define FLASH_CR_MER_Msk               (0x1UL << FLASH_CR_MER_Pos)
#define FLASH_CR_MER                   FLASH_CR_MER_Msk
#define FLASH_CR_SNB_Pos               (3U)
#define FLASH_CR_SNB_Msk               (0x1FUL << FLASH_CR_SNB_Pos)
#define FLASH_CR_SNB                   FLASH_CR_SNB_Msk
#define FLASH_CR_SNB_0                 (0x01UL << FLASH_CR_SNB_Pos)
#define FLASH_CR_SNB_1                 (0x02UL << FLASH_CR_SNB_Pos)
#define FLASH_CR_SNB_2                 (0x04UL << FLASH_CR_SNB_Pos)
#define FLASH_CR_SNB_3                 (0x08UL << FLASH_CR_SNB_Pos)
#define FLASH_CR_SNB_4                 (0x10UL << FLASH_CR_SNB_Pos)
#define FLASH_CR_PSIZE_Pos             (8U)
#define FLASH_CR_PSIZE_Msk             (0x3UL << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_PSIZE                 FLASH_CR_PSIZE_Msk
#define FLASH_CR_PSIZE_0               (0x1UL << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_PSIZE_1               (0x2UL << FLASH_CR_PSIZE_Pos)
#define FLASH_CR_STRT_Pos              (16U)
#define FLASH_CR_STRT_Msk              (0x1UL << FLASH_CR_STRT_Pos)
#define FLASH_CR_STRT                  FLASH_CR_STRT_Msk
#define FLASH_CR_EOPIE_Pos             (24U)
#define FLASH_CR_EOPIE_Msk             (0x1UL << FLASH_CR_EOPIE_Pos)
#define FLASH_CR_EOPIE                 FLASH_CR_EOPIE_Msk
#define FLASH_CR_ERRIE_Pos             (25U)
#define FLASH_CR_ERRIE_Msk             (0x1UL << FLASH_CR_ERRIE_Pos)
#define FLASH_CR_ERRIE                 FLASH_CR_ERRIE_Msk
#define FLASH_CR_LOCK_Pos              (31U)
#define FLASH_CR_LOCK_Msk              (0x1UL << FLASH_CR_LOCK_Pos)
#define FLASH_CR_LOCK                  FLASH_CR_LOCK_Msk

#define FLASH_OPTCR_OPTLOCK_Pos        (0U)
#define FLASH_OPTCR_OPTLOCK_Msk        (0x1UL << FLASH_OPTCR_OPTLOCK_Pos)
#define FLASH_OPTCR_OPTLOCK            FLASH_OPTCR_OPTLOCK_Msk
#define FLASH_OPTCR_OPTSTRT_Pos        (1U)
#define FLASH_OPTCR_OPTSTRT_Msk        (0x1UL << FLASH_OPTCR_OPTSTRT_Pos)
#define FLASH_OPTCR_OPTSTRT            FLASH_OPTCR_OPTSTRT_Msk

#define FLASH_OPTCR_BOR_LEV_0          0x00000004U
#define FLASH_OPTCR_BOR_LEV_1          0x00000008U
#define FLASH_OPTCR_BOR_LEV_Pos        (2U)
#define FLASH_OPTCR_BOR_LEV_Msk        (0x3UL << FLASH_OPTCR_BOR_LEV_Pos)
#define FLASH_OPTCR_BOR_LEV            FLASH_OPTCR_BOR_LEV_Msk
#define FLASH_OPTCR_WDG_SW_Pos         (5U)
#define FLASH_OPTCR_WDG_SW_Msk         (0x1UL << FLASH_OPTCR_WDG_SW_Pos)
#define FLASH_OPTCR_WDG_SW             FLASH_OPTCR_WDG_SW_Msk
#define FLASH_OPTCR_nRST_STOP_Pos      (6U)
#define FLASH_OPTCR_nRST_STOP_Msk      (0x1UL << FLASH_OPTCR_nRST_STOP_Pos)
#define FLASH_OPTCR_nRST_STOP          FLASH_OPTCR_nRST_STOP_Msk
#define FLASH_OPTCR_nRST_STDBY_Pos     (7U)
#define FLASH_OPTCR_nRST_STDBY_Msk     (0x1UL << FLASH_OPTCR_nRST_STDBY_Pos)
#define FLASH_OPTCR_nRST_STDBY         FLASH_OPTCR_nRST_STDBY_Msk
#define FLASH_OPTCR_RDP_Pos            (8U)
#define FLASH_OPTCR_RDP_Msk            (0xFFUL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP                FLASH_OPTCR_RDP_Msk
#define FLASH_OPTCR_RDP_0              (0x01UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_1              (0x02UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_2              (0x04UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_3              (0x08UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_4              (0x10UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_5              (0x20UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_6              (0x40UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_RDP_7              (0x80UL << FLASH_OPTCR_RDP_Pos)
#define FLASH_OPTCR_nWRP_Pos           (16U)
#define FLASH_OPTCR_nWRP_Msk           (0xFFFUL << FLASH_OPTCR_nWRP_Pos)
#define FLASH_OPTCR_nWRP               FLASH_OPTCR_nWRP_Msk
#define FLASH_OPTCR_nWRP_0             0x00010000U
#define FLASH_OPTCR_nWRP_1             0x00020000U
#define FLASH_OPTCR_nWRP_2             0x00040000U
#define FLASH_OPTCR_nWRP_3             0x00080000U
#define FLASH_OPTCR_nWRP_4             0x00100000U
#define FLASH_OPTCR_nWRP_5             0x00200000U
#define FLASH_OPTCR_nWRP_6             0x00400000U
#define FLASH_OPTCR_nWRP_7             0x00800000U
#define FLASH_OPTCR_nWRP_8             0x01000000U
#define FLASH_OPTCR_nWRP_9             0x02000000U
#define FLASH_OPTCR_nWRP_10            0x04000000U
#define FLASH_OPTCR_nWRP_11            0x08000000U

#define FLASH_OPTCR1_nWRP_Pos          (16U)
#define FLASH_OPTCR1_nWRP_Msk          (0xFFFUL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP              FLASH_OPTCR1_nWRP_Msk
#define FLASH_OPTCR1_nWRP_0            (0x001UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_1            (0x002UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_2            (0x004UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_3            (0x008UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_4            (0x010UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_5            (0x020UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_6            (0x040UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_7            (0x080UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_8            (0x100UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_9            (0x200UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_10           (0x400UL << FLASH_OPTCR1_nWRP_Pos)
#define FLASH_OPTCR1_nWRP_11           (0x800UL << FLASH_OPTCR1_nWRP_Pos)

#define FLASH_SR_SOP_Pos    FLASH_SR_OPERR_Pos
#define FLASH_SR_SOP_Msk    FLASH_SR_OPERR_Msk
#define FLASH_SR_SOP        FLASH_SR_OPERR
#define FLASH_ACR_BYTE0_ADDRESS_Pos    (10U)
#define FLASH_ACR_BYTE0_ADDRESS_Msk    (0x10008FUL << FLASH_ACR_BYTE0_ADDRESS_Pos)
#define FLASH_ACR_BYTE0_ADDRESS        FLASH_ACR_BYTE0_ADDRESS_Msk
#define FLASH_ACR_BYTE2_ADDRESS_Pos    (0U)
#define FLASH_ACR_BYTE2_ADDRESS_Msk    (0x40023C03UL << FLASH_ACR_BYTE2_ADDRESS_Pos)
#define FLASH_ACR_BYTE2_ADDRESS        FLASH_ACR_BYTE2_ADDRESS_Msk

#define GPIO_MODER_MODER0_Pos            (0U)
#define GPIO_MODER_MODER0_Msk            (0x3UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER0                GPIO_MODER_MODER0_Msk
#define GPIO_MODER_MODER0_0              (0x1UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER0_1              (0x2UL << GPIO_MODER_MODER0_Pos)
#define GPIO_MODER_MODER1_Pos            (2U)
#define GPIO_MODER_MODER1_Msk            (0x3UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER1                GPIO_MODER_MODER1_Msk
#define GPIO_MODER_MODER1_0              (0x1UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER1_1              (0x2UL << GPIO_MODER_MODER1_Pos)
#define GPIO_MODER_MODER2_Pos            (4U)
#define GPIO_MODER_MODER2_Msk            (0x3UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2                GPIO_MODER_MODER2_Msk
#define GPIO_MODER_MODER2_0              (0x1UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER2_1              (0x2UL << GPIO_MODER_MODER2_Pos)
#define GPIO_MODER_MODER3_Pos            (6U)
#define GPIO_MODER_MODER3_Msk            (0x3UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER3                GPIO_MODER_MODER3_Msk
#define GPIO_MODER_MODER3_0              (0x1UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER3_1              (0x2UL << GPIO_MODER_MODER3_Pos)
#define GPIO_MODER_MODER4_Pos            (8U)
#define GPIO_MODER_MODER4_Msk            (0x3UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER4                GPIO_MODER_MODER4_Msk
#define GPIO_MODER_MODER4_0              (0x1UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER4_1              (0x2UL << GPIO_MODER_MODER4_Pos)
#define GPIO_MODER_MODER5_Pos            (10U)
#define GPIO_MODER_MODER5_Msk            (0x3UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5                GPIO_MODER_MODER5_Msk
#define GPIO_MODER_MODER5_0              (0x1UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER5_1              (0x2UL << GPIO_MODER_MODER5_Pos)
#define GPIO_MODER_MODER6_Pos            (12U)
#define GPIO_MODER_MODER6_Msk            (0x3UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER6                GPIO_MODER_MODER6_Msk
#define GPIO_MODER_MODER6_0              (0x1UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER6_1              (0x2UL << GPIO_MODER_MODER6_Pos)
#define GPIO_MODER_MODER7_Pos            (14U)
#define GPIO_MODER_MODER7_Msk            (0x3UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER7                GPIO_MODER_MODER7_Msk
#define GPIO_MODER_MODER7_0              (0x1UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER7_1              (0x2UL << GPIO_MODER_MODER7_Pos)
#define GPIO_MODER_MODER8_Pos            (16U)
#define GPIO_MODER_MODER8_Msk            (0x3UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER8                GPIO_MODER_MODER8_Msk
#define GPIO_MODER_MODER8_0              (0x1UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER8_1              (0x2UL << GPIO_MODER_MODER8_Pos)
#define GPIO_MODER_MODER9_Pos            (18U)
#define GPIO_MODER_MODER9_Msk            (0x3UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER9                GPIO_MODER_MODER9_Msk
#define GPIO_MODER_MODER9_0              (0x1UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER9_1              (0x2UL << GPIO_MODER_MODER9_Pos)
#define GPIO_MODER_MODER10_Pos           (20U)
#define GPIO_MODER_MODER10_Msk           (0x3UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER10               GPIO_MODER_MODER10_Msk
#define GPIO_MODER_MODER10_0             (0x1UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER10_1             (0x2UL << GPIO_MODER_MODER10_Pos)
#define GPIO_MODER_MODER11_Pos           (22U)
#define GPIO_MODER_MODER11_Msk           (0x3UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER11               GPIO_MODER_MODER11_Msk
#define GPIO_MODER_MODER11_0             (0x1UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER11_1             (0x2UL << GPIO_MODER_MODER11_Pos)
#define GPIO_MODER_MODER12_Pos           (24U)
#define GPIO_MODER_MODER12_Msk           (0x3UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER12               GPIO_MODER_MODER12_Msk
#define GPIO_MODER_MODER12_0             (0x1UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER12_1             (0x2UL << GPIO_MODER_MODER12_Pos)
#define GPIO_MODER_MODER13_Pos           (26U)
#define GPIO_MODER_MODER13_Msk           (0x3UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER13               GPIO_MODER_MODER13_Msk
#define GPIO_MODER_MODER13_0             (0x1UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER13_1             (0x2UL << GPIO_MODER_MODER13_Pos)
#define GPIO_MODER_MODER14_Pos           (28U)
#define GPIO_MODER_MODER14_Msk           (0x3UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER14               GPIO_MODER_MODER14_Msk
#define GPIO_MODER_MODER14_0             (0x1UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER14_1             (0x2UL << GPIO_MODER_MODER14_Pos)
#define GPIO_MODER_MODER15_Pos           (30U)
#define GPIO_MODER_MODER15_Msk           (0x3UL << GPIO_MODER_MODER15_Pos)
#define GPIO_MODER_MODER15               GPIO_MODER_MODER15_Msk
#define GPIO_MODER_MODER15_0             (0x1UL << GPIO_MODER_MODER15_Pos)
#define GPIO_MODER_MODER15_1             (0x2UL << GPIO_MODER_MODER15_Pos)

#define GPIO_MODER_MODE0_Pos             GPIO_MODER_MODER0_Pos
#define GPIO_MODER_MODE0_Msk             GPIO_MODER_MODER0_Msk
#define GPIO_MODER_MODE0                 GPIO_MODER_MODER0
#define GPIO_MODER_MODE0_0               GPIO_MODER_MODER0_0
#define GPIO_MODER_MODE0_1               GPIO_MODER_MODER0_1
#define GPIO_MODER_MODE1_Pos             GPIO_MODER_MODER1_Pos
#define GPIO_MODER_MODE1_Msk             GPIO_MODER_MODER1_Msk
#define GPIO_MODER_MODE1                 GPIO_MODER_MODER1
#define GPIO_MODER_MODE1_0               GPIO_MODER_MODER1_0
#define GPIO_MODER_MODE1_1               GPIO_MODER_MODER1_1
#define GPIO_MODER_MODE2_Pos             GPIO_MODER_MODER2_Pos
#define GPIO_MODER_MODE2_Msk             GPIO_MODER_MODER2_Msk
#define GPIO_MODER_MODE2                 GPIO_MODER_MODER2
#define GPIO_MODER_MODE2_0               GPIO_MODER_MODER2_0
#define GPIO_MODER_MODE2_1               GPIO_MODER_MODER2_1
#define GPIO_MODER_MODE3_Pos             GPIO_MODER_MODER3_Pos
#define GPIO_MODER_MODE3_Msk             GPIO_MODER_MODER3_Msk
#define GPIO_MODER_MODE3                 GPIO_MODER_MODER3
#define GPIO_MODER_MODE3_0               GPIO_MODER_MODER3_0
#define GPIO_MODER_MODE3_1               GPIO_MODER_MODER3_1
#define GPIO_MODER_MODE4_Pos             GPIO_MODER_MODER4_Pos
#define GPIO_MODER_MODE4_Msk             GPIO_MODER_MODER4_Msk
#define GPIO_MODER_MODE4                 GPIO_MODER_MODER4
#define GPIO_MODER_MODE4_0               GPIO_MODER_MODER4_0
#define GPIO_MODER_MODE4_1               GPIO_MODER_MODER4_1
#define GPIO_MODER_MODE5_Pos             GPIO_MODER_MODER5_Pos
#define GPIO_MODER_MODE5_Msk             GPIO_MODER_MODER5_Msk
#define GPIO_MODER_MODE5                 GPIO_MODER_MODER5
#define GPIO_MODER_MODE5_0               GPIO_MODER_MODER5_0
#define GPIO_MODER_MODE5_1               GPIO_MODER_MODER5_1
#define GPIO_MODER_MODE6_Pos             GPIO_MODER_MODER6_Pos
#define GPIO_MODER_MODE6_Msk             GPIO_MODER_MODER6_Msk
#define GPIO_MODER_MODE6                 GPIO_MODER_MODER6
#define GPIO_MODER_MODE6_0               GPIO_MODER_MODER6_0
#define GPIO_MODER_MODE6_1               GPIO_MODER_MODER6_1
#define GPIO_MODER_MODE7_Pos             GPIO_MODER_MODER7_Pos
#define GPIO_MODER_MODE7_Msk             GPIO_MODER_MODER7_Msk
#define GPIO_MODER_MODE7                 GPIO_MODER_MODER7
#define GPIO_MODER_MODE7_0               GPIO_MODER_MODER7_0
#define GPIO_MODER_MODE7_1               GPIO_MODER_MODER7_1
#define GPIO_MODER_MODE8_Pos             GPIO_MODER_MODER8_Pos
#define GPIO_MODER_MODE8_Msk             GPIO_MODER_MODER8_Msk
#define GPIO_MODER_MODE8                 GPIO_MODER_MODER8
#define GPIO_MODER_MODE8_0               GPIO_MODER_MODER8_0
#define GPIO_MODER_MODE8_1               GPIO_MODER_MODER8_1
#define GPIO_MODER_MODE9_Pos             GPIO_MODER_MODER9_Pos
#define GPIO_MODER_MODE9_Msk             GPIO_MODER_MODER9_Msk
#define GPIO_MODER_MODE9                 GPIO_MODER_MODER9
#define GPIO_MODER_MODE9_0               GPIO_MODER_MODER9_0
#define GPIO_MODER_MODE9_1               GPIO_MODER_MODER9_1
#define GPIO_MODER_MODE10_Pos            GPIO_MODER_MODER10_Pos
#define GPIO_MODER_MODE10_Msk            GPIO_MODER_MODER10_Msk
#define GPIO_MODER_MODE10                GPIO_MODER_MODER10
#define GPIO_MODER_MODE10_0              GPIO_MODER_MODER10_0
#define GPIO_MODER_MODE10_1              GPIO_MODER_MODER10_1
#define GPIO_MODER_MODE11_Pos            GPIO_MODER_MODER11_Pos
#define GPIO_MODER_MODE11_Msk            GPIO_MODER_MODER11_Msk
#define GPIO_MODER_MODE11                GPIO_MODER_MODER11
#define GPIO_MODER_MODE11_0              GPIO_MODER_MODER11_0
#define GPIO_MODER_MODE11_1              GPIO_MODER_MODER11_1
#define GPIO_MODER_MODE12_Pos            GPIO_MODER_MODER12_Pos
#define GPIO_MODER_MODE12_Msk            GPIO_MODER_MODER12_Msk
#define GPIO_MODER_MODE12                GPIO_MODER_MODER12
#define GPIO_MODER_MODE12_0              GPIO_MODER_MODER12_0
#define GPIO_MODER_MODE12_1              GPIO_MODER_MODER12_1
#define GPIO_MODER_MODE13_Pos            GPIO_MODER_MODER13_Pos
#define GPIO_MODER_MODE13_Msk            GPIO_MODER_MODER13_Msk
#define GPIO_MODER_MODE13                GPIO_MODER_MODER13
#define GPIO_MODER_MODE13_0              GPIO_MODER_MODER13_0
#define GPIO_MODER_MODE13_1              GPIO_MODER_MODER13_1
#define GPIO_MODER_MODE14_Pos            GPIO_MODER_MODER14_Pos
#define GPIO_MODER_MODE14_Msk            GPIO_MODER_MODER14_Msk
#define GPIO_MODER_MODE14                GPIO_MODER_MODER14
#define GPIO_MODER_MODE14_0              GPIO_MODER_MODER14_0
#define GPIO_MODER_MODE14_1              GPIO_MODER_MODER14_1
#define GPIO_MODER_MODE15_Pos            GPIO_MODER_MODER15_Pos
#define GPIO_MODER_MODE15_Msk            GPIO_MODER_MODER15_Msk
#define GPIO_MODER_MODE15                GPIO_MODER_MODER15
#define GPIO_MODER_MODE15_0              GPIO_MODER_MODER15_0
#define GPIO_MODER_MODE15_1              GPIO_MODER_MODER15_1

#define GPIO_OTYPER_OT0_Pos              (0U)
#define GPIO_OTYPER_OT0_Msk              (0x1UL << GPIO_OTYPER_OT0_Pos)
#define GPIO_OTYPER_OT0                  GPIO_OTYPER_OT0_Msk
#define GPIO_OTYPER_OT1_Pos              (1U)
#define GPIO_OTYPER_OT1_Msk              (0x1UL << GPIO_OTYPER_OT1_Pos)
#define GPIO_OTYPER_OT1                  GPIO_OTYPER_OT1_Msk
#define GPIO_OTYPER_OT2_Pos              (2U)
#define GPIO_OTYPER_OT2_Msk              (0x1UL << GPIO_OTYPER_OT2_Pos)
#define GPIO_OTYPER_OT2                  GPIO_OTYPER_OT2_Msk
#define GPIO_OTYPER_OT3_Pos              (3U)
#define GPIO_OTYPER_OT3_Msk              (0x1UL << GPIO_OTYPER_OT3_Pos)
#define GPIO_OTYPER_OT3                  GPIO_OTYPER_OT3_Msk
#define GPIO_OTYPER_OT4_Pos              (4U)
#define GPIO_OTYPER_OT4_Msk              (0x1UL << GPIO_OTYPER_OT4_Pos)
#define GPIO_OTYPER_OT4                  GPIO_OTYPER_OT4_Msk
#define GPIO_OTYPER_OT5_Pos              (5U)
#define GPIO_OTYPER_OT5_Msk              (0x1UL << GPIO_OTYPER_OT5_Pos)
#define GPIO_OTYPER_OT5                  GPIO_OTYPER_OT5_Msk
#define GPIO_OTYPER_OT6_Pos              (6U)
#define GPIO_OTYPER_OT6_Msk              (0x1UL << GPIO_OTYPER_OT6_Pos)
#define GPIO_OTYPER_OT6                  GPIO_OTYPER_OT6_Msk
#define GPIO_OTYPER_OT7_Pos              (7U)
#define GPIO_OTYPER_OT7_Msk              (0x1UL << GPIO_OTYPER_OT7_Pos)
#define GPIO_OTYPER_OT7                  GPIO_OTYPER_OT7_Msk
#define GPIO_OTYPER_OT8_Pos              (8U)
#define GPIO_OTYPER_OT8_Msk              (0x1UL << GPIO_OTYPER_OT8_Pos)
#define GPIO_OTYPER_OT8                  GPIO_OTYPER_OT8_Msk
#define GPIO_OTYPER_OT9_Pos              (9U)
#define GPIO_OTYPER_OT9_Msk              (0x1UL << GPIO_OTYPER_OT9_Pos)
#define GPIO_OTYPER_OT9                  GPIO_OTYPER_OT9_Msk
#define GPIO_OTYPER_OT10_Pos             (10U)
#define GPIO_OTYPER_OT10_Msk             (0x1UL << GPIO_OTYPER_OT10_Pos)
#define GPIO_OTYPER_OT10                 GPIO_OTYPER_OT10_Msk
#define GPIO_OTYPER_OT11_Pos             (11U)
#define GPIO_OTYPER_OT11_Msk             (0x1UL << GPIO_OTYPER_OT11_Pos)
#define GPIO_OTYPER_OT11                 GPIO_OTYPER_OT11_Msk
#define GPIO_OTYPER_OT12_Pos             (12U)
#define GPIO_OTYPER_OT12_Msk             (0x1UL << GPIO_OTYPER_OT12_Pos)
#define GPIO_OTYPER_OT12                 GPIO_OTYPER_OT12_Msk
#define GPIO_OTYPER_OT13_Pos             (13U)
#define GPIO_OTYPER_OT13_Msk             (0x1UL << GPIO_OTYPER_OT13_Pos)
#define GPIO_OTYPER_OT13                 GPIO_OTYPER_OT13_Msk
#define GPIO_OTYPER_OT14_Pos             (14U)
#define GPIO_OTYPER_OT14_Msk             (0x1UL << GPIO_OTYPER_OT14_Pos)
#define GPIO_OTYPER_OT14                 GPIO_OTYPER_OT14_Msk
#define GPIO_OTYPER_OT15_Pos             (15U)
#define GPIO_OTYPER_OT15_Msk             (0x1UL << GPIO_OTYPER_OT15_Pos)
#define GPIO_OTYPER_OT15                 GPIO_OTYPER_OT15_Msk

#define GPIO_OTYPER_OT_0                 GPIO_OTYPER_OT0
#define GPIO_OTYPER_OT_1                 GPIO_OTYPER_OT1
#define GPIO_OTYPER_OT_2                 GPIO_OTYPER_OT2
#define GPIO_OTYPER_OT_3                 GPIO_OTYPER_OT3
#define GPIO_OTYPER_OT_4                 GPIO_OTYPER_OT4
#define GPIO_OTYPER_OT_5                 GPIO_OTYPER_OT5
#define GPIO_OTYPER_OT_6                 GPIO_OTYPER_OT6
#define GPIO_OTYPER_OT_7                 GPIO_OTYPER_OT7
#define GPIO_OTYPER_OT_8                 GPIO_OTYPER_OT8
#define GPIO_OTYPER_OT_9                 GPIO_OTYPER_OT9
#define GPIO_OTYPER_OT_10                GPIO_OTYPER_OT10
#define GPIO_OTYPER_OT_11                GPIO_OTYPER_OT11
#define GPIO_OTYPER_OT_12                GPIO_OTYPER_OT12
#define GPIO_OTYPER_OT_13                GPIO_OTYPER_OT13
#define GPIO_OTYPER_OT_14                GPIO_OTYPER_OT14
#define GPIO_OTYPER_OT_15                GPIO_OTYPER_OT15

#define GPIO_OSPEEDR_OSPEED0_Pos         (0U)
#define GPIO_OSPEEDR_OSPEED0_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED0_Pos)
#define GPIO_OSPEEDR_OSPEED0             GPIO_OSPEEDR_OSPEED0_Msk
#define GPIO_OSPEEDR_OSPEED0_0           (0x1UL << GPIO_OSPEEDR_OSPEED0_Pos)
#define GPIO_OSPEEDR_OSPEED0_1           (0x2UL << GPIO_OSPEEDR_OSPEED0_Pos)
#define GPIO_OSPEEDR_OSPEED1_Pos         (2U)
#define GPIO_OSPEEDR_OSPEED1_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED1_Pos)
#define GPIO_OSPEEDR_OSPEED1             GPIO_OSPEEDR_OSPEED1_Msk
#define GPIO_OSPEEDR_OSPEED1_0           (0x1UL << GPIO_OSPEEDR_OSPEED1_Pos)
#define GPIO_OSPEEDR_OSPEED1_1           (0x2UL << GPIO_OSPEEDR_OSPEED1_Pos)
#define GPIO_OSPEEDR_OSPEED2_Pos         (4U)
#define GPIO_OSPEEDR_OSPEED2_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED2_Pos)
#define GPIO_OSPEEDR_OSPEED2             GPIO_OSPEEDR_OSPEED2_Msk
#define GPIO_OSPEEDR_OSPEED2_0           (0x1UL << GPIO_OSPEEDR_OSPEED2_Pos)
#define GPIO_OSPEEDR_OSPEED2_1           (0x2UL << GPIO_OSPEEDR_OSPEED2_Pos)
#define GPIO_OSPEEDR_OSPEED3_Pos         (6U)
#define GPIO_OSPEEDR_OSPEED3_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED3_Pos)
#define GPIO_OSPEEDR_OSPEED3             GPIO_OSPEEDR_OSPEED3_Msk
#define GPIO_OSPEEDR_OSPEED3_0           (0x1UL << GPIO_OSPEEDR_OSPEED3_Pos)
#define GPIO_OSPEEDR_OSPEED3_1           (0x2UL << GPIO_OSPEEDR_OSPEED3_Pos)
#define GPIO_OSPEEDR_OSPEED4_Pos         (8U)
#define GPIO_OSPEEDR_OSPEED4_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED4_Pos)
#define GPIO_OSPEEDR_OSPEED4             GPIO_OSPEEDR_OSPEED4_Msk
#define GPIO_OSPEEDR_OSPEED4_0           (0x1UL << GPIO_OSPEEDR_OSPEED4_Pos)
#define GPIO_OSPEEDR_OSPEED4_1           (0x2UL << GPIO_OSPEEDR_OSPEED4_Pos)
#define GPIO_OSPEEDR_OSPEED5_Pos         (10U)
#define GPIO_OSPEEDR_OSPEED5_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED5_Pos)
#define GPIO_OSPEEDR_OSPEED5             GPIO_OSPEEDR_OSPEED5_Msk
#define GPIO_OSPEEDR_OSPEED5_0           (0x1UL << GPIO_OSPEEDR_OSPEED5_Pos)
#define GPIO_OSPEEDR_OSPEED5_1           (0x2UL << GPIO_OSPEEDR_OSPEED5_Pos)
#define GPIO_OSPEEDR_OSPEED6_Pos         (12U)
#define GPIO_OSPEEDR_OSPEED6_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED6_Pos)
#define GPIO_OSPEEDR_OSPEED6             GPIO_OSPEEDR_OSPEED6_Msk
#define GPIO_OSPEEDR_OSPEED6_0           (0x1UL << GPIO_OSPEEDR_OSPEED6_Pos)
#define GPIO_OSPEEDR_OSPEED6_1           (0x2UL << GPIO_OSPEEDR_OSPEED6_Pos)
#define GPIO_OSPEEDR_OSPEED7_Pos         (14U)
#define GPIO_OSPEEDR_OSPEED7_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED7_Pos)
#define GPIO_OSPEEDR_OSPEED7             GPIO_OSPEEDR_OSPEED7_Msk
#define GPIO_OSPEEDR_OSPEED7_0           (0x1UL << GPIO_OSPEEDR_OSPEED7_Pos)
#define GPIO_OSPEEDR_OSPEED7_1           (0x2UL << GPIO_OSPEEDR_OSPEED7_Pos)
#define GPIO_OSPEEDR_OSPEED8_Pos         (16U)
#define GPIO_OSPEEDR_OSPEED8_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED8_Pos)
#define GPIO_OSPEEDR_OSPEED8             GPIO_OSPEEDR_OSPEED8_Msk
#define GPIO_OSPEEDR_OSPEED8_0           (0x1UL << GPIO_OSPEEDR_OSPEED8_Pos)
#define GPIO_OSPEEDR_OSPEED8_1           (0x2UL << GPIO_OSPEEDR_OSPEED8_Pos)
#define GPIO_OSPEEDR_OSPEED9_Pos         (18U)
#define GPIO_OSPEEDR_OSPEED9_Msk         (0x3UL << GPIO_OSPEEDR_OSPEED9_Pos)
#define GPIO_OSPEEDR_OSPEED9             GPIO_OSPEEDR_OSPEED9_Msk
#define GPIO_OSPEEDR_OSPEED9_0           (0x1UL << GPIO_OSPEEDR_OSPEED9_Pos)
#define GPIO_OSPEEDR_OSPEED9_1           (0x2UL << GPIO_OSPEEDR_OSPEED9_Pos)
#define GPIO_OSPEEDR_OSPEED10_Pos        (20U)
#define GPIO_OSPEEDR_OSPEED10_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED10_Pos)
#define GPIO_OSPEEDR_OSPEED10            GPIO_OSPEEDR_OSPEED10_Msk
#define GPIO_OSPEEDR_OSPEED10_0          (0x1UL << GPIO_OSPEEDR_OSPEED10_Pos)
#define GPIO_OSPEEDR_OSPEED10_1          (0x2UL << GPIO_OSPEEDR_OSPEED10_Pos)
#define GPIO_OSPEEDR_OSPEED11_Pos        (22U)
#define GPIO_OSPEEDR_OSPEED11_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED11_Pos)
#define GPIO_OSPEEDR_OSPEED11            GPIO_OSPEEDR_OSPEED11_Msk
#define GPIO_OSPEEDR_OSPEED11_0          (0x1UL << GPIO_OSPEEDR_OSPEED11_Pos)
#define GPIO_OSPEEDR_OSPEED11_1          (0x2UL << GPIO_OSPEEDR_OSPEED11_Pos)
#define GPIO_OSPEEDR_OSPEED12_Pos        (24U)
#define GPIO_OSPEEDR_OSPEED12_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED12_Pos)
#define GPIO_OSPEEDR_OSPEED12            GPIO_OSPEEDR_OSPEED12_Msk
#define GPIO_OSPEEDR_OSPEED12_0          (0x1UL << GPIO_OSPEEDR_OSPEED12_Pos)
#define GPIO_OSPEEDR_OSPEED12_1          (0x2UL << GPIO_OSPEEDR_OSPEED12_Pos)
#define GPIO_OSPEEDR_OSPEED13_Pos        (26U)
#define GPIO_OSPEEDR_OSPEED13_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED13_Pos)
#define GPIO_OSPEEDR_OSPEED13            GPIO_OSPEEDR_OSPEED13_Msk
#define GPIO_OSPEEDR_OSPEED13_0          (0x1UL << GPIO_OSPEEDR_OSPEED13_Pos)
#define GPIO_OSPEEDR_OSPEED13_1          (0x2UL << GPIO_OSPEEDR_OSPEED13_Pos)
#define GPIO_OSPEEDR_OSPEED14_Pos        (28U)
#define GPIO_OSPEEDR_OSPEED14_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED14_Pos)
#define GPIO_OSPEEDR_OSPEED14            GPIO_OSPEEDR_OSPEED14_Msk
#define GPIO_OSPEEDR_OSPEED14_0          (0x1UL << GPIO_OSPEEDR_OSPEED14_Pos)
#define GPIO_OSPEEDR_OSPEED14_1          (0x2UL << GPIO_OSPEEDR_OSPEED14_Pos)
#define GPIO_OSPEEDR_OSPEED15_Pos        (30U)
#define GPIO_OSPEEDR_OSPEED15_Msk        (0x3UL << GPIO_OSPEEDR_OSPEED15_Pos)
#define GPIO_OSPEEDR_OSPEED15            GPIO_OSPEEDR_OSPEED15_Msk
#define GPIO_OSPEEDR_OSPEED15_0          (0x1UL << GPIO_OSPEEDR_OSPEED15_Pos)
#define GPIO_OSPEEDR_OSPEED15_1          (0x2UL << GPIO_OSPEEDR_OSPEED15_Pos)

#define GPIO_OSPEEDER_OSPEEDR0           GPIO_OSPEEDR_OSPEED0
#define GPIO_OSPEEDER_OSPEEDR0_0         GPIO_OSPEEDR_OSPEED0_0
#define GPIO_OSPEEDER_OSPEEDR0_1         GPIO_OSPEEDR_OSPEED0_1
#define GPIO_OSPEEDER_OSPEEDR1           GPIO_OSPEEDR_OSPEED1
#define GPIO_OSPEEDER_OSPEEDR1_0         GPIO_OSPEEDR_OSPEED1_0
#define GPIO_OSPEEDER_OSPEEDR1_1         GPIO_OSPEEDR_OSPEED1_1
#define GPIO_OSPEEDER_OSPEEDR2           GPIO_OSPEEDR_OSPEED2
#define GPIO_OSPEEDER_OSPEEDR2_0         GPIO_OSPEEDR_OSPEED2_0
#define GPIO_OSPEEDER_OSPEEDR2_1         GPIO_OSPEEDR_OSPEED2_1
#define GPIO_OSPEEDER_OSPEEDR3           GPIO_OSPEEDR_OSPEED3
#define GPIO_OSPEEDER_OSPEEDR3_0         GPIO_OSPEEDR_OSPEED3_0
#define GPIO_OSPEEDER_OSPEEDR3_1         GPIO_OSPEEDR_OSPEED3_1
#define GPIO_OSPEEDER_OSPEEDR4           GPIO_OSPEEDR_OSPEED4
#define GPIO_OSPEEDER_OSPEEDR4_0         GPIO_OSPEEDR_OSPEED4_0
#define GPIO_OSPEEDER_OSPEEDR4_1         GPIO_OSPEEDR_OSPEED4_1
#define GPIO_OSPEEDER_OSPEEDR5           GPIO_OSPEEDR_OSPEED5
#define GPIO_OSPEEDER_OSPEEDR5_0         GPIO_OSPEEDR_OSPEED5_0
#define GPIO_OSPEEDER_OSPEEDR5_1         GPIO_OSPEEDR_OSPEED5_1
#define GPIO_OSPEEDER_OSPEEDR6           GPIO_OSPEEDR_OSPEED6
#define GPIO_OSPEEDER_OSPEEDR6_0         GPIO_OSPEEDR_OSPEED6_0
#define GPIO_OSPEEDER_OSPEEDR6_1         GPIO_OSPEEDR_OSPEED6_1
#define GPIO_OSPEEDER_OSPEEDR7           GPIO_OSPEEDR_OSPEED7
#define GPIO_OSPEEDER_OSPEEDR7_0         GPIO_OSPEEDR_OSPEED7_0
#define GPIO_OSPEEDER_OSPEEDR7_1         GPIO_OSPEEDR_OSPEED7_1
#define GPIO_OSPEEDER_OSPEEDR8           GPIO_OSPEEDR_OSPEED8
#define GPIO_OSPEEDER_OSPEEDR8_0         GPIO_OSPEEDR_OSPEED8_0
#define GPIO_OSPEEDER_OSPEEDR8_1         GPIO_OSPEEDR_OSPEED8_1
#define GPIO_OSPEEDER_OSPEEDR9           GPIO_OSPEEDR_OSPEED9
#define GPIO_OSPEEDER_OSPEEDR9_0         GPIO_OSPEEDR_OSPEED9_0
#define GPIO_OSPEEDER_OSPEEDR9_1         GPIO_OSPEEDR_OSPEED9_1
#define GPIO_OSPEEDER_OSPEEDR10          GPIO_OSPEEDR_OSPEED10
#define GPIO_OSPEEDER_OSPEEDR10_0        GPIO_OSPEEDR_OSPEED10_0
#define GPIO_OSPEEDER_OSPEEDR10_1        GPIO_OSPEEDR_OSPEED10_1
#define GPIO_OSPEEDER_OSPEEDR11          GPIO_OSPEEDR_OSPEED11
#define GPIO_OSPEEDER_OSPEEDR11_0        GPIO_OSPEEDR_OSPEED11_0
#define GPIO_OSPEEDER_OSPEEDR11_1        GPIO_OSPEEDR_OSPEED11_1
#define GPIO_OSPEEDER_OSPEEDR12          GPIO_OSPEEDR_OSPEED12
#define GPIO_OSPEEDER_OSPEEDR12_0        GPIO_OSPEEDR_OSPEED12_0
#define GPIO_OSPEEDER_OSPEEDR12_1        GPIO_OSPEEDR_OSPEED12_1
#define GPIO_OSPEEDER_OSPEEDR13          GPIO_OSPEEDR_OSPEED13
#define GPIO_OSPEEDER_OSPEEDR13_0        GPIO_OSPEEDR_OSPEED13_0
#define GPIO_OSPEEDER_OSPEEDR13_1        GPIO_OSPEEDR_OSPEED13_1
#define GPIO_OSPEEDER_OSPEEDR14          GPIO_OSPEEDR_OSPEED14
#define GPIO_OSPEEDER_OSPEEDR14_0        GPIO_OSPEEDR_OSPEED14_0
#define GPIO_OSPEEDER_OSPEEDR14_1        GPIO_OSPEEDR_OSPEED14_1
#define GPIO_OSPEEDER_OSPEEDR15          GPIO_OSPEEDR_OSPEED15
#define GPIO_OSPEEDER_OSPEEDR15_0        GPIO_OSPEEDR_OSPEED15_0
#define GPIO_OSPEEDER_OSPEEDR15_1        GPIO_OSPEEDR_OSPEED15_1

#define GPIO_PUPDR_PUPD0_Pos             (0U)
#define GPIO_PUPDR_PUPD0_Msk             (0x3UL << GPIO_PUPDR_PUPD0_Pos)
#define GPIO_PUPDR_PUPD0                 GPIO_PUPDR_PUPD0_Msk
#define GPIO_PUPDR_PUPD0_0               (0x1UL << GPIO_PUPDR_PUPD0_Pos)
#define GPIO_PUPDR_PUPD0_1               (0x2UL << GPIO_PUPDR_PUPD0_Pos)
#define GPIO_PUPDR_PUPD1_Pos             (2U)
#define GPIO_PUPDR_PUPD1_Msk             (0x3UL << GPIO_PUPDR_PUPD1_Pos)
#define GPIO_PUPDR_PUPD1                 GPIO_PUPDR_PUPD1_Msk
#define GPIO_PUPDR_PUPD1_0               (0x1UL << GPIO_PUPDR_PUPD1_Pos)
#define GPIO_PUPDR_PUPD1_1               (0x2UL << GPIO_PUPDR_PUPD1_Pos)
#define GPIO_PUPDR_PUPD2_Pos             (4U)
#define GPIO_PUPDR_PUPD2_Msk             (0x3UL << GPIO_PUPDR_PUPD2_Pos)
#define GPIO_PUPDR_PUPD2                 GPIO_PUPDR_PUPD2_Msk
#define GPIO_PUPDR_PUPD2_0               (0x1UL << GPIO_PUPDR_PUPD2_Pos)
#define GPIO_PUPDR_PUPD2_1               (0x2UL << GPIO_PUPDR_PUPD2_Pos)
#define GPIO_PUPDR_PUPD3_Pos             (6U)
#define GPIO_PUPDR_PUPD3_Msk             (0x3UL << GPIO_PUPDR_PUPD3_Pos)
#define GPIO_PUPDR_PUPD3                 GPIO_PUPDR_PUPD3_Msk
#define GPIO_PUPDR_PUPD3_0               (0x1UL << GPIO_PUPDR_PUPD3_Pos)
#define GPIO_PUPDR_PUPD3_1               (0x2UL << GPIO_PUPDR_PUPD3_Pos)
#define GPIO_PUPDR_PUPD4_Pos             (8U)
#define GPIO_PUPDR_PUPD4_Msk             (0x3UL << GPIO_PUPDR_PUPD4_Pos)
#define GPIO_PUPDR_PUPD4                 GPIO_PUPDR_PUPD4_Msk
#define GPIO_PUPDR_PUPD4_0               (0x1UL << GPIO_PUPDR_PUPD4_Pos)
#define GPIO_PUPDR_PUPD4_1               (0x2UL << GPIO_PUPDR_PUPD4_Pos)
#define GPIO_PUPDR_PUPD5_Pos             (10U)
#define GPIO_PUPDR_PUPD5_Msk             (0x3UL << GPIO_PUPDR_PUPD5_Pos)
#define GPIO_PUPDR_PUPD5                 GPIO_PUPDR_PUPD5_Msk
#define GPIO_PUPDR_PUPD5_0               (0x1UL << GPIO_PUPDR_PUPD5_Pos)
#define GPIO_PUPDR_PUPD5_1               (0x2UL << GPIO_PUPDR_PUPD5_Pos)
#define GPIO_PUPDR_PUPD6_Pos             (12U)
#define GPIO_PUPDR_PUPD6_Msk             (0x3UL << GPIO_PUPDR_PUPD6_Pos)
#define GPIO_PUPDR_PUPD6                 GPIO_PUPDR_PUPD6_Msk
#define GPIO_PUPDR_PUPD6_0               (0x1UL << GPIO_PUPDR_PUPD6_Pos)
#define GPIO_PUPDR_PUPD6_1               (0x2UL << GPIO_PUPDR_PUPD6_Pos)
#define GPIO_PUPDR_PUPD7_Pos             (14U)
#define GPIO_PUPDR_PUPD7_Msk             (0x3UL << GPIO_PUPDR_PUPD7_Pos)
#define GPIO_PUPDR_PUPD7                 GPIO_PUPDR_PUPD7_Msk
#define GPIO_PUPDR_PUPD7_0               (0x1UL << GPIO_PUPDR_PUPD7_Pos)
#define GPIO_PUPDR_PUPD7_1               (0x2UL << GPIO_PUPDR_PUPD7_Pos)
#define GPIO_PUPDR_PUPD8_Pos             (16U)
#define GPIO_PUPDR_PUPD8_Msk             (0x3UL << GPIO_PUPDR_PUPD8_Pos)
#define GPIO_PUPDR_PUPD8                 GPIO_PUPDR_PUPD8_Msk
#define GPIO_PUPDR_PUPD8_0               (0x1UL << GPIO_PUPDR_PUPD8_Pos)
#define GPIO_PUPDR_PUPD8_1               (0x2UL << GPIO_PUPDR_PUPD8_Pos)
#define GPIO_PUPDR_PUPD9_Pos             (18U)
#define GPIO_PUPDR_PUPD9_Msk             (0x3UL << GPIO_PUPDR_PUPD9_Pos)
#define GPIO_PUPDR_PUPD9                 GPIO_PUPDR_PUPD9_Msk
#define GPIO_PUPDR_PUPD9_0               (0x1UL << GPIO_PUPDR_PUPD9_Pos)
#define GPIO_PUPDR_PUPD9_1               (0x2UL << GPIO_PUPDR_PUPD9_Pos)
#define GPIO_PUPDR_PUPD10_Pos            (20U)
#define GPIO_PUPDR_PUPD10_Msk            (0x3UL << GPIO_PUPDR_PUPD10_Pos)
#define GPIO_PUPDR_PUPD10                GPIO_PUPDR_PUPD10_Msk
#define GPIO_PUPDR_PUPD10_0              (0x1UL << GPIO_PUPDR_PUPD10_Pos)
#define GPIO_PUPDR_PUPD10_1              (0x2UL << GPIO_PUPDR_PUPD10_Pos)
#define GPIO_PUPDR_PUPD11_Pos            (22U)
#define GPIO_PUPDR_PUPD11_Msk            (0x3UL << GPIO_PUPDR_PUPD11_Pos)
#define GPIO_PUPDR_PUPD11                GPIO_PUPDR_PUPD11_Msk
#define GPIO_PUPDR_PUPD11_0              (0x1UL << GPIO_PUPDR_PUPD11_Pos)
#define GPIO_PUPDR_PUPD11_1              (0x2UL << GPIO_PUPDR_PUPD11_Pos)
#define GPIO_PUPDR_PUPD12_Pos            (24U)
#define GPIO_PUPDR_PUPD12_Msk            (0x3UL << GPIO_PUPDR_PUPD12_Pos)
#define GPIO_PUPDR_PUPD12                GPIO_PUPDR_PUPD12_Msk
#define GPIO_PUPDR_PUPD12_0              (0x1UL << GPIO_PUPDR_PUPD12_Pos)
#define GPIO_PUPDR_PUPD12_1              (0x2UL << GPIO_PUPDR_PUPD12_Pos)
#define GPIO_PUPDR_PUPD13_Pos            (26U)
#define GPIO_PUPDR_PUPD13_Msk            (0x3UL << GPIO_PUPDR_PUPD13_Pos)
#define GPIO_PUPDR_PUPD13                GPIO_PUPDR_PUPD13_Msk
#define GPIO_PUPDR_PUPD13_0              (0x1UL << GPIO_PUPDR_PUPD13_Pos)
#define GPIO_PUPDR_PUPD13_1              (0x2UL << GPIO_PUPDR_PUPD13_Pos)
#define GPIO_PUPDR_PUPD14_Pos            (28U)
#define GPIO_PUPDR_PUPD14_Msk            (0x3UL << GPIO_PUPDR_PUPD14_Pos)
#define GPIO_PUPDR_PUPD14                GPIO_PUPDR_PUPD14_Msk
#define GPIO_PUPDR_PUPD14_0              (0x1UL << GPIO_PUPDR_PUPD14_Pos)
#define GPIO_PUPDR_PUPD14_1              (0x2UL << GPIO_PUPDR_PUPD14_Pos)
#define GPIO_PUPDR_PUPD15_Pos            (30U)
#define GPIO_PUPDR_PUPD15_Msk            (0x3UL << GPIO_PUPDR_PUPD15_Pos)
#define GPIO_PUPDR_PUPD15                GPIO_PUPDR_PUPD15_Msk
#define GPIO_PUPDR_PUPD15_0              (0x1UL << GPIO_PUPDR_PUPD15_Pos)
#define GPIO_PUPDR_PUPD15_1              (0x2UL << GPIO_PUPDR_PUPD15_Pos)

#define GPIO_PUPDR_PUPDR0                GPIO_PUPDR_PUPD0
#define GPIO_PUPDR_PUPDR0_0              GPIO_PUPDR_PUPD0_0
#define GPIO_PUPDR_PUPDR0_1              GPIO_PUPDR_PUPD0_1
#define GPIO_PUPDR_PUPDR1                GPIO_PUPDR_PUPD1
#define GPIO_PUPDR_PUPDR1_0              GPIO_PUPDR_PUPD1_0
#define GPIO_PUPDR_PUPDR1_1              GPIO_PUPDR_PUPD1_1
#define GPIO_PUPDR_PUPDR2                GPIO_PUPDR_PUPD2
#define GPIO_PUPDR_PUPDR2_0              GPIO_PUPDR_PUPD2_0
#define GPIO_PUPDR_PUPDR2_1              GPIO_PUPDR_PUPD2_1
#define GPIO_PUPDR_PUPDR3                GPIO_PUPDR_PUPD3
#define GPIO_PUPDR_PUPDR3_0              GPIO_PUPDR_PUPD3_0
#define GPIO_PUPDR_PUPDR3_1              GPIO_PUPDR_PUPD3_1
#define GPIO_PUPDR_PUPDR4                GPIO_PUPDR_PUPD4
#define GPIO_PUPDR_PUPDR4_0              GPIO_PUPDR_PUPD4_0
#define GPIO_PUPDR_PUPDR4_1              GPIO_PUPDR_PUPD4_1
#define GPIO_PUPDR_PUPDR5                GPIO_PUPDR_PUPD5
#define GPIO_PUPDR_PUPDR5_0              GPIO_PUPDR_PUPD5_0
#define GPIO_PUPDR_PUPDR5_1              GPIO_PUPDR_PUPD5_1
#define GPIO_PUPDR_PUPDR6                GPIO_PUPDR_PUPD6
#define GPIO_PUPDR_PUPDR6_0              GPIO_PUPDR_PUPD6_0
#define GPIO_PUPDR_PUPDR6_1              GPIO_PUPDR_PUPD6_1
#define GPIO_PUPDR_PUPDR7                GPIO_PUPDR_PUPD7
#define GPIO_PUPDR_PUPDR7_0              GPIO_PUPDR_PUPD7_0
#define GPIO_PUPDR_PUPDR7_1              GPIO_PUPDR_PUPD7_1
#define GPIO_PUPDR_PUPDR8                GPIO_PUPDR_PUPD8
#define GPIO_PUPDR_PUPDR8_0              GPIO_PUPDR_PUPD8_0
#define GPIO_PUPDR_PUPDR8_1              GPIO_PUPDR_PUPD8_1
#define GPIO_PUPDR_PUPDR9                GPIO_PUPDR_PUPD9
#define GPIO_PUPDR_PUPDR9_0              GPIO_PUPDR_PUPD9_0
#define GPIO_PUPDR_PUPDR9_1              GPIO_PUPDR_PUPD9_1
#define GPIO_PUPDR_PUPDR10               GPIO_PUPDR_PUPD10
#define GPIO_PUPDR_PUPDR10_0             GPIO_PUPDR_PUPD10_0
#define GPIO_PUPDR_PUPDR10_1             GPIO_PUPDR_PUPD10_1
#define GPIO_PUPDR_PUPDR11               GPIO_PUPDR_PUPD11
#define GPIO_PUPDR_PUPDR11_0             GPIO_PUPDR_PUPD11_0
#define GPIO_PUPDR_PUPDR11_1             GPIO_PUPDR_PUPD11_1
#define GPIO_PUPDR_PUPDR12               GPIO_PUPDR_PUPD12
#define GPIO_PUPDR_PUPDR12_0             GPIO_PUPDR_PUPD12_0
#define GPIO_PUPDR_PUPDR12_1             GPIO_PUPDR_PUPD12_1
#define GPIO_PUPDR_PUPDR13               GPIO_PUPDR_PUPD13
#define GPIO_PUPDR_PUPDR13_0             GPIO_PUPDR_PUPD13_0
#define GPIO_PUPDR_PUPDR13_1             GPIO_PUPDR_PUPD13_1
#define GPIO_PUPDR_PUPDR14               GPIO_PUPDR_PUPD14
#define GPIO_PUPDR_PUPDR14_0             GPIO_PUPDR_PUPD14_0
#define GPIO_PUPDR_PUPDR14_1             GPIO_PUPDR_PUPD14_1
#define GPIO_PUPDR_PUPDR15               GPIO_PUPDR_PUPD15
#define GPIO_PUPDR_PUPDR15_0             GPIO_PUPDR_PUPD15_0
#define GPIO_PUPDR_PUPDR15_1             GPIO_PUPDR_PUPD15_1

#define GPIO_IDR_ID0_Pos                 (0U)
#define GPIO_IDR_ID0_Msk                 (0x1UL << GPIO_IDR_ID0_Pos)
#define GPIO_IDR_ID0                     GPIO_IDR_ID0_Msk
#define GPIO_IDR_ID1_Pos                 (1U)
#define GPIO_IDR_ID1_Msk                 (0x1UL << GPIO_IDR_ID1_Pos)
#define GPIO_IDR_ID1                     GPIO_IDR_ID1_Msk
#define GPIO_IDR_ID2_Pos                 (2U)
#define GPIO_IDR_ID2_Msk                 (0x1UL << GPIO_IDR_ID2_Pos)
#define GPIO_IDR_ID2                     GPIO_IDR_ID2_Msk
#define GPIO_IDR_ID3_Pos                 (3U)
#define GPIO_IDR_ID3_Msk                 (0x1UL << GPIO_IDR_ID3_Pos)
#define GPIO_IDR_ID3                     GPIO_IDR_ID3_Msk
#define GPIO_IDR_ID4_Pos                 (4U)
#define GPIO_IDR_ID4_Msk                 (0x1UL << GPIO_IDR_ID4_Pos)
#define GPIO_IDR_ID4                     GPIO_IDR_ID4_Msk
#define GPIO_IDR_ID5_Pos                 (5U)
#define GPIO_IDR_ID5_Msk                 (0x1UL << GPIO_IDR_ID5_Pos)
#define GPIO_IDR_ID5                     GPIO_IDR_ID5_Msk
#define GPIO_IDR_ID6_Pos                 (6U)
#define GPIO_IDR_ID6_Msk                 (0x1UL << GPIO_IDR_ID6_Pos)
#define GPIO_IDR_ID6                     GPIO_IDR_ID6_Msk
#define GPIO_IDR_ID7_Pos                 (7U)
#define GPIO_IDR_ID7_Msk                 (0x1UL << GPIO_IDR_ID7_Pos)
#define GPIO_IDR_ID7                     GPIO_IDR_ID7_Msk
#define GPIO_IDR_ID8_Pos                 (8U)
#define GPIO_IDR_ID8_Msk                 (0x1UL << GPIO_IDR_ID8_Pos)
#define GPIO_IDR_ID8                     GPIO_IDR_ID8_Msk
#define GPIO_IDR_ID9_Pos                 (9U)
#define GPIO_IDR_ID9_Msk                 (0x1UL << GPIO_IDR_ID9_Pos)
#define GPIO_IDR_ID9                     GPIO_IDR_ID9_Msk
#define GPIO_IDR_ID10_Pos                (10U)
#define GPIO_IDR_ID10_Msk                (0x1UL << GPIO_IDR_ID10_Pos)
#define GPIO_IDR_ID10                    GPIO_IDR_ID10_Msk
#define GPIO_IDR_ID11_Pos                (11U)
#define GPIO_IDR_ID11_Msk                (0x1UL << GPIO_IDR_ID11_Pos)
#define GPIO_IDR_ID11                    GPIO_IDR_ID11_Msk
#define GPIO_IDR_ID12_Pos                (12U)
#define GPIO_IDR_ID12_Msk                (0x1UL << GPIO_IDR_ID12_Pos)
#define GPIO_IDR_ID12                    GPIO_IDR_ID12_Msk
#define GPIO_IDR_ID13_Pos                (13U)
#define GPIO_IDR_ID13_Msk                (0x1UL << GPIO_IDR_ID13_Pos)
#define GPIO_IDR_ID13                    GPIO_IDR_ID13_Msk
#define GPIO_IDR_ID14_Pos                (14U)
#define GPIO_IDR_ID14_Msk                (0x1UL << GPIO_IDR_ID14_Pos)
#define GPIO_IDR_ID14                    GPIO_IDR_ID14_Msk
#define GPIO_IDR_ID15_Pos                (15U)
#define GPIO_IDR_ID15_Msk                (0x1UL << GPIO_IDR_ID15_Pos)
#define GPIO_IDR_ID15                    GPIO_IDR_ID15_Msk

#define GPIO_IDR_IDR_0                   GPIO_IDR_ID0
#define GPIO_IDR_IDR_1                   GPIO_IDR_ID1
#define GPIO_IDR_IDR_2                   GPIO_IDR_ID2
#define GPIO_IDR_IDR_3                   GPIO_IDR_ID3
#define GPIO_IDR_IDR_4                   GPIO_IDR_ID4
#define GPIO_IDR_IDR_5                   GPIO_IDR_ID5
#define GPIO_IDR_IDR_6                   GPIO_IDR_ID6
#define GPIO_IDR_IDR_7                   GPIO_IDR_ID7
#define GPIO_IDR_IDR_8                   GPIO_IDR_ID8
#define GPIO_IDR_IDR_9                   GPIO_IDR_ID9
#define GPIO_IDR_IDR_10                  GPIO_IDR_ID10
#define GPIO_IDR_IDR_11                  GPIO_IDR_ID11
#define GPIO_IDR_IDR_12                  GPIO_IDR_ID12
#define GPIO_IDR_IDR_13                  GPIO_IDR_ID13
#define GPIO_IDR_IDR_14                  GPIO_IDR_ID14
#define GPIO_IDR_IDR_15                  GPIO_IDR_ID15

#define GPIO_ODR_OD0_Pos                 (0U)
#define GPIO_ODR_OD0_Msk                 (0x1UL << GPIO_ODR_OD0_Pos)
#define GPIO_ODR_OD0                     GPIO_ODR_OD0_Msk
#define GPIO_ODR_OD1_Pos                 (1U)
#define GPIO_ODR_OD1_Msk                 (0x1UL << GPIO_ODR_OD1_Pos)
#define GPIO_ODR_OD1                     GPIO_ODR_OD1_Msk
#define GPIO_ODR_OD2_Pos                 (2U)
#define GPIO_ODR_OD2_Msk                 (0x1UL << GPIO_ODR_OD2_Pos)
#define GPIO_ODR_OD2                     GPIO_ODR_OD2_Msk
#define GPIO_ODR_OD3_Pos                 (3U)
#define GPIO_ODR_OD3_Msk                 (0x1UL << GPIO_ODR_OD3_Pos)
#define GPIO_ODR_OD3                     GPIO_ODR_OD3_Msk
#define GPIO_ODR_OD4_Pos                 (4U)
#define GPIO_ODR_OD4_Msk                 (0x1UL << GPIO_ODR_OD4_Pos)
#define GPIO_ODR_OD4                     GPIO_ODR_OD4_Msk
#define GPIO_ODR_OD5_Pos                 (5U)
#define GPIO_ODR_OD5_Msk                 (0x1UL << GPIO_ODR_OD5_Pos)
#define GPIO_ODR_OD5                     GPIO_ODR_OD5_Msk
#define GPIO_ODR_OD6_Pos                 (6U)
#define GPIO_ODR_OD6_Msk                 (0x1UL << GPIO_ODR_OD6_Pos)
#define GPIO_ODR_OD6                     GPIO_ODR_OD6_Msk
#define GPIO_ODR_OD7_Pos                 (7U)
#define GPIO_ODR_OD7_Msk                 (0x1UL << GPIO_ODR_OD7_Pos)
#define GPIO_ODR_OD7                     GPIO_ODR_OD7_Msk
#define GPIO_ODR_OD8_Pos                 (8U)
#define GPIO_ODR_OD8_Msk                 (0x1UL << GPIO_ODR_OD8_Pos)
#define GPIO_ODR_OD8                     GPIO_ODR_OD8_Msk
#define GPIO_ODR_OD9_Pos                 (9U)
#define GPIO_ODR_OD9_Msk                 (0x1UL << GPIO_ODR_OD9_Pos)
#define GPIO_ODR_OD9                     GPIO_ODR_OD9_Msk
#define GPIO_ODR_OD10_Pos                (10U)
#define GPIO_ODR_OD10_Msk                (0x1UL << GPIO_ODR_OD10_Pos)
#define GPIO_ODR_OD10                    GPIO_ODR_OD10_Msk
#define GPIO_ODR_OD11_Pos                (11U)
#define GPIO_ODR_OD11_Msk                (0x1UL << GPIO_ODR_OD11_Pos)
#define GPIO_ODR_OD11                    GPIO_ODR_OD11_Msk
#define GPIO_ODR_OD12_Pos                (12U)
#define GPIO_ODR_OD12_Msk                (0x1UL << GPIO_ODR_OD12_Pos)
#define GPIO_ODR_OD12                    GPIO_ODR_OD12_Msk
#define GPIO_ODR_OD13_Pos                (13U)
#define GPIO_ODR_OD13_Msk                (0x1UL << GPIO_ODR_OD13_Pos)
#define GPIO_ODR_OD13                    GPIO_ODR_OD13_Msk
#define GPIO_ODR_OD14_Pos                (14U)
#define GPIO_ODR_OD14_Msk                (0x1UL << GPIO_ODR_OD14_Pos)
#define GPIO_ODR_OD14                    GPIO_ODR_OD14_Msk
#define GPIO_ODR_OD15_Pos                (15U)
#define GPIO_ODR_OD15_Msk                (0x1UL << GPIO_ODR_OD15_Pos)
#define GPIO_ODR_OD15                    GPIO_ODR_OD15_Msk

#define GPIO_ODR_ODR_0                   GPIO_ODR_OD0
#define GPIO_ODR_ODR_1                   GPIO_ODR_OD1
#define GPIO_ODR_ODR_2                   GPIO_ODR_OD2
#define GPIO_ODR_ODR_3                   GPIO_ODR_OD3
#define GPIO_ODR_ODR_4                   GPIO_ODR_OD4
#define GPIO_ODR_ODR_5                   GPIO_ODR_OD5
#define GPIO_ODR_ODR_6                   GPIO_ODR_OD6
#define GPIO_ODR_ODR_7                   GPIO_ODR_OD7
#define GPIO_ODR_ODR_8                   GPIO_ODR_OD8
#define GPIO_ODR_ODR_9                   GPIO_ODR_OD9
#define GPIO_ODR_ODR_10                  GPIO_ODR_OD10
#define GPIO_ODR_ODR_11                  GPIO_ODR_OD11
#define GPIO_ODR_ODR_12                  GPIO_ODR_OD12
#define GPIO_ODR_ODR_13                  GPIO_ODR_OD13
#define GPIO_ODR_ODR_14                  GPIO_ODR_OD14
#define GPIO_ODR_ODR_15                  GPIO_ODR_OD15

#define GPIO_BSRR_BS0_Pos                (0U)
#define GPIO_BSRR_BS0_Msk                (0x1UL << GPIO_BSRR_BS0_Pos)
#define GPIO_BSRR_BS0                    GPIO_BSRR_BS0_Msk
#define GPIO_BSRR_BS1_Pos                (1U)
#define GPIO_BSRR_BS1_Msk                (0x1UL << GPIO_BSRR_BS1_Pos)
#define GPIO_BSRR_BS1                    GPIO_BSRR_BS1_Msk
#define GPIO_BSRR_BS2_Pos                (2U)
#define GPIO_BSRR_BS2_Msk                (0x1UL << GPIO_BSRR_BS2_Pos)
#define GPIO_BSRR_BS2                    GPIO_BSRR_BS2_Msk
#define GPIO_BSRR_BS3_Pos                (3U)
#define GPIO_BSRR_BS3_Msk                (0x1UL << GPIO_BSRR_BS3_Pos)
#define GPIO_BSRR_BS3                    GPIO_BSRR_BS3_Msk
#define GPIO_BSRR_BS4_Pos                (4U)
#define GPIO_BSRR_BS4_Msk                (0x1UL << GPIO_BSRR_BS4_Pos)
#define GPIO_BSRR_BS4                    GPIO_BSRR_BS4_Msk
#define GPIO_BSRR_BS5_Pos                (5U)
#define GPIO_BSRR_BS5_Msk                (0x1UL << GPIO_BSRR_BS5_Pos)
#define GPIO_BSRR_BS5                    GPIO_BSRR_BS5_Msk
#define GPIO_BSRR_BS6_Pos                (6U)
#define GPIO_BSRR_BS6_Msk                (0x1UL << GPIO_BSRR_BS6_Pos)
#define GPIO_BSRR_BS6                    GPIO_BSRR_BS6_Msk
#define GPIO_BSRR_BS7_Pos                (7U)
#define GPIO_BSRR_BS7_Msk                (0x1UL << GPIO_BSRR_BS7_Pos)
#define GPIO_BSRR_BS7                    GPIO_BSRR_BS7_Msk
#define GPIO_BSRR_BS8_Pos                (8U)
#define GPIO_BSRR_BS8_Msk                (0x1UL << GPIO_BSRR_BS8_Pos)
#define GPIO_BSRR_BS8                    GPIO_BSRR_BS8_Msk
#define GPIO_BSRR_BS9_Pos                (9U)
#define GPIO_BSRR_BS9_Msk                (0x1UL << GPIO_BSRR_BS9_Pos)
#define GPIO_BSRR_BS9                    GPIO_BSRR_BS9_Msk
#define GPIO_BSRR_BS10_Pos               (10U)
#define GPIO_BSRR_BS10_Msk               (0x1UL << GPIO_BSRR_BS10_Pos)
#define GPIO_BSRR_BS10                   GPIO_BSRR_BS10_Msk
#define GPIO_BSRR_BS11_Pos               (11U)
#define GPIO_BSRR_BS11_Msk               (0x1UL << GPIO_BSRR_BS11_Pos)
#define GPIO_BSRR_BS11                   GPIO_BSRR_BS11_Msk
#define GPIO_BSRR_BS12_Pos               (12U)
#define GPIO_BSRR_BS12_Msk               (0x1UL << GPIO_BSRR_BS12_Pos)
#define GPIO_BSRR_BS12                   GPIO_BSRR_BS12_Msk
#define GPIO_BSRR_BS13_Pos               (13U)
#define GPIO_BSRR_BS13_Msk               (0x1UL << GPIO_BSRR_BS13_Pos)
#define GPIO_BSRR_BS13                   GPIO_BSRR_BS13_Msk
#define GPIO_BSRR_BS14_Pos               (14U)
#define GPIO_BSRR_BS14_Msk               (0x1UL << GPIO_BSRR_BS14_Pos)
#define GPIO_BSRR_BS14                   GPIO_BSRR_BS14_Msk
#define GPIO_BSRR_BS15_Pos               (15U)
#define GPIO_BSRR_BS15_Msk               (0x1UL << GPIO_BSRR_BS15_Pos)
#define GPIO_BSRR_BS15                   GPIO_BSRR_BS15_Msk
#define GPIO_BSRR_BR0_Pos                (16U)
#define GPIO_BSRR_BR0_Msk                (0x1UL << GPIO_BSRR_BR0_Pos)
#define GPIO_BSRR_BR0                    GPIO_BSRR_BR0_Msk
#define GPIO_BSRR_BR1_Pos                (17U)
#define GPIO_BSRR_BR1_Msk                (0x1UL << GPIO_BSRR_BR1_Pos)
#define GPIO_BSRR_BR1                    GPIO_BSRR_BR1_Msk
#define GPIO_BSRR_BR2_Pos                (18U)
#define GPIO_BSRR_BR2_Msk                (0x1UL << GPIO_BSRR_BR2_Pos)
#define GPIO_BSRR_BR2                    GPIO_BSRR_BR2_Msk
#define GPIO_BSRR_BR3_Pos                (19U)
#define GPIO_BSRR_BR3_Msk                (0x1UL << GPIO_BSRR_BR3_Pos)
#define GPIO_BSRR_BR3                    GPIO_BSRR_BR3_Msk
#define GPIO_BSRR_BR4_Pos                (20U)
#define GPIO_BSRR_BR4_Msk                (0x1UL << GPIO_BSRR_BR4_Pos)
#define GPIO_BSRR_BR4                    GPIO_BSRR_BR4_Msk
#define GPIO_BSRR_BR5_Pos                (21U)
#define GPIO_BSRR_BR5_Msk                (0x1UL << GPIO_BSRR_BR5_Pos)
#define GPIO_BSRR_BR5                    GPIO_BSRR_BR5_Msk
#define GPIO_BSRR_BR6_Pos                (22U)
#define GPIO_BSRR_BR6_Msk                (0x1UL << GPIO_BSRR_BR6_Pos)
#define GPIO_BSRR_BR6                    GPIO_BSRR_BR6_Msk
#define GPIO_BSRR_BR7_Pos                (23U)
#define GPIO_BSRR_BR7_Msk                (0x1UL << GPIO_BSRR_BR7_Pos)
#define GPIO_BSRR_BR7                    GPIO_BSRR_BR7_Msk
#define GPIO_BSRR_BR8_Pos                (24U)
#define GPIO_BSRR_BR8_Msk                (0x1UL << GPIO_BSRR_BR8_Pos)
#define GPIO_BSRR_BR8                    GPIO_BSRR_BR8_Msk
#define GPIO_BSRR_BR9_Pos                (25U)
#define GPIO_BSRR_BR9_Msk                (0x1UL << GPIO_BSRR_BR9_Pos)
#define GPIO_BSRR_BR9                    GPIO_BSRR_BR9_Msk
#define GPIO_BSRR_BR10_Pos               (26U)
#define GPIO_BSRR_BR10_Msk               (0x1UL << GPIO_BSRR_BR10_Pos)
#define GPIO_BSRR_BR10                   GPIO_BSRR_BR10_Msk
#define GPIO_BSRR_BR11_Pos               (27U)
#define GPIO_BSRR_BR11_Msk               (0x1UL << GPIO_BSRR_BR11_Pos)
#define GPIO_BSRR_BR11                   GPIO_BSRR_BR11_Msk
#define GPIO_BSRR_BR12_Pos               (28U)
#define GPIO_BSRR_BR12_Msk               (0x1UL << GPIO_BSRR_BR12_Pos)
#define GPIO_BSRR_BR12                   GPIO_BSRR_BR12_Msk
#define GPIO_BSRR_BR13_Pos               (29U)
#define GPIO_BSRR_BR13_Msk               (0x1UL << GPIO_BSRR_BR13_Pos)
#define GPIO_BSRR_BR13                   GPIO_BSRR_BR13_Msk
#define GPIO_BSRR_BR14_Pos               (30U)
#define GPIO_BSRR_BR14_Msk               (0x1UL << GPIO_BSRR_BR14_Pos)
#define GPIO_BSRR_BR14                   GPIO_BSRR_BR14_Msk
#define GPIO_BSRR_BR15_Pos               (31U)
#define GPIO_BSRR_BR15_Msk               (0x1UL << GPIO_BSRR_BR15_Pos)
#define GPIO_BSRR_BR15                   GPIO_BSRR_BR15_Msk

#define GPIO_BSRR_BS_0                   GPIO_BSRR_BS0
#define GPIO_BSRR_BS_1                   GPIO_BSRR_BS1
#define GPIO_BSRR_BS_2                   GPIO_BSRR_BS2
#define GPIO_BSRR_BS_3                   GPIO_BSRR_BS3
#define GPIO_BSRR_BS_4                   GPIO_BSRR_BS4
#define GPIO_BSRR_BS_5                   GPIO_BSRR_BS5
#define GPIO_BSRR_BS_6                   GPIO_BSRR_BS6
#define GPIO_BSRR_BS_7                   GPIO_BSRR_BS7
#define GPIO_BSRR_BS_8                   GPIO_BSRR_BS8
#define GPIO_BSRR_BS_9                   GPIO_BSRR_BS9
#define GPIO_BSRR_BS_10                  GPIO_BSRR_BS10
#define GPIO_BSRR_BS_11                  GPIO_BSRR_BS11
#define GPIO_BSRR_BS_12                  GPIO_BSRR_BS12
#define GPIO_BSRR_BS_13                  GPIO_BSRR_BS13
#define GPIO_BSRR_BS_14                  GPIO_BSRR_BS14
#define GPIO_BSRR_BS_15                  GPIO_BSRR_BS15
#define GPIO_BSRR_BR_0                   GPIO_BSRR_BR0
#define GPIO_BSRR_BR_1                   GPIO_BSRR_BR1
#define GPIO_BSRR_BR_2                   GPIO_BSRR_BR2
#define GPIO_BSRR_BR_3                   GPIO_BSRR_BR3
#define GPIO_BSRR_BR_4                   GPIO_BSRR_BR4
#define GPIO_BSRR_BR_5                   GPIO_BSRR_BR5
#define GPIO_BSRR_BR_6                   GPIO_BSRR_BR6
#define GPIO_BSRR_BR_7                   GPIO_BSRR_BR7
#define GPIO_BSRR_BR_8                   GPIO_BSRR_BR8
#define GPIO_BSRR_BR_9                   GPIO_BSRR_BR9
#define GPIO_BSRR_BR_10                  GPIO_BSRR_BR10
#define GPIO_BSRR_BR_11                  GPIO_BSRR_BR11
#define GPIO_BSRR_BR_12                  GPIO_BSRR_BR12
#define GPIO_BSRR_BR_13                  GPIO_BSRR_BR13
#define GPIO_BSRR_BR_14                  GPIO_BSRR_BR14
#define GPIO_BSRR_BR_15                  GPIO_BSRR_BR15
#define GPIO_BRR_BR0                     GPIO_BSRR_BR0
#define GPIO_BRR_BR0_Pos                 GPIO_BSRR_BR0_Pos
#define GPIO_BRR_BR0_Msk                 GPIO_BSRR_BR0_Msk
#define GPIO_BRR_BR1                     GPIO_BSRR_BR1
#define GPIO_BRR_BR1_Pos                 GPIO_BSRR_BR1_Pos
#define GPIO_BRR_BR1_Msk                 GPIO_BSRR_BR1_Msk
#define GPIO_BRR_BR2                     GPIO_BSRR_BR2
#define GPIO_BRR_BR2_Pos                 GPIO_BSRR_BR2_Pos
#define GPIO_BRR_BR2_Msk                 GPIO_BSRR_BR2_Msk
#define GPIO_BRR_BR3                     GPIO_BSRR_BR3
#define GPIO_BRR_BR3_Pos                 GPIO_BSRR_BR3_Pos
#define GPIO_BRR_BR3_Msk                 GPIO_BSRR_BR3_Msk
#define GPIO_BRR_BR4                     GPIO_BSRR_BR4
#define GPIO_BRR_BR4_Pos                 GPIO_BSRR_BR4_Pos
#define GPIO_BRR_BR4_Msk                 GPIO_BSRR_BR4_Msk
#define GPIO_BRR_BR5                     GPIO_BSRR_BR5
#define GPIO_BRR_BR5_Pos                 GPIO_BSRR_BR5_Pos
#define GPIO_BRR_BR5_Msk                 GPIO_BSRR_BR5_Msk
#define GPIO_BRR_BR6                     GPIO_BSRR_BR6
#define GPIO_BRR_BR6_Pos                 GPIO_BSRR_BR6_Pos
#define GPIO_BRR_BR6_Msk                 GPIO_BSRR_BR6_Msk
#define GPIO_BRR_BR7                     GPIO_BSRR_BR7
#define GPIO_BRR_BR7_Pos                 GPIO_BSRR_BR7_Pos
#define GPIO_BRR_BR7_Msk                 GPIO_BSRR_BR7_Msk
#define GPIO_BRR_BR8                     GPIO_BSRR_BR8
#define GPIO_BRR_BR8_Pos                 GPIO_BSRR_BR8_Pos
#define GPIO_BRR_BR8_Msk                 GPIO_BSRR_BR8_Msk
#define GPIO_BRR_BR9                     GPIO_BSRR_BR9
#define GPIO_BRR_BR9_Pos                 GPIO_BSRR_BR9_Pos
#define GPIO_BRR_BR9_Msk                 GPIO_BSRR_BR9_Msk
#define GPIO_BRR_BR10                    GPIO_BSRR_BR10
#define GPIO_BRR_BR10_Pos                GPIO_BSRR_BR10_Pos
#define GPIO_BRR_BR10_Msk                GPIO_BSRR_BR10_Msk
#define GPIO_BRR_BR11                    GPIO_BSRR_BR11
#define GPIO_BRR_BR11_Pos                GPIO_BSRR_BR11_Pos
#define GPIO_BRR_BR11_Msk                GPIO_BSRR_BR11_Msk
#define GPIO_BRR_BR12                    GPIO_BSRR_BR12
#define GPIO_BRR_BR12_Pos                GPIO_BSRR_BR12_Pos
#define GPIO_BRR_BR12_Msk                GPIO_BSRR_BR12_Msk
#define GPIO_BRR_BR13                    GPIO_BSRR_BR13
#define GPIO_BRR_BR13_Pos                GPIO_BSRR_BR13_Pos
#define GPIO_BRR_BR13_Msk                GPIO_BSRR_BR13_Msk
#define GPIO_BRR_BR14                    GPIO_BSRR_BR14
#define GPIO_BRR_BR14_Pos                GPIO_BSRR_BR14_Pos
#define GPIO_BRR_BR14_Msk                GPIO_BSRR_BR14_Msk
#define GPIO_BRR_BR15                    GPIO_BSRR_BR15
#define GPIO_BRR_BR15_Pos                GPIO_BSRR_BR15_Pos
#define GPIO_BRR_BR15_Msk                GPIO_BSRR_BR15_Msk

#define GPIO_LCKR_LCK0_Pos               (0U)
#define GPIO_LCKR_LCK0_Msk               (0x1UL << GPIO_LCKR_LCK0_Pos)
#define GPIO_LCKR_LCK0                   GPIO_LCKR_LCK0_Msk
#define GPIO_LCKR_LCK1_Pos               (1U)
#define GPIO_LCKR_LCK1_Msk               (0x1UL << GPIO_LCKR_LCK1_Pos)
#define GPIO_LCKR_LCK1                   GPIO_LCKR_LCK1_Msk
#define GPIO_LCKR_LCK2_Pos               (2U)
#define GPIO_LCKR_LCK2_Msk               (0x1UL << GPIO_LCKR_LCK2_Pos)
#define GPIO_LCKR_LCK2                   GPIO_LCKR_LCK2_Msk
#define GPIO_LCKR_LCK3_Pos               (3U)
#define GPIO_LCKR_LCK3_Msk               (0x1UL << GPIO_LCKR_LCK3_Pos)
#define GPIO_LCKR_LCK3                   GPIO_LCKR_LCK3_Msk
#define GPIO_LCKR_LCK4_Pos               (4U)
#define GPIO_LCKR_LCK4_Msk               (0x1UL << GPIO_LCKR_LCK4_Pos)
#define GPIO_LCKR_LCK4                   GPIO_LCKR_LCK4_Msk
#define GPIO_LCKR_LCK5_Pos               (5U)
#define GPIO_LCKR_LCK5_Msk               (0x1UL << GPIO_LCKR_LCK5_Pos)
#define GPIO_LCKR_LCK5                   GPIO_LCKR_LCK5_Msk
#define GPIO_LCKR_LCK6_Pos               (6U)
#define GPIO_LCKR_LCK6_Msk               (0x1UL << GPIO_LCKR_LCK6_Pos)
#define GPIO_LCKR_LCK6                   GPIO_LCKR_LCK6_Msk
#define GPIO_LCKR_LCK7_Pos               (7U)
#define GPIO_LCKR_LCK7_Msk               (0x1UL << GPIO_LCKR_LCK7_Pos)
#define GPIO_LCKR_LCK7                   GPIO_LCKR_LCK7_Msk
#define GPIO_LCKR_LCK8_Pos               (8U)
#define GPIO_LCKR_LCK8_Msk               (0x1UL << GPIO_LCKR_LCK8_Pos)
#define GPIO_LCKR_LCK8                   GPIO_LCKR_LCK8_Msk
#define GPIO_LCKR_LCK9_Pos               (9U)
#define GPIO_LCKR_LCK9_Msk               (0x1UL << GPIO_LCKR_LCK9_Pos)
#define GPIO_LCKR_LCK9                   GPIO_LCKR_LCK9_Msk
#define GPIO_LCKR_LCK10_Pos              (10U)
#define GPIO_LCKR_LCK10_Msk              (0x1UL << GPIO_LCKR_LCK10_Pos)
#define GPIO_LCKR_LCK10                  GPIO_LCKR_LCK10_Msk
#define GPIO_LCKR_LCK11_Pos              (11U)
#define GPIO_LCKR_LCK11_Msk              (0x1UL << GPIO_LCKR_LCK11_Pos)
#define GPIO_LCKR_LCK11                  GPIO_LCKR_LCK11_Msk
#define GPIO_LCKR_LCK12_Pos              (12U)
#define GPIO_LCKR_LCK12_Msk              (0x1UL << GPIO_LCKR_LCK12_Pos)
#define GPIO_LCKR_LCK12                  GPIO_LCKR_LCK12_Msk
#define GPIO_LCKR_LCK13_Pos              (13U)
#define GPIO_LCKR_LCK13_Msk              (0x1UL << GPIO_LCKR_LCK13_Pos)
#define GPIO_LCKR_LCK13                  GPIO_LCKR_LCK13_Msk
#define GPIO_LCKR_LCK14_Pos              (14U)
#define GPIO_LCKR_LCK14_Msk              (0x1UL << GPIO_LCKR_LCK14_Pos)
#define GPIO_LCKR_LCK14                  GPIO_LCKR_LCK14_Msk
#define GPIO_LCKR_LCK15_Pos              (15U)
#define GPIO_LCKR_LCK15_Msk              (0x1UL << GPIO_LCKR_LCK15_Pos)
#define GPIO_LCKR_LCK15                  GPIO_LCKR_LCK15_Msk
#define GPIO_LCKR_LCKK_Pos               (16U)
#define GPIO_LCKR_LCKK_Msk               (0x1UL << GPIO_LCKR_LCKK_Pos)
#define GPIO_LCKR_LCKK                   GPIO_LCKR_LCKK_Msk

#define GPIO_AFRL_AFSEL0_Pos             (0U)
#define GPIO_AFRL_AFSEL0_Msk             (0xFUL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0                 GPIO_AFRL_AFSEL0_Msk
#define GPIO_AFRL_AFSEL0_0               (0x1UL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0_1               (0x2UL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0_2               (0x4UL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL0_3               (0x8UL << GPIO_AFRL_AFSEL0_Pos)
#define GPIO_AFRL_AFSEL1_Pos             (4U)
#define GPIO_AFRL_AFSEL1_Msk             (0xFUL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1                 GPIO_AFRL_AFSEL1_Msk
#define GPIO_AFRL_AFSEL1_0               (0x1UL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1_1               (0x2UL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1_2               (0x4UL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL1_3               (0x8UL << GPIO_AFRL_AFSEL1_Pos)
#define GPIO_AFRL_AFSEL2_Pos             (8U)
#define GPIO_AFRL_AFSEL2_Msk             (0xFUL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2                 GPIO_AFRL_AFSEL2_Msk
#define GPIO_AFRL_AFSEL2_0               (0x1UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2_1               (0x2UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2_2               (0x4UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL2_3               (0x8UL << GPIO_AFRL_AFSEL2_Pos)
#define GPIO_AFRL_AFSEL3_Pos             (12U)
#define GPIO_AFRL_AFSEL3_Msk             (0xFUL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3                 GPIO_AFRL_AFSEL3_Msk
#define GPIO_AFRL_AFSEL3_0               (0x1UL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3_1               (0x2UL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3_2               (0x4UL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL3_3               (0x8UL << GPIO_AFRL_AFSEL3_Pos)
#define GPIO_AFRL_AFSEL4_Pos             (16U)
#define GPIO_AFRL_AFSEL4_Msk             (0xFUL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4                 GPIO_AFRL_AFSEL4_Msk
#define GPIO_AFRL_AFSEL4_0               (0x1UL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4_1               (0x2UL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4_2               (0x4UL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL4_3               (0x8UL << GPIO_AFRL_AFSEL4_Pos)
#define GPIO_AFRL_AFSEL5_Pos             (20U)
#define GPIO_AFRL_AFSEL5_Msk             (0xFUL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5                 GPIO_AFRL_AFSEL5_Msk
#define GPIO_AFRL_AFSEL5_0               (0x1UL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5_1               (0x2UL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5_2               (0x4UL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL5_3               (0x8UL << GPIO_AFRL_AFSEL5_Pos)
#define GPIO_AFRL_AFSEL6_Pos             (24U)
#define GPIO_AFRL_AFSEL6_Msk             (0xFUL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6                 GPIO_AFRL_AFSEL6_Msk
#define GPIO_AFRL_AFSEL6_0               (0x1UL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6_1               (0x2UL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6_2               (0x4UL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL6_3               (0x8UL << GPIO_AFRL_AFSEL6_Pos)
#define GPIO_AFRL_AFSEL7_Pos             (28U)
#define GPIO_AFRL_AFSEL7_Msk             (0xFUL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7                 GPIO_AFRL_AFSEL7_Msk
#define GPIO_AFRL_AFSEL7_0               (0x1UL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7_1               (0x2UL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7_2               (0x4UL << GPIO_AFRL_AFSEL7_Pos)
#define GPIO_AFRL_AFSEL7_3               (0x8UL << GPIO_AFRL_AFSEL7_Pos)

#define GPIO_AFRL_AFRL0                  GPIO_AFRL_AFSEL0
#define GPIO_AFRL_AFRL0_0                GPIO_AFRL_AFSEL0_0
#define GPIO_AFRL_AFRL0_1                GPIO_AFRL_AFSEL0_1
#define GPIO_AFRL_AFRL0_2                GPIO_AFRL_AFSEL0_2
#define GPIO_AFRL_AFRL0_3                GPIO_AFRL_AFSEL0_3
#define GPIO_AFRL_AFRL1                  GPIO_AFRL_AFSEL1
#define GPIO_AFRL_AFRL1_0                GPIO_AFRL_AFSEL1_0
#define GPIO_AFRL_AFRL1_1                GPIO_AFRL_AFSEL1_1
#define GPIO_AFRL_AFRL1_2                GPIO_AFRL_AFSEL1_2
#define GPIO_AFRL_AFRL1_3                GPIO_AFRL_AFSEL1_3
#define GPIO_AFRL_AFRL2                  GPIO_AFRL_AFSEL2
#define GPIO_AFRL_AFRL2_0                GPIO_AFRL_AFSEL2_0
#define GPIO_AFRL_AFRL2_1                GPIO_AFRL_AFSEL2_1
#define GPIO_AFRL_AFRL2_2                GPIO_AFRL_AFSEL2_2
#define GPIO_AFRL_AFRL2_3                GPIO_AFRL_AFSEL2_3
#define GPIO_AFRL_AFRL3                  GPIO_AFRL_AFSEL3
#define GPIO_AFRL_AFRL3_0                GPIO_AFRL_AFSEL3_0
#define GPIO_AFRL_AFRL3_1                GPIO_AFRL_AFSEL3_1
#define GPIO_AFRL_AFRL3_2                GPIO_AFRL_AFSEL3_2
#define GPIO_AFRL_AFRL3_3                GPIO_AFRL_AFSEL3_3
#define GPIO_AFRL_AFRL4                  GPIO_AFRL_AFSEL4
#define GPIO_AFRL_AFRL4_0                GPIO_AFRL_AFSEL4_0
#define GPIO_AFRL_AFRL4_1                GPIO_AFRL_AFSEL4_1
#define GPIO_AFRL_AFRL4_2                GPIO_AFRL_AFSEL4_2
#define GPIO_AFRL_AFRL4_3                GPIO_AFRL_AFSEL4_3
#define GPIO_AFRL_AFRL5                  GPIO_AFRL_AFSEL5
#define GPIO_AFRL_AFRL5_0                GPIO_AFRL_AFSEL5_0
#define GPIO_AFRL_AFRL5_1                GPIO_AFRL_AFSEL5_1
#define GPIO_AFRL_AFRL5_2                GPIO_AFRL_AFSEL5_2
#define GPIO_AFRL_AFRL5_3                GPIO_AFRL_AFSEL5_3
#define GPIO_AFRL_AFRL6                  GPIO_AFRL_AFSEL6
#define GPIO_AFRL_AFRL6_0                GPIO_AFRL_AFSEL6_0
#define GPIO_AFRL_AFRL6_1                GPIO_AFRL_AFSEL6_1
#define GPIO_AFRL_AFRL6_2                GPIO_AFRL_AFSEL6_2
#define GPIO_AFRL_AFRL6_3                GPIO_AFRL_AFSEL6_3
#define GPIO_AFRL_AFRL7                  GPIO_AFRL_AFSEL7
#define GPIO_AFRL_AFRL7_0                GPIO_AFRL_AFSEL7_0
#define GPIO_AFRL_AFRL7_1                GPIO_AFRL_AFSEL7_1
#define GPIO_AFRL_AFRL7_2                GPIO_AFRL_AFSEL7_2
#define GPIO_AFRL_AFRL7_3                GPIO_AFRL_AFSEL7_3

#define GPIO_AFRH_AFSEL8_Pos             (0U)
#define GPIO_AFRH_AFSEL8_Msk             (0xFUL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8                 GPIO_AFRH_AFSEL8_Msk
#define GPIO_AFRH_AFSEL8_0               (0x1UL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8_1               (0x2UL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8_2               (0x4UL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL8_3               (0x8UL << GPIO_AFRH_AFSEL8_Pos)
#define GPIO_AFRH_AFSEL9_Pos             (4U)
#define GPIO_AFRH_AFSEL9_Msk             (0xFUL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9                 GPIO_AFRH_AFSEL9_Msk
#define GPIO_AFRH_AFSEL9_0               (0x1UL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9_1               (0x2UL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9_2               (0x4UL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL9_3               (0x8UL << GPIO_AFRH_AFSEL9_Pos)
#define GPIO_AFRH_AFSEL10_Pos            (8U)
#define GPIO_AFRH_AFSEL10_Msk            (0xFUL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10                GPIO_AFRH_AFSEL10_Msk
#define GPIO_AFRH_AFSEL10_0              (0x1UL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10_1              (0x2UL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10_2              (0x4UL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL10_3              (0x8UL << GPIO_AFRH_AFSEL10_Pos)
#define GPIO_AFRH_AFSEL11_Pos            (12U)
#define GPIO_AFRH_AFSEL11_Msk            (0xFUL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11                GPIO_AFRH_AFSEL11_Msk
#define GPIO_AFRH_AFSEL11_0              (0x1UL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11_1              (0x2UL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11_2              (0x4UL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL11_3              (0x8UL << GPIO_AFRH_AFSEL11_Pos)
#define GPIO_AFRH_AFSEL12_Pos            (16U)
#define GPIO_AFRH_AFSEL12_Msk            (0xFUL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12                GPIO_AFRH_AFSEL12_Msk
#define GPIO_AFRH_AFSEL12_0              (0x1UL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12_1              (0x2UL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12_2              (0x4UL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL12_3              (0x8UL << GPIO_AFRH_AFSEL12_Pos)
#define GPIO_AFRH_AFSEL13_Pos            (20U)
#define GPIO_AFRH_AFSEL13_Msk            (0xFUL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13                GPIO_AFRH_AFSEL13_Msk
#define GPIO_AFRH_AFSEL13_0              (0x1UL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13_1              (0x2UL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13_2              (0x4UL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL13_3              (0x8UL << GPIO_AFRH_AFSEL13_Pos)
#define GPIO_AFRH_AFSEL14_Pos            (24U)
#define GPIO_AFRH_AFSEL14_Msk            (0xFUL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14                GPIO_AFRH_AFSEL14_Msk
#define GPIO_AFRH_AFSEL14_0              (0x1UL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14_1              (0x2UL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14_2              (0x4UL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL14_3              (0x8UL << GPIO_AFRH_AFSEL14_Pos)
#define GPIO_AFRH_AFSEL15_Pos            (28U)
#define GPIO_AFRH_AFSEL15_Msk            (0xFUL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15                GPIO_AFRH_AFSEL15_Msk
#define GPIO_AFRH_AFSEL15_0              (0x1UL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15_1              (0x2UL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15_2              (0x4UL << GPIO_AFRH_AFSEL15_Pos)
#define GPIO_AFRH_AFSEL15_3              (0x8UL << GPIO_AFRH_AFSEL15_Pos)

#define GPIO_AFRH_AFRH0                  GPIO_AFRH_AFSEL8
#define GPIO_AFRH_AFRH0_0                GPIO_AFRH_AFSEL8_0
#define GPIO_AFRH_AFRH0_1                GPIO_AFRH_AFSEL8_1
#define GPIO_AFRH_AFRH0_2                GPIO_AFRH_AFSEL8_2
#define GPIO_AFRH_AFRH0_3                GPIO_AFRH_AFSEL8_3
#define GPIO_AFRH_AFRH1                  GPIO_AFRH_AFSEL9
#define GPIO_AFRH_AFRH1_0                GPIO_AFRH_AFSEL9_0
#define GPIO_AFRH_AFRH1_1                GPIO_AFRH_AFSEL9_1
#define GPIO_AFRH_AFRH1_2                GPIO_AFRH_AFSEL9_2
#define GPIO_AFRH_AFRH1_3                GPIO_AFRH_AFSEL9_3
#define GPIO_AFRH_AFRH2                  GPIO_AFRH_AFSEL10
#define GPIO_AFRH_AFRH2_0                GPIO_AFRH_AFSEL10_0
#define GPIO_AFRH_AFRH2_1                GPIO_AFRH_AFSEL10_1
#define GPIO_AFRH_AFRH2_2                GPIO_AFRH_AFSEL10_2
#define GPIO_AFRH_AFRH2_3                GPIO_AFRH_AFSEL10_3
#define GPIO_AFRH_AFRH3                  GPIO_AFRH_AFSEL11
#define GPIO_AFRH_AFRH3_0                GPIO_AFRH_AFSEL11_0
#define GPIO_AFRH_AFRH3_1                GPIO_AFRH_AFSEL11_1
#define GPIO_AFRH_AFRH3_2                GPIO_AFRH_AFSEL11_2
#define GPIO_AFRH_AFRH3_3                GPIO_AFRH_AFSEL11_3
#define GPIO_AFRH_AFRH4                  GPIO_AFRH_AFSEL12
#define GPIO_AFRH_AFRH4_0                GPIO_AFRH_AFSEL12_0
#define GPIO_AFRH_AFRH4_1                GPIO_AFRH_AFSEL12_1
#define GPIO_AFRH_AFRH4_2                GPIO_AFRH_AFSEL12_2
#define GPIO_AFRH_AFRH4_3                GPIO_AFRH_AFSEL12_3
#define GPIO_AFRH_AFRH5                  GPIO_AFRH_AFSEL13
#define GPIO_AFRH_AFRH5_0                GPIO_AFRH_AFSEL13_0
#define GPIO_AFRH_AFRH5_1                GPIO_AFRH_AFSEL13_1
#define GPIO_AFRH_AFRH5_2                GPIO_AFRH_AFSEL13_2
#define GPIO_AFRH_AFRH5_3                GPIO_AFRH_AFSEL13_3
#define GPIO_AFRH_AFRH6                  GPIO_AFRH_AFSEL14
#define GPIO_AFRH_AFRH6_0                GPIO_AFRH_AFSEL14_0
#define GPIO_AFRH_AFRH6_1                GPIO_AFRH_AFSEL14_1
#define GPIO_AFRH_AFRH6_2                GPIO_AFRH_AFSEL14_2
#define GPIO_AFRH_AFRH6_3                GPIO_AFRH_AFSEL14_3
#define GPIO_AFRH_AFRH7                  GPIO_AFRH_AFSEL15
#define GPIO_AFRH_AFRH7_0                GPIO_AFRH_AFSEL15_0
#define GPIO_AFRH_AFRH7_1                GPIO_AFRH_AFSEL15_1
#define GPIO_AFRH_AFRH7_2                GPIO_AFRH_AFSEL15_2
#define GPIO_AFRH_AFRH7_3                GPIO_AFRH_AFSEL15_3

#define I2C_CR1_PE_Pos            (0U)
#define I2C_CR1_PE_Msk            (0x1UL << I2C_CR1_PE_Pos)
#define I2C_CR1_PE                I2C_CR1_PE_Msk
#define I2C_CR1_SMBUS_Pos         (1U)
#define I2C_CR1_SMBUS_Msk         (0x1UL << I2C_CR1_SMBUS_Pos)
#define I2C_CR1_SMBUS             I2C_CR1_SMBUS_Msk
#define I2C_CR1_SMBTYPE_Pos       (3U)
#define I2C_CR1_SMBTYPE_Msk       (0x1UL << I2C_CR1_SMBTYPE_Pos)
#define I2C_CR1_SMBTYPE           I2C_CR1_SMBTYPE_Msk
#define I2C_CR1_ENARP_Pos         (4U)
#define I2C_CR1_ENARP_Msk         (0x1UL << I2C_CR1_ENARP_Pos)
#define I2C_CR1_ENARP             I2C_CR1_ENARP_Msk
#define I2C_CR1_ENPEC_Pos         (5U)
#define I2C_CR1_ENPEC_Msk         (0x1UL << I2C_CR1_ENPEC_Pos)
#define I2C_CR1_ENPEC             I2C_CR1_ENPEC_Msk
#define I2C_CR1_ENGC_Pos          (6U)
#define I2C_CR1_ENGC_Msk          (0x1UL << I2C_CR1_ENGC_Pos)
#define I2C_CR1_ENGC              I2C_CR1_ENGC_Msk
#define I2C_CR1_NOSTRETCH_Pos     (7U)
#define I2C_CR1_NOSTRETCH_Msk     (0x1UL << I2C_CR1_NOSTRETCH_Pos)
#define I2C_CR1_NOSTRETCH         I2C_CR1_NOSTRETCH_Msk
#define I2C_CR1_START_Pos         (8U)
#define I2C_CR1_START_Msk         (0x1UL << I2C_CR1_START_Pos)
#define I2C_CR1_START             I2C_CR1_START_Msk
#define I2C_CR1_STOP_Pos          (9U)
#define I2C_CR1_STOP_Msk          (0x1UL << I2C_CR1_STOP_Pos)
#define I2C_CR1_STOP              I2C_CR1_STOP_Msk
#define I2C_CR1_ACK_Pos           (10U)
#define I2C_CR1_ACK_Msk           (0x1UL << I2C_CR1_ACK_Pos)
#define I2C_CR1_ACK               I2C_CR1_ACK_Msk
#define I2C_CR1_POS_Pos           (11U)
#define I2C_CR1_POS_Msk           (0x1UL << I2C_CR1_POS_Pos)
#define I2C_CR1_POS               I2C_CR1_POS_Msk
#define I2C_CR1_PEC_Pos           (12U)
#define I2C_CR1_PEC_Msk           (0x1UL << I2C_CR1_PEC_Pos)
#define I2C_CR1_PEC               I2C_CR1_PEC_Msk
#define I2C_CR1_ALERT_Pos         (13U)
#define I2C_CR1_ALERT_Msk         (0x1UL << I2C_CR1_ALERT_Pos)
#define I2C_CR1_ALERT             I2C_CR1_ALERT_Msk
#define I2C_CR1_SWRST_Pos         (15U)
#define I2C_CR1_SWRST_Msk         (0x1UL << I2C_CR1_SWRST_Pos)
#define I2C_CR1_SWRST             I2C_CR1_SWRST_Msk

#define I2C_CR2_FREQ_Pos          (0U)
#define I2C_CR2_FREQ_Msk          (0x3FUL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ              I2C_CR2_FREQ_Msk
#define I2C_CR2_FREQ_0            (0x01UL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ_1            (0x02UL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ_2            (0x04UL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ_3            (0x08UL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ_4            (0x10UL << I2C_CR2_FREQ_Pos)
#define I2C_CR2_FREQ_5            (0x20UL << I2C_CR2_FREQ_Pos)

#define I2C_CR2_ITERREN_Pos       (8U)
#define I2C_CR2_ITERREN_Msk       (0x1UL << I2C_CR2_ITERREN_Pos)
#define I2C_CR2_ITERREN           I2C_CR2_ITERREN_Msk
#define I2C_CR2_ITEVTEN_Pos       (9U)
#define I2C_CR2_ITEVTEN_Msk       (0x1UL << I2C_CR2_ITEVTEN_Pos)
#define I2C_CR2_ITEVTEN           I2C_CR2_ITEVTEN_Msk
#define I2C_CR2_ITBUFEN_Pos       (10U)
#define I2C_CR2_ITBUFEN_Msk       (0x1UL << I2C_CR2_ITBUFEN_Pos)
#define I2C_CR2_ITBUFEN           I2C_CR2_ITBUFEN_Msk
#define I2C_CR2_DMAEN_Pos         (11U)
#define I2C_CR2_DMAEN_Msk         (0x1UL << I2C_CR2_DMAEN_Pos)
#define I2C_CR2_DMAEN             I2C_CR2_DMAEN_Msk
#define I2C_CR2_LAST_Pos          (12U)
#define I2C_CR2_LAST_Msk          (0x1UL << I2C_CR2_LAST_Pos)
#define I2C_CR2_LAST              I2C_CR2_LAST_Msk

#define I2C_OAR1_ADD1_7           0x000000FEU
#define I2C_OAR1_ADD8_9           0x00000300U

#define I2C_OAR1_ADD0_Pos         (0U)
#define I2C_OAR1_ADD0_Msk         (0x1UL << I2C_OAR1_ADD0_Pos)
#define I2C_OAR1_ADD0             I2C_OAR1_ADD0_Msk
#define I2C_OAR1_ADD1_Pos         (1U)
#define I2C_OAR1_ADD1_Msk         (0x1UL << I2C_OAR1_ADD1_Pos)
#define I2C_OAR1_ADD1             I2C_OAR1_ADD1_Msk
#define I2C_OAR1_ADD2_Pos         (2U)
#define I2C_OAR1_ADD2_Msk         (0x1UL << I2C_OAR1_ADD2_Pos)
#define I2C_OAR1_ADD2             I2C_OAR1_ADD2_Msk
#define I2C_OAR1_ADD3_Pos         (3U)
#define I2C_OAR1_ADD3_Msk         (0x1UL << I2C_OAR1_ADD3_Pos)
#define I2C_OAR1_ADD3             I2C_OAR1_ADD3_Msk
#define I2C_OAR1_ADD4_Pos         (4U)
#define I2C_OAR1_ADD4_Msk         (0x1UL << I2C_OAR1_ADD4_Pos)
#define I2C_OAR1_ADD4             I2C_OAR1_ADD4_Msk
#define I2C_OAR1_ADD5_Pos         (5U)
#define I2C_OAR1_ADD5_Msk         (0x1UL << I2C_OAR1_ADD5_Pos)
#define I2C_OAR1_ADD5             I2C_OAR1_ADD5_Msk
#define I2C_OAR1_ADD6_Pos         (6U)
#define I2C_OAR1_ADD6_Msk         (0x1UL << I2C_OAR1_ADD6_Pos)
#define I2C_OAR1_ADD6             I2C_OAR1_ADD6_Msk
#define I2C_OAR1_ADD7_Pos         (7U)
#define I2C_OAR1_ADD7_Msk         (0x1UL << I2C_OAR1_ADD7_Pos)
#define I2C_OAR1_ADD7             I2C_OAR1_ADD7_Msk
#define I2C_OAR1_ADD8_Pos         (8U)
#define I2C_OAR1_ADD8_Msk         (0x1UL << I2C_OAR1_ADD8_Pos)
#define I2C_OAR1_ADD8             I2C_OAR1_ADD8_Msk
#define I2C_OAR1_ADD9_Pos         (9U)
#define I2C_OAR1_ADD9_Msk         (0x1UL << I2C_OAR1_ADD9_Pos)
#define I2C_OAR1_ADD9             I2C_OAR1_ADD9_Msk

#define I2C_OAR1_ADDMODE_Pos      (15U)
#define I2C_OAR1_ADDMODE_Msk      (0x1UL << I2C_OAR1_ADDMODE_Pos)
#define I2C_OAR1_ADDMODE          I2C_OAR1_ADDMODE_Msk

#define I2C_OAR2_ENDUAL_Pos       (0U)
#define I2C_OAR2_ENDUAL_Msk       (0x1UL << I2C_OAR2_ENDUAL_Pos)
#define I2C_OAR2_ENDUAL           I2C_OAR2_ENDUAL_Msk
#define I2C_OAR2_ADD2_Pos         (1U)
#define I2C_OAR2_ADD2_Msk         (0x7FUL << I2C_OAR2_ADD2_Pos)
#define I2C_OAR2_ADD2             I2C_OAR2_ADD2_Msk

#define I2C_DR_DR_Pos             (0U)
#define I2C_DR_DR_Msk             (0xFFUL << I2C_DR_DR_Pos)
#define I2C_DR_DR                 I2C_DR_DR_Msk

#define I2C_SR1_SB_Pos            (0U)
#define I2C_SR1_SB_Msk            (0x1UL << I2C_SR1_SB_Pos)
#define I2C_SR1_SB                I2C_SR1_SB_Msk
#define I2C_SR1_ADDR_Pos          (1U)
#define I2C_SR1_ADDR_Msk          (0x1UL << I2C_SR1_ADDR_Pos)
#define I2C_SR1_ADDR              I2C_SR1_ADDR_Msk
#define I2C_SR1_BTF_Pos           (2U)
#define I2C_SR1_BTF_Msk           (0x1UL << I2C_SR1_BTF_Pos)
#define I2C_SR1_BTF               I2C_SR1_BTF_Msk
#define I2C_SR1_ADD10_Pos         (3U)
#define I2C_SR1_ADD10_Msk         (0x1UL << I2C_SR1_ADD10_Pos)
#define I2C_SR1_ADD10             I2C_SR1_ADD10_Msk
#define I2C_SR1_STOPF_Pos         (4U)
#define I2C_SR1_STOPF_Msk         (0x1UL << I2C_SR1_STOPF_Pos)
#define I2C_SR1_STOPF             I2C_SR1_STOPF_Msk
#define I2C_SR1_RXNE_Pos          (6U)
#define I2C_SR1_RXNE_Msk          (0x1UL << I2C_SR1_RXNE_Pos)
#define I2C_SR1_RXNE              I2C_SR1_RXNE_Msk
#define I2C_SR1_TXE_Pos           (7U)
#define I2C_SR1_TXE_Msk           (0x1UL << I2C_SR1_TXE_Pos)
#define I2C_SR1_TXE               I2C_SR1_TXE_Msk
#define I2C_SR1_BERR_Pos          (8U)
#define I2C_SR1_BERR_Msk          (0x1UL << I2C_SR1_BERR_Pos)
#define I2C_SR1_BERR              I2C_SR1_BERR_Msk
#define I2C_SR1_ARLO_Pos          (9U)
#define I2C_SR1_ARLO_Msk          (0x1UL << I2C_SR1_ARLO_Pos)
#define I2C_SR1_ARLO              I2C_SR1_ARLO_Msk
#define I2C_SR1_AF_Pos            (10U)
#define I2C_SR1_AF_Msk            (0x1UL << I2C_SR1_AF_Pos)
#define I2C_SR1_AF                I2C_SR1_AF_Msk
#define I2C_SR1_OVR_Pos           (11U)
#define I2C_SR1_OVR_Msk           (0x1UL << I2C_SR1_OVR_Pos)
#define I2C_SR1_OVR               I2C_SR1_OVR_Msk
#define I2C_SR1_PECERR_Pos        (12U)
#define I2C_SR1_PECERR_Msk        (0x1UL << I2C_SR1_PECERR_Pos)
#define I2C_SR1_PECERR            I2C_SR1_PECERR_Msk
#define I2C_SR1_TIMEOUT_Pos       (14U)
#define I2C_SR1_TIMEOUT_Msk       (0x1UL << I2C_SR1_TIMEOUT_Pos)
#define I2C_SR1_TIMEOUT           I2C_SR1_TIMEOUT_Msk
#define I2C_SR1_SMBALERT_Pos      (15U)
#define I2C_SR1_SMBALERT_Msk      (0x1UL << I2C_SR1_SMBALERT_Pos)
#define I2C_SR1_SMBALERT          I2C_SR1_SMBALERT_Msk

#define I2C_SR2_MSL_Pos           (0U)
#define I2C_SR2_MSL_Msk           (0x1UL << I2C_SR2_MSL_Pos)
#define I2C_SR2_MSL               I2C_SR2_MSL_Msk
#define I2C_SR2_BUSY_Pos          (1U)
#define I2C_SR2_BUSY_Msk          (0x1UL << I2C_SR2_BUSY_Pos)
#define I2C_SR2_BUSY              I2C_SR2_BUSY_Msk
#define I2C_SR2_TRA_Pos           (2U)
#define I2C_SR2_TRA_Msk           (0x1UL << I2C_SR2_TRA_Pos)
#define I2C_SR2_TRA               I2C_SR2_TRA_Msk
#define I2C_SR2_GENCALL_Pos       (4U)
#define I2C_SR2_GENCALL_Msk       (0x1UL << I2C_SR2_GENCALL_Pos)
#define I2C_SR2_GENCALL           I2C_SR2_GENCALL_Msk
#define I2C_SR2_SMBDEFAULT_Pos    (5U)
#define I2C_SR2_SMBDEFAULT_Msk    (0x1UL << I2C_SR2_SMBDEFAULT_Pos)
#define I2C_SR2_SMBDEFAULT        I2C_SR2_SMBDEFAULT_Msk
#define I2C_SR2_SMBHOST_Pos       (6U)
#define I2C_SR2_SMBHOST_Msk       (0x1UL << I2C_SR2_SMBHOST_Pos)
#define I2C_SR2_SMBHOST           I2C_SR2_SMBHOST_Msk
#define I2C_SR2_DUALF_Pos         (7U)
#define I2C_SR2_DUALF_Msk         (0x1UL << I2C_SR2_DUALF_Pos)
#define I2C_SR2_DUALF             I2C_SR2_DUALF_Msk
#define I2C_SR2_PEC_Pos           (8U)
#define I2C_SR2_PEC_Msk           (0xFFUL << I2C_SR2_PEC_Pos)
#define I2C_SR2_PEC               I2C_SR2_PEC_Msk

#define I2C_CCR_CCR_Pos           (0U)
#define I2C_CCR_CCR_Msk           (0xFFFUL << I2C_CCR_CCR_Pos)
#define I2C_CCR_CCR               I2C_CCR_CCR_Msk
#define I2C_CCR_DUTY_Pos          (14U)
#define I2C_CCR_DUTY_Msk          (0x1UL << I2C_CCR_DUTY_Pos)
#define I2C_CCR_DUTY              I2C_CCR_DUTY_Msk
#define I2C_CCR_FS_Pos            (15U)
#define I2C_CCR_FS_Msk            (0x1UL << I2C_CCR_FS_Pos)
#define I2C_CCR_FS                I2C_CCR_FS_Msk

#define I2C_TRISE_TRISE_Pos       (0U)
#define I2C_TRISE_TRISE_Msk       (0x3FUL << I2C_TRISE_TRISE_Pos)
#define I2C_TRISE_TRISE           I2C_TRISE_TRISE_Msk

#define I2C_FLTR_DNF_Pos          (0U)
#define I2C_FLTR_DNF_Msk          (0xFUL << I2C_FLTR_DNF_Pos)
#define I2C_FLTR_DNF              I2C_FLTR_DNF_Msk
#define I2C_FLTR_ANOFF_Pos        (4U)
#define I2C_FLTR_ANOFF_Msk        (0x1UL << I2C_FLTR_ANOFF_Pos)
#define I2C_FLTR_ANOFF            I2C_FLTR_ANOFF_Msk

#define IWDG_KR_KEY_Pos     (0U)
#define IWDG_KR_KEY_Msk     (0xFFFFUL << IWDG_KR_KEY_Pos)
#define IWDG_KR_KEY         IWDG_KR_KEY_Msk

#define IWDG_PR_PR_Pos      (0U)
#define IWDG_PR_PR_Msk      (0x7UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR          IWDG_PR_PR_Msk
#define IWDG_PR_PR_0        (0x1UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_1        (0x2UL << IWDG_PR_PR_Pos)
#define IWDG_PR_PR_2        (0x4UL << IWDG_PR_PR_Pos)

#define IWDG_RLR_RL_Pos     (0U)
#define IWDG_RLR_RL_Msk     (0xFFFUL << IWDG_RLR_RL_Pos)
#define IWDG_RLR_RL         IWDG_RLR_RL_Msk

#define IWDG_SR_PVU_Pos     (0U)
#define IWDG_SR_PVU_Msk     (0x1UL << IWDG_SR_PVU_Pos)
#define IWDG_SR_PVU         IWDG_SR_PVU_Msk
#define IWDG_SR_RVU_Pos     (1U)
#define IWDG_SR_RVU_Msk     (0x1UL << IWDG_SR_RVU_Pos)
#define IWDG_SR_RVU         IWDG_SR_RVU_Msk

#define PWR_CR_LPDS_Pos        (0U)
#define PWR_CR_LPDS_Msk        (0x1UL << PWR_CR_LPDS_Pos)
#define PWR_CR_LPDS            PWR_CR_LPDS_Msk
#define PWR_CR_PDDS_Pos        (1U)
#define PWR_CR_PDDS_Msk        (0x1UL << PWR_CR_PDDS_Pos)
#define PWR_CR_PDDS            PWR_CR_PDDS_Msk
#define PWR_CR_CWUF_Pos        (2U)
#define PWR_CR_CWUF_Msk        (0x1UL << PWR_CR_CWUF_Pos)
#define PWR_CR_CWUF            PWR_CR_CWUF_Msk
#define PWR_CR_CSBF_Pos        (3U)
#define PWR_CR_CSBF_Msk        (0x1UL << PWR_CR_CSBF_Pos)
#define PWR_CR_CSBF            PWR_CR_CSBF_Msk
#define PWR_CR_PVDE_Pos        (4U)
#define PWR_CR_PVDE_Msk        (0x1UL << PWR_CR_PVDE_Pos)
#define PWR_CR_PVDE            PWR_CR_PVDE_Msk

#define PWR_CR_PLS_Pos         (5U)
#define PWR_CR_PLS_Msk         (0x7UL << PWR_CR_PLS_Pos)
#define PWR_CR_PLS             PWR_CR_PLS_Msk
#define PWR_CR_PLS_0           (0x1UL << PWR_CR_PLS_Pos)
#define PWR_CR_PLS_1           (0x2UL << PWR_CR_PLS_Pos)
#define PWR_CR_PLS_2           (0x4UL << PWR_CR_PLS_Pos)

#define PWR_CR_PLS_LEV0        0x00000000U
#define PWR_CR_PLS_LEV1        0x00000020U
#define PWR_CR_PLS_LEV2        0x00000040U
#define PWR_CR_PLS_LEV3        0x00000060U
#define PWR_CR_PLS_LEV4        0x00000080U
#define PWR_CR_PLS_LEV5        0x000000A0U
#define PWR_CR_PLS_LEV6        0x000000C0U
#define PWR_CR_PLS_LEV7        0x000000E0U
#define PWR_CR_DBP_Pos         (8U)
#define PWR_CR_DBP_Msk         (0x1UL << PWR_CR_DBP_Pos)
#define PWR_CR_DBP             PWR_CR_DBP_Msk
#define PWR_CR_FPDS_Pos        (9U)
#define PWR_CR_FPDS_Msk        (0x1UL << PWR_CR_FPDS_Pos)
#define PWR_CR_FPDS            PWR_CR_FPDS_Msk
#define PWR_CR_LPLVDS_Pos      (10U)
#define PWR_CR_LPLVDS_Msk      (0x1UL << PWR_CR_LPLVDS_Pos)
#define PWR_CR_LPLVDS          PWR_CR_LPLVDS_Msk
#define PWR_CR_MRLVDS_Pos      (11U)
#define PWR_CR_MRLVDS_Msk      (0x1UL << PWR_CR_MRLVDS_Pos)
#define PWR_CR_MRLVDS          PWR_CR_MRLVDS_Msk
#define PWR_CR_ADCDC1_Pos      (13U)
#define PWR_CR_ADCDC1_Msk      (0x1UL << PWR_CR_ADCDC1_Pos)
#define PWR_CR_ADCDC1          PWR_CR_ADCDC1_Msk
#define PWR_CR_VOS_Pos         (14U)
#define PWR_CR_VOS_Msk         (0x3UL << PWR_CR_VOS_Pos)
#define PWR_CR_VOS             PWR_CR_VOS_Msk
#define PWR_CR_VOS_0           0x00004000U
#define PWR_CR_VOS_1           0x00008000U

#define  PWR_CR_PMODE                        PWR_CR_VOS

#define PWR_CSR_WUF_Pos        (0U)
#define PWR_CSR_WUF_Msk        (0x1UL << PWR_CSR_WUF_Pos)
#define PWR_CSR_WUF            PWR_CSR_WUF_Msk
#define PWR_CSR_SBF_Pos        (1U)
#define PWR_CSR_SBF_Msk        (0x1UL << PWR_CSR_SBF_Pos)
#define PWR_CSR_SBF            PWR_CSR_SBF_Msk
#define PWR_CSR_PVDO_Pos       (2U)
#define PWR_CSR_PVDO_Msk       (0x1UL << PWR_CSR_PVDO_Pos)
#define PWR_CSR_PVDO           PWR_CSR_PVDO_Msk
#define PWR_CSR_BRR_Pos        (3U)
#define PWR_CSR_BRR_Msk        (0x1UL << PWR_CSR_BRR_Pos)
#define PWR_CSR_BRR            PWR_CSR_BRR_Msk
#define PWR_CSR_EWUP_Pos       (8U)
#define PWR_CSR_EWUP_Msk       (0x1UL << PWR_CSR_EWUP_Pos)
#define PWR_CSR_EWUP           PWR_CSR_EWUP_Msk
#define PWR_CSR_BRE_Pos        (9U)
#define PWR_CSR_BRE_Msk        (0x1UL << PWR_CSR_BRE_Pos)
#define PWR_CSR_BRE            PWR_CSR_BRE_Msk
#define PWR_CSR_VOSRDY_Pos     (14U)
#define PWR_CSR_VOSRDY_Msk     (0x1UL << PWR_CSR_VOSRDY_Pos)
#define PWR_CSR_VOSRDY         PWR_CSR_VOSRDY_Msk

#define  PWR_CSR_REGRDY                      PWR_CSR_VOSRDY

#define RCC_CR_HSION_Pos                   (0U)
#define RCC_CR_HSION_Msk                   (0x1UL << RCC_CR_HSION_Pos)
#define RCC_CR_HSION                       RCC_CR_HSION_Msk
#define RCC_CR_HSIRDY_Pos                  (1U)
#define RCC_CR_HSIRDY_Msk                  (0x1UL << RCC_CR_HSIRDY_Pos)
#define RCC_CR_HSIRDY                      RCC_CR_HSIRDY_Msk

#define RCC_CR_HSITRIM_Pos                 (3U)
#define RCC_CR_HSITRIM_Msk                 (0x1FUL << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSITRIM                     RCC_CR_HSITRIM_Msk
#define RCC_CR_HSITRIM_0                   (0x01UL << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSITRIM_1                   (0x02UL << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSITRIM_2                   (0x04UL << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSITRIM_3                   (0x08UL << RCC_CR_HSITRIM_Pos)
#define RCC_CR_HSITRIM_4                   (0x10UL << RCC_CR_HSITRIM_Pos)

#define RCC_CR_HSICAL_Pos                  (8U)
#define RCC_CR_HSICAL_Msk                  (0xFFUL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL                      RCC_CR_HSICAL_Msk
#define RCC_CR_HSICAL_0                    (0x01UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_1                    (0x02UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_2                    (0x04UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_3                    (0x08UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_4                    (0x10UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_5                    (0x20UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_6                    (0x40UL << RCC_CR_HSICAL_Pos)
#define RCC_CR_HSICAL_7                    (0x80UL << RCC_CR_HSICAL_Pos)

#define RCC_CR_HSEON_Pos                   (16U)
#define RCC_CR_HSEON_Msk                   (0x1UL << RCC_CR_HSEON_Pos)
#define RCC_CR_HSEON                       RCC_CR_HSEON_Msk
#define RCC_CR_HSERDY_Pos                  (17U)
#define RCC_CR_HSERDY_Msk                  (0x1UL << RCC_CR_HSERDY_Pos)
#define RCC_CR_HSERDY                      RCC_CR_HSERDY_Msk
#define RCC_CR_HSEBYP_Pos                  (18U)
#define RCC_CR_HSEBYP_Msk                  (0x1UL << RCC_CR_HSEBYP_Pos)
#define RCC_CR_HSEBYP                      RCC_CR_HSEBYP_Msk
#define RCC_CR_CSSON_Pos                   (19U)
#define RCC_CR_CSSON_Msk                   (0x1UL << RCC_CR_CSSON_Pos)
#define RCC_CR_CSSON                       RCC_CR_CSSON_Msk
#define RCC_CR_PLLON_Pos                   (24U)
#define RCC_CR_PLLON_Msk                   (0x1UL << RCC_CR_PLLON_Pos)
#define RCC_CR_PLLON                       RCC_CR_PLLON_Msk
#define RCC_CR_PLLRDY_Pos                  (25U)
#define RCC_CR_PLLRDY_Msk                  (0x1UL << RCC_CR_PLLRDY_Pos)
#define RCC_CR_PLLRDY                      RCC_CR_PLLRDY_Msk

#define RCC_PLLI2S_SUPPORT

#define RCC_CR_PLLI2SON_Pos                (26U)
#define RCC_CR_PLLI2SON_Msk                (0x1UL << RCC_CR_PLLI2SON_Pos)
#define RCC_CR_PLLI2SON                    RCC_CR_PLLI2SON_Msk
#define RCC_CR_PLLI2SRDY_Pos               (27U)
#define RCC_CR_PLLI2SRDY_Msk               (0x1UL << RCC_CR_PLLI2SRDY_Pos)
#define RCC_CR_PLLI2SRDY                   RCC_CR_PLLI2SRDY_Msk

#define RCC_PLLCFGR_PLLM_Pos               (0U)
#define RCC_PLLCFGR_PLLM_Msk               (0x3FUL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM                   RCC_PLLCFGR_PLLM_Msk
#define RCC_PLLCFGR_PLLM_0                 (0x01UL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM_1                 (0x02UL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM_2                 (0x04UL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM_3                 (0x08UL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM_4                 (0x10UL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM_5                 (0x20UL << RCC_PLLCFGR_PLLM_Pos)

#define RCC_PLLCFGR_PLLN_Pos               (6U)
#define RCC_PLLCFGR_PLLN_Msk               (0x1FFUL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN                   RCC_PLLCFGR_PLLN_Msk
#define RCC_PLLCFGR_PLLN_0                 (0x001UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_1                 (0x002UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_2                 (0x004UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_3                 (0x008UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_4                 (0x010UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_5                 (0x020UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_6                 (0x040UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_7                 (0x080UL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN_8                 (0x100UL << RCC_PLLCFGR_PLLN_Pos)

#define RCC_PLLCFGR_PLLP_Pos               (16U)
#define RCC_PLLCFGR_PLLP_Msk               (0x3UL << RCC_PLLCFGR_PLLP_Pos)
#define RCC_PLLCFGR_PLLP                   RCC_PLLCFGR_PLLP_Msk
#define RCC_PLLCFGR_PLLP_0                 (0x1UL << RCC_PLLCFGR_PLLP_Pos)
#define RCC_PLLCFGR_PLLP_1                 (0x2UL << RCC_PLLCFGR_PLLP_Pos)

#define RCC_PLLCFGR_PLLSRC_Pos             (22U)
#define RCC_PLLCFGR_PLLSRC_Msk             (0x1UL << RCC_PLLCFGR_PLLSRC_Pos)
#define RCC_PLLCFGR_PLLSRC                 RCC_PLLCFGR_PLLSRC_Msk
#define RCC_PLLCFGR_PLLSRC_HSE_Pos         (22U)
#define RCC_PLLCFGR_PLLSRC_HSE_Msk         (0x1UL << RCC_PLLCFGR_PLLSRC_HSE_Pos)
#define RCC_PLLCFGR_PLLSRC_HSE             RCC_PLLCFGR_PLLSRC_HSE_Msk
#define RCC_PLLCFGR_PLLSRC_HSI             0x00000000U

#define RCC_PLLCFGR_PLLQ_Pos               (24U)
#define RCC_PLLCFGR_PLLQ_Msk               (0xFUL << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLQ                   RCC_PLLCFGR_PLLQ_Msk
#define RCC_PLLCFGR_PLLQ_0                 (0x1UL << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLQ_1                 (0x2UL << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLQ_2                 (0x4UL << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLQ_3                 (0x8UL << RCC_PLLCFGR_PLLQ_Pos)

#define RCC_CFGR_SW_Pos                    (0U)
#define RCC_CFGR_SW_Msk                    (0x3UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW                        RCC_CFGR_SW_Msk
#define RCC_CFGR_SW_0                      (0x1UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_1                      (0x2UL << RCC_CFGR_SW_Pos)

#define RCC_CFGR_SW_HSI                    0x00000000U
#define RCC_CFGR_SW_HSE                    0x00000001U
#define RCC_CFGR_SW_PLL                    0x00000002U

#define RCC_CFGR_SWS_Pos                   (2U)
#define RCC_CFGR_SWS_Msk                   (0x3UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS                       RCC_CFGR_SWS_Msk
#define RCC_CFGR_SWS_0                     (0x1UL << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS_1                     (0x2UL << RCC_CFGR_SWS_Pos)

#define RCC_CFGR_SWS_HSI                   0x00000000U
#define RCC_CFGR_SWS_HSE                   0x00000004U
#define RCC_CFGR_SWS_PLL                   0x00000008U

#define RCC_CFGR_HPRE_Pos                  (4U)
#define RCC_CFGR_HPRE_Msk                  (0xFUL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE                      RCC_CFGR_HPRE_Msk
#define RCC_CFGR_HPRE_0                    (0x1UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_1                    (0x2UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_2                    (0x4UL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_3                    (0x8UL << RCC_CFGR_HPRE_Pos)

#define RCC_CFGR_HPRE_DIV1                 0x00000000U
#define RCC_CFGR_HPRE_DIV2                 0x00000080U
#define RCC_CFGR_HPRE_DIV4                 0x00000090U
#define RCC_CFGR_HPRE_DIV8                 0x000000A0U
#define RCC_CFGR_HPRE_DIV16                0x000000B0U
#define RCC_CFGR_HPRE_DIV64                0x000000C0U
#define RCC_CFGR_HPRE_DIV128               0x000000D0U
#define RCC_CFGR_HPRE_DIV256               0x000000E0U
#define RCC_CFGR_HPRE_DIV512               0x000000F0U

#define RCC_CFGR_PPRE1_Pos                 (10U)
#define RCC_CFGR_PPRE1_Msk                 (0x7UL << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1                     RCC_CFGR_PPRE1_Msk
#define RCC_CFGR_PPRE1_0                   (0x1UL << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_1                   (0x2UL << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE1_2                   (0x4UL << RCC_CFGR_PPRE1_Pos)

#define RCC_CFGR_PPRE1_DIV1                0x00000000U
#define RCC_CFGR_PPRE1_DIV2                0x00001000U
#define RCC_CFGR_PPRE1_DIV4                0x00001400U
#define RCC_CFGR_PPRE1_DIV8                0x00001800U
#define RCC_CFGR_PPRE1_DIV16               0x00001C00U

#define RCC_CFGR_PPRE2_Pos                 (13U)
#define RCC_CFGR_PPRE2_Msk                 (0x7UL << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2                     RCC_CFGR_PPRE2_Msk
#define RCC_CFGR_PPRE2_0                   (0x1UL << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_1                   (0x2UL << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE2_2                   (0x4UL << RCC_CFGR_PPRE2_Pos)

#define RCC_CFGR_PPRE2_DIV1                0x00000000U
#define RCC_CFGR_PPRE2_DIV2                0x00008000U
#define RCC_CFGR_PPRE2_DIV4                0x0000A000U
#define RCC_CFGR_PPRE2_DIV8                0x0000C000U
#define RCC_CFGR_PPRE2_DIV16               0x0000E000U

#define RCC_CFGR_RTCPRE_Pos                (16U)
#define RCC_CFGR_RTCPRE_Msk                (0x1FUL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE                    RCC_CFGR_RTCPRE_Msk
#define RCC_CFGR_RTCPRE_0                  (0x01UL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE_1                  (0x02UL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE_2                  (0x04UL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE_3                  (0x08UL << RCC_CFGR_RTCPRE_Pos)
#define RCC_CFGR_RTCPRE_4                  (0x10UL << RCC_CFGR_RTCPRE_Pos)

#define RCC_CFGR_MCO1_Pos                  (21U)
#define RCC_CFGR_MCO1_Msk                  (0x3UL << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1                      RCC_CFGR_MCO1_Msk
#define RCC_CFGR_MCO1_0                    (0x1UL << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO1_1                    (0x2UL << RCC_CFGR_MCO1_Pos)

#define RCC_CFGR_I2SSRC_Pos                (23U)
#define RCC_CFGR_I2SSRC_Msk                (0x1UL << RCC_CFGR_I2SSRC_Pos)
#define RCC_CFGR_I2SSRC                    RCC_CFGR_I2SSRC_Msk

#define RCC_CFGR_MCO1PRE_Pos               (24U)
#define RCC_CFGR_MCO1PRE_Msk               (0x7UL << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE                   RCC_CFGR_MCO1PRE_Msk
#define RCC_CFGR_MCO1PRE_0                 (0x1UL << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_1                 (0x2UL << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO1PRE_2                 (0x4UL << RCC_CFGR_MCO1PRE_Pos)

#define RCC_CFGR_MCO2PRE_Pos               (27U)
#define RCC_CFGR_MCO2PRE_Msk               (0x7UL << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE                   RCC_CFGR_MCO2PRE_Msk
#define RCC_CFGR_MCO2PRE_0                 (0x1UL << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_1                 (0x2UL << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_MCO2PRE_2                 (0x4UL << RCC_CFGR_MCO2PRE_Pos)

#define RCC_CFGR_MCO2_Pos                  (30U)
#define RCC_CFGR_MCO2_Msk                  (0x3UL << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2                      RCC_CFGR_MCO2_Msk
#define RCC_CFGR_MCO2_0                    (0x1UL << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO2_1                    (0x2UL << RCC_CFGR_MCO2_Pos)

#define RCC_CIR_LSIRDYF_Pos                (0U)
#define RCC_CIR_LSIRDYF_Msk                (0x1UL << RCC_CIR_LSIRDYF_Pos)
#define RCC_CIR_LSIRDYF                    RCC_CIR_LSIRDYF_Msk
#define RCC_CIR_LSERDYF_Pos                (1U)
#define RCC_CIR_LSERDYF_Msk                (0x1UL << RCC_CIR_LSERDYF_Pos)
#define RCC_CIR_LSERDYF                    RCC_CIR_LSERDYF_Msk
#define RCC_CIR_HSIRDYF_Pos                (2U)
#define RCC_CIR_HSIRDYF_Msk                (0x1UL << RCC_CIR_HSIRDYF_Pos)
#define RCC_CIR_HSIRDYF                    RCC_CIR_HSIRDYF_Msk
#define RCC_CIR_HSERDYF_Pos                (3U)
#define RCC_CIR_HSERDYF_Msk                (0x1UL << RCC_CIR_HSERDYF_Pos)
#define RCC_CIR_HSERDYF                    RCC_CIR_HSERDYF_Msk
#define RCC_CIR_PLLRDYF_Pos                (4U)
#define RCC_CIR_PLLRDYF_Msk                (0x1UL << RCC_CIR_PLLRDYF_Pos)
#define RCC_CIR_PLLRDYF                    RCC_CIR_PLLRDYF_Msk
#define RCC_CIR_PLLI2SRDYF_Pos             (5U)
#define RCC_CIR_PLLI2SRDYF_Msk             (0x1UL << RCC_CIR_PLLI2SRDYF_Pos)
#define RCC_CIR_PLLI2SRDYF                 RCC_CIR_PLLI2SRDYF_Msk

#define RCC_CIR_CSSF_Pos                   (7U)
#define RCC_CIR_CSSF_Msk                   (0x1UL << RCC_CIR_CSSF_Pos)
#define RCC_CIR_CSSF                       RCC_CIR_CSSF_Msk
#define RCC_CIR_LSIRDYIE_Pos               (8U)
#define RCC_CIR_LSIRDYIE_Msk               (0x1UL << RCC_CIR_LSIRDYIE_Pos)
#define RCC_CIR_LSIRDYIE                   RCC_CIR_LSIRDYIE_Msk
#define RCC_CIR_LSERDYIE_Pos               (9U)
#define RCC_CIR_LSERDYIE_Msk               (0x1UL << RCC_CIR_LSERDYIE_Pos)
#define RCC_CIR_LSERDYIE                   RCC_CIR_LSERDYIE_Msk
#define RCC_CIR_HSIRDYIE_Pos               (10U)
#define RCC_CIR_HSIRDYIE_Msk               (0x1UL << RCC_CIR_HSIRDYIE_Pos)
#define RCC_CIR_HSIRDYIE                   RCC_CIR_HSIRDYIE_Msk
#define RCC_CIR_HSERDYIE_Pos               (11U)
#define RCC_CIR_HSERDYIE_Msk               (0x1UL << RCC_CIR_HSERDYIE_Pos)
#define RCC_CIR_HSERDYIE                   RCC_CIR_HSERDYIE_Msk
#define RCC_CIR_PLLRDYIE_Pos               (12U)
#define RCC_CIR_PLLRDYIE_Msk               (0x1UL << RCC_CIR_PLLRDYIE_Pos)
#define RCC_CIR_PLLRDYIE                   RCC_CIR_PLLRDYIE_Msk
#define RCC_CIR_PLLI2SRDYIE_Pos            (13U)
#define RCC_CIR_PLLI2SRDYIE_Msk            (0x1UL << RCC_CIR_PLLI2SRDYIE_Pos)
#define RCC_CIR_PLLI2SRDYIE                RCC_CIR_PLLI2SRDYIE_Msk

#define RCC_CIR_LSIRDYC_Pos                (16U)
#define RCC_CIR_LSIRDYC_Msk                (0x1UL << RCC_CIR_LSIRDYC_Pos)
#define RCC_CIR_LSIRDYC                    RCC_CIR_LSIRDYC_Msk
#define RCC_CIR_LSERDYC_Pos                (17U)
#define RCC_CIR_LSERDYC_Msk                (0x1UL << RCC_CIR_LSERDYC_Pos)
#define RCC_CIR_LSERDYC                    RCC_CIR_LSERDYC_Msk
#define RCC_CIR_HSIRDYC_Pos                (18U)
#define RCC_CIR_HSIRDYC_Msk                (0x1UL << RCC_CIR_HSIRDYC_Pos)
#define RCC_CIR_HSIRDYC                    RCC_CIR_HSIRDYC_Msk
#define RCC_CIR_HSERDYC_Pos                (19U)
#define RCC_CIR_HSERDYC_Msk                (0x1UL << RCC_CIR_HSERDYC_Pos)
#define RCC_CIR_HSERDYC                    RCC_CIR_HSERDYC_Msk
#define RCC_CIR_PLLRDYC_Pos                (20U)
#define RCC_CIR_PLLRDYC_Msk                (0x1UL << RCC_CIR_PLLRDYC_Pos)
#define RCC_CIR_PLLRDYC                    RCC_CIR_PLLRDYC_Msk
#define RCC_CIR_PLLI2SRDYC_Pos             (21U)
#define RCC_CIR_PLLI2SRDYC_Msk             (0x1UL << RCC_CIR_PLLI2SRDYC_Pos)
#define RCC_CIR_PLLI2SRDYC                 RCC_CIR_PLLI2SRDYC_Msk

#define RCC_CIR_CSSC_Pos                   (23U)
#define RCC_CIR_CSSC_Msk                   (0x1UL << RCC_CIR_CSSC_Pos)
#define RCC_CIR_CSSC                       RCC_CIR_CSSC_Msk

#define RCC_AHB1RSTR_GPIOARST_Pos          (0U)
#define RCC_AHB1RSTR_GPIOARST_Msk          (0x1UL << RCC_AHB1RSTR_GPIOARST_Pos)
#define RCC_AHB1RSTR_GPIOARST              RCC_AHB1RSTR_GPIOARST_Msk
#define RCC_AHB1RSTR_GPIOBRST_Pos          (1U)
#define RCC_AHB1RSTR_GPIOBRST_Msk          (0x1UL << RCC_AHB1RSTR_GPIOBRST_Pos)
#define RCC_AHB1RSTR_GPIOBRST              RCC_AHB1RSTR_GPIOBRST_Msk
#define RCC_AHB1RSTR_GPIOCRST_Pos          (2U)
#define RCC_AHB1RSTR_GPIOCRST_Msk          (0x1UL << RCC_AHB1RSTR_GPIOCRST_Pos)
#define RCC_AHB1RSTR_GPIOCRST              RCC_AHB1RSTR_GPIOCRST_Msk
#define RCC_AHB1RSTR_GPIODRST_Pos          (3U)
#define RCC_AHB1RSTR_GPIODRST_Msk          (0x1UL << RCC_AHB1RSTR_GPIODRST_Pos)
#define RCC_AHB1RSTR_GPIODRST              RCC_AHB1RSTR_GPIODRST_Msk
#define RCC_AHB1RSTR_GPIOERST_Pos          (4U)
#define RCC_AHB1RSTR_GPIOERST_Msk          (0x1UL << RCC_AHB1RSTR_GPIOERST_Pos)
#define RCC_AHB1RSTR_GPIOERST              RCC_AHB1RSTR_GPIOERST_Msk
#define RCC_AHB1RSTR_GPIOHRST_Pos          (7U)
#define RCC_AHB1RSTR_GPIOHRST_Msk          (0x1UL << RCC_AHB1RSTR_GPIOHRST_Pos)
#define RCC_AHB1RSTR_GPIOHRST              RCC_AHB1RSTR_GPIOHRST_Msk
#define RCC_AHB1RSTR_CRCRST_Pos            (12U)
#define RCC_AHB1RSTR_CRCRST_Msk            (0x1UL << RCC_AHB1RSTR_CRCRST_Pos)
#define RCC_AHB1RSTR_CRCRST                RCC_AHB1RSTR_CRCRST_Msk
#define RCC_AHB1RSTR_DMA1RST_Pos           (21U)
#define RCC_AHB1RSTR_DMA1RST_Msk           (0x1UL << RCC_AHB1RSTR_DMA1RST_Pos)
#define RCC_AHB1RSTR_DMA1RST               RCC_AHB1RSTR_DMA1RST_Msk
#define RCC_AHB1RSTR_DMA2RST_Pos           (22U)
#define RCC_AHB1RSTR_DMA2RST_Msk           (0x1UL << RCC_AHB1RSTR_DMA2RST_Pos)
#define RCC_AHB1RSTR_DMA2RST               RCC_AHB1RSTR_DMA2RST_Msk

#define RCC_AHB2RSTR_OTGFSRST_Pos          (7U)
#define RCC_AHB2RSTR_OTGFSRST_Msk          (0x1UL << RCC_AHB2RSTR_OTGFSRST_Pos)
#define RCC_AHB2RSTR_OTGFSRST              RCC_AHB2RSTR_OTGFSRST_Msk

#define RCC_APB1RSTR_TIM2RST_Pos           (0U)
#define RCC_APB1RSTR_TIM2RST_Msk           (0x1UL << RCC_APB1RSTR_TIM2RST_Pos)
#define RCC_APB1RSTR_TIM2RST               RCC_APB1RSTR_TIM2RST_Msk
#define RCC_APB1RSTR_TIM3RST_Pos           (1U)
#define RCC_APB1RSTR_TIM3RST_Msk           (0x1UL << RCC_APB1RSTR_TIM3RST_Pos)
#define RCC_APB1RSTR_TIM3RST               RCC_APB1RSTR_TIM3RST_Msk
#define RCC_APB1RSTR_TIM4RST_Pos           (2U)
#define RCC_APB1RSTR_TIM4RST_Msk           (0x1UL << RCC_APB1RSTR_TIM4RST_Pos)
#define RCC_APB1RSTR_TIM4RST               RCC_APB1RSTR_TIM4RST_Msk
#define RCC_APB1RSTR_TIM5RST_Pos           (3U)
#define RCC_APB1RSTR_TIM5RST_Msk           (0x1UL << RCC_APB1RSTR_TIM5RST_Pos)
#define RCC_APB1RSTR_TIM5RST               RCC_APB1RSTR_TIM5RST_Msk
#define RCC_APB1RSTR_WWDGRST_Pos           (11U)
#define RCC_APB1RSTR_WWDGRST_Msk           (0x1UL << RCC_APB1RSTR_WWDGRST_Pos)
#define RCC_APB1RSTR_WWDGRST               RCC_APB1RSTR_WWDGRST_Msk
#define RCC_APB1RSTR_SPI2RST_Pos           (14U)
#define RCC_APB1RSTR_SPI2RST_Msk           (0x1UL << RCC_APB1RSTR_SPI2RST_Pos)
#define RCC_APB1RSTR_SPI2RST               RCC_APB1RSTR_SPI2RST_Msk
#define RCC_APB1RSTR_SPI3RST_Pos           (15U)
#define RCC_APB1RSTR_SPI3RST_Msk           (0x1UL << RCC_APB1RSTR_SPI3RST_Pos)
#define RCC_APB1RSTR_SPI3RST               RCC_APB1RSTR_SPI3RST_Msk
#define RCC_APB1RSTR_USART2RST_Pos         (17U)
#define RCC_APB1RSTR_USART2RST_Msk         (0x1UL << RCC_APB1RSTR_USART2RST_Pos)
#define RCC_APB1RSTR_USART2RST             RCC_APB1RSTR_USART2RST_Msk
#define RCC_APB1RSTR_I2C1RST_Pos           (21U)
#define RCC_APB1RSTR_I2C1RST_Msk           (0x1UL << RCC_APB1RSTR_I2C1RST_Pos)
#define RCC_APB1RSTR_I2C1RST               RCC_APB1RSTR_I2C1RST_Msk
#define RCC_APB1RSTR_I2C2RST_Pos           (22U)
#define RCC_APB1RSTR_I2C2RST_Msk           (0x1UL << RCC_APB1RSTR_I2C2RST_Pos)
#define RCC_APB1RSTR_I2C2RST               RCC_APB1RSTR_I2C2RST_Msk
#define RCC_APB1RSTR_I2C3RST_Pos           (23U)
#define RCC_APB1RSTR_I2C3RST_Msk           (0x1UL << RCC_APB1RSTR_I2C3RST_Pos)
#define RCC_APB1RSTR_I2C3RST               RCC_APB1RSTR_I2C3RST_Msk
#define RCC_APB1RSTR_PWRRST_Pos            (28U)
#define RCC_APB1RSTR_PWRRST_Msk            (0x1UL << RCC_APB1RSTR_PWRRST_Pos)
#define RCC_APB1RSTR_PWRRST                RCC_APB1RSTR_PWRRST_Msk

#define RCC_APB2RSTR_TIM1RST_Pos           (0U)
#define RCC_APB2RSTR_TIM1RST_Msk           (0x1UL << RCC_APB2RSTR_TIM1RST_Pos)
#define RCC_APB2RSTR_TIM1RST               RCC_APB2RSTR_TIM1RST_Msk
#define RCC_APB2RSTR_USART1RST_Pos         (4U)
#define RCC_APB2RSTR_USART1RST_Msk         (0x1UL << RCC_APB2RSTR_USART1RST_Pos)
#define RCC_APB2RSTR_USART1RST             RCC_APB2RSTR_USART1RST_Msk
#define RCC_APB2RSTR_USART6RST_Pos         (5U)
#define RCC_APB2RSTR_USART6RST_Msk         (0x1UL << RCC_APB2RSTR_USART6RST_Pos)
#define RCC_APB2RSTR_USART6RST             RCC_APB2RSTR_USART6RST_Msk
#define RCC_APB2RSTR_ADCRST_Pos            (8U)
#define RCC_APB2RSTR_ADCRST_Msk            (0x1UL << RCC_APB2RSTR_ADCRST_Pos)
#define RCC_APB2RSTR_ADCRST                RCC_APB2RSTR_ADCRST_Msk
#define RCC_APB2RSTR_SDIORST_Pos           (11U)
#define RCC_APB2RSTR_SDIORST_Msk           (0x1UL << RCC_APB2RSTR_SDIORST_Pos)
#define RCC_APB2RSTR_SDIORST               RCC_APB2RSTR_SDIORST_Msk
#define RCC_APB2RSTR_SPI1RST_Pos           (12U)
#define RCC_APB2RSTR_SPI1RST_Msk           (0x1UL << RCC_APB2RSTR_SPI1RST_Pos)
#define RCC_APB2RSTR_SPI1RST               RCC_APB2RSTR_SPI1RST_Msk
#define RCC_APB2RSTR_SPI4RST_Pos           (13U)
#define RCC_APB2RSTR_SPI4RST_Msk           (0x1UL << RCC_APB2RSTR_SPI4RST_Pos)
#define RCC_APB2RSTR_SPI4RST               RCC_APB2RSTR_SPI4RST_Msk
#define RCC_APB2RSTR_SYSCFGRST_Pos         (14U)
#define RCC_APB2RSTR_SYSCFGRST_Msk         (0x1UL << RCC_APB2RSTR_SYSCFGRST_Pos)
#define RCC_APB2RSTR_SYSCFGRST             RCC_APB2RSTR_SYSCFGRST_Msk
#define RCC_APB2RSTR_TIM9RST_Pos           (16U)
#define RCC_APB2RSTR_TIM9RST_Msk           (0x1UL << RCC_APB2RSTR_TIM9RST_Pos)
#define RCC_APB2RSTR_TIM9RST               RCC_APB2RSTR_TIM9RST_Msk
#define RCC_APB2RSTR_TIM10RST_Pos          (17U)
#define RCC_APB2RSTR_TIM10RST_Msk          (0x1UL << RCC_APB2RSTR_TIM10RST_Pos)
#define RCC_APB2RSTR_TIM10RST              RCC_APB2RSTR_TIM10RST_Msk
#define RCC_APB2RSTR_TIM11RST_Pos          (18U)
#define RCC_APB2RSTR_TIM11RST_Msk          (0x1UL << RCC_APB2RSTR_TIM11RST_Pos)
#define RCC_APB2RSTR_TIM11RST              RCC_APB2RSTR_TIM11RST_Msk

#define  RCC_APB2RSTR_SPI1                   RCC_APB2RSTR_SPI1RST

#define RCC_AHB1ENR_GPIOAEN_Pos            (0U)
#define RCC_AHB1ENR_GPIOAEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_AHB1ENR_GPIOAEN                RCC_AHB1ENR_GPIOAEN_Msk
#define RCC_AHB1ENR_GPIOBEN_Pos            (1U)
#define RCC_AHB1ENR_GPIOBEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOBEN_Pos)
#define RCC_AHB1ENR_GPIOBEN                RCC_AHB1ENR_GPIOBEN_Msk
#define RCC_AHB1ENR_GPIOCEN_Pos            (2U)
#define RCC_AHB1ENR_GPIOCEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOCEN_Pos)
#define RCC_AHB1ENR_GPIOCEN                RCC_AHB1ENR_GPIOCEN_Msk
#define RCC_AHB1ENR_GPIODEN_Pos            (3U)
#define RCC_AHB1ENR_GPIODEN_Msk            (0x1UL << RCC_AHB1ENR_GPIODEN_Pos)
#define RCC_AHB1ENR_GPIODEN                RCC_AHB1ENR_GPIODEN_Msk
#define RCC_AHB1ENR_GPIOEEN_Pos            (4U)
#define RCC_AHB1ENR_GPIOEEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOEEN_Pos)
#define RCC_AHB1ENR_GPIOEEN                RCC_AHB1ENR_GPIOEEN_Msk
#define RCC_AHB1ENR_GPIOHEN_Pos            (7U)
#define RCC_AHB1ENR_GPIOHEN_Msk            (0x1UL << RCC_AHB1ENR_GPIOHEN_Pos)
#define RCC_AHB1ENR_GPIOHEN                RCC_AHB1ENR_GPIOHEN_Msk
#define RCC_AHB1ENR_CRCEN_Pos              (12U)
#define RCC_AHB1ENR_CRCEN_Msk              (0x1UL << RCC_AHB1ENR_CRCEN_Pos)
#define RCC_AHB1ENR_CRCEN                  RCC_AHB1ENR_CRCEN_Msk
#define RCC_AHB1ENR_DMA1EN_Pos             (21U)
#define RCC_AHB1ENR_DMA1EN_Msk             (0x1UL << RCC_AHB1ENR_DMA1EN_Pos)
#define RCC_AHB1ENR_DMA1EN                 RCC_AHB1ENR_DMA1EN_Msk
#define RCC_AHB1ENR_DMA2EN_Pos             (22U)
#define RCC_AHB1ENR_DMA2EN_Msk             (0x1UL << RCC_AHB1ENR_DMA2EN_Pos)
#define RCC_AHB1ENR_DMA2EN                 RCC_AHB1ENR_DMA2EN_Msk

#define RCC_AHB2_SUPPORT

#define RCC_AHB2ENR_OTGFSEN_Pos            (7U)
#define RCC_AHB2ENR_OTGFSEN_Msk            (0x1UL << RCC_AHB2ENR_OTGFSEN_Pos)
#define RCC_AHB2ENR_OTGFSEN                RCC_AHB2ENR_OTGFSEN_Msk

#define RCC_APB1ENR_TIM2EN_Pos             (0U)
#define RCC_APB1ENR_TIM2EN_Msk             (0x1UL << RCC_APB1ENR_TIM2EN_Pos)
#define RCC_APB1ENR_TIM2EN                 RCC_APB1ENR_TIM2EN_Msk
#define RCC_APB1ENR_TIM3EN_Pos             (1U)
#define RCC_APB1ENR_TIM3EN_Msk             (0x1UL << RCC_APB1ENR_TIM3EN_Pos)
#define RCC_APB1ENR_TIM3EN                 RCC_APB1ENR_TIM3EN_Msk
#define RCC_APB1ENR_TIM4EN_Pos             (2U)
#define RCC_APB1ENR_TIM4EN_Msk             (0x1UL << RCC_APB1ENR_TIM4EN_Pos)
#define RCC_APB1ENR_TIM4EN                 RCC_APB1ENR_TIM4EN_Msk
#define RCC_APB1ENR_TIM5EN_Pos             (3U)
#define RCC_APB1ENR_TIM5EN_Msk             (0x1UL << RCC_APB1ENR_TIM5EN_Pos)
#define RCC_APB1ENR_TIM5EN                 RCC_APB1ENR_TIM5EN_Msk
#define RCC_APB1ENR_WWDGEN_Pos             (11U)
#define RCC_APB1ENR_WWDGEN_Msk             (0x1UL << RCC_APB1ENR_WWDGEN_Pos)
#define RCC_APB1ENR_WWDGEN                 RCC_APB1ENR_WWDGEN_Msk
#define RCC_APB1ENR_SPI2EN_Pos             (14U)
#define RCC_APB1ENR_SPI2EN_Msk             (0x1UL << RCC_APB1ENR_SPI2EN_Pos)
#define RCC_APB1ENR_SPI2EN                 RCC_APB1ENR_SPI2EN_Msk
#define RCC_APB1ENR_SPI3EN_Pos             (15U)
#define RCC_APB1ENR_SPI3EN_Msk             (0x1UL << RCC_APB1ENR_SPI3EN_Pos)
#define RCC_APB1ENR_SPI3EN                 RCC_APB1ENR_SPI3EN_Msk
#define RCC_APB1ENR_USART2EN_Pos           (17U)
#define RCC_APB1ENR_USART2EN_Msk           (0x1UL << RCC_APB1ENR_USART2EN_Pos)
#define RCC_APB1ENR_USART2EN               RCC_APB1ENR_USART2EN_Msk
#define RCC_APB1ENR_I2C1EN_Pos             (21U)
#define RCC_APB1ENR_I2C1EN_Msk             (0x1UL << RCC_APB1ENR_I2C1EN_Pos)
#define RCC_APB1ENR_I2C1EN                 RCC_APB1ENR_I2C1EN_Msk
#define RCC_APB1ENR_I2C2EN_Pos             (22U)
#define RCC_APB1ENR_I2C2EN_Msk             (0x1UL << RCC_APB1ENR_I2C2EN_Pos)
#define RCC_APB1ENR_I2C2EN                 RCC_APB1ENR_I2C2EN_Msk
#define RCC_APB1ENR_I2C3EN_Pos             (23U)
#define RCC_APB1ENR_I2C3EN_Msk             (0x1UL << RCC_APB1ENR_I2C3EN_Pos)
#define RCC_APB1ENR_I2C3EN                 RCC_APB1ENR_I2C3EN_Msk
#define RCC_APB1ENR_PWREN_Pos              (28U)
#define RCC_APB1ENR_PWREN_Msk              (0x1UL << RCC_APB1ENR_PWREN_Pos)
#define RCC_APB1ENR_PWREN                  RCC_APB1ENR_PWREN_Msk

#define RCC_APB2ENR_TIM1EN_Pos             (0U)
#define RCC_APB2ENR_TIM1EN_Msk             (0x1UL << RCC_APB2ENR_TIM1EN_Pos)
#define RCC_APB2ENR_TIM1EN                 RCC_APB2ENR_TIM1EN_Msk
#define RCC_APB2ENR_USART1EN_Pos           (4U)
#define RCC_APB2ENR_USART1EN_Msk           (0x1UL << RCC_APB2ENR_USART1EN_Pos)
#define RCC_APB2ENR_USART1EN               RCC_APB2ENR_USART1EN_Msk
#define RCC_APB2ENR_USART6EN_Pos           (5U)
#define RCC_APB2ENR_USART6EN_Msk           (0x1UL << RCC_APB2ENR_USART6EN_Pos)
#define RCC_APB2ENR_USART6EN               RCC_APB2ENR_USART6EN_Msk
#define RCC_APB2ENR_ADC1EN_Pos             (8U)
#define RCC_APB2ENR_ADC1EN_Msk             (0x1UL << RCC_APB2ENR_ADC1EN_Pos)
#define RCC_APB2ENR_ADC1EN                 RCC_APB2ENR_ADC1EN_Msk
#define RCC_APB2ENR_SDIOEN_Pos             (11U)
#define RCC_APB2ENR_SDIOEN_Msk             (0x1UL << RCC_APB2ENR_SDIOEN_Pos)
#define RCC_APB2ENR_SDIOEN                 RCC_APB2ENR_SDIOEN_Msk
#define RCC_APB2ENR_SPI1EN_Pos             (12U)
#define RCC_APB2ENR_SPI1EN_Msk             (0x1UL << RCC_APB2ENR_SPI1EN_Pos)
#define RCC_APB2ENR_SPI1EN                 RCC_APB2ENR_SPI1EN_Msk
#define RCC_APB2ENR_SPI4EN_Pos             (13U)
#define RCC_APB2ENR_SPI4EN_Msk             (0x1UL << RCC_APB2ENR_SPI4EN_Pos)
#define RCC_APB2ENR_SPI4EN                 RCC_APB2ENR_SPI4EN_Msk
#define RCC_APB2ENR_SYSCFGEN_Pos           (14U)
#define RCC_APB2ENR_SYSCFGEN_Msk           (0x1UL << RCC_APB2ENR_SYSCFGEN_Pos)
#define RCC_APB2ENR_SYSCFGEN               RCC_APB2ENR_SYSCFGEN_Msk
#define RCC_APB2ENR_TIM9EN_Pos             (16U)
#define RCC_APB2ENR_TIM9EN_Msk             (0x1UL << RCC_APB2ENR_TIM9EN_Pos)
#define RCC_APB2ENR_TIM9EN                 RCC_APB2ENR_TIM9EN_Msk
#define RCC_APB2ENR_TIM10EN_Pos            (17U)
#define RCC_APB2ENR_TIM10EN_Msk            (0x1UL << RCC_APB2ENR_TIM10EN_Pos)
#define RCC_APB2ENR_TIM10EN                RCC_APB2ENR_TIM10EN_Msk
#define RCC_APB2ENR_TIM11EN_Pos            (18U)
#define RCC_APB2ENR_TIM11EN_Msk            (0x1UL << RCC_APB2ENR_TIM11EN_Pos)
#define RCC_APB2ENR_TIM11EN                RCC_APB2ENR_TIM11EN_Msk

#define RCC_AHB1LPENR_GPIOALPEN_Pos        (0U)
#define RCC_AHB1LPENR_GPIOALPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIOALPEN_Pos)
#define RCC_AHB1LPENR_GPIOALPEN            RCC_AHB1LPENR_GPIOALPEN_Msk
#define RCC_AHB1LPENR_GPIOBLPEN_Pos        (1U)
#define RCC_AHB1LPENR_GPIOBLPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIOBLPEN_Pos)
#define RCC_AHB1LPENR_GPIOBLPEN            RCC_AHB1LPENR_GPIOBLPEN_Msk
#define RCC_AHB1LPENR_GPIOCLPEN_Pos        (2U)
#define RCC_AHB1LPENR_GPIOCLPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIOCLPEN_Pos)
#define RCC_AHB1LPENR_GPIOCLPEN            RCC_AHB1LPENR_GPIOCLPEN_Msk
#define RCC_AHB1LPENR_GPIODLPEN_Pos        (3U)
#define RCC_AHB1LPENR_GPIODLPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIODLPEN_Pos)
#define RCC_AHB1LPENR_GPIODLPEN            RCC_AHB1LPENR_GPIODLPEN_Msk
#define RCC_AHB1LPENR_GPIOELPEN_Pos        (4U)
#define RCC_AHB1LPENR_GPIOELPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIOELPEN_Pos)
#define RCC_AHB1LPENR_GPIOELPEN            RCC_AHB1LPENR_GPIOELPEN_Msk
#define RCC_AHB1LPENR_GPIOHLPEN_Pos        (7U)
#define RCC_AHB1LPENR_GPIOHLPEN_Msk        (0x1UL << RCC_AHB1LPENR_GPIOHLPEN_Pos)
#define RCC_AHB1LPENR_GPIOHLPEN            RCC_AHB1LPENR_GPIOHLPEN_Msk
#define RCC_AHB1LPENR_CRCLPEN_Pos          (12U)
#define RCC_AHB1LPENR_CRCLPEN_Msk          (0x1UL << RCC_AHB1LPENR_CRCLPEN_Pos)
#define RCC_AHB1LPENR_CRCLPEN              RCC_AHB1LPENR_CRCLPEN_Msk
#define RCC_AHB1LPENR_FLITFLPEN_Pos        (15U)
#define RCC_AHB1LPENR_FLITFLPEN_Msk        (0x1UL << RCC_AHB1LPENR_FLITFLPEN_Pos)
#define RCC_AHB1LPENR_FLITFLPEN            RCC_AHB1LPENR_FLITFLPEN_Msk
#define RCC_AHB1LPENR_SRAM1LPEN_Pos        (16U)
#define RCC_AHB1LPENR_SRAM1LPEN_Msk        (0x1UL << RCC_AHB1LPENR_SRAM1LPEN_Pos)
#define RCC_AHB1LPENR_SRAM1LPEN            RCC_AHB1LPENR_SRAM1LPEN_Msk
#define RCC_AHB1LPENR_DMA1LPEN_Pos         (21U)
#define RCC_AHB1LPENR_DMA1LPEN_Msk         (0x1UL << RCC_AHB1LPENR_DMA1LPEN_Pos)
#define RCC_AHB1LPENR_DMA1LPEN             RCC_AHB1LPENR_DMA1LPEN_Msk
#define RCC_AHB1LPENR_DMA2LPEN_Pos         (22U)
#define RCC_AHB1LPENR_DMA2LPEN_Msk         (0x1UL << RCC_AHB1LPENR_DMA2LPEN_Pos)
#define RCC_AHB1LPENR_DMA2LPEN             RCC_AHB1LPENR_DMA2LPEN_Msk

#define RCC_AHB2LPENR_OTGFSLPEN_Pos        (7U)
#define RCC_AHB2LPENR_OTGFSLPEN_Msk        (0x1UL << RCC_AHB2LPENR_OTGFSLPEN_Pos)
#define RCC_AHB2LPENR_OTGFSLPEN            RCC_AHB2LPENR_OTGFSLPEN_Msk

#define RCC_APB1LPENR_TIM2LPEN_Pos         (0U)
#define RCC_APB1LPENR_TIM2LPEN_Msk         (0x1UL << RCC_APB1LPENR_TIM2LPEN_Pos)
#define RCC_APB1LPENR_TIM2LPEN             RCC_APB1LPENR_TIM2LPEN_Msk
#define RCC_APB1LPENR_TIM3LPEN_Pos         (1U)
#define RCC_APB1LPENR_TIM3LPEN_Msk         (0x1UL << RCC_APB1LPENR_TIM3LPEN_Pos)
#define RCC_APB1LPENR_TIM3LPEN             RCC_APB1LPENR_TIM3LPEN_Msk
#define RCC_APB1LPENR_TIM4LPEN_Pos         (2U)
#define RCC_APB1LPENR_TIM4LPEN_Msk         (0x1UL << RCC_APB1LPENR_TIM4LPEN_Pos)
#define RCC_APB1LPENR_TIM4LPEN             RCC_APB1LPENR_TIM4LPEN_Msk
#define RCC_APB1LPENR_TIM5LPEN_Pos         (3U)
#define RCC_APB1LPENR_TIM5LPEN_Msk         (0x1UL << RCC_APB1LPENR_TIM5LPEN_Pos)
#define RCC_APB1LPENR_TIM5LPEN             RCC_APB1LPENR_TIM5LPEN_Msk
#define RCC_APB1LPENR_WWDGLPEN_Pos         (11U)
#define RCC_APB1LPENR_WWDGLPEN_Msk         (0x1UL << RCC_APB1LPENR_WWDGLPEN_Pos)
#define RCC_APB1LPENR_WWDGLPEN             RCC_APB1LPENR_WWDGLPEN_Msk
#define RCC_APB1LPENR_SPI2LPEN_Pos         (14U)
#define RCC_APB1LPENR_SPI2LPEN_Msk         (0x1UL << RCC_APB1LPENR_SPI2LPEN_Pos)
#define RCC_APB1LPENR_SPI2LPEN             RCC_APB1LPENR_SPI2LPEN_Msk
#define RCC_APB1LPENR_SPI3LPEN_Pos         (15U)
#define RCC_APB1LPENR_SPI3LPEN_Msk         (0x1UL << RCC_APB1LPENR_SPI3LPEN_Pos)
#define RCC_APB1LPENR_SPI3LPEN             RCC_APB1LPENR_SPI3LPEN_Msk
#define RCC_APB1LPENR_USART2LPEN_Pos       (17U)
#define RCC_APB1LPENR_USART2LPEN_Msk       (0x1UL << RCC_APB1LPENR_USART2LPEN_Pos)
#define RCC_APB1LPENR_USART2LPEN           RCC_APB1LPENR_USART2LPEN_Msk
#define RCC_APB1LPENR_I2C1LPEN_Pos         (21U)
#define RCC_APB1LPENR_I2C1LPEN_Msk         (0x1UL << RCC_APB1LPENR_I2C1LPEN_Pos)
#define RCC_APB1LPENR_I2C1LPEN             RCC_APB1LPENR_I2C1LPEN_Msk
#define RCC_APB1LPENR_I2C2LPEN_Pos         (22U)
#define RCC_APB1LPENR_I2C2LPEN_Msk         (0x1UL << RCC_APB1LPENR_I2C2LPEN_Pos)
#define RCC_APB1LPENR_I2C2LPEN             RCC_APB1LPENR_I2C2LPEN_Msk
#define RCC_APB1LPENR_I2C3LPEN_Pos         (23U)
#define RCC_APB1LPENR_I2C3LPEN_Msk         (0x1UL << RCC_APB1LPENR_I2C3LPEN_Pos)
#define RCC_APB1LPENR_I2C3LPEN             RCC_APB1LPENR_I2C3LPEN_Msk
#define RCC_APB1LPENR_PWRLPEN_Pos          (28U)
#define RCC_APB1LPENR_PWRLPEN_Msk          (0x1UL << RCC_APB1LPENR_PWRLPEN_Pos)
#define RCC_APB1LPENR_PWRLPEN              RCC_APB1LPENR_PWRLPEN_Msk

#define RCC_APB2LPENR_TIM1LPEN_Pos         (0U)
#define RCC_APB2LPENR_TIM1LPEN_Msk         (0x1UL << RCC_APB2LPENR_TIM1LPEN_Pos)
#define RCC_APB2LPENR_TIM1LPEN             RCC_APB2LPENR_TIM1LPEN_Msk
#define RCC_APB2LPENR_USART1LPEN_Pos       (4U)
#define RCC_APB2LPENR_USART1LPEN_Msk       (0x1UL << RCC_APB2LPENR_USART1LPEN_Pos)
#define RCC_APB2LPENR_USART1LPEN           RCC_APB2LPENR_USART1LPEN_Msk
#define RCC_APB2LPENR_USART6LPEN_Pos       (5U)
#define RCC_APB2LPENR_USART6LPEN_Msk       (0x1UL << RCC_APB2LPENR_USART6LPEN_Pos)
#define RCC_APB2LPENR_USART6LPEN           RCC_APB2LPENR_USART6LPEN_Msk
#define RCC_APB2LPENR_ADC1LPEN_Pos         (8U)
#define RCC_APB2LPENR_ADC1LPEN_Msk         (0x1UL << RCC_APB2LPENR_ADC1LPEN_Pos)
#define RCC_APB2LPENR_ADC1LPEN             RCC_APB2LPENR_ADC1LPEN_Msk
#define RCC_APB2LPENR_SDIOLPEN_Pos         (11U)
#define RCC_APB2LPENR_SDIOLPEN_Msk         (0x1UL << RCC_APB2LPENR_SDIOLPEN_Pos)
#define RCC_APB2LPENR_SDIOLPEN             RCC_APB2LPENR_SDIOLPEN_Msk
#define RCC_APB2LPENR_SPI1LPEN_Pos         (12U)
#define RCC_APB2LPENR_SPI1LPEN_Msk         (0x1UL << RCC_APB2LPENR_SPI1LPEN_Pos)
#define RCC_APB2LPENR_SPI1LPEN             RCC_APB2LPENR_SPI1LPEN_Msk
#define RCC_APB2LPENR_SPI4LPEN_Pos         (13U)
#define RCC_APB2LPENR_SPI4LPEN_Msk         (0x1UL << RCC_APB2LPENR_SPI4LPEN_Pos)
#define RCC_APB2LPENR_SPI4LPEN             RCC_APB2LPENR_SPI4LPEN_Msk
#define RCC_APB2LPENR_SYSCFGLPEN_Pos       (14U)
#define RCC_APB2LPENR_SYSCFGLPEN_Msk       (0x1UL << RCC_APB2LPENR_SYSCFGLPEN_Pos)
#define RCC_APB2LPENR_SYSCFGLPEN           RCC_APB2LPENR_SYSCFGLPEN_Msk
#define RCC_APB2LPENR_TIM9LPEN_Pos         (16U)
#define RCC_APB2LPENR_TIM9LPEN_Msk         (0x1UL << RCC_APB2LPENR_TIM9LPEN_Pos)
#define RCC_APB2LPENR_TIM9LPEN             RCC_APB2LPENR_TIM9LPEN_Msk
#define RCC_APB2LPENR_TIM10LPEN_Pos        (17U)
#define RCC_APB2LPENR_TIM10LPEN_Msk        (0x1UL << RCC_APB2LPENR_TIM10LPEN_Pos)
#define RCC_APB2LPENR_TIM10LPEN            RCC_APB2LPENR_TIM10LPEN_Msk
#define RCC_APB2LPENR_TIM11LPEN_Pos        (18U)
#define RCC_APB2LPENR_TIM11LPEN_Msk        (0x1UL << RCC_APB2LPENR_TIM11LPEN_Pos)
#define RCC_APB2LPENR_TIM11LPEN            RCC_APB2LPENR_TIM11LPEN_Msk

#define RCC_BDCR_LSEON_Pos                 (0U)
#define RCC_BDCR_LSEON_Msk                 (0x1UL << RCC_BDCR_LSEON_Pos)
#define RCC_BDCR_LSEON                     RCC_BDCR_LSEON_Msk
#define RCC_BDCR_LSERDY_Pos                (1U)
#define RCC_BDCR_LSERDY_Msk                (0x1UL << RCC_BDCR_LSERDY_Pos)
#define RCC_BDCR_LSERDY                    RCC_BDCR_LSERDY_Msk
#define RCC_BDCR_LSEBYP_Pos                (2U)
#define RCC_BDCR_LSEBYP_Msk                (0x1UL << RCC_BDCR_LSEBYP_Pos)
#define RCC_BDCR_LSEBYP                    RCC_BDCR_LSEBYP_Msk

#define RCC_BDCR_RTCSEL_Pos                (8U)
#define RCC_BDCR_RTCSEL_Msk                (0x3UL << RCC_BDCR_RTCSEL_Pos)
#define RCC_BDCR_RTCSEL                    RCC_BDCR_RTCSEL_Msk
#define RCC_BDCR_RTCSEL_0                  (0x1UL << RCC_BDCR_RTCSEL_Pos)
#define RCC_BDCR_RTCSEL_1                  (0x2UL << RCC_BDCR_RTCSEL_Pos)

#define RCC_BDCR_RTCEN_Pos                 (15U)
#define RCC_BDCR_RTCEN_Msk                 (0x1UL << RCC_BDCR_RTCEN_Pos)
#define RCC_BDCR_RTCEN                     RCC_BDCR_RTCEN_Msk
#define RCC_BDCR_BDRST_Pos                 (16U)
#define RCC_BDCR_BDRST_Msk                 (0x1UL << RCC_BDCR_BDRST_Pos)
#define RCC_BDCR_BDRST                     RCC_BDCR_BDRST_Msk

#define RCC_CSR_LSION_Pos                  (0U)
#define RCC_CSR_LSION_Msk                  (0x1UL << RCC_CSR_LSION_Pos)
#define RCC_CSR_LSION                      RCC_CSR_LSION_Msk
#define RCC_CSR_LSIRDY_Pos                 (1U)
#define RCC_CSR_LSIRDY_Msk                 (0x1UL << RCC_CSR_LSIRDY_Pos)
#define RCC_CSR_LSIRDY                     RCC_CSR_LSIRDY_Msk
#define RCC_CSR_RMVF_Pos                   (24U)
#define RCC_CSR_RMVF_Msk                   (0x1UL << RCC_CSR_RMVF_Pos)
#define RCC_CSR_RMVF                       RCC_CSR_RMVF_Msk
#define RCC_CSR_BORRSTF_Pos                (25U)
#define RCC_CSR_BORRSTF_Msk                (0x1UL << RCC_CSR_BORRSTF_Pos)
#define RCC_CSR_BORRSTF                    RCC_CSR_BORRSTF_Msk
#define RCC_CSR_PINRSTF_Pos                (26U)
#define RCC_CSR_PINRSTF_Msk                (0x1UL << RCC_CSR_PINRSTF_Pos)
#define RCC_CSR_PINRSTF                    RCC_CSR_PINRSTF_Msk
#define RCC_CSR_PORRSTF_Pos                (27U)
#define RCC_CSR_PORRSTF_Msk                (0x1UL << RCC_CSR_PORRSTF_Pos)
#define RCC_CSR_PORRSTF                    RCC_CSR_PORRSTF_Msk
#define RCC_CSR_SFTRSTF_Pos                (28U)
#define RCC_CSR_SFTRSTF_Msk                (0x1UL << RCC_CSR_SFTRSTF_Pos)
#define RCC_CSR_SFTRSTF                    RCC_CSR_SFTRSTF_Msk
#define RCC_CSR_IWDGRSTF_Pos               (29U)
#define RCC_CSR_IWDGRSTF_Msk               (0x1UL << RCC_CSR_IWDGRSTF_Pos)
#define RCC_CSR_IWDGRSTF                   RCC_CSR_IWDGRSTF_Msk
#define RCC_CSR_WWDGRSTF_Pos               (30U)
#define RCC_CSR_WWDGRSTF_Msk               (0x1UL << RCC_CSR_WWDGRSTF_Pos)
#define RCC_CSR_WWDGRSTF                   RCC_CSR_WWDGRSTF_Msk
#define RCC_CSR_LPWRRSTF_Pos               (31U)
#define RCC_CSR_LPWRRSTF_Msk               (0x1UL << RCC_CSR_LPWRRSTF_Pos)
#define RCC_CSR_LPWRRSTF                   RCC_CSR_LPWRRSTF_Msk

#define RCC_CSR_PADRSTF                    RCC_CSR_PINRSTF
#define RCC_CSR_WDGRSTF                    RCC_CSR_IWDGRSTF

#define RCC_SSCGR_MODPER_Pos               (0U)
#define RCC_SSCGR_MODPER_Msk               (0x1FFFUL << RCC_SSCGR_MODPER_Pos)
#define RCC_SSCGR_MODPER                   RCC_SSCGR_MODPER_Msk
#define RCC_SSCGR_INCSTEP_Pos              (13U)
#define RCC_SSCGR_INCSTEP_Msk              (0x7FFFUL << RCC_SSCGR_INCSTEP_Pos)
#define RCC_SSCGR_INCSTEP                  RCC_SSCGR_INCSTEP_Msk
#define RCC_SSCGR_SPREADSEL_Pos            (30U)
#define RCC_SSCGR_SPREADSEL_Msk            (0x1UL << RCC_SSCGR_SPREADSEL_Pos)
#define RCC_SSCGR_SPREADSEL                RCC_SSCGR_SPREADSEL_Msk
#define RCC_SSCGR_SSCGEN_Pos               (31U)
#define RCC_SSCGR_SSCGEN_Msk               (0x1UL << RCC_SSCGR_SSCGEN_Pos)
#define RCC_SSCGR_SSCGEN                   RCC_SSCGR_SSCGEN_Msk

#define RCC_PLLI2SCFGR_PLLI2SN_Pos         (6U)
#define RCC_PLLI2SCFGR_PLLI2SN_Msk         (0x1FFUL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN             RCC_PLLI2SCFGR_PLLI2SN_Msk
#define RCC_PLLI2SCFGR_PLLI2SN_0           (0x001UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_1           (0x002UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_2           (0x004UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_3           (0x008UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_4           (0x010UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_5           (0x020UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_6           (0x040UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_7           (0x080UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)
#define RCC_PLLI2SCFGR_PLLI2SN_8           (0x100UL << RCC_PLLI2SCFGR_PLLI2SN_Pos)

#define RCC_PLLI2SCFGR_PLLI2SR_Pos         (28U)
#define RCC_PLLI2SCFGR_PLLI2SR_Msk         (0x7UL << RCC_PLLI2SCFGR_PLLI2SR_Pos)
#define RCC_PLLI2SCFGR_PLLI2SR             RCC_PLLI2SCFGR_PLLI2SR_Msk
#define RCC_PLLI2SCFGR_PLLI2SR_0           (0x1UL << RCC_PLLI2SCFGR_PLLI2SR_Pos)
#define RCC_PLLI2SCFGR_PLLI2SR_1           (0x2UL << RCC_PLLI2SCFGR_PLLI2SR_Pos)
#define RCC_PLLI2SCFGR_PLLI2SR_2           (0x4UL << RCC_PLLI2SCFGR_PLLI2SR_Pos)

#define RCC_DCKCFGR_TIMPRE_Pos             (24U)
#define RCC_DCKCFGR_TIMPRE_Msk             (0x1UL << RCC_DCKCFGR_TIMPRE_Pos)
#define RCC_DCKCFGR_TIMPRE                 RCC_DCKCFGR_TIMPRE_Msk

#define RTC_TR_PM_Pos                 (22U)
#define RTC_TR_PM_Msk                 (0x1UL << RTC_TR_PM_Pos)
#define RTC_TR_PM                     RTC_TR_PM_Msk
#define RTC_TR_HT_Pos                 (20U)
#define RTC_TR_HT_Msk                 (0x3UL << RTC_TR_HT_Pos)
#define RTC_TR_HT                     RTC_TR_HT_Msk
#define RTC_TR_HT_0                   (0x1UL << RTC_TR_HT_Pos)
#define RTC_TR_HT_1                   (0x2UL << RTC_TR_HT_Pos)
#define RTC_TR_HU_Pos                 (16U)
#define RTC_TR_HU_Msk                 (0xFUL << RTC_TR_HU_Pos)
#define RTC_TR_HU                     RTC_TR_HU_Msk
#define RTC_TR_HU_0                   (0x1UL << RTC_TR_HU_Pos)
#define RTC_TR_HU_1                   (0x2UL << RTC_TR_HU_Pos)
#define RTC_TR_HU_2                   (0x4UL << RTC_TR_HU_Pos)
#define RTC_TR_HU_3                   (0x8UL << RTC_TR_HU_Pos)
#define RTC_TR_MNT_Pos                (12U)
#define RTC_TR_MNT_Msk                (0x7UL << RTC_TR_MNT_Pos)
#define RTC_TR_MNT                    RTC_TR_MNT_Msk
#define RTC_TR_MNT_0                  (0x1UL << RTC_TR_MNT_Pos)
#define RTC_TR_MNT_1                  (0x2UL << RTC_TR_MNT_Pos)
#define RTC_TR_MNT_2                  (0x4UL << RTC_TR_MNT_Pos)
#define RTC_TR_MNU_Pos                (8U)
#define RTC_TR_MNU_Msk                (0xFUL << RTC_TR_MNU_Pos)
#define RTC_TR_MNU                    RTC_TR_MNU_Msk
#define RTC_TR_MNU_0                  (0x1UL << RTC_TR_MNU_Pos)
#define RTC_TR_MNU_1                  (0x2UL << RTC_TR_MNU_Pos)
#define RTC_TR_MNU_2                  (0x4UL << RTC_TR_MNU_Pos)
#define RTC_TR_MNU_3                  (0x8UL << RTC_TR_MNU_Pos)
#define RTC_TR_ST_Pos                 (4U)
#define RTC_TR_ST_Msk                 (0x7UL << RTC_TR_ST_Pos)
#define RTC_TR_ST                     RTC_TR_ST_Msk
#define RTC_TR_ST_0                   (0x1UL << RTC_TR_ST_Pos)
#define RTC_TR_ST_1                   (0x2UL << RTC_TR_ST_Pos)
#define RTC_TR_ST_2                   (0x4UL << RTC_TR_ST_Pos)
#define RTC_TR_SU_Pos                 (0U)
#define RTC_TR_SU_Msk                 (0xFUL << RTC_TR_SU_Pos)
#define RTC_TR_SU                     RTC_TR_SU_Msk
#define RTC_TR_SU_0                   (0x1UL << RTC_TR_SU_Pos)
#define RTC_TR_SU_1                   (0x2UL << RTC_TR_SU_Pos)
#define RTC_TR_SU_2                   (0x4UL << RTC_TR_SU_Pos)
#define RTC_TR_SU_3                   (0x8UL << RTC_TR_SU_Pos)

#define RTC_DR_YT_Pos                 (20U)
#define RTC_DR_YT_Msk                 (0xFUL << RTC_DR_YT_Pos)
#define RTC_DR_YT                     RTC_DR_YT_Msk
#define RTC_DR_YT_0                   (0x1UL << RTC_DR_YT_Pos)
#define RTC_DR_YT_1                   (0x2UL << RTC_DR_YT_Pos)
#define RTC_DR_YT_2                   (0x4UL << RTC_DR_YT_Pos)
#define RTC_DR_YT_3                   (0x8UL << RTC_DR_YT_Pos)
#define RTC_DR_YU_Pos                 (16U)
#define RTC_DR_YU_Msk                 (0xFUL << RTC_DR_YU_Pos)
#define RTC_DR_YU                     RTC_DR_YU_Msk
#define RTC_DR_YU_0                   (0x1UL << RTC_DR_YU_Pos)
#define RTC_DR_YU_1                   (0x2UL << RTC_DR_YU_Pos)
#define RTC_DR_YU_2                   (0x4UL << RTC_DR_YU_Pos)
#define RTC_DR_YU_3                   (0x8UL << RTC_DR_YU_Pos)
#define RTC_DR_WDU_Pos                (13U)
#define RTC_DR_WDU_Msk                (0x7UL << RTC_DR_WDU_Pos)
#define RTC_DR_WDU                    RTC_DR_WDU_Msk
#define RTC_DR_WDU_0                  (0x1UL << RTC_DR_WDU_Pos)
#define RTC_DR_WDU_1                  (0x2UL << RTC_DR_WDU_Pos)
#define RTC_DR_WDU_2                  (0x4UL << RTC_DR_WDU_Pos)
#define RTC_DR_MT_Pos                 (12U)
#define RTC_DR_MT_Msk                 (0x1UL << RTC_DR_MT_Pos)
#define RTC_DR_MT                     RTC_DR_MT_Msk
#define RTC_DR_MU_Pos                 (8U)
#define RTC_DR_MU_Msk                 (0xFUL << RTC_DR_MU_Pos)
#define RTC_DR_MU                     RTC_DR_MU_Msk
#define RTC_DR_MU_0                   (0x1UL << RTC_DR_MU_Pos)
#define RTC_DR_MU_1                   (0x2UL << RTC_DR_MU_Pos)
#define RTC_DR_MU_2                   (0x4UL << RTC_DR_MU_Pos)
#define RTC_DR_MU_3                   (0x8UL << RTC_DR_MU_Pos)
#define RTC_DR_DT_Pos                 (4U)
#define RTC_DR_DT_Msk                 (0x3UL << RTC_DR_DT_Pos)
#define RTC_DR_DT                     RTC_DR_DT_Msk
#define RTC_DR_DT_0                   (0x1UL << RTC_DR_DT_Pos)
#define RTC_DR_DT_1                   (0x2UL << RTC_DR_DT_Pos)
#define RTC_DR_DU_Pos                 (0U)
#define RTC_DR_DU_Msk                 (0xFUL << RTC_DR_DU_Pos)
#define RTC_DR_DU                     RTC_DR_DU_Msk
#define RTC_DR_DU_0                   (0x1UL << RTC_DR_DU_Pos)
#define RTC_DR_DU_1                   (0x2UL << RTC_DR_DU_Pos)
#define RTC_DR_DU_2                   (0x4UL << RTC_DR_DU_Pos)
#define RTC_DR_DU_3                   (0x8UL << RTC_DR_DU_Pos)

#define RTC_CR_COE_Pos                (23U)
#define RTC_CR_COE_Msk                (0x1UL << RTC_CR_COE_Pos)
#define RTC_CR_COE                    RTC_CR_COE_Msk
#define RTC_CR_OSEL_Pos               (21U)
#define RTC_CR_OSEL_Msk               (0x3UL << RTC_CR_OSEL_Pos)
#define RTC_CR_OSEL                   RTC_CR_OSEL_Msk
#define RTC_CR_OSEL_0                 (0x1UL << RTC_CR_OSEL_Pos)
#define RTC_CR_OSEL_1                 (0x2UL << RTC_CR_OSEL_Pos)
#define RTC_CR_POL_Pos                (20U)
#define RTC_CR_POL_Msk                (0x1UL << RTC_CR_POL_Pos)
#define RTC_CR_POL                    RTC_CR_POL_Msk
#define RTC_CR_COSEL_Pos              (19U)
#define RTC_CR_COSEL_Msk              (0x1UL << RTC_CR_COSEL_Pos)
#define RTC_CR_COSEL                  RTC_CR_COSEL_Msk
#define RTC_CR_BKP_Pos                 (18U)
#define RTC_CR_BKP_Msk                 (0x1UL << RTC_CR_BKP_Pos)
#define RTC_CR_BKP                     RTC_CR_BKP_Msk
#define RTC_CR_SUB1H_Pos              (17U)
#define RTC_CR_SUB1H_Msk              (0x1UL << RTC_CR_SUB1H_Pos)
#define RTC_CR_SUB1H                  RTC_CR_SUB1H_Msk
#define RTC_CR_ADD1H_Pos              (16U)
#define RTC_CR_ADD1H_Msk              (0x1UL << RTC_CR_ADD1H_Pos)
#define RTC_CR_ADD1H                  RTC_CR_ADD1H_Msk
#define RTC_CR_TSIE_Pos               (15U)
#define RTC_CR_TSIE_Msk               (0x1UL << RTC_CR_TSIE_Pos)
#define RTC_CR_TSIE                   RTC_CR_TSIE_Msk
#define RTC_CR_WUTIE_Pos              (14U)
#define RTC_CR_WUTIE_Msk              (0x1UL << RTC_CR_WUTIE_Pos)
#define RTC_CR_WUTIE                  RTC_CR_WUTIE_Msk
#define RTC_CR_ALRBIE_Pos             (13U)
#define RTC_CR_ALRBIE_Msk             (0x1UL << RTC_CR_ALRBIE_Pos)
#define RTC_CR_ALRBIE                 RTC_CR_ALRBIE_Msk
#define RTC_CR_ALRAIE_Pos             (12U)
#define RTC_CR_ALRAIE_Msk             (0x1UL << RTC_CR_ALRAIE_Pos)
#define RTC_CR_ALRAIE                 RTC_CR_ALRAIE_Msk
#define RTC_CR_TSE_Pos                (11U)
#define RTC_CR_TSE_Msk                (0x1UL << RTC_CR_TSE_Pos)
#define RTC_CR_TSE                    RTC_CR_TSE_Msk
#define RTC_CR_WUTE_Pos               (10U)
#define RTC_CR_WUTE_Msk               (0x1UL << RTC_CR_WUTE_Pos)
#define RTC_CR_WUTE                   RTC_CR_WUTE_Msk
#define RTC_CR_ALRBE_Pos              (9U)
#define RTC_CR_ALRBE_Msk              (0x1UL << RTC_CR_ALRBE_Pos)
#define RTC_CR_ALRBE                  RTC_CR_ALRBE_Msk
#define RTC_CR_ALRAE_Pos              (8U)
#define RTC_CR_ALRAE_Msk              (0x1UL << RTC_CR_ALRAE_Pos)
#define RTC_CR_ALRAE                  RTC_CR_ALRAE_Msk
#define RTC_CR_DCE_Pos                (7U)
#define RTC_CR_DCE_Msk                (0x1UL << RTC_CR_DCE_Pos)
#define RTC_CR_DCE                    RTC_CR_DCE_Msk
#define RTC_CR_FMT_Pos                (6U)
#define RTC_CR_FMT_Msk                (0x1UL << RTC_CR_FMT_Pos)
#define RTC_CR_FMT                    RTC_CR_FMT_Msk
#define RTC_CR_BYPSHAD_Pos            (5U)
#define RTC_CR_BYPSHAD_Msk            (0x1UL << RTC_CR_BYPSHAD_Pos)
#define RTC_CR_BYPSHAD                RTC_CR_BYPSHAD_Msk
#define RTC_CR_REFCKON_Pos            (4U)
#define RTC_CR_REFCKON_Msk            (0x1UL << RTC_CR_REFCKON_Pos)
#define RTC_CR_REFCKON                RTC_CR_REFCKON_Msk
#define RTC_CR_TSEDGE_Pos             (3U)
#define RTC_CR_TSEDGE_Msk             (0x1UL << RTC_CR_TSEDGE_Pos)
#define RTC_CR_TSEDGE                 RTC_CR_TSEDGE_Msk
#define RTC_CR_WUCKSEL_Pos            (0U)
#define RTC_CR_WUCKSEL_Msk            (0x7UL << RTC_CR_WUCKSEL_Pos)
#define RTC_CR_WUCKSEL                RTC_CR_WUCKSEL_Msk
#define RTC_CR_WUCKSEL_0              (0x1UL << RTC_CR_WUCKSEL_Pos)
#define RTC_CR_WUCKSEL_1              (0x2UL << RTC_CR_WUCKSEL_Pos)
#define RTC_CR_WUCKSEL_2              (0x4UL << RTC_CR_WUCKSEL_Pos)

#define RTC_CR_BCK                     RTC_CR_BKP

#define RTC_ISR_RECALPF_Pos           (16U)
#define RTC_ISR_RECALPF_Msk           (0x1UL << RTC_ISR_RECALPF_Pos)
#define RTC_ISR_RECALPF               RTC_ISR_RECALPF_Msk
#define RTC_ISR_TAMP1F_Pos            (13U)
#define RTC_ISR_TAMP1F_Msk            (0x1UL << RTC_ISR_TAMP1F_Pos)
#define RTC_ISR_TAMP1F                RTC_ISR_TAMP1F_Msk
#define RTC_ISR_TAMP2F_Pos            (14U)
#define RTC_ISR_TAMP2F_Msk            (0x1UL << RTC_ISR_TAMP2F_Pos)
#define RTC_ISR_TAMP2F                RTC_ISR_TAMP2F_Msk
#define RTC_ISR_TSOVF_Pos             (12U)
#define RTC_ISR_TSOVF_Msk             (0x1UL << RTC_ISR_TSOVF_Pos)
#define RTC_ISR_TSOVF                 RTC_ISR_TSOVF_Msk
#define RTC_ISR_TSF_Pos               (11U)
#define RTC_ISR_TSF_Msk               (0x1UL << RTC_ISR_TSF_Pos)
#define RTC_ISR_TSF                   RTC_ISR_TSF_Msk
#define RTC_ISR_WUTF_Pos              (10U)
#define RTC_ISR_WUTF_Msk              (0x1UL << RTC_ISR_WUTF_Pos)
#define RTC_ISR_WUTF                  RTC_ISR_WUTF_Msk
#define RTC_ISR_ALRBF_Pos             (9U)
#define RTC_ISR_ALRBF_Msk             (0x1UL << RTC_ISR_ALRBF_Pos)
#define RTC_ISR_ALRBF                 RTC_ISR_ALRBF_Msk
#define RTC_ISR_ALRAF_Pos             (8U)
#define RTC_ISR_ALRAF_Msk             (0x1UL << RTC_ISR_ALRAF_Pos)
#define RTC_ISR_ALRAF                 RTC_ISR_ALRAF_Msk
#define RTC_ISR_INIT_Pos              (7U)
#define RTC_ISR_INIT_Msk              (0x1UL << RTC_ISR_INIT_Pos)
#define RTC_ISR_INIT                  RTC_ISR_INIT_Msk
#define RTC_ISR_INITF_Pos             (6U)
#define RTC_ISR_INITF_Msk             (0x1UL << RTC_ISR_INITF_Pos)
#define RTC_ISR_INITF                 RTC_ISR_INITF_Msk
#define RTC_ISR_RSF_Pos               (5U)
#define RTC_ISR_RSF_Msk               (0x1UL << RTC_ISR_RSF_Pos)
#define RTC_ISR_RSF                   RTC_ISR_RSF_Msk
#define RTC_ISR_INITS_Pos             (4U)
#define RTC_ISR_INITS_Msk             (0x1UL << RTC_ISR_INITS_Pos)
#define RTC_ISR_INITS                 RTC_ISR_INITS_Msk
#define RTC_ISR_SHPF_Pos              (3U)
#define RTC_ISR_SHPF_Msk              (0x1UL << RTC_ISR_SHPF_Pos)
#define RTC_ISR_SHPF                  RTC_ISR_SHPF_Msk
#define RTC_ISR_WUTWF_Pos             (2U)
#define RTC_ISR_WUTWF_Msk             (0x1UL << RTC_ISR_WUTWF_Pos)
#define RTC_ISR_WUTWF                 RTC_ISR_WUTWF_Msk
#define RTC_ISR_ALRBWF_Pos            (1U)
#define RTC_ISR_ALRBWF_Msk            (0x1UL << RTC_ISR_ALRBWF_Pos)
#define RTC_ISR_ALRBWF                RTC_ISR_ALRBWF_Msk
#define RTC_ISR_ALRAWF_Pos            (0U)
#define RTC_ISR_ALRAWF_Msk            (0x1UL << RTC_ISR_ALRAWF_Pos)
#define RTC_ISR_ALRAWF                RTC_ISR_ALRAWF_Msk

#define RTC_PRER_PREDIV_A_Pos         (16U)
#define RTC_PRER_PREDIV_A_Msk         (0x7FUL << RTC_PRER_PREDIV_A_Pos)
#define RTC_PRER_PREDIV_A             RTC_PRER_PREDIV_A_Msk
#define RTC_PRER_PREDIV_S_Pos         (0U)
#define RTC_PRER_PREDIV_S_Msk         (0x7FFFUL << RTC_PRER_PREDIV_S_Pos)
#define RTC_PRER_PREDIV_S             RTC_PRER_PREDIV_S_Msk

#define RTC_WUTR_WUT_Pos              (0U)
#define RTC_WUTR_WUT_Msk              (0xFFFFUL << RTC_WUTR_WUT_Pos)
#define RTC_WUTR_WUT                  RTC_WUTR_WUT_Msk

#define RTC_CALIBR_DCS_Pos            (7U)
#define RTC_CALIBR_DCS_Msk            (0x1UL << RTC_CALIBR_DCS_Pos)
#define RTC_CALIBR_DCS                RTC_CALIBR_DCS_Msk
#define RTC_CALIBR_DC_Pos             (0U)
#define RTC_CALIBR_DC_Msk             (0x1FUL << RTC_CALIBR_DC_Pos)
#define RTC_CALIBR_DC                 RTC_CALIBR_DC_Msk

#define RTC_ALRMAR_MSK4_Pos           (31U)
#define RTC_ALRMAR_MSK4_Msk           (0x1UL << RTC_ALRMAR_MSK4_Pos)
#define RTC_ALRMAR_MSK4               RTC_ALRMAR_MSK4_Msk
#define RTC_ALRMAR_WDSEL_Pos          (30U)
#define RTC_ALRMAR_WDSEL_Msk          (0x1UL << RTC_ALRMAR_WDSEL_Pos)
#define RTC_ALRMAR_WDSEL              RTC_ALRMAR_WDSEL_Msk
#define RTC_ALRMAR_DT_Pos             (28U)
#define RTC_ALRMAR_DT_Msk             (0x3UL << RTC_ALRMAR_DT_Pos)
#define RTC_ALRMAR_DT                 RTC_ALRMAR_DT_Msk
#define RTC_ALRMAR_DT_0               (0x1UL << RTC_ALRMAR_DT_Pos)
#define RTC_ALRMAR_DT_1               (0x2UL << RTC_ALRMAR_DT_Pos)
#define RTC_ALRMAR_DU_Pos             (24U)
#define RTC_ALRMAR_DU_Msk             (0xFUL << RTC_ALRMAR_DU_Pos)
#define RTC_ALRMAR_DU                 RTC_ALRMAR_DU_Msk
#define RTC_ALRMAR_DU_0               (0x1UL << RTC_ALRMAR_DU_Pos)
#define RTC_ALRMAR_DU_1               (0x2UL << RTC_ALRMAR_DU_Pos)
#define RTC_ALRMAR_DU_2               (0x4UL << RTC_ALRMAR_DU_Pos)
#define RTC_ALRMAR_DU_3               (0x8UL << RTC_ALRMAR_DU_Pos)
#define RTC_ALRMAR_MSK3_Pos           (23U)
#define RTC_ALRMAR_MSK3_Msk           (0x1UL << RTC_ALRMAR_MSK3_Pos)
#define RTC_ALRMAR_MSK3               RTC_ALRMAR_MSK3_Msk
#define RTC_ALRMAR_PM_Pos             (22U)
#define RTC_ALRMAR_PM_Msk             (0x1UL << RTC_ALRMAR_PM_Pos)
#define RTC_ALRMAR_PM                 RTC_ALRMAR_PM_Msk
#define RTC_ALRMAR_HT_Pos             (20U)
#define RTC_ALRMAR_HT_Msk             (0x3UL << RTC_ALRMAR_HT_Pos)
#define RTC_ALRMAR_HT                 RTC_ALRMAR_HT_Msk
#define RTC_ALRMAR_HT_0               (0x1UL << RTC_ALRMAR_HT_Pos)
#define RTC_ALRMAR_HT_1               (0x2UL << RTC_ALRMAR_HT_Pos)
#define RTC_ALRMAR_HU_Pos             (16U)
#define RTC_ALRMAR_HU_Msk             (0xFUL << RTC_ALRMAR_HU_Pos)
#define RTC_ALRMAR_HU                 RTC_ALRMAR_HU_Msk
#define RTC_ALRMAR_HU_0               (0x1UL << RTC_ALRMAR_HU_Pos)
#define RTC_ALRMAR_HU_1               (0x2UL << RTC_ALRMAR_HU_Pos)
#define RTC_ALRMAR_HU_2               (0x4UL << RTC_ALRMAR_HU_Pos)
#define RTC_ALRMAR_HU_3               (0x8UL << RTC_ALRMAR_HU_Pos)
#define RTC_ALRMAR_MSK2_Pos           (15U)
#define RTC_ALRMAR_MSK2_Msk           (0x1UL << RTC_ALRMAR_MSK2_Pos)
#define RTC_ALRMAR_MSK2               RTC_ALRMAR_MSK2_Msk
#define RTC_ALRMAR_MNT_Pos            (12U)
#define RTC_ALRMAR_MNT_Msk            (0x7UL << RTC_ALRMAR_MNT_Pos)
#define RTC_ALRMAR_MNT                RTC_ALRMAR_MNT_Msk
#define RTC_ALRMAR_MNT_0              (0x1UL << RTC_ALRMAR_MNT_Pos)
#define RTC_ALRMAR_MNT_1              (0x2UL << RTC_ALRMAR_MNT_Pos)
#define RTC_ALRMAR_MNT_2              (0x4UL << RTC_ALRMAR_MNT_Pos)
#define RTC_ALRMAR_MNU_Pos            (8U)
#define RTC_ALRMAR_MNU_Msk            (0xFUL << RTC_ALRMAR_MNU_Pos)
#define RTC_ALRMAR_MNU                RTC_ALRMAR_MNU_Msk
#define RTC_ALRMAR_MNU_0              (0x1UL << RTC_ALRMAR_MNU_Pos)
#define RTC_ALRMAR_MNU_1              (0x2UL << RTC_ALRMAR_MNU_Pos)
#define RTC_ALRMAR_MNU_2              (0x4UL << RTC_ALRMAR_MNU_Pos)
#define RTC_ALRMAR_MNU_3              (0x8UL << RTC_ALRMAR_MNU_Pos)
#define RTC_ALRMAR_MSK1_Pos           (7U)
#define RTC_ALRMAR_MSK1_Msk           (0x1UL << RTC_ALRMAR_MSK1_Pos)
#define RTC_ALRMAR_MSK1               RTC_ALRMAR_MSK1_Msk
#define RTC_ALRMAR_ST_Pos             (4U)
#define RTC_ALRMAR_ST_Msk             (0x7UL << RTC_ALRMAR_ST_Pos)
#define RTC_ALRMAR_ST                 RTC_ALRMAR_ST_Msk
#define RTC_ALRMAR_ST_0               (0x1UL << RTC_ALRMAR_ST_Pos)
#define RTC_ALRMAR_ST_1               (0x2UL << RTC_ALRMAR_ST_Pos)
#define RTC_ALRMAR_ST_2               (0x4UL << RTC_ALRMAR_ST_Pos)
#define RTC_ALRMAR_SU_Pos             (0U)
#define RTC_ALRMAR_SU_Msk             (0xFUL << RTC_ALRMAR_SU_Pos)
#define RTC_ALRMAR_SU                 RTC_ALRMAR_SU_Msk
#define RTC_ALRMAR_SU_0               (0x1UL << RTC_ALRMAR_SU_Pos)
#define RTC_ALRMAR_SU_1               (0x2UL << RTC_ALRMAR_SU_Pos)
#define RTC_ALRMAR_SU_2               (0x4UL << RTC_ALRMAR_SU_Pos)
#define RTC_ALRMAR_SU_3               (0x8UL << RTC_ALRMAR_SU_Pos)

#define RTC_ALRMBR_MSK4_Pos           (31U)
#define RTC_ALRMBR_MSK4_Msk           (0x1UL << RTC_ALRMBR_MSK4_Pos)
#define RTC_ALRMBR_MSK4               RTC_ALRMBR_MSK4_Msk
#define RTC_ALRMBR_WDSEL_Pos          (30U)
#define RTC_ALRMBR_WDSEL_Msk          (0x1UL << RTC_ALRMBR_WDSEL_Pos)
#define RTC_ALRMBR_WDSEL              RTC_ALRMBR_WDSEL_Msk
#define RTC_ALRMBR_DT_Pos             (28U)
#define RTC_ALRMBR_DT_Msk             (0x3UL << RTC_ALRMBR_DT_Pos)
#define RTC_ALRMBR_DT                 RTC_ALRMBR_DT_Msk
#define RTC_ALRMBR_DT_0               (0x1UL << RTC_ALRMBR_DT_Pos)
#define RTC_ALRMBR_DT_1               (0x2UL << RTC_ALRMBR_DT_Pos)
#define RTC_ALRMBR_DU_Pos             (24U)
#define RTC_ALRMBR_DU_Msk             (0xFUL << RTC_ALRMBR_DU_Pos)
#define RTC_ALRMBR_DU                 RTC_ALRMBR_DU_Msk
#define RTC_ALRMBR_DU_0               (0x1UL << RTC_ALRMBR_DU_Pos)
#define RTC_ALRMBR_DU_1               (0x2UL << RTC_ALRMBR_DU_Pos)
#define RTC_ALRMBR_DU_2               (0x4UL << RTC_ALRMBR_DU_Pos)
#define RTC_ALRMBR_DU_3               (0x8UL << RTC_ALRMBR_DU_Pos)
#define RTC_ALRMBR_MSK3_Pos           (23U)
#define RTC_ALRMBR_MSK3_Msk           (0x1UL << RTC_ALRMBR_MSK3_Pos)
#define RTC_ALRMBR_MSK3               RTC_ALRMBR_MSK3_Msk
#define RTC_ALRMBR_PM_Pos             (22U)
#define RTC_ALRMBR_PM_Msk             (0x1UL << RTC_ALRMBR_PM_Pos)
#define RTC_ALRMBR_PM                 RTC_ALRMBR_PM_Msk
#define RTC_ALRMBR_HT_Pos             (20U)
#define RTC_ALRMBR_HT_Msk             (0x3UL << RTC_ALRMBR_HT_Pos)
#define RTC_ALRMBR_HT                 RTC_ALRMBR_HT_Msk
#define RTC_ALRMBR_HT_0               (0x1UL << RTC_ALRMBR_HT_Pos)
#define RTC_ALRMBR_HT_1               (0x2UL << RTC_ALRMBR_HT_Pos)
#define RTC_ALRMBR_HU_Pos             (16U)
#define RTC_ALRMBR_HU_Msk             (0xFUL << RTC_ALRMBR_HU_Pos)
#define RTC_ALRMBR_HU                 RTC_ALRMBR_HU_Msk
#define RTC_ALRMBR_HU_0               (0x1UL << RTC_ALRMBR_HU_Pos)
#define RTC_ALRMBR_HU_1               (0x2UL << RTC_ALRMBR_HU_Pos)
#define RTC_ALRMBR_HU_2               (0x4UL << RTC_ALRMBR_HU_Pos)
#define RTC_ALRMBR_HU_3               (0x8UL << RTC_ALRMBR_HU_Pos)
#define RTC_ALRMBR_MSK2_Pos           (15U)
#define RTC_ALRMBR_MSK2_Msk           (0x1UL << RTC_ALRMBR_MSK2_Pos)
#define RTC_ALRMBR_MSK2               RTC_ALRMBR_MSK2_Msk
#define RTC_ALRMBR_MNT_Pos            (12U)
#define RTC_ALRMBR_MNT_Msk            (0x7UL << RTC_ALRMBR_MNT_Pos)
#define RTC_ALRMBR_MNT                RTC_ALRMBR_MNT_Msk
#define RTC_ALRMBR_MNT_0              (0x1UL << RTC_ALRMBR_MNT_Pos)
#define RTC_ALRMBR_MNT_1              (0x2UL << RTC_ALRMBR_MNT_Pos)
#define RTC_ALRMBR_MNT_2              (0x4UL << RTC_ALRMBR_MNT_Pos)
#define RTC_ALRMBR_MNU_Pos            (8U)
#define RTC_ALRMBR_MNU_Msk            (0xFUL << RTC_ALRMBR_MNU_Pos)
#define RTC_ALRMBR_MNU                RTC_ALRMBR_MNU_Msk
#define RTC_ALRMBR_MNU_0              (0x1UL << RTC_ALRMBR_MNU_Pos)
#define RTC_ALRMBR_MNU_1              (0x2UL << RTC_ALRMBR_MNU_Pos)
#define RTC_ALRMBR_MNU_2              (0x4UL << RTC_ALRMBR_MNU_Pos)
#define RTC_ALRMBR_MNU_3              (0x8UL << RTC_ALRMBR_MNU_Pos)
#define RTC_ALRMBR_MSK1_Pos           (7U)
#define RTC_ALRMBR_MSK1_Msk           (0x1UL << RTC_ALRMBR_MSK1_Pos)
#define RTC_ALRMBR_MSK1               RTC_ALRMBR_MSK1_Msk
#define RTC_ALRMBR_ST_Pos             (4U)
#define RTC_ALRMBR_ST_Msk             (0x7UL << RTC_ALRMBR_ST_Pos)
#define RTC_ALRMBR_ST                 RTC_ALRMBR_ST_Msk
#define RTC_ALRMBR_ST_0               (0x1UL << RTC_ALRMBR_ST_Pos)
#define RTC_ALRMBR_ST_1               (0x2UL << RTC_ALRMBR_ST_Pos)
#define RTC_ALRMBR_ST_2               (0x4UL << RTC_ALRMBR_ST_Pos)
#define RTC_ALRMBR_SU_Pos             (0U)
#define RTC_ALRMBR_SU_Msk             (0xFUL << RTC_ALRMBR_SU_Pos)
#define RTC_ALRMBR_SU                 RTC_ALRMBR_SU_Msk
#define RTC_ALRMBR_SU_0               (0x1UL << RTC_ALRMBR_SU_Pos)
#define RTC_ALRMBR_SU_1               (0x2UL << RTC_ALRMBR_SU_Pos)
#define RTC_ALRMBR_SU_2               (0x4UL << RTC_ALRMBR_SU_Pos)
#define RTC_ALRMBR_SU_3               (0x8UL << RTC_ALRMBR_SU_Pos)

#define RTC_WPR_KEY_Pos               (0U)
#define RTC_WPR_KEY_Msk               (0xFFUL << RTC_WPR_KEY_Pos)
#define RTC_WPR_KEY                   RTC_WPR_KEY_Msk

#define RTC_SSR_SS_Pos                (0U)
#define RTC_SSR_SS_Msk                (0xFFFFUL << RTC_SSR_SS_Pos)
#define RTC_SSR_SS                    RTC_SSR_SS_Msk

#define RTC_SHIFTR_SUBFS_Pos          (0U)
#define RTC_SHIFTR_SUBFS_Msk          (0x7FFFUL << RTC_SHIFTR_SUBFS_Pos)
#define RTC_SHIFTR_SUBFS              RTC_SHIFTR_SUBFS_Msk
#define RTC_SHIFTR_ADD1S_Pos          (31U)
#define RTC_SHIFTR_ADD1S_Msk          (0x1UL << RTC_SHIFTR_ADD1S_Pos)
#define RTC_SHIFTR_ADD1S              RTC_SHIFTR_ADD1S_Msk

#define RTC_TSTR_PM_Pos               (22U)
#define RTC_TSTR_PM_Msk               (0x1UL << RTC_TSTR_PM_Pos)
#define RTC_TSTR_PM                   RTC_TSTR_PM_Msk
#define RTC_TSTR_HT_Pos               (20U)
#define RTC_TSTR_HT_Msk               (0x3UL << RTC_TSTR_HT_Pos)
#define RTC_TSTR_HT                   RTC_TSTR_HT_Msk
#define RTC_TSTR_HT_0                 (0x1UL << RTC_TSTR_HT_Pos)
#define RTC_TSTR_HT_1                 (0x2UL << RTC_TSTR_HT_Pos)
#define RTC_TSTR_HU_Pos               (16U)
#define RTC_TSTR_HU_Msk               (0xFUL << RTC_TSTR_HU_Pos)
#define RTC_TSTR_HU                   RTC_TSTR_HU_Msk
#define RTC_TSTR_HU_0                 (0x1UL << RTC_TSTR_HU_Pos)
#define RTC_TSTR_HU_1                 (0x2UL << RTC_TSTR_HU_Pos)
#define RTC_TSTR_HU_2                 (0x4UL << RTC_TSTR_HU_Pos)
#define RTC_TSTR_HU_3                 (0x8UL << RTC_TSTR_HU_Pos)
#define RTC_TSTR_MNT_Pos              (12U)
#define RTC_TSTR_MNT_Msk              (0x7UL << RTC_TSTR_MNT_Pos)
#define RTC_TSTR_MNT                  RTC_TSTR_MNT_Msk
#define RTC_TSTR_MNT_0                (0x1UL << RTC_TSTR_MNT_Pos)
#define RTC_TSTR_MNT_1                (0x2UL << RTC_TSTR_MNT_Pos)
#define RTC_TSTR_MNT_2                (0x4UL << RTC_TSTR_MNT_Pos)
#define RTC_TSTR_MNU_Pos              (8U)
#define RTC_TSTR_MNU_Msk              (0xFUL << RTC_TSTR_MNU_Pos)
#define RTC_TSTR_MNU                  RTC_TSTR_MNU_Msk
#define RTC_TSTR_MNU_0                (0x1UL << RTC_TSTR_MNU_Pos)
#define RTC_TSTR_MNU_1                (0x2UL << RTC_TSTR_MNU_Pos)
#define RTC_TSTR_MNU_2                (0x4UL << RTC_TSTR_MNU_Pos)
#define RTC_TSTR_MNU_3                (0x8UL << RTC_TSTR_MNU_Pos)
#define RTC_TSTR_ST_Pos               (4U)
#define RTC_TSTR_ST_Msk               (0x7UL << RTC_TSTR_ST_Pos)
#define RTC_TSTR_ST                   RTC_TSTR_ST_Msk
#define RTC_TSTR_ST_0                 (0x1UL << RTC_TSTR_ST_Pos)
#define RTC_TSTR_ST_1                 (0x2UL << RTC_TSTR_ST_Pos)
#define RTC_TSTR_ST_2                 (0x4UL << RTC_TSTR_ST_Pos)
#define RTC_TSTR_SU_Pos               (0U)
#define RTC_TSTR_SU_Msk               (0xFUL << RTC_TSTR_SU_Pos)
#define RTC_TSTR_SU                   RTC_TSTR_SU_Msk
#define RTC_TSTR_SU_0                 (0x1UL << RTC_TSTR_SU_Pos)
#define RTC_TSTR_SU_1                 (0x2UL << RTC_TSTR_SU_Pos)
#define RTC_TSTR_SU_2                 (0x4UL << RTC_TSTR_SU_Pos)
#define RTC_TSTR_SU_3                 (0x8UL << RTC_TSTR_SU_Pos)

#define RTC_TSDR_WDU_Pos              (13U)
#define RTC_TSDR_WDU_Msk              (0x7UL << RTC_TSDR_WDU_Pos)
#define RTC_TSDR_WDU                  RTC_TSDR_WDU_Msk
#define RTC_TSDR_WDU_0                (0x1UL << RTC_TSDR_WDU_Pos)
#define RTC_TSDR_WDU_1                (0x2UL << RTC_TSDR_WDU_Pos)
#define RTC_TSDR_WDU_2                (0x4UL << RTC_TSDR_WDU_Pos)
#define RTC_TSDR_MT_Pos               (12U)
#define RTC_TSDR_MT_Msk               (0x1UL << RTC_TSDR_MT_Pos)
#define RTC_TSDR_MT                   RTC_TSDR_MT_Msk
#define RTC_TSDR_MU_Pos               (8U)
#define RTC_TSDR_MU_Msk               (0xFUL << RTC_TSDR_MU_Pos)
#define RTC_TSDR_MU                   RTC_TSDR_MU_Msk
#define RTC_TSDR_MU_0                 (0x1UL << RTC_TSDR_MU_Pos)
#define RTC_TSDR_MU_1                 (0x2UL << RTC_TSDR_MU_Pos)
#define RTC_TSDR_MU_2                 (0x4UL << RTC_TSDR_MU_Pos)
#define RTC_TSDR_MU_3                 (0x8UL << RTC_TSDR_MU_Pos)
#define RTC_TSDR_DT_Pos               (4U)
#define RTC_TSDR_DT_Msk               (0x3UL << RTC_TSDR_DT_Pos)
#define RTC_TSDR_DT                   RTC_TSDR_DT_Msk
#define RTC_TSDR_DT_0                 (0x1UL << RTC_TSDR_DT_Pos)
#define RTC_TSDR_DT_1                 (0x2UL << RTC_TSDR_DT_Pos)
#define RTC_TSDR_DU_Pos               (0U)
#define RTC_TSDR_DU_Msk               (0xFUL << RTC_TSDR_DU_Pos)
#define RTC_TSDR_DU                   RTC_TSDR_DU_Msk
#define RTC_TSDR_DU_0                 (0x1UL << RTC_TSDR_DU_Pos)
#define RTC_TSDR_DU_1                 (0x2UL << RTC_TSDR_DU_Pos)
#define RTC_TSDR_DU_2                 (0x4UL << RTC_TSDR_DU_Pos)
#define RTC_TSDR_DU_3                 (0x8UL << RTC_TSDR_DU_Pos)

#define RTC_TSSSR_SS_Pos              (0U)
#define RTC_TSSSR_SS_Msk              (0xFFFFUL << RTC_TSSSR_SS_Pos)
#define RTC_TSSSR_SS                  RTC_TSSSR_SS_Msk

#define RTC_CALR_CALP_Pos             (15U)
#define RTC_CALR_CALP_Msk             (0x1UL << RTC_CALR_CALP_Pos)
#define RTC_CALR_CALP                 RTC_CALR_CALP_Msk
#define RTC_CALR_CALW8_Pos            (14U)
#define RTC_CALR_CALW8_Msk            (0x1UL << RTC_CALR_CALW8_Pos)
#define RTC_CALR_CALW8                RTC_CALR_CALW8_Msk
#define RTC_CALR_CALW16_Pos           (13U)
#define RTC_CALR_CALW16_Msk           (0x1UL << RTC_CALR_CALW16_Pos)
#define RTC_CALR_CALW16               RTC_CALR_CALW16_Msk
#define RTC_CALR_CALM_Pos             (0U)
#define RTC_CALR_CALM_Msk             (0x1FFUL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM                 RTC_CALR_CALM_Msk
#define RTC_CALR_CALM_0               (0x001UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_1               (0x002UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_2               (0x004UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_3               (0x008UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_4               (0x010UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_5               (0x020UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_6               (0x040UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_7               (0x080UL << RTC_CALR_CALM_Pos)
#define RTC_CALR_CALM_8               (0x100UL << RTC_CALR_CALM_Pos)

#define RTC_TAFCR_ALARMOUTTYPE_Pos    (18U)
#define RTC_TAFCR_ALARMOUTTYPE_Msk    (0x1UL << RTC_TAFCR_ALARMOUTTYPE_Pos)
#define RTC_TAFCR_ALARMOUTTYPE        RTC_TAFCR_ALARMOUTTYPE_Msk
#define RTC_TAFCR_TSINSEL_Pos         (17U)
#define RTC_TAFCR_TSINSEL_Msk         (0x1UL << RTC_TAFCR_TSINSEL_Pos)
#define RTC_TAFCR_TSINSEL             RTC_TAFCR_TSINSEL_Msk
#define RTC_TAFCR_TAMP1INSEL_Pos      (16U)
#define RTC_TAFCR_TAMP1INSEL_Msk      (0x1UL << RTC_TAFCR_TAMP1INSEL_Pos)
#define RTC_TAFCR_TAMP1INSEL          RTC_TAFCR_TAMP1INSEL_Msk
#define RTC_TAFCR_TAMPPUDIS_Pos       (15U)
#define RTC_TAFCR_TAMPPUDIS_Msk       (0x1UL << RTC_TAFCR_TAMPPUDIS_Pos)
#define RTC_TAFCR_TAMPPUDIS           RTC_TAFCR_TAMPPUDIS_Msk
#define RTC_TAFCR_TAMPPRCH_Pos        (13U)
#define RTC_TAFCR_TAMPPRCH_Msk        (0x3UL << RTC_TAFCR_TAMPPRCH_Pos)
#define RTC_TAFCR_TAMPPRCH            RTC_TAFCR_TAMPPRCH_Msk
#define RTC_TAFCR_TAMPPRCH_0          (0x1UL << RTC_TAFCR_TAMPPRCH_Pos)
#define RTC_TAFCR_TAMPPRCH_1          (0x2UL << RTC_TAFCR_TAMPPRCH_Pos)
#define RTC_TAFCR_TAMPFLT_Pos         (11U)
#define RTC_TAFCR_TAMPFLT_Msk         (0x3UL << RTC_TAFCR_TAMPFLT_Pos)
#define RTC_TAFCR_TAMPFLT             RTC_TAFCR_TAMPFLT_Msk
#define RTC_TAFCR_TAMPFLT_0           (0x1UL << RTC_TAFCR_TAMPFLT_Pos)
#define RTC_TAFCR_TAMPFLT_1           (0x2UL << RTC_TAFCR_TAMPFLT_Pos)
#define RTC_TAFCR_TAMPFREQ_Pos        (8U)
#define RTC_TAFCR_TAMPFREQ_Msk        (0x7UL << RTC_TAFCR_TAMPFREQ_Pos)
#define RTC_TAFCR_TAMPFREQ            RTC_TAFCR_TAMPFREQ_Msk
#define RTC_TAFCR_TAMPFREQ_0          (0x1UL << RTC_TAFCR_TAMPFREQ_Pos)
#define RTC_TAFCR_TAMPFREQ_1          (0x2UL << RTC_TAFCR_TAMPFREQ_Pos)
#define RTC_TAFCR_TAMPFREQ_2          (0x4UL << RTC_TAFCR_TAMPFREQ_Pos)
#define RTC_TAFCR_TAMPTS_Pos          (7U)
#define RTC_TAFCR_TAMPTS_Msk          (0x1UL << RTC_TAFCR_TAMPTS_Pos)
#define RTC_TAFCR_TAMPTS              RTC_TAFCR_TAMPTS_Msk
#define RTC_TAFCR_TAMP2TRG_Pos        (4U)
#define RTC_TAFCR_TAMP2TRG_Msk        (0x1UL << RTC_TAFCR_TAMP2TRG_Pos)
#define RTC_TAFCR_TAMP2TRG            RTC_TAFCR_TAMP2TRG_Msk
#define RTC_TAFCR_TAMP2E_Pos          (3U)
#define RTC_TAFCR_TAMP2E_Msk          (0x1UL << RTC_TAFCR_TAMP2E_Pos)
#define RTC_TAFCR_TAMP2E              RTC_TAFCR_TAMP2E_Msk
#define RTC_TAFCR_TAMPIE_Pos          (2U)
#define RTC_TAFCR_TAMPIE_Msk          (0x1UL << RTC_TAFCR_TAMPIE_Pos)
#define RTC_TAFCR_TAMPIE              RTC_TAFCR_TAMPIE_Msk
#define RTC_TAFCR_TAMP1TRG_Pos        (1U)
#define RTC_TAFCR_TAMP1TRG_Msk        (0x1UL << RTC_TAFCR_TAMP1TRG_Pos)
#define RTC_TAFCR_TAMP1TRG            RTC_TAFCR_TAMP1TRG_Msk
#define RTC_TAFCR_TAMP1E_Pos          (0U)
#define RTC_TAFCR_TAMP1E_Msk          (0x1UL << RTC_TAFCR_TAMP1E_Pos)
#define RTC_TAFCR_TAMP1E              RTC_TAFCR_TAMP1E_Msk

#define RTC_TAFCR_TAMPINSEL           RTC_TAFCR_TAMP1INSEL

#define RTC_ALRMASSR_MASKSS_Pos       (24U)
#define RTC_ALRMASSR_MASKSS_Msk       (0xFUL << RTC_ALRMASSR_MASKSS_Pos)
#define RTC_ALRMASSR_MASKSS           RTC_ALRMASSR_MASKSS_Msk
#define RTC_ALRMASSR_MASKSS_0         (0x1UL << RTC_ALRMASSR_MASKSS_Pos)
#define RTC_ALRMASSR_MASKSS_1         (0x2UL << RTC_ALRMASSR_MASKSS_Pos)
#define RTC_ALRMASSR_MASKSS_2         (0x4UL << RTC_ALRMASSR_MASKSS_Pos)
#define RTC_ALRMASSR_MASKSS_3         (0x8UL << RTC_ALRMASSR_MASKSS_Pos)
#define RTC_ALRMASSR_SS_Pos           (0U)
#define RTC_ALRMASSR_SS_Msk           (0x7FFFUL << RTC_ALRMASSR_SS_Pos)
#define RTC_ALRMASSR_SS               RTC_ALRMASSR_SS_Msk

#define RTC_ALRMBSSR_MASKSS_Pos       (24U)
#define RTC_ALRMBSSR_MASKSS_Msk       (0xFUL << RTC_ALRMBSSR_MASKSS_Pos)
#define RTC_ALRMBSSR_MASKSS           RTC_ALRMBSSR_MASKSS_Msk
#define RTC_ALRMBSSR_MASKSS_0         (0x1UL << RTC_ALRMBSSR_MASKSS_Pos)
#define RTC_ALRMBSSR_MASKSS_1         (0x2UL << RTC_ALRMBSSR_MASKSS_Pos)
#define RTC_ALRMBSSR_MASKSS_2         (0x4UL << RTC_ALRMBSSR_MASKSS_Pos)
#define RTC_ALRMBSSR_MASKSS_3         (0x8UL << RTC_ALRMBSSR_MASKSS_Pos)
#define RTC_ALRMBSSR_SS_Pos           (0U)
#define RTC_ALRMBSSR_SS_Msk           (0x7FFFUL << RTC_ALRMBSSR_SS_Pos)
#define RTC_ALRMBSSR_SS               RTC_ALRMBSSR_SS_Msk

#define RTC_BKP0R_Pos                 (0U)
#define RTC_BKP0R_Msk                 (0xFFFFFFFFUL << RTC_BKP0R_Pos)
#define RTC_BKP0R                     RTC_BKP0R_Msk

#define RTC_BKP1R_Pos                 (0U)
#define RTC_BKP1R_Msk                 (0xFFFFFFFFUL << RTC_BKP1R_Pos)
#define RTC_BKP1R                     RTC_BKP1R_Msk

#define RTC_BKP2R_Pos                 (0U)
#define RTC_BKP2R_Msk                 (0xFFFFFFFFUL << RTC_BKP2R_Pos)
#define RTC_BKP2R                     RTC_BKP2R_Msk

#define RTC_BKP3R_Pos                 (0U)
#define RTC_BKP3R_Msk                 (0xFFFFFFFFUL << RTC_BKP3R_Pos)
#define RTC_BKP3R                     RTC_BKP3R_Msk

#define RTC_BKP4R_Pos                 (0U)
#define RTC_BKP4R_Msk                 (0xFFFFFFFFUL << RTC_BKP4R_Pos)
#define RTC_BKP4R                     RTC_BKP4R_Msk

#define RTC_BKP5R_Pos                 (0U)
#define RTC_BKP5R_Msk                 (0xFFFFFFFFUL << RTC_BKP5R_Pos)
#define RTC_BKP5R                     RTC_BKP5R_Msk

#define RTC_BKP6R_Pos                 (0U)
#define RTC_BKP6R_Msk                 (0xFFFFFFFFUL << RTC_BKP6R_Pos)
#define RTC_BKP6R                     RTC_BKP6R_Msk

#define RTC_BKP7R_Pos                 (0U)
#define RTC_BKP7R_Msk                 (0xFFFFFFFFUL << RTC_BKP7R_Pos)
#define RTC_BKP7R                     RTC_BKP7R_Msk

#define RTC_BKP8R_Pos                 (0U)
#define RTC_BKP8R_Msk                 (0xFFFFFFFFUL << RTC_BKP8R_Pos)
#define RTC_BKP8R                     RTC_BKP8R_Msk

#define RTC_BKP9R_Pos                 (0U)
#define RTC_BKP9R_Msk                 (0xFFFFFFFFUL << RTC_BKP9R_Pos)
#define RTC_BKP9R                     RTC_BKP9R_Msk

#define RTC_BKP10R_Pos                (0U)
#define RTC_BKP10R_Msk                (0xFFFFFFFFUL << RTC_BKP10R_Pos)
#define RTC_BKP10R                    RTC_BKP10R_Msk

#define RTC_BKP11R_Pos                (0U)
#define RTC_BKP11R_Msk                (0xFFFFFFFFUL << RTC_BKP11R_Pos)
#define RTC_BKP11R                    RTC_BKP11R_Msk

#define RTC_BKP12R_Pos                (0U)
#define RTC_BKP12R_Msk                (0xFFFFFFFFUL << RTC_BKP12R_Pos)
#define RTC_BKP12R                    RTC_BKP12R_Msk

#define RTC_BKP13R_Pos                (0U)
#define RTC_BKP13R_Msk                (0xFFFFFFFFUL << RTC_BKP13R_Pos)
#define RTC_BKP13R                    RTC_BKP13R_Msk

#define RTC_BKP14R_Pos                (0U)
#define RTC_BKP14R_Msk                (0xFFFFFFFFUL << RTC_BKP14R_Pos)
#define RTC_BKP14R                    RTC_BKP14R_Msk

#define RTC_BKP15R_Pos                (0U)
#define RTC_BKP15R_Msk                (0xFFFFFFFFUL << RTC_BKP15R_Pos)
#define RTC_BKP15R                    RTC_BKP15R_Msk

#define RTC_BKP16R_Pos                (0U)
#define RTC_BKP16R_Msk                (0xFFFFFFFFUL << RTC_BKP16R_Pos)
#define RTC_BKP16R                    RTC_BKP16R_Msk

#define RTC_BKP17R_Pos                (0U)
#define RTC_BKP17R_Msk                (0xFFFFFFFFUL << RTC_BKP17R_Pos)
#define RTC_BKP17R                    RTC_BKP17R_Msk

#define RTC_BKP18R_Pos                (0U)
#define RTC_BKP18R_Msk                (0xFFFFFFFFUL << RTC_BKP18R_Pos)
#define RTC_BKP18R                    RTC_BKP18R_Msk

#define RTC_BKP19R_Pos                (0U)
#define RTC_BKP19R_Msk                (0xFFFFFFFFUL << RTC_BKP19R_Pos)
#define RTC_BKP19R                    RTC_BKP19R_Msk

#define RTC_BKP_NUMBER                       0x000000014U

#define SDIO_POWER_PWRCTRL_Pos         (0U)
#define SDIO_POWER_PWRCTRL_Msk         (0x3UL << SDIO_POWER_PWRCTRL_Pos)
#define SDIO_POWER_PWRCTRL             SDIO_POWER_PWRCTRL_Msk
#define SDIO_POWER_PWRCTRL_0           (0x1UL << SDIO_POWER_PWRCTRL_Pos)
#define SDIO_POWER_PWRCTRL_1           (0x2UL << SDIO_POWER_PWRCTRL_Pos)

#define SDIO_CLKCR_CLKDIV_Pos          (0U)
#define SDIO_CLKCR_CLKDIV_Msk          (0xFFUL << SDIO_CLKCR_CLKDIV_Pos)
#define SDIO_CLKCR_CLKDIV              SDIO_CLKCR_CLKDIV_Msk
#define SDIO_CLKCR_CLKEN_Pos           (8U)
#define SDIO_CLKCR_CLKEN_Msk           (0x1UL << SDIO_CLKCR_CLKEN_Pos)
#define SDIO_CLKCR_CLKEN               SDIO_CLKCR_CLKEN_Msk
#define SDIO_CLKCR_PWRSAV_Pos          (9U)
#define SDIO_CLKCR_PWRSAV_Msk          (0x1UL << SDIO_CLKCR_PWRSAV_Pos)
#define SDIO_CLKCR_PWRSAV              SDIO_CLKCR_PWRSAV_Msk
#define SDIO_CLKCR_BYPASS_Pos          (10U)
#define SDIO_CLKCR_BYPASS_Msk          (0x1UL << SDIO_CLKCR_BYPASS_Pos)
#define SDIO_CLKCR_BYPASS              SDIO_CLKCR_BYPASS_Msk

#define SDIO_CLKCR_WIDBUS_Pos          (11U)
#define SDIO_CLKCR_WIDBUS_Msk          (0x3UL << SDIO_CLKCR_WIDBUS_Pos)
#define SDIO_CLKCR_WIDBUS              SDIO_CLKCR_WIDBUS_Msk
#define SDIO_CLKCR_WIDBUS_0            (0x1UL << SDIO_CLKCR_WIDBUS_Pos)
#define SDIO_CLKCR_WIDBUS_1            (0x2UL << SDIO_CLKCR_WIDBUS_Pos)

#define SDIO_CLKCR_NEGEDGE_Pos         (13U)
#define SDIO_CLKCR_NEGEDGE_Msk         (0x1UL << SDIO_CLKCR_NEGEDGE_Pos)
#define SDIO_CLKCR_NEGEDGE             SDIO_CLKCR_NEGEDGE_Msk
#define SDIO_CLKCR_HWFC_EN_Pos         (14U)
#define SDIO_CLKCR_HWFC_EN_Msk         (0x1UL << SDIO_CLKCR_HWFC_EN_Pos)
#define SDIO_CLKCR_HWFC_EN             SDIO_CLKCR_HWFC_EN_Msk

#define SDIO_ARG_CMDARG_Pos            (0U)
#define SDIO_ARG_CMDARG_Msk            (0xFFFFFFFFUL << SDIO_ARG_CMDARG_Pos)
#define SDIO_ARG_CMDARG                SDIO_ARG_CMDARG_Msk

#define SDIO_CMD_CMDINDEX_Pos          (0U)
#define SDIO_CMD_CMDINDEX_Msk          (0x3FUL << SDIO_CMD_CMDINDEX_Pos)
#define SDIO_CMD_CMDINDEX              SDIO_CMD_CMDINDEX_Msk

#define SDIO_CMD_WAITRESP_Pos          (6U)
#define SDIO_CMD_WAITRESP_Msk          (0x3UL << SDIO_CMD_WAITRESP_Pos)
#define SDIO_CMD_WAITRESP              SDIO_CMD_WAITRESP_Msk
#define SDIO_CMD_WAITRESP_0            (0x1UL << SDIO_CMD_WAITRESP_Pos)
#define SDIO_CMD_WAITRESP_1            (0x2UL << SDIO_CMD_WAITRESP_Pos)

#define SDIO_CMD_WAITINT_Pos           (8U)
#define SDIO_CMD_WAITINT_Msk           (0x1UL << SDIO_CMD_WAITINT_Pos)
#define SDIO_CMD_WAITINT               SDIO_CMD_WAITINT_Msk
#define SDIO_CMD_WAITPEND_Pos          (9U)
#define SDIO_CMD_WAITPEND_Msk          (0x1UL << SDIO_CMD_WAITPEND_Pos)
#define SDIO_CMD_WAITPEND              SDIO_CMD_WAITPEND_Msk
#define SDIO_CMD_CPSMEN_Pos            (10U)
#define SDIO_CMD_CPSMEN_Msk            (0x1UL << SDIO_CMD_CPSMEN_Pos)
#define SDIO_CMD_CPSMEN                SDIO_CMD_CPSMEN_Msk
#define SDIO_CMD_SDIOSUSPEND_Pos       (11U)
#define SDIO_CMD_SDIOSUSPEND_Msk       (0x1UL << SDIO_CMD_SDIOSUSPEND_Pos)
#define SDIO_CMD_SDIOSUSPEND           SDIO_CMD_SDIOSUSPEND_Msk
#define SDIO_CMD_ENCMDCOMPL_Pos        (12U)
#define SDIO_CMD_ENCMDCOMPL_Msk        (0x1UL << SDIO_CMD_ENCMDCOMPL_Pos)
#define SDIO_CMD_ENCMDCOMPL            SDIO_CMD_ENCMDCOMPL_Msk
#define SDIO_CMD_NIEN_Pos              (13U)
#define SDIO_CMD_NIEN_Msk              (0x1UL << SDIO_CMD_NIEN_Pos)
#define SDIO_CMD_NIEN                  SDIO_CMD_NIEN_Msk
#define SDIO_CMD_CEATACMD_Pos          (14U)
#define SDIO_CMD_CEATACMD_Msk          (0x1UL << SDIO_CMD_CEATACMD_Pos)
#define SDIO_CMD_CEATACMD              SDIO_CMD_CEATACMD_Msk

#define SDIO_RESPCMD_RESPCMD_Pos       (0U)
#define SDIO_RESPCMD_RESPCMD_Msk       (0x3FUL << SDIO_RESPCMD_RESPCMD_Pos)
#define SDIO_RESPCMD_RESPCMD           SDIO_RESPCMD_RESPCMD_Msk

#define SDIO_RESP0_CARDSTATUS0_Pos     (0U)
#define SDIO_RESP0_CARDSTATUS0_Msk     (0xFFFFFFFFUL << SDIO_RESP0_CARDSTATUS0_Pos)
#define SDIO_RESP0_CARDSTATUS0         SDIO_RESP0_CARDSTATUS0_Msk

#define SDIO_RESP1_CARDSTATUS1_Pos     (0U)
#define SDIO_RESP1_CARDSTATUS1_Msk     (0xFFFFFFFFUL << SDIO_RESP1_CARDSTATUS1_Pos)
#define SDIO_RESP1_CARDSTATUS1         SDIO_RESP1_CARDSTATUS1_Msk

#define SDIO_RESP2_CARDSTATUS2_Pos     (0U)
#define SDIO_RESP2_CARDSTATUS2_Msk     (0xFFFFFFFFUL << SDIO_RESP2_CARDSTATUS2_Pos)
#define SDIO_RESP2_CARDSTATUS2         SDIO_RESP2_CARDSTATUS2_Msk

#define SDIO_RESP3_CARDSTATUS3_Pos     (0U)
#define SDIO_RESP3_CARDSTATUS3_Msk     (0xFFFFFFFFUL << SDIO_RESP3_CARDSTATUS3_Pos)
#define SDIO_RESP3_CARDSTATUS3         SDIO_RESP3_CARDSTATUS3_Msk

#define SDIO_RESP4_CARDSTATUS4_Pos     (0U)
#define SDIO_RESP4_CARDSTATUS4_Msk     (0xFFFFFFFFUL << SDIO_RESP4_CARDSTATUS4_Pos)
#define SDIO_RESP4_CARDSTATUS4         SDIO_RESP4_CARDSTATUS4_Msk

#define SDIO_DTIMER_DATATIME_Pos       (0U)
#define SDIO_DTIMER_DATATIME_Msk       (0xFFFFFFFFUL << SDIO_DTIMER_DATATIME_Pos)
#define SDIO_DTIMER_DATATIME           SDIO_DTIMER_DATATIME_Msk

#define SDIO_DLEN_DATALENGTH_Pos       (0U)
#define SDIO_DLEN_DATALENGTH_Msk       (0x1FFFFFFUL << SDIO_DLEN_DATALENGTH_Pos)
#define SDIO_DLEN_DATALENGTH           SDIO_DLEN_DATALENGTH_Msk

#define SDIO_DCTRL_DTEN_Pos            (0U)
#define SDIO_DCTRL_DTEN_Msk            (0x1UL << SDIO_DCTRL_DTEN_Pos)
#define SDIO_DCTRL_DTEN                SDIO_DCTRL_DTEN_Msk
#define SDIO_DCTRL_DTDIR_Pos           (1U)
#define SDIO_DCTRL_DTDIR_Msk           (0x1UL << SDIO_DCTRL_DTDIR_Pos)
#define SDIO_DCTRL_DTDIR               SDIO_DCTRL_DTDIR_Msk
#define SDIO_DCTRL_DTMODE_Pos          (2U)
#define SDIO_DCTRL_DTMODE_Msk          (0x1UL << SDIO_DCTRL_DTMODE_Pos)
#define SDIO_DCTRL_DTMODE              SDIO_DCTRL_DTMODE_Msk
#define SDIO_DCTRL_DMAEN_Pos           (3U)
#define SDIO_DCTRL_DMAEN_Msk           (0x1UL << SDIO_DCTRL_DMAEN_Pos)
#define SDIO_DCTRL_DMAEN               SDIO_DCTRL_DMAEN_Msk

#define SDIO_DCTRL_DBLOCKSIZE_Pos      (4U)
#define SDIO_DCTRL_DBLOCKSIZE_Msk      (0xFUL << SDIO_DCTRL_DBLOCKSIZE_Pos)
#define SDIO_DCTRL_DBLOCKSIZE          SDIO_DCTRL_DBLOCKSIZE_Msk
#define SDIO_DCTRL_DBLOCKSIZE_0        (0x1UL << SDIO_DCTRL_DBLOCKSIZE_Pos)
#define SDIO_DCTRL_DBLOCKSIZE_1        (0x2UL << SDIO_DCTRL_DBLOCKSIZE_Pos)
#define SDIO_DCTRL_DBLOCKSIZE_2        (0x4UL << SDIO_DCTRL_DBLOCKSIZE_Pos)
#define SDIO_DCTRL_DBLOCKSIZE_3        (0x8UL << SDIO_DCTRL_DBLOCKSIZE_Pos)

#define SDIO_DCTRL_RWSTART_Pos         (8U)
#define SDIO_DCTRL_RWSTART_Msk         (0x1UL << SDIO_DCTRL_RWSTART_Pos)
#define SDIO_DCTRL_RWSTART             SDIO_DCTRL_RWSTART_Msk
#define SDIO_DCTRL_RWSTOP_Pos          (9U)
#define SDIO_DCTRL_RWSTOP_Msk          (0x1UL << SDIO_DCTRL_RWSTOP_Pos)
#define SDIO_DCTRL_RWSTOP              SDIO_DCTRL_RWSTOP_Msk
#define SDIO_DCTRL_RWMOD_Pos           (10U)
#define SDIO_DCTRL_RWMOD_Msk           (0x1UL << SDIO_DCTRL_RWMOD_Pos)
#define SDIO_DCTRL_RWMOD               SDIO_DCTRL_RWMOD_Msk
#define SDIO_DCTRL_SDIOEN_Pos          (11U)
#define SDIO_DCTRL_SDIOEN_Msk          (0x1UL << SDIO_DCTRL_SDIOEN_Pos)
#define SDIO_DCTRL_SDIOEN              SDIO_DCTRL_SDIOEN_Msk

#define SDIO_DCOUNT_DATACOUNT_Pos      (0U)
#define SDIO_DCOUNT_DATACOUNT_Msk      (0x1FFFFFFUL << SDIO_DCOUNT_DATACOUNT_Pos)
#define SDIO_DCOUNT_DATACOUNT          SDIO_DCOUNT_DATACOUNT_Msk

#define SDIO_STA_CCRCFAIL_Pos          (0U)
#define SDIO_STA_CCRCFAIL_Msk          (0x1UL << SDIO_STA_CCRCFAIL_Pos)
#define SDIO_STA_CCRCFAIL              SDIO_STA_CCRCFAIL_Msk
#define SDIO_STA_DCRCFAIL_Pos          (1U)
#define SDIO_STA_DCRCFAIL_Msk          (0x1UL << SDIO_STA_DCRCFAIL_Pos)
#define SDIO_STA_DCRCFAIL              SDIO_STA_DCRCFAIL_Msk
#define SDIO_STA_CTIMEOUT_Pos          (2U)
#define SDIO_STA_CTIMEOUT_Msk          (0x1UL << SDIO_STA_CTIMEOUT_Pos)
#define SDIO_STA_CTIMEOUT              SDIO_STA_CTIMEOUT_Msk
#define SDIO_STA_DTIMEOUT_Pos          (3U)
#define SDIO_STA_DTIMEOUT_Msk          (0x1UL << SDIO_STA_DTIMEOUT_Pos)
#define SDIO_STA_DTIMEOUT              SDIO_STA_DTIMEOUT_Msk
#define SDIO_STA_TXUNDERR_Pos          (4U)
#define SDIO_STA_TXUNDERR_Msk          (0x1UL << SDIO_STA_TXUNDERR_Pos)
#define SDIO_STA_TXUNDERR              SDIO_STA_TXUNDERR_Msk
#define SDIO_STA_RXOVERR_Pos           (5U)
#define SDIO_STA_RXOVERR_Msk           (0x1UL << SDIO_STA_RXOVERR_Pos)
#define SDIO_STA_RXOVERR               SDIO_STA_RXOVERR_Msk
#define SDIO_STA_CMDREND_Pos           (6U)
#define SDIO_STA_CMDREND_Msk           (0x1UL << SDIO_STA_CMDREND_Pos)
#define SDIO_STA_CMDREND               SDIO_STA_CMDREND_Msk
#define SDIO_STA_CMDSENT_Pos           (7U)
#define SDIO_STA_CMDSENT_Msk           (0x1UL << SDIO_STA_CMDSENT_Pos)
#define SDIO_STA_CMDSENT               SDIO_STA_CMDSENT_Msk
#define SDIO_STA_DATAEND_Pos           (8U)
#define SDIO_STA_DATAEND_Msk           (0x1UL << SDIO_STA_DATAEND_Pos)
#define SDIO_STA_DATAEND               SDIO_STA_DATAEND_Msk
#define SDIO_STA_STBITERR_Pos          (9U)
#define SDIO_STA_STBITERR_Msk          (0x1UL << SDIO_STA_STBITERR_Pos)
#define SDIO_STA_STBITERR              SDIO_STA_STBITERR_Msk
#define SDIO_STA_DBCKEND_Pos           (10U)
#define SDIO_STA_DBCKEND_Msk           (0x1UL << SDIO_STA_DBCKEND_Pos)
#define SDIO_STA_DBCKEND               SDIO_STA_DBCKEND_Msk
#define SDIO_STA_CMDACT_Pos            (11U)
#define SDIO_STA_CMDACT_Msk            (0x1UL << SDIO_STA_CMDACT_Pos)
#define SDIO_STA_CMDACT                SDIO_STA_CMDACT_Msk
#define SDIO_STA_TXACT_Pos             (12U)
#define SDIO_STA_TXACT_Msk             (0x1UL << SDIO_STA_TXACT_Pos)
#define SDIO_STA_TXACT                 SDIO_STA_TXACT_Msk
#define SDIO_STA_RXACT_Pos             (13U)
#define SDIO_STA_RXACT_Msk             (0x1UL << SDIO_STA_RXACT_Pos)
#define SDIO_STA_RXACT                 SDIO_STA_RXACT_Msk
#define SDIO_STA_TXFIFOHE_Pos          (14U)
#define SDIO_STA_TXFIFOHE_Msk          (0x1UL << SDIO_STA_TXFIFOHE_Pos)
#define SDIO_STA_TXFIFOHE              SDIO_STA_TXFIFOHE_Msk
#define SDIO_STA_RXFIFOHF_Pos          (15U)
#define SDIO_STA_RXFIFOHF_Msk          (0x1UL << SDIO_STA_RXFIFOHF_Pos)
#define SDIO_STA_RXFIFOHF              SDIO_STA_RXFIFOHF_Msk
#define SDIO_STA_TXFIFOF_Pos           (16U)
#define SDIO_STA_TXFIFOF_Msk           (0x1UL << SDIO_STA_TXFIFOF_Pos)
#define SDIO_STA_TXFIFOF               SDIO_STA_TXFIFOF_Msk
#define SDIO_STA_RXFIFOF_Pos           (17U)
#define SDIO_STA_RXFIFOF_Msk           (0x1UL << SDIO_STA_RXFIFOF_Pos)
#define SDIO_STA_RXFIFOF               SDIO_STA_RXFIFOF_Msk
#define SDIO_STA_TXFIFOE_Pos           (18U)
#define SDIO_STA_TXFIFOE_Msk           (0x1UL << SDIO_STA_TXFIFOE_Pos)
#define SDIO_STA_TXFIFOE               SDIO_STA_TXFIFOE_Msk
#define SDIO_STA_RXFIFOE_Pos           (19U)
#define SDIO_STA_RXFIFOE_Msk           (0x1UL << SDIO_STA_RXFIFOE_Pos)
#define SDIO_STA_RXFIFOE               SDIO_STA_RXFIFOE_Msk
#define SDIO_STA_TXDAVL_Pos            (20U)
#define SDIO_STA_TXDAVL_Msk            (0x1UL << SDIO_STA_TXDAVL_Pos)
#define SDIO_STA_TXDAVL                SDIO_STA_TXDAVL_Msk
#define SDIO_STA_RXDAVL_Pos            (21U)
#define SDIO_STA_RXDAVL_Msk            (0x1UL << SDIO_STA_RXDAVL_Pos)
#define SDIO_STA_RXDAVL                SDIO_STA_RXDAVL_Msk
#define SDIO_STA_SDIOIT_Pos            (22U)
#define SDIO_STA_SDIOIT_Msk            (0x1UL << SDIO_STA_SDIOIT_Pos)
#define SDIO_STA_SDIOIT                SDIO_STA_SDIOIT_Msk
#define SDIO_STA_CEATAEND_Pos          (23U)
#define SDIO_STA_CEATAEND_Msk          (0x1UL << SDIO_STA_CEATAEND_Pos)
#define SDIO_STA_CEATAEND              SDIO_STA_CEATAEND_Msk

#define SDIO_ICR_CCRCFAILC_Pos         (0U)
#define SDIO_ICR_CCRCFAILC_Msk         (0x1UL << SDIO_ICR_CCRCFAILC_Pos)
#define SDIO_ICR_CCRCFAILC             SDIO_ICR_CCRCFAILC_Msk
#define SDIO_ICR_DCRCFAILC_Pos         (1U)
#define SDIO_ICR_DCRCFAILC_Msk         (0x1UL << SDIO_ICR_DCRCFAILC_Pos)
#define SDIO_ICR_DCRCFAILC             SDIO_ICR_DCRCFAILC_Msk
#define SDIO_ICR_CTIMEOUTC_Pos         (2U)
#define SDIO_ICR_CTIMEOUTC_Msk         (0x1UL << SDIO_ICR_CTIMEOUTC_Pos)
#define SDIO_ICR_CTIMEOUTC             SDIO_ICR_CTIMEOUTC_Msk
#define SDIO_ICR_DTIMEOUTC_Pos         (3U)
#define SDIO_ICR_DTIMEOUTC_Msk         (0x1UL << SDIO_ICR_DTIMEOUTC_Pos)
#define SDIO_ICR_DTIMEOUTC             SDIO_ICR_DTIMEOUTC_Msk
#define SDIO_ICR_TXUNDERRC_Pos         (4U)
#define SDIO_ICR_TXUNDERRC_Msk         (0x1UL << SDIO_ICR_TXUNDERRC_Pos)
#define SDIO_ICR_TXUNDERRC             SDIO_ICR_TXUNDERRC_Msk
#define SDIO_ICR_RXOVERRC_Pos          (5U)
#define SDIO_ICR_RXOVERRC_Msk          (0x1UL << SDIO_ICR_RXOVERRC_Pos)
#define SDIO_ICR_RXOVERRC              SDIO_ICR_RXOVERRC_Msk
#define SDIO_ICR_CMDRENDC_Pos          (6U)
#define SDIO_ICR_CMDRENDC_Msk          (0x1UL << SDIO_ICR_CMDRENDC_Pos)
#define SDIO_ICR_CMDRENDC              SDIO_ICR_CMDRENDC_Msk
#define SDIO_ICR_CMDSENTC_Pos          (7U)
#define SDIO_ICR_CMDSENTC_Msk          (0x1UL << SDIO_ICR_CMDSENTC_Pos)
#define SDIO_ICR_CMDSENTC              SDIO_ICR_CMDSENTC_Msk
#define SDIO_ICR_DATAENDC_Pos          (8U)
#define SDIO_ICR_DATAENDC_Msk          (0x1UL << SDIO_ICR_DATAENDC_Pos)
#define SDIO_ICR_DATAENDC              SDIO_ICR_DATAENDC_Msk
#define SDIO_ICR_STBITERRC_Pos         (9U)
#define SDIO_ICR_STBITERRC_Msk         (0x1UL << SDIO_ICR_STBITERRC_Pos)
#define SDIO_ICR_STBITERRC             SDIO_ICR_STBITERRC_Msk
#define SDIO_ICR_DBCKENDC_Pos          (10U)
#define SDIO_ICR_DBCKENDC_Msk          (0x1UL << SDIO_ICR_DBCKENDC_Pos)
#define SDIO_ICR_DBCKENDC              SDIO_ICR_DBCKENDC_Msk
#define SDIO_ICR_SDIOITC_Pos           (22U)
#define SDIO_ICR_SDIOITC_Msk           (0x1UL << SDIO_ICR_SDIOITC_Pos)
#define SDIO_ICR_SDIOITC               SDIO_ICR_SDIOITC_Msk
#define SDIO_ICR_CEATAENDC_Pos         (23U)
#define SDIO_ICR_CEATAENDC_Msk         (0x1UL << SDIO_ICR_CEATAENDC_Pos)
#define SDIO_ICR_CEATAENDC             SDIO_ICR_CEATAENDC_Msk

#define SDIO_MASK_CCRCFAILIE_Pos       (0U)
#define SDIO_MASK_CCRCFAILIE_Msk       (0x1UL << SDIO_MASK_CCRCFAILIE_Pos)
#define SDIO_MASK_CCRCFAILIE           SDIO_MASK_CCRCFAILIE_Msk
#define SDIO_MASK_DCRCFAILIE_Pos       (1U)
#define SDIO_MASK_DCRCFAILIE_Msk       (0x1UL << SDIO_MASK_DCRCFAILIE_Pos)
#define SDIO_MASK_DCRCFAILIE           SDIO_MASK_DCRCFAILIE_Msk
#define SDIO_MASK_CTIMEOUTIE_Pos       (2U)
#define SDIO_MASK_CTIMEOUTIE_Msk       (0x1UL << SDIO_MASK_CTIMEOUTIE_Pos)
#define SDIO_MASK_CTIMEOUTIE           SDIO_MASK_CTIMEOUTIE_Msk
#define SDIO_MASK_DTIMEOUTIE_Pos       (3U)
#define SDIO_MASK_DTIMEOUTIE_Msk       (0x1UL << SDIO_MASK_DTIMEOUTIE_Pos)
#define SDIO_MASK_DTIMEOUTIE           SDIO_MASK_DTIMEOUTIE_Msk
#define SDIO_MASK_TXUNDERRIE_Pos       (4U)
#define SDIO_MASK_TXUNDERRIE_Msk       (0x1UL << SDIO_MASK_TXUNDERRIE_Pos)
#define SDIO_MASK_TXUNDERRIE           SDIO_MASK_TXUNDERRIE_Msk
#define SDIO_MASK_RXOVERRIE_Pos        (5U)
#define SDIO_MASK_RXOVERRIE_Msk        (0x1UL << SDIO_MASK_RXOVERRIE_Pos)
#define SDIO_MASK_RXOVERRIE            SDIO_MASK_RXOVERRIE_Msk
#define SDIO_MASK_CMDRENDIE_Pos        (6U)
#define SDIO_MASK_CMDRENDIE_Msk        (0x1UL << SDIO_MASK_CMDRENDIE_Pos)
#define SDIO_MASK_CMDRENDIE            SDIO_MASK_CMDRENDIE_Msk
#define SDIO_MASK_CMDSENTIE_Pos        (7U)
#define SDIO_MASK_CMDSENTIE_Msk        (0x1UL << SDIO_MASK_CMDSENTIE_Pos)
#define SDIO_MASK_CMDSENTIE            SDIO_MASK_CMDSENTIE_Msk
#define SDIO_MASK_DATAENDIE_Pos        (8U)
#define SDIO_MASK_DATAENDIE_Msk        (0x1UL << SDIO_MASK_DATAENDIE_Pos)
#define SDIO_MASK_DATAENDIE            SDIO_MASK_DATAENDIE_Msk
#define SDIO_MASK_STBITERRIE_Pos       (9U)
#define SDIO_MASK_STBITERRIE_Msk       (0x1UL << SDIO_MASK_STBITERRIE_Pos)
#define SDIO_MASK_STBITERRIE           SDIO_MASK_STBITERRIE_Msk
#define SDIO_MASK_DBCKENDIE_Pos        (10U)
#define SDIO_MASK_DBCKENDIE_Msk        (0x1UL << SDIO_MASK_DBCKENDIE_Pos)
#define SDIO_MASK_DBCKENDIE            SDIO_MASK_DBCKENDIE_Msk
#define SDIO_MASK_CMDACTIE_Pos         (11U)
#define SDIO_MASK_CMDACTIE_Msk         (0x1UL << SDIO_MASK_CMDACTIE_Pos)
#define SDIO_MASK_CMDACTIE             SDIO_MASK_CMDACTIE_Msk
#define SDIO_MASK_TXACTIE_Pos          (12U)
#define SDIO_MASK_TXACTIE_Msk          (0x1UL << SDIO_MASK_TXACTIE_Pos)
#define SDIO_MASK_TXACTIE              SDIO_MASK_TXACTIE_Msk
#define SDIO_MASK_RXACTIE_Pos          (13U)
#define SDIO_MASK_RXACTIE_Msk          (0x1UL << SDIO_MASK_RXACTIE_Pos)
#define SDIO_MASK_RXACTIE              SDIO_MASK_RXACTIE_Msk
#define SDIO_MASK_TXFIFOHEIE_Pos       (14U)
#define SDIO_MASK_TXFIFOHEIE_Msk       (0x1UL << SDIO_MASK_TXFIFOHEIE_Pos)
#define SDIO_MASK_TXFIFOHEIE           SDIO_MASK_TXFIFOHEIE_Msk
#define SDIO_MASK_RXFIFOHFIE_Pos       (15U)
#define SDIO_MASK_RXFIFOHFIE_Msk       (0x1UL << SDIO_MASK_RXFIFOHFIE_Pos)
#define SDIO_MASK_RXFIFOHFIE           SDIO_MASK_RXFIFOHFIE_Msk
#define SDIO_MASK_TXFIFOFIE_Pos        (16U)
#define SDIO_MASK_TXFIFOFIE_Msk        (0x1UL << SDIO_MASK_TXFIFOFIE_Pos)
#define SDIO_MASK_TXFIFOFIE            SDIO_MASK_TXFIFOFIE_Msk
#define SDIO_MASK_RXFIFOFIE_Pos        (17U)
#define SDIO_MASK_RXFIFOFIE_Msk        (0x1UL << SDIO_MASK_RXFIFOFIE_Pos)
#define SDIO_MASK_RXFIFOFIE            SDIO_MASK_RXFIFOFIE_Msk
#define SDIO_MASK_TXFIFOEIE_Pos        (18U)
#define SDIO_MASK_TXFIFOEIE_Msk        (0x1UL << SDIO_MASK_TXFIFOEIE_Pos)
#define SDIO_MASK_TXFIFOEIE            SDIO_MASK_TXFIFOEIE_Msk
#define SDIO_MASK_RXFIFOEIE_Pos        (19U)
#define SDIO_MASK_RXFIFOEIE_Msk        (0x1UL << SDIO_MASK_RXFIFOEIE_Pos)
#define SDIO_MASK_RXFIFOEIE            SDIO_MASK_RXFIFOEIE_Msk
#define SDIO_MASK_TXDAVLIE_Pos         (20U)
#define SDIO_MASK_TXDAVLIE_Msk         (0x1UL << SDIO_MASK_TXDAVLIE_Pos)
#define SDIO_MASK_TXDAVLIE             SDIO_MASK_TXDAVLIE_Msk
#define SDIO_MASK_RXDAVLIE_Pos         (21U)
#define SDIO_MASK_RXDAVLIE_Msk         (0x1UL << SDIO_MASK_RXDAVLIE_Pos)
#define SDIO_MASK_RXDAVLIE             SDIO_MASK_RXDAVLIE_Msk
#define SDIO_MASK_SDIOITIE_Pos         (22U)
#define SDIO_MASK_SDIOITIE_Msk         (0x1UL << SDIO_MASK_SDIOITIE_Pos)
#define SDIO_MASK_SDIOITIE             SDIO_MASK_SDIOITIE_Msk
#define SDIO_MASK_CEATAENDIE_Pos       (23U)
#define SDIO_MASK_CEATAENDIE_Msk       (0x1UL << SDIO_MASK_CEATAENDIE_Pos)
#define SDIO_MASK_CEATAENDIE           SDIO_MASK_CEATAENDIE_Msk

#define SDIO_FIFOCNT_FIFOCOUNT_Pos     (0U)
#define SDIO_FIFOCNT_FIFOCOUNT_Msk     (0xFFFFFFUL << SDIO_FIFOCNT_FIFOCOUNT_Pos)
#define SDIO_FIFOCNT_FIFOCOUNT         SDIO_FIFOCNT_FIFOCOUNT_Msk

#define SDIO_FIFO_FIFODATA_Pos         (0U)
#define SDIO_FIFO_FIFODATA_Msk         (0xFFFFFFFFUL << SDIO_FIFO_FIFODATA_Pos)
#define SDIO_FIFO_FIFODATA             SDIO_FIFO_FIFODATA_Msk

#define SPI_I2S_FULLDUPLEX_SUPPORT

#define SPI_CR1_CPHA_Pos            (0U)
#define SPI_CR1_CPHA_Msk            (0x1UL << SPI_CR1_CPHA_Pos)
#define SPI_CR1_CPHA                SPI_CR1_CPHA_Msk
#define SPI_CR1_CPOL_Pos            (1U)
#define SPI_CR1_CPOL_Msk            (0x1UL << SPI_CR1_CPOL_Pos)
#define SPI_CR1_CPOL                SPI_CR1_CPOL_Msk
#define SPI_CR1_MSTR_Pos            (2U)
#define SPI_CR1_MSTR_Msk            (0x1UL << SPI_CR1_MSTR_Pos)
#define SPI_CR1_MSTR                SPI_CR1_MSTR_Msk

#define SPI_CR1_BR_Pos              (3U)
#define SPI_CR1_BR_Msk              (0x7UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR                  SPI_CR1_BR_Msk
#define SPI_CR1_BR_0                (0x1UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_1                (0x2UL << SPI_CR1_BR_Pos)
#define SPI_CR1_BR_2                (0x4UL << SPI_CR1_BR_Pos)

#define SPI_CR1_SPE_Pos             (6U)
#define SPI_CR1_SPE_Msk             (0x1UL << SPI_CR1_SPE_Pos)
#define SPI_CR1_SPE                 SPI_CR1_SPE_Msk
#define SPI_CR1_LSBFIRST_Pos        (7U)
#define SPI_CR1_LSBFIRST_Msk        (0x1UL << SPI_CR1_LSBFIRST_Pos)
#define SPI_CR1_LSBFIRST            SPI_CR1_LSBFIRST_Msk
#define SPI_CR1_SSI_Pos             (8U)
#define SPI_CR1_SSI_Msk             (0x1UL << SPI_CR1_SSI_Pos)
#define SPI_CR1_SSI                 SPI_CR1_SSI_Msk
#define SPI_CR1_SSM_Pos             (9U)
#define SPI_CR1_SSM_Msk             (0x1UL << SPI_CR1_SSM_Pos)
#define SPI_CR1_SSM                 SPI_CR1_SSM_Msk
#define SPI_CR1_RXONLY_Pos          (10U)
#define SPI_CR1_RXONLY_Msk          (0x1UL << SPI_CR1_RXONLY_Pos)
#define SPI_CR1_RXONLY              SPI_CR1_RXONLY_Msk
#define SPI_CR1_DFF_Pos             (11U)
#define SPI_CR1_DFF_Msk             (0x1UL << SPI_CR1_DFF_Pos)
#define SPI_CR1_DFF                 SPI_CR1_DFF_Msk
#define SPI_CR1_CRCNEXT_Pos         (12U)
#define SPI_CR1_CRCNEXT_Msk         (0x1UL << SPI_CR1_CRCNEXT_Pos)
#define SPI_CR1_CRCNEXT             SPI_CR1_CRCNEXT_Msk
#define SPI_CR1_CRCEN_Pos           (13U)
#define SPI_CR1_CRCEN_Msk           (0x1UL << SPI_CR1_CRCEN_Pos)
#define SPI_CR1_CRCEN               SPI_CR1_CRCEN_Msk
#define SPI_CR1_BIDIOE_Pos          (14U)
#define SPI_CR1_BIDIOE_Msk          (0x1UL << SPI_CR1_BIDIOE_Pos)
#define SPI_CR1_BIDIOE              SPI_CR1_BIDIOE_Msk
#define SPI_CR1_BIDIMODE_Pos        (15U)
#define SPI_CR1_BIDIMODE_Msk        (0x1UL << SPI_CR1_BIDIMODE_Pos)
#define SPI_CR1_BIDIMODE            SPI_CR1_BIDIMODE_Msk

#define SPI_CR2_RXDMAEN_Pos         (0U)
#define SPI_CR2_RXDMAEN_Msk         (0x1UL << SPI_CR2_RXDMAEN_Pos)
#define SPI_CR2_RXDMAEN             SPI_CR2_RXDMAEN_Msk
#define SPI_CR2_TXDMAEN_Pos         (1U)
#define SPI_CR2_TXDMAEN_Msk         (0x1UL << SPI_CR2_TXDMAEN_Pos)
#define SPI_CR2_TXDMAEN             SPI_CR2_TXDMAEN_Msk
#define SPI_CR2_SSOE_Pos            (2U)
#define SPI_CR2_SSOE_Msk            (0x1UL << SPI_CR2_SSOE_Pos)
#define SPI_CR2_SSOE                SPI_CR2_SSOE_Msk
#define SPI_CR2_FRF_Pos             (4U)
#define SPI_CR2_FRF_Msk             (0x1UL << SPI_CR2_FRF_Pos)
#define SPI_CR2_FRF                 SPI_CR2_FRF_Msk
#define SPI_CR2_ERRIE_Pos           (5U)
#define SPI_CR2_ERRIE_Msk           (0x1UL << SPI_CR2_ERRIE_Pos)
#define SPI_CR2_ERRIE               SPI_CR2_ERRIE_Msk
#define SPI_CR2_RXNEIE_Pos          (6U)
#define SPI_CR2_RXNEIE_Msk          (0x1UL << SPI_CR2_RXNEIE_Pos)
#define SPI_CR2_RXNEIE              SPI_CR2_RXNEIE_Msk
#define SPI_CR2_TXEIE_Pos           (7U)
#define SPI_CR2_TXEIE_Msk           (0x1UL << SPI_CR2_TXEIE_Pos)
#define SPI_CR2_TXEIE               SPI_CR2_TXEIE_Msk

#define SPI_SR_RXNE_Pos             (0U)
#define SPI_SR_RXNE_Msk             (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE                 SPI_SR_RXNE_Msk
#define SPI_SR_TXE_Pos              (1U)
#define SPI_SR_TXE_Msk              (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE                  SPI_SR_TXE_Msk
#define SPI_SR_CHSIDE_Pos           (2U)
#define SPI_SR_CHSIDE_Msk           (0x1UL << SPI_SR_CHSIDE_Pos)
#define SPI_SR_CHSIDE               SPI_SR_CHSIDE_Msk
#define SPI_SR_UDR_Pos              (3U)
#define SPI_SR_UDR_Msk              (0x1UL << SPI_SR_UDR_Pos)
#define SPI_SR_UDR                  SPI_SR_UDR_Msk
#define SPI_SR_CRCERR_Pos           (4U)
#define SPI_SR_CRCERR_Msk           (0x1UL << SPI_SR_CRCERR_Pos)
#define SPI_SR_CRCERR               SPI_SR_CRCERR_Msk
#define SPI_SR_MODF_Pos             (5U)
#define SPI_SR_MODF_Msk             (0x1UL << SPI_SR_MODF_Pos)
#define SPI_SR_MODF                 SPI_SR_MODF_Msk
#define SPI_SR_OVR_Pos              (6U)
#define SPI_SR_OVR_Msk              (0x1UL << SPI_SR_OVR_Pos)
#define SPI_SR_OVR                  SPI_SR_OVR_Msk
#define SPI_SR_BSY_Pos              (7U)
#define SPI_SR_BSY_Msk              (0x1UL << SPI_SR_BSY_Pos)
#define SPI_SR_BSY                  SPI_SR_BSY_Msk
#define SPI_SR_FRE_Pos              (8U)
#define SPI_SR_FRE_Msk              (0x1UL << SPI_SR_FRE_Pos)
#define SPI_SR_FRE                  SPI_SR_FRE_Msk

#define SPI_DR_DR_Pos               (0U)
#define SPI_DR_DR_Msk               (0xFFFFUL << SPI_DR_DR_Pos)
#define SPI_DR_DR                   SPI_DR_DR_Msk

#define SPI_CRCPR_CRCPOLY_Pos       (0U)
#define SPI_CRCPR_CRCPOLY_Msk       (0xFFFFUL << SPI_CRCPR_CRCPOLY_Pos)
#define SPI_CRCPR_CRCPOLY           SPI_CRCPR_CRCPOLY_Msk

#define SPI_RXCRCR_RXCRC_Pos        (0U)
#define SPI_RXCRCR_RXCRC_Msk        (0xFFFFUL << SPI_RXCRCR_RXCRC_Pos)
#define SPI_RXCRCR_RXCRC            SPI_RXCRCR_RXCRC_Msk

#define SPI_TXCRCR_TXCRC_Pos        (0U)
#define SPI_TXCRCR_TXCRC_Msk        (0xFFFFUL << SPI_TXCRCR_TXCRC_Pos)
#define SPI_TXCRCR_TXCRC            SPI_TXCRCR_TXCRC_Msk

#define SPI_I2SCFGR_CHLEN_Pos       (0U)
#define SPI_I2SCFGR_CHLEN_Msk       (0x1UL << SPI_I2SCFGR_CHLEN_Pos)
#define SPI_I2SCFGR_CHLEN           SPI_I2SCFGR_CHLEN_Msk

#define SPI_I2SCFGR_DATLEN_Pos      (1U)
#define SPI_I2SCFGR_DATLEN_Msk      (0x3UL << SPI_I2SCFGR_DATLEN_Pos)
#define SPI_I2SCFGR_DATLEN          SPI_I2SCFGR_DATLEN_Msk
#define SPI_I2SCFGR_DATLEN_0        (0x1UL << SPI_I2SCFGR_DATLEN_Pos)
#define SPI_I2SCFGR_DATLEN_1        (0x2UL << SPI_I2SCFGR_DATLEN_Pos)

#define SPI_I2SCFGR_CKPOL_Pos       (3U)
#define SPI_I2SCFGR_CKPOL_Msk       (0x1UL << SPI_I2SCFGR_CKPOL_Pos)
#define SPI_I2SCFGR_CKPOL           SPI_I2SCFGR_CKPOL_Msk

#define SPI_I2SCFGR_I2SSTD_Pos      (4U)
#define SPI_I2SCFGR_I2SSTD_Msk      (0x3UL << SPI_I2SCFGR_I2SSTD_Pos)
#define SPI_I2SCFGR_I2SSTD          SPI_I2SCFGR_I2SSTD_Msk
#define SPI_I2SCFGR_I2SSTD_0        (0x1UL << SPI_I2SCFGR_I2SSTD_Pos)
#define SPI_I2SCFGR_I2SSTD_1        (0x2UL << SPI_I2SCFGR_I2SSTD_Pos)

#define SPI_I2SCFGR_PCMSYNC_Pos     (7U)
#define SPI_I2SCFGR_PCMSYNC_Msk     (0x1UL << SPI_I2SCFGR_PCMSYNC_Pos)
#define SPI_I2SCFGR_PCMSYNC         SPI_I2SCFGR_PCMSYNC_Msk

#define SPI_I2SCFGR_I2SCFG_Pos      (8U)
#define SPI_I2SCFGR_I2SCFG_Msk      (0x3UL << SPI_I2SCFGR_I2SCFG_Pos)
#define SPI_I2SCFGR_I2SCFG          SPI_I2SCFGR_I2SCFG_Msk
#define SPI_I2SCFGR_I2SCFG_0        (0x1UL << SPI_I2SCFGR_I2SCFG_Pos)
#define SPI_I2SCFGR_I2SCFG_1        (0x2UL << SPI_I2SCFGR_I2SCFG_Pos)

#define SPI_I2SCFGR_I2SE_Pos        (10U)
#define SPI_I2SCFGR_I2SE_Msk        (0x1UL << SPI_I2SCFGR_I2SE_Pos)
#define SPI_I2SCFGR_I2SE            SPI_I2SCFGR_I2SE_Msk
#define SPI_I2SCFGR_I2SMOD_Pos      (11U)
#define SPI_I2SCFGR_I2SMOD_Msk      (0x1UL << SPI_I2SCFGR_I2SMOD_Pos)
#define SPI_I2SCFGR_I2SMOD          SPI_I2SCFGR_I2SMOD_Msk

#define SPI_I2SPR_I2SDIV_Pos        (0U)
#define SPI_I2SPR_I2SDIV_Msk        (0xFFUL << SPI_I2SPR_I2SDIV_Pos)
#define SPI_I2SPR_I2SDIV            SPI_I2SPR_I2SDIV_Msk
#define SPI_I2SPR_ODD_Pos           (8U)
#define SPI_I2SPR_ODD_Msk           (0x1UL << SPI_I2SPR_ODD_Pos)
#define SPI_I2SPR_ODD               SPI_I2SPR_ODD_Msk
#define SPI_I2SPR_MCKOE_Pos         (9U)
#define SPI_I2SPR_MCKOE_Msk         (0x1UL << SPI_I2SPR_MCKOE_Pos)
#define SPI_I2SPR_MCKOE             SPI_I2SPR_MCKOE_Msk

#define SYSCFG_MEMRMP_MEM_MODE_Pos           (0U)
#define SYSCFG_MEMRMP_MEM_MODE_Msk           (0x3UL << SYSCFG_MEMRMP_MEM_MODE_Pos)
#define SYSCFG_MEMRMP_MEM_MODE               SYSCFG_MEMRMP_MEM_MODE_Msk
#define SYSCFG_MEMRMP_MEM_MODE_0             (0x1UL << SYSCFG_MEMRMP_MEM_MODE_Pos)
#define SYSCFG_MEMRMP_MEM_MODE_1             (0x2UL << SYSCFG_MEMRMP_MEM_MODE_Pos)

#define SYSCFG_PMC_ADC1DC2_Pos               (16U)
#define SYSCFG_PMC_ADC1DC2_Msk               (0x1UL << SYSCFG_PMC_ADC1DC2_Pos)
#define SYSCFG_PMC_ADC1DC2                   SYSCFG_PMC_ADC1DC2_Msk

#define SYSCFG_EXTICR1_EXTI0_Pos             (0U)
#define SYSCFG_EXTICR1_EXTI0_Msk             (0xFUL << SYSCFG_EXTICR1_EXTI0_Pos)
#define SYSCFG_EXTICR1_EXTI0                 SYSCFG_EXTICR1_EXTI0_Msk
#define SYSCFG_EXTICR1_EXTI1_Pos             (4U)
#define SYSCFG_EXTICR1_EXTI1_Msk             (0xFUL << SYSCFG_EXTICR1_EXTI1_Pos)
#define SYSCFG_EXTICR1_EXTI1                 SYSCFG_EXTICR1_EXTI1_Msk
#define SYSCFG_EXTICR1_EXTI2_Pos             (8U)
#define SYSCFG_EXTICR1_EXTI2_Msk             (0xFUL << SYSCFG_EXTICR1_EXTI2_Pos)
#define SYSCFG_EXTICR1_EXTI2                 SYSCFG_EXTICR1_EXTI2_Msk
#define SYSCFG_EXTICR1_EXTI3_Pos             (12U)
#define SYSCFG_EXTICR1_EXTI3_Msk             (0xFUL << SYSCFG_EXTICR1_EXTI3_Pos)
#define SYSCFG_EXTICR1_EXTI3                 SYSCFG_EXTICR1_EXTI3_Msk

#define SYSCFG_EXTICR1_EXTI0_PA              0x0000U
#define SYSCFG_EXTICR1_EXTI0_PB              0x0001U
#define SYSCFG_EXTICR1_EXTI0_PC              0x0002U
#define SYSCFG_EXTICR1_EXTI0_PD              0x0003U
#define SYSCFG_EXTICR1_EXTI0_PE              0x0004U
#define SYSCFG_EXTICR1_EXTI0_PH              0x0007U

#define SYSCFG_EXTICR1_EXTI1_PA              0x0000U
#define SYSCFG_EXTICR1_EXTI1_PB              0x0010U
#define SYSCFG_EXTICR1_EXTI1_PC              0x0020U
#define SYSCFG_EXTICR1_EXTI1_PD              0x0030U
#define SYSCFG_EXTICR1_EXTI1_PE              0x0040U
#define SYSCFG_EXTICR1_EXTI1_PH              0x0070U

#define SYSCFG_EXTICR1_EXTI2_PA              0x0000U
#define SYSCFG_EXTICR1_EXTI2_PB              0x0100U
#define SYSCFG_EXTICR1_EXTI2_PC              0x0200U
#define SYSCFG_EXTICR1_EXTI2_PD              0x0300U
#define SYSCFG_EXTICR1_EXTI2_PE              0x0400U
#define SYSCFG_EXTICR1_EXTI2_PH              0x0700U

#define SYSCFG_EXTICR1_EXTI3_PA              0x0000U
#define SYSCFG_EXTICR1_EXTI3_PB              0x1000U
#define SYSCFG_EXTICR1_EXTI3_PC              0x2000U
#define SYSCFG_EXTICR1_EXTI3_PD              0x3000U
#define SYSCFG_EXTICR1_EXTI3_PE              0x4000U
#define SYSCFG_EXTICR1_EXTI3_PH              0x7000U

#define SYSCFG_EXTICR2_EXTI4_Pos             (0U)
#define SYSCFG_EXTICR2_EXTI4_Msk             (0xFUL << SYSCFG_EXTICR2_EXTI4_Pos)
#define SYSCFG_EXTICR2_EXTI4                 SYSCFG_EXTICR2_EXTI4_Msk
#define SYSCFG_EXTICR2_EXTI5_Pos             (4U)
#define SYSCFG_EXTICR2_EXTI5_Msk             (0xFUL << SYSCFG_EXTICR2_EXTI5_Pos)
#define SYSCFG_EXTICR2_EXTI5                 SYSCFG_EXTICR2_EXTI5_Msk
#define SYSCFG_EXTICR2_EXTI6_Pos             (8U)
#define SYSCFG_EXTICR2_EXTI6_Msk             (0xFUL << SYSCFG_EXTICR2_EXTI6_Pos)
#define SYSCFG_EXTICR2_EXTI6                 SYSCFG_EXTICR2_EXTI6_Msk
#define SYSCFG_EXTICR2_EXTI7_Pos             (12U)
#define SYSCFG_EXTICR2_EXTI7_Msk             (0xFUL << SYSCFG_EXTICR2_EXTI7_Pos)
#define SYSCFG_EXTICR2_EXTI7                 SYSCFG_EXTICR2_EXTI7_Msk

#define SYSCFG_EXTICR2_EXTI4_PA              0x0000U
#define SYSCFG_EXTICR2_EXTI4_PB              0x0001U
#define SYSCFG_EXTICR2_EXTI4_PC              0x0002U
#define SYSCFG_EXTICR2_EXTI4_PD              0x0003U
#define SYSCFG_EXTICR2_EXTI4_PE              0x0004U
#define SYSCFG_EXTICR2_EXTI4_PH              0x0007U

#define SYSCFG_EXTICR2_EXTI5_PA              0x0000U
#define SYSCFG_EXTICR2_EXTI5_PB              0x0010U
#define SYSCFG_EXTICR2_EXTI5_PC              0x0020U
#define SYSCFG_EXTICR2_EXTI5_PD              0x0030U
#define SYSCFG_EXTICR2_EXTI5_PE              0x0040U
#define SYSCFG_EXTICR2_EXTI5_PH              0x0070U

#define SYSCFG_EXTICR2_EXTI6_PA              0x0000U
#define SYSCFG_EXTICR2_EXTI6_PB              0x0100U
#define SYSCFG_EXTICR2_EXTI6_PC              0x0200U
#define SYSCFG_EXTICR2_EXTI6_PD              0x0300U
#define SYSCFG_EXTICR2_EXTI6_PE              0x0400U
#define SYSCFG_EXTICR2_EXTI6_PH              0x0700U

#define SYSCFG_EXTICR2_EXTI7_PA              0x0000U
#define SYSCFG_EXTICR2_EXTI7_PB              0x1000U
#define SYSCFG_EXTICR2_EXTI7_PC              0x2000U
#define SYSCFG_EXTICR2_EXTI7_PD              0x3000U
#define SYSCFG_EXTICR2_EXTI7_PE              0x4000U
#define SYSCFG_EXTICR2_EXTI7_PH              0x7000U

#define SYSCFG_EXTICR3_EXTI8_Pos             (0U)
#define SYSCFG_EXTICR3_EXTI8_Msk             (0xFUL << SYSCFG_EXTICR3_EXTI8_Pos)
#define SYSCFG_EXTICR3_EXTI8                 SYSCFG_EXTICR3_EXTI8_Msk
#define SYSCFG_EXTICR3_EXTI9_Pos             (4U)
#define SYSCFG_EXTICR3_EXTI9_Msk             (0xFUL << SYSCFG_EXTICR3_EXTI9_Pos)
#define SYSCFG_EXTICR3_EXTI9                 SYSCFG_EXTICR3_EXTI9_Msk
#define SYSCFG_EXTICR3_EXTI10_Pos            (8U)
#define SYSCFG_EXTICR3_EXTI10_Msk            (0xFUL << SYSCFG_EXTICR3_EXTI10_Pos)
#define SYSCFG_EXTICR3_EXTI10                SYSCFG_EXTICR3_EXTI10_Msk
#define SYSCFG_EXTICR3_EXTI11_Pos            (12U)
#define SYSCFG_EXTICR3_EXTI11_Msk            (0xFUL << SYSCFG_EXTICR3_EXTI11_Pos)
#define SYSCFG_EXTICR3_EXTI11                SYSCFG_EXTICR3_EXTI11_Msk

#define SYSCFG_EXTICR3_EXTI8_PA              0x0000U
#define SYSCFG_EXTICR3_EXTI8_PB              0x0001U
#define SYSCFG_EXTICR3_EXTI8_PC              0x0002U
#define SYSCFG_EXTICR3_EXTI8_PD              0x0003U
#define SYSCFG_EXTICR3_EXTI8_PE              0x0004U
#define SYSCFG_EXTICR3_EXTI8_PH              0x0007U

#define SYSCFG_EXTICR3_EXTI9_PA              0x0000U
#define SYSCFG_EXTICR3_EXTI9_PB              0x0010U
#define SYSCFG_EXTICR3_EXTI9_PC              0x0020U
#define SYSCFG_EXTICR3_EXTI9_PD              0x0030U
#define SYSCFG_EXTICR3_EXTI9_PE              0x0040U
#define SYSCFG_EXTICR3_EXTI9_PH              0x0070U

#define SYSCFG_EXTICR3_EXTI10_PA             0x0000U
#define SYSCFG_EXTICR3_EXTI10_PB             0x0100U
#define SYSCFG_EXTICR3_EXTI10_PC             0x0200U
#define SYSCFG_EXTICR3_EXTI10_PD             0x0300U
#define SYSCFG_EXTICR3_EXTI10_PE             0x0400U
#define SYSCFG_EXTICR3_EXTI10_PH             0x0700U

#define SYSCFG_EXTICR3_EXTI11_PA             0x0000U
#define SYSCFG_EXTICR3_EXTI11_PB             0x1000U
#define SYSCFG_EXTICR3_EXTI11_PC             0x2000U
#define SYSCFG_EXTICR3_EXTI11_PD             0x3000U
#define SYSCFG_EXTICR3_EXTI11_PE             0x4000U
#define SYSCFG_EXTICR3_EXTI11_PH             0x7000U

#define SYSCFG_EXTICR4_EXTI12_Pos            (0U)
#define SYSCFG_EXTICR4_EXTI12_Msk            (0xFUL << SYSCFG_EXTICR4_EXTI12_Pos)
#define SYSCFG_EXTICR4_EXTI12                SYSCFG_EXTICR4_EXTI12_Msk
#define SYSCFG_EXTICR4_EXTI13_Pos            (4U)
#define SYSCFG_EXTICR4_EXTI13_Msk            (0xFUL << SYSCFG_EXTICR4_EXTI13_Pos)
#define SYSCFG_EXTICR4_EXTI13                SYSCFG_EXTICR4_EXTI13_Msk
#define SYSCFG_EXTICR4_EXTI14_Pos            (8U)
#define SYSCFG_EXTICR4_EXTI14_Msk            (0xFUL << SYSCFG_EXTICR4_EXTI14_Pos)
#define SYSCFG_EXTICR4_EXTI14                SYSCFG_EXTICR4_EXTI14_Msk
#define SYSCFG_EXTICR4_EXTI15_Pos            (12U)
#define SYSCFG_EXTICR4_EXTI15_Msk            (0xFUL << SYSCFG_EXTICR4_EXTI15_Pos)
#define SYSCFG_EXTICR4_EXTI15                SYSCFG_EXTICR4_EXTI15_Msk

#define SYSCFG_EXTICR4_EXTI12_PA             0x0000U
#define SYSCFG_EXTICR4_EXTI12_PB             0x0001U
#define SYSCFG_EXTICR4_EXTI12_PC             0x0002U
#define SYSCFG_EXTICR4_EXTI12_PD             0x0003U
#define SYSCFG_EXTICR4_EXTI12_PE             0x0004U
#define SYSCFG_EXTICR4_EXTI12_PH             0x0007U

#define SYSCFG_EXTICR4_EXTI13_PA             0x0000U
#define SYSCFG_EXTICR4_EXTI13_PB             0x0010U
#define SYSCFG_EXTICR4_EXTI13_PC             0x0020U
#define SYSCFG_EXTICR4_EXTI13_PD             0x0030U
#define SYSCFG_EXTICR4_EXTI13_PE             0x0040U
#define SYSCFG_EXTICR4_EXTI13_PH             0x0070U

#define SYSCFG_EXTICR4_EXTI14_PA             0x0000U
#define SYSCFG_EXTICR4_EXTI14_PB             0x0100U
#define SYSCFG_EXTICR4_EXTI14_PC             0x0200U
#define SYSCFG_EXTICR4_EXTI14_PD             0x0300U
#define SYSCFG_EXTICR4_EXTI14_PE             0x0400U
#define SYSCFG_EXTICR4_EXTI14_PH             0x0700U

#define SYSCFG_EXTICR4_EXTI15_PA             0x0000U
#define SYSCFG_EXTICR4_EXTI15_PB             0x1000U
#define SYSCFG_EXTICR4_EXTI15_PC             0x2000U
#define SYSCFG_EXTICR4_EXTI15_PD             0x3000U
#define SYSCFG_EXTICR4_EXTI15_PE             0x4000U
#define SYSCFG_EXTICR4_EXTI15_PH             0x7000U

#define SYSCFG_CMPCR_CMP_PD_Pos              (0U)
#define SYSCFG_CMPCR_CMP_PD_Msk              (0x1UL << SYSCFG_CMPCR_CMP_PD_Pos)
#define SYSCFG_CMPCR_CMP_PD                  SYSCFG_CMPCR_CMP_PD_Msk
#define SYSCFG_CMPCR_READY_Pos               (8U)
#define SYSCFG_CMPCR_READY_Msk               (0x1UL << SYSCFG_CMPCR_READY_Pos)
#define SYSCFG_CMPCR_READY                   SYSCFG_CMPCR_READY_Msk

#define TIM_CR1_CEN_Pos           (0U)
#define TIM_CR1_CEN_Msk           (0x1UL << TIM_CR1_CEN_Pos)
#define TIM_CR1_CEN               TIM_CR1_CEN_Msk
#define TIM_CR1_UDIS_Pos          (1U)
#define TIM_CR1_UDIS_Msk          (0x1UL << TIM_CR1_UDIS_Pos)
#define TIM_CR1_UDIS              TIM_CR1_UDIS_Msk
#define TIM_CR1_URS_Pos           (2U)
#define TIM_CR1_URS_Msk           (0x1UL << TIM_CR1_URS_Pos)
#define TIM_CR1_URS               TIM_CR1_URS_Msk
#define TIM_CR1_OPM_Pos           (3U)
#define TIM_CR1_OPM_Msk           (0x1UL << TIM_CR1_OPM_Pos)
#define TIM_CR1_OPM               TIM_CR1_OPM_Msk
#define TIM_CR1_DIR_Pos           (4U)
#define TIM_CR1_DIR_Msk           (0x1UL << TIM_CR1_DIR_Pos)
#define TIM_CR1_DIR               TIM_CR1_DIR_Msk

#define TIM_CR1_CMS_Pos           (5U)
#define TIM_CR1_CMS_Msk           (0x3UL << TIM_CR1_CMS_Pos)
#define TIM_CR1_CMS               TIM_CR1_CMS_Msk
#define TIM_CR1_CMS_0             (0x1UL << TIM_CR1_CMS_Pos)
#define TIM_CR1_CMS_1             (0x2UL << TIM_CR1_CMS_Pos)

#define TIM_CR1_ARPE_Pos          (7U)
#define TIM_CR1_ARPE_Msk          (0x1UL << TIM_CR1_ARPE_Pos)
#define TIM_CR1_ARPE              TIM_CR1_ARPE_Msk

#define TIM_CR1_CKD_Pos           (8U)
#define TIM_CR1_CKD_Msk           (0x3UL << TIM_CR1_CKD_Pos)
#define TIM_CR1_CKD               TIM_CR1_CKD_Msk
#define TIM_CR1_CKD_0             (0x1UL << TIM_CR1_CKD_Pos)
#define TIM_CR1_CKD_1             (0x2UL << TIM_CR1_CKD_Pos)

#define TIM_CR2_CCPC_Pos          (0U)
#define TIM_CR2_CCPC_Msk          (0x1UL << TIM_CR2_CCPC_Pos)
#define TIM_CR2_CCPC              TIM_CR2_CCPC_Msk
#define TIM_CR2_CCUS_Pos          (2U)
#define TIM_CR2_CCUS_Msk          (0x1UL << TIM_CR2_CCUS_Pos)
#define TIM_CR2_CCUS              TIM_CR2_CCUS_Msk
#define TIM_CR2_CCDS_Pos          (3U)
#define TIM_CR2_CCDS_Msk          (0x1UL << TIM_CR2_CCDS_Pos)
#define TIM_CR2_CCDS              TIM_CR2_CCDS_Msk

#define TIM_CR2_MMS_Pos           (4U)
#define TIM_CR2_MMS_Msk           (0x7UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS               TIM_CR2_MMS_Msk
#define TIM_CR2_MMS_0             (0x1UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_1             (0x2UL << TIM_CR2_MMS_Pos)
#define TIM_CR2_MMS_2             (0x4UL << TIM_CR2_MMS_Pos)

#define TIM_CR2_TI1S_Pos          (7U)
#define TIM_CR2_TI1S_Msk          (0x1UL << TIM_CR2_TI1S_Pos)
#define TIM_CR2_TI1S              TIM_CR2_TI1S_Msk
#define TIM_CR2_OIS1_Pos          (8U)
#define TIM_CR2_OIS1_Msk          (0x1UL << TIM_CR2_OIS1_Pos)
#define TIM_CR2_OIS1              TIM_CR2_OIS1_Msk
#define TIM_CR2_OIS1N_Pos         (9U)
#define TIM_CR2_OIS1N_Msk         (0x1UL << TIM_CR2_OIS1N_Pos)
#define TIM_CR2_OIS1N             TIM_CR2_OIS1N_Msk
#define TIM_CR2_OIS2_Pos          (10U)
#define TIM_CR2_OIS2_Msk          (0x1UL << TIM_CR2_OIS2_Pos)
#define TIM_CR2_OIS2              TIM_CR2_OIS2_Msk
#define TIM_CR2_OIS2N_Pos         (11U)
#define TIM_CR2_OIS2N_Msk         (0x1UL << TIM_CR2_OIS2N_Pos)
#define TIM_CR2_OIS2N             TIM_CR2_OIS2N_Msk
#define TIM_CR2_OIS3_Pos          (12U)
#define TIM_CR2_OIS3_Msk          (0x1UL << TIM_CR2_OIS3_Pos)
#define TIM_CR2_OIS3              TIM_CR2_OIS3_Msk
#define TIM_CR2_OIS3N_Pos         (13U)
#define TIM_CR2_OIS3N_Msk         (0x1UL << TIM_CR2_OIS3N_Pos)
#define TIM_CR2_OIS3N             TIM_CR2_OIS3N_Msk
#define TIM_CR2_OIS4_Pos          (14U)
#define TIM_CR2_OIS4_Msk          (0x1UL << TIM_CR2_OIS4_Pos)
#define TIM_CR2_OIS4              TIM_CR2_OIS4_Msk

#define TIM_SMCR_SMS_Pos          (0U)
#define TIM_SMCR_SMS_Msk          (0x7UL << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS              TIM_SMCR_SMS_Msk
#define TIM_SMCR_SMS_0            (0x1UL << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_1            (0x2UL << TIM_SMCR_SMS_Pos)
#define TIM_SMCR_SMS_2            (0x4UL << TIM_SMCR_SMS_Pos)

#define TIM_SMCR_TS_Pos           (4U)
#define TIM_SMCR_TS_Msk           (0x7UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS               TIM_SMCR_TS_Msk
#define TIM_SMCR_TS_0             (0x1UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_1             (0x2UL << TIM_SMCR_TS_Pos)
#define TIM_SMCR_TS_2             (0x4UL << TIM_SMCR_TS_Pos)

#define TIM_SMCR_MSM_Pos          (7U)
#define TIM_SMCR_MSM_Msk          (0x1UL << TIM_SMCR_MSM_Pos)
#define TIM_SMCR_MSM              TIM_SMCR_MSM_Msk

#define TIM_SMCR_ETF_Pos          (8U)
#define TIM_SMCR_ETF_Msk          (0xFUL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF              TIM_SMCR_ETF_Msk
#define TIM_SMCR_ETF_0            (0x1UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_1            (0x2UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_2            (0x4UL << TIM_SMCR_ETF_Pos)
#define TIM_SMCR_ETF_3            (0x8UL << TIM_SMCR_ETF_Pos)

#define TIM_SMCR_ETPS_Pos         (12U)
#define TIM_SMCR_ETPS_Msk         (0x3UL << TIM_SMCR_ETPS_Pos)
#define TIM_SMCR_ETPS             TIM_SMCR_ETPS_Msk
#define TIM_SMCR_ETPS_0           (0x1UL << TIM_SMCR_ETPS_Pos)
#define TIM_SMCR_ETPS_1           (0x2UL << TIM_SMCR_ETPS_Pos)

#define TIM_SMCR_ECE_Pos          (14U)
#define TIM_SMCR_ECE_Msk          (0x1UL << TIM_SMCR_ECE_Pos)
#define TIM_SMCR_ECE              TIM_SMCR_ECE_Msk
#define TIM_SMCR_ETP_Pos          (15U)
#define TIM_SMCR_ETP_Msk          (0x1UL << TIM_SMCR_ETP_Pos)
#define TIM_SMCR_ETP              TIM_SMCR_ETP_Msk

#define TIM_DIER_UIE_Pos          (0U)
#define TIM_DIER_UIE_Msk          (0x1UL << TIM_DIER_UIE_Pos)
#define TIM_DIER_UIE              TIM_DIER_UIE_Msk
#define TIM_DIER_CC1IE_Pos        (1U)
#define TIM_DIER_CC1IE_Msk        (0x1UL << TIM_DIER_CC1IE_Pos)
#define TIM_DIER_CC1IE            TIM_DIER_CC1IE_Msk
#define TIM_DIER_CC2IE_Pos        (2U)
#define TIM_DIER_CC2IE_Msk        (0x1UL << TIM_DIER_CC2IE_Pos)
#define TIM_DIER_CC2IE            TIM_DIER_CC2IE_Msk
#define TIM_DIER_CC3IE_Pos        (3U)
#define TIM_DIER_CC3IE_Msk        (0x1UL << TIM_DIER_CC3IE_Pos)
#define TIM_DIER_CC3IE            TIM_DIER_CC3IE_Msk
#define TIM_DIER_CC4IE_Pos        (4U)
#define TIM_DIER_CC4IE_Msk        (0x1UL << TIM_DIER_CC4IE_Pos)
#define TIM_DIER_CC4IE            TIM_DIER_CC4IE_Msk
#define TIM_DIER_COMIE_Pos        (5U)
#define TIM_DIER_COMIE_Msk        (0x1UL << TIM_DIER_COMIE_Pos)
#define TIM_DIER_COMIE            TIM_DIER_COMIE_Msk
#define TIM_DIER_TIE_Pos          (6U)
#define TIM_DIER_TIE_Msk          (0x1UL << TIM_DIER_TIE_Pos)
#define TIM_DIER_TIE              TIM_DIER_TIE_Msk
#define TIM_DIER_BIE_Pos          (7U)
#define TIM_DIER_BIE_Msk          (0x1UL << TIM_DIER_BIE_Pos)
#define TIM_DIER_BIE              TIM_DIER_BIE_Msk
#define TIM_DIER_UDE_Pos          (8U)
#define TIM_DIER_UDE_Msk          (0x1UL << TIM_DIER_UDE_Pos)
#define TIM_DIER_UDE              TIM_DIER_UDE_Msk
#define TIM_DIER_CC1DE_Pos        (9U)
#define TIM_DIER_CC1DE_Msk        (0x1UL << TIM_DIER_CC1DE_Pos)
#define TIM_DIER_CC1DE            TIM_DIER_CC1DE_Msk
#define TIM_DIER_CC2DE_Pos        (10U)
#define TIM_DIER_CC2DE_Msk        (0x1UL << TIM_DIER_CC2DE_Pos)
#define TIM_DIER_CC2DE            TIM_DIER_CC2DE_Msk
#define TIM_DIER_CC3DE_Pos        (11U)
#define TIM_DIER_CC3DE_Msk        (0x1UL << TIM_DIER_CC3DE_Pos)
#define TIM_DIER_CC3DE            TIM_DIER_CC3DE_Msk
#define TIM_DIER_CC4DE_Pos        (12U)
#define TIM_DIER_CC4DE_Msk        (0x1UL << TIM_DIER_CC4DE_Pos)
#define TIM_DIER_CC4DE            TIM_DIER_CC4DE_Msk
#define TIM_DIER_COMDE_Pos        (13U)
#define TIM_DIER_COMDE_Msk        (0x1UL << TIM_DIER_COMDE_Pos)
#define TIM_DIER_COMDE            TIM_DIER_COMDE_Msk
#define TIM_DIER_TDE_Pos          (14U)
#define TIM_DIER_TDE_Msk          (0x1UL << TIM_DIER_TDE_Pos)
#define TIM_DIER_TDE              TIM_DIER_TDE_Msk

#define TIM_SR_UIF_Pos            (0U)
#define TIM_SR_UIF_Msk            (0x1UL << TIM_SR_UIF_Pos)
#define TIM_SR_UIF                TIM_SR_UIF_Msk
#define TIM_SR_CC1IF_Pos          (1U)
#define TIM_SR_CC1IF_Msk          (0x1UL << TIM_SR_CC1IF_Pos)
#define TIM_SR_CC1IF              TIM_SR_CC1IF_Msk
#define TIM_SR_CC2IF_Pos          (2U)
#define TIM_SR_CC2IF_Msk          (0x1UL << TIM_SR_CC2IF_Pos)
#define TIM_SR_CC2IF              TIM_SR_CC2IF_Msk
#define TIM_SR_CC3IF_Pos          (3U)
#define TIM_SR_CC3IF_Msk          (0x1UL << TIM_SR_CC3IF_Pos)
#define TIM_SR_CC3IF              TIM_SR_CC3IF_Msk
#define TIM_SR_CC4IF_Pos          (4U)
#define TIM_SR_CC4IF_Msk          (0x1UL << TIM_SR_CC4IF_Pos)
#define TIM_SR_CC4IF              TIM_SR_CC4IF_Msk
#define TIM_SR_COMIF_Pos          (5U)
#define TIM_SR_COMIF_Msk          (0x1UL << TIM_SR_COMIF_Pos)
#define TIM_SR_COMIF              TIM_SR_COMIF_Msk
#define TIM_SR_TIF_Pos            (6U)
#define TIM_SR_TIF_Msk            (0x1UL << TIM_SR_TIF_Pos)
#define TIM_SR_TIF                TIM_SR_TIF_Msk
#define TIM_SR_BIF_Pos            (7U)
#define TIM_SR_BIF_Msk            (0x1UL << TIM_SR_BIF_Pos)
#define TIM_SR_BIF                TIM_SR_BIF_Msk
#define TIM_SR_CC1OF_Pos          (9U)
#define TIM_SR_CC1OF_Msk          (0x1UL << TIM_SR_CC1OF_Pos)
#define TIM_SR_CC1OF              TIM_SR_CC1OF_Msk
#define TIM_SR_CC2OF_Pos          (10U)
#define TIM_SR_CC2OF_Msk          (0x1UL << TIM_SR_CC2OF_Pos)
#define TIM_SR_CC2OF              TIM_SR_CC2OF_Msk
#define TIM_SR_CC3OF_Pos          (11U)
#define TIM_SR_CC3OF_Msk          (0x1UL << TIM_SR_CC3OF_Pos)
#define TIM_SR_CC3OF              TIM_SR_CC3OF_Msk
#define TIM_SR_CC4OF_Pos          (12U)
#define TIM_SR_CC4OF_Msk          (0x1UL << TIM_SR_CC4OF_Pos)
#define TIM_SR_CC4OF              TIM_SR_CC4OF_Msk

#define TIM_EGR_UG_Pos            (0U)
#define TIM_EGR_UG_Msk            (0x1UL << TIM_EGR_UG_Pos)
#define TIM_EGR_UG                TIM_EGR_UG_Msk
#define TIM_EGR_CC1G_Pos          (1U)
#define TIM_EGR_CC1G_Msk          (0x1UL << TIM_EGR_CC1G_Pos)
#define TIM_EGR_CC1G              TIM_EGR_CC1G_Msk
#define TIM_EGR_CC2G_Pos          (2U)
#define TIM_EGR_CC2G_Msk          (0x1UL << TIM_EGR_CC2G_Pos)
#define TIM_EGR_CC2G              TIM_EGR_CC2G_Msk
#define TIM_EGR_CC3G_Pos          (3U)
#define TIM_EGR_CC3G_Msk          (0x1UL << TIM_EGR_CC3G_Pos)
#define TIM_EGR_CC3G              TIM_EGR_CC3G_Msk
#define TIM_EGR_CC4G_Pos          (4U)
#define TIM_EGR_CC4G_Msk          (0x1UL << TIM_EGR_CC4G_Pos)
#define TIM_EGR_CC4G              TIM_EGR_CC4G_Msk
#define TIM_EGR_COMG_Pos          (5U)
#define TIM_EGR_COMG_Msk          (0x1UL << TIM_EGR_COMG_Pos)
#define TIM_EGR_COMG              TIM_EGR_COMG_Msk
#define TIM_EGR_TG_Pos            (6U)
#define TIM_EGR_TG_Msk            (0x1UL << TIM_EGR_TG_Pos)
#define TIM_EGR_TG                TIM_EGR_TG_Msk
#define TIM_EGR_BG_Pos            (7U)
#define TIM_EGR_BG_Msk            (0x1UL << TIM_EGR_BG_Pos)
#define TIM_EGR_BG                TIM_EGR_BG_Msk

#define TIM_CCMR1_CC1S_Pos        (0U)
#define TIM_CCMR1_CC1S_Msk        (0x3UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S            TIM_CCMR1_CC1S_Msk
#define TIM_CCMR1_CC1S_0          (0x1UL << TIM_CCMR1_CC1S_Pos)
#define TIM_CCMR1_CC1S_1          (0x2UL << TIM_CCMR1_CC1S_Pos)

#define TIM_CCMR1_OC1FE_Pos       (2U)
#define TIM_CCMR1_OC1FE_Msk       (0x1UL << TIM_CCMR1_OC1FE_Pos)
#define TIM_CCMR1_OC1FE           TIM_CCMR1_OC1FE_Msk
#define TIM_CCMR1_OC1PE_Pos       (3U)
#define TIM_CCMR1_OC1PE_Msk       (0x1UL << TIM_CCMR1_OC1PE_Pos)
#define TIM_CCMR1_OC1PE           TIM_CCMR1_OC1PE_Msk

#define TIM_CCMR1_OC1M_Pos        (4U)
#define TIM_CCMR1_OC1M_Msk        (0x7UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M            TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1M_0          (0x1UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M_1          (0x2UL << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M_2          (0x4UL << TIM_CCMR1_OC1M_Pos)

#define TIM_CCMR1_OC1CE_Pos       (7U)
#define TIM_CCMR1_OC1CE_Msk       (0x1UL << TIM_CCMR1_OC1CE_Pos)
#define TIM_CCMR1_OC1CE           TIM_CCMR1_OC1CE_Msk

#define TIM_CCMR1_CC2S_Pos        (8U)
#define TIM_CCMR1_CC2S_Msk        (0x3UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S            TIM_CCMR1_CC2S_Msk
#define TIM_CCMR1_CC2S_0          (0x1UL << TIM_CCMR1_CC2S_Pos)
#define TIM_CCMR1_CC2S_1          (0x2UL << TIM_CCMR1_CC2S_Pos)

#define TIM_CCMR1_OC2FE_Pos       (10U)
#define TIM_CCMR1_OC2FE_Msk       (0x1UL << TIM_CCMR1_OC2FE_Pos)
#define TIM_CCMR1_OC2FE           TIM_CCMR1_OC2FE_Msk
#define TIM_CCMR1_OC2PE_Pos       (11U)
#define TIM_CCMR1_OC2PE_Msk       (0x1UL << TIM_CCMR1_OC2PE_Pos)
#define TIM_CCMR1_OC2PE           TIM_CCMR1_OC2PE_Msk

#define TIM_CCMR1_OC2M_Pos        (12U)
#define TIM_CCMR1_OC2M_Msk        (0x7UL << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2M            TIM_CCMR1_OC2M_Msk
#define TIM_CCMR1_OC2M_0          (0x1UL << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2M_1          (0x2UL << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2M_2          (0x4UL << TIM_CCMR1_OC2M_Pos)

#define TIM_CCMR1_OC2CE_Pos       (15U)
#define TIM_CCMR1_OC2CE_Msk       (0x1UL << TIM_CCMR1_OC2CE_Pos)
#define TIM_CCMR1_OC2CE           TIM_CCMR1_OC2CE_Msk

#define TIM_CCMR1_IC1PSC_Pos      (2U)
#define TIM_CCMR1_IC1PSC_Msk      (0x3UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_CCMR1_IC1PSC          TIM_CCMR1_IC1PSC_Msk
#define TIM_CCMR1_IC1PSC_0        (0x1UL << TIM_CCMR1_IC1PSC_Pos)
#define TIM_CCMR1_IC1PSC_1        (0x2UL << TIM_CCMR1_IC1PSC_Pos)

#define TIM_CCMR1_IC1F_Pos        (4U)
#define TIM_CCMR1_IC1F_Msk        (0xFUL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F            TIM_CCMR1_IC1F_Msk
#define TIM_CCMR1_IC1F_0          (0x1UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_1          (0x2UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_2          (0x4UL << TIM_CCMR1_IC1F_Pos)
#define TIM_CCMR1_IC1F_3          (0x8UL << TIM_CCMR1_IC1F_Pos)

#define TIM_CCMR1_IC2PSC_Pos      (10U)
#define TIM_CCMR1_IC2PSC_Msk      (0x3UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_CCMR1_IC2PSC          TIM_CCMR1_IC2PSC_Msk
#define TIM_CCMR1_IC2PSC_0        (0x1UL << TIM_CCMR1_IC2PSC_Pos)
#define TIM_CCMR1_IC2PSC_1        (0x2UL << TIM_CCMR1_IC2PSC_Pos)

#define TIM_CCMR1_IC2F_Pos        (12U)
#define TIM_CCMR1_IC2F_Msk        (0xFUL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F            TIM_CCMR1_IC2F_Msk
#define TIM_CCMR1_IC2F_0          (0x1UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_1          (0x2UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_2          (0x4UL << TIM_CCMR1_IC2F_Pos)
#define TIM_CCMR1_IC2F_3          (0x8UL << TIM_CCMR1_IC2F_Pos)

#define TIM_CCMR2_CC3S_Pos        (0U)
#define TIM_CCMR2_CC3S_Msk        (0x3UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC3S            TIM_CCMR2_CC3S_Msk
#define TIM_CCMR2_CC3S_0          (0x1UL << TIM_CCMR2_CC3S_Pos)
#define TIM_CCMR2_CC3S_1          (0x2UL << TIM_CCMR2_CC3S_Pos)

#define TIM_CCMR2_OC3FE_Pos       (2U)
#define TIM_CCMR2_OC3FE_Msk       (0x1UL << TIM_CCMR2_OC3FE_Pos)
#define TIM_CCMR2_OC3FE           TIM_CCMR2_OC3FE_Msk
#define TIM_CCMR2_OC3PE_Pos       (3U)
#define TIM_CCMR2_OC3PE_Msk       (0x1UL << TIM_CCMR2_OC3PE_Pos)
#define TIM_CCMR2_OC3PE           TIM_CCMR2_OC3PE_Msk

#define TIM_CCMR2_OC3M_Pos        (4U)
#define TIM_CCMR2_OC3M_Msk        (0x7UL << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3M            TIM_CCMR2_OC3M_Msk
#define TIM_CCMR2_OC3M_0          (0x1UL << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3M_1          (0x2UL << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3M_2          (0x4UL << TIM_CCMR2_OC3M_Pos)

#define TIM_CCMR2_OC3CE_Pos       (7U)
#define TIM_CCMR2_OC3CE_Msk       (0x1UL << TIM_CCMR2_OC3CE_Pos)
#define TIM_CCMR2_OC3CE           TIM_CCMR2_OC3CE_Msk

#define TIM_CCMR2_CC4S_Pos        (8U)
#define TIM_CCMR2_CC4S_Msk        (0x3UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR2_CC4S            TIM_CCMR2_CC4S_Msk
#define TIM_CCMR2_CC4S_0          (0x1UL << TIM_CCMR2_CC4S_Pos)
#define TIM_CCMR2_CC4S_1          (0x2UL << TIM_CCMR2_CC4S_Pos)

#define TIM_CCMR2_OC4FE_Pos       (10U)
#define TIM_CCMR2_OC4FE_Msk       (0x1UL << TIM_CCMR2_OC4FE_Pos)
#define TIM_CCMR2_OC4FE           TIM_CCMR2_OC4FE_Msk
#define TIM_CCMR2_OC4PE_Pos       (11U)
#define TIM_CCMR2_OC4PE_Msk       (0x1UL << TIM_CCMR2_OC4PE_Pos)
#define TIM_CCMR2_OC4PE           TIM_CCMR2_OC4PE_Msk

#define TIM_CCMR2_OC4M_Pos        (12U)
#define TIM_CCMR2_OC4M_Msk        (0x7UL << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4M            TIM_CCMR2_OC4M_Msk
#define TIM_CCMR2_OC4M_0          (0x1UL << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4M_1          (0x2UL << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4M_2          (0x4UL << TIM_CCMR2_OC4M_Pos)

#define TIM_CCMR2_OC4CE_Pos       (15U)
#define TIM_CCMR2_OC4CE_Msk       (0x1UL << TIM_CCMR2_OC4CE_Pos)
#define TIM_CCMR2_OC4CE           TIM_CCMR2_OC4CE_Msk

#define TIM_CCMR2_IC3PSC_Pos      (2U)
#define TIM_CCMR2_IC3PSC_Msk      (0x3UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_CCMR2_IC3PSC          TIM_CCMR2_IC3PSC_Msk
#define TIM_CCMR2_IC3PSC_0        (0x1UL << TIM_CCMR2_IC3PSC_Pos)
#define TIM_CCMR2_IC3PSC_1        (0x2UL << TIM_CCMR2_IC3PSC_Pos)

#define TIM_CCMR2_IC3F_Pos        (4U)
#define TIM_CCMR2_IC3F_Msk        (0xFUL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F            TIM_CCMR2_IC3F_Msk
#define TIM_CCMR2_IC3F_0          (0x1UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_1          (0x2UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_2          (0x4UL << TIM_CCMR2_IC3F_Pos)
#define TIM_CCMR2_IC3F_3          (0x8UL << TIM_CCMR2_IC3F_Pos)

#define TIM_CCMR2_IC4PSC_Pos      (10U)
#define TIM_CCMR2_IC4PSC_Msk      (0x3UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_CCMR2_IC4PSC          TIM_CCMR2_IC4PSC_Msk
#define TIM_CCMR2_IC4PSC_0        (0x1UL << TIM_CCMR2_IC4PSC_Pos)
#define TIM_CCMR2_IC4PSC_1        (0x2UL << TIM_CCMR2_IC4PSC_Pos)

#define TIM_CCMR2_IC4F_Pos        (12U)
#define TIM_CCMR2_IC4F_Msk        (0xFUL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F            TIM_CCMR2_IC4F_Msk
#define TIM_CCMR2_IC4F_0          (0x1UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_1          (0x2UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_2          (0x4UL << TIM_CCMR2_IC4F_Pos)
#define TIM_CCMR2_IC4F_3          (0x8UL << TIM_CCMR2_IC4F_Pos)

#define TIM_CCER_CC1E_Pos         (0U)
#define TIM_CCER_CC1E_Msk         (0x1UL << TIM_CCER_CC1E_Pos)
#define TIM_CCER_CC1E             TIM_CCER_CC1E_Msk
#define TIM_CCER_CC1P_Pos         (1U)
#define TIM_CCER_CC1P_Msk         (0x1UL << TIM_CCER_CC1P_Pos)
#define TIM_CCER_CC1P             TIM_CCER_CC1P_Msk
#define TIM_CCER_CC1NE_Pos        (2U)
#define TIM_CCER_CC1NE_Msk        (0x1UL << TIM_CCER_CC1NE_Pos)
#define TIM_CCER_CC1NE            TIM_CCER_CC1NE_Msk
#define TIM_CCER_CC1NP_Pos        (3U)
#define TIM_CCER_CC1NP_Msk        (0x1UL << TIM_CCER_CC1NP_Pos)
#define TIM_CCER_CC1NP            TIM_CCER_CC1NP_Msk
#define TIM_CCER_CC2E_Pos         (4U)
#define TIM_CCER_CC2E_Msk         (0x1UL << TIM_CCER_CC2E_Pos)
#define TIM_CCER_CC2E             TIM_CCER_CC2E_Msk
#define TIM_CCER_CC2P_Pos         (5U)
#define TIM_CCER_CC2P_Msk         (0x1UL << TIM_CCER_CC2P_Pos)
#define TIM_CCER_CC2P             TIM_CCER_CC2P_Msk
#define TIM_CCER_CC2NE_Pos        (6U)
#define TIM_CCER_CC2NE_Msk        (0x1UL << TIM_CCER_CC2NE_Pos)
#define TIM_CCER_CC2NE            TIM_CCER_CC2NE_Msk
#define TIM_CCER_CC2NP_Pos        (7U)
#define TIM_CCER_CC2NP_Msk        (0x1UL << TIM_CCER_CC2NP_Pos)
#define TIM_CCER_CC2NP            TIM_CCER_CC2NP_Msk
#define TIM_CCER_CC3E_Pos         (8U)
#define TIM_CCER_CC3E_Msk         (0x1UL << TIM_CCER_CC3E_Pos)
#define TIM_CCER_CC3E             TIM_CCER_CC3E_Msk
#define TIM_CCER_CC3P_Pos         (9U)
#define TIM_CCER_CC3P_Msk         (0x1UL << TIM_CCER_CC3P_Pos)
#define TIM_CCER_CC3P             TIM_CCER_CC3P_Msk
#define TIM_CCER_CC3NE_Pos        (10U)
#define TIM_CCER_CC3NE_Msk        (0x1UL << TIM_CCER_CC3NE_Pos)
#define TIM_CCER_CC3NE            TIM_CCER_CC3NE_Msk
#define TIM_CCER_CC3NP_Pos        (11U)
#define TIM_CCER_CC3NP_Msk        (0x1UL << TIM_CCER_CC3NP_Pos)
#define TIM_CCER_CC3NP            TIM_CCER_CC3NP_Msk
#define TIM_CCER_CC4E_Pos         (12U)
#define TIM_CCER_CC4E_Msk         (0x1UL << TIM_CCER_CC4E_Pos)
#define TIM_CCER_CC4E             TIM_CCER_CC4E_Msk
#define TIM_CCER_CC4P_Pos         (13U)
#define TIM_CCER_CC4P_Msk         (0x1UL << TIM_CCER_CC4P_Pos)
#define TIM_CCER_CC4P             TIM_CCER_CC4P_Msk
#define TIM_CCER_CC4NP_Pos        (15U)
#define TIM_CCER_CC4NP_Msk        (0x1UL << TIM_CCER_CC4NP_Pos)
#define TIM_CCER_CC4NP            TIM_CCER_CC4NP_Msk

#define TIM_CNT_CNT_Pos           (0U)
#define TIM_CNT_CNT_Msk           (0xFFFFFFFFUL << TIM_CNT_CNT_Pos)
#define TIM_CNT_CNT               TIM_CNT_CNT_Msk

#define TIM_PSC_PSC_Pos           (0U)
#define TIM_PSC_PSC_Msk           (0xFFFFUL << TIM_PSC_PSC_Pos)
#define TIM_PSC_PSC               TIM_PSC_PSC_Msk

#define TIM_ARR_ARR_Pos           (0U)
#define TIM_ARR_ARR_Msk           (0xFFFFFFFFUL << TIM_ARR_ARR_Pos)
#define TIM_ARR_ARR               TIM_ARR_ARR_Msk

#define TIM_RCR_REP_Pos           (0U)
#define TIM_RCR_REP_Msk           (0xFFUL << TIM_RCR_REP_Pos)
#define TIM_RCR_REP               TIM_RCR_REP_Msk

#define TIM_CCR1_CCR1_Pos         (0U)
#define TIM_CCR1_CCR1_Msk         (0xFFFFUL << TIM_CCR1_CCR1_Pos)
#define TIM_CCR1_CCR1             TIM_CCR1_CCR1_Msk

#define TIM_CCR2_CCR2_Pos         (0U)
#define TIM_CCR2_CCR2_Msk         (0xFFFFUL << TIM_CCR2_CCR2_Pos)
#define TIM_CCR2_CCR2             TIM_CCR2_CCR2_Msk

#define TIM_CCR3_CCR3_Pos         (0U)
#define TIM_CCR3_CCR3_Msk         (0xFFFFUL << TIM_CCR3_CCR3_Pos)
#define TIM_CCR3_CCR3             TIM_CCR3_CCR3_Msk

#define TIM_CCR4_CCR4_Pos         (0U)
#define TIM_CCR4_CCR4_Msk         (0xFFFFUL << TIM_CCR4_CCR4_Pos)
#define TIM_CCR4_CCR4             TIM_CCR4_CCR4_Msk

#define TIM_BDTR_DTG_Pos          (0U)
#define TIM_BDTR_DTG_Msk          (0xFFUL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG              TIM_BDTR_DTG_Msk
#define TIM_BDTR_DTG_0            (0x01UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_1            (0x02UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_2            (0x04UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_3            (0x08UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_4            (0x10UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_5            (0x20UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_6            (0x40UL << TIM_BDTR_DTG_Pos)
#define TIM_BDTR_DTG_7            (0x80UL << TIM_BDTR_DTG_Pos)

#define TIM_BDTR_LOCK_Pos         (8U)
#define TIM_BDTR_LOCK_Msk         (0x3UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_LOCK             TIM_BDTR_LOCK_Msk
#define TIM_BDTR_LOCK_0           (0x1UL << TIM_BDTR_LOCK_Pos)
#define TIM_BDTR_LOCK_1           (0x2UL << TIM_BDTR_LOCK_Pos)

#define TIM_BDTR_OSSI_Pos         (10U)
#define TIM_BDTR_OSSI_Msk         (0x1UL << TIM_BDTR_OSSI_Pos)
#define TIM_BDTR_OSSI             TIM_BDTR_OSSI_Msk
#define TIM_BDTR_OSSR_Pos         (11U)
#define TIM_BDTR_OSSR_Msk         (0x1UL << TIM_BDTR_OSSR_Pos)
#define TIM_BDTR_OSSR             TIM_BDTR_OSSR_Msk
#define TIM_BDTR_BKE_Pos          (12U)
#define TIM_BDTR_BKE_Msk          (0x1UL << TIM_BDTR_BKE_Pos)
#define TIM_BDTR_BKE              TIM_BDTR_BKE_Msk
#define TIM_BDTR_BKP_Pos          (13U)
#define TIM_BDTR_BKP_Msk          (0x1UL << TIM_BDTR_BKP_Pos)
#define TIM_BDTR_BKP              TIM_BDTR_BKP_Msk
#define TIM_BDTR_AOE_Pos          (14U)
#define TIM_BDTR_AOE_Msk          (0x1UL << TIM_BDTR_AOE_Pos)
#define TIM_BDTR_AOE              TIM_BDTR_AOE_Msk
#define TIM_BDTR_MOE_Pos          (15U)
#define TIM_BDTR_MOE_Msk          (0x1UL << TIM_BDTR_MOE_Pos)
#define TIM_BDTR_MOE              TIM_BDTR_MOE_Msk

#define TIM_DCR_DBA_Pos           (0U)
#define TIM_DCR_DBA_Msk           (0x1FUL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA               TIM_DCR_DBA_Msk
#define TIM_DCR_DBA_0             (0x01UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_1             (0x02UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_2             (0x04UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_3             (0x08UL << TIM_DCR_DBA_Pos)
#define TIM_DCR_DBA_4             (0x10UL << TIM_DCR_DBA_Pos)

#define TIM_DCR_DBL_Pos           (8U)
#define TIM_DCR_DBL_Msk           (0x1FUL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL               TIM_DCR_DBL_Msk
#define TIM_DCR_DBL_0             (0x01UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_1             (0x02UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_2             (0x04UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_3             (0x08UL << TIM_DCR_DBL_Pos)
#define TIM_DCR_DBL_4             (0x10UL << TIM_DCR_DBL_Pos)

#define TIM_DMAR_DMAB_Pos         (0U)
#define TIM_DMAR_DMAB_Msk         (0xFFFFUL << TIM_DMAR_DMAB_Pos)
#define TIM_DMAR_DMAB             TIM_DMAR_DMAB_Msk

#define TIM_OR_TI1_RMP_Pos        (0U)
#define TIM_OR_TI1_RMP_Msk        (0x3UL << TIM_OR_TI1_RMP_Pos)
#define TIM_OR_TI1_RMP            TIM_OR_TI1_RMP_Msk
#define TIM_OR_TI1_RMP_0          (0x1UL << TIM_OR_TI1_RMP_Pos)
#define TIM_OR_TI1_RMP_1          (0x2UL << TIM_OR_TI1_RMP_Pos)

#define TIM_OR_TI4_RMP_Pos        (6U)
#define TIM_OR_TI4_RMP_Msk        (0x3UL << TIM_OR_TI4_RMP_Pos)
#define TIM_OR_TI4_RMP            TIM_OR_TI4_RMP_Msk
#define TIM_OR_TI4_RMP_0          (0x1UL << TIM_OR_TI4_RMP_Pos)
#define TIM_OR_TI4_RMP_1          (0x2UL << TIM_OR_TI4_RMP_Pos)
#define TIM_OR_ITR1_RMP_Pos       (10U)
#define TIM_OR_ITR1_RMP_Msk       (0x3UL << TIM_OR_ITR1_RMP_Pos)
#define TIM_OR_ITR1_RMP           TIM_OR_ITR1_RMP_Msk
#define TIM_OR_ITR1_RMP_0         (0x1UL << TIM_OR_ITR1_RMP_Pos)
#define TIM_OR_ITR1_RMP_1         (0x2UL << TIM_OR_ITR1_RMP_Pos)

#define USART_SR_PE_Pos               (0U)
#define USART_SR_PE_Msk               (0x1UL << USART_SR_PE_Pos)
#define USART_SR_PE                   USART_SR_PE_Msk
#define USART_SR_FE_Pos               (1U)
#define USART_SR_FE_Msk               (0x1UL << USART_SR_FE_Pos)
#define USART_SR_FE                   USART_SR_FE_Msk
#define USART_SR_NE_Pos               (2U)
#define USART_SR_NE_Msk               (0x1UL << USART_SR_NE_Pos)
#define USART_SR_NE                   USART_SR_NE_Msk
#define USART_SR_ORE_Pos              (3U)
#define USART_SR_ORE_Msk              (0x1UL << USART_SR_ORE_Pos)
#define USART_SR_ORE                  USART_SR_ORE_Msk
#define USART_SR_IDLE_Pos             (4U)
#define USART_SR_IDLE_Msk             (0x1UL << USART_SR_IDLE_Pos)
#define USART_SR_IDLE                 USART_SR_IDLE_Msk
#define USART_SR_RXNE_Pos             (5U)
#define USART_SR_RXNE_Msk             (0x1UL << USART_SR_RXNE_Pos)
#define USART_SR_RXNE                 USART_SR_RXNE_Msk
#define USART_SR_TC_Pos               (6U)
#define USART_SR_TC_Msk               (0x1UL << USART_SR_TC_Pos)
#define USART_SR_TC                   USART_SR_TC_Msk
#define USART_SR_TXE_Pos              (7U)
#define USART_SR_TXE_Msk              (0x1UL << USART_SR_TXE_Pos)
#define USART_SR_TXE                  USART_SR_TXE_Msk
#define USART_SR_LBD_Pos              (8U)
#define USART_SR_LBD_Msk              (0x1UL << USART_SR_LBD_Pos)
#define USART_SR_LBD                  USART_SR_LBD_Msk
#define USART_SR_CTS_Pos              (9U)
#define USART_SR_CTS_Msk              (0x1UL << USART_SR_CTS_Pos)
#define USART_SR_CTS                  USART_SR_CTS_Msk

#define USART_DR_DR_Pos               (0U)
#define USART_DR_DR_Msk               (0x1FFUL << USART_DR_DR_Pos)
#define USART_DR_DR                   USART_DR_DR_Msk

#define USART_BRR_DIV_Fraction_Pos    (0U)
#define USART_BRR_DIV_Fraction_Msk    (0xFUL << USART_BRR_DIV_Fraction_Pos)
#define USART_BRR_DIV_Fraction        USART_BRR_DIV_Fraction_Msk
#define USART_BRR_DIV_Mantissa_Pos    (4U)
#define USART_BRR_DIV_Mantissa_Msk    (0xFFFUL << USART_BRR_DIV_Mantissa_Pos)
#define USART_BRR_DIV_Mantissa        USART_BRR_DIV_Mantissa_Msk

#define USART_CR1_SBK_Pos             (0U)
#define USART_CR1_SBK_Msk             (0x1UL << USART_CR1_SBK_Pos)
#define USART_CR1_SBK                 USART_CR1_SBK_Msk
#define USART_CR1_RWU_Pos             (1U)
#define USART_CR1_RWU_Msk             (0x1UL << USART_CR1_RWU_Pos)
#define USART_CR1_RWU                 USART_CR1_RWU_Msk
#define USART_CR1_RE_Pos              (2U)
#define USART_CR1_RE_Msk              (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_RE                  USART_CR1_RE_Msk
#define USART_CR1_TE_Pos              (3U)
#define USART_CR1_TE_Msk              (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_TE                  USART_CR1_TE_Msk
#define USART_CR1_IDLEIE_Pos          (4U)
#define USART_CR1_IDLEIE_Msk          (0x1UL << USART_CR1_IDLEIE_Pos)
#define USART_CR1_IDLEIE              USART_CR1_IDLEIE_Msk
#define USART_CR1_RXNEIE_Pos          (5U)
#define USART_CR1_RXNEIE_Msk          (0x1UL << USART_CR1_RXNEIE_Pos)
#define USART_CR1_RXNEIE              USART_CR1_RXNEIE_Msk
#define USART_CR1_TCIE_Pos            (6U)
#define USART_CR1_TCIE_Msk            (0x1UL << USART_CR1_TCIE_Pos)
#define USART_CR1_TCIE                USART_CR1_TCIE_Msk
#define USART_CR1_TXEIE_Pos           (7U)
#define USART_CR1_TXEIE_Msk           (0x1UL << USART_CR1_TXEIE_Pos)
#define USART_CR1_TXEIE               USART_CR1_TXEIE_Msk
#define USART_CR1_PEIE_Pos            (8U)
#define USART_CR1_PEIE_Msk            (0x1UL << USART_CR1_PEIE_Pos)
#define USART_CR1_PEIE                USART_CR1_PEIE_Msk
#define USART_CR1_PS_Pos              (9U)
#define USART_CR1_PS_Msk              (0x1UL << USART_CR1_PS_Pos)
#define USART_CR1_PS                  USART_CR1_PS_Msk
#define USART_CR1_PCE_Pos             (10U)
#define USART_CR1_PCE_Msk             (0x1UL << USART_CR1_PCE_Pos)
#define USART_CR1_PCE                 USART_CR1_PCE_Msk
#define USART_CR1_WAKE_Pos            (11U)
#define USART_CR1_WAKE_Msk            (0x1UL << USART_CR1_WAKE_Pos)
#define USART_CR1_WAKE                USART_CR1_WAKE_Msk
#define USART_CR1_M_Pos               (12U)
#define USART_CR1_M_Msk               (0x1UL << USART_CR1_M_Pos)
#define USART_CR1_M                   USART_CR1_M_Msk
#define USART_CR1_UE_Pos              (13U)
#define USART_CR1_UE_Msk              (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_UE                  USART_CR1_UE_Msk
#define USART_CR1_OVER8_Pos           (15U)
#define USART_CR1_OVER8_Msk           (0x1UL << USART_CR1_OVER8_Pos)
#define USART_CR1_OVER8               USART_CR1_OVER8_Msk

#define USART_CR2_ADD_Pos             (0U)
#define USART_CR2_ADD_Msk             (0xFUL << USART_CR2_ADD_Pos)
#define USART_CR2_ADD                 USART_CR2_ADD_Msk
#define USART_CR2_LBDL_Pos            (5U)
#define USART_CR2_LBDL_Msk            (0x1UL << USART_CR2_LBDL_Pos)
#define USART_CR2_LBDL                USART_CR2_LBDL_Msk
#define USART_CR2_LBDIE_Pos           (6U)
#define USART_CR2_LBDIE_Msk           (0x1UL << USART_CR2_LBDIE_Pos)
#define USART_CR2_LBDIE               USART_CR2_LBDIE_Msk
#define USART_CR2_LBCL_Pos            (8U)
#define USART_CR2_LBCL_Msk            (0x1UL << USART_CR2_LBCL_Pos)
#define USART_CR2_LBCL                USART_CR2_LBCL_Msk
#define USART_CR2_CPHA_Pos            (9U)
#define USART_CR2_CPHA_Msk            (0x1UL << USART_CR2_CPHA_Pos)
#define USART_CR2_CPHA                USART_CR2_CPHA_Msk
#define USART_CR2_CPOL_Pos            (10U)
#define USART_CR2_CPOL_Msk            (0x1UL << USART_CR2_CPOL_Pos)
#define USART_CR2_CPOL                USART_CR2_CPOL_Msk
#define USART_CR2_CLKEN_Pos           (11U)
#define USART_CR2_CLKEN_Msk           (0x1UL << USART_CR2_CLKEN_Pos)
#define USART_CR2_CLKEN               USART_CR2_CLKEN_Msk

#define USART_CR2_STOP_Pos            (12U)
#define USART_CR2_STOP_Msk            (0x3UL << USART_CR2_STOP_Pos)
#define USART_CR2_STOP                USART_CR2_STOP_Msk
#define USART_CR2_STOP_0              (0x1UL << USART_CR2_STOP_Pos)
#define USART_CR2_STOP_1              (0x2UL << USART_CR2_STOP_Pos)

#define USART_CR2_LINEN_Pos           (14U)
#define USART_CR2_LINEN_Msk           (0x1UL << USART_CR2_LINEN_Pos)
#define USART_CR2_LINEN               USART_CR2_LINEN_Msk

#define USART_CR3_EIE_Pos             (0U)
#define USART_CR3_EIE_Msk             (0x1UL << USART_CR3_EIE_Pos)
#define USART_CR3_EIE                 USART_CR3_EIE_Msk
#define USART_CR3_IREN_Pos            (1U)
#define USART_CR3_IREN_Msk            (0x1UL << USART_CR3_IREN_Pos)
#define USART_CR3_IREN                USART_CR3_IREN_Msk
#define USART_CR3_IRLP_Pos            (2U)
#define USART_CR3_IRLP_Msk            (0x1UL << USART_CR3_IRLP_Pos)
#define USART_CR3_IRLP                USART_CR3_IRLP_Msk
#define USART_CR3_HDSEL_Pos           (3U)
#define USART_CR3_HDSEL_Msk           (0x1UL << USART_CR3_HDSEL_Pos)
#define USART_CR3_HDSEL               USART_CR3_HDSEL_Msk
#define USART_CR3_NACK_Pos            (4U)
#define USART_CR3_NACK_Msk            (0x1UL << USART_CR3_NACK_Pos)
#define USART_CR3_NACK                USART_CR3_NACK_Msk
#define USART_CR3_SCEN_Pos            (5U)
#define USART_CR3_SCEN_Msk            (0x1UL << USART_CR3_SCEN_Pos)
#define USART_CR3_SCEN                USART_CR3_SCEN_Msk
#define USART_CR3_DMAR_Pos            (6U)
#define USART_CR3_DMAR_Msk            (0x1UL << USART_CR3_DMAR_Pos)
#define USART_CR3_DMAR                USART_CR3_DMAR_Msk
#define USART_CR3_DMAT_Pos            (7U)
#define USART_CR3_DMAT_Msk            (0x1UL << USART_CR3_DMAT_Pos)
#define USART_CR3_DMAT                USART_CR3_DMAT_Msk
#define USART_CR3_RTSE_Pos            (8U)
#define USART_CR3_RTSE_Msk            (0x1UL << USART_CR3_RTSE_Pos)
#define USART_CR3_RTSE                USART_CR3_RTSE_Msk
#define USART_CR3_CTSE_Pos            (9U)
#define USART_CR3_CTSE_Msk            (0x1UL << USART_CR3_CTSE_Pos)
#define USART_CR3_CTSE                USART_CR3_CTSE_Msk
#define USART_CR3_CTSIE_Pos           (10U)
#define USART_CR3_CTSIE_Msk           (0x1UL << USART_CR3_CTSIE_Pos)
#define USART_CR3_CTSIE               USART_CR3_CTSIE_Msk
#define USART_CR3_ONEBIT_Pos          (11U)
#define USART_CR3_ONEBIT_Msk          (0x1UL << USART_CR3_ONEBIT_Pos)
#define USART_CR3_ONEBIT              USART_CR3_ONEBIT_Msk

#define USART_GTPR_PSC_Pos            (0U)
#define USART_GTPR_PSC_Msk            (0xFFUL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC                USART_GTPR_PSC_Msk
#define USART_GTPR_PSC_0              (0x01UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_1              (0x02UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_2              (0x04UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_3              (0x08UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_4              (0x10UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_5              (0x20UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_6              (0x40UL << USART_GTPR_PSC_Pos)
#define USART_GTPR_PSC_7              (0x80UL << USART_GTPR_PSC_Pos)

#define USART_GTPR_GT_Pos             (8U)
#define USART_GTPR_GT_Msk             (0xFFUL << USART_GTPR_GT_Pos)
#define USART_GTPR_GT                 USART_GTPR_GT_Msk

#define WWDG_CR_T_Pos           (0U)
#define WWDG_CR_T_Msk           (0x7FUL << WWDG_CR_T_Pos)
#define WWDG_CR_T               WWDG_CR_T_Msk
#define WWDG_CR_T_0             (0x01UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_1             (0x02UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_2             (0x04UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_3             (0x08UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_4             (0x10UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_5             (0x20UL << WWDG_CR_T_Pos)
#define WWDG_CR_T_6             (0x40UL << WWDG_CR_T_Pos)

#define  WWDG_CR_T0                          WWDG_CR_T_0
#define  WWDG_CR_T1                          WWDG_CR_T_1
#define  WWDG_CR_T2                          WWDG_CR_T_2
#define  WWDG_CR_T3                          WWDG_CR_T_3
#define  WWDG_CR_T4                          WWDG_CR_T_4
#define  WWDG_CR_T5                          WWDG_CR_T_5
#define  WWDG_CR_T6                          WWDG_CR_T_6

#define WWDG_CR_WDGA_Pos        (7U)
#define WWDG_CR_WDGA_Msk        (0x1UL << WWDG_CR_WDGA_Pos)
#define WWDG_CR_WDGA            WWDG_CR_WDGA_Msk

#define WWDG_CFR_W_Pos          (0U)
#define WWDG_CFR_W_Msk          (0x7FUL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W              WWDG_CFR_W_Msk
#define WWDG_CFR_W_0            (0x01UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_1            (0x02UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_2            (0x04UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_3            (0x08UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_4            (0x10UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_5            (0x20UL << WWDG_CFR_W_Pos)
#define WWDG_CFR_W_6            (0x40UL << WWDG_CFR_W_Pos)

#define  WWDG_CFR_W0                         WWDG_CFR_W_0
#define  WWDG_CFR_W1                         WWDG_CFR_W_1
#define  WWDG_CFR_W2                         WWDG_CFR_W_2
#define  WWDG_CFR_W3                         WWDG_CFR_W_3
#define  WWDG_CFR_W4                         WWDG_CFR_W_4
#define  WWDG_CFR_W5                         WWDG_CFR_W_5
#define  WWDG_CFR_W6                         WWDG_CFR_W_6

#define WWDG_CFR_WDGTB_Pos      (7U)
#define WWDG_CFR_WDGTB_Msk      (0x3UL << WWDG_CFR_WDGTB_Pos)
#define WWDG_CFR_WDGTB          WWDG_CFR_WDGTB_Msk
#define WWDG_CFR_WDGTB_0        (0x1UL << WWDG_CFR_WDGTB_Pos)
#define WWDG_CFR_WDGTB_1        (0x2UL << WWDG_CFR_WDGTB_Pos)

#define  WWDG_CFR_WDGTB0                     WWDG_CFR_WDGTB_0
#define  WWDG_CFR_WDGTB1                     WWDG_CFR_WDGTB_1

#define WWDG_CFR_EWI_Pos        (9U)
#define WWDG_CFR_EWI_Msk        (0x1UL << WWDG_CFR_EWI_Pos)
#define WWDG_CFR_EWI            WWDG_CFR_EWI_Msk

#define WWDG_SR_EWIF_Pos        (0U)
#define WWDG_SR_EWIF_Msk        (0x1UL << WWDG_SR_EWIF_Pos)
#define WWDG_SR_EWIF            WWDG_SR_EWIF_Msk

#define DBGMCU_IDCODE_DEV_ID_Pos                     (0U)
#define DBGMCU_IDCODE_DEV_ID_Msk                     (0xFFFUL << DBGMCU_IDCODE_DEV_ID_Pos)
#define DBGMCU_IDCODE_DEV_ID                         DBGMCU_IDCODE_DEV_ID_Msk
#define DBGMCU_IDCODE_REV_ID_Pos                     (16U)
#define DBGMCU_IDCODE_REV_ID_Msk                     (0xFFFFUL << DBGMCU_IDCODE_REV_ID_Pos)
#define DBGMCU_IDCODE_REV_ID                         DBGMCU_IDCODE_REV_ID_Msk

#define DBGMCU_CR_DBG_SLEEP_Pos                      (0U)
#define DBGMCU_CR_DBG_SLEEP_Msk                      (0x1UL << DBGMCU_CR_DBG_SLEEP_Pos)
#define DBGMCU_CR_DBG_SLEEP                          DBGMCU_CR_DBG_SLEEP_Msk
#define DBGMCU_CR_DBG_STOP_Pos                       (1U)
#define DBGMCU_CR_DBG_STOP_Msk                       (0x1UL << DBGMCU_CR_DBG_STOP_Pos)
#define DBGMCU_CR_DBG_STOP                           DBGMCU_CR_DBG_STOP_Msk
#define DBGMCU_CR_DBG_STANDBY_Pos                    (2U)
#define DBGMCU_CR_DBG_STANDBY_Msk                    (0x1UL << DBGMCU_CR_DBG_STANDBY_Pos)
#define DBGMCU_CR_DBG_STANDBY                        DBGMCU_CR_DBG_STANDBY_Msk
#define DBGMCU_CR_TRACE_IOEN_Pos                     (5U)
#define DBGMCU_CR_TRACE_IOEN_Msk                     (0x1UL << DBGMCU_CR_TRACE_IOEN_Pos)
#define DBGMCU_CR_TRACE_IOEN                         DBGMCU_CR_TRACE_IOEN_Msk

#define DBGMCU_CR_TRACE_MODE_Pos                     (6U)
#define DBGMCU_CR_TRACE_MODE_Msk                     (0x3UL << DBGMCU_CR_TRACE_MODE_Pos)
#define DBGMCU_CR_TRACE_MODE                         DBGMCU_CR_TRACE_MODE_Msk
#define DBGMCU_CR_TRACE_MODE_0                       (0x1UL << DBGMCU_CR_TRACE_MODE_Pos)
#define DBGMCU_CR_TRACE_MODE_1                       (0x2UL << DBGMCU_CR_TRACE_MODE_Pos)

#define DBGMCU_APB1_FZ_DBG_TIM2_STOP_Pos             (0U)
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_TIM2_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_TIM2_STOP                 DBGMCU_APB1_FZ_DBG_TIM2_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP_Pos             (1U)
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_TIM3_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_TIM3_STOP                 DBGMCU_APB1_FZ_DBG_TIM3_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP_Pos             (2U)
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_TIM4_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_TIM4_STOP                 DBGMCU_APB1_FZ_DBG_TIM4_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP_Pos             (3U)
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_TIM5_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_TIM5_STOP                 DBGMCU_APB1_FZ_DBG_TIM5_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_RTC_STOP_Pos              (10U)
#define DBGMCU_APB1_FZ_DBG_RTC_STOP_Msk              (0x1UL << DBGMCU_APB1_FZ_DBG_RTC_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_RTC_STOP                  DBGMCU_APB1_FZ_DBG_RTC_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_WWDG_STOP_Pos             (11U)
#define DBGMCU_APB1_FZ_DBG_WWDG_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_WWDG_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_WWDG_STOP                 DBGMCU_APB1_FZ_DBG_WWDG_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_IWDG_STOP_Pos             (12U)
#define DBGMCU_APB1_FZ_DBG_IWDG_STOP_Msk             (0x1UL << DBGMCU_APB1_FZ_DBG_IWDG_STOP_Pos)
#define DBGMCU_APB1_FZ_DBG_IWDG_STOP                 DBGMCU_APB1_FZ_DBG_IWDG_STOP_Msk
#define DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_Pos    (21U)
#define DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_Msk    (0x1UL << DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_Pos)
#define DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT        DBGMCU_APB1_FZ_DBG_I2C1_SMBUS_TIMEOUT_Msk
#define DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_Pos    (22U)
#define DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_Msk    (0x1UL << DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_Pos)
#define DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT        DBGMCU_APB1_FZ_DBG_I2C2_SMBUS_TIMEOUT_Msk
#define DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_Pos    (23U)
#define DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_Msk    (0x1UL << DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_Pos)
#define DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT        DBGMCU_APB1_FZ_DBG_I2C3_SMBUS_TIMEOUT_Msk

#define  DBGMCU_APB1_FZ_DBG_IWDEG_STOP           DBGMCU_APB1_FZ_DBG_IWDG_STOP

#define DBGMCU_APB2_FZ_DBG_TIM1_STOP_Pos             (0U)
#define DBGMCU_APB2_FZ_DBG_TIM1_STOP_Msk             (0x1UL << DBGMCU_APB2_FZ_DBG_TIM1_STOP_Pos)
#define DBGMCU_APB2_FZ_DBG_TIM1_STOP                 DBGMCU_APB2_FZ_DBG_TIM1_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM9_STOP_Pos             (16U)
#define DBGMCU_APB2_FZ_DBG_TIM9_STOP_Msk             (0x1UL << DBGMCU_APB2_FZ_DBG_TIM9_STOP_Pos)
#define DBGMCU_APB2_FZ_DBG_TIM9_STOP                 DBGMCU_APB2_FZ_DBG_TIM9_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM10_STOP_Pos            (17U)
#define DBGMCU_APB2_FZ_DBG_TIM10_STOP_Msk            (0x1UL << DBGMCU_APB2_FZ_DBG_TIM10_STOP_Pos)
#define DBGMCU_APB2_FZ_DBG_TIM10_STOP                DBGMCU_APB2_FZ_DBG_TIM10_STOP_Msk
#define DBGMCU_APB2_FZ_DBG_TIM11_STOP_Pos            (18U)
#define DBGMCU_APB2_FZ_DBG_TIM11_STOP_Msk            (0x1UL << DBGMCU_APB2_FZ_DBG_TIM11_STOP_Pos)
#define DBGMCU_APB2_FZ_DBG_TIM11_STOP                DBGMCU_APB2_FZ_DBG_TIM11_STOP_Msk

#define USB_OTG_GOTGCTL_SRQSCS_Pos               (0U)
#define USB_OTG_GOTGCTL_SRQSCS_Msk               (0x1UL << USB_OTG_GOTGCTL_SRQSCS_Pos)
#define USB_OTG_GOTGCTL_SRQSCS                   USB_OTG_GOTGCTL_SRQSCS_Msk
#define USB_OTG_GOTGCTL_SRQ_Pos                  (1U)
#define USB_OTG_GOTGCTL_SRQ_Msk                  (0x1UL << USB_OTG_GOTGCTL_SRQ_Pos)
#define USB_OTG_GOTGCTL_SRQ                      USB_OTG_GOTGCTL_SRQ_Msk
#define USB_OTG_GOTGCTL_HNGSCS_Pos               (8U)
#define USB_OTG_GOTGCTL_HNGSCS_Msk               (0x1UL << USB_OTG_GOTGCTL_HNGSCS_Pos)
#define USB_OTG_GOTGCTL_HNGSCS                   USB_OTG_GOTGCTL_HNGSCS_Msk
#define USB_OTG_GOTGCTL_HNPRQ_Pos                (9U)
#define USB_OTG_GOTGCTL_HNPRQ_Msk                (0x1UL << USB_OTG_GOTGCTL_HNPRQ_Pos)
#define USB_OTG_GOTGCTL_HNPRQ                    USB_OTG_GOTGCTL_HNPRQ_Msk
#define USB_OTG_GOTGCTL_HSHNPEN_Pos              (10U)
#define USB_OTG_GOTGCTL_HSHNPEN_Msk              (0x1UL << USB_OTG_GOTGCTL_HSHNPEN_Pos)
#define USB_OTG_GOTGCTL_HSHNPEN                  USB_OTG_GOTGCTL_HSHNPEN_Msk
#define USB_OTG_GOTGCTL_DHNPEN_Pos               (11U)
#define USB_OTG_GOTGCTL_DHNPEN_Msk               (0x1UL << USB_OTG_GOTGCTL_DHNPEN_Pos)
#define USB_OTG_GOTGCTL_DHNPEN                   USB_OTG_GOTGCTL_DHNPEN_Msk
#define USB_OTG_GOTGCTL_CIDSTS_Pos               (16U)
#define USB_OTG_GOTGCTL_CIDSTS_Msk               (0x1UL << USB_OTG_GOTGCTL_CIDSTS_Pos)
#define USB_OTG_GOTGCTL_CIDSTS                   USB_OTG_GOTGCTL_CIDSTS_Msk
#define USB_OTG_GOTGCTL_DBCT_Pos                 (17U)
#define USB_OTG_GOTGCTL_DBCT_Msk                 (0x1UL << USB_OTG_GOTGCTL_DBCT_Pos)
#define USB_OTG_GOTGCTL_DBCT                     USB_OTG_GOTGCTL_DBCT_Msk
#define USB_OTG_GOTGCTL_ASVLD_Pos                (18U)
#define USB_OTG_GOTGCTL_ASVLD_Msk                (0x1UL << USB_OTG_GOTGCTL_ASVLD_Pos)
#define USB_OTG_GOTGCTL_ASVLD                    USB_OTG_GOTGCTL_ASVLD_Msk
#define USB_OTG_GOTGCTL_BSVLD_Pos                (19U)
#define USB_OTG_GOTGCTL_BSVLD_Msk                (0x1UL << USB_OTG_GOTGCTL_BSVLD_Pos)
#define USB_OTG_GOTGCTL_BSVLD                    USB_OTG_GOTGCTL_BSVLD_Msk

#define USB_OTG_HCFG_FSLSPCS_Pos                 (0U)
#define USB_OTG_HCFG_FSLSPCS_Msk                 (0x3UL << USB_OTG_HCFG_FSLSPCS_Pos)
#define USB_OTG_HCFG_FSLSPCS                     USB_OTG_HCFG_FSLSPCS_Msk
#define USB_OTG_HCFG_FSLSPCS_0                   (0x1UL << USB_OTG_HCFG_FSLSPCS_Pos)
#define USB_OTG_HCFG_FSLSPCS_1                   (0x2UL << USB_OTG_HCFG_FSLSPCS_Pos)
#define USB_OTG_HCFG_FSLSS_Pos                   (2U)
#define USB_OTG_HCFG_FSLSS_Msk                   (0x1UL << USB_OTG_HCFG_FSLSS_Pos)
#define USB_OTG_HCFG_FSLSS                       USB_OTG_HCFG_FSLSS_Msk

#define USB_OTG_DCFG_DSPD_Pos                    (0U)
#define USB_OTG_DCFG_DSPD_Msk                    (0x3UL << USB_OTG_DCFG_DSPD_Pos)
#define USB_OTG_DCFG_DSPD                        USB_OTG_DCFG_DSPD_Msk
#define USB_OTG_DCFG_DSPD_0                      (0x1UL << USB_OTG_DCFG_DSPD_Pos)
#define USB_OTG_DCFG_DSPD_1                      (0x2UL << USB_OTG_DCFG_DSPD_Pos)
#define USB_OTG_DCFG_NZLSOHSK_Pos                (2U)
#define USB_OTG_DCFG_NZLSOHSK_Msk                (0x1UL << USB_OTG_DCFG_NZLSOHSK_Pos)
#define USB_OTG_DCFG_NZLSOHSK                    USB_OTG_DCFG_NZLSOHSK_Msk

#define USB_OTG_DCFG_DAD_Pos                     (4U)
#define USB_OTG_DCFG_DAD_Msk                     (0x7FUL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD                         USB_OTG_DCFG_DAD_Msk
#define USB_OTG_DCFG_DAD_0                       (0x01UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_1                       (0x02UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_2                       (0x04UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_3                       (0x08UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_4                       (0x10UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_5                       (0x20UL << USB_OTG_DCFG_DAD_Pos)
#define USB_OTG_DCFG_DAD_6                       (0x40UL << USB_OTG_DCFG_DAD_Pos)

#define USB_OTG_DCFG_PFIVL_Pos                   (11U)
#define USB_OTG_DCFG_PFIVL_Msk                   (0x3UL << USB_OTG_DCFG_PFIVL_Pos)
#define USB_OTG_DCFG_PFIVL                       USB_OTG_DCFG_PFIVL_Msk
#define USB_OTG_DCFG_PFIVL_0                     (0x1UL << USB_OTG_DCFG_PFIVL_Pos)
#define USB_OTG_DCFG_PFIVL_1                     (0x2UL << USB_OTG_DCFG_PFIVL_Pos)

#define USB_OTG_DCFG_XCVRDLY_Pos                 (14U)
#define USB_OTG_DCFG_XCVRDLY_Msk                 (0x1UL << USB_OTG_DCFG_XCVRDLY_Pos)
#define USB_OTG_DCFG_XCVRDLY                     USB_OTG_DCFG_XCVRDLY_Msk

#define USB_OTG_DCFG_ERRATIM_Pos                 (15U)
#define USB_OTG_DCFG_ERRATIM_Msk                 (0x1UL << USB_OTG_DCFG_ERRATIM_Pos)
#define USB_OTG_DCFG_ERRATIM                     USB_OTG_DCFG_ERRATIM_Msk

#define USB_OTG_DCFG_PERSCHIVL_Pos               (24U)
#define USB_OTG_DCFG_PERSCHIVL_Msk               (0x3UL << USB_OTG_DCFG_PERSCHIVL_Pos)
#define USB_OTG_DCFG_PERSCHIVL                   USB_OTG_DCFG_PERSCHIVL_Msk
#define USB_OTG_DCFG_PERSCHIVL_0                 (0x1UL << USB_OTG_DCFG_PERSCHIVL_Pos)
#define USB_OTG_DCFG_PERSCHIVL_1                 (0x2UL << USB_OTG_DCFG_PERSCHIVL_Pos)

#define USB_OTG_PCGCR_STPPCLK_Pos                (0U)
#define USB_OTG_PCGCR_STPPCLK_Msk                (0x1UL << USB_OTG_PCGCR_STPPCLK_Pos)
#define USB_OTG_PCGCR_STPPCLK                    USB_OTG_PCGCR_STPPCLK_Msk
#define USB_OTG_PCGCR_GATEHCLK_Pos               (1U)
#define USB_OTG_PCGCR_GATEHCLK_Msk               (0x1UL << USB_OTG_PCGCR_GATEHCLK_Pos)
#define USB_OTG_PCGCR_GATEHCLK                   USB_OTG_PCGCR_GATEHCLK_Msk
#define USB_OTG_PCGCR_PHYSUSP_Pos                (4U)
#define USB_OTG_PCGCR_PHYSUSP_Msk                (0x1UL << USB_OTG_PCGCR_PHYSUSP_Pos)
#define USB_OTG_PCGCR_PHYSUSP                    USB_OTG_PCGCR_PHYSUSP_Msk

#define USB_OTG_GOTGINT_SEDET_Pos                (2U)
#define USB_OTG_GOTGINT_SEDET_Msk                (0x1UL << USB_OTG_GOTGINT_SEDET_Pos)
#define USB_OTG_GOTGINT_SEDET                    USB_OTG_GOTGINT_SEDET_Msk
#define USB_OTG_GOTGINT_SRSSCHG_Pos              (8U)
#define USB_OTG_GOTGINT_SRSSCHG_Msk              (0x1UL << USB_OTG_GOTGINT_SRSSCHG_Pos)
#define USB_OTG_GOTGINT_SRSSCHG                  USB_OTG_GOTGINT_SRSSCHG_Msk
#define USB_OTG_GOTGINT_HNSSCHG_Pos              (9U)
#define USB_OTG_GOTGINT_HNSSCHG_Msk              (0x1UL << USB_OTG_GOTGINT_HNSSCHG_Pos)
#define USB_OTG_GOTGINT_HNSSCHG                  USB_OTG_GOTGINT_HNSSCHG_Msk
#define USB_OTG_GOTGINT_HNGDET_Pos               (17U)
#define USB_OTG_GOTGINT_HNGDET_Msk               (0x1UL << USB_OTG_GOTGINT_HNGDET_Pos)
#define USB_OTG_GOTGINT_HNGDET                   USB_OTG_GOTGINT_HNGDET_Msk
#define USB_OTG_GOTGINT_ADTOCHG_Pos              (18U)
#define USB_OTG_GOTGINT_ADTOCHG_Msk              (0x1UL << USB_OTG_GOTGINT_ADTOCHG_Pos)
#define USB_OTG_GOTGINT_ADTOCHG                  USB_OTG_GOTGINT_ADTOCHG_Msk
#define USB_OTG_GOTGINT_DBCDNE_Pos               (19U)
#define USB_OTG_GOTGINT_DBCDNE_Msk               (0x1UL << USB_OTG_GOTGINT_DBCDNE_Pos)
#define USB_OTG_GOTGINT_DBCDNE                   USB_OTG_GOTGINT_DBCDNE_Msk

#define USB_OTG_DCTL_RWUSIG_Pos                  (0U)
#define USB_OTG_DCTL_RWUSIG_Msk                  (0x1UL << USB_OTG_DCTL_RWUSIG_Pos)
#define USB_OTG_DCTL_RWUSIG                      USB_OTG_DCTL_RWUSIG_Msk
#define USB_OTG_DCTL_SDIS_Pos                    (1U)
#define USB_OTG_DCTL_SDIS_Msk                    (0x1UL << USB_OTG_DCTL_SDIS_Pos)
#define USB_OTG_DCTL_SDIS                        USB_OTG_DCTL_SDIS_Msk
#define USB_OTG_DCTL_GINSTS_Pos                  (2U)
#define USB_OTG_DCTL_GINSTS_Msk                  (0x1UL << USB_OTG_DCTL_GINSTS_Pos)
#define USB_OTG_DCTL_GINSTS                      USB_OTG_DCTL_GINSTS_Msk
#define USB_OTG_DCTL_GONSTS_Pos                  (3U)
#define USB_OTG_DCTL_GONSTS_Msk                  (0x1UL << USB_OTG_DCTL_GONSTS_Pos)
#define USB_OTG_DCTL_GONSTS                      USB_OTG_DCTL_GONSTS_Msk

#define USB_OTG_DCTL_TCTL_Pos                    (4U)
#define USB_OTG_DCTL_TCTL_Msk                    (0x7UL << USB_OTG_DCTL_TCTL_Pos)
#define USB_OTG_DCTL_TCTL                        USB_OTG_DCTL_TCTL_Msk
#define USB_OTG_DCTL_TCTL_0                      (0x1UL << USB_OTG_DCTL_TCTL_Pos)
#define USB_OTG_DCTL_TCTL_1                      (0x2UL << USB_OTG_DCTL_TCTL_Pos)
#define USB_OTG_DCTL_TCTL_2                      (0x4UL << USB_OTG_DCTL_TCTL_Pos)
#define USB_OTG_DCTL_SGINAK_Pos                  (7U)
#define USB_OTG_DCTL_SGINAK_Msk                  (0x1UL << USB_OTG_DCTL_SGINAK_Pos)
#define USB_OTG_DCTL_SGINAK                      USB_OTG_DCTL_SGINAK_Msk
#define USB_OTG_DCTL_CGINAK_Pos                  (8U)
#define USB_OTG_DCTL_CGINAK_Msk                  (0x1UL << USB_OTG_DCTL_CGINAK_Pos)
#define USB_OTG_DCTL_CGINAK                      USB_OTG_DCTL_CGINAK_Msk
#define USB_OTG_DCTL_SGONAK_Pos                  (9U)
#define USB_OTG_DCTL_SGONAK_Msk                  (0x1UL << USB_OTG_DCTL_SGONAK_Pos)
#define USB_OTG_DCTL_SGONAK                      USB_OTG_DCTL_SGONAK_Msk
#define USB_OTG_DCTL_CGONAK_Pos                  (10U)
#define USB_OTG_DCTL_CGONAK_Msk                  (0x1UL << USB_OTG_DCTL_CGONAK_Pos)
#define USB_OTG_DCTL_CGONAK                      USB_OTG_DCTL_CGONAK_Msk
#define USB_OTG_DCTL_POPRGDNE_Pos                (11U)
#define USB_OTG_DCTL_POPRGDNE_Msk                (0x1UL << USB_OTG_DCTL_POPRGDNE_Pos)
#define USB_OTG_DCTL_POPRGDNE                    USB_OTG_DCTL_POPRGDNE_Msk

#define USB_OTG_HFIR_FRIVL_Pos                   (0U)
#define USB_OTG_HFIR_FRIVL_Msk                   (0xFFFFUL << USB_OTG_HFIR_FRIVL_Pos)
#define USB_OTG_HFIR_FRIVL                       USB_OTG_HFIR_FRIVL_Msk

#define USB_OTG_HFNUM_FRNUM_Pos                  (0U)
#define USB_OTG_HFNUM_FRNUM_Msk                  (0xFFFFUL << USB_OTG_HFNUM_FRNUM_Pos)
#define USB_OTG_HFNUM_FRNUM                      USB_OTG_HFNUM_FRNUM_Msk
#define USB_OTG_HFNUM_FTREM_Pos                  (16U)
#define USB_OTG_HFNUM_FTREM_Msk                  (0xFFFFUL << USB_OTG_HFNUM_FTREM_Pos)
#define USB_OTG_HFNUM_FTREM                      USB_OTG_HFNUM_FTREM_Msk

#define USB_OTG_DSTS_SUSPSTS_Pos                 (0U)
#define USB_OTG_DSTS_SUSPSTS_Msk                 (0x1UL << USB_OTG_DSTS_SUSPSTS_Pos)
#define USB_OTG_DSTS_SUSPSTS                     USB_OTG_DSTS_SUSPSTS_Msk

#define USB_OTG_DSTS_ENUMSPD_Pos                 (1U)
#define USB_OTG_DSTS_ENUMSPD_Msk                 (0x3UL << USB_OTG_DSTS_ENUMSPD_Pos)
#define USB_OTG_DSTS_ENUMSPD                     USB_OTG_DSTS_ENUMSPD_Msk
#define USB_OTG_DSTS_ENUMSPD_0                   (0x1UL << USB_OTG_DSTS_ENUMSPD_Pos)
#define USB_OTG_DSTS_ENUMSPD_1                   (0x2UL << USB_OTG_DSTS_ENUMSPD_Pos)
#define USB_OTG_DSTS_EERR_Pos                    (3U)
#define USB_OTG_DSTS_EERR_Msk                    (0x1UL << USB_OTG_DSTS_EERR_Pos)
#define USB_OTG_DSTS_EERR                        USB_OTG_DSTS_EERR_Msk
#define USB_OTG_DSTS_FNSOF_Pos                   (8U)
#define USB_OTG_DSTS_FNSOF_Msk                   (0x3FFFUL << USB_OTG_DSTS_FNSOF_Pos)
#define USB_OTG_DSTS_FNSOF                       USB_OTG_DSTS_FNSOF_Msk

#define USB_OTG_GAHBCFG_GINT_Pos                 (0U)
#define USB_OTG_GAHBCFG_GINT_Msk                 (0x1UL << USB_OTG_GAHBCFG_GINT_Pos)
#define USB_OTG_GAHBCFG_GINT                     USB_OTG_GAHBCFG_GINT_Msk
#define USB_OTG_GAHBCFG_HBSTLEN_Pos              (1U)
#define USB_OTG_GAHBCFG_HBSTLEN_Msk              (0xFUL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_HBSTLEN                  USB_OTG_GAHBCFG_HBSTLEN_Msk
#define USB_OTG_GAHBCFG_HBSTLEN_0                (0x0UL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_HBSTLEN_1                (0x1UL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_HBSTLEN_2                (0x3UL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_HBSTLEN_3                (0x5UL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_HBSTLEN_4                (0x7UL << USB_OTG_GAHBCFG_HBSTLEN_Pos)
#define USB_OTG_GAHBCFG_DMAEN_Pos                (5U)
#define USB_OTG_GAHBCFG_DMAEN_Msk                (0x1UL << USB_OTG_GAHBCFG_DMAEN_Pos)
#define USB_OTG_GAHBCFG_DMAEN                    USB_OTG_GAHBCFG_DMAEN_Msk
#define USB_OTG_GAHBCFG_TXFELVL_Pos              (7U)
#define USB_OTG_GAHBCFG_TXFELVL_Msk              (0x1UL << USB_OTG_GAHBCFG_TXFELVL_Pos)
#define USB_OTG_GAHBCFG_TXFELVL                  USB_OTG_GAHBCFG_TXFELVL_Msk
#define USB_OTG_GAHBCFG_PTXFELVL_Pos             (8U)
#define USB_OTG_GAHBCFG_PTXFELVL_Msk             (0x1UL << USB_OTG_GAHBCFG_PTXFELVL_Pos)
#define USB_OTG_GAHBCFG_PTXFELVL                 USB_OTG_GAHBCFG_PTXFELVL_Msk

#define USB_OTG_GUSBCFG_TOCAL_Pos                (0U)
#define USB_OTG_GUSBCFG_TOCAL_Msk                (0x7UL << USB_OTG_GUSBCFG_TOCAL_Pos)
#define USB_OTG_GUSBCFG_TOCAL                    USB_OTG_GUSBCFG_TOCAL_Msk
#define USB_OTG_GUSBCFG_TOCAL_0                  (0x1UL << USB_OTG_GUSBCFG_TOCAL_Pos)
#define USB_OTG_GUSBCFG_TOCAL_1                  (0x2UL << USB_OTG_GUSBCFG_TOCAL_Pos)
#define USB_OTG_GUSBCFG_TOCAL_2                  (0x4UL << USB_OTG_GUSBCFG_TOCAL_Pos)
#define USB_OTG_GUSBCFG_PHYSEL_Pos               (6U)
#define USB_OTG_GUSBCFG_PHYSEL_Msk               (0x1UL << USB_OTG_GUSBCFG_PHYSEL_Pos)
#define USB_OTG_GUSBCFG_PHYSEL                   USB_OTG_GUSBCFG_PHYSEL_Msk
#define USB_OTG_GUSBCFG_SRPCAP_Pos               (8U)
#define USB_OTG_GUSBCFG_SRPCAP_Msk               (0x1UL << USB_OTG_GUSBCFG_SRPCAP_Pos)
#define USB_OTG_GUSBCFG_SRPCAP                   USB_OTG_GUSBCFG_SRPCAP_Msk
#define USB_OTG_GUSBCFG_HNPCAP_Pos               (9U)
#define USB_OTG_GUSBCFG_HNPCAP_Msk               (0x1UL << USB_OTG_GUSBCFG_HNPCAP_Pos)
#define USB_OTG_GUSBCFG_HNPCAP                   USB_OTG_GUSBCFG_HNPCAP_Msk
#define USB_OTG_GUSBCFG_TRDT_Pos                 (10U)
#define USB_OTG_GUSBCFG_TRDT_Msk                 (0xFUL << USB_OTG_GUSBCFG_TRDT_Pos)
#define USB_OTG_GUSBCFG_TRDT                     USB_OTG_GUSBCFG_TRDT_Msk
#define USB_OTG_GUSBCFG_TRDT_0                   (0x1UL << USB_OTG_GUSBCFG_TRDT_Pos)
#define USB_OTG_GUSBCFG_TRDT_1                   (0x2UL << USB_OTG_GUSBCFG_TRDT_Pos)
#define USB_OTG_GUSBCFG_TRDT_2                   (0x4UL << USB_OTG_GUSBCFG_TRDT_Pos)
#define USB_OTG_GUSBCFG_TRDT_3                   (0x8UL << USB_OTG_GUSBCFG_TRDT_Pos)
#define USB_OTG_GUSBCFG_PHYLPCS_Pos              (15U)
#define USB_OTG_GUSBCFG_PHYLPCS_Msk              (0x1UL << USB_OTG_GUSBCFG_PHYLPCS_Pos)
#define USB_OTG_GUSBCFG_PHYLPCS                  USB_OTG_GUSBCFG_PHYLPCS_Msk
#define USB_OTG_GUSBCFG_ULPIFSLS_Pos             (17U)
#define USB_OTG_GUSBCFG_ULPIFSLS_Msk             (0x1UL << USB_OTG_GUSBCFG_ULPIFSLS_Pos)
#define USB_OTG_GUSBCFG_ULPIFSLS                 USB_OTG_GUSBCFG_ULPIFSLS_Msk
#define USB_OTG_GUSBCFG_ULPIAR_Pos               (18U)
#define USB_OTG_GUSBCFG_ULPIAR_Msk               (0x1UL << USB_OTG_GUSBCFG_ULPIAR_Pos)
#define USB_OTG_GUSBCFG_ULPIAR                   USB_OTG_GUSBCFG_ULPIAR_Msk
#define USB_OTG_GUSBCFG_ULPICSM_Pos              (19U)
#define USB_OTG_GUSBCFG_ULPICSM_Msk              (0x1UL << USB_OTG_GUSBCFG_ULPICSM_Pos)
#define USB_OTG_GUSBCFG_ULPICSM                  USB_OTG_GUSBCFG_ULPICSM_Msk
#define USB_OTG_GUSBCFG_ULPIEVBUSD_Pos           (20U)
#define USB_OTG_GUSBCFG_ULPIEVBUSD_Msk           (0x1UL << USB_OTG_GUSBCFG_ULPIEVBUSD_Pos)
#define USB_OTG_GUSBCFG_ULPIEVBUSD               USB_OTG_GUSBCFG_ULPIEVBUSD_Msk
#define USB_OTG_GUSBCFG_ULPIEVBUSI_Pos           (21U)
#define USB_OTG_GUSBCFG_ULPIEVBUSI_Msk           (0x1UL << USB_OTG_GUSBCFG_ULPIEVBUSI_Pos)
#define USB_OTG_GUSBCFG_ULPIEVBUSI               USB_OTG_GUSBCFG_ULPIEVBUSI_Msk
#define USB_OTG_GUSBCFG_TSDPS_Pos                (22U)
#define USB_OTG_GUSBCFG_TSDPS_Msk                (0x1UL << USB_OTG_GUSBCFG_TSDPS_Pos)
#define USB_OTG_GUSBCFG_TSDPS                    USB_OTG_GUSBCFG_TSDPS_Msk
#define USB_OTG_GUSBCFG_PCCI_Pos                 (23U)
#define USB_OTG_GUSBCFG_PCCI_Msk                 (0x1UL << USB_OTG_GUSBCFG_PCCI_Pos)
#define USB_OTG_GUSBCFG_PCCI                     USB_OTG_GUSBCFG_PCCI_Msk
#define USB_OTG_GUSBCFG_PTCI_Pos                 (24U)
#define USB_OTG_GUSBCFG_PTCI_Msk                 (0x1UL << USB_OTG_GUSBCFG_PTCI_Pos)
#define USB_OTG_GUSBCFG_PTCI                     USB_OTG_GUSBCFG_PTCI_Msk
#define USB_OTG_GUSBCFG_ULPIIPD_Pos              (25U)
#define USB_OTG_GUSBCFG_ULPIIPD_Msk              (0x1UL << USB_OTG_GUSBCFG_ULPIIPD_Pos)
#define USB_OTG_GUSBCFG_ULPIIPD                  USB_OTG_GUSBCFG_ULPIIPD_Msk
#define USB_OTG_GUSBCFG_FHMOD_Pos                (29U)
#define USB_OTG_GUSBCFG_FHMOD_Msk                (0x1UL << USB_OTG_GUSBCFG_FHMOD_Pos)
#define USB_OTG_GUSBCFG_FHMOD                    USB_OTG_GUSBCFG_FHMOD_Msk
#define USB_OTG_GUSBCFG_FDMOD_Pos                (30U)
#define USB_OTG_GUSBCFG_FDMOD_Msk                (0x1UL << USB_OTG_GUSBCFG_FDMOD_Pos)
#define USB_OTG_GUSBCFG_FDMOD                    USB_OTG_GUSBCFG_FDMOD_Msk
#define USB_OTG_GUSBCFG_CTXPKT_Pos               (31U)
#define USB_OTG_GUSBCFG_CTXPKT_Msk               (0x1UL << USB_OTG_GUSBCFG_CTXPKT_Pos)
#define USB_OTG_GUSBCFG_CTXPKT                   USB_OTG_GUSBCFG_CTXPKT_Msk

#define USB_OTG_GRSTCTL_CSRST_Pos                (0U)
#define USB_OTG_GRSTCTL_CSRST_Msk                (0x1UL << USB_OTG_GRSTCTL_CSRST_Pos)
#define USB_OTG_GRSTCTL_CSRST                    USB_OTG_GRSTCTL_CSRST_Msk
#define USB_OTG_GRSTCTL_HSRST_Pos                (1U)
#define USB_OTG_GRSTCTL_HSRST_Msk                (0x1UL << USB_OTG_GRSTCTL_HSRST_Pos)
#define USB_OTG_GRSTCTL_HSRST                    USB_OTG_GRSTCTL_HSRST_Msk
#define USB_OTG_GRSTCTL_FCRST_Pos                (2U)
#define USB_OTG_GRSTCTL_FCRST_Msk                (0x1UL << USB_OTG_GRSTCTL_FCRST_Pos)
#define USB_OTG_GRSTCTL_FCRST                    USB_OTG_GRSTCTL_FCRST_Msk
#define USB_OTG_GRSTCTL_RXFFLSH_Pos              (4U)
#define USB_OTG_GRSTCTL_RXFFLSH_Msk              (0x1UL << USB_OTG_GRSTCTL_RXFFLSH_Pos)
#define USB_OTG_GRSTCTL_RXFFLSH                  USB_OTG_GRSTCTL_RXFFLSH_Msk
#define USB_OTG_GRSTCTL_TXFFLSH_Pos              (5U)
#define USB_OTG_GRSTCTL_TXFFLSH_Msk              (0x1UL << USB_OTG_GRSTCTL_TXFFLSH_Pos)
#define USB_OTG_GRSTCTL_TXFFLSH                  USB_OTG_GRSTCTL_TXFFLSH_Msk

#define USB_OTG_GRSTCTL_TXFNUM_Pos               (6U)
#define USB_OTG_GRSTCTL_TXFNUM_Msk               (0x1FUL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_TXFNUM                   USB_OTG_GRSTCTL_TXFNUM_Msk
#define USB_OTG_GRSTCTL_TXFNUM_0                 (0x01UL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_TXFNUM_1                 (0x02UL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_TXFNUM_2                 (0x04UL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_TXFNUM_3                 (0x08UL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_TXFNUM_4                 (0x10UL << USB_OTG_GRSTCTL_TXFNUM_Pos)
#define USB_OTG_GRSTCTL_DMAREQ_Pos               (30U)
#define USB_OTG_GRSTCTL_DMAREQ_Msk               (0x1UL << USB_OTG_GRSTCTL_DMAREQ_Pos)
#define USB_OTG_GRSTCTL_DMAREQ                   USB_OTG_GRSTCTL_DMAREQ_Msk
#define USB_OTG_GRSTCTL_AHBIDL_Pos               (31U)
#define USB_OTG_GRSTCTL_AHBIDL_Msk               (0x1UL << USB_OTG_GRSTCTL_AHBIDL_Pos)
#define USB_OTG_GRSTCTL_AHBIDL                   USB_OTG_GRSTCTL_AHBIDL_Msk

#define USB_OTG_DIEPMSK_XFRCM_Pos                (0U)
#define USB_OTG_DIEPMSK_XFRCM_Msk                (0x1UL << USB_OTG_DIEPMSK_XFRCM_Pos)
#define USB_OTG_DIEPMSK_XFRCM                    USB_OTG_DIEPMSK_XFRCM_Msk
#define USB_OTG_DIEPMSK_EPDM_Pos                 (1U)
#define USB_OTG_DIEPMSK_EPDM_Msk                 (0x1UL << USB_OTG_DIEPMSK_EPDM_Pos)
#define USB_OTG_DIEPMSK_EPDM                     USB_OTG_DIEPMSK_EPDM_Msk
#define USB_OTG_DIEPMSK_TOM_Pos                  (3U)
#define USB_OTG_DIEPMSK_TOM_Msk                  (0x1UL << USB_OTG_DIEPMSK_TOM_Pos)
#define USB_OTG_DIEPMSK_TOM                      USB_OTG_DIEPMSK_TOM_Msk
#define USB_OTG_DIEPMSK_ITTXFEMSK_Pos            (4U)
#define USB_OTG_DIEPMSK_ITTXFEMSK_Msk            (0x1UL << USB_OTG_DIEPMSK_ITTXFEMSK_Pos)
#define USB_OTG_DIEPMSK_ITTXFEMSK                USB_OTG_DIEPMSK_ITTXFEMSK_Msk
#define USB_OTG_DIEPMSK_INEPNMM_Pos              (5U)
#define USB_OTG_DIEPMSK_INEPNMM_Msk              (0x1UL << USB_OTG_DIEPMSK_INEPNMM_Pos)
#define USB_OTG_DIEPMSK_INEPNMM                  USB_OTG_DIEPMSK_INEPNMM_Msk
#define USB_OTG_DIEPMSK_INEPNEM_Pos              (6U)
#define USB_OTG_DIEPMSK_INEPNEM_Msk              (0x1UL << USB_OTG_DIEPMSK_INEPNEM_Pos)
#define USB_OTG_DIEPMSK_INEPNEM                  USB_OTG_DIEPMSK_INEPNEM_Msk
#define USB_OTG_DIEPMSK_TXFURM_Pos               (8U)
#define USB_OTG_DIEPMSK_TXFURM_Msk               (0x1UL << USB_OTG_DIEPMSK_TXFURM_Pos)
#define USB_OTG_DIEPMSK_TXFURM                   USB_OTG_DIEPMSK_TXFURM_Msk
#define USB_OTG_DIEPMSK_NAKM_Pos                 (13U)
#define USB_OTG_DIEPMSK_NAKM_Msk                 (0x1UL << USB_OTG_DIEPMSK_NAKM_Pos)
#define USB_OTG_DIEPMSK_NAKM                     USB_OTG_DIEPMSK_NAKM_Msk

#define USB_OTG_HPTXSTS_PTXFSAVL_Pos             (0U)
#define USB_OTG_HPTXSTS_PTXFSAVL_Msk             (0xFFFFUL << USB_OTG_HPTXSTS_PTXFSAVL_Pos)
#define USB_OTG_HPTXSTS_PTXFSAVL                 USB_OTG_HPTXSTS_PTXFSAVL_Msk
#define USB_OTG_HPTXSTS_PTXQSAV_Pos              (16U)
#define USB_OTG_HPTXSTS_PTXQSAV_Msk              (0xFFUL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV                  USB_OTG_HPTXSTS_PTXQSAV_Msk
#define USB_OTG_HPTXSTS_PTXQSAV_0                (0x01UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_1                (0x02UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_2                (0x04UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_3                (0x08UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_4                (0x10UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_5                (0x20UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_6                (0x40UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)
#define USB_OTG_HPTXSTS_PTXQSAV_7                (0x80UL << USB_OTG_HPTXSTS_PTXQSAV_Pos)

#define USB_OTG_HPTXSTS_PTXQTOP_Pos              (24U)
#define USB_OTG_HPTXSTS_PTXQTOP_Msk              (0xFFUL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP                  USB_OTG_HPTXSTS_PTXQTOP_Msk
#define USB_OTG_HPTXSTS_PTXQTOP_0                (0x01UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_1                (0x02UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_2                (0x04UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_3                (0x08UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_4                (0x10UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_5                (0x20UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_6                (0x40UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)
#define USB_OTG_HPTXSTS_PTXQTOP_7                (0x80UL << USB_OTG_HPTXSTS_PTXQTOP_Pos)

#define USB_OTG_HAINT_HAINT_Pos                  (0U)
#define USB_OTG_HAINT_HAINT_Msk                  (0xFFFFUL << USB_OTG_HAINT_HAINT_Pos)
#define USB_OTG_HAINT_HAINT                      USB_OTG_HAINT_HAINT_Msk

#define USB_OTG_DOEPMSK_XFRCM_Pos                (0U)
#define USB_OTG_DOEPMSK_XFRCM_Msk                (0x1UL << USB_OTG_DOEPMSK_XFRCM_Pos)
#define USB_OTG_DOEPMSK_XFRCM                    USB_OTG_DOEPMSK_XFRCM_Msk
#define USB_OTG_DOEPMSK_EPDM_Pos                 (1U)
#define USB_OTG_DOEPMSK_EPDM_Msk                 (0x1UL << USB_OTG_DOEPMSK_EPDM_Pos)
#define USB_OTG_DOEPMSK_EPDM                     USB_OTG_DOEPMSK_EPDM_Msk
#define USB_OTG_DOEPMSK_AHBERRM_Pos              (2U)
#define USB_OTG_DOEPMSK_AHBERRM_Msk              (0x1UL << USB_OTG_DOEPMSK_AHBERRM_Pos)
#define USB_OTG_DOEPMSK_AHBERRM                  USB_OTG_DOEPMSK_AHBERRM_Msk
#define USB_OTG_DOEPMSK_STUPM_Pos                (3U)
#define USB_OTG_DOEPMSK_STUPM_Msk                (0x1UL << USB_OTG_DOEPMSK_STUPM_Pos)
#define USB_OTG_DOEPMSK_STUPM                    USB_OTG_DOEPMSK_STUPM_Msk
#define USB_OTG_DOEPMSK_OTEPDM_Pos               (4U)
#define USB_OTG_DOEPMSK_OTEPDM_Msk               (0x1UL << USB_OTG_DOEPMSK_OTEPDM_Pos)
#define USB_OTG_DOEPMSK_OTEPDM                   USB_OTG_DOEPMSK_OTEPDM_Msk
#define USB_OTG_DOEPMSK_OTEPSPRM_Pos             (5U)
#define USB_OTG_DOEPMSK_OTEPSPRM_Msk             (0x1UL << USB_OTG_DOEPMSK_OTEPSPRM_Pos)
#define USB_OTG_DOEPMSK_OTEPSPRM                 USB_OTG_DOEPMSK_OTEPSPRM_Msk
#define USB_OTG_DOEPMSK_B2BSTUP_Pos              (6U)
#define USB_OTG_DOEPMSK_B2BSTUP_Msk              (0x1UL << USB_OTG_DOEPMSK_B2BSTUP_Pos)
#define USB_OTG_DOEPMSK_B2BSTUP                  USB_OTG_DOEPMSK_B2BSTUP_Msk
#define USB_OTG_DOEPMSK_OPEM_Pos                 (8U)
#define USB_OTG_DOEPMSK_OPEM_Msk                 (0x1UL << USB_OTG_DOEPMSK_OPEM_Pos)
#define USB_OTG_DOEPMSK_OPEM                     USB_OTG_DOEPMSK_OPEM_Msk
#define USB_OTG_DOEPMSK_BOIM_Pos                 (9U)
#define USB_OTG_DOEPMSK_BOIM_Msk                 (0x1UL << USB_OTG_DOEPMSK_BOIM_Pos)
#define USB_OTG_DOEPMSK_BOIM                     USB_OTG_DOEPMSK_BOIM_Msk
#define USB_OTG_DOEPMSK_BERRM_Pos                (12U)
#define USB_OTG_DOEPMSK_BERRM_Msk                (0x1UL << USB_OTG_DOEPMSK_BERRM_Pos)
#define USB_OTG_DOEPMSK_BERRM                    USB_OTG_DOEPMSK_BERRM_Msk
#define USB_OTG_DOEPMSK_NAKM_Pos                 (13U)
#define USB_OTG_DOEPMSK_NAKM_Msk                 (0x1UL << USB_OTG_DOEPMSK_NAKM_Pos)
#define USB_OTG_DOEPMSK_NAKM                     USB_OTG_DOEPMSK_NAKM_Msk
#define USB_OTG_DOEPMSK_NYETM_Pos                (14U)
#define USB_OTG_DOEPMSK_NYETM_Msk                (0x1UL << USB_OTG_DOEPMSK_NYETM_Pos)
#define USB_OTG_DOEPMSK_NYETM                    USB_OTG_DOEPMSK_NYETM_Msk

#define USB_OTG_GINTSTS_CMOD_Pos                 (0U)
#define USB_OTG_GINTSTS_CMOD_Msk                 (0x1UL << USB_OTG_GINTSTS_CMOD_Pos)
#define USB_OTG_GINTSTS_CMOD                     USB_OTG_GINTSTS_CMOD_Msk
#define USB_OTG_GINTSTS_MMIS_Pos                 (1U)
#define USB_OTG_GINTSTS_MMIS_Msk                 (0x1UL << USB_OTG_GINTSTS_MMIS_Pos)
#define USB_OTG_GINTSTS_MMIS                     USB_OTG_GINTSTS_MMIS_Msk
#define USB_OTG_GINTSTS_OTGINT_Pos               (2U)
#define USB_OTG_GINTSTS_OTGINT_Msk               (0x1UL << USB_OTG_GINTSTS_OTGINT_Pos)
#define USB_OTG_GINTSTS_OTGINT                   USB_OTG_GINTSTS_OTGINT_Msk
#define USB_OTG_GINTSTS_SOF_Pos                  (3U)
#define USB_OTG_GINTSTS_SOF_Msk                  (0x1UL << USB_OTG_GINTSTS_SOF_Pos)
#define USB_OTG_GINTSTS_SOF                      USB_OTG_GINTSTS_SOF_Msk
#define USB_OTG_GINTSTS_RXFLVL_Pos               (4U)
#define USB_OTG_GINTSTS_RXFLVL_Msk               (0x1UL << USB_OTG_GINTSTS_RXFLVL_Pos)
#define USB_OTG_GINTSTS_RXFLVL                   USB_OTG_GINTSTS_RXFLVL_Msk
#define USB_OTG_GINTSTS_NPTXFE_Pos               (5U)
#define USB_OTG_GINTSTS_NPTXFE_Msk               (0x1UL << USB_OTG_GINTSTS_NPTXFE_Pos)
#define USB_OTG_GINTSTS_NPTXFE                   USB_OTG_GINTSTS_NPTXFE_Msk
#define USB_OTG_GINTSTS_GINAKEFF_Pos             (6U)
#define USB_OTG_GINTSTS_GINAKEFF_Msk             (0x1UL << USB_OTG_GINTSTS_GINAKEFF_Pos)
#define USB_OTG_GINTSTS_GINAKEFF                 USB_OTG_GINTSTS_GINAKEFF_Msk
#define USB_OTG_GINTSTS_BOUTNAKEFF_Pos           (7U)
#define USB_OTG_GINTSTS_BOUTNAKEFF_Msk           (0x1UL << USB_OTG_GINTSTS_BOUTNAKEFF_Pos)
#define USB_OTG_GINTSTS_BOUTNAKEFF               USB_OTG_GINTSTS_BOUTNAKEFF_Msk
#define USB_OTG_GINTSTS_ESUSP_Pos                (10U)
#define USB_OTG_GINTSTS_ESUSP_Msk                (0x1UL << USB_OTG_GINTSTS_ESUSP_Pos)
#define USB_OTG_GINTSTS_ESUSP                    USB_OTG_GINTSTS_ESUSP_Msk
#define USB_OTG_GINTSTS_USBSUSP_Pos              (11U)
#define USB_OTG_GINTSTS_USBSUSP_Msk              (0x1UL << USB_OTG_GINTSTS_USBSUSP_Pos)
#define USB_OTG_GINTSTS_USBSUSP                  USB_OTG_GINTSTS_USBSUSP_Msk
#define USB_OTG_GINTSTS_USBRST_Pos               (12U)
#define USB_OTG_GINTSTS_USBRST_Msk               (0x1UL << USB_OTG_GINTSTS_USBRST_Pos)
#define USB_OTG_GINTSTS_USBRST                   USB_OTG_GINTSTS_USBRST_Msk
#define USB_OTG_GINTSTS_ENUMDNE_Pos              (13U)
#define USB_OTG_GINTSTS_ENUMDNE_Msk              (0x1UL << USB_OTG_GINTSTS_ENUMDNE_Pos)
#define USB_OTG_GINTSTS_ENUMDNE                  USB_OTG_GINTSTS_ENUMDNE_Msk
#define USB_OTG_GINTSTS_ISOODRP_Pos              (14U)
#define USB_OTG_GINTSTS_ISOODRP_Msk              (0x1UL << USB_OTG_GINTSTS_ISOODRP_Pos)
#define USB_OTG_GINTSTS_ISOODRP                  USB_OTG_GINTSTS_ISOODRP_Msk
#define USB_OTG_GINTSTS_EOPF_Pos                 (15U)
#define USB_OTG_GINTSTS_EOPF_Msk                 (0x1UL << USB_OTG_GINTSTS_EOPF_Pos)
#define USB_OTG_GINTSTS_EOPF                     USB_OTG_GINTSTS_EOPF_Msk
#define USB_OTG_GINTSTS_IEPINT_Pos               (18U)
#define USB_OTG_GINTSTS_IEPINT_Msk               (0x1UL << USB_OTG_GINTSTS_IEPINT_Pos)
#define USB_OTG_GINTSTS_IEPINT                   USB_OTG_GINTSTS_IEPINT_Msk
#define USB_OTG_GINTSTS_OEPINT_Pos               (19U)
#define USB_OTG_GINTSTS_OEPINT_Msk               (0x1UL << USB_OTG_GINTSTS_OEPINT_Pos)
#define USB_OTG_GINTSTS_OEPINT                   USB_OTG_GINTSTS_OEPINT_Msk
#define USB_OTG_GINTSTS_IISOIXFR_Pos             (20U)
#define USB_OTG_GINTSTS_IISOIXFR_Msk             (0x1UL << USB_OTG_GINTSTS_IISOIXFR_Pos)
#define USB_OTG_GINTSTS_IISOIXFR                 USB_OTG_GINTSTS_IISOIXFR_Msk
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Pos    (21U)
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Msk    (0x1UL << USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Pos)
#define USB_OTG_GINTSTS_PXFR_INCOMPISOOUT        USB_OTG_GINTSTS_PXFR_INCOMPISOOUT_Msk
#define USB_OTG_GINTSTS_DATAFSUSP_Pos            (22U)
#define USB_OTG_GINTSTS_DATAFSUSP_Msk            (0x1UL << USB_OTG_GINTSTS_DATAFSUSP_Pos)
#define USB_OTG_GINTSTS_DATAFSUSP                USB_OTG_GINTSTS_DATAFSUSP_Msk
#define USB_OTG_GINTSTS_HPRTINT_Pos              (24U)
#define USB_OTG_GINTSTS_HPRTINT_Msk              (0x1UL << USB_OTG_GINTSTS_HPRTINT_Pos)
#define USB_OTG_GINTSTS_HPRTINT                  USB_OTG_GINTSTS_HPRTINT_Msk
#define USB_OTG_GINTSTS_HCINT_Pos                (25U)
#define USB_OTG_GINTSTS_HCINT_Msk                (0x1UL << USB_OTG_GINTSTS_HCINT_Pos)
#define USB_OTG_GINTSTS_HCINT                    USB_OTG_GINTSTS_HCINT_Msk
#define USB_OTG_GINTSTS_PTXFE_Pos                (26U)
#define USB_OTG_GINTSTS_PTXFE_Msk                (0x1UL << USB_OTG_GINTSTS_PTXFE_Pos)
#define USB_OTG_GINTSTS_PTXFE                    USB_OTG_GINTSTS_PTXFE_Msk
#define USB_OTG_GINTSTS_CIDSCHG_Pos              (28U)
#define USB_OTG_GINTSTS_CIDSCHG_Msk              (0x1UL << USB_OTG_GINTSTS_CIDSCHG_Pos)
#define USB_OTG_GINTSTS_CIDSCHG                  USB_OTG_GINTSTS_CIDSCHG_Msk
#define USB_OTG_GINTSTS_DISCINT_Pos              (29U)
#define USB_OTG_GINTSTS_DISCINT_Msk              (0x1UL << USB_OTG_GINTSTS_DISCINT_Pos)
#define USB_OTG_GINTSTS_DISCINT                  USB_OTG_GINTSTS_DISCINT_Msk
#define USB_OTG_GINTSTS_SRQINT_Pos               (30U)
#define USB_OTG_GINTSTS_SRQINT_Msk               (0x1UL << USB_OTG_GINTSTS_SRQINT_Pos)
#define USB_OTG_GINTSTS_SRQINT                   USB_OTG_GINTSTS_SRQINT_Msk
#define USB_OTG_GINTSTS_WKUINT_Pos               (31U)
#define USB_OTG_GINTSTS_WKUINT_Msk               (0x1UL << USB_OTG_GINTSTS_WKUINT_Pos)
#define USB_OTG_GINTSTS_WKUINT                   USB_OTG_GINTSTS_WKUINT_Msk

#define USB_OTG_GINTMSK_MMISM_Pos                (1U)
#define USB_OTG_GINTMSK_MMISM_Msk                (0x1UL << USB_OTG_GINTMSK_MMISM_Pos)
#define USB_OTG_GINTMSK_MMISM                    USB_OTG_GINTMSK_MMISM_Msk
#define USB_OTG_GINTMSK_OTGINT_Pos               (2U)
#define USB_OTG_GINTMSK_OTGINT_Msk               (0x1UL << USB_OTG_GINTMSK_OTGINT_Pos)
#define USB_OTG_GINTMSK_OTGINT                   USB_OTG_GINTMSK_OTGINT_Msk
#define USB_OTG_GINTMSK_SOFM_Pos                 (3U)
#define USB_OTG_GINTMSK_SOFM_Msk                 (0x1UL << USB_OTG_GINTMSK_SOFM_Pos)
#define USB_OTG_GINTMSK_SOFM                     USB_OTG_GINTMSK_SOFM_Msk
#define USB_OTG_GINTMSK_RXFLVLM_Pos              (4U)
#define USB_OTG_GINTMSK_RXFLVLM_Msk              (0x1UL << USB_OTG_GINTMSK_RXFLVLM_Pos)
#define USB_OTG_GINTMSK_RXFLVLM                  USB_OTG_GINTMSK_RXFLVLM_Msk
#define USB_OTG_GINTMSK_NPTXFEM_Pos              (5U)
#define USB_OTG_GINTMSK_NPTXFEM_Msk              (0x1UL << USB_OTG_GINTMSK_NPTXFEM_Pos)
#define USB_OTG_GINTMSK_NPTXFEM                  USB_OTG_GINTMSK_NPTXFEM_Msk
#define USB_OTG_GINTMSK_GINAKEFFM_Pos            (6U)
#define USB_OTG_GINTMSK_GINAKEFFM_Msk            (0x1UL << USB_OTG_GINTMSK_GINAKEFFM_Pos)
#define USB_OTG_GINTMSK_GINAKEFFM                USB_OTG_GINTMSK_GINAKEFFM_Msk
#define USB_OTG_GINTMSK_GONAKEFFM_Pos            (7U)
#define USB_OTG_GINTMSK_GONAKEFFM_Msk            (0x1UL << USB_OTG_GINTMSK_GONAKEFFM_Pos)
#define USB_OTG_GINTMSK_GONAKEFFM                USB_OTG_GINTMSK_GONAKEFFM_Msk
#define USB_OTG_GINTMSK_ESUSPM_Pos               (10U)
#define USB_OTG_GINTMSK_ESUSPM_Msk               (0x1UL << USB_OTG_GINTMSK_ESUSPM_Pos)
#define USB_OTG_GINTMSK_ESUSPM                   USB_OTG_GINTMSK_ESUSPM_Msk
#define USB_OTG_GINTMSK_USBSUSPM_Pos             (11U)
#define USB_OTG_GINTMSK_USBSUSPM_Msk             (0x1UL << USB_OTG_GINTMSK_USBSUSPM_Pos)
#define USB_OTG_GINTMSK_USBSUSPM                 USB_OTG_GINTMSK_USBSUSPM_Msk
#define USB_OTG_GINTMSK_USBRST_Pos               (12U)
#define USB_OTG_GINTMSK_USBRST_Msk               (0x1UL << USB_OTG_GINTMSK_USBRST_Pos)
#define USB_OTG_GINTMSK_USBRST                   USB_OTG_GINTMSK_USBRST_Msk
#define USB_OTG_GINTMSK_ENUMDNEM_Pos             (13U)
#define USB_OTG_GINTMSK_ENUMDNEM_Msk             (0x1UL << USB_OTG_GINTMSK_ENUMDNEM_Pos)
#define USB_OTG_GINTMSK_ENUMDNEM                 USB_OTG_GINTMSK_ENUMDNEM_Msk
#define USB_OTG_GINTMSK_ISOODRPM_Pos             (14U)
#define USB_OTG_GINTMSK_ISOODRPM_Msk             (0x1UL << USB_OTG_GINTMSK_ISOODRPM_Pos)
#define USB_OTG_GINTMSK_ISOODRPM                 USB_OTG_GINTMSK_ISOODRPM_Msk
#define USB_OTG_GINTMSK_EOPFM_Pos                (15U)
#define USB_OTG_GINTMSK_EOPFM_Msk                (0x1UL << USB_OTG_GINTMSK_EOPFM_Pos)
#define USB_OTG_GINTMSK_EOPFM                    USB_OTG_GINTMSK_EOPFM_Msk
#define USB_OTG_GINTMSK_EPMISM_Pos               (17U)
#define USB_OTG_GINTMSK_EPMISM_Msk               (0x1UL << USB_OTG_GINTMSK_EPMISM_Pos)
#define USB_OTG_GINTMSK_EPMISM                   USB_OTG_GINTMSK_EPMISM_Msk
#define USB_OTG_GINTMSK_IEPINT_Pos               (18U)
#define USB_OTG_GINTMSK_IEPINT_Msk               (0x1UL << USB_OTG_GINTMSK_IEPINT_Pos)
#define USB_OTG_GINTMSK_IEPINT                   USB_OTG_GINTMSK_IEPINT_Msk
#define USB_OTG_GINTMSK_OEPINT_Pos               (19U)
#define USB_OTG_GINTMSK_OEPINT_Msk               (0x1UL << USB_OTG_GINTMSK_OEPINT_Pos)
#define USB_OTG_GINTMSK_OEPINT                   USB_OTG_GINTMSK_OEPINT_Msk
#define USB_OTG_GINTMSK_IISOIXFRM_Pos            (20U)
#define USB_OTG_GINTMSK_IISOIXFRM_Msk            (0x1UL << USB_OTG_GINTMSK_IISOIXFRM_Pos)
#define USB_OTG_GINTMSK_IISOIXFRM                USB_OTG_GINTMSK_IISOIXFRM_Msk
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Pos      (21U)
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Msk      (0x1UL << USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Pos)
#define USB_OTG_GINTMSK_PXFRM_IISOOXFRM          USB_OTG_GINTMSK_PXFRM_IISOOXFRM_Msk
#define USB_OTG_GINTMSK_FSUSPM_Pos               (22U)
#define USB_OTG_GINTMSK_FSUSPM_Msk               (0x1UL << USB_OTG_GINTMSK_FSUSPM_Pos)
#define USB_OTG_GINTMSK_FSUSPM                   USB_OTG_GINTMSK_FSUSPM_Msk
#define USB_OTG_GINTMSK_PRTIM_Pos                (24U)
#define USB_OTG_GINTMSK_PRTIM_Msk                (0x1UL << USB_OTG_GINTMSK_PRTIM_Pos)
#define USB_OTG_GINTMSK_PRTIM                    USB_OTG_GINTMSK_PRTIM_Msk
#define USB_OTG_GINTMSK_HCIM_Pos                 (25U)
#define USB_OTG_GINTMSK_HCIM_Msk                 (0x1UL << USB_OTG_GINTMSK_HCIM_Pos)
#define USB_OTG_GINTMSK_HCIM                     USB_OTG_GINTMSK_HCIM_Msk
#define USB_OTG_GINTMSK_PTXFEM_Pos               (26U)
#define USB_OTG_GINTMSK_PTXFEM_Msk               (0x1UL << USB_OTG_GINTMSK_PTXFEM_Pos)
#define USB_OTG_GINTMSK_PTXFEM                   USB_OTG_GINTMSK_PTXFEM_Msk
#define USB_OTG_GINTMSK_CIDSCHGM_Pos             (28U)
#define USB_OTG_GINTMSK_CIDSCHGM_Msk             (0x1UL << USB_OTG_GINTMSK_CIDSCHGM_Pos)
#define USB_OTG_GINTMSK_CIDSCHGM                 USB_OTG_GINTMSK_CIDSCHGM_Msk
#define USB_OTG_GINTMSK_DISCINT_Pos              (29U)
#define USB_OTG_GINTMSK_DISCINT_Msk              (0x1UL << USB_OTG_GINTMSK_DISCINT_Pos)
#define USB_OTG_GINTMSK_DISCINT                  USB_OTG_GINTMSK_DISCINT_Msk
#define USB_OTG_GINTMSK_SRQIM_Pos                (30U)
#define USB_OTG_GINTMSK_SRQIM_Msk                (0x1UL << USB_OTG_GINTMSK_SRQIM_Pos)
#define USB_OTG_GINTMSK_SRQIM                    USB_OTG_GINTMSK_SRQIM_Msk
#define USB_OTG_GINTMSK_WUIM_Pos                 (31U)
#define USB_OTG_GINTMSK_WUIM_Msk                 (0x1UL << USB_OTG_GINTMSK_WUIM_Pos)
#define USB_OTG_GINTMSK_WUIM                     USB_OTG_GINTMSK_WUIM_Msk

#define USB_OTG_DAINT_IEPINT_Pos                 (0U)
#define USB_OTG_DAINT_IEPINT_Msk                 (0xFFFFUL << USB_OTG_DAINT_IEPINT_Pos)
#define USB_OTG_DAINT_IEPINT                     USB_OTG_DAINT_IEPINT_Msk
#define USB_OTG_DAINT_OEPINT_Pos                 (16U)
#define USB_OTG_DAINT_OEPINT_Msk                 (0xFFFFUL << USB_OTG_DAINT_OEPINT_Pos)
#define USB_OTG_DAINT_OEPINT                     USB_OTG_DAINT_OEPINT_Msk

#define USB_OTG_HAINTMSK_HAINTM_Pos              (0U)
#define USB_OTG_HAINTMSK_HAINTM_Msk              (0xFFFFUL << USB_OTG_HAINTMSK_HAINTM_Pos)
#define USB_OTG_HAINTMSK_HAINTM                  USB_OTG_HAINTMSK_HAINTM_Msk

#define USB_OTG_GRXSTSP_EPNUM_Pos                (0U)
#define USB_OTG_GRXSTSP_EPNUM_Msk                (0xFUL << USB_OTG_GRXSTSP_EPNUM_Pos)
#define USB_OTG_GRXSTSP_EPNUM                    USB_OTG_GRXSTSP_EPNUM_Msk
#define USB_OTG_GRXSTSP_BCNT_Pos                 (4U)
#define USB_OTG_GRXSTSP_BCNT_Msk                 (0x7FFUL << USB_OTG_GRXSTSP_BCNT_Pos)
#define USB_OTG_GRXSTSP_BCNT                     USB_OTG_GRXSTSP_BCNT_Msk
#define USB_OTG_GRXSTSP_DPID_Pos                 (15U)
#define USB_OTG_GRXSTSP_DPID_Msk                 (0x3UL << USB_OTG_GRXSTSP_DPID_Pos)
#define USB_OTG_GRXSTSP_DPID                     USB_OTG_GRXSTSP_DPID_Msk
#define USB_OTG_GRXSTSP_PKTSTS_Pos               (17U)
#define USB_OTG_GRXSTSP_PKTSTS_Msk               (0xFUL << USB_OTG_GRXSTSP_PKTSTS_Pos)
#define USB_OTG_GRXSTSP_PKTSTS                   USB_OTG_GRXSTSP_PKTSTS_Msk

#define USB_OTG_DAINTMSK_IEPM_Pos                (0U)
#define USB_OTG_DAINTMSK_IEPM_Msk                (0xFFFFUL << USB_OTG_DAINTMSK_IEPM_Pos)
#define USB_OTG_DAINTMSK_IEPM                    USB_OTG_DAINTMSK_IEPM_Msk
#define USB_OTG_DAINTMSK_OEPM_Pos                (16U)
#define USB_OTG_DAINTMSK_OEPM_Msk                (0xFFFFUL << USB_OTG_DAINTMSK_OEPM_Pos)
#define USB_OTG_DAINTMSK_OEPM                    USB_OTG_DAINTMSK_OEPM_Msk

#define USB_OTG_GRXFSIZ_RXFD_Pos                 (0U)
#define USB_OTG_GRXFSIZ_RXFD_Msk                 (0xFFFFUL << USB_OTG_GRXFSIZ_RXFD_Pos)
#define USB_OTG_GRXFSIZ_RXFD                     USB_OTG_GRXFSIZ_RXFD_Msk

#define USB_OTG_DVBUSDIS_VBUSDT_Pos              (0U)
#define USB_OTG_DVBUSDIS_VBUSDT_Msk              (0xFFFFUL << USB_OTG_DVBUSDIS_VBUSDT_Pos)
#define USB_OTG_DVBUSDIS_VBUSDT                  USB_OTG_DVBUSDIS_VBUSDT_Msk

#define USB_OTG_NPTXFSA_Pos                      (0U)
#define USB_OTG_NPTXFSA_Msk                      (0xFFFFUL << USB_OTG_NPTXFSA_Pos)
#define USB_OTG_NPTXFSA                          USB_OTG_NPTXFSA_Msk
#define USB_OTG_NPTXFD_Pos                       (16U)
#define USB_OTG_NPTXFD_Msk                       (0xFFFFUL << USB_OTG_NPTXFD_Pos)
#define USB_OTG_NPTXFD                           USB_OTG_NPTXFD_Msk
#define USB_OTG_TX0FSA_Pos                       (0U)
#define USB_OTG_TX0FSA_Msk                       (0xFFFFUL << USB_OTG_TX0FSA_Pos)
#define USB_OTG_TX0FSA                           USB_OTG_TX0FSA_Msk
#define USB_OTG_TX0FD_Pos                        (16U)
#define USB_OTG_TX0FD_Msk                        (0xFFFFUL << USB_OTG_TX0FD_Pos)
#define USB_OTG_TX0FD                            USB_OTG_TX0FD_Msk

#define USB_OTG_DVBUSPULSE_DVBUSP_Pos            (0U)
#define USB_OTG_DVBUSPULSE_DVBUSP_Msk            (0xFFFUL << USB_OTG_DVBUSPULSE_DVBUSP_Pos)
#define USB_OTG_DVBUSPULSE_DVBUSP                USB_OTG_DVBUSPULSE_DVBUSP_Msk

#define USB_OTG_GNPTXSTS_NPTXFSAV_Pos            (0U)
#define USB_OTG_GNPTXSTS_NPTXFSAV_Msk            (0xFFFFUL << USB_OTG_GNPTXSTS_NPTXFSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTXFSAV                USB_OTG_GNPTXSTS_NPTXFSAV_Msk

#define USB_OTG_GNPTXSTS_NPTQXSAV_Pos            (16U)
#define USB_OTG_GNPTXSTS_NPTQXSAV_Msk            (0xFFUL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV                USB_OTG_GNPTXSTS_NPTQXSAV_Msk
#define USB_OTG_GNPTXSTS_NPTQXSAV_0              (0x01UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_1              (0x02UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_2              (0x04UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_3              (0x08UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_4              (0x10UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_5              (0x20UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_6              (0x40UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)
#define USB_OTG_GNPTXSTS_NPTQXSAV_7              (0x80UL << USB_OTG_GNPTXSTS_NPTQXSAV_Pos)

#define USB_OTG_GNPTXSTS_NPTXQTOP_Pos            (24U)
#define USB_OTG_GNPTXSTS_NPTXQTOP_Msk            (0x7FUL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP                USB_OTG_GNPTXSTS_NPTXQTOP_Msk
#define USB_OTG_GNPTXSTS_NPTXQTOP_0              (0x01UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_1              (0x02UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_2              (0x04UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_3              (0x08UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_4              (0x10UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_5              (0x20UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)
#define USB_OTG_GNPTXSTS_NPTXQTOP_6              (0x40UL << USB_OTG_GNPTXSTS_NPTXQTOP_Pos)

#define USB_OTG_DTHRCTL_NONISOTHREN_Pos          (0U)
#define USB_OTG_DTHRCTL_NONISOTHREN_Msk          (0x1UL << USB_OTG_DTHRCTL_NONISOTHREN_Pos)
#define USB_OTG_DTHRCTL_NONISOTHREN              USB_OTG_DTHRCTL_NONISOTHREN_Msk
#define USB_OTG_DTHRCTL_ISOTHREN_Pos             (1U)
#define USB_OTG_DTHRCTL_ISOTHREN_Msk             (0x1UL << USB_OTG_DTHRCTL_ISOTHREN_Pos)
#define USB_OTG_DTHRCTL_ISOTHREN                 USB_OTG_DTHRCTL_ISOTHREN_Msk

#define USB_OTG_DTHRCTL_TXTHRLEN_Pos             (2U)
#define USB_OTG_DTHRCTL_TXTHRLEN_Msk             (0x1FFUL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN                 USB_OTG_DTHRCTL_TXTHRLEN_Msk
#define USB_OTG_DTHRCTL_TXTHRLEN_0               (0x001UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_1               (0x002UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_2               (0x004UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_3               (0x008UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_4               (0x010UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_5               (0x020UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_6               (0x040UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_7               (0x080UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_TXTHRLEN_8               (0x100UL << USB_OTG_DTHRCTL_TXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHREN_Pos              (16U)
#define USB_OTG_DTHRCTL_RXTHREN_Msk              (0x1UL << USB_OTG_DTHRCTL_RXTHREN_Pos)
#define USB_OTG_DTHRCTL_RXTHREN                  USB_OTG_DTHRCTL_RXTHREN_Msk

#define USB_OTG_DTHRCTL_RXTHRLEN_Pos             (17U)
#define USB_OTG_DTHRCTL_RXTHRLEN_Msk             (0x1FFUL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN                 USB_OTG_DTHRCTL_RXTHRLEN_Msk
#define USB_OTG_DTHRCTL_RXTHRLEN_0               (0x001UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_1               (0x002UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_2               (0x004UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_3               (0x008UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_4               (0x010UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_5               (0x020UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_6               (0x040UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_7               (0x080UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_RXTHRLEN_8               (0x100UL << USB_OTG_DTHRCTL_RXTHRLEN_Pos)
#define USB_OTG_DTHRCTL_ARPEN_Pos                (27U)
#define USB_OTG_DTHRCTL_ARPEN_Msk                (0x1UL << USB_OTG_DTHRCTL_ARPEN_Pos)
#define USB_OTG_DTHRCTL_ARPEN                    USB_OTG_DTHRCTL_ARPEN_Msk

#define USB_OTG_DIEPEMPMSK_INEPTXFEM_Pos         (0U)
#define USB_OTG_DIEPEMPMSK_INEPTXFEM_Msk         (0xFFFFUL << USB_OTG_DIEPEMPMSK_INEPTXFEM_Pos)
#define USB_OTG_DIEPEMPMSK_INEPTXFEM             USB_OTG_DIEPEMPMSK_INEPTXFEM_Msk

#define USB_OTG_DEACHINT_IEP1INT_Pos             (1U)
#define USB_OTG_DEACHINT_IEP1INT_Msk             (0x1UL << USB_OTG_DEACHINT_IEP1INT_Pos)
#define USB_OTG_DEACHINT_IEP1INT                 USB_OTG_DEACHINT_IEP1INT_Msk
#define USB_OTG_DEACHINT_OEP1INT_Pos             (17U)
#define USB_OTG_DEACHINT_OEP1INT_Msk             (0x1UL << USB_OTG_DEACHINT_OEP1INT_Pos)
#define USB_OTG_DEACHINT_OEP1INT                 USB_OTG_DEACHINT_OEP1INT_Msk

#define USB_OTG_GCCFG_PWRDWN_Pos                 (16U)
#define USB_OTG_GCCFG_PWRDWN_Msk                 (0x1UL << USB_OTG_GCCFG_PWRDWN_Pos)
#define USB_OTG_GCCFG_PWRDWN                     USB_OTG_GCCFG_PWRDWN_Msk
#define USB_OTG_GCCFG_I2CPADEN_Pos               (17U)
#define USB_OTG_GCCFG_I2CPADEN_Msk               (0x1UL << USB_OTG_GCCFG_I2CPADEN_Pos)
#define USB_OTG_GCCFG_I2CPADEN                   USB_OTG_GCCFG_I2CPADEN_Msk
#define USB_OTG_GCCFG_VBUSASEN_Pos               (18U)
#define USB_OTG_GCCFG_VBUSASEN_Msk               (0x1UL << USB_OTG_GCCFG_VBUSASEN_Pos)
#define USB_OTG_GCCFG_VBUSASEN                   USB_OTG_GCCFG_VBUSASEN_Msk
#define USB_OTG_GCCFG_VBUSBSEN_Pos               (19U)
#define USB_OTG_GCCFG_VBUSBSEN_Msk               (0x1UL << USB_OTG_GCCFG_VBUSBSEN_Pos)
#define USB_OTG_GCCFG_VBUSBSEN                   USB_OTG_GCCFG_VBUSBSEN_Msk
#define USB_OTG_GCCFG_SOFOUTEN_Pos               (20U)
#define USB_OTG_GCCFG_SOFOUTEN_Msk               (0x1UL << USB_OTG_GCCFG_SOFOUTEN_Pos)
#define USB_OTG_GCCFG_SOFOUTEN                   USB_OTG_GCCFG_SOFOUTEN_Msk
#define USB_OTG_GCCFG_NOVBUSSENS_Pos             (21U)
#define USB_OTG_GCCFG_NOVBUSSENS_Msk             (0x1UL << USB_OTG_GCCFG_NOVBUSSENS_Pos)
#define USB_OTG_GCCFG_NOVBUSSENS                 USB_OTG_GCCFG_NOVBUSSENS_Msk

#define USB_OTG_DEACHINTMSK_IEP1INTM_Pos         (1U)
#define USB_OTG_DEACHINTMSK_IEP1INTM_Msk         (0x1UL << USB_OTG_DEACHINTMSK_IEP1INTM_Pos)
#define USB_OTG_DEACHINTMSK_IEP1INTM             USB_OTG_DEACHINTMSK_IEP1INTM_Msk
#define USB_OTG_DEACHINTMSK_OEP1INTM_Pos         (17U)
#define USB_OTG_DEACHINTMSK_OEP1INTM_Msk         (0x1UL << USB_OTG_DEACHINTMSK_OEP1INTM_Pos)
#define USB_OTG_DEACHINTMSK_OEP1INTM             USB_OTG_DEACHINTMSK_OEP1INTM_Msk

#define USB_OTG_CID_PRODUCT_ID_Pos               (0U)
#define USB_OTG_CID_PRODUCT_ID_Msk               (0xFFFFFFFFUL << USB_OTG_CID_PRODUCT_ID_Pos)
#define USB_OTG_CID_PRODUCT_ID                   USB_OTG_CID_PRODUCT_ID_Msk

#define USB_OTG_DIEPEACHMSK1_XFRCM_Pos           (0U)
#define USB_OTG_DIEPEACHMSK1_XFRCM_Msk           (0x1UL << USB_OTG_DIEPEACHMSK1_XFRCM_Pos)
#define USB_OTG_DIEPEACHMSK1_XFRCM               USB_OTG_DIEPEACHMSK1_XFRCM_Msk
#define USB_OTG_DIEPEACHMSK1_EPDM_Pos            (1U)
#define USB_OTG_DIEPEACHMSK1_EPDM_Msk            (0x1UL << USB_OTG_DIEPEACHMSK1_EPDM_Pos)
#define USB_OTG_DIEPEACHMSK1_EPDM                USB_OTG_DIEPEACHMSK1_EPDM_Msk
#define USB_OTG_DIEPEACHMSK1_TOM_Pos             (3U)
#define USB_OTG_DIEPEACHMSK1_TOM_Msk             (0x1UL << USB_OTG_DIEPEACHMSK1_TOM_Pos)
#define USB_OTG_DIEPEACHMSK1_TOM                 USB_OTG_DIEPEACHMSK1_TOM_Msk
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Pos       (4U)
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Msk       (0x1UL << USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Pos)
#define USB_OTG_DIEPEACHMSK1_ITTXFEMSK           USB_OTG_DIEPEACHMSK1_ITTXFEMSK_Msk
#define USB_OTG_DIEPEACHMSK1_INEPNMM_Pos         (5U)
#define USB_OTG_DIEPEACHMSK1_INEPNMM_Msk         (0x1UL << USB_OTG_DIEPEACHMSK1_INEPNMM_Pos)
#define USB_OTG_DIEPEACHMSK1_INEPNMM             USB_OTG_DIEPEACHMSK1_INEPNMM_Msk
#define USB_OTG_DIEPEACHMSK1_INEPNEM_Pos         (6U)
#define USB_OTG_DIEPEACHMSK1_INEPNEM_Msk         (0x1UL << USB_OTG_DIEPEACHMSK1_INEPNEM_Pos)
#define USB_OTG_DIEPEACHMSK1_INEPNEM             USB_OTG_DIEPEACHMSK1_INEPNEM_Msk
#define USB_OTG_DIEPEACHMSK1_TXFURM_Pos          (8U)
#define USB_OTG_DIEPEACHMSK1_TXFURM_Msk          (0x1UL << USB_OTG_DIEPEACHMSK1_TXFURM_Pos)
#define USB_OTG_DIEPEACHMSK1_TXFURM              USB_OTG_DIEPEACHMSK1_TXFURM_Msk
#define USB_OTG_DIEPEACHMSK1_BIM_Pos             (9U)
#define USB_OTG_DIEPEACHMSK1_BIM_Msk             (0x1UL << USB_OTG_DIEPEACHMSK1_BIM_Pos)
#define USB_OTG_DIEPEACHMSK1_BIM                 USB_OTG_DIEPEACHMSK1_BIM_Msk
#define USB_OTG_DIEPEACHMSK1_NAKM_Pos            (13U)
#define USB_OTG_DIEPEACHMSK1_NAKM_Msk            (0x1UL << USB_OTG_DIEPEACHMSK1_NAKM_Pos)
#define USB_OTG_DIEPEACHMSK1_NAKM                USB_OTG_DIEPEACHMSK1_NAKM_Msk

#define USB_OTG_HPRT_PCSTS_Pos                   (0U)
#define USB_OTG_HPRT_PCSTS_Msk                   (0x1UL << USB_OTG_HPRT_PCSTS_Pos)
#define USB_OTG_HPRT_PCSTS                       USB_OTG_HPRT_PCSTS_Msk
#define USB_OTG_HPRT_PCDET_Pos                   (1U)
#define USB_OTG_HPRT_PCDET_Msk                   (0x1UL << USB_OTG_HPRT_PCDET_Pos)
#define USB_OTG_HPRT_PCDET                       USB_OTG_HPRT_PCDET_Msk
#define USB_OTG_HPRT_PENA_Pos                    (2U)
#define USB_OTG_HPRT_PENA_Msk                    (0x1UL << USB_OTG_HPRT_PENA_Pos)
#define USB_OTG_HPRT_PENA                        USB_OTG_HPRT_PENA_Msk
#define USB_OTG_HPRT_PENCHNG_Pos                 (3U)
#define USB_OTG_HPRT_PENCHNG_Msk                 (0x1UL << USB_OTG_HPRT_PENCHNG_Pos)
#define USB_OTG_HPRT_PENCHNG                     USB_OTG_HPRT_PENCHNG_Msk
#define USB_OTG_HPRT_POCA_Pos                    (4U)
#define USB_OTG_HPRT_POCA_Msk                    (0x1UL << USB_OTG_HPRT_POCA_Pos)
#define USB_OTG_HPRT_POCA                        USB_OTG_HPRT_POCA_Msk
#define USB_OTG_HPRT_POCCHNG_Pos                 (5U)
#define USB_OTG_HPRT_POCCHNG_Msk                 (0x1UL << USB_OTG_HPRT_POCCHNG_Pos)
#define USB_OTG_HPRT_POCCHNG                     USB_OTG_HPRT_POCCHNG_Msk
#define USB_OTG_HPRT_PRES_Pos                    (6U)
#define USB_OTG_HPRT_PRES_Msk                    (0x1UL << USB_OTG_HPRT_PRES_Pos)
#define USB_OTG_HPRT_PRES                        USB_OTG_HPRT_PRES_Msk
#define USB_OTG_HPRT_PSUSP_Pos                   (7U)
#define USB_OTG_HPRT_PSUSP_Msk                   (0x1UL << USB_OTG_HPRT_PSUSP_Pos)
#define USB_OTG_HPRT_PSUSP                       USB_OTG_HPRT_PSUSP_Msk
#define USB_OTG_HPRT_PRST_Pos                    (8U)
#define USB_OTG_HPRT_PRST_Msk                    (0x1UL << USB_OTG_HPRT_PRST_Pos)
#define USB_OTG_HPRT_PRST                        USB_OTG_HPRT_PRST_Msk

#define USB_OTG_HPRT_PLSTS_Pos                   (10U)
#define USB_OTG_HPRT_PLSTS_Msk                   (0x3UL << USB_OTG_HPRT_PLSTS_Pos)
#define USB_OTG_HPRT_PLSTS                       USB_OTG_HPRT_PLSTS_Msk
#define USB_OTG_HPRT_PLSTS_0                     (0x1UL << USB_OTG_HPRT_PLSTS_Pos)
#define USB_OTG_HPRT_PLSTS_1                     (0x2UL << USB_OTG_HPRT_PLSTS_Pos)
#define USB_OTG_HPRT_PPWR_Pos                    (12U)
#define USB_OTG_HPRT_PPWR_Msk                    (0x1UL << USB_OTG_HPRT_PPWR_Pos)
#define USB_OTG_HPRT_PPWR                        USB_OTG_HPRT_PPWR_Msk

#define USB_OTG_HPRT_PTCTL_Pos                   (13U)
#define USB_OTG_HPRT_PTCTL_Msk                   (0xFUL << USB_OTG_HPRT_PTCTL_Pos)
#define USB_OTG_HPRT_PTCTL                       USB_OTG_HPRT_PTCTL_Msk
#define USB_OTG_HPRT_PTCTL_0                     (0x1UL << USB_OTG_HPRT_PTCTL_Pos)
#define USB_OTG_HPRT_PTCTL_1                     (0x2UL << USB_OTG_HPRT_PTCTL_Pos)
#define USB_OTG_HPRT_PTCTL_2                     (0x4UL << USB_OTG_HPRT_PTCTL_Pos)
#define USB_OTG_HPRT_PTCTL_3                     (0x8UL << USB_OTG_HPRT_PTCTL_Pos)

#define USB_OTG_HPRT_PSPD_Pos                    (17U)
#define USB_OTG_HPRT_PSPD_Msk                    (0x3UL << USB_OTG_HPRT_PSPD_Pos)
#define USB_OTG_HPRT_PSPD                        USB_OTG_HPRT_PSPD_Msk
#define USB_OTG_HPRT_PSPD_0                      (0x1UL << USB_OTG_HPRT_PSPD_Pos)
#define USB_OTG_HPRT_PSPD_1                      (0x2UL << USB_OTG_HPRT_PSPD_Pos)

#define USB_OTG_DOEPEACHMSK1_XFRCM_Pos           (0U)
#define USB_OTG_DOEPEACHMSK1_XFRCM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_XFRCM_Pos)
#define USB_OTG_DOEPEACHMSK1_XFRCM               USB_OTG_DOEPEACHMSK1_XFRCM_Msk
#define USB_OTG_DOEPEACHMSK1_EPDM_Pos            (1U)
#define USB_OTG_DOEPEACHMSK1_EPDM_Msk            (0x1UL << USB_OTG_DOEPEACHMSK1_EPDM_Pos)
#define USB_OTG_DOEPEACHMSK1_EPDM                USB_OTG_DOEPEACHMSK1_EPDM_Msk
#define USB_OTG_DOEPEACHMSK1_TOM_Pos             (3U)
#define USB_OTG_DOEPEACHMSK1_TOM_Msk             (0x1UL << USB_OTG_DOEPEACHMSK1_TOM_Pos)
#define USB_OTG_DOEPEACHMSK1_TOM                 USB_OTG_DOEPEACHMSK1_TOM_Msk
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Pos       (4U)
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Msk       (0x1UL << USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Pos)
#define USB_OTG_DOEPEACHMSK1_ITTXFEMSK           USB_OTG_DOEPEACHMSK1_ITTXFEMSK_Msk
#define USB_OTG_DOEPEACHMSK1_INEPNMM_Pos         (5U)
#define USB_OTG_DOEPEACHMSK1_INEPNMM_Msk         (0x1UL << USB_OTG_DOEPEACHMSK1_INEPNMM_Pos)
#define USB_OTG_DOEPEACHMSK1_INEPNMM             USB_OTG_DOEPEACHMSK1_INEPNMM_Msk
#define USB_OTG_DOEPEACHMSK1_INEPNEM_Pos         (6U)
#define USB_OTG_DOEPEACHMSK1_INEPNEM_Msk         (0x1UL << USB_OTG_DOEPEACHMSK1_INEPNEM_Pos)
#define USB_OTG_DOEPEACHMSK1_INEPNEM             USB_OTG_DOEPEACHMSK1_INEPNEM_Msk
#define USB_OTG_DOEPEACHMSK1_TXFURM_Pos          (8U)
#define USB_OTG_DOEPEACHMSK1_TXFURM_Msk          (0x1UL << USB_OTG_DOEPEACHMSK1_TXFURM_Pos)
#define USB_OTG_DOEPEACHMSK1_TXFURM              USB_OTG_DOEPEACHMSK1_TXFURM_Msk
#define USB_OTG_DOEPEACHMSK1_BIM_Pos             (9U)
#define USB_OTG_DOEPEACHMSK1_BIM_Msk             (0x1UL << USB_OTG_DOEPEACHMSK1_BIM_Pos)
#define USB_OTG_DOEPEACHMSK1_BIM                 USB_OTG_DOEPEACHMSK1_BIM_Msk
#define USB_OTG_DOEPEACHMSK1_BERRM_Pos           (12U)
#define USB_OTG_DOEPEACHMSK1_BERRM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_BERRM_Pos)
#define USB_OTG_DOEPEACHMSK1_BERRM               USB_OTG_DOEPEACHMSK1_BERRM_Msk
#define USB_OTG_DOEPEACHMSK1_NAKM_Pos            (13U)
#define USB_OTG_DOEPEACHMSK1_NAKM_Msk            (0x1UL << USB_OTG_DOEPEACHMSK1_NAKM_Pos)
#define USB_OTG_DOEPEACHMSK1_NAKM                USB_OTG_DOEPEACHMSK1_NAKM_Msk
#define USB_OTG_DOEPEACHMSK1_NYETM_Pos           (14U)
#define USB_OTG_DOEPEACHMSK1_NYETM_Msk           (0x1UL << USB_OTG_DOEPEACHMSK1_NYETM_Pos)
#define USB_OTG_DOEPEACHMSK1_NYETM               USB_OTG_DOEPEACHMSK1_NYETM_Msk

#define USB_OTG_HPTXFSIZ_PTXSA_Pos               (0U)
#define USB_OTG_HPTXFSIZ_PTXSA_Msk               (0xFFFFUL << USB_OTG_HPTXFSIZ_PTXSA_Pos)
#define USB_OTG_HPTXFSIZ_PTXSA                   USB_OTG_HPTXFSIZ_PTXSA_Msk
#define USB_OTG_HPTXFSIZ_PTXFD_Pos               (16U)
#define USB_OTG_HPTXFSIZ_PTXFD_Msk               (0xFFFFUL << USB_OTG_HPTXFSIZ_PTXFD_Pos)
#define USB_OTG_HPTXFSIZ_PTXFD                   USB_OTG_HPTXFSIZ_PTXFD_Msk

#define USB_OTG_DIEPCTL_MPSIZ_Pos                (0U)
#define USB_OTG_DIEPCTL_MPSIZ_Msk                (0x7FFUL << USB_OTG_DIEPCTL_MPSIZ_Pos)
#define USB_OTG_DIEPCTL_MPSIZ                    USB_OTG_DIEPCTL_MPSIZ_Msk
#define USB_OTG_DIEPCTL_USBAEP_Pos               (15U)
#define USB_OTG_DIEPCTL_USBAEP_Msk               (0x1UL << USB_OTG_DIEPCTL_USBAEP_Pos)
#define USB_OTG_DIEPCTL_USBAEP                   USB_OTG_DIEPCTL_USBAEP_Msk
#define USB_OTG_DIEPCTL_EONUM_DPID_Pos           (16U)
#define USB_OTG_DIEPCTL_EONUM_DPID_Msk           (0x1UL << USB_OTG_DIEPCTL_EONUM_DPID_Pos)
#define USB_OTG_DIEPCTL_EONUM_DPID               USB_OTG_DIEPCTL_EONUM_DPID_Msk
#define USB_OTG_DIEPCTL_NAKSTS_Pos               (17U)
#define USB_OTG_DIEPCTL_NAKSTS_Msk               (0x1UL << USB_OTG_DIEPCTL_NAKSTS_Pos)
#define USB_OTG_DIEPCTL_NAKSTS                   USB_OTG_DIEPCTL_NAKSTS_Msk

#define USB_OTG_DIEPCTL_EPTYP_Pos                (18U)
#define USB_OTG_DIEPCTL_EPTYP_Msk                (0x3UL << USB_OTG_DIEPCTL_EPTYP_Pos)
#define USB_OTG_DIEPCTL_EPTYP                    USB_OTG_DIEPCTL_EPTYP_Msk
#define USB_OTG_DIEPCTL_EPTYP_0                  (0x1UL << USB_OTG_DIEPCTL_EPTYP_Pos)
#define USB_OTG_DIEPCTL_EPTYP_1                  (0x2UL << USB_OTG_DIEPCTL_EPTYP_Pos)
#define USB_OTG_DIEPCTL_STALL_Pos                (21U)
#define USB_OTG_DIEPCTL_STALL_Msk                (0x1UL << USB_OTG_DIEPCTL_STALL_Pos)
#define USB_OTG_DIEPCTL_STALL                    USB_OTG_DIEPCTL_STALL_Msk

#define USB_OTG_DIEPCTL_TXFNUM_Pos               (22U)
#define USB_OTG_DIEPCTL_TXFNUM_Msk               (0xFUL << USB_OTG_DIEPCTL_TXFNUM_Pos)
#define USB_OTG_DIEPCTL_TXFNUM                   USB_OTG_DIEPCTL_TXFNUM_Msk
#define USB_OTG_DIEPCTL_TXFNUM_0                 (0x1UL << USB_OTG_DIEPCTL_TXFNUM_Pos)
#define USB_OTG_DIEPCTL_TXFNUM_1                 (0x2UL << USB_OTG_DIEPCTL_TXFNUM_Pos)
#define USB_OTG_DIEPCTL_TXFNUM_2                 (0x4UL << USB_OTG_DIEPCTL_TXFNUM_Pos)
#define USB_OTG_DIEPCTL_TXFNUM_3                 (0x8UL << USB_OTG_DIEPCTL_TXFNUM_Pos)
#define USB_OTG_DIEPCTL_CNAK_Pos                 (26U)
#define USB_OTG_DIEPCTL_CNAK_Msk                 (0x1UL << USB_OTG_DIEPCTL_CNAK_Pos)
#define USB_OTG_DIEPCTL_CNAK                     USB_OTG_DIEPCTL_CNAK_Msk
#define USB_OTG_DIEPCTL_SNAK_Pos                 (27U)
#define USB_OTG_DIEPCTL_SNAK_Msk                 (0x1UL << USB_OTG_DIEPCTL_SNAK_Pos)
#define USB_OTG_DIEPCTL_SNAK                     USB_OTG_DIEPCTL_SNAK_Msk
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Pos       (28U)
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Msk       (0x1UL << USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Pos)
#define USB_OTG_DIEPCTL_SD0PID_SEVNFRM           USB_OTG_DIEPCTL_SD0PID_SEVNFRM_Msk
#define USB_OTG_DIEPCTL_SODDFRM_Pos              (29U)
#define USB_OTG_DIEPCTL_SODDFRM_Msk              (0x1UL << USB_OTG_DIEPCTL_SODDFRM_Pos)
#define USB_OTG_DIEPCTL_SODDFRM                  USB_OTG_DIEPCTL_SODDFRM_Msk
#define USB_OTG_DIEPCTL_EPDIS_Pos                (30U)
#define USB_OTG_DIEPCTL_EPDIS_Msk                (0x1UL << USB_OTG_DIEPCTL_EPDIS_Pos)
#define USB_OTG_DIEPCTL_EPDIS                    USB_OTG_DIEPCTL_EPDIS_Msk
#define USB_OTG_DIEPCTL_EPENA_Pos                (31U)
#define USB_OTG_DIEPCTL_EPENA_Msk                (0x1UL << USB_OTG_DIEPCTL_EPENA_Pos)
#define USB_OTG_DIEPCTL_EPENA                    USB_OTG_DIEPCTL_EPENA_Msk

#define USB_OTG_HCCHAR_MPSIZ_Pos                 (0U)
#define USB_OTG_HCCHAR_MPSIZ_Msk                 (0x7FFUL << USB_OTG_HCCHAR_MPSIZ_Pos)
#define USB_OTG_HCCHAR_MPSIZ                     USB_OTG_HCCHAR_MPSIZ_Msk

#define USB_OTG_HCCHAR_EPNUM_Pos                 (11U)
#define USB_OTG_HCCHAR_EPNUM_Msk                 (0xFUL << USB_OTG_HCCHAR_EPNUM_Pos)
#define USB_OTG_HCCHAR_EPNUM                     USB_OTG_HCCHAR_EPNUM_Msk
#define USB_OTG_HCCHAR_EPNUM_0                   (0x1UL << USB_OTG_HCCHAR_EPNUM_Pos)
#define USB_OTG_HCCHAR_EPNUM_1                   (0x2UL << USB_OTG_HCCHAR_EPNUM_Pos)
#define USB_OTG_HCCHAR_EPNUM_2                   (0x4UL << USB_OTG_HCCHAR_EPNUM_Pos)
#define USB_OTG_HCCHAR_EPNUM_3                   (0x8UL << USB_OTG_HCCHAR_EPNUM_Pos)
#define USB_OTG_HCCHAR_EPDIR_Pos                 (15U)
#define USB_OTG_HCCHAR_EPDIR_Msk                 (0x1UL << USB_OTG_HCCHAR_EPDIR_Pos)
#define USB_OTG_HCCHAR_EPDIR                     USB_OTG_HCCHAR_EPDIR_Msk
#define USB_OTG_HCCHAR_LSDEV_Pos                 (17U)
#define USB_OTG_HCCHAR_LSDEV_Msk                 (0x1UL << USB_OTG_HCCHAR_LSDEV_Pos)
#define USB_OTG_HCCHAR_LSDEV                     USB_OTG_HCCHAR_LSDEV_Msk

#define USB_OTG_HCCHAR_EPTYP_Pos                 (18U)
#define USB_OTG_HCCHAR_EPTYP_Msk                 (0x3UL << USB_OTG_HCCHAR_EPTYP_Pos)
#define USB_OTG_HCCHAR_EPTYP                     USB_OTG_HCCHAR_EPTYP_Msk
#define USB_OTG_HCCHAR_EPTYP_0                   (0x1UL << USB_OTG_HCCHAR_EPTYP_Pos)
#define USB_OTG_HCCHAR_EPTYP_1                   (0x2UL << USB_OTG_HCCHAR_EPTYP_Pos)

#define USB_OTG_HCCHAR_MC_Pos                    (20U)
#define USB_OTG_HCCHAR_MC_Msk                    (0x3UL << USB_OTG_HCCHAR_MC_Pos)
#define USB_OTG_HCCHAR_MC                        USB_OTG_HCCHAR_MC_Msk
#define USB_OTG_HCCHAR_MC_0                      (0x1UL << USB_OTG_HCCHAR_MC_Pos)
#define USB_OTG_HCCHAR_MC_1                      (0x2UL << USB_OTG_HCCHAR_MC_Pos)

#define USB_OTG_HCCHAR_DAD_Pos                   (22U)
#define USB_OTG_HCCHAR_DAD_Msk                   (0x7FUL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD                       USB_OTG_HCCHAR_DAD_Msk
#define USB_OTG_HCCHAR_DAD_0                     (0x01UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_1                     (0x02UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_2                     (0x04UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_3                     (0x08UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_4                     (0x10UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_5                     (0x20UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_DAD_6                     (0x40UL << USB_OTG_HCCHAR_DAD_Pos)
#define USB_OTG_HCCHAR_ODDFRM_Pos                (29U)
#define USB_OTG_HCCHAR_ODDFRM_Msk                (0x1UL << USB_OTG_HCCHAR_ODDFRM_Pos)
#define USB_OTG_HCCHAR_ODDFRM                    USB_OTG_HCCHAR_ODDFRM_Msk
#define USB_OTG_HCCHAR_CHDIS_Pos                 (30U)
#define USB_OTG_HCCHAR_CHDIS_Msk                 (0x1UL << USB_OTG_HCCHAR_CHDIS_Pos)
#define USB_OTG_HCCHAR_CHDIS                     USB_OTG_HCCHAR_CHDIS_Msk
#define USB_OTG_HCCHAR_CHENA_Pos                 (31U)
#define USB_OTG_HCCHAR_CHENA_Msk                 (0x1UL << USB_OTG_HCCHAR_CHENA_Pos)
#define USB_OTG_HCCHAR_CHENA                     USB_OTG_HCCHAR_CHENA_Msk

#define USB_OTG_HCSPLT_PRTADDR_Pos               (0U)
#define USB_OTG_HCSPLT_PRTADDR_Msk               (0x7FUL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR                   USB_OTG_HCSPLT_PRTADDR_Msk
#define USB_OTG_HCSPLT_PRTADDR_0                 (0x01UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_1                 (0x02UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_2                 (0x04UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_3                 (0x08UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_4                 (0x10UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_5                 (0x20UL << USB_OTG_HCSPLT_PRTADDR_Pos)
#define USB_OTG_HCSPLT_PRTADDR_6                 (0x40UL << USB_OTG_HCSPLT_PRTADDR_Pos)

#define USB_OTG_HCSPLT_HUBADDR_Pos               (7U)
#define USB_OTG_HCSPLT_HUBADDR_Msk               (0x7FUL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR                   USB_OTG_HCSPLT_HUBADDR_Msk
#define USB_OTG_HCSPLT_HUBADDR_0                 (0x01UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_1                 (0x02UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_2                 (0x04UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_3                 (0x08UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_4                 (0x10UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_5                 (0x20UL << USB_OTG_HCSPLT_HUBADDR_Pos)
#define USB_OTG_HCSPLT_HUBADDR_6                 (0x40UL << USB_OTG_HCSPLT_HUBADDR_Pos)

#define USB_OTG_HCSPLT_XACTPOS_Pos               (14U)
#define USB_OTG_HCSPLT_XACTPOS_Msk               (0x3UL << USB_OTG_HCSPLT_XACTPOS_Pos)
#define USB_OTG_HCSPLT_XACTPOS                   USB_OTG_HCSPLT_XACTPOS_Msk
#define USB_OTG_HCSPLT_XACTPOS_0                 (0x1UL << USB_OTG_HCSPLT_XACTPOS_Pos)
#define USB_OTG_HCSPLT_XACTPOS_1                 (0x2UL << USB_OTG_HCSPLT_XACTPOS_Pos)
#define USB_OTG_HCSPLT_COMPLSPLT_Pos             (16U)
#define USB_OTG_HCSPLT_COMPLSPLT_Msk             (0x1UL << USB_OTG_HCSPLT_COMPLSPLT_Pos)
#define USB_OTG_HCSPLT_COMPLSPLT                 USB_OTG_HCSPLT_COMPLSPLT_Msk
#define USB_OTG_HCSPLT_SPLITEN_Pos               (31U)
#define USB_OTG_HCSPLT_SPLITEN_Msk               (0x1UL << USB_OTG_HCSPLT_SPLITEN_Pos)
#define USB_OTG_HCSPLT_SPLITEN                   USB_OTG_HCSPLT_SPLITEN_Msk

#define USB_OTG_HCINT_XFRC_Pos                   (0U)
#define USB_OTG_HCINT_XFRC_Msk                   (0x1UL << USB_OTG_HCINT_XFRC_Pos)
#define USB_OTG_HCINT_XFRC                       USB_OTG_HCINT_XFRC_Msk
#define USB_OTG_HCINT_CHH_Pos                    (1U)
#define USB_OTG_HCINT_CHH_Msk                    (0x1UL << USB_OTG_HCINT_CHH_Pos)
#define USB_OTG_HCINT_CHH                        USB_OTG_HCINT_CHH_Msk
#define USB_OTG_HCINT_AHBERR_Pos                 (2U)
#define USB_OTG_HCINT_AHBERR_Msk                 (0x1UL << USB_OTG_HCINT_AHBERR_Pos)
#define USB_OTG_HCINT_AHBERR                     USB_OTG_HCINT_AHBERR_Msk
#define USB_OTG_HCINT_STALL_Pos                  (3U)
#define USB_OTG_HCINT_STALL_Msk                  (0x1UL << USB_OTG_HCINT_STALL_Pos)
#define USB_OTG_HCINT_STALL                      USB_OTG_HCINT_STALL_Msk
#define USB_OTG_HCINT_NAK_Pos                    (4U)
#define USB_OTG_HCINT_NAK_Msk                    (0x1UL << USB_OTG_HCINT_NAK_Pos)
#define USB_OTG_HCINT_NAK                        USB_OTG_HCINT_NAK_Msk
#define USB_OTG_HCINT_ACK_Pos                    (5U)
#define USB_OTG_HCINT_ACK_Msk                    (0x1UL << USB_OTG_HCINT_ACK_Pos)
#define USB_OTG_HCINT_ACK                        USB_OTG_HCINT_ACK_Msk
#define USB_OTG_HCINT_NYET_Pos                   (6U)
#define USB_OTG_HCINT_NYET_Msk                   (0x1UL << USB_OTG_HCINT_NYET_Pos)
#define USB_OTG_HCINT_NYET                       USB_OTG_HCINT_NYET_Msk
#define USB_OTG_HCINT_TXERR_Pos                  (7U)
#define USB_OTG_HCINT_TXERR_Msk                  (0x1UL << USB_OTG_HCINT_TXERR_Pos)
#define USB_OTG_HCINT_TXERR                      USB_OTG_HCINT_TXERR_Msk
#define USB_OTG_HCINT_BBERR_Pos                  (8U)
#define USB_OTG_HCINT_BBERR_Msk                  (0x1UL << USB_OTG_HCINT_BBERR_Pos)
#define USB_OTG_HCINT_BBERR                      USB_OTG_HCINT_BBERR_Msk
#define USB_OTG_HCINT_FRMOR_Pos                  (9U)
#define USB_OTG_HCINT_FRMOR_Msk                  (0x1UL << USB_OTG_HCINT_FRMOR_Pos)
#define USB_OTG_HCINT_FRMOR                      USB_OTG_HCINT_FRMOR_Msk
#define USB_OTG_HCINT_DTERR_Pos                  (10U)
#define USB_OTG_HCINT_DTERR_Msk                  (0x1UL << USB_OTG_HCINT_DTERR_Pos)
#define USB_OTG_HCINT_DTERR                      USB_OTG_HCINT_DTERR_Msk

#define USB_OTG_DIEPINT_XFRC_Pos                 (0U)
#define USB_OTG_DIEPINT_XFRC_Msk                 (0x1UL << USB_OTG_DIEPINT_XFRC_Pos)
#define USB_OTG_DIEPINT_XFRC                     USB_OTG_DIEPINT_XFRC_Msk
#define USB_OTG_DIEPINT_EPDISD_Pos               (1U)
#define USB_OTG_DIEPINT_EPDISD_Msk               (0x1UL << USB_OTG_DIEPINT_EPDISD_Pos)
#define USB_OTG_DIEPINT_EPDISD                   USB_OTG_DIEPINT_EPDISD_Msk
#define USB_OTG_DIEPINT_AHBERR_Pos               (2U)
#define USB_OTG_DIEPINT_AHBERR_Msk               (0x1UL << USB_OTG_DIEPINT_AHBERR_Pos)
#define USB_OTG_DIEPINT_AHBERR                   USB_OTG_DIEPINT_AHBERR_Msk
#define USB_OTG_DIEPINT_TOC_Pos                  (3U)
#define USB_OTG_DIEPINT_TOC_Msk                  (0x1UL << USB_OTG_DIEPINT_TOC_Pos)
#define USB_OTG_DIEPINT_TOC                      USB_OTG_DIEPINT_TOC_Msk
#define USB_OTG_DIEPINT_ITTXFE_Pos               (4U)
#define USB_OTG_DIEPINT_ITTXFE_Msk               (0x1UL << USB_OTG_DIEPINT_ITTXFE_Pos)
#define USB_OTG_DIEPINT_ITTXFE                   USB_OTG_DIEPINT_ITTXFE_Msk
#define USB_OTG_DIEPINT_INEPNM_Pos               (5U)
#define USB_OTG_DIEPINT_INEPNM_Msk               (0x1UL << USB_OTG_DIEPINT_INEPNM_Pos)
#define USB_OTG_DIEPINT_INEPNM                   USB_OTG_DIEPINT_INEPNM_Msk
#define USB_OTG_DIEPINT_INEPNE_Pos               (6U)
#define USB_OTG_DIEPINT_INEPNE_Msk               (0x1UL << USB_OTG_DIEPINT_INEPNE_Pos)
#define USB_OTG_DIEPINT_INEPNE                   USB_OTG_DIEPINT_INEPNE_Msk
#define USB_OTG_DIEPINT_TXFE_Pos                 (7U)
#define USB_OTG_DIEPINT_TXFE_Msk                 (0x1UL << USB_OTG_DIEPINT_TXFE_Pos)
#define USB_OTG_DIEPINT_TXFE                     USB_OTG_DIEPINT_TXFE_Msk
#define USB_OTG_DIEPINT_TXFIFOUDRN_Pos           (8U)
#define USB_OTG_DIEPINT_TXFIFOUDRN_Msk           (0x1UL << USB_OTG_DIEPINT_TXFIFOUDRN_Pos)
#define USB_OTG_DIEPINT_TXFIFOUDRN               USB_OTG_DIEPINT_TXFIFOUDRN_Msk
#define USB_OTG_DIEPINT_BNA_Pos                  (9U)
#define USB_OTG_DIEPINT_BNA_Msk                  (0x1UL << USB_OTG_DIEPINT_BNA_Pos)
#define USB_OTG_DIEPINT_BNA                      USB_OTG_DIEPINT_BNA_Msk
#define USB_OTG_DIEPINT_PKTDRPSTS_Pos            (11U)
#define USB_OTG_DIEPINT_PKTDRPSTS_Msk            (0x1UL << USB_OTG_DIEPINT_PKTDRPSTS_Pos)
#define USB_OTG_DIEPINT_PKTDRPSTS                USB_OTG_DIEPINT_PKTDRPSTS_Msk
#define USB_OTG_DIEPINT_BERR_Pos                 (12U)
#define USB_OTG_DIEPINT_BERR_Msk                 (0x1UL << USB_OTG_DIEPINT_BERR_Pos)
#define USB_OTG_DIEPINT_BERR                     USB_OTG_DIEPINT_BERR_Msk
#define USB_OTG_DIEPINT_NAK_Pos                  (13U)
#define USB_OTG_DIEPINT_NAK_Msk                  (0x1UL << USB_OTG_DIEPINT_NAK_Pos)
#define USB_OTG_DIEPINT_NAK                      USB_OTG_DIEPINT_NAK_Msk

#define USB_OTG_HCINTMSK_XFRCM_Pos               (0U)
#define USB_OTG_HCINTMSK_XFRCM_Msk               (0x1UL << USB_OTG_HCINTMSK_XFRCM_Pos)
#define USB_OTG_HCINTMSK_XFRCM                   USB_OTG_HCINTMSK_XFRCM_Msk
#define USB_OTG_HCINTMSK_CHHM_Pos                (1U)
#define USB_OTG_HCINTMSK_CHHM_Msk                (0x1UL << USB_OTG_HCINTMSK_CHHM_Pos)
#define USB_OTG_HCINTMSK_CHHM                    USB_OTG_HCINTMSK_CHHM_Msk
#define USB_OTG_HCINTMSK_AHBERR_Pos              (2U)
#define USB_OTG_HCINTMSK_AHBERR_Msk              (0x1UL << USB_OTG_HCINTMSK_AHBERR_Pos)
#define USB_OTG_HCINTMSK_AHBERR                  USB_OTG_HCINTMSK_AHBERR_Msk
#define USB_OTG_HCINTMSK_STALLM_Pos              (3U)
#define USB_OTG_HCINTMSK_STALLM_Msk              (0x1UL << USB_OTG_HCINTMSK_STALLM_Pos)
#define USB_OTG_HCINTMSK_STALLM                  USB_OTG_HCINTMSK_STALLM_Msk
#define USB_OTG_HCINTMSK_NAKM_Pos                (4U)
#define USB_OTG_HCINTMSK_NAKM_Msk                (0x1UL << USB_OTG_HCINTMSK_NAKM_Pos)
#define USB_OTG_HCINTMSK_NAKM                    USB_OTG_HCINTMSK_NAKM_Msk
#define USB_OTG_HCINTMSK_ACKM_Pos                (5U)
#define USB_OTG_HCINTMSK_ACKM_Msk                (0x1UL << USB_OTG_HCINTMSK_ACKM_Pos)
#define USB_OTG_HCINTMSK_ACKM                    USB_OTG_HCINTMSK_ACKM_Msk
#define USB_OTG_HCINTMSK_NYET_Pos                (6U)
#define USB_OTG_HCINTMSK_NYET_Msk                (0x1UL << USB_OTG_HCINTMSK_NYET_Pos)
#define USB_OTG_HCINTMSK_NYET                    USB_OTG_HCINTMSK_NYET_Msk
#define USB_OTG_HCINTMSK_TXERRM_Pos              (7U)
#define USB_OTG_HCINTMSK_TXERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_TXERRM_Pos)
#define USB_OTG_HCINTMSK_TXERRM                  USB_OTG_HCINTMSK_TXERRM_Msk
#define USB_OTG_HCINTMSK_BBERRM_Pos              (8U)
#define USB_OTG_HCINTMSK_BBERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_BBERRM_Pos)
#define USB_OTG_HCINTMSK_BBERRM                  USB_OTG_HCINTMSK_BBERRM_Msk
#define USB_OTG_HCINTMSK_FRMORM_Pos              (9U)
#define USB_OTG_HCINTMSK_FRMORM_Msk              (0x1UL << USB_OTG_HCINTMSK_FRMORM_Pos)
#define USB_OTG_HCINTMSK_FRMORM                  USB_OTG_HCINTMSK_FRMORM_Msk
#define USB_OTG_HCINTMSK_DTERRM_Pos              (10U)
#define USB_OTG_HCINTMSK_DTERRM_Msk              (0x1UL << USB_OTG_HCINTMSK_DTERRM_Pos)
#define USB_OTG_HCINTMSK_DTERRM                  USB_OTG_HCINTMSK_DTERRM_Msk

#define USB_OTG_DIEPTSIZ_XFRSIZ_Pos              (0U)
#define USB_OTG_DIEPTSIZ_XFRSIZ_Msk              (0x7FFFFUL << USB_OTG_DIEPTSIZ_XFRSIZ_Pos)
#define USB_OTG_DIEPTSIZ_XFRSIZ                  USB_OTG_DIEPTSIZ_XFRSIZ_Msk
#define USB_OTG_DIEPTSIZ_PKTCNT_Pos              (19U)
#define USB_OTG_DIEPTSIZ_PKTCNT_Msk              (0x3FFUL << USB_OTG_DIEPTSIZ_PKTCNT_Pos)
#define USB_OTG_DIEPTSIZ_PKTCNT                  USB_OTG_DIEPTSIZ_PKTCNT_Msk
#define USB_OTG_DIEPTSIZ_MULCNT_Pos              (29U)
#define USB_OTG_DIEPTSIZ_MULCNT_Msk              (0x3UL << USB_OTG_DIEPTSIZ_MULCNT_Pos)
#define USB_OTG_DIEPTSIZ_MULCNT                  USB_OTG_DIEPTSIZ_MULCNT_Msk

#define USB_OTG_HCTSIZ_XFRSIZ_Pos                (0U)
#define USB_OTG_HCTSIZ_XFRSIZ_Msk                (0x7FFFFUL << USB_OTG_HCTSIZ_XFRSIZ_Pos)
#define USB_OTG_HCTSIZ_XFRSIZ                    USB_OTG_HCTSIZ_XFRSIZ_Msk
#define USB_OTG_HCTSIZ_PKTCNT_Pos                (19U)
#define USB_OTG_HCTSIZ_PKTCNT_Msk                (0x3FFUL << USB_OTG_HCTSIZ_PKTCNT_Pos)
#define USB_OTG_HCTSIZ_PKTCNT                    USB_OTG_HCTSIZ_PKTCNT_Msk
#define USB_OTG_HCTSIZ_DOPING_Pos                (31U)
#define USB_OTG_HCTSIZ_DOPING_Msk                (0x1UL << USB_OTG_HCTSIZ_DOPING_Pos)
#define USB_OTG_HCTSIZ_DOPING                    USB_OTG_HCTSIZ_DOPING_Msk
#define USB_OTG_HCTSIZ_DPID_Pos                  (29U)
#define USB_OTG_HCTSIZ_DPID_Msk                  (0x3UL << USB_OTG_HCTSIZ_DPID_Pos)
#define USB_OTG_HCTSIZ_DPID                      USB_OTG_HCTSIZ_DPID_Msk
#define USB_OTG_HCTSIZ_DPID_0                    (0x1UL << USB_OTG_HCTSIZ_DPID_Pos)
#define USB_OTG_HCTSIZ_DPID_1                    (0x2UL << USB_OTG_HCTSIZ_DPID_Pos)

#define USB_OTG_DIEPDMA_DMAADDR_Pos              (0U)
#define USB_OTG_DIEPDMA_DMAADDR_Msk              (0xFFFFFFFFUL << USB_OTG_DIEPDMA_DMAADDR_Pos)
#define USB_OTG_DIEPDMA_DMAADDR                  USB_OTG_DIEPDMA_DMAADDR_Msk

#define USB_OTG_HCDMA_DMAADDR_Pos                (0U)
#define USB_OTG_HCDMA_DMAADDR_Msk                (0xFFFFFFFFUL << USB_OTG_HCDMA_DMAADDR_Pos)
#define USB_OTG_HCDMA_DMAADDR                    USB_OTG_HCDMA_DMAADDR_Msk

#define USB_OTG_DTXFSTS_INEPTFSAV_Pos            (0U)
#define USB_OTG_DTXFSTS_INEPTFSAV_Msk            (0xFFFFUL << USB_OTG_DTXFSTS_INEPTFSAV_Pos)
#define USB_OTG_DTXFSTS_INEPTFSAV                USB_OTG_DTXFSTS_INEPTFSAV_Msk

#define USB_OTG_DIEPTXF_INEPTXSA_Pos             (0U)
#define USB_OTG_DIEPTXF_INEPTXSA_Msk             (0xFFFFUL << USB_OTG_DIEPTXF_INEPTXSA_Pos)
#define USB_OTG_DIEPTXF_INEPTXSA                 USB_OTG_DIEPTXF_INEPTXSA_Msk
#define USB_OTG_DIEPTXF_INEPTXFD_Pos             (16U)
#define USB_OTG_DIEPTXF_INEPTXFD_Msk             (0xFFFFUL << USB_OTG_DIEPTXF_INEPTXFD_Pos)
#define USB_OTG_DIEPTXF_INEPTXFD                 USB_OTG_DIEPTXF_INEPTXFD_Msk

#define USB_OTG_DOEPCTL_MPSIZ_Pos                (0U)
#define USB_OTG_DOEPCTL_MPSIZ_Msk                (0x7FFUL << USB_OTG_DOEPCTL_MPSIZ_Pos)
#define USB_OTG_DOEPCTL_MPSIZ                    USB_OTG_DOEPCTL_MPSIZ_Msk
#define USB_OTG_DOEPCTL_USBAEP_Pos               (15U)
#define USB_OTG_DOEPCTL_USBAEP_Msk               (0x1UL << USB_OTG_DOEPCTL_USBAEP_Pos)
#define USB_OTG_DOEPCTL_USBAEP                   USB_OTG_DOEPCTL_USBAEP_Msk
#define USB_OTG_DOEPCTL_NAKSTS_Pos               (17U)
#define USB_OTG_DOEPCTL_NAKSTS_Msk               (0x1UL << USB_OTG_DOEPCTL_NAKSTS_Pos)
#define USB_OTG_DOEPCTL_NAKSTS                   USB_OTG_DOEPCTL_NAKSTS_Msk
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Pos       (28U)
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Msk       (0x1UL << USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Pos)
#define USB_OTG_DOEPCTL_SD0PID_SEVNFRM           USB_OTG_DOEPCTL_SD0PID_SEVNFRM_Msk
#define USB_OTG_DOEPCTL_SODDFRM_Pos              (29U)
#define USB_OTG_DOEPCTL_SODDFRM_Msk              (0x1UL << USB_OTG_DOEPCTL_SODDFRM_Pos)
#define USB_OTG_DOEPCTL_SODDFRM                  USB_OTG_DOEPCTL_SODDFRM_Msk
#define USB_OTG_DOEPCTL_EPTYP_Pos                (18U)
#define USB_OTG_DOEPCTL_EPTYP_Msk                (0x3UL << USB_OTG_DOEPCTL_EPTYP_Pos)
#define USB_OTG_DOEPCTL_EPTYP                    USB_OTG_DOEPCTL_EPTYP_Msk
#define USB_OTG_DOEPCTL_EPTYP_0                  (0x1UL << USB_OTG_DOEPCTL_EPTYP_Pos)
#define USB_OTG_DOEPCTL_EPTYP_1                  (0x2UL << USB_OTG_DOEPCTL_EPTYP_Pos)
#define USB_OTG_DOEPCTL_SNPM_Pos                 (20U)
#define USB_OTG_DOEPCTL_SNPM_Msk                 (0x1UL << USB_OTG_DOEPCTL_SNPM_Pos)
#define USB_OTG_DOEPCTL_SNPM                     USB_OTG_DOEPCTL_SNPM_Msk
#define USB_OTG_DOEPCTL_STALL_Pos                (21U)
#define USB_OTG_DOEPCTL_STALL_Msk                (0x1UL << USB_OTG_DOEPCTL_STALL_Pos)
#define USB_OTG_DOEPCTL_STALL                    USB_OTG_DOEPCTL_STALL_Msk
#define USB_OTG_DOEPCTL_CNAK_Pos                 (26U)
#define USB_OTG_DOEPCTL_CNAK_Msk                 (0x1UL << USB_OTG_DOEPCTL_CNAK_Pos)
#define USB_OTG_DOEPCTL_CNAK                     USB_OTG_DOEPCTL_CNAK_Msk
#define USB_OTG_DOEPCTL_SNAK_Pos                 (27U)
#define USB_OTG_DOEPCTL_SNAK_Msk                 (0x1UL << USB_OTG_DOEPCTL_SNAK_Pos)
#define USB_OTG_DOEPCTL_SNAK                     USB_OTG_DOEPCTL_SNAK_Msk
#define USB_OTG_DOEPCTL_EPDIS_Pos                (30U)
#define USB_OTG_DOEPCTL_EPDIS_Msk                (0x1UL << USB_OTG_DOEPCTL_EPDIS_Pos)
#define USB_OTG_DOEPCTL_EPDIS                    USB_OTG_DOEPCTL_EPDIS_Msk
#define USB_OTG_DOEPCTL_EPENA_Pos                (31U)
#define USB_OTG_DOEPCTL_EPENA_Msk                (0x1UL << USB_OTG_DOEPCTL_EPENA_Pos)
#define USB_OTG_DOEPCTL_EPENA                    USB_OTG_DOEPCTL_EPENA_Msk

#define USB_OTG_DOEPINT_XFRC_Pos                 (0U)
#define USB_OTG_DOEPINT_XFRC_Msk                 (0x1UL << USB_OTG_DOEPINT_XFRC_Pos)
#define USB_OTG_DOEPINT_XFRC                     USB_OTG_DOEPINT_XFRC_Msk
#define USB_OTG_DOEPINT_EPDISD_Pos               (1U)
#define USB_OTG_DOEPINT_EPDISD_Msk               (0x1UL << USB_OTG_DOEPINT_EPDISD_Pos)
#define USB_OTG_DOEPINT_EPDISD                   USB_OTG_DOEPINT_EPDISD_Msk
#define USB_OTG_DOEPINT_AHBERR_Pos               (2U)
#define USB_OTG_DOEPINT_AHBERR_Msk               (0x1UL << USB_OTG_DOEPINT_AHBERR_Pos)
#define USB_OTG_DOEPINT_AHBERR                   USB_OTG_DOEPINT_AHBERR_Msk
#define USB_OTG_DOEPINT_STUP_Pos                 (3U)
#define USB_OTG_DOEPINT_STUP_Msk                 (0x1UL << USB_OTG_DOEPINT_STUP_Pos)
#define USB_OTG_DOEPINT_STUP                     USB_OTG_DOEPINT_STUP_Msk
#define USB_OTG_DOEPINT_OTEPDIS_Pos              (4U)
#define USB_OTG_DOEPINT_OTEPDIS_Msk              (0x1UL << USB_OTG_DOEPINT_OTEPDIS_Pos)
#define USB_OTG_DOEPINT_OTEPDIS                  USB_OTG_DOEPINT_OTEPDIS_Msk
#define USB_OTG_DOEPINT_OTEPSPR_Pos              (5U)
#define USB_OTG_DOEPINT_OTEPSPR_Msk              (0x1UL << USB_OTG_DOEPINT_OTEPSPR_Pos)
#define USB_OTG_DOEPINT_OTEPSPR                  USB_OTG_DOEPINT_OTEPSPR_Msk
#define USB_OTG_DOEPINT_B2BSTUP_Pos              (6U)
#define USB_OTG_DOEPINT_B2BSTUP_Msk              (0x1UL << USB_OTG_DOEPINT_B2BSTUP_Pos)
#define USB_OTG_DOEPINT_B2BSTUP                  USB_OTG_DOEPINT_B2BSTUP_Msk
#define USB_OTG_DOEPINT_OUTPKTERR_Pos            (8U)
#define USB_OTG_DOEPINT_OUTPKTERR_Msk            (0x1UL << USB_OTG_DOEPINT_OUTPKTERR_Pos)
#define USB_OTG_DOEPINT_OUTPKTERR                USB_OTG_DOEPINT_OUTPKTERR_Msk
#define USB_OTG_DOEPINT_NAK_Pos                  (13U)
#define USB_OTG_DOEPINT_NAK_Msk                  (0x1UL << USB_OTG_DOEPINT_NAK_Pos)
#define USB_OTG_DOEPINT_NAK                      USB_OTG_DOEPINT_NAK_Msk
#define USB_OTG_DOEPINT_NYET_Pos                 (14U)
#define USB_OTG_DOEPINT_NYET_Msk                 (0x1UL << USB_OTG_DOEPINT_NYET_Pos)
#define USB_OTG_DOEPINT_NYET                     USB_OTG_DOEPINT_NYET_Msk
#define USB_OTG_DOEPINT_STPKTRX_Pos              (15U)
#define USB_OTG_DOEPINT_STPKTRX_Msk              (0x1UL << USB_OTG_DOEPINT_STPKTRX_Pos)
#define USB_OTG_DOEPINT_STPKTRX                  USB_OTG_DOEPINT_STPKTRX_Msk

#define USB_OTG_DOEPTSIZ_XFRSIZ_Pos              (0U)
#define USB_OTG_DOEPTSIZ_XFRSIZ_Msk              (0x7FFFFUL << USB_OTG_DOEPTSIZ_XFRSIZ_Pos)
#define USB_OTG_DOEPTSIZ_XFRSIZ                  USB_OTG_DOEPTSIZ_XFRSIZ_Msk
#define USB_OTG_DOEPTSIZ_PKTCNT_Pos              (19U)
#define USB_OTG_DOEPTSIZ_PKTCNT_Msk              (0x3FFUL << USB_OTG_DOEPTSIZ_PKTCNT_Pos)
#define USB_OTG_DOEPTSIZ_PKTCNT                  USB_OTG_DOEPTSIZ_PKTCNT_Msk

#define USB_OTG_DOEPTSIZ_STUPCNT_Pos             (29U)
#define USB_OTG_DOEPTSIZ_STUPCNT_Msk             (0x3UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos)
#define USB_OTG_DOEPTSIZ_STUPCNT                 USB_OTG_DOEPTSIZ_STUPCNT_Msk
#define USB_OTG_DOEPTSIZ_STUPCNT_0               (0x1UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos)
#define USB_OTG_DOEPTSIZ_STUPCNT_1               (0x2UL << USB_OTG_DOEPTSIZ_STUPCNT_Pos)

#define USB_OTG_PCGCCTL_STOPCLK_Pos              (0U)
#define USB_OTG_PCGCCTL_STOPCLK_Msk              (0x1UL << USB_OTG_PCGCCTL_STOPCLK_Pos)
#define USB_OTG_PCGCCTL_STOPCLK                  USB_OTG_PCGCCTL_STOPCLK_Msk
#define USB_OTG_PCGCCTL_GATECLK_Pos              (1U)
#define USB_OTG_PCGCCTL_GATECLK_Msk              (0x1UL << USB_OTG_PCGCCTL_GATECLK_Pos)
#define USB_OTG_PCGCCTL_GATECLK                  USB_OTG_PCGCCTL_GATECLK_Msk
#define USB_OTG_PCGCCTL_PHYSUSP_Pos              (4U)
#define USB_OTG_PCGCCTL_PHYSUSP_Msk              (0x1UL << USB_OTG_PCGCCTL_PHYSUSP_Pos)
#define USB_OTG_PCGCCTL_PHYSUSP                  USB_OTG_PCGCCTL_PHYSUSP_Msk

#define USB_OTG_CHNUM_Pos                        (0U)
#define USB_OTG_CHNUM_Msk                        (0xFUL << USB_OTG_CHNUM_Pos)
#define USB_OTG_CHNUM                            USB_OTG_CHNUM_Msk
#define USB_OTG_CHNUM_0                          (0x1UL << USB_OTG_CHNUM_Pos)
#define USB_OTG_CHNUM_1                          (0x2UL << USB_OTG_CHNUM_Pos)
#define USB_OTG_CHNUM_2                          (0x4UL << USB_OTG_CHNUM_Pos)
#define USB_OTG_CHNUM_3                          (0x8UL << USB_OTG_CHNUM_Pos)
#define USB_OTG_BCNT_Pos                         (4U)
#define USB_OTG_BCNT_Msk                         (0x7FFUL << USB_OTG_BCNT_Pos)
#define USB_OTG_BCNT                             USB_OTG_BCNT_Msk

#define USB_OTG_DPID_Pos                         (15U)
#define USB_OTG_DPID_Msk                         (0x3UL << USB_OTG_DPID_Pos)
#define USB_OTG_DPID                             USB_OTG_DPID_Msk
#define USB_OTG_DPID_0                           (0x1UL << USB_OTG_DPID_Pos)
#define USB_OTG_DPID_1                           (0x2UL << USB_OTG_DPID_Pos)

#define USB_OTG_PKTSTS_Pos                       (17U)
#define USB_OTG_PKTSTS_Msk                       (0xFUL << USB_OTG_PKTSTS_Pos)
#define USB_OTG_PKTSTS                           USB_OTG_PKTSTS_Msk
#define USB_OTG_PKTSTS_0                         (0x1UL << USB_OTG_PKTSTS_Pos)
#define USB_OTG_PKTSTS_1                         (0x2UL << USB_OTG_PKTSTS_Pos)
#define USB_OTG_PKTSTS_2                         (0x4UL << USB_OTG_PKTSTS_Pos)
#define USB_OTG_PKTSTS_3                         (0x8UL << USB_OTG_PKTSTS_Pos)

#define USB_OTG_EPNUM_Pos                        (0U)
#define USB_OTG_EPNUM_Msk                        (0xFUL << USB_OTG_EPNUM_Pos)
#define USB_OTG_EPNUM                            USB_OTG_EPNUM_Msk
#define USB_OTG_EPNUM_0                          (0x1UL << USB_OTG_EPNUM_Pos)
#define USB_OTG_EPNUM_1                          (0x2UL << USB_OTG_EPNUM_Pos)
#define USB_OTG_EPNUM_2                          (0x4UL << USB_OTG_EPNUM_Pos)
#define USB_OTG_EPNUM_3                          (0x8UL << USB_OTG_EPNUM_Pos)

#define USB_OTG_FRMNUM_Pos                       (21U)
#define USB_OTG_FRMNUM_Msk                       (0xFUL << USB_OTG_FRMNUM_Pos)
#define USB_OTG_FRMNUM                           USB_OTG_FRMNUM_Msk
#define USB_OTG_FRMNUM_0                         (0x1UL << USB_OTG_FRMNUM_Pos)
#define USB_OTG_FRMNUM_1                         (0x2UL << USB_OTG_FRMNUM_Pos)
#define USB_OTG_FRMNUM_2                         (0x4UL << USB_OTG_FRMNUM_Pos)
#define USB_OTG_FRMNUM_3                         (0x8UL << USB_OTG_FRMNUM_Pos)

#define IS_ADC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

#define IS_ADC_COMMON_INSTANCE(INSTANCE) ((INSTANCE) == ADC1_COMMON)

#define IS_CRC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CRC)

#define IS_DMA_STREAM_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA1_Stream0) || \
                                              ((INSTANCE) == DMA1_Stream1) || \
                                              ((INSTANCE) == DMA1_Stream2) || \
                                              ((INSTANCE) == DMA1_Stream3) || \
                                              ((INSTANCE) == DMA1_Stream4) || \
                                              ((INSTANCE) == DMA1_Stream5) || \
                                              ((INSTANCE) == DMA1_Stream6) || \
                                              ((INSTANCE) == DMA1_Stream7) || \
                                              ((INSTANCE) == DMA2_Stream0) || \
                                              ((INSTANCE) == DMA2_Stream1) || \
                                              ((INSTANCE) == DMA2_Stream2) || \
                                              ((INSTANCE) == DMA2_Stream3) || \
                                              ((INSTANCE) == DMA2_Stream4) || \
                                              ((INSTANCE) == DMA2_Stream5) || \
                                              ((INSTANCE) == DMA2_Stream6) || \
                                              ((INSTANCE) == DMA2_Stream7))

#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD) || \
                                        ((INSTANCE) == GPIOE) || \
                                        ((INSTANCE) == GPIOH))

#define IS_I2C_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2C1) || \
                                       ((INSTANCE) == I2C2) || \
                                       ((INSTANCE) == I2C3))

#define IS_SMBUS_ALL_INSTANCE         IS_I2C_ALL_INSTANCE

#define IS_I2S_ALL_INSTANCE(INSTANCE)  (((INSTANCE) == SPI2) || \
                                       ((INSTANCE) == SPI3))

#define IS_I2S_EXT_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2S2ext)|| \
                                           ((INSTANCE) == I2S3ext))

#define IS_I2S_ALL_INSTANCE_EXT    IS_I2S_EXT_ALL_INSTANCE

#define IS_RTC_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == RTC)

#define IS_SPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2) || \
                                       ((INSTANCE) == SPI3) || \
                                       ((INSTANCE) == SPI4))

#define IS_TIM_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                   ((INSTANCE) == TIM2)   || \
                                   ((INSTANCE) == TIM3)   || \
                                   ((INSTANCE) == TIM4)   || \
                                   ((INSTANCE) == TIM5)   || \
                                   ((INSTANCE) == TIM9)   || \
                                   ((INSTANCE) == TIM10)  || \
                                   ((INSTANCE) == TIM11))

#define IS_TIM_CC1_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)  || \
                                         ((INSTANCE) == TIM2)  || \
                                         ((INSTANCE) == TIM3)  || \
                                         ((INSTANCE) == TIM4)  || \
                                         ((INSTANCE) == TIM5)  || \
                                         ((INSTANCE) == TIM9)  || \
                                         ((INSTANCE) == TIM10) || \
                                         ((INSTANCE) == TIM11))

#define IS_TIM_CC2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                       ((INSTANCE) == TIM2) || \
                                       ((INSTANCE) == TIM3) || \
                                       ((INSTANCE) == TIM4) || \
                                       ((INSTANCE) == TIM5) || \
                                       ((INSTANCE) == TIM9))

#define IS_TIM_CC3_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1) || \
                                         ((INSTANCE) == TIM2) || \
                                         ((INSTANCE) == TIM3) || \
                                         ((INSTANCE) == TIM4) || \
                                         ((INSTANCE) == TIM5))

#define IS_TIM_CC4_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                       ((INSTANCE) == TIM2) || \
                                       ((INSTANCE) == TIM3) || \
                                       ((INSTANCE) == TIM4) || \
                                       ((INSTANCE) == TIM5))

#define IS_TIM_ADVANCED_INSTANCE(INSTANCE) ((INSTANCE) == TIM1)

#define IS_TIM_XOR_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1) || \
                                         ((INSTANCE) == TIM2) || \
                                         ((INSTANCE) == TIM3) || \
                                         ((INSTANCE) == TIM4) || \
                                         ((INSTANCE) == TIM5))

#define IS_TIM_DMA_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                       ((INSTANCE) == TIM2) || \
                                       ((INSTANCE) == TIM3) || \
                                       ((INSTANCE) == TIM4) || \
                                       ((INSTANCE) == TIM5))

#define IS_TIM_DMA_CC_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                          ((INSTANCE) == TIM2) || \
                                          ((INSTANCE) == TIM3) || \
                                          ((INSTANCE) == TIM4) || \
                                          ((INSTANCE) == TIM5))

#define IS_TIM_CCDMA_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                          ((INSTANCE) == TIM2) || \
                                          ((INSTANCE) == TIM3) || \
                                          ((INSTANCE) == TIM4) || \
                                          ((INSTANCE) == TIM5))

#define IS_TIM_DMABURST_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                             ((INSTANCE) == TIM2) || \
                                             ((INSTANCE) == TIM3) || \
                                             ((INSTANCE) == TIM4) || \
                                             ((INSTANCE) == TIM5))

#define IS_TIM_MASTER_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                          ((INSTANCE) == TIM2) || \
                                          ((INSTANCE) == TIM3) || \
                                          ((INSTANCE) == TIM4) || \
                                          ((INSTANCE) == TIM5))

#define IS_TIM_SLAVE_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                         ((INSTANCE) == TIM2) || \
                                         ((INSTANCE) == TIM3) || \
                                         ((INSTANCE) == TIM4) || \
                                         ((INSTANCE) == TIM5) || \
                                         ((INSTANCE) == TIM9))

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE)(((INSTANCE) == TIM2) || \
                                              ((INSTANCE) == TIM5))

#define IS_TIM_ETR_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                        ((INSTANCE) == TIM2) || \
                                        ((INSTANCE) == TIM3) || \
                                        ((INSTANCE) == TIM4) || \
                                        ((INSTANCE) == TIM5))

#define IS_TIM_REMAP_INSTANCE(INSTANCE) (((INSTANCE) == TIM2)  || \
                                         ((INSTANCE) == TIM5)  || \
                                         ((INSTANCE) == TIM11))

#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
    ((((INSTANCE) == TIM1) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == TIM2) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == TIM3) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == TIM4) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == TIM5) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
    ||                                         \
    (((INSTANCE) == TIM9) &&                   \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2)))           \
    ||                                         \
    (((INSTANCE) == TIM10) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1)))           \
    ||                                         \
    (((INSTANCE) == TIM11) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1))))

#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == TIM1) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3))))

#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM5))

#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                  ((INSTANCE) == TIM2)   || \
                                                  ((INSTANCE) == TIM3)   || \
                                                  ((INSTANCE) == TIM4)   || \
                                                  ((INSTANCE) == TIM5)   || \
                                                  ((INSTANCE) == TIM9)   || \
                                                  ((INSTANCE) == TIM10)  || \
                                                  ((INSTANCE) == TIM11))

#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) ((INSTANCE) == TIM1)

#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)        (((INSTANCE) == TIM1) || \
                                                       ((INSTANCE) == TIM2) || \
                                                       ((INSTANCE) == TIM3) || \
                                                       ((INSTANCE) == TIM4) || \
                                                       ((INSTANCE) == TIM5))

#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM5) || \
                                                        ((INSTANCE) == TIM9))

#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)|| \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM5))

#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM5) || \
                                                        ((INSTANCE) == TIM9))

#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)     (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM5) || \
                                                        ((INSTANCE) == TIM9))

#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1))

#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                                      ((INSTANCE) == TIM2) || \
                                                      ((INSTANCE) == TIM3) || \
                                                      ((INSTANCE) == TIM4) || \
                                                      ((INSTANCE) == TIM5) || \
                                                      ((INSTANCE) == TIM9))

#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                                          ((INSTANCE) == TIM2) || \
                                                          ((INSTANCE) == TIM3) || \
                                                          ((INSTANCE) == TIM4) || \
                                                          ((INSTANCE) == TIM5))

#define IS_TIM_BREAK_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1))

#define IS_USART_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                     ((INSTANCE) == USART2) || \
                                     ((INSTANCE) == USART6))

#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                               ((INSTANCE) == USART2) || \
                                               ((INSTANCE) == USART6))

#define IS_UART_INSTANCE          IS_UART_HALFDUPLEX_INSTANCE

#define IS_UART_HWFLOW_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                           ((INSTANCE) == USART2) || \
                                           ((INSTANCE) == USART6))

#define IS_UART_LIN_INSTANCE          IS_UART_HALFDUPLEX_INSTANCE

#define IS_SMARTCARD_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                         ((INSTANCE) == USART2) || \
                                         ((INSTANCE) == USART6))

#define IS_IRDA_INSTANCE(INSTANCE) (((INSTANCE) == USART1) || \
                                    ((INSTANCE) == USART2) || \
                                    ((INSTANCE) == USART6))

#define IS_PCD_ALL_INSTANCE(INSTANCE) (((INSTANCE) == USB_OTG_FS))

#define IS_HCD_ALL_INSTANCE(INSTANCE) (((INSTANCE) == USB_OTG_FS))

#define IS_SDIO_ALL_INSTANCE(INSTANCE) ((INSTANCE) == SDIO)

#define IS_IWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == IWDG)

#define IS_WWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == WWDG)

#define USB_OTG_FS_HOST_MAX_CHANNEL_NBR                8U
#define USB_OTG_FS_MAX_IN_ENDPOINTS                    4U
#define USB_OTG_FS_MAX_OUT_ENDPOINTS                   4U
#define USB_OTG_FS_TOTAL_FIFO_SIZE                     1280U

#define RCC_PLLCFGR_RST_VALUE              0x24003010U
#define RCC_PLLI2SCFGR_RST_VALUE           0x20003000U

#define RCC_MAX_FREQUENCY            84000000U
#define RCC_MAX_FREQUENCY_SCALE3     60000000U
#define RCC_MAX_FREQUENCY_SCALE2    RCC_MAX_FREQUENCY
#define RCC_PLLVCO_OUTPUT_MIN       192000000U
#define RCC_PLLVCO_INPUT_MIN           950000U
#define RCC_PLLVCO_INPUT_MAX          2100000U
#define RCC_PLLVCO_OUTPUT_MAX       432000000U

#define RCC_PLLN_MIN_VALUE                192U
#define RCC_PLLN_MAX_VALUE                432U

#define FLASH_SCALE2_LATENCY1_FREQ    30000000U
#define FLASH_SCALE2_LATENCY2_FREQ    60000000U

#define FLASH_SCALE3_LATENCY1_FREQ    30000000U
#define FLASH_SCALE3_LATENCY2_FREQ    60000000U

#ifdef __cplusplus
}
#endif

#endif
