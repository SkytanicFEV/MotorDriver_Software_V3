/*
 * control.c
 *
 *  Created on: Dec 5, 2019
 *      Author: alex
 */

#include "control.h"

/**
  * @brief Function to enable the motor driver output
  * @param none
  * @retval none
  */
void EnableMotorDriver(void)
{
	// Only need to enable if the board is disabled
	if(motorEnable == Disabled)
	{
		HAL_TIM_MspPostInit(&htim1);

		motorEnable = Enabled;
	}
}

/**
  * @brief Function to enable the motor driver output
  * @param none
  * @retval none
  */
void DisableMotorDriver(void)
{
	// Only need to disable if the board is enabled
	if(motorEnable == Enabled)
	{
//	    HAL_GPIO_DeInit(GPIOA, PWM_PHASE_U_LOW_PIN | PWM_PHASE_U_HIGH_PIN | PWM_PHASE_W_HIGH_PIN | PWM_PHASE_V_HIGH_PIN
//	                          | MASTER_HEARTBEAT_PIN | EXTERNAL_TRIGGER_PIN);
//
//	    HAL_GPIO_DeInit(GPIOB, PWM_PHASE_W_LOW_PIN | PWM_PHASE_V_LOW_PIN);

		motorEnable = Disabled;

	}
}

/**
  * @brief Function to find the waveform phase based on the hall effect values
  * @param none
  * @retval none
  */
void FindWaveformPhase(void)
{
	if(GPIOC->IDR & HALL_A_PIN)
	{
		if(GPIOC->IDR & HALL_B_PIN)
		{
			waveformPhase = waveform_Phase4;
		}
		else if(GPIOC->IDR & HALL_C_PIN)
		{
			waveformPhase = waveform_Phase6;

		}
		else
		{
			waveformPhase = waveform_Phase5;
		}
	}
	else
	{
		if(GPIOC->IDR & HALL_B_PIN)
		{
			if(GPIOC->IDR & HALL_C_PIN)
			{
				waveformPhase = waveform_Phase2;

			}
			else
			{
				waveformPhase = waveform_Phase3;

			}
		}
		else
		{
			if(GPIOC->IDR & HALL_C_PIN)
			{
				waveformPhase = waveform_Phase1;
			}
			// If none of the hall effect outputs are active then there is a problem
			else
			{
				waveformPhase = waveform_NoWaveform;
			}

		}
	}
}

/**
  * @brief Function to start the waveforms and turn on the output
  * @param none
  * @retval none
  */
void StartWaveforms(void)
{
	// Look at the hall effects to determine the phase
	FindWaveformPhase();

	// Update the waveforms based on hall effect values
	UpdateWaveforms();
	// Update output status
	outputState = outputOn;
}

/**
  * @brief Function to stop the waveforms and turn off the output
  * @param none
  * @retval none
  */
void StopWaveforms(void)
{
	// Turn off all high side
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;

	// Update output status
	outputState = outputOff;
}

/**
  * @brief Function to update the three waveforms
  * @param none
  * @retval none
  */
