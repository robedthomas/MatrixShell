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
@fn R_new
@brief Allocates a new Rational equal to 1/1.
@return A pointer to a dynamically allocated Rational struct with top = 1 and
bottom = 1.
*/
Rational *R_new ()
{
	Rational *r = (Rational *)malloc(sizeof(Rational));
	r->top = 1;
	r->bottom = 1;
	return r;
}

/**
@fn R_copy
@brief Creates a dynamically allocated copy of another Rational.
@param r The Rational to be copied.
@return A pointer to a dynamically allocated copy of r.
*/
Rational *R_copy (Rational r)
{
	Rational *c = (Rational *)malloc(sizeof(Rational));
	c->top = r.top;
	c->bottom = r.bottom;
	return c;
}

/**
@fn R_GCD
@brief Determines the greatest common denominator between two non-negative integers.
@param top One of the two integers whose GCD will be found. Must be non-negative.
@param bottom One of the two integers whose GCD will be found. Must be
non-negative.
@return The GCD of top and bottom. -1 if either top and/or bottom was negative.
*/
int64_t R_GCD (int64_t top, int64_t bottom)
{
	/* Ensure that top and bottom are non-negative. */
	if ( top < 0 || bottom < 0 )
	{
		/* @TODO: implement error codes */
		return -1;
	}
	/* If either top or bottom is zero, then the GCD must be the non-zero input. */
	if ( top == 0 && bottom != 0 )
	{
		return bottom;
	}
	else if ( bottom == 0 && top != 0 )
	{
		return top;
	}
	else if ( top == 0 && bottom == 0 )
	{
		/* @TODO: implement error codes */
		return -2;
	}
	/* Determine which of the two inputs is larger. */
	int64_t larger, smaller;
	if ( top > bottom )
	{
		larger = top;
		smaller = bottom;
	}
	else 
	{
		larger = bottom;
		smaller = top;
	}
	int64_t swap;
	/* Use Euclidean algorithm to find the GCD. */
	while ( larger > 0 && smaller > 0 )
	{
		larger %= smaller;
		swap = larger;
		larger = smaller;
		smaller = swap;
	}
	return larger;
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
	/* If the bottom is negative, make the top negative instead. */
	if ( r->bottom < 0 )
	{
		r->bottom *= -1;
		r->top *= -1;
	}
	/* Find the GCD between the top and bottom. */
	int32_t gcd = R_GCD(r->top, r->bottom);
	/* Divide the top and bottom by the GCD, thus reducing the fraction. */
	if ( gcd > 1 )
	{
		r->top /= gcd;
		r->bottom /= gcd;
	}
}

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
void R_reduce64 (Rational *dest, int64_t top, int64_t bottom)
{
	/* If the bottom is negative, make the top negative instead. */
	if ( bottom < 0 )
	{
		bottom *= -1;
		top *= -1;
	}
	/* Find the GCD between the top and bottom. */
	int64_t gcd = R_GCD(top, bottom);
	/* Divide the top and bottom by the GCD, thus reducing the fraction. */
	if ( gcd > 1 )
	{
		top /= gcd;
		bottom /= gcd;
	}
	/* Set dest's top and bottom to the top and bottom just formulated. */
	dest->top = top;
	dest->bottom = bottom;
}

/**
@fn R_invert
@brief Inverts a rational's fraction form. So for instance, 2/7 will be inverted
to 7/2. 0/x will be converted x/0 without throwing any sort of error notification.
@param r Pointer to the Rational to be inverted.
*/
void R_invert (Rational *r)
{
	/* Swap the top and bottom. */
	int32_t swap = r->bottom;
	r->bottom = r->top;
	r->top = swap;
	/* Reduce r. */
	R_reduce(r);
}

/**
@fn R_add
@brief Adds an integer to a Rational.
@param r Pointer to the Rational which will be added to.
@param i The integer to add to r.
*/
void R_add (Rational *r, int32_t i)
{
	/* Scale i up to match the bottom of r. */
	i *= r->bottom;
	/* Add i to the top of r. */
	r->top += i;
	/* Reduce r. */
	R_reduce(r);
}

