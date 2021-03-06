/**
@file Rational.c
@author Rob Thomas
@brief Contains functions for representing rational numbers and their operations.
A rational number is any number equal to q/p, where q and p are integers.
Rationals are represented by two signed integers, each 32 bytes, representing 
the integers q and p.
*/

/*** INCLUDES: ***/

/*** DEFINES: ***/

/*** STRUCTS: ***/

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

/**
@fn R_new
@brief Allocates a new Rational equal to 1/1.
@return A pointer to a dynamically allocated Rational struct with top = 1 and
bottom = 1.
*/
Rational *R_new ();

/**
@fn R_copy
@brief Creates a dynamically allocated copy of another Rational.
@param r The Rational to be copied.
@return A pointer to a dynamically allocated copy of r.
*/
Rational *R_copy (Rational r);

/**
@fn GCD
@brief Determines the greatest common denominator between two integers.
@param top One of the two integers whose GCD will be found.
@param bottom One of the two integers whose GCD will be found.
@return The GCD of top and bottom. -1 if either top and/or bottom was negative.
*/
int64_t R_GCD (int64_t top, int64_t bottom);

/**
@fn R_reduce
@brief Reduces a Rational such that the greatest common denominator between the
Rational's numerator and denominator is 1. If the Rational is negative, then 
following reduction the numerator will be negative and the denominator will be
positive.
@param r Pointer to the Rational to be reduced.
*/
void R_reduce (Rational *r);

/**
@fn R_reduce64
@brief Similar to R_reduce, reduces the top and bottom of a rational such that
afterwards their greatest common denominator is 1. However, this version takes 
in a top and bottom with double precision (64-bit ints instead of 32-bit ints).
This is necessary because certain operations (such as multiplication) can
result in temporary overflow before reduction is completed.
@param dest Pointer to the Rational where the resulting top and bottom will be
stored.
@param top 64-bit integer representing the top of the Rational being reduced.
@param bottom 64-bit integer representing the bottom of the Rational being reduced.
*/
void R_reduce64 (Rational *dest, int64_t top, int64_t bottom);

/**
@fn R_invert
@brief Inverts a rational's fraction form. So for instance, 2/7 will be inverted
to 7/2. 0/x will be converted x/0 without throwing any sort of error notification.
@param r Pointer to the Rational to be inverted.
*/
void R_invert (Rational *r);

/**
@fn R_add
@brief Adds an integer to a Rational.
@param r Pointer to the Rational which will be added to.
@param i The integer to add to r.
*/
void R_add (Rational *r, int32_t i);

/**
@fn R_addR
@brief Adds a Rational to another Rational.
@param r Pointer to the Rational which will be altered by the addition.
@param a The Rational to add to r.
*/
void R_addR (Rational *r, Rational a);

/**
@fn R_subtract
@brief Subtracts an integer from a Rational.
@param r Pointer to the Rational which will be subtracted from.
@param i The integer to subtract from r.
*/
void R_subtract (Rational *r, int32_t i);

/**
@fn R_subtractR
@brief Subtracts a Rational from another Rational.
@param r Pointer to the Rational which will be altered by the subtraction.
@param s The Rational to subtract from r.
*/
void R_subtractR (Rational *r, Rational s);

/**
@fn R_mult
@brief Multiplies a rational by an integer. 
@details Note that this function is vulnerable to overflow if the Rational and 
integer being multiplied have extreme magnitudes.
@param r Pointer to the Rational which will be multiplied.
@param i The integer to multiply r by.
*/
void R_mult (Rational *r, int32_t i);

/**
@fn R_multR
@brief Multiplies a Rational by another Rational. 
@details Note that this function is vulnerable to overflow if the Rationals 
being multiplied have extreme magnitudes.
@param r Pointer to the Rational which will be altered by the multiplication.
@param m The Rational to multiply r by.
*/
void R_multR (Rational *r, Rational m);

/**
@fn R_div
@brief Divides a rational by an integer. 
@details Note that this function is vulnerable to overflow if the Rational and 
integer being divided have extreme magnitudes.
@param r Pointer to the Rational which will be divided.
@param i The integer to divide r by.
*/
void R_div (Rational *r, int32_t i);

/**
@fn R_divR
@brief Divides a Rational by another Rational. 
@details Note that this function is vulnerable to overflow if the Rationals 
being divided have extreme magnitudes.
@param r Pointer to the Rational which will be altered by the division.
This Rational will be the numerator.
@param a The Rational to divide r by.
*/
void R_divR (Rational *r, Rational d);