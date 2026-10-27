/* Infineon DPS310 over 4-wire SPI.
 * Datasheet v1.2: CPOL=1, CPHA=1; READ=addr|0x80, WRITE=addr&0x7F.
 * Sign-extended factory coefficients 0x10..0x21 correct pressure and temp.
 */
#include "dps310.h"
#include <math.h>
#include <string.h>

#define REG_PRS_B2        0x00U  /* 0x00..02: signed 24-bit pressure */
#define REG_PRS_CFG       0x06U  /* [6:4] sample rate, [3:0] oversampling */
#define REG_TMP_CFG       0x07U  /* [7] sensor source, [6:4] rate, [3:0] OSR */
#define REG_MEAS_CFG      0x08U  /* [7] coef ready, [6] sensor ready,
                                   [5] TMP_RDY, [4] PRS_RDY */
#define REG_CFG           0x09U  /* [3] temp shift, [2] pressure shift,
                                   [1] FIFO, [0] 3-wire SPI enable */
#define REG_RESET         0x0CU  /* 0x09 = software reset */
#define REG_ID            0x0DU  /* 0x10 = revision 1, product ID 0 */
#define REG_COEF          0x10U  /* 0x10..0x21: 18 coefficient bytes */
#define REG_COEF_SRCE     0x28U  /* [7] temperature source for coefficients */

#define DPS310_ID         0x10U
#define DPS310_SPI_TIMEOUT_MS 2U
#define DPS310_READ_MAX   18U
#define DPS310_KP         7864320.0f /* Pressure OSR 8x (PRS_CFG=0x53) */
#define DPS310_KT          524288.0f /* Temp OSR 1x (TMP_CFG=0x20/0xA0) */
#define DPS310_ALPHA          0.20f /* LPF pressure, update on new sample */

static void DPS310_CS(DPS310_t *dev, GPIO_PinState state) {
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, state);
}

/* Full-duplex read: byte 0 is command (R/W bit7 = 1), data begins rx[1].
 * CS stays low for entire transaction; auto-increment register addresses.
 */
static HAL_StatusTypeDef DPS310_ReadRegs(DPS310_t *dev, uint8_t reg,
		uint8_t *data, uint16_t len) {
	if (!dev || !dev->hspi || !dev->cs_port || !data
			|| len == 0U|| len > DPS310_READ_MAX)
		return HAL_ERROR;

	uint8_t tx[DPS310_READ_MAX + 1U] = { 0U };
	uint8_t rx[DPS310_READ_MAX + 1U] = { 0U };
	tx[0] = (uint8_t) (reg | 0x80U);

	DPS310_CS(dev, GPIO_PIN_RESET);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(dev->hspi, tx, rx,
			(uint16_t) (len + 1U), DPS310_SPI_TIMEOUT_MS);
	DPS310_CS(dev, GPIO_PIN_SET);

	if (status == HAL_OK)
		memcpy(data, rx + 1U, len);
	return status;
}

/* Write one register: byte 0 command (R/W bit7 = 0), byte 1 value. */
static HAL_StatusTypeDef DPS310_WriteReg(DPS310_t *dev, uint8_t reg,
		uint8_t value) {
	if (!dev || !dev->hspi || !dev->cs_port)
		return HAL_ERROR;
	uint8_t tx[2] = { (uint8_t) (reg & 0x7FU), value };
	DPS310_CS(dev, GPIO_PIN_RESET);
	HAL_StatusTypeDef status = HAL_SPI_Transmit(dev->hspi, tx, 2U,
	DPS310_SPI_TIMEOUT_MS);
	DPS310_CS(dev, GPIO_PIN_SET);
	return status;
}

/* N-bit signed two's-complement packed fields, N=12,16,20,24. */
static int32_t DPS310_SignExtend(uint32_t x, uint8_t n) {
	uint32_t sign = 1UL << (n - 1U);
	return (int32_t) ((x ^ sign) - sign);
}

static int32_t DPS310_Raw24(const uint8_t *b) {
	return DPS310_SignExtend(
			((uint32_t) b[0] << 16) | ((uint32_t) b[1] << 8) | b[2], 24U);
}

