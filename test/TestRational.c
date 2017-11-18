/**
@file TestRational.c
@author Rob Thomas
@brief Contains Unity functions for testing the functionality of Rational.c.
*/

/*** INCLUDES: ***/
#include "unity.h"
#include "Random.h"
#include "Rational.h"

/*** DEFINES: ***/

/*** FUNCTION DEFINITIONS: ***/

/**
@fn test_R_new
@brief Tests the functionality of R_new().
@details Verifies that R_new() creates a new Rational with top and bottom both
equal to 1.
*/
void test_R_new ()
{
	/* Use R_new() to create a new Rational. */
	Rational *r = R_new();
	/* Verify r's top and bottom. */
	TEST_ASSERT_EQUAL_INT32(1, r->top);
	TEST_ASSERT_EQUAL_INT32(1, r->bottom);
	/* Afterwards, free r. */
	free(r);
}

/**
@fn void test_R_copy
@brief Tests the functionality of R_copy().
@details Verifies that R_copy will correctly copy a variety of Rationals.
*/

int main ()
{
	/* Initialize Unity. */
	UNITY_BEGIN();
	/* Call each test function using Unity's RUN_TEST() function. */
	/* Once each test is complete, return Unity's result. */
	return UNITY_END();
}