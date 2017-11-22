/**
@file Random.h
@author Rob Thomas
@brief Contains functions for simple random number generation.
*/

/*** INCLUDES: ***/
#include <stdlib.h>

/*** DEFINES: ***/

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
int32_t Random_at_most (int32_t max, int *errorCode);

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
int32_t Random_in_range (int32_t min, int32_t max, int *errorCode);