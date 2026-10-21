#pragma once
#ifndef MMC5983MA_H
#define MMC5983MA_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define MMC5983_I2C_ADDR (0x30 << 1)

#define MMC5983_WHOAMI 0x30

typedef struct
{

	I2C_HandleTypeDef *hi2c;

	int32_t raw_x;

	int32_t raw_y;

	int32_t raw_z;

	float mag_x;

	float mag_y;

	float mag_z;

} MMC5983MA_t;

HAL_StatusTypeDef MMC5983_Init(MMC5983MA_t *dev);

uint8_t MMC5983_WhoAmI(MMC5983MA_t *dev);

HAL_StatusTypeDef MMC5983_ReadRaw(
	MMC5983MA_t *dev,
	int32_t *x,
	int32_t *y,
	int32_t *z);

HAL_StatusTypeDef MMC5983_ReadMag(
	MMC5983MA_t *dev,
	float *x,
	float *y,
	float *z);

HAL_StatusTypeDef MMC5983_StartMeasurement(MMC5983MA_t *dev);

HAL_StatusTypeDef MMC5983_ReadMagIfReady(MMC5983MA_t *dev,
                                         float *x, float *y, float *z);

#endif
