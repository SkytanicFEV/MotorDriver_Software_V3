/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

	int dummy;
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_adc);
}

/**
  * @brief This function handles pins 2 and 3 external interrupts
  */
void EXTI2_3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(OUTPUT_ON_SWITCH_PIN);
}

/**
  * @brief This function handles pins 4 to 15 external interrupts
  */
void EXTI4_15_IRQHandler(void)
{
	// Check for hall A interrupt
	if(__HAL_GPIO_EXTI_GET_IT(HALL_A_PIN) != RESET)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(HALL_A_PIN);
		HAL_GPIO_EXTI_Callback(HALL_A_PIN);
	}
	// Check for hall B interrupt
	if(__HAL_GPIO_EXTI_GET_IT(HALL_B_PIN) != RESET)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(HALL_B_PIN);
		HAL_GPIO_EXTI_Callback(HALL_B_PIN);
	}
	// Check for hall C interrupt
	if(__HAL_GPIO_EXTI_GET_IT(HALL_C_PIN) != RESET)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(HALL_C_PIN);
		HAL_GPIO_EXTI_Callback(HALL_C_PIN);
	}
	// Check for external interrupt
	if(__HAL_GPIO_EXTI_GET_IT(EXTERNAL_TRIGGER_PIN) != RESET)
	{
		__HAL_GPIO_EXTI_CLEAR_IT(EXTERNAL_TRIGGER_PIN);
		HAL_GPIO_EXTI_Callback(EXTERNAL_TRIGGER_PIN);
	}
}

/**
  * @brief This function handles ADC 1 interrupts
  */
void ADC1_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&hadc);
}

/**
  * @brief This function handles timer 1 capture compare interrupts
  */
void TIM1_CC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim1);
}

/**
  * @brief This function handles USART 1 interrupts
  */
void USART1_IRQHandler(void)
{
	static uint8_t last_char;
	// Get the character received over UART
	rx_buffer[last_char] = huart1.Instance->RDR;
	if(rx_buffer[last_char] == BOARD_ADDRESS)
	{
		last_char++;
		// If the character was the board address then set up the TX to begin transmitting
		// This is done so that both boards are not messing with the inter-board communication
		GPIO_InitTypeDef GPIO_InitStruct = {0};
	    GPIO_InitStruct.Pin = GPIO_PIN_6;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	else if((rx_buffer[last_char] == RPM_MESSAGE) && (rx_buffer[last_char - 1] == BOARD_ADDRESS))
	{
		// Convert the rpm to a string and send it back to the IO board
		uint8_t msg[3];
		IntToString(rpm, msg, 3);
		HAL_UART_Transmit(&huart1, msg, 3, 1000);
		last_char = 0;

	}
	else
	{
		// Once communication is done reset the TX pin so that it does not mess with communication
		GPIO_InitTypeDef GPIO_InitStruct = {0};
	    GPIO_InitStruct.Pin = GPIO_PIN_6;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF0_USART1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	// Call the HAL interrupt handler to properly deal with interrupt
	HAL_UART_IRQHandler(&huart1);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
