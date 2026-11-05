#ifndef GPS_H
#define GPS_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

/* Coordinates are WGS84 decimal degrees; speed is ground speed. */
typedef struct
{
    double latitude;
    double longitude;
    float speed_kmh;
    float speed_ms;
    float course;             /* GPS course over ground, degrees, NOT compass yaw. */
    uint8_t fix;              /* RMC data valid and not stale. */
    uint8_t satellites;       /* From GGA, 0 when not reported. */
    uint32_t last_update_ms;  /* Timestamp of latest valid RMC. */
    uint32_t valid_rmc_count;
    uint32_t bad_nmea_count;
    uint32_t rx_overflow_count;
    uint32_t uart_error_count;
} GPS_Data_t;

/* Call once with the already configured USART1, 38400 8N1. */
HAL_StatusTypeDef GPS_Init(UART_HandleTypeDef *huart);

/* Fast RX interrupt handling. Call GPS_RxCpltCallback on USART1 RX complete. */
void GPS_RxCallback(uint8_t data);
void GPS_RxCpltCallback(void);
void GPS_ErrorCallback(void);

/* Call frequently from main loop (not from an interrupt). */
void GPS_Process(void);
GPS_Data_t *GPS_GetData(void);

#endif /* GPS_H */
