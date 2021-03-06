/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

// TIM1 init function
void MX_TIM1_Init(void)
{
	TIM_SlaveConfigTypeDef sSlaveConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	// Set up timer 1 in up mode with no prescaler or division
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = TIM_PERIOD;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
#ifndef MASTER
//	sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
//	sSlaveConfig.InputTrigger = TIM_TS_ETRF;
//	sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_RISING;
//	sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPOLARITY_BOTHEDGE;
//	sSlaveConfig.TriggerFilter = 0;
//	if (HAL_TIM_SlaveConfigSynchronization(&htim1, &sSlaveConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}

//	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0; /* (1)*/
//	TIM1->CCER &= (uint16_t)(~TIM_CCER_CC1P); /* (2) */
//	TIM1->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_TS_2 | TIM_SMCR_TS_0; /* (3) */
//	TIM1->PSC = 47999; /* (4) */
//	TIM1->CR1 |= TIM_CR1_CEN;
#endif

	// Setup the PWM channels
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
#ifdef MASTER
	// If the board is the master output a sqare wave at the switching frequency for synchronization
	sConfigOC.Pulse = TIM_PERIOD / 2;
	if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
#endif
#ifdef COMPLIMENTARY_OUTPUT
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = PWM_DEADTIME;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_ENABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
#endif
//#ifdef ALWAYS_ENABLE
	HAL_TIM_MspPostInit(&htim1);
//#endif

	// Enable clock tree
	__HAL_RCC_TIM1_CLK_ENABLE();

	// Start Channel 1 Waveforms
	if(HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	// Start Channel 2 Waveforms
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	// Start Channel 3 Waveforms
	if(HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}

#ifdef COMPLIMENTARY_OUTPUT
	// Start Channel 1 Negative Waveforms
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	// Start Channel 2 Negative Waveforms
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	// Start Channel 3 Negative Waveforms
	if(HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
#endif

#ifdef MASTER
	// Start Channel 4 Waveforms
	if(HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
#endif

	// Configure and enable TIM3 interrupt channel in NVIC
	HAL_NVIC_SetPriority(TIM1_CC_IRQn, 3, 0);
	HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
}

// TIM3 init function
// This timer was an option to be used for Hall effect feedback in hardware, but it was never implemented
void MX_TIM3_Init(void)
{
	TIM_HallSensor_InitTypeDef sConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 0;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.Commutation_Delay = 0;
	if (HAL_TIMEx_HallSensor_Init(&htim3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_OC2REF;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

// Microprocessor specific timer base initialization
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tim_baseHandle->Instance==TIM1)
  {
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM1 GPIO Configuration    
    PA12     ------> TIM1_ETR 
    */
    GPIO_InitStruct.Pin = EXTERNAL_TRIGGER_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(EXTERNAL_TRIGGER_PORT, &GPIO_InitStruct);
  }
}

// Microprocessor specific hall sensor initialization
void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef* timex_hallsensorHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timex_hallsensorHandle->Instance==TIM3)
  {
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM3 GPIO Configuration    
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2
    PC8     ------> TIM3_CH3 
    */
    GPIO_InitStruct.Pin = HALL_A_PIN|HALL_B_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = HALL_C_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
    HAL_GPIO_Init(HALL_C_PORT, &GPIO_InitStruct);
  }
}

// Microprocessor specific timer initialization
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(timHandle->Instance==TIM1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**TIM1 GPIO Configuration
		PA7     ------> TIM1_CH1N
		PB0     ------> TIM1_CH2N
		PB1     ------> TIM1_CH3N
		PA8     ------> TIM1_CH1
		PA9     ------> TIM1_CH2
		PA10     ------> TIM1_CH3
		PA11     ------> TIM1_CH4
		*/
		GPIO_InitStruct.Pin = PWM_PHASE_U_HIGH_PIN|PWM_PHASE_W_HIGH_PIN|PWM_PHASE_V_HIGH_PIN
							  |MASTER_HEARTBEAT_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#ifdef COMPLIMENTARY_OUTPUT
		GPIO_InitStruct.Pin = PWM_PHASE_U_LOW_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = PWM_PHASE_W_LOW_PIN|PWM_PHASE_V_LOW_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
	}
}

// Microprocessor specific de-initialization function
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();
  
    /**TIM1 GPIO Configuration    
    PA7     ------> TIM1_CH1N
    PB0     ------> TIM1_CH2N
    PB1     ------> TIM1_CH3N
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2
    PA10     ------> TIM1_CH3
    PA11     ------> TIM1_CH4
    PA12     ------> TIM1_ETR 
    */
    HAL_GPIO_DeInit(GPIOA, PWM_PHASE_U_LOW_PIN|PWM_PHASE_U_HIGH_PIN|PWM_PHASE_W_HIGH_PIN|PWM_PHASE_V_HIGH_PIN 
                          |MASTER_HEARTBEAT_PIN|EXTERNAL_TRIGGER_PIN);

    HAL_GPIO_DeInit(GPIOB, PWM_PHASE_W_LOW_PIN|PWM_PHASE_V_LOW_PIN);
  }
}

// Microprocessor specific timer de-initialization function
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef* timex_hallsensorHandle)
{

  if(timex_hallsensorHandle->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  
    /**TIM3 GPIO Configuration    
    PC6     ------> TIM3_CH1
    PC7     ------> TIM3_CH2
    PC8     ------> TIM3_CH3 
    */
    HAL_GPIO_DeInit(GPIOC, HALL_A_PIN|HALL_B_PIN|HALL_C_PIN);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
