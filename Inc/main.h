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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VOLTAGE_PHASE_U_Pin GPIO_PIN_0
#define VOLTAGE_PHASE_U_GPIO_Port GPIOA
#define VOLTAGE_PHASE_V_Pin GPIO_PIN_1
#define VOLTAGE_PHASE_V_GPIO_Port GPIOA
#define VOLTAGE_PHASE_W_Pin GPIO_PIN_2
#define VOLTAGE_PHASE_W_GPIO_Port GPIOA
#define THROTTLE_Pin GPIO_PIN_6
#define THROTTLE_GPIO_Port GPIOA
#define PWM_PHASE_U_LOW_Pin GPIO_PIN_7
#define PWM_PHASE_U_LOW_GPIO_Port GPIOA
#define PWM_PHASE_W_LOW_Pin GPIO_PIN_0
#define PWM_PHASE_W_LOW_GPIO_Port GPIOB
#define PWM_PHASE_V_LOW_Pin GPIO_PIN_1
#define PWM_PHASE_V_LOW_GPIO_Port GPIOB
#define HAL_A_Pin GPIO_PIN_6
#define HAL_A_GPIO_Port GPIOC
#define HAL_B_Pin GPIO_PIN_7
#define HAL_B_GPIO_Port GPIOC
#define HAL_C_Pin GPIO_PIN_8
#define HAL_C_GPIO_Port GPIOC
#define PWM_PHASE_U_HIGH_Pin GPIO_PIN_8
#define PWM_PHASE_U_HIGH_GPIO_Port GPIOA
#define PWM_PHASE_W_HIGH_Pin GPIO_PIN_9
#define PWM_PHASE_W_HIGH_GPIO_Port GPIOA
#define PWM_PHASE_V_HIGH_Pin GPIO_PIN_10
#define PWM_PHASE_V_HIGH_GPIO_Port GPIOA
#define MASTER_HEARTBEAT_Pin GPIO_PIN_11
#define MASTER_HEARTBEAT_GPIO_Port GPIOA
#define EXTERNAL_TRIGGER_Pin GPIO_PIN_12
#define EXTERNAL_TRIGGER_GPIO_Port GPIOA
#define OUTPUT_ON_SWITCH_Pin GPIO_PIN_2
#define OUTPUT_ON_SWITCH_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
