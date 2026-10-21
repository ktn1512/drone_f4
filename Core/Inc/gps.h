#ifndef GPS_H
#define GPS_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

typedef struct
{

	double latitude;

	double longitude;

	float speed_kmh;

	float speed_ms;

	float course;

	uint8_t fix;

	uint8_t satellites;

} GPS_Data_t;

HAL_StatusTypeDef GPS_Init(UART_HandleTypeDef *huart);

void GPS_RxCallback(uint8_t data);

void GPS_Process(void);

GPS_Data_t *GPS_GetData(void);

#endif
