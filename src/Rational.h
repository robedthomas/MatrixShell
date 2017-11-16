/**
@file Rational.c
@author Rob Thomas
@brief Contains functions for representing rational numbers and their operations.
A rational number is any number equal to q/p, where q and p are integers.
Rationals are represented by two signed integers, each 32 bytes, representing 
the integers q and p.
*/

/**
@def Rational
@brief A struct representing a rational number.
@var top The top integer (numerator) of the rational number.
@var bottom The bottom integer (denominator) of the rational number.
*/
typedef struct 
{
	int32_t top;
	int32_t bottom;
} Rational;