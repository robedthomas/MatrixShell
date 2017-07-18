/**
@file HashTable.c
@author Rob Thomas
@brief Contains the HashTable struct and functions for generating, maintaining, 
and deleting hash tables. These tables currently only support the Jenkins 
one-at-a-time hash function and handle collisions using the coalesced linking 
style. This hash table is built to represent a list of pseudo-variables being 
declared by the user through the matrix shell.
*/

/*** INCLUDES: ***/
#include <stdlib.h>

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
*/
typedef struct 
{
	char *key;
	void *value;
	value_t valueType;
	int linkedIndex;
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