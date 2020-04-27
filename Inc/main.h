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
#include "control.h"
#include "adc.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "stringConvert.h"

// Enum for phases
typedef enum
{
	phase_U = 0,
	phase_V,
	phase_W,
}phase_t;

// Enum for enable/disbale
typedef enum
{
	Disabled = 0,
	Enabled
}enable_t;

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

// Un-comment this to have the motor driver always enabled
//#define ALWAYS_ENABLE
// Comment this to disable complimentary waveforms
//#define COMPLIMENTARY_OUTPUT
// Un-comment this to use a manual hall effect control algorithm
#define MANUAL_HALL

// Comment this to make the board a slave
#define MASTER

#ifdef MASTER
#define BOARD_ADDRESS						((uint8_t) '1')
#else
#define BOARD_ADDRESS						((uint8_t) '2')
#endif

// Number of poles in the motor
#define NUM_POLES							(4U)

/* Private defines -----------------------------------------------------------*/

// Number of timer counts since last HAL interrupt
uint32_t hall_tim_counts;
volatile uint16_t rpm;

// Status of motor enable
enable_t motorEnable;

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
