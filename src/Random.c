/**
@file Random.c
@author Rob Thomas
@brief Contains functions for simple random number generation.
*/

/*** INCLUDES: ***/
#include "Random.h"

/*** DEFINES: ***/
#define NEGATIVE_MAX -1
#define MIN_GREATER_THAN_MAX -2

/*** FUNCTION DEFINITIONS: ***/

/**
@fn Random_at_most
@brief Generates a random 32-bit integer between 0 and the given number 
(inclusive). Results are evenly distributed across this range.
@details This function is inspired by Ryan Reich's response on StackOverflow.com:
https://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range.
This function may cause hitching as it randomly picks values until a valid one
is found.
@param max The maximum value for the random value to take.
@param errorCode Pointer to an int which this function will write error codes to.
@return An unsigned 32-bit integer randomly picked with even distribution from 
the range [0, max].
*/
int32_t Random_at_most (uint32_t max, int *errorCode)
{
	/* If max == UINT_MAX, then simply return the result of random(). */
	if (max == UINT_MAX)
	{
		return random();
	}
	/* The size of the set of integers between 0 and RAND_MAX. This set is the
	   set that random() will choose from. */
	uint32_t setSize = (uint32_t)(RAND_MAX + 1);
	/* Divide the set of all integers between 0 and RAND_MAX into equally-sized
	   bins. */
	uint32_t numBins = max + 1;
	/* Determine the size of each of these bins. */
	uint32_t binSize = setSize / numBins;
	/* Not all of the set will be covered by these bins. Only numBins * binSize
	   will be covered, so if random() chooses an integer greater than 
	   numBins * binSize - 1, that choice will be invalid. */
	uint32_t invalidSize = setSize % numBins;
	/* Use random() to choose from the set. If the choice is within one of the
	   bins, then determine which bin and return the corresponding value.
	   If the choice was invalid, then choose again. */
	int32_t choice;
	do 
	{
		choice = random();
	} while ( choice >= (int32_t)(numBins * binSize) );
	/* Once a valid choice has been made, find which bin it corresponds to and
	   return that answer. */
	return choice / binSize;
}

/**
@fn Random_in_range
@brief Generates a random 32-bit integer between the two given numbers 
(inclusive). Results are evenly distributed across the given range.
@param min The minimum value that the random result can have.
@param max The maximum value that the random result can have.
@param errorCode Pointer to an int which this function will write error codes to.
@return A 32-bit integer randomly picked with even distribution from the range
[min, max].
*/
int32_t Random_in_range (int32_t min, int32_t max, int *errorCode)
{
	/* Verify that min is less than max. */
	if ( min > max )
	{
		*errorCode = MIN_GREATER_THAN_MAX;
		return 0;
	}
	/* To find a random integer in a range, find a random integer in a range of
	   the same size starting at 0, then rebase that range to match the desired
	   range. */
	int32_t rangeSize = max - min;
	int32_t choice = Random_at_most(rangeSize);
	return choice + min;
}