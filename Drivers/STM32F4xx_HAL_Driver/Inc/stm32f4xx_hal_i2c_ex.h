#ifndef __STM32F4xx_HAL_I2C_EX_H
#define __STM32F4xx_HAL_I2C_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#if  defined(I2C_FLTR_ANOFF)&&defined(I2C_FLTR_DNF)

#include "stm32f4xx_hal_def.h"

#define I2C_ANALOGFILTER_ENABLE        0x00000000U
#define I2C_ANALOGFILTER_DISABLE       I2C_FLTR_ANOFF

HAL_StatusTypeDef HAL_I2CEx_ConfigAnalogFilter(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter);
HAL_StatusTypeDef HAL_I2CEx_ConfigDigitalFilter(I2C_HandleTypeDef *hi2c, uint32_t DigitalFilter);

#define IS_I2C_ANALOG_FILTER(FILTER) (((FILTER) == I2C_ANALOGFILTER_ENABLE) || \
                                      ((FILTER) == I2C_ANALOGFILTER_DISABLE))
#define IS_I2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000FU)

#endif

#ifdef __cplusplus
}
#endif

#endif
