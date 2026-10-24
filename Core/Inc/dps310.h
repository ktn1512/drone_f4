/* DPS310: cam bien ap suat + nhiet do I2C, do cao tuong doi (m).
 * Ket noi: I2C2 PB10=SCL, PB3=SDA trong drone_f4/ver0.1.
 * Driver chi doc cam bien, KHONG dieu khien motor/PID.
 */
#ifndef DPS310_H
#define DPS310_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define DPS310_SAMPLE_HOME_COUNT 64U   /* 64 mau dau (khoang 2 s) lam moc do cao */

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint16_t address;                /* Dia chi 7-bit da dich trai 1 cho STM32 HAL */
    uint8_t initialized;
    uint8_t valid;
    uint8_t home_valid;

    int32_t c0, c1, c00, c10, c01, c11, c20, c21, c30;
    float pressure_pa;              /* Ap suat da bu nhiet (Pa) */
    float pressure_filtered_pa;     /* Ap suat sau low-pass (Pa) */
    float temperature_c;            /* Nhiet do (do C) */
    float altitude_isa_m;           /* Do cao xap xi theo khi quyen chuan (m) */
    float altitude_rel_m;           /* Do cao so voi luc lay moc (m) */
    float home_pressure_pa;
    float home_pressure_sum;
    uint16_t home_samples;
    uint32_t last_update_ms;
    uint32_t sample_count;
    uint32_t error_count;
} DPS310_t;

/* Tu dong tim dia chi I2C 0x77/0x76; reset, doc he so calibration,
 * PRS: 32 Hz, 8x; TMP: 4 Hz, 1x; background P+T.
 * Chi goi mot lan khi khoi dong; co HAL_Delay trong Init.
 */
HAL_StatusTypeDef DPS310_Init(DPS310_t *dev, I2C_HandleTypeDef *hi2c);

/* Khong HAL_Delay. HAL_OK: co mau ap suat moi; HAL_BUSY: chua co mau;
 * HAL_ERROR/HAL_TIMEOUT: giao dich/doc khong hop le.
 */
HAL_StatusTypeDef DPS310_ReadIfReady(DPS310_t *dev);

/* Lay lai moc ap suat khi drone dang dung yen, motor chua quay.
 * Sau 64 mau hop le, home_valid = 1.
 */
void DPS310_ResetHome(DPS310_t *dev);

#endif /* DPS310_H */
