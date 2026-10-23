/* Cài đặt ICM42670: bit7 địa chỉ SPI = 1 khi đọc, = 0 khi ghi. */
#include "icm42670.h"
#include <string.h>

/* Chọn chip: CS=0. */
static void CS_Low(void)
{
    HAL_GPIO_WritePin(ICM_CS_PORT, ICM_CS_PIN, GPIO_PIN_RESET);
}

/* Bỏ chọn chip: CS=1. */
static void CS_High(void)
{
    HAL_GPIO_WritePin(ICM_CS_PORT, ICM_CS_PIN, GPIO_PIN_SET);
}

/* Đọc byte thanh ghi, trả mã trạng thái. */
ICM42670_Status_t ICM42670_ReadReg(uint8_t reg, uint8_t *data)
{
    if (data == NULL)
        return ICM42670_ERROR;

/* SPI READ: reg | 0x80U -> bit7=1, bit[6:0] la dia chi thanh ghi. */
    uint8_t addr = reg | 0x80U;

    HAL_StatusTypeDef status;

    CS_Low();
    status = HAL_SPI_Transmit(&ICM42670_SPI, &addr, 1U, 100U);
    if (status == HAL_OK)
        status = HAL_SPI_Receive(&ICM42670_SPI, data, 1U, 100U);
    CS_High();

    if (status == HAL_TIMEOUT)
        return ICM42670_TIMEOUT;
    if (status != HAL_OK)
        return ICM42670_ERROR;

    return ICM42670_OK;
}

/* Ghi byte dữ liệu vào thanh ghi. */
ICM42670_Status_t ICM42670_WriteReg(uint8_t reg, uint8_t data)
{

/* SPI WRITE: reg & 0x7FU -> bit7=0, bit[6:0] la dia chi thanh ghi. */
    uint8_t buf[2] = { (uint8_t)(reg & 0x7FU), data };

    HAL_StatusTypeDef status;

    CS_Low();
    status = HAL_SPI_Transmit(&ICM42670_SPI, buf, 2U, 100U);
    CS_High();

    if (status == HAL_TIMEOUT)
        return ICM42670_TIMEOUT;
    if (status != HAL_OK)
        return ICM42670_ERROR;

    return ICM42670_OK;
}

/* Đọc len byte liên tiếp, giữ CS ở mức thấp. */
static ICM42670_Status_t ICM42670_ReadBytes(uint8_t reg, uint8_t *data, uint16_t len)
{
    if ((data == NULL) || (len == 0U))
        return ICM42670_ERROR;

/* SPI READ: reg | 0x80U -> bit7=1, bit[6:0] la dia chi thanh ghi. */
    uint8_t addr = reg | 0x80U;

    HAL_StatusTypeDef status;

    CS_Low();
    status = HAL_SPI_Transmit(&ICM42670_SPI, &addr, 1U, 100U);
    if (status == HAL_OK)
        status = HAL_SPI_Receive(&ICM42670_SPI, data, len, 100U);
    CS_High();

    if (status == HAL_TIMEOUT)
        return ICM42670_TIMEOUT;
    if (status != HAL_OK)
        return ICM42670_ERROR;

    return ICM42670_OK;
}

/* Ghép 2 byte MSB/LSB thành int16. */
static int16_t MakeInt16(uint8_t msb, uint8_t lsb)
{
    return (int16_t)(((uint16_t)msb << 8) | lsb);
}

