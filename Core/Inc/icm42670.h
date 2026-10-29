/* ICM42670-P: địa chỉ thanh ghi SPI, hệ số đổi raw và giao diện driver. */
#ifndef INC_ICM42670_H_
#define INC_ICM42670_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;

#define ICM42670_SPI        hspi1 // IMU giao tiếp bằng SPI1.

#define ICM_CS_PORT         GPIOA // Cổng CS: GPIOA.

#define ICM_CS_PIN          GPIO_PIN_4 // CS chân PA4, mức thấp kích hoạt.

#define ICM_WHO_AM_I        0x75U // 0x75: thanh ghi đọc mã cảm biến.

#define ICM_PWR_MGMT0       0x1FU // 0x1F: chế độ nguồn gyro/accel.

#define ICM_GYRO_CONFIG0    0x20U // 0x20: chọn thang đo [6:5] và ODR [3:0] gyro.

#define ICM_ACCEL_CONFIG0   0x21U // 0x21: chọn thang đo [6:5] và ODR [3:0] accel.

#define ICM_GYRO_CONFIG1    0x23U // 0x23: lọc thông thấp gyro [2:0].

#define ICM_ACCEL_CONFIG1   0x24U // 0x24: lọc accel [2:0], averaging LP [6:4].

#define ICM_TEMP_DATA1      0x09U // 0x09: MSB nhiệt độ, đầu khối đọc liên tục 14 byte.

#define ICM_ACCEL_DATA_X1   0x0BU // 0x0B: MSB accel X.

#define ICM_GYRO_DATA_X1    0x11U // 0x11: MSB gyro X.

#define ICM_WHO_AM_I_VALUE  0x67U // ID phải bằng 0x67.

#define ICM_GYRO_FS_DPS     2000.0f // Thang gyro ±2000 độ/giây.

#define ICM_ACCEL_FS_G      16.0f // Thang accel ±16g.

#define ICM_GYRO_LSB_PER_DPS 16.4f // 16,4 LSB/(độ/giây) tại ±2000 dps.

#define ICM_ACCEL_LSB_PER_G  2048.0f // 2048 LSB/g tại ±16g.

typedef enum
{

    ICM42670_OK = 0,

    ICM42670_ERROR = 1,

    ICM42670_TIMEOUT = 2,

    ICM42670_WHOAMI_ERROR = 3
} ICM42670_Status_t;

typedef struct
{

    int16_t ax_raw; // Gia tốc X raw int16.

    int16_t ay_raw; // Gia tốc Y raw int16.

    int16_t az_raw; // Gia tốc Z raw int16.

    int16_t gx_raw; // Gyro X raw int16.

    int16_t gy_raw; // Gyro Y raw int16.

    int16_t gz_raw; // Gyro Z raw int16.

    int16_t temp_raw; // Nhiệt độ raw int16.

    float ax_g; // Gia tốc X (g).

    float ay_g; // Gia tốc Y (g).

    float az_g; // Gia tốc Z (g).

    float gx_dps; // Vận tốc góc X (độ/s).

    float gy_dps; // Vận tốc góc Y (độ/s).

    float gz_dps; // Vận tốc góc Z (độ/s).

    float temperature_c; // Nhiệt độ (°C).

} ICM42670_Data_t;

typedef struct
{

    float gyro_bias_x_dps; // Bias gyro X (độ/s).

    float gyro_bias_y_dps; // Bias gyro Y (độ/s).

    float gyro_bias_z_dps; // Bias gyro Z (độ/s).

    uint8_t initialized; // 1 nếu Init thành công.
} ICM42670_t;

/* Kiểm tra chip và cấu hình cảm biến. */
ICM42670_Status_t ICM42670_Init(ICM42670_t *dev);

/* Đọc 1 thanh ghi qua SPI. */
ICM42670_Status_t ICM42670_ReadReg(uint8_t reg, uint8_t *data);

/* Ghi 1 thanh ghi qua SPI. */
ICM42670_Status_t ICM42670_WriteReg(uint8_t reg, uint8_t data);

/* Đọc 14 byte raw: nhiệt độ, accel, gyro. */
ICM42670_Status_t ICM42670_ReadRaw(ICM42670_Data_t *imu);

/* Đổi raw thành g, độ/giây và °C. */
ICM42670_Status_t ICM42670_ReadAll(ICM42670_Data_t *imu);

/* Trừ bias gyro khỏi dữ liệu đo. */
void ICM42670_ApplyCalibration(ICM42670_t *dev, ICM42670_Data_t *imu);

/* Lấy trung bình gyro khi drone đứng yên. */
ICM42670_Status_t ICM42670_CalibrateGyro(ICM42670_t *dev, uint16_t samples, uint16_t sample_delay_ms);

#endif
