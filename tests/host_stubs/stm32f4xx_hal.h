/* Stub HAL toi thieu de bien dich drone_link.c tren may tinh (chi cho test). */
#ifndef HOST_STUB_STM32F4XX_HAL_H
#define HOST_STUB_STM32F4XX_HAL_H
#include <stdint.h>
#include <stddef.h>
typedef enum { HAL_OK = 0, HAL_ERROR, HAL_BUSY, HAL_TIMEOUT } HAL_StatusTypeDef;
typedef enum { HAL_UART_STATE_READY = 0x20U, HAL_UART_STATE_BUSY_TX = 0x21U } HAL_UART_StateTypeDef;
typedef struct { uint32_t BaudRate; } UART_InitTypeDef;
typedef struct { void *Instance; UART_InitTypeDef Init; volatile HAL_UART_StateTypeDef gState, RxState; void *hdmatx; } UART_HandleTypeDef;
typedef struct { void *Instance; } TIM_HandleTypeDef;
uint32_t HAL_GetTick(void);
#endif
