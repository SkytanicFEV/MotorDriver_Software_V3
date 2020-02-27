/*
 * it_callbacks.c
 *
 *  Created on: Feb 25, 2020
 *      Author: alex
 */

#include "main.h"


/**
  * @brief  Handles call backs from EXTI interrupts
  * @param  Pin that was interrupted
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// Check to see if the output enable pin was interrupted
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
	if(GPIO_Pin == HALL_A_PIN)
	{
		FindWaveformPhase();
		UpdateWaveforms();
	}
	if(GPIO_Pin == HALL_B_PIN)
	{
		FindWaveformPhase();
		UpdateWaveforms();
	}
	if(GPIO_Pin == HALL_C_PIN)
	{
		FindWaveformPhase();
		UpdateWaveforms();
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
		// Update the timer capture compares if they should be running
		if(phaseU_State == phaseHigh)
		{
			TIM1->CCR1 = (uint16_t) waveformAmplitude;
		}
		if(phaseV_State == phaseHigh)
		{
			TIM1->CCR2 = (uint16_t) waveformAmplitude;
		}
		if(phaseW_State == phaseHigh)
		{
			TIM1->CCR3 = (uint16_t) waveformAmplitude;
		}
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
