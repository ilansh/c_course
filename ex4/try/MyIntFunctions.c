//##############################################################################
// FILE       : MyIntFunctions.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex4 summer 2011
// DESCRIPTION: MyIntFunctions.c Is a file implementing MyIntFunctions.h.
//				It implements A print, hash and comparison functions
//				for integer type.
//				Those functions are used by GenericHashTable.c to insert,
//				retrieve and print integers from a hash table.
//##############################################################################

#include <stdio.h>
#include <stdlib.h>
#include "MyIntFunctions.h"
#include "TableErrorHandle.h"

#define EQUALS 0
#define NON_EQUALS 1

/*
 * Check if the given argument is null.
 * If it is, Print an error message and exit the program.
 * If not, do nothing.
 * @param arg - the argument to check.
 */
static void isNullArg(const void* arg)
{
//	The same method is also used in a static fashion in
//	GenericHashTable.c
//	I thought it would be better to rewrite it
//	Than to include the entire .c file.
	if(arg == NULL)
	{
		reportError(GENERAL_ERROR);
		exit(-1);
	}
}

/*
 * Hash function for integers.
 * calculates
 */
int intFcn (const void *key, size_t table_size)
{
	isNullArg(key);
	int int_val = *(int*)key;
	if(int_val < 0)
	{
		int_val = (int_val % (int)table_size) +  (int)table_size;
	}
	int size = (int)table_size;
	return (int_val % size);
}

void intPrint (const void *key)
{
	isNullArg(key);
	printf("(%d)",*(int*)key);
}

int intCompare (const void *key1, const void *key2)
{
	isNullArg(key1);
	isNullArg(key2);
	int int1 = *(int*)key1;
	int int2 = *(int*)key2;
	if(int1 == int2)
	{
		return EQUALS;
	}
	return NON_EQUALS;
}
