#ifndef __SYSTEM_STM32F4XX_H
#define __SYSTEM_STM32F4XX_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;

extern const uint8_t  AHBPrescTable[16];
extern const uint8_t  APBPrescTable[8];

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif
