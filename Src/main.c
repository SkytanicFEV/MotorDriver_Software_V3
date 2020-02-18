/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{



	// Start with the phase U voltage channel on the ADC
	currentChannel = ADC_Throttle;

	/* MCU Configuration--------------------------------------------------------*/

	// Reset of all peripherals, Initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Initialize all configured peripherals
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();
	MX_USART1_UART_Init();

#ifdef ALWAYS_ENABLE
	motorEnable = Enabled;
//	EnableMotorDriver();
#else
	motorEnable = Disabled;
#endif

//	// Start the DMA transfer
//	if(HAL_ADC_Start_DMA(&hadc, adc_buffer, NUM_ADC_CHANNEL) != HAL_OK)
//	{
//		Error_Handler();
//	}
//
//	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
//	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	// Infinite loop
	while (1)
	{
//		// Update the timer capture compares
//		TIM1->CCR1 = (uint16_t) waveformAmplitude;
//		TIM1->CCR2 = (uint16_t) waveformAmplitude;
//		TIM1->CCR3 = (uint16_t) waveformAmplitude;
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	// Initializes the CPU, AHB and APB busses clocks
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.HSI14CalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL10;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	// Initializes the CPU, AHB and APB busses clocks
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
							  | RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief  Handles call backs from EXTI interrupts
  * @param  Pin that was interrupted
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Check to see if the master clock pin was interrupted
	if(GPIO_Pin == OUTPUT_ON_SWITCH_PIN)
	{
		if(GPIOD->IDR & OUTPUT_ON_SWITCH_PIN)
		{
			EnableMotorDriver();
		}
		else
		{
			DisableMotorDriver();
		}

	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * hadc)
{
	switch(currentChannel)
	{
	case(ADC_Voltage_Phase_U):
		// Update state machine to the next channel
		currentChannel = ADC_Voltage_Phase_V;
		break;
	case(ADC_Voltage_Phase_V):
		// Update state machine to the next channel
		currentChannel = ADC_Voltage_Phase_W;
		break;
	case(ADC_Voltage_Phase_W):
		// Update state machine to the next channel
		currentChannel = ADC_Throttle;
		break;
	case(ADC_Throttle):
		// Get the current ADC conversion
		throttleValue = (ADC1->DR / 2) + (throttleValue / 2);
		// Update the waveform amplitudes
		waveformAmplitude = TIM_PERIOD * throttleValue / (THROTTLE_MAX_VALUE);
		// Check for maximums
		if(waveformAmplitude > MAX_AMPLITUDE)
		{
			waveformAmplitude = MAX_AMPLITUDE;
		}
		else if(waveformAmplitude < MIN_AMPLITUDE)
		{
			waveformAmplitude = MIN_AMPLITUDE;
		}
		// Update the timer capture compares
		TIM1->CCR1 = (uint16_t) waveformAmplitude;
		TIM1->CCR2 = (uint16_t) waveformAmplitude;
		TIM1->CCR3 = (uint16_t) waveformAmplitude;
		// Update the state machine back to the beginning
//		currentChannel = ADC_Voltage_Phase_U;
		break;
	default:
		break;
	}

}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

}

//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
//{
//
//}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

	// Enter an infinite loop for debugging
	while(1)
	{

	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
