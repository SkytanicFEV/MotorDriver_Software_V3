/*
 * stringConvert.h
 *
 *  Created on: Jul 10, 2019
 *      Author: ajohnson
 */

#include "stdint.h"

#ifndef STRINGCONVERT_H_
#define STRINGCONVERT_H_

/* Function Prototypes ***************************************************************************/

/**
  * @brief Convert the given integer to the given string
  * @param n = integer to convert, string = resulting string, length = lenght of string = number of digits to convert
  * @retval void
  */
void IntToString(int n, char * string, int length);

/**
  * @brief Convert the given integer to the given string, adding a '-' if negative and a leading 0 if positive
  * @param n = integer to convert, string = resulting string, length = lenght of string = number of digits to convert
  * @retval void
  */
void SignIntToString(int n, char * string, int length);

/**
  * @brief Convert the given floating point value to the given string
  * @param n = float to convert, string = resulting string, before_decimal = digits before decimal point, after_decimal = digits after decimal point
  * @retval void
  */
void FloatToString(float n, char * string, int before_decimal, int after_decimal);

/**
  * @brief Convert the given string to a floating point value
  * @param string = string to convert, length = length of string
  * @retval void
  */
float StringToFloat(char const * string, int const length);

/**
 * @brief Convert the given string to an int, stopping when it encounter a non-numeric char
 * @param string, the string to convert
 * @param length, the length of the string being converted
 * @retval resulting integer
 */
int StringToInt(char * string, int length);


#endif /* STRINGCONVERT_H_ */