void UpdateWaveforms(void)
{
	switch(waveformPhase)
	{
	// TODO Use forced output
	case waveform_Phase1:
		// Turn on phase U high side
		TIM1->CCR1 = waveformAmplitude;
		// Turn off phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, RESET);
    	// Update phase state
    	phaseU_State = phaseHigh;

    	// Turn off phase V high side
    	TIM1->CCR2 = 0;
    	// Turn on phase V low side
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, SET);
    	// Update phase state
    	phaseV_State = phaseLow;

    	// Turn off phase W high side
    	TIM1->CCR3 = 0;
    	// Turn off phase W low side
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, RESET);
    	// Update phase state
    	phaseW_State = phaseOff;
		return;
	case waveform_Phase2:
		// Turn off phase U high side
		TIM1->CCR1 = 0;
		// Turn off phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, RESET);
    	// Update phase state
    	phaseU_State = phaseOff;

    	// Turn off phase V high side
    	TIM1->CCR2 = 0;
    	// Turn on phase V low side
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, SET);
    	// Update phase state
    	phaseV_State = phaseLow;

    	// Turn on phase W high side
    	TIM1->CCR3 = waveformAmplitude;
    	// Turn off phase W low side
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, RESET);
    	// Update phase state
    	phaseW_State = phaseHigh;
		return;
	case waveform_Phase3:
		// Turn off phase U high side
		TIM1->CCR1 = 0;
		// Turn on phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, SET);
    	// Update phase state
    	phaseU_State = phaseLow;

    	// Turn off phase V high side
    	TIM1->CCR2 = 0;
    	// Turn off phase V low side
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, RESET);
    	// Update phase state
    	phaseV_State = phaseOff;

    	// Turn on phase W high side
    	TIM1->CCR3 = waveformAmplitude;
    	// Turn off phase W low side (will get turned back on in interrupts)
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, RESET);
    	// Update phase state
    	phaseW_State = phaseHigh;
		return;
	case waveform_Phase4:
		// Turn off phase U high side
		TIM1->CCR1 = 0;
		// Turn on phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, SET);
    	// Update phase state
    	phaseU_State = phaseLow;

    	// Turn on phase V high side
    	TIM1->CCR2 = waveformAmplitude;
    	// Turn on phase V low side (will get turned back on in interrupts)
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, RESET);
    	// Update phase state
    	phaseV_State = phaseHigh;

    	// Turn off phase W high side
    	TIM1->CCR3 = 0;
    	// Turn off phase W low side
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, RESET);
    	// Update phase state
    	phaseW_State = phaseOff;
		return;
	case waveform_Phase5:
		// Turn off phase U high side
		TIM1->CCR1 = 0;
		// Turn off phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, RESET);
    	// Update phase state
    	phaseU_State = phaseOff;

    	// Turn on phase V high side
    	TIM1->CCR2 = waveformAmplitude;
    	// Turn on phase V low side
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, RESET);
    	// Update phase state
    	phaseV_State = phaseHigh;

    	// Turn off phase W high side
    	HAL_GPIO_WritePin(PWM_PHASE_W_HIGH_PORT, PWM_PHASE_W_HIGH_PIN, RESET);
    	TIM1->CCR3 = 0;
    	// Turn on phase W low side
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, SET);
    	// Update phase state
    	phaseW_State = phaseLow;
		return;
	case waveform_Phase6:
		// Turn on phase U high side
		TIM1->CCR1 = waveformAmplitude;
		// Turn off phase U low side
    	HAL_GPIO_WritePin(PWM_PHASE_U_LOW_PORT, PWM_PHASE_U_LOW_PIN, RESET);
    	// Update phase state
    	phaseU_State = phaseHigh;

    	// Turn off phase V high side
    	TIM1->CCR2 = 0;
    	// Turn on phase V low side
    	HAL_GPIO_WritePin(PWM_PHASE_V_LOW_PORT, PWM_PHASE_V_LOW_PIN, RESET);
    	// Update phase state
    	phaseV_State = phaseOff;

    	// Turn off phase W high side
    	TIM1->CCR3 = 0;
    	// Turn on phase W low side
    	HAL_GPIO_WritePin(PWM_PHASE_W_LOW_PORT, PWM_PHASE_W_LOW_PIN, SET);
    	// Update phase state
    	phaseW_State = phaseLow;
		return;
	default:
		// If none of the phases are detected then turn off the output
		StopWaveforms();

		return;
	}
}

/**
  * @brief Function to calculate RPM of the motor
  * @param none
  * @retval none
  */
void CalculateRPM(void)
{
	// Calculate the RPM
	rpm = 50000 / hall_tim_counts * 60;
	rpm = rpm/NUM_POLES;

	// Reset the hall timer counts
	hall_tim_counts = 0;
}
