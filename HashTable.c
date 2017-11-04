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
	int len = strlen(key);
	return jenkins_one_at_a_time_hash_value(key, len);
}

/**
@fn jenkins_one_at_a_time_hash_value
@brief Uses the Jenkins one-at-a-time hashing algorithm to convert a key any
positive length into the corresponding hash value.
@param key The key whose hash value will be calculated.
@param len The length of the key (in bytes).
@return The hash value of the given key as an unsigned int.
*/
unsigned int jenkins_one_at_a_time_hash_value(char *key, int len)
{
	int i = 0;
	unsigned int hashValue = 0;
	for (int i = 0; i < len; i++)
	{
		hashValue += key[i];
		hashValue += (hashValue << 10);
		hashValue ^= (hashValue >> 6);
	}

	hashValue += (hashValue << 3);
	hashValue ^= (hashValue >> 11);
	hashValue += (hashValue << 15);
	return hashValue;
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
	/* First, make sure the table isn't already full. */
	if (table->numItems >= table->maxNumItems)
	{
		return FAIL_TABLE_FULL;
	}
	/* Get the index in the hash table that this key would normally be added at. */
	unsigned int index = HT_hashValue(key) % table->maxNumItems;
	/* If the HashSpace is empty, simply add the key/value pair in. */
	if (!table->pairs[index].key)
	{
		/* Allocate and add the key and value. */
		table->pairs[index].key = HT_copyString(key);
		table->pairs[index].value = HT_copyValue(value, valueType);
		table->pairs[index].valueType = valueType;
		/* Indicate that there is no chain from this space. */
		table->pairs[index].linkedIndex = 0;
		table->pairs[index].hasLink = false;
		/* If this pair was added where the next link of a chain would be added,
		   advance the next link pointer to the next free space. */
		if (index == table->nextLink)
		{
			while (table->pairs[table->nextLink].key)
			{
				table->nextLink++;
				/* Catch no space being available for a new link. */
				if (table->nextLink >= table->maxNumItems)
				{
					return ERR_NEXT_LINK_OUT_OF_BOUNDS;
				}
			}
		}
		return 0;
	}
	/* If the HashSpace is filled, it may point to another space. If so, travel 
	to the end of the linked chain so that the link of the HashSpace at the end 
	can be set. */
	bool linkAvailable;
	do
	{
		/* While travelling along the chain, check for the key already being
		present. If it is, overwrite the present value with the new value. */
		if (!strcmp(key, table->pairs[index].key))
		{
			if (table->pairs[index].value)
			{
				/* Free the old value. */
				free(table->pairs[index].value);
				/* Decrement the number of items in the table to compensate for
				   it being incremented when the new value is added. */
				table->numItems--;
			}
			/* Allocate for the new value and copy it in. */
			unsigned int size = HT_typeSize(valueType);
			table->pairs[index].value = HT_copyValue(value, size);
			table->pairs[index].valueType = valueType;
			table->numItems++;
			return 0;
		}
		if (table->pairs[index].hasLink)
		{
			linkAvailable = true;
			/* Move to the next space in the chain. */
			index = table->pairs[index].linkedIndex;
		}
		else 
		{
			linkAvailable = false;
		}
	} while (linkAvailable);
	/* Once at the last HashSpace in the chain, make sure that the next link to
	be made is within the bounds of the table. */
	if (table->nextLink < table->maxNumItems)
	{
		/* Link the space at the end of the chain to the next link space, where
		this key/value pair will be added. */
		table->pairs[index].linkedIndex = table->nextLink;
		/* Add the key/value pair. */
		table->pairs[table->nextLink].key = HT_copyString(key);
		unsigned int size = HT_typeSize(valueType);
		table->pairs[table->nextLink].value = HT_copyValue(value, size);
		table->pairs[table->nextLink].valueType = valueType;
		table->pairs[table->nextLink].linkedIndex = -1;
		table->numItems++;
		/* Advance the next link to point at the closest empty space below where
		it originally pointed. */
		while (table->pairs[++(table->nextLink)].key) {}
	}
	/* If the next link was outside of the bounds of the table, return with an 
	error code. */
	else
	{
		return ERR_NEXT_LINK_OUT_OF_BOUNDS;
	}
	return 0;
}

/**
@fn HT_copyString
@brief Creates a dynamically allocated copy of the given string.
@param str The string to be copied.
@return A dynamically allocated string containing the string given.
*/
char *HT_copyString(char *str)
{
	unsigned int len = strlen(str);
	newStr = (char *)malloc(sizeof(char) * (len + 1));
	strcpy(newStr, str);
	return newStr;
}

/**
@fn HT_copyValue
@brief Creates a dynamically allocated copy of the given data block.
@param value The data block to be copied.
@param size The size (in bytes) of the data block to be copied.
@return A pointer to a dynamically allocated block of data containing the data
given in value.
*/
void *HT_copyValue(void *value, size_t size)
{
	void *newValue = malloc(size);
	memcpy(newValue, value, size);
	return newValue;
}