/* DPS310 Infineon: STM32 HAL I2C, calibration 0x10..0x21.
 * He so/bit thanh ghi theo Infineon DPS310 datasheet V1.2.
 */
#include "dps310.h"
#include <math.h>
#include <string.h>

#define DPS310_REG_PRS_B2       0x00U /* 0x00..02: pressure raw signed 24-bit */
#define DPS310_REG_PRS_CFG      0x06U /* [6:4] rate, [2:0] OSR */
#define DPS310_REG_TMP_CFG      0x07U /* bit7 source, [6:4] rate, [2:0] OSR */
#define DPS310_REG_MEAS_CFG     0x08U /* bit7 COEF_RDY, bit6 SENSOR_RDY, bit5 TMP_RDY, bit4 PRS_RDY */
#define DPS310_REG_CFG_REG      0x09U /* bit3 T_SHIFT, bit2 P_SHIFT */
#define DPS310_REG_RESET        0x0CU /* 0x09: soft reset */
#define DPS310_REG_ID           0x0DU /* low nibble PRODUCT_ID = 0 */
#define DPS310_REG_COEF         0x10U /* 18 bytes: c0..c30 */
#define DPS310_REG_COEF_SRCE    0x28U /* bit7: temp sensor calibration source */

#define DPS310_READY_BOTH       0xC0U
#define DPS310_READY_TMP        0x20U
#define DPS310_READY_PRS        0x10U
#define DPS310_I2C_TIMEOUT_MS  5U

/* OSR 8x => kP=7864320; OSR 1x => kT=524288.
 * Khong bat SHIFT vi OSR khong vuot qua 8x.
 */
#define DPS310_KP              7864320.0f
#define DPS310_KT               524288.0f
#define DPS310_PRESSURE_ALPHA       0.20f

static HAL_StatusTypeDef DPS310_ReadReg(DPS310_t *dev, uint8_t reg,
                                        uint8_t *buf, uint16_t length)
{
    return HAL_I2C_Mem_Read(dev->hi2c, dev->address, reg,
                            I2C_MEMADD_SIZE_8BIT, buf, length,
                            DPS310_I2C_TIMEOUT_MS);
}

static HAL_StatusTypeDef DPS310_WriteReg(DPS310_t *dev, uint8_t reg,
                                         uint8_t value)
{
    return HAL_I2C_Mem_Write(dev->hi2c, dev->address, reg,
                             I2C_MEMADD_SIZE_8BIT, &value, 1U,
                             DPS310_I2C_TIMEOUT_MS);
}

/* Bu dau two's complement cho he so 12, 16, 20 va raw 24 bit. */
static int32_t DPS310_SignExtend(uint32_t value, uint8_t bits)
{
    uint32_t sign = 1UL << (bits - 1U);
    return (int32_t)((value ^ sign) - sign);
}

static int32_t DPS310_Raw24(const uint8_t *b)
{
    return DPS310_SignExtend(((uint32_t)b[0] << 16) |
                             ((uint32_t)b[1] << 8) | b[2], 24U);
}

static HAL_StatusTypeDef DPS310_ReadCoefficients(DPS310_t *dev)
{
    uint8_t b[18];
    if (DPS310_ReadReg(dev, DPS310_REG_COEF, b, sizeof(b)) != HAL_OK)
        return HAL_ERROR;

    dev->c0  = DPS310_SignExtend(((uint32_t)b[0] << 4) | (b[1] >> 4), 12U);
    dev->c1  = DPS310_SignExtend(((uint32_t)(b[1] & 0x0FU) << 8) | b[2], 12U);
    dev->c00 = DPS310_SignExtend(((uint32_t)b[3] << 12) |
                                 ((uint32_t)b[4] << 4) | (b[5] >> 4), 20U);
    dev->c10 = DPS310_SignExtend(((uint32_t)(b[5] & 0x0FU) << 16) |
                                 ((uint32_t)b[6] << 8) | b[7], 20U);
    dev->c01 = DPS310_SignExtend(((uint32_t)b[8] << 8) | b[9], 16U);
    dev->c11 = DPS310_SignExtend(((uint32_t)b[10] << 8) | b[11], 16U);
    dev->c20 = DPS310_SignExtend(((uint32_t)b[12] << 8) | b[13], 16U);
    dev->c21 = DPS310_SignExtend(((uint32_t)b[14] << 8) | b[15], 16U);
    dev->c30 = DPS310_SignExtend(((uint32_t)b[16] << 8) | b[17], 16U);
    return HAL_OK;
}