/* Decode 9 factory coefficients with fields crossing byte boundaries. */
static HAL_StatusTypeDef DPS310_ReadCoefficients(DPS310_t *dev) {
	uint8_t b[18];
	HAL_StatusTypeDef st = DPS310_ReadRegs(dev, REG_COEF, b, sizeof(b));
	if (st != HAL_OK)
		return st;

	dev->c0 = DPS310_SignExtend(((uint32_t) b[0] << 4) | (b[1] >> 4), 12U);
	dev->c1 = DPS310_SignExtend(((uint32_t) (b[1] & 0x0FU) << 8) | b[2], 12U);
	dev->c00 = DPS310_SignExtend(
			((uint32_t) b[3] << 12) | ((uint32_t) b[4] << 4) | (b[5] >> 4),
			20U);
	dev->c10 = DPS310_SignExtend(
			((uint32_t) (b[5] & 0x0FU) << 16) | ((uint32_t) b[6] << 8) | b[7],
			20U);
	dev->c01 = DPS310_SignExtend(((uint32_t) b[8] << 8) | b[9], 16U);
	dev->c11 = DPS310_SignExtend(((uint32_t) b[10] << 8) | b[11], 16U);
	dev->c20 = DPS310_SignExtend(((uint32_t) b[12] << 8) | b[13], 16U);
	dev->c21 = DPS310_SignExtend(((uint32_t) b[14] << 8) | b[15], 16U);
	dev->c30 = DPS310_SignExtend(((uint32_t) b[16] << 8) | b[17], 16U);
	return HAL_OK;
}

void DPS310_ResetHome(DPS310_t *dev) {
	if (dev == NULL)
		return;
	dev->home_valid = 0U;
	dev->home_samples = 0U;
	dev->home_pressure_sum = 0.0f;
	dev->home_pressure_pa = 0.0f;
	dev->altitude_rel_m = 0.0f;
}

HAL_StatusTypeDef DPS310_Init(DPS310_t *dev, SPI_HandleTypeDef *hspi,
		GPIO_TypeDef *cs_port, uint16_t cs_pin) {
	if (!dev || !hspi || !cs_port || cs_pin == 0U)
		return HAL_ERROR;
	/* Avoid silently reading garbage when CubeMX still uses SPI Mode 0. */
	if (hspi->Init.CLKPolarity != SPI_POLARITY_HIGH
			|| hspi->Init.CLKPhase != SPI_PHASE_2EDGE
			|| hspi->Init.Direction != SPI_DIRECTION_2LINES
			|| hspi->Init.DataSize != SPI_DATASIZE_8BIT)
		return HAL_ERROR;

	memset(dev, 0, sizeof(*dev));
	dev->hspi = hspi;
	dev->cs_port = cs_port;
	dev->cs_pin = cs_pin;
	DPS310_CS(dev, GPIO_PIN_SET); /* idle CS high; select only for transfers */
	HAL_Delay(10U);

	uint8_t id = 0U;
	HAL_StatusTypeDef st = DPS310_ReadRegs(dev, REG_ID, &id, 1U);
	if (st != HAL_OK)
		return st;
	if (id != DPS310_ID)
		return HAL_ERROR;

	/* RESET(0x0C) <- 0x09: software reset. */
	st = DPS310_WriteReg(dev, REG_RESET, 0x09U);
	if (st != HAL_OK)
		return st;
	HAL_Delay(40U);

	/* MEAS_CFG(0x08): COEF_RDY(bit7) and SENSOR_RDY(bit6) must both be 1. */
	uint32_t start = HAL_GetTick();
	uint8_t status = 0U;
	do {
		st = DPS310_ReadRegs(dev, REG_MEAS_CFG, &status, 1U);
		if (st != HAL_OK)
			return st;
		if ((status & 0xC0U) == 0xC0U)
			break;
		HAL_Delay(2U);
	} while ((HAL_GetTick() - start) < 100U);
	if ((status & 0xC0U) != 0xC0U)
		return HAL_TIMEOUT;

	st = DPS310_ReadCoefficients(dev);
	if (st != HAL_OK)
		return st;

	/* Bit7 COEF_SRCE(0x28) must match bit7 TMP_CFG(0x07). */
	uint8_t temp_source = 0U;
	st = DPS310_ReadRegs(dev, REG_COEF_SRCE, &temp_source, 1U);
	if (st != HAL_OK)
		return st;

	/* PRS_CFG(0x06) <- 0x53 = 0101 0011: rate 32 Hz, OSR 8x. */
	st = DPS310_WriteReg(dev, REG_PRS_CFG, 0x53U);
	if (st != HAL_OK)
		return st;

	/* TMP_CFG(0x07) <- 0x20|source: rate 4 Hz, OSR 1x. */
	st = DPS310_WriteReg(dev, REG_TMP_CFG,
			(uint8_t) (0x20U | (temp_source & 0x80U)));
	if (st != HAL_OK)
		return st;

	/* CFG_REG(0x09) <- 0x00: SPI 4-wire, FIFO off, shift bits 0. */
	st = DPS310_WriteReg(dev, REG_CFG, 0x00U);
	if (st != HAL_OK)
		return st;

	/* MEAS_CFG(0x08) <- 0x07: continuous background P+T measurements. */
	st = DPS310_WriteReg(dev, REG_MEAS_CFG, 0x07U);
	if (st != HAL_OK)
		return st;

	dev->initialized = 1U;
	DPS310_ResetHome(dev);
	return HAL_OK;
}

