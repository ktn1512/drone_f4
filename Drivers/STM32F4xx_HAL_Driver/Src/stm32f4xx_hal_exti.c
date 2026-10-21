#include "stm32f4xx_hal.h"

#ifdef HAL_EXTI_MODULE_ENABLED

HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
{
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;

  if ((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_EXTI_LINE(pExtiConfig->Line));
  assert_param(IS_EXTI_MODE(pExtiConfig->Mode));

  hexti->Line = pExtiConfig->Line;

  linepos = (pExtiConfig->Line & EXTI_PIN_MASK);
  maskline = (1uL << linepos);

  if ((pExtiConfig->Line & EXTI_CONFIG) != 0x00u)
  {
    assert_param(IS_EXTI_TRIGGER(pExtiConfig->Trigger));

    if ((pExtiConfig->Trigger & EXTI_TRIGGER_RISING) != 0x00u)
    {
      EXTI->RTSR |= maskline;
    }
    else
    {
      EXTI->RTSR &= ~maskline;
    }

    if ((pExtiConfig->Trigger & EXTI_TRIGGER_FALLING) != 0x00u)
    {
      EXTI->FTSR |= maskline;
    }
    else
    {
      EXTI->FTSR &= ~maskline;
    }

    if ((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PORT(pExtiConfig->GPIOSel));
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = SYSCFG->EXTICR[linepos >> 2u];
      regval &= ~(SYSCFG_EXTICR1_EXTI0 << (SYSCFG_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
      regval |= (pExtiConfig->GPIOSel << (SYSCFG_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
      SYSCFG->EXTICR[linepos >> 2u] = regval;
    }
  }

  if ((pExtiConfig->Mode & EXTI_MODE_INTERRUPT) != 0x00u)
  {
    EXTI->IMR |= maskline;
  }
  else
  {
    EXTI->IMR &= ~maskline;
  }

  if ((pExtiConfig->Mode & EXTI_MODE_EVENT) != 0x00u)
  {
    EXTI->EMR |= maskline;
  }
  else
  {
    EXTI->EMR &= ~maskline;
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
{
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;

  if ((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  assert_param(IS_EXTI_LINE(hexti->Line));

  pExtiConfig->Line = hexti->Line;

  linepos = (pExtiConfig->Line & EXTI_PIN_MASK);
  maskline = (1uL << linepos);

  if ((EXTI->IMR & maskline) != 0x00u)
  {
    pExtiConfig->Mode = EXTI_MODE_INTERRUPT;
  }
  else
  {
    pExtiConfig->Mode = EXTI_MODE_NONE;
  }

  if ((EXTI->EMR & maskline) != 0x00u)
  {
    pExtiConfig->Mode |= EXTI_MODE_EVENT;
  }

  pExtiConfig->Trigger = EXTI_TRIGGER_NONE;
  pExtiConfig->GPIOSel = 0x00u;

  if ((pExtiConfig->Line & EXTI_CONFIG) != 0x00u)
  {

    if ((EXTI->RTSR & maskline) != 0x00u)
    {
      pExtiConfig->Trigger = EXTI_TRIGGER_RISING;
    }

    if ((EXTI->FTSR & maskline) != 0x00u)
    {
      pExtiConfig->Trigger |= EXTI_TRIGGER_FALLING;
    }

    if ((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = SYSCFG->EXTICR[linepos >> 2u];
      pExtiConfig->GPIOSel = (regval >> (SYSCFG_EXTICR1_EXTI1_Pos * (linepos & 0x03u))) & SYSCFG_EXTICR1_EXTI0;
    }
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti)
{
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;

  if (hexti == NULL)
  {
    return HAL_ERROR;
  }

  assert_param(IS_EXTI_LINE(hexti->Line));

  linepos = (hexti->Line & EXTI_PIN_MASK);
  maskline = (1uL << linepos);

  EXTI->IMR = (EXTI->IMR & ~maskline);

  EXTI->EMR = (EXTI->EMR & ~maskline);

  if ((hexti->Line & EXTI_CONFIG) != 0x00u)
  {
    EXTI->RTSR = (EXTI->RTSR & ~maskline);
    EXTI->FTSR = (EXTI->FTSR & ~maskline);

    if ((hexti->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = SYSCFG->EXTICR[linepos >> 2u];
      regval &= ~(SYSCFG_EXTICR1_EXTI0 << (SYSCFG_EXTICR1_EXTI1_Pos * (linepos & 0x03u)));
      SYSCFG->EXTICR[linepos >> 2u] = regval;
    }
  }

  return HAL_OK;
}

HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void))
{
  HAL_StatusTypeDef status = HAL_OK;

  switch (CallbackID)
  {
    case  HAL_EXTI_COMMON_CB_ID:
      hexti->PendingCallback = pPendingCbfn;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}

HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine)
{

  assert_param(IS_EXTI_LINE(ExtiLine));

  if (hexti == NULL)
  {
    return HAL_ERROR;
  }
  else
  {

    hexti->Line = ExtiLine;

    return HAL_OK;
  }
}

void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti)
{
  uint32_t regval;
  uint32_t maskline;

  maskline = (1uL << (hexti->Line & EXTI_PIN_MASK));

  regval = (EXTI->PR & maskline);
  if (regval != 0x00u)
  {

    EXTI->PR = maskline;

    if (hexti->PendingCallback != NULL)
    {
      hexti->PendingCallback();
    }
  }
}

uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;

  UNUSED(Edge);

  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  linepos = (hexti->Line & EXTI_PIN_MASK);
  maskline = (1uL << linepos);

  regval = ((EXTI->PR & maskline) >> linepos);
  return regval;
}

void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  uint32_t maskline;

  UNUSED(Edge);

  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  maskline = (1uL << (hexti->Line & EXTI_PIN_MASK));

  EXTI->PR =  maskline;
}

void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti)
{
  uint32_t maskline;

  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));

  maskline = (1uL << (hexti->Line & EXTI_PIN_MASK));

  EXTI->SWIER = maskline;
}

#endif
