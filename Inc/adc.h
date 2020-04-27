/**
  ******************************************************************************
  * File Name          : ADC.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

 typedef enum
 {
	 ADC_Voltage_Phase_U = 0,
	 ADC_Voltage_Phase_V,
	 ADC_Voltage_Phase_W,
	 ADC_Throttle,
 }adcChannel_t;
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define NUM_ADC_CHANNEL				(4U)
#define THROTTLE_AVERAGE_CONST		(4U)

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;
uint32_t adc_buffer[NUM_ADC_CHANNEL];

adcChannel_t currentChannel;


void MX_ADC_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
