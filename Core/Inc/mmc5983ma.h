/* MMC5983MA: driver từ kế I2C, raw 18-bit và giá trị từ trường (gauss). */
#pragma once
#ifndef MMC5983MA_H
#define MMC5983MA_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define MMC5983_I2C_ADDR (0x30 << 1) // Địa chỉ 7-bit 0x30, dịch thành 0x60 để dùng STM32 HAL.

#define MMC5983_WHOAMI 0x30 // PRODUCT_ID mong đợi = 0x30.

typedef struct
{

	I2C_HandleTypeDef *hi2c; // Handle I2C phải gán trước khi Init.

	int32_t raw_x; // Raw X 18-bit, dạng offset binary.

	int32_t raw_y; // Raw Y 18-bit, dạng offset binary.

	int32_t raw_z; // Raw Z 18-bit, dạng offset binary.

	float mag_x; // Từ trường X, đơn vị gauss (G).

	float mag_y; // Từ trường Y, đơn vị gauss (G).

	float mag_z; // Từ trường Z, đơn vị gauss (G).

} MMC5983MA_t;

/* Kiểm tra ID, SET/RESET và chế độ single-shot. */
HAL_StatusTypeDef MMC5983_Init(MMC5983MA_t *dev);

/* Đọc PRODUCT_ID. */
uint8_t MMC5983_WhoAmI(MMC5983MA_t *dev);

/* Đo và lấy raw XYZ 18-bit (có chờ). */
HAL_StatusTypeDef MMC5983_ReadRaw(
	MMC5983MA_t *dev,
	int32_t *x,
	int32_t *y,
	int32_t *z);

/* Đổi raw sang G, 1 G = 100 µT. */
HAL_StatusTypeDef MMC5983_ReadMag(
	MMC5983MA_t *dev,
	float *x,
	float *y,
	float *z);

/* Kích phép đo single-shot không chờ. */
HAL_StatusTypeDef MMC5983_StartMeasurement(MMC5983MA_t *dev);

/* Nếu DONE=1 lấy kết quả; chưa có trả HAL_BUSY. */
HAL_StatusTypeDef MMC5983_ReadMagIfReady(MMC5983MA_t *dev,
                                         float *x, float *y, float *z);

#endif
