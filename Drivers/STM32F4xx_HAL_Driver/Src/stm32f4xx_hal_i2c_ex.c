#include "stm32f4xx_hal.h"

#ifdef HAL_I2C_MODULE_ENABLED

#if  defined(I2C_FLTR_ANOFF)&&defined(I2C_FLTR_DNF)

HAL_StatusTypeDef HAL_I2CEx_ConfigAnalogFilter(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter)
{

  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  assert_param(IS_I2C_ANALOG_FILTER(AnalogFilter));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    hi2c->State = HAL_I2C_STATE_BUSY;

    __HAL_I2C_DISABLE(hi2c);

    hi2c->Instance->FLTR &= ~(I2C_FLTR_ANOFF);

    hi2c->Instance->FLTR |= AnalogFilter;

    __HAL_I2C_ENABLE(hi2c);

    hi2c->State = HAL_I2C_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

HAL_StatusTypeDef HAL_I2CEx_ConfigDigitalFilter(I2C_HandleTypeDef *hi2c, uint32_t DigitalFilter)
{
  uint16_t tmpreg = 0;

  assert_param(IS_I2C_ALL_INSTANCE(hi2c->Instance));
  assert_param(IS_I2C_DIGITAL_FILTER(DigitalFilter));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    hi2c->State = HAL_I2C_STATE_BUSY;

    __HAL_I2C_DISABLE(hi2c);

    tmpreg = hi2c->Instance->FLTR;

    tmpreg &= ~(I2C_FLTR_DNF);

    tmpreg |= DigitalFilter;

    hi2c->Instance->FLTR = tmpreg;

    __HAL_I2C_ENABLE(hi2c);

    hi2c->State = HAL_I2C_STATE_READY;

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

#endif

#endif
