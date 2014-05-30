//##############################################################################
// FILE       : HashIntMain.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex4 summer 2011
// DESCRIPTION: HashIntMain.c Is a driver for testing GenericHashTable.c
//				It includes only a main function for creating a table,
//				inserting objects containing integers into the table,
//				printing the table, and finally freeing the table.
//##############################################################################

#include <stdio.h>
#include "GenericHashTable.h"
#include "MyIntFunctions.h"
#include <stdlib.h>
#include <math.h>

#define MIN_INT -17
#define MAX_INT 21

/*
 * main function for testing GenericHashTable.c
 * as described above.
 */
int main(int argc, char* argv[])
{
	TableP my_table = createTable(atoi(argv[1]),intFcn,intPrint,intCompare);
	int i;
	int* key;
	ObjectP object;
	for(i=MIN_INT; i<= MAX_INT; i++)
	{
		key = (int*)malloc(sizeof(int));
		*key = i;
		object = createObject(key);
		insertObject(my_table,object);
	}
	printTable(my_table);
	freeTable(my_table);
	return 0;
}