/* Khởi tạo thang đo, ODR, DLPF và Low Noise. */
ICM42670_Status_t ICM42670_Init(ICM42670_t *dev)
{
    if (dev == NULL)
        return ICM42670_ERROR;

    memset(dev, 0, sizeof(*dev));
    CS_High();
    HAL_Delay(10U);

    uint8_t who_am_i = 0U;

    ICM42670_Status_t status = ICM42670_ReadReg(ICM_WHO_AM_I, &who_am_i);
    if (status != ICM42670_OK)
        return status;

    if (who_am_i != ICM_WHO_AM_I_VALUE)
        return ICM42670_WHOAMI_ERROR;

/*
 * GYRO_CONFIG0 (0x20) <- 0x05 = 0b0000_0101
 * [7]   = 0    : reserved (ghi 0).
 * [6:5] = 00   : GYRO_UI_FS_SEL = ±2000 dps; 01=±1000, 10=±500, 11=±250.
 * [4]   = 0    : reserved.
 * [3:0] = 0101 : GYRO_ODR = 1600 Hz.
 *                0110=800, 0111=400, 1000=200, 1001=100,
 *                1010=50, 1011=25, 1100=12.5 Hz.
 * Luu y: neu doi FS phai doi he so ICM_GYRO_LSB_PER_DPS trong .h.
 */
    status = ICM42670_WriteReg(ICM_GYRO_CONFIG0, 0x05U);
    if (status != ICM42670_OK)
        return status;

/*
 * ACCEL_CONFIG0 (0x21) <- 0x25 = 0b0010_0101
 * [7]   = 0    : reserved.
 * [6:5] = 01   : ACCEL_UI_FS_SEL = ±8g; 00=±16g, 10=±4g, 11=±2g.
 * [4]   = 0    : reserved.
 * [3:0] = 0101 : ACCEL_ODR = 1600 Hz (chi hop le trong Low Noise).
 *                0110=800 Hz (LN); 0111=400, 1000=200, 1001=100,
 *                1010=50, 1011=25, 1100=12.5 Hz (LP/LN).
 * Luu y: neu doi FS phai doi ICM_ACCEL_LSB_PER_G trong .h.
 */
    status = ICM42670_WriteReg(ICM_ACCEL_CONFIG0, 0x25U);
    if (status != ICM42670_OK)
        return status;

/*
 * GYRO_CONFIG1 (0x23) <- 0x06 = 0b0000_0110
 * [7:3] = 00000 : reserved (ghi 0).
 * [2:0] = 110   : GYRO_UI_FILT_BW = 25 Hz (bo loc thong thap).
 * Lua chon: 000=bypass; 001=180; 010=121; 011=73;
 *           100=53; 101=34; 110=25; 111=16 Hz.
 * ODR 1600 Hz la toc do tao mau; 25 Hz la bang thong loc, KHONG phai ODR.
 */
    status = ICM42670_WriteReg(ICM_GYRO_CONFIG1, 0x06U);
    if (status != ICM42670_OK)
        return status;

/*
 * ACCEL_CONFIG1 (0x24) <- 0x06 = 0b0000_0110
 * [7]   = 0   : reserved.
 * [6:4] = 000 : ACCEL_UI_AVG = 2x (chi co tac dung trong Low Power).
 *                001=4x; 010=8x; 011=16x; 100=32x; 101..111=64x.
 * [3]   = 0   : reserved.
 * [2:0] = 110 : ACCEL_UI_FILT_BW = 25 Hz; cac muc loc giong gyro:
 *               000=bypass, 001=180, 010=121, 011=73,
 *               100=53, 101=34, 110=25, 111=16 Hz.
 * Hien accel o Low Noise (0x0F) nen AVG 2x KHONG duoc ap dung.
 */
    status = ICM42670_WriteReg(ICM_ACCEL_CONFIG1, 0x06U);
    if (status != ICM42670_OK)
        return status;

/*
 * PWR_MGMT0 (0x1F) <- 0x0F = 0b0000_1111
 * [7]   = 0  : ACCEL_LP_CLK_SEL = wake-up clock (chi cho accel LP).
 * [6:5] = 00 : reserved.
 * [4]   = 0  : IDLE=0, khong ep RC oscillator duy tri luc tat sensor.
 * [3:2] = 11 : GYRO_MODE = Low Noise;
 *              00=Off, 01=Standby, 10=reserved, 11=Low Noise.
 * [1:0] = 11 : ACCEL_MODE = Low Noise;
 *              00/01=Off, 10=Low Power, 11=Low Noise.
 * Chuyen tu Off sang On: khong ghi thanh ghi trong 200 us.
 * Gyro can bat it nhat 45 ms; HAL_Delay(50) ben duoi dap ung yeu cau.
 */
    status = ICM42670_WriteReg(ICM_PWR_MGMT0, 0x0FU);
    if (status != ICM42670_OK)
        return status;

    HAL_Delay(50U);
    dev->initialized = 1U;

    return ICM42670_OK;
}