HAL_StatusTypeDef DPS310_ReadIfReady(DPS310_t *dev) {
	if (!dev || !dev->initialized)
		return HAL_ERROR;

	/* Read at most 200 Hz; sensor generates new pressure at 32 Hz. */
	uint32_t now = HAL_GetTick();
	if (dev->last_poll_ms != 0U && (now - dev->last_poll_ms) < 5U)
		return HAL_BUSY;
	dev->last_poll_ms = now;

	uint8_t status = 0U;
	HAL_StatusTypeDef st = DPS310_ReadRegs(dev, REG_MEAS_CFG, &status, 1U);
	if (st != HAL_OK) {
		++dev->error_count;
		return st;
	}
	if ((status & 0x10U) == 0U)
		return HAL_BUSY; /* PRS_RDY=0 */
	if (!dev->valid && (status & 0x20U) == 0U)
		return HAL_BUSY; /* wait first valid temperature */

	/* Read 0x00..0x05: raw24 pressure, raw24 temperature. */
	uint8_t raw[6];
	st = DPS310_ReadRegs(dev, REG_PRS_B2, raw, sizeof(raw));
	if (st != HAL_OK) {
		++dev->error_count;
		return st;
	}

	const float p = (float) DPS310_Raw24(&raw[0]) / DPS310_KP;
	const float t = (float) DPS310_Raw24(&raw[3]) / DPS310_KT;
	/* Polynomial compensation (pressure in Pa, temperature in deg C). */
	const float pressure = (float) dev->c00
			+ p
					* ((float) dev->c10
							+ p * ((float) dev->c20 + p * (float) dev->c30))
			+ t
					* ((float) dev->c01
							+ p * ((float) dev->c11 + p * (float) dev->c21));
	const float temperature = 0.5f * (float) dev->c0 + (float) dev->c1 * t;

	if (!isfinite(pressure) || pressure < 30000.0f || pressure > 120000.0f
			|| !isfinite(temperature) || temperature < -40.0f
			|| temperature > 85.0f) {
		++dev->error_count;
		return HAL_ERROR;
	}

	dev->pressure_pa = pressure;
	dev->temperature_c = temperature;
	if (!dev->valid)
		dev->pressure_filtered_pa = pressure;
	else
		dev->pressure_filtered_pa += DPS310_ALPHA
				* (pressure - dev->pressure_filtered_pa);
	dev->valid = 1U;
	dev->last_update_ms = HAL_GetTick();
	++dev->sample_count;

	/* Approx. absolute altitude uses standard sea level reference 101325 Pa. */
	dev->altitude_isa_m = 44330.0f
			* (1.0f - powf(dev->pressure_filtered_pa / 101325.0f, 0.19029496f));

	/* First 64 valid readings average home pressure (~2 seconds). */
	if (!dev->home_valid) {
		dev->home_pressure_sum += pressure;
		++dev->home_samples;
		if (dev->home_samples >= DPS310_SAMPLE_HOME_COUNT) {
			dev->home_pressure_pa = dev->home_pressure_sum
					/ (float) dev->home_samples;
			dev->home_valid = 1U;
		}
	}
	if (dev->home_valid) {
		dev->altitude_rel_m = 44330.0f
				* (1.0f
						- powf(
								dev->pressure_filtered_pa
										/ dev->home_pressure_pa, 0.19029496f));
	}
	return HAL_OK;
}
