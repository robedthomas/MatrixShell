/**
@file Rational.c
@author Rob Thomas
@brief Contains functions for representing rational numbers and their operations.
A rational number is any number equal to q/p, where q and p are integers.
Rationals are represented by two signed integers, each 32 bytes, representing 
the integers q and p.
*/

/*** INCLUDES: ***/
#include "Rational.h"

/*** DEFINES: ***/

/*** FUNCTION DEFINITIONS: ***/

/**
@fn GCD
@brief Determines the greatest common denominator between two integers.
@param top One of the two integers whose GCD will be found.
@param bottom One of the two integers whose GCD will be found.
@return The GCD of top and bottom.
*/
int32_t GCD (int32_t top, int32_t bottom)
{
	/* @TODO: implement */
}

/**
@fn R_reduce
@brief Reduces a Rational such that the greatest common denominator between the
Rational's numerator and denominator is 1. If the Rational is negative, then 
following reduction the numerator will be negative and the denominator will be
positive.
@param r Pointer to the Rational to be reduced.
*/
void R_reduce (Rational *r)
{
	/* @TODO: implement */
}

/**
@fn R_add
@brief Adds an integer to a Rational.
@param r Pointer to the Rational which will be added to.
@param i The integer to add to r.
*/
void R_add (Rational *r, int32_t i)
{
	/* @TODO: implement */
}

/**
@fn R_addR
@brief Adds a Rational to another Rational.
@param r Pointer to the Rational which will be altered by the addition.
@param a The Rational to add to r.
*/
void R_addR (Rational *r, Rational a)
{
	/* @TODO: implement */
}

/**
@fn R_subtract
@brief Subtracts an integer from a Rational.
@param r Pointer to the Rational which will be subtracted from.
@param i The integer to subtract from r.
*/
void R_subtract (Rational *r, int32_t i)
{
	/* @TODO: implement */
}

/**
@fn R_subtractR
@brief Subtracts a Rational from another Rational.
@param r Pointer to the Rational which will be altered by the subtraction.
@param s The Rational to subtract from r.
*/
void R_subtractR (Rational *r, Rational s)
{
	/* @TODO: implement */
}

/**
@fn R_mult
@brief Multiplies a rational by an integer.
@param r Pointer to the Rational which will be multiplied.
@param i The integer to multiply r by.
*/
void R_mult (Rational *r, int32_t i)
{
	/* @TODO: implement */
}

/**
@fn R_multR
@brief Multiplies a Rational by another Rational.
@param r Pointer to the Rational which will be altered by the multiplication.
@param m The Rational to multiply r by.
*/
void R_multR (Rational *r, Rational m)
{
	/* @TODO: implement */
}

/**
@fn R_div
@brief Divides a rational by an integer.
@param r Pointer to the Rational which will be divided.
@param i The integer to divide r by.
*/
void R_div (Rational *r, int32_t i)
{
	/* @TODO: implement */
}

/**
@fn R_divR
@brief Divides a Rational by another Rational.
@param r Pointer to the Rational which will be altered by the division.
This Rational will be the numerator.
@param a The Rational to divide r by.
*/
void R_divR (Rational *r, Rational d)
{
	/* @TODO: implement */
}