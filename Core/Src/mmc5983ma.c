/* MMC5983MA: thanh ghi 0x00..0x06 chứa 18 bit XYZ; CONTROL0/1/2 ở 0x09/0x0A/0x0B. */
#include "mmc5983ma.h"

#define REG_XOUT0       0x00U // 0x00: X MSB.

#define REG_XOUT1       0x01U // 0x01: X byte thấp.

#define REG_YOUT0       0x02U // 0x02: Y MSB.

#define REG_YOUT1       0x03U // 0x03: Y byte thấp.

#define REG_ZOUT0       0x04U // 0x04: Z MSB.

#define REG_ZOUT1       0x05U // 0x05: Z byte thấp.

#define REG_XYZOUT2     0x06U // 0x06: 2 bit LSB của mỗi trục.

#define REG_STATUS      0x08U // 0x08: bit0=M_DONE.

#define REG_CONTROL0    0x09U // 0x09: TM_M/SET/RESET.

#define REG_CONTROL1    0x0AU // 0x0A: BW và enable các trục.

#define REG_CONTROL2    0x0BU // 0x0B: liên tục hay single-shot.

#define REG_PRODUCTID   0x2FU // 0x2F: mã sản phẩm.

#define STATUS_MEAS_M_DONE  0x01U // 0x01: bit0=1 khi đo xong.

#define CTRL0_TM_M          0x01U // 0x01: trigger đo từ trường.

#define CTRL0_SET           0x08U // 0x08: tạo xung SET miền từ.

#define CTRL0_RESET         0x10U // 0x10: tạo xung RESET miền từ (không phải soft reset).

#define MMC5983_I2C_TIMEOUT_MS  100U // Timeout I2C 100 ms.

#define MMC5983_MEAS_TIMEOUT_MS 10U // Chờ hoàn thành tối đa 10 ms.

#define MMC5983_POLL_DELAY_MS   1U // Polling mỗi 1 ms.

/* Ghi 1 byte vào thanh ghi I2C. */
static HAL_StatusTypeDef WriteReg(MMC5983MA_t *dev, uint8_t reg, uint8_t data)
{
    if ((dev == NULL) || (dev->hi2c == NULL))
        return HAL_ERROR;

    return HAL_I2C_Mem_Write(dev->hi2c,
                             MMC5983_I2C_ADDR,
                             reg,
                             I2C_MEMADD_SIZE_8BIT,
                             &data,
                             1U,
                             MMC5983_I2C_TIMEOUT_MS);
}

/* Đọc len byte từ thanh ghi I2C. */
static HAL_StatusTypeDef ReadReg(MMC5983MA_t *dev,
                                 uint8_t reg,
                                 uint8_t *data,
                                 uint16_t len)
{
    if ((dev == NULL) || (dev->hi2c == NULL) || (data == NULL) || (len == 0U))
        return HAL_ERROR;

    return HAL_I2C_Mem_Read(dev->hi2c,
                            MMC5983_I2C_ADDR,
                            reg,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            len,
                            MMC5983_I2C_TIMEOUT_MS);
}

/* Kiểm tra ID chip ở 0x2F. */
uint8_t MMC5983_WhoAmI(MMC5983MA_t *dev)
{

    uint8_t id = 0U;

    if (ReadReg(dev, REG_PRODUCTID, &id, 1U) != HAL_OK)
        return 0U;

    return id;
}

