/**
@file HashTable.c
@author Rob Thomas
@brief Contains functions for generating, maintaining, and deleting hash tables. 
These tables currently only support the Jenkins one-at-a-time hash function and
handle collisions using the coalesced linking style. This hash table is built
to represent a list of pseudo-variables being declared by the user through the
matrix shell.
*/

/*** INCLUDES: ***/
#include "HashTable.h"

/*** DEFINES: ***/

/*** FUNCTION DEFINITIONS: ***/

/**
@fn HT_newTable
@brief Generates a newly allocated HashTable struct and initializes it. All keys
will be set to NULL to indicate that each bucket in the table is empty.
@param maxNumItems The maximum number of key/value pairs allowed in the hash table.
@return A pointer to a newly allocated and initialized HashTable struct.
*/
HashTable *HT_newTable(unsigned int maxNumItems)
{
	/* Allocate the table and initialize its basic members. */
	HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	table->numItems = 0;
	table->maxNumItems = maxNumItems;
	table->nextLink = 0;
	/* Allocate the list of HashSpaces. */
	table->pairs = (HashSpace *)malloc(sizeof(HashSpace) * maxNumItems);
	/* Set each HashSpace's key to NULL to indicate that it is empty. */
	for (unsigned int i = 0; i < maxNumItems; i++)
	{
		table->pairs[i].key = NULL;
	}
	return table;
}

/**
@fn HT_freeTable
@brief Frees an allocated HashTable struct.
NOTE: assumes that all keys and values in the table were dynamically allocated 
for and thus frees those too.
@param table Pointer to a dynamically allocated HashTable struct which will be
freed.
*/
void HT_freeTable(HashTable *table)
{
	/* Free each non-NULL key and value in the hash table. */
	for (unsigned int i = 0; i < table->maxNumItems; i++)
	{
		if (table->pairs[i].key)
		{
			free(table->pairs[i].key);
		}
		if (table->pairs[i].value)
		{
			free(table->pairs[i].value);
		}
	}
	/* Free the list of HashSpaces. */
	free(table->pairs);
	/* Free the table itself. */
	free(table);
}

/**
@fn HT_hashValue
@brief Calculates the hash value of a key using the Jenkins one-at-a-time
algorithm.
@param key The key whose hash value will be calculated. Must be null-terminated.
@return The hash value of the given key as an unsigned int.
*/
unsigned int HT_hashValue(char *key)
{
	/* @TODO: Implement */
}

/**
@fn HT_add
@brief Adds a key/value pair to a HashTable.
@param table Pointer to the HashTable struct which the key/value pair will be
added to.
@param key The string representing the key to be added. Must be null-terminated.
@param value Pointer to a block of data representing the value to be added.
For instance, if the value is a Matrix struct, then this parameter would simply
be the pointer to that struct.
@param valueType The type of data of the value. If the value is a Matrix struct,
then valueType will be VT_MATRIX.
@return An error code. 0 if no problems were encountered.
*/
int HT_add(HashTable *table, char *key, void *value, value_t valueType)
{
	/* Get the index in the hash table that this key would normally be added at. */
	unsigned int index = HT_hashValue(key) % table->maxNumItems;
	/* This index may point to an already-filled HashSpace. If so, check for the
	key already being present along the chain of linked spaces. */
}