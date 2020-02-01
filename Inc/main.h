/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

// Enum for phases
typedef enum
{
	phase_U = 0,
	phase_V,
	phase_W,
}phase_t;

// Enum describing output state
typedef enum
{
	outputOff = 0,
	outputOn,
}outputState_t;

// Enum describing the state of each phase
typedef enum
{
	phaseOff = 0,
	phaseHigh,
	phaseLow,
}phaseState_t;

// Enum describing the phase of the waveform
typedef enum
{
	waveform_NoWaveform = 0,
	waveform_Phase1 = 1,
	waveform_Phase2,
	waveform_Phase3,
	waveform_Phase4,
	waveform_Phase5,
	waveform_Phase6,
}waveformPhase_t;

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define BUTTON_PIN 						GPIO_PIN_13
#define BUTTON_PORT 					GPIOC
#define VOLTAGE_PHASE_U_PIN 			GPIO_PIN_0
#define VOLTAGE_PHASE_U_PORT 			GPIOA
#define VOLTAGE_PHASE_V_PIN 			GPIO_PIN_1
#define VOLTAGE_PHASE_V_PORT 			GPIOA
#define VOLTAGE_PHASE_W_PIN 			GPIO_PIN_2
#define VOLTAGE_PHASE_W_PORT 			GPIOA
#define CURRENT_PHASE_U_PIN 			GPIO_PIN_3
#define CURRENT_PHASE_U_PORT 			GPIOA
#define CURRENT_PHASE_V_PIN 			GPIO_PIN_4
#define CURRENT_PHASE_V_PORT 			GPIOA
#define CURRENT_PHASE_W_PIN 			GPIO_PIN_5
#define CURRENT_PHASE_W_PORT 			GPIOA
#define THROTTLE_PIN 					GPIO_PIN_6
#define THROTTLE_PORT 					GPIOA
#define PWM_PHASE_U_LOW_PIN 			GPIO_PIN_7
#define PWM_PHASE_U_LOW_PORT 			GPIOA
#define HALL_C_PIN 						GPIO_PIN_11
#define HALL_C_PORT 					GPIOB
#define HALL_A_PIN 						GPIO_PIN_12
#define HALL_A_PORT 					GPIOB
#define HALL_B_PIN 						GPIO_PIN_13
#define HALL_B_PORT 					GPIOB
#define PWM_PHASE_W_HIGH_PIN 			GPIO_PIN_14
#define PWM_PHASE_W_HIGH_PORT 			GPIOB
#define PWM_PHASE_W_LOW_PIN 			GPIO_PIN_15
#define PWM_PHASE_W_LOW_PORT 			GPIOB
#define PWM_PHASE_V_LOW_PIN 			GPIO_PIN_6
#define PWM_PHASE_V_LOW_PORT 			GPIOC
#define PWM_PHASE_V_HIGH_PIN 			GPIO_PIN_7
#define PWM_PHASE_V_HIGH_PORT 			GPIOC
#define PWM_PHASE_U_HIGH_PIN 			GPIO_PIN_8
#define PWM_PHASE_U_HIGH_PORT 			GPIOA

// Frequency of the processor in KHz
#define PROC_FREQ_KHZ					40000U

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
