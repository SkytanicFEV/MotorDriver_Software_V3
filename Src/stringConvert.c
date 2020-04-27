/*
 * stringConvert.c
 *
 *  Created on: Jul 10, 2019
 *      Author: ajohnson
 */

#include "stringConvert.h"

/**
 * @brief Count the number of decimal digits in an int and return that count
 * @param num = number to count the number of digits in
 * @retval number of digits in num
 */
static int NumDigitsInInt(int num)
{
    int count = 0;
    while(num != 0)
    {
        count += 1;
        num /= 10;
    }
    return count;
}

/**
  * @brief Convert the given integer to the given string
  * @param n = integer to convert, string = resulting string, length = lenght of string = number of digits to convert
  * @retval void
  */
void IntToString(int n, char * string, int length)
{

	int i = 0, j = 0, temp;
	while(n && (i < length))
	{
		string[i++] = (n % 10) + '0';
		n = n / 10;
	}

	// If the number is small enough add 0s at the beginning of the string
	while(i < length)
	{
		string[i++] = '0';
	}

	// Reverse the string
	i = 0;
	j = length - 1;
	while(i < j)
	{
		temp = string[i];
		string[i] = string[j];
		string[j] = temp;
		i++;
		j--;
	}

	// Don't add NULL characters to the end of the string in this function, it messes up float_to_string
}

/**
  * @brief Convert the given integer to the given string, adding a '-' if negative and a leading 0 if positive
  * @param n = integer to convert, string = resulting string, length = lenght of string = number of digits to convert
  * @retval void
  */
void SignIntToString(int n, char * string, int length)
{
	// Check the sign of the number, if negative add a leading '-' and make n positive
	if(n < 0)
	{
		string[0] = '-';
		n *= -1;
	}
	else
	{
		string[0] = '+';
	}

	// Call int_to_string with new positive number
	IntToString(n, string + 1, length -1);
}

/**
  * @brief Convert the given floating point value to the given string
  * @param n = float to convert, string = resulting string, before_decimal = digits before decimal point, after_decimal = digits after decimal point
  * @retval void
  */
void FloatToString(float n, char * string, int before_decimal, int after_decimal)
{

	// If the number is less than zero then add a negative sign and make the number positive
	if(n < 0)
	{
		n *= (-1);
		string[0] = '-';
	}
	else{
		string[0] = '0';
	}
	// Get the portion before the decimal point
	int before_dec = (int) n;

    before_decimal = NumDigitsInInt(before_dec);
	// Convert this first portion to a string
	IntToString(before_dec, string + 1, before_decimal);

	// Add the decimal point
	string[before_decimal + 1] = '.';

	// Get the portion after the decimal point
	float after_dec = n - (float) before_dec;

    int numZeroes = 0;
    while(after_dec != (int)after_dec)
    {
        after_dec *= 10;
        if(after_dec < 1) numZeroes += 1;
    }

    after_decimal = NumDigitsInInt((int) after_dec);
	// after_dec = after_dec * mult;

	// Convert the rest of the number to a string
	IntToString((int) after_dec, string + before_decimal + 2, after_decimal + numZeroes);
}

/**
  * @brief Convert the given string to a floating point value
  * @param string = string to convert, length = length of string
  * @retval resulting floating point value if successful
  */
float StringToFloat(char const * string, int const length)
{
	float n = 0;
	float multiplier = 0;
	int decimal_place = 0;

	// Find where the decimal point is
	for(decimal_place = 0; (string[decimal_place] != '.') && (decimal_place < length); decimal_place++);

	// If decimal_place is zero then there are no numbers before the decimal
	if(decimal_place == 0)
	{
		multiplier = .1;
		for(int i = 1; i < length; i++)
		{
			// Check to make sure that the character is a number before adding it to the result
			if((string[i] >= '0') && (string[i] <= '9'))
			{
				n += (string[i] - '0') * multiplier;
			}
			multiplier *= .1;
		}
	}
	else
	{
		// Set the multiplier up to the correct value
		multiplier = 1;
		for(int i = 1; i < decimal_place; i++)
		{
			multiplier *= 10;
		}
		// Add the characters to the number
		for(int i = 0; i < length; i++)
		{
			if(i != decimal_place)
			{
				// Check to make sure that the character is a number before adding it to the result
				if((string[i] >= '0') && (string[i] <= '9'))
				{
					n += (string[i] - '0') * multiplier;
				}
				multiplier *= .1;
			}
		}
	}
	if(string[0] == '-')
	{
		n *= -1;
	}

	return n;
}

/**
 * @brief Convert the given string to an int, stopping when it encounter a non-numeric char
 * @param string, the string to convert
 * @param length, the length of the string being converted
 * @retval resulting integer
 */
int StringToInt(char * string, int length)
{
	int num = 0;
	for(int i = 0; i < length; i++)
	{
		if(string[i] >= '0' && string[i] <= '9')
		{
			num *= 10;
			num += string[i] - '0';
		}
		else
		{
			break;
		}
	}
	return num;
}
