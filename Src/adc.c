/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* ADC init function */
void MX_ADC_Init(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.LowPowerAutoPowerOff = DISABLE;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	hadc.Init.DMAContinuousRequests = DISABLE;
	hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel to be converted.
	*/
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
//	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/** Configure for the selected ADC regular channel to be converted.
//	*/
//	sConfig.Channel = ADC_CHANNEL_1;
//	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/** Configure for the selected ADC regular channel to be converted.
//	*/
//	sConfig.Channel = ADC_CHANNEL_2;
//	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
	/** Configure for the selected ADC regular channel to be converted.
	*/
	sConfig.Channel = ADC_CHANNEL_6;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_NVIC_SetPriority(ADC1_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(ADC1_IRQn);

	// Calibrate ADC
	HAL_ADCEx_Calibration_Start(&hadc);

	// Micro Specific Processor Initiation
	HAL_ADC_MspInit(&hadc);

	if(HAL_ADC_Start_IT(&hadc) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(adcHandle->Instance==ADC1)
	{
		/* ADC1 clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**ADC GPIO Configuration
		PA0     ------> ADC_IN0
		PA1     ------> ADC_IN1
		PA2     ------> ADC_IN2
		PA6     ------> ADC_IN6
		*/
		GPIO_InitStruct.Pin = VOLTAGE_PHASE_U_PIN|VOLTAGE_PHASE_V_PIN|VOLTAGE_PHASE_W_PIN|THROTTLE_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* ADC1 DMA Init */
		/* ADC Init */
		hdma_adc.Instance = DMA1_Channel1;
		hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc.Init.Mode = DMA_CIRCULAR;
		hdma_adc.Init.Priority = DMA_PRIORITY_HIGH;
		if (HAL_DMA_Init(&hdma_adc) != HAL_OK)
		{
		  Error_Handler();
		}

		__HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc);
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

	if(adcHandle->Instance==ADC1)
	{
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC GPIO Configuration
		PA0     ------> ADC_IN0
		PA1     ------> ADC_IN1
		PA2     ------> ADC_IN2
		PA6     ------> ADC_IN6
		*/
		HAL_GPIO_DeInit(GPIOA, VOLTAGE_PHASE_U_PIN|VOLTAGE_PHASE_V_PIN|VOLTAGE_PHASE_W_PIN|THROTTLE_PIN);

		/* ADC1 DMA DeInit */
		HAL_DMA_DeInit(adcHandle->DMA_Handle);
	}
} 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