/**
@fn R_addR
@brief Adds a Rational to another Rational.
@param r Pointer to the Rational which will be altered by the addition.
@param a The Rational to add to r.
*/
void R_addR (Rational *r, Rational a)
{
	/* Cross-multiply the two rationals to prepare them for addition. */
	/* While cross-multiplying, cast the products as 64-bit ints to avoid
	   potential overflow. */
	int64_t tempTop, tempBottom, addToTop;
	tempTop = (int64_t)(r->top) * (int64_t)(a.bottom);
	tempBottom = (int64_t)(r->bottom) * (int64_t)(a.bottom);
	addToTop = (int64_t)(a.top) * (int64_t)(r->bottom);
	/* Add the two tops together. */
	tempTop += addToTop;
	/* Finally, reduce r. */
	R_reduce64(r, tempTop, tempBottom);
}

/**
@fn R_subtract
@brief Subtracts an integer from a Rational.
@param r Pointer to the Rational which will be subtracted from.
@param i The integer to subtract from r.
*/
void R_subtract (Rational *r, int32_t i)
{
	/* Subtract i from r by adding negative i to r. */
	R_add(r, i * -1);
}

/**
@fn R_subtractR
@brief Subtracts a Rational from another Rational.
@param r Pointer to the Rational which will be altered by the subtraction.
@param s The Rational to subtract from r.
*/
void R_subtractR (Rational *r, Rational s)
{
	/* Subtract s from r by adding negative s to r. */
	s.top *= -1;
	R_addR(r, s);
}

/**
@fn R_mult
@brief Multiplies a rational by an integer. 
@details Note that this function is vulnerable to overflow if the Rational and 
integer being multiplied have extreme magnitudes.
@param r Pointer to the Rational which will be multiplied.
@param i The integer to multiply r by.
*/
void R_mult (Rational *r, int32_t i)
{
	/* Multiply the top of r by i. */
	int64_t tempTop = (int64_t)(r->top) * (int64_t)(i);
	/* Reduce r. */
	R_reduce64(r, tempTop, r->bottom);
}

/**
@fn R_multR
@brief Multiplies a Rational by another Rational. 
@details Note that this function is vulnerable to overflow if the Rationals 
being multiplied have extreme magnitudes.
@param r Pointer to the Rational which will be altered by the multiplication.
@param m The Rational to multiply r by.
*/
void R_multR (Rational *r, Rational m)
{
	/* Multiply the tops together and the bottoms together. */
	int64_t tempTop, tempBottom;
	tempTop = (int64_t)(r->top) * (int64_t)(m.top);
	tempBottom = (int64_t)(r->bottom) * (int64_t)(m.bottom);
	/* Reduce r. */
	R_reduce64(r, tempTop, tempBottom);
}

/**
@fn R_div
@brief Divides a rational by an integer. 
@details Note that this function is vulnerable to overflow if the Rational and 
integer being divided have extreme magnitudes.
@param r Pointer to the Rational which will be divided.
@param i The integer to divide r by.
*/
void R_div (Rational *r, int32_t i)
{
	/* Multiply the bottom of r by i. */
	int64_t tempBottom = (int64_t)(r->bottom) * (int64_t)(i);
	/* Reduce r. */
	R_reduce64(r, r->top, tempBottom);
}

/**
@fn R_divR
@brief Divides a Rational by another Rational. 
@details Note that this function is vulnerable to overflow if the Rationals 
being divided have extreme magnitudes.
@param r Pointer to the Rational which will be altered by the division.
This Rational will be the numerator.
@param a The Rational to divide r by.
*/
void R_divR (Rational *r, Rational d)
{
	/* Divide r by d by multiplying by the inverse of d. */
	Rational *inverted = R_invert(R_copy(d));
	R_multR(r, inverted);
	/* Free the inverted copy of d. */
	free(inverted);
}