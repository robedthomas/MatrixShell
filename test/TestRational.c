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
	int32_t top, bottom;
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

/**
@fn test_R_GCD
@brief Tests the functionality of R_GCD().
@details Performs various tests to ensure R_GCD() returns the proper greatest
common denominator between two non-negative integers.
*/
void test_R_GCD ()
{
	int32_t top, bottom, gcd;
	/* Try a random negative value for either input. R_GCD() should fail. */
	top = Random_in_range(INT_MIN, -1);
	bottom = Random_in_range(INT_MIN, -1);
	gcd = R_GCD(top, bottom);
	TEST_ASSERT_EQUAL_INT32(-1, gcd);
	/* Try 0 for both inputs. R_GCD() should fail and return -2. */
	gcd = R_GCD(0, 0);
	TEST_ASSERT_EQUAL_INT32(-2, gcd);
	/* Try 0 for one, then for the other. Should return the non-zero input. */
	top = Random_in_range(1, INT_MAX);
	gcd = R_GCD(top, 0);
	TEST_ASSERT_EQUAL_INT32(top, gcd);
	bottom = Random_in_range(1, INT_MAX);
	gcd = R_GCD(0, bottom);
	TEST_ASSERT_EQUAL_INT32(bottom, gcd);
	/* Try 1 for one input, then for the other. Should return 1. */
	top = Random_in_range(2, INT_MAX);
	gcd = R_GCD(top, 1);
	TEST_ASSERT_EQUAL_INT32(1, gcd);
	bottom = Random_in_range(2, INT_MAX);
	gcd = R_GCD(1, bottom);
	TEST_ASSERT_EQUAL_INT32(1, gcd);
	/* Try any two random numbers, then flip them. Results should be the same. */
	top = Random_in_range(1, INT_MAX);
	bottom = Random_in_range(1, INT_MAX);
	gcd = R_GCD(top, bottom);
	int32_t secondGcd = R_GCD(bottom, top);
	TEST_ASSERT_EQUAL_INT32(gcd, secondGcd);
	/* Try any two integers greater x, y > 1. The result r should divide them
	   evenly (x % r = 0, y % r = 0). */
	top = Random_in_range(2, 512);
	bottom = Random_in_range(2, 512);
	gcd = R_GCD(top, bottom);
	TEST_ASSERT_EQUAL_INT32(0, top % gcd);
	TEST_ASSERT_EQUAL_INT32(0, bottom % gcd);
	/* With respect to the previous test, increment r until it reaches x or y.
	   r should never evenly divide x and y during incrementing. This proves 
	   that the original r was in fact the GREATEST common denominator. */
	gcd++;
	while ( gcd < top && gcd < bottom )
	{
		TEST_ASSERT(top % gcd != 0);
		TEST_ASSERT(bottom % gcd != 0);
		gcd++;
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