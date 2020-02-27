/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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
#include "gpio.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/** Configure pins
*/
void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
#ifndef ALWAYS_ENABLE
	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = OUTPUT_ON_SWITCH_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(OUTPUT_ON_SWITCH_PORT, &GPIO_InitStruct);

	// Enable interrupts in the NVIC
	HAL_NVIC_SetPriority(EXTI2_3_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);
#endif
#ifdef MANUAL_HALL
    GPIO_InitStruct.Pin = HALL_A_PIN | HALL_B_PIN | HALL_C_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Enable interrupts in the NVIC
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
#endif
#ifndef COMPLIMENTARY_OUTPUT
		GPIO_InitStruct.Pin = PWM_PHASE_U_LOW_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = PWM_PHASE_W_LOW_PIN|PWM_PHASE_V_LOW_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
