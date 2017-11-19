/**
@file TestRational.c
@author Rob Thomas
@brief Contains Unity functions for testing the functionality of Rational.c.
*/

/*** INCLUDES: ***/
#include <limits.h>

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
@fn test_R_copy
@brief Tests the functionality of R_copy().
@details Verifies that R_copy() will accurately copy a Rational. Checks edge
cases and then several random cases.
*/
void test_R_copy ()
{
	/* Create a new Rational, copy it, then make sure its top and bottom are 1. */
	Rational *first = R_new();
	Rational *second = R_copy(*first);
	TEST_ASSERT_EQUAL_INT32(1, second->top);
	TEST_ASSERT_EQUAL_INT32(1, second->bottom);
	/* Copy 0/0. */
	free(second);
	first->top = 0;
	first->bottom = 0;
	second = R_copy(first);
	TEST_ASSERT_EQUAL_INT32(0, second->top);
	TEST_ASSERT_EQUAL_INT32(0, second->bottom);
	/* Copy INT_MIN/INT_MIN and INT_MAX/INT_MAX. */
	free(second);
	first->top = INT_MIN;
	first->bottom = INT_MIN;
	second = R_copy(first);
	TEST_ASSERT_EQUAL_INT32(INT_MIN, second->top);
	TEST_ASSERT_EQUAL_INT32(INT_MIN, second->bottom);
	free(second);
	first->top = INT_MAX;
	first->bottom = INT_MAX;
	second = R_copy(first);
	TEST_ASSERT_EQUAL_INT32(INT_MAX, second->top);
	TEST_ASSERT_EQUAL_INT32(INT_MAX, second->bottom);
	/* Test ten different random Rationals. */
	int32_t top;
	int32_t bottom;
	for (int i = 0; i < 10; i++)
	{
		top = Random_in_range(INT_MIN, INT_MAX);
		bottom = Random_in_range(INT_MIN, INT_MAX);
		first->top = top;
		first->bottom = bottom;
		second = R_copy(first);
		TEST_ASSERT_EQUAL_INT32(top, second->top);
		TEST_ASSERT_EQUAL_INT32(bottom, second->bottom);
		free(second);
	}
}

int main ()
{
	/* Initialize Unity. */
	UNITY_BEGIN();
	/* Call each test function using Unity's RUN_TEST() function. */
	/* Once each test is complete, return Unity's result. */
	return UNITY_END();
}