/* Tạo xung RESET, SET rồi cấu hình phép đo từ trường. */
HAL_StatusTypeDef MMC5983_Init(MMC5983MA_t *dev)
{
    if ((dev == NULL) || (dev->hi2c == NULL))
        return HAL_ERROR;

    dev->raw_x = 0;
    dev->raw_y = 0;
    dev->raw_z = 0;
    dev->mag_x = 0.0f;
    dev->mag_y = 0.0f;
    dev->mag_z = 0.0f;

    uint8_t id = MMC5983_WhoAmI(dev);
    if (id != MMC5983_WHOAMI)
        return HAL_ERROR;

    HAL_Delay(1U);

/* CONTROL0 (0x09) <- 0x10 = 0001_0000: bit4=RESET (xung reset tu hoa); bit3 SET=0, bit0 TM_M=0. */
    if (WriteReg(dev, REG_CONTROL0, CTRL0_RESET) != HAL_OK)
        return HAL_ERROR;

    HAL_Delay(1U);

/* CONTROL0 (0x09) <- 0x08 = 0000_1000: bit3=SET (xung set tu hoa); bit4 RESET=0, bit0 TM_M=0. */
    if (WriteReg(dev, REG_CONTROL0, CTRL0_SET) != HAL_OK)
        return HAL_ERROR;

    HAL_Delay(1U);

/* CONTROL1 (0x0A) <- 0x00 = 0000_0000: BW[1:0]=00 (~8 ms/do, 100 Hz max); X/Y/Z_INHIBIT[4:2]=000 (bat ca 3 truc); SW_RST[7]=0. Lua chon BW: 01=200Hz, 10=400Hz, 11=800Hz max. */
    if (WriteReg(dev, REG_CONTROL1, 0x00U) != HAL_OK)
        return HAL_ERROR;

/* CONTROL2 (0x0B) <- 0x00 = 0000_0000: Cmm_en(bit3)=0 => single-shot; CM_Freq[2:0]=000 (khong co y nghia khi Cmm_en=0); EN_PRD_SET[7]=0. */
    if (WriteReg(dev, REG_CONTROL2, 0x00U) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

/* Trigger đo, poll DONE và ghép 7 byte thành XYZ 18-bit. */
HAL_StatusTypeDef MMC5983_ReadRaw(MMC5983MA_t *dev,
                                  int32_t *x,
                                  int32_t *y,
                                  int32_t *z)
{
    if ((dev == NULL) || (dev->hi2c == NULL) ||
        (x == NULL) || (y == NULL) || (z == NULL))
        return HAL_ERROR;

    uint8_t status = 0U;

    uint8_t buf[7] = {0U};

    /* CONTROL0 (0x09) <- 0x01 = 0000_0001: bit0 TM_M=1, bat dau do tu truong 1 lan. */
    if (WriteReg(dev, REG_CONTROL0, CTRL0_TM_M) != HAL_OK)
        return HAL_ERROR;

    uint32_t start = HAL_GetTick();

    do
    {
        if (ReadReg(dev, REG_STATUS, &status, 1U) != HAL_OK)
            return HAL_ERROR;

        /* STATUS (0x08): kiem tra bit0=1 neu ket thuc do; bit khac khong dung de xac nhan. */
        if ((status & STATUS_MEAS_M_DONE) != 0U)
            break;

        HAL_Delay(MMC5983_POLL_DELAY_MS);

    } while ((HAL_GetTick() - start) <= MMC5983_MEAS_TIMEOUT_MS);

    if ((status & STATUS_MEAS_M_DONE) == 0U)
        return HAL_TIMEOUT;

    if (ReadReg(dev, REG_XOUT0, buf, sizeof(buf)) != HAL_OK)
        return HAL_ERROR;

    uint32_t raw_x = ((uint32_t)buf[0] << 10) |
                     ((uint32_t)buf[1] << 2) |
                     ((buf[6] >> 6) & 0x03U);

    uint32_t raw_y = ((uint32_t)buf[2] << 10) |
                     ((uint32_t)buf[3] << 2) |
                     ((buf[6] >> 4) & 0x03U);

    uint32_t raw_z = ((uint32_t)buf[4] << 10) |
                     ((uint32_t)buf[5] << 2) |
                     ((buf[6] >> 2) & 0x03U);

    *x = (int32_t)raw_x;
    *y = (int32_t)raw_y;
    *z = (int32_t)raw_z;

    dev->raw_x = *x;
    dev->raw_y = *y;
    dev->raw_z = *z;

    return HAL_OK;
}

/* Đổi raw sang gauss theo (raw-131072)/16384. */
HAL_StatusTypeDef MMC5983_ReadMag(MMC5983MA_t *dev,
                                  float *x,
                                  float *y,
                                  float *z)
{
    if ((dev == NULL) || (x == NULL) || (y == NULL) || (z == NULL))
        return HAL_ERROR;

    int32_t raw_x;

    int32_t raw_y;

    int32_t raw_z;

    HAL_StatusTypeDef status = MMC5983_ReadRaw(dev, &raw_x, &raw_y, &raw_z);
    if (status != HAL_OK)
        return status;

/* Raw offset 131072 = 0 G; 16384 LSB/G; kết quả G, không phải µT. */
    *x = ((float)raw_x - 131072.0f) / 16384.0f;
    *y = ((float)raw_y - 131072.0f) / 16384.0f;
    *z = ((float)raw_z - 131072.0f) / 16384.0f;

    dev->mag_x = *x;
    dev->mag_y = *y;
    dev->mag_z = *z;

    return HAL_OK;
}

#define MMC5983_FAST_I2C_TIMEOUT_MS 3U // Timeout giao dịch I2C nhanh 3 ms.

/* Ghi TM_M=1 để bắt đầu một phép đo. */
HAL_StatusTypeDef MMC5983_StartMeasurement(MMC5983MA_t *dev)
{
    if ((dev == NULL) || (dev->hi2c == NULL)) return HAL_ERROR;
    /* CONTROL0 (0x09) <- 0x01: kich phep do single-shot, khong doi status DONE tai day. */
    uint8_t cmd = CTRL0_TM_M;
    return HAL_I2C_Mem_Write(dev->hi2c, MMC5983_I2C_ADDR, REG_CONTROL0,
                             I2C_MEMADD_SIZE_8BIT, &cmd, 1U,
                             MMC5983_FAST_I2C_TIMEOUT_MS);
}

/* Trả HAL_BUSY nếu chưa xong, nếu xong trả gauss. */
HAL_StatusTypeDef MMC5983_ReadMagIfReady(MMC5983MA_t *dev,
                                         float *x, float *y, float *z)
{
    if ((dev == NULL) || (dev->hi2c == NULL) ||
        (x == NULL) || (y == NULL) || (z == NULL)) return HAL_ERROR;

    uint8_t status = 0U;
    HAL_StatusTypeDef r = HAL_I2C_Mem_Read(dev->hi2c, MMC5983_I2C_ADDR,
                              REG_STATUS, I2C_MEMADD_SIZE_8BIT,
                              &status, 1U, MMC5983_FAST_I2C_TIMEOUT_MS);
    if (r != HAL_OK) return r;
    /* STATUS (0x08), bit0=0: phep do chua hoan thanh. */
    if ((status & STATUS_MEAS_M_DONE) == 0U) return HAL_BUSY;

    uint8_t buf[7] = {0};
    r = HAL_I2C_Mem_Read(dev->hi2c, MMC5983_I2C_ADDR, REG_XOUT0,
                         I2C_MEMADD_SIZE_8BIT, buf, sizeof(buf),
                         MMC5983_FAST_I2C_TIMEOUT_MS);
    if (r != HAL_OK) return r;
    dev->raw_x = (int32_t)(((uint32_t)buf[0] << 10) | ((uint32_t)buf[1] << 2) |
                           ((buf[6] >> 6) & 0x03U));
    dev->raw_y = (int32_t)(((uint32_t)buf[2] << 10) | ((uint32_t)buf[3] << 2) |
                           ((buf[6] >> 4) & 0x03U));
    dev->raw_z = (int32_t)(((uint32_t)buf[4] << 10) | ((uint32_t)buf[5] << 2) |
                           ((buf[6] >> 2) & 0x03U));
/* Đổi XYZ raw 18-bit sang G; nhân 100 nếu cần µT. */
    dev->mag_x = *x = ((float)dev->raw_x - 131072.0f) / 16384.0f;
    dev->mag_y = *y = ((float)dev->raw_y - 131072.0f) / 16384.0f;
    dev->mag_z = *z = ((float)dev->raw_z - 131072.0f) / 16384.0f;
    return HAL_OK;
}
