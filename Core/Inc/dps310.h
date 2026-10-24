/* DPS310 SPI 4-wire: pressure, temperature and relative altitude.
 * STM32F401 drone_f4/ver0.1: SPI2 PB13=SCK PB14=MISO PB15=MOSI; PB12=CS.
 * SPI MODE 3: CPOL=1, CPHA=1. No motor/PID changes in this driver.
 */
#ifndef DPS310_H
#define DPS310_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define DPS310_SAMPLE_HOME_COUNT 64U /* ~2 s at 32 Hz with drone stationary */

typedef struct {
    SPI_HandleTypeDef *hspi;      /* SPI peripheral, configured for Mode 3 */
    GPIO_TypeDef *cs_port;        /* CS pin GPIO port */
    uint16_t cs_pin;              /* CS pin GPIO mask */
    uint8_t initialized;
    uint8_t valid;
    uint8_t home_valid;

    /* Factory calibration coefficients, sign extended to 32-bit. */
    int32_t c0, c1, c00, c10, c01, c11, c20, c21, c30;

    float pressure_pa;            /* Compensated pressure (Pa) */
    float pressure_filtered_pa;   /* First-order filtered pressure (Pa) */
    float temperature_c;          /* Compensated temperature (deg C) */
    float altitude_isa_m;         /* ISA altitude, P0=101325 Pa (m) */
    float altitude_rel_m;         /* Relative to averaged home pressure (m) */
    float home_pressure_pa;       /* Home reference pressure (Pa) */
    float home_pressure_sum;
    uint16_t home_samples;
    uint32_t last_update_ms;      /* Tick of last NEW pressure sample */
    uint32_t last_poll_ms;
    uint32_t sample_count;
    uint32_t error_count;
} DPS310_t;

/* Boot DPS310, read coefficients, start background P/T measurement.
 * Pressure 32 Hz, 8x oversampling; temperature 4 Hz, 1x.
 * Uses HAL_Delay only during initialization. Caller must configure SPI Mode 3.
 */
HAL_StatusTypeDef DPS310_Init(DPS310_t *dev,
                              SPI_HandleTypeDef *hspi,
                              GPIO_TypeDef *cs_port,
                              uint16_t cs_pin);

/* Non-delaying, poll at most once / 5 ms.
 * HAL_OK = new sample; HAL_BUSY = no new data; others = bus/format error.
 * Uses blocking HAL SPI transactions with short (2 ms) timeout; avoid
 * invoking from interrupts. Read preferably outside time-critical control.
 */
HAL_StatusTypeDef DPS310_ReadIfReady(DPS310_t *dev);

/* Reset altitude zero; next 64 readings are averaged as home pressure.
 * Reset only while motors are stopped and drone is stationary.
 */
void DPS310_ResetHome(DPS310_t *dev);

#endif /* DPS310_H */
