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
	}
}