void DPS310_ResetHome(DPS310_t *dev)
{
    if (dev == NULL) return;
    dev->home_valid = 0U;
    dev->home_samples = 0U;
    dev->home_pressure_sum = 0.0f;
    dev->home_pressure_pa = 0.0f;
    dev->altitude_rel_m = 0.0f;
}

HAL_StatusTypeDef DPS310_Init(DPS310_t *dev, I2C_HandleTypeDef *hi2c)
{
    if ((dev == NULL) || (hi2c == NULL)) return HAL_ERROR;
    memset(dev, 0, sizeof(*dev));
    dev->hi2c = hi2c;

    /* Thu 0x77 (SDO high), sau do 0x76 (SDO low). */
    uint8_t addresses[] = {0x77U, 0x76U};
    uint8_t found = 0U;
    for (uint8_t i = 0U; i < 2U; i++) {
        uint16_t addr = (uint16_t)(addresses[i] << 1);
        if (HAL_I2C_IsDeviceReady(hi2c, addr, 2U, 5U) == HAL_OK) {
            dev->address = addr;
            found = 1U;
            break;
        }
    }
    if (!found) return HAL_ERROR;

    uint8_t id = 0U;
    if (DPS310_ReadReg(dev, DPS310_REG_ID, &id, 1U) != HAL_OK)
        return HAL_ERROR;
    if ((id & 0x0FU) != 0x00U) return HAL_ERROR;

    if (DPS310_WriteReg(dev, DPS310_REG_RESET, 0x09U) != HAL_OK)
        return HAL_ERROR;
    HAL_Delay(40U); /* Chi dung luc Init, cho sensor khoi dong. */

    /* Doi SENSOR_RDY(bit6) va COEF_RDY(bit7), timeout 100 ms. */
    uint32_t start = HAL_GetTick();
    uint8_t status = 0U;
    do {
        if (DPS310_ReadReg(dev, DPS310_REG_MEAS_CFG, &status, 1U) != HAL_OK)
            return HAL_ERROR;
        if ((status & DPS310_READY_BOTH) == DPS310_READY_BOTH) break;
        HAL_Delay(2U);
    } while ((HAL_GetTick() - start) < 100U);
    if ((status & DPS310_READY_BOTH) != DPS310_READY_BOTH)
        return HAL_TIMEOUT;

    if (DPS310_ReadCoefficients(dev) != HAL_OK) return HAL_ERROR;

    /* TMP_COEF_SRCE 0x28 bit7 phai giong TMP_CFG 0x07 bit7. */
    uint8_t temp_src;
    if (DPS310_ReadReg(dev, DPS310_REG_COEF_SRCE, &temp_src, 1U) != HAL_OK)
        return HAL_ERROR;

    /* PRS_CFG=0x53: PM_RATE=101 => 32 Hz; PM_PRC=011 => 8x. */
    if (DPS310_WriteReg(dev, DPS310_REG_PRS_CFG, 0x53U) != HAL_OK)
        return HAL_ERROR;
    /* TMP_CFG=0x20 | source: TMP_RATE=010 => 4 Hz; TMP_PRC=000 => 1x. */
    if (DPS310_WriteReg(dev, DPS310_REG_TMP_CFG,
                        (uint8_t)(0x20U | (temp_src & 0x80U))) != HAL_OK)
        return HAL_ERROR;
    /* CFG_REG=0: FIFO off, interrupts off, T_SHIFT=0, P_SHIFT=0. */
    if (DPS310_WriteReg(dev, DPS310_REG_CFG_REG, 0x00U) != HAL_OK)
        return HAL_ERROR;
    /* MEAS_CFG=0x07: background measurement, pressure + temperature. */
    if (DPS310_WriteReg(dev, DPS310_REG_MEAS_CFG, 0x07U) != HAL_OK)
        return HAL_ERROR;

    dev->initialized = 1U;
    DPS310_ResetHome(dev);
    return HAL_OK;
}

