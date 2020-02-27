/*
 * control.h
 *
 *  Created on: Jan 14, 2020
 *      Author: alex
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "main.h"

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

// Enum describing output state
typedef enum
{
	outputOff = 0,
	outputOn,
}outputState_t;

// Deadtime of the PWM
#define PWM_DEADTIME					(10U)
// Maximum ADC value of the throttle
#define THROTTLE_MAX_VALUE				((uint16_t) 1040)
// Maximum pulse width
#define MAX_AMPLITUDE					((uint32_t) (TIM_PERIOD * .9))
// Minimum pulse width
#define MIN_AMPLITUDE					((uint32_t) 50)


// Switch state variables
phaseState_t phaseU_State;
phaseState_t phaseW_State;
phaseState_t phaseV_State;

// Throttle variables
uint16_t throttleValue;

// Max value of output waveform
uint32_t waveformAmplitude;

// Current phase of the output waveforms
waveformPhase_t waveformPhase;

// Current state of the output
outputState_t outputState;

/**
  * @brief Function to enable the motor driver output
  * @param none
  * @retval none
  */
void EnableMotorDriver(void);

/**
  * @brief Function to enable the motor driver output
  * @param none
  * @retval none
  */
void DisableMotorDriver(void);

/**
  * @brief Function to find the waveform phase based on the hall effect values
  * @param none
  * @retval none
  */
void FindWaveformPhase(void);

/**
  * @brief Function to start the waveforms and turn on the output
  * @param none
  * @retval none
  */
void StartWaveforms(void);

/**
  * @brief Function to stop the waveforms and turn off the output
  * @param none
  * @retval none
  */
void StopWaveforms(void);

/**
  * @brief Function to update the three waveforms
  * @param none
  * @retval none
  */
void UpdateWaveforms(void);


#endif /* CONTROL_H_ */