/* Đọc raw 14 byte bắt đầu TEMP_DATA1 (0x09). */
ICM42670_Status_t ICM42670_ReadRaw(ICM42670_Data_t *imu)
{
    if (imu == NULL)
        return ICM42670_ERROR;

    uint8_t buf[14];

    ICM42670_Status_t status = ICM42670_ReadBytes(ICM_TEMP_DATA1, buf, sizeof(buf));
    if (status != ICM42670_OK)
        return status;

    imu->temp_raw = MakeInt16(buf[0], buf[1]);
    imu->ax_raw = MakeInt16(buf[2], buf[3]);
    imu->ay_raw = MakeInt16(buf[4], buf[5]);
    imu->az_raw = MakeInt16(buf[6], buf[7]);
    imu->gx_raw = MakeInt16(buf[8], buf[9]);
    imu->gy_raw = MakeInt16(buf[10], buf[11]);
    imu->gz_raw = MakeInt16(buf[12], buf[13]);

    return ICM42670_OK;
}

/* Raw/4096 => g; raw/16,4 => độ/s; chuyển nhiệt độ. */
ICM42670_Status_t ICM42670_ReadAll(ICM42670_Data_t *imu)
{
    if (imu == NULL)
        return ICM42670_ERROR;

    ICM42670_Status_t status = ICM42670_ReadRaw(imu);
    if (status != ICM42670_OK)
        return status;

    imu->ax_g = (float)imu->ax_raw / ICM_ACCEL_LSB_PER_G;
    imu->ay_g = (float)imu->ay_raw / ICM_ACCEL_LSB_PER_G;
    imu->az_g = (float)imu->az_raw / ICM_ACCEL_LSB_PER_G;

    imu->gx_dps = (float)imu->gx_raw / ICM_GYRO_LSB_PER_DPS;
    imu->gy_dps = (float)imu->gy_raw / ICM_GYRO_LSB_PER_DPS;
    imu->gz_dps = (float)imu->gz_raw / ICM_GYRO_LSB_PER_DPS;

/* Nhiệt độ °C = temp_raw/132,48 + 25. */
    imu->temperature_c = ((float)imu->temp_raw / 132.48f) + 25.0f;

    return ICM42670_OK;
}

/* Trừ gyro bias đã hiệu chỉnh, đơn vị độ/s. */
void ICM42670_ApplyCalibration(ICM42670_t *dev, ICM42670_Data_t *imu)
{
    if ((dev == NULL) || (imu == NULL))
        return;

    imu->gx_dps -= dev->gyro_bias_x_dps;
    imu->gy_dps -= dev->gyro_bias_y_dps;
    imu->gz_dps -= dev->gyro_bias_z_dps;
}

/* Lấy mẫu gyro đứng yên và lưu giá trị trung bình. */
ICM42670_Status_t ICM42670_CalibrateGyro(ICM42670_t *dev, uint16_t samples, uint16_t sample_delay_ms)
{
    if ((dev == NULL) || (samples == 0U))
        return ICM42670_ERROR;

    float sum_x = 0.0f;

    float sum_y = 0.0f;

    float sum_z = 0.0f;

    ICM42670_Data_t imu;

    for (uint16_t i = 0U; i < samples; ++i)
    {

        ICM42670_Status_t status = ICM42670_ReadAll(&imu);
        if (status != ICM42670_OK)
            return status;

        sum_x += imu.gx_dps;
        sum_y += imu.gy_dps;
        sum_z += imu.gz_dps;

        if (sample_delay_ms > 0U)
            HAL_Delay(sample_delay_ms);
    }

    dev->gyro_bias_x_dps = sum_x / (float)samples;
    dev->gyro_bias_y_dps = sum_y / (float)samples;
    dev->gyro_bias_z_dps = sum_z / (float)samples;

    return ICM42670_OK;
}