HAL_StatusTypeDef DPS310_ReadIfReady(DPS310_t *dev)
{
    if ((dev == NULL) || !dev->initialized) return HAL_ERROR;

    uint8_t status;
    HAL_StatusTypeDef res = DPS310_ReadReg(dev, DPS310_REG_MEAS_CFG,
                                           &status, 1U);
    if (res != HAL_OK) {
        dev->error_count++;
        return res;
    }
    if ((status & DPS310_READY_PRS) == 0U) return HAL_BUSY;

    /* Cho ca ket qua nhiet do dau tien de bu ap suat chinh xac. */
    if (!dev->valid && (status & DPS310_READY_TMP) == 0U)
        return HAL_BUSY;

    /* 0x00..0x05: pressure 24-bit, temperature 24-bit.
     * FIFO off nen co the doc ca hai ket qua trong mot lan I2C.
     */
    uint8_t raw[6];
    res = DPS310_ReadReg(dev, DPS310_REG_PRS_B2, raw, sizeof(raw));
    if (res != HAL_OK) {
        dev->error_count++;
        return res;
    }

    float p = (float)DPS310_Raw24(&raw[0]) / DPS310_KP;
    float t = (float)DPS310_Raw24(&raw[3]) / DPS310_KT;

    /* Infineon: calibrated pressure in Pa; temperature in deg C. */
    float pressure = (float)dev->c00 +
        p * ((float)dev->c10 + p * ((float)dev->c20 + p * (float)dev->c30)) +
        t * ((float)dev->c01 + p * ((float)dev->c11 + p * (float)dev->c21));
    float temp = 0.5f * (float)dev->c0 + (float)dev->c1 * t;

    if (!isfinite(pressure) || pressure < 30000.0f ||
        pressure > 120000.0f || !isfinite(temp) ||
        temp < -40.0f || temp > 85.0f) {
        dev->error_count++;
        return HAL_ERROR;
    }

    dev->pressure_pa = pressure;
    dev->temperature_c = temp;
    if (!dev->valid) dev->pressure_filtered_pa = pressure;
    else dev->pressure_filtered_pa += DPS310_PRESSURE_ALPHA *
                                     (pressure - dev->pressure_filtered_pa);
    dev->valid = 1U;
    dev->last_update_ms = HAL_GetTick();
    dev->sample_count++;

    /* Chi la ISA altitude (sea-level pressure gia dinh 101325 Pa). */
    dev->altitude_isa_m = 44330.0f *
        (1.0f - powf(dev->pressure_filtered_pa / 101325.0f, 0.19029496f));

    /* Khoi tao home bang 64 mau, phai de drone dung yen luc nay. */
    if (!dev->home_valid) {
        dev->home_pressure_sum += pressure;
        dev->home_samples++;
        if (dev->home_samples >= DPS310_SAMPLE_HOME_COUNT) {
            dev->home_pressure_pa = dev->home_pressure_sum /
                                    (float)dev->home_samples;
            dev->home_valid = 1U;
        }
    }
    if (dev->home_valid) {
        dev->altitude_rel_m = 44330.0f *
            (1.0f - powf(dev->pressure_filtered_pa /
                           dev->home_pressure_pa, 0.19029496f));
    }
    return HAL_OK;
}
