#include "main.h"
#include "stm32f4xx_it.h"

extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;

void NMI_Handler(void)
{

   while (1)
  {
  }

}

void HardFault_Handler(void)
{

  while (1)
  {

  }
}

void MemManage_Handler(void)
{

  while (1)
  {

  }
}

void BusFault_Handler(void)
{

  while (1)
  {

  }
}

void UsageFault_Handler(void)
{

  while (1)
  {

  }
}

void SVC_Handler(void)
{

}

void DebugMon_Handler(void)
{

}

void PendSV_Handler(void)
{

}

void SysTick_Handler(void)
{

  HAL_IncTick();

}

void USART1_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart1);

}

void DMA2_Stream1_IRQHandler(void)
{

  HAL_DMA_IRQHandler(&hdma_usart6_rx);

}

void DMA2_Stream6_IRQHandler(void)
{

  HAL_DMA_IRQHandler(&hdma_usart6_tx);

}

void USART6_IRQHandler(void)
{

  HAL_UART_IRQHandler(&huart6);

}
