/*
 * control.h
 *
 *  Created on: Jan 14, 2020
 *      Author: alex
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "main.h"

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
