/**
@file HashTable.c
@author Rob Thomas
@brief Contains the HashTable struct and functions for generating, maintaining, 
and deleting hash tables. These tables currently only support the Jenkins 
one-at-a-time hash function and handle collisions using the coalesced linking 
style. This hash table is built to represent a list of pseudo-variables being 
declared by the user through the matrix shell.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

/*** INCLUDES: ***/
#include <stdlib.h>
#include <stdbool.h>

/*** DEFINES: ***/

/*** STRUCTS: ***/

/**
@def value_t
@brief An enumerated type representing a type of variable being stored in the
hash table.
@var VT_MATRIX Indicates that whatever variable this is associated with is of 
the Matrix type.
@var VT_RATIONAL Indicates that whatever variable this is associated with is of
the Rational type.
*/
typedef enum 
{
	VT_MATRIX,
	VT_RATIONAL
} value_t;

/**
@def HashSpace
@brief A struct representing a single cell in the hash table.
@var key A string representing the key of this space. Must be NULL if there is
no key/value pair present in this space.
@var value A block of data representing the value of this space.
@var valueType The type that the value is expressed in. See definition of 
value_t above.
@var linkedIndex The index in the hash table of the HashSpace containing the 
first key/value pair which collided with this one. This is what gives the 
hash table its coalescing behavior. By following the chain of indexes, one can 
search through all key/value pairs that have collided.
@var hasLink A boolean value representing whether or not this HashSpace links to 
another HashSpace.
*/
typedef struct 
{
	char *key;
	void *value;
	value_t valueType;
	int linkedIndex;
	bool hasLink;
} HashSpace;

/**
@def HashTable
@brief A struct representing an entire hash table.
@var numItems The number of key/value pairs currently in the hash table.
@var maxNumItems The maximum number of key/value pairs allowed to be in the
hash table.
@var nextLink The index in the hash table of the next HashSpace which should be
filled with a key/value pair that collides with another key/value pair. This is
always the topmost (closest to 0) index not already containing a pair.
@var HashSpace pairs A list of HashSpaces representing the table of key/value
pairs. 
*/
typedef struct 
{
	unsigned int numItems;
	unsigned int maxNumItems;
	int nextLink;
	HashSpace *pairs;
} HashTable;

/*** FUNCTION PROTOTYPES: ***/

/**
@fn HT_newTable
@brief Generates a newly allocated HashTable struct and initializes it. All keys
will be set to NULL to indicate that each bucket in the table is empty.
@param maxNumItems The maximum number of key/value pairs allowed in the hash table.
@return A pointer to a newly allocated and initialized HashTable struct.
*/
HashTable *HT_newTable(unsigned int maxNumItems);

/**
@fn HT_freeTable
@brief Frees an allocated HashTable struct.
NOTE: assumes that all keys and values in the table were dynamically allocated 
for and thus frees those too.
@param table Pointer to a dynamically allocated HashTable struct which will be
freed.
*/
void HT_freeTable(HashTable *table);

/**
@fn HT_hashValue
@brief Calculates the hash value of a key using the Jenkins one-at-a-time
algorithm.
@param key The key whose hash value will be calculated. Must be null-terminated.
@return The hash value of the given key as an unsigned int.
*/
unsigned int HT_hashValue(char *key);

/**
@fn jenkins_one_at_a_time_hash_value
@brief Uses the Jenkins one-at-a-time hashing algorithm to convert a key any
positive length into the corresponding hash value.
@param key The key whose hash value will be calculated.
@param len The length of the key (in bytes).
@return The hash value of the given key as an unsigned int.
*/
unsigned int jenkins_one_at_a_time_hash_value(char *key, int len);

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
int HT_add(HashTable *table, char *key, void *value, value_t valueType);

/**
@fn HT_copyString
@brief Creates a dynamically allocated copy of the given string.
@param str The string to be copied.
@return A dynamically allocated string containing the string given.
*/
char *HT_copyString(char *str);

/**
@fn HT_copyValue
@brief Creates a dynamically allocated copy of the given data block.
@param value The data block to be copied.
@param size The size (in bytes) of the data block to be copied.
@return A pointer to a dynamically allocated block of data containing the data
given in value.
*/
void *HT_copyValue(void *value, size_t size);



#endif /* HASHTABLE_H */