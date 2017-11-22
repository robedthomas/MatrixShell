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
@return A 32-bit integer randomly picked with even distribution from 
the range [0, max].
*/
int32_t Random_at_most (int32_t max, int *errorCode)
{
	/* If max == UINT_MAX, then simply return the result of random(). */
	if (max == UINT_MAX)
	{
		return random();
	}
	/* Otherwise, use Random_in_range to find a random int in the range [0, max]. */
	return Random_in_range(0, max, errorCode);
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
	/* If min and max are identical, return max. */
	if ( min == max )
	{
		return max;
	}
	/* The size of the set of integers between RAND_MIN and RAND_MAX. This set is 
	   the set that random() will choose from. setSize is stored in a 64-bit
	   integer since RAND_MAX - RAND_MIN + 1 is 1 larger than the maximum 
	   magnitude of an unsigned 32-bit integer. */
	uint64_t setSize = (uint64_t)((RAND_MAX - RAND_MIN) + 1);
	/* Divide the set of all integers between RAND_MIN and RAND_MAX into 
	   equally-sized bins. numBins is stored in a 64-bit integer because
	   max - min + 1 could overflow a 32-bit unsigned integer. */
	uint64_t numBins = (uint64_t)((max - min) + 1);
	/* Determine the size of each of these bins. */
	uint64_t binSize = setSize / numBins;
	/* Not all of the set will be covered by these bins. Only numBins * binSize
	   will be covered, so if random() chooses an integer greater than 
	   numBins * binSize - 1, that choice will be invalid. */
	int32_t invalidSize = (int32_t)(setSize % numBins);
	/* Use random() to choose from the set. If the choice is within one of the
	   bins, then determine which bin and return the corresponding value.
	   If the choice was invalid, then choose again. */
	int32_t choice;
	do 
	{
		choice = random();
	} while ( choice > RAND_MAX - invalidSize );
	/* Once a valid choice has been made, find which bin it corresponds to and
	   return that answer. (choice / binSize) sorts the choice into the 
	   corresponding bin, but these bins will be indexed in the set 
	   [-numBins/2, numBins/2]. Adding (numBins / 2) will shift the indexing of
	   the bins to [0, numBins - 1]. Finally, adding min will shift the indexing
	   of the bins to [min, max]. */
	return (int32_t)((int64_t)(choice) / binSize) + (int32_t)(numBins / 2) + min;
}