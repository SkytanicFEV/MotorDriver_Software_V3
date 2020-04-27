/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define VOLTAGE_PHASE_U_PIN 			GPIO_PIN_0
#define VOLTAGE_PHASE_U_PORT 			GPIOA
#define VOLTAGE_PHASE_V_PIN 			GPIO_PIN_1
#define VOLTAGE_PHASE_V_PORT 			GPIOA
#define VOLTAGE_PHASE_W_PIN 			GPIO_PIN_2
#define VOLTAGE_PHASE_W_PORT 			GPIOA
#define THROTTLE_PIN 					GPIO_PIN_6
#define THROTTLE_GPIO_PORT 				GPIOA
#define PWM_PHASE_U_LOW_PIN 			GPIO_PIN_7
#define PWM_PHASE_U_LOW_PORT 			GPIOA
#define PWM_PHASE_W_LOW_PIN 			GPIO_PIN_1
#define PWM_PHASE_W_LOW_PORT 			GPIOB
#define PWM_PHASE_V_LOW_PIN 			GPIO_PIN_0
#define PWM_PHASE_V_LOW_PORT 			GPIOB
#define HALL_A_PIN 						GPIO_PIN_6
#define HALL_A_PORT 					GPIOC
#define HALL_B_PIN 						GPIO_PIN_8
#define HALL_B_PORT 					GPIOC
#define HALL_C_PIN 						GPIO_PIN_7
#define HALL_C_PORT 					GPIOC
#define PWM_PHASE_U_HIGH_PIN 			GPIO_PIN_8
#define PWM_PHASE_U_HIGH_PORT 			GPIOA
#define PWM_PHASE_W_HIGH_PIN 			GPIO_PIN_9
#define PWM_PHASE_W_HIGH_PORT 			GPIOA
#define PWM_PHASE_V_HIGH_PIN 			GPIO_PIN_10
#define PWM_PHASE_V_HIGH_PORT 			GPIOA
#define MASTER_HEARTBEAT_PIN 			GPIO_PIN_11
#define MASTER_HEARTBEAT_PORT 			GPIOA
#define EXTERNAL_TRIGGER_PIN 			GPIO_PIN_12
#define EXTERNAL_TRIGGER_PORT 			GPIOA
#define OUTPUT_ON_SWITCH_PIN 			GPIO_PIN_2
#define OUTPUT_ON_SWITCH_PORT 			GPIOD

void MX_GPIO_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
