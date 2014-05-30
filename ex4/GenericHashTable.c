//##############################################################################
// FILE       : GenericHashTable.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex4 summer 2011
// DESCRIPTION: GenericHashTable.c Is a file implementing the GenericHashTable.h
//				interface.
//				It implements various operations on a hash table containing
//				keys of generic type - as long as each type provides an
//				implementation to its hash function, comparison function and
//				printing function.
//##############################################################################

#include <stdio.h>
#include "GenericHashTable.h"
#include "TableErrorHandle.h"
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND -1
#define NODE_ARROW_REGEX "\t--->\t"
#define CELL_REGEX "[cell %d]\t"
#define MAX_LIST_SIZE 2
#define GROWTH_FACTOR 2

typedef struct List* ListP;
typedef const struct List* ConstListP;
typedef const struct List ConstList;

//general object type contained in the hash table
//includes key and next (implemented as a list node)
//as each cell in the table contains a list of objects.
typedef struct Object
{
	ObjectP next;
	void *key;
}Object;

//table struct, contains the table cells (the lists),
//current table size, current table growth (growth factor
//from original table size), and the required functions
//as pointer.
typedef struct Table
{
	ListP lists;
	int size;
	int growth_factor;
	hashFcn hash_func;
	printFcn print_func;
	comparisonFcn comp_func;
}Table;

//List type, contained in each cell of the table.
//List struct has a pointer to the head of the list,
//as well a current size field.
typedef struct List
{
	ObjectP head;
	int size;
}List;

/*
 * Check if the given argument is null.
 * If it is, Print an error message and exit the program.
 * If not, do nothing.
 * @param arg - the argument to check.
 */
static void isNullArg(const void* arg)
{
	if(arg == NULL)
	{
		reportError(GENERAL_ERROR);
		exit(-1);
	}
}

/*
 * allocate memory and return a pointer to it.
 * print a relevant error message if there was not enough memory in the heap.
 * This method uses realloc if the given pointer is different than null.
 * This method uses malloc if the given pointer is null.
 * @param size - the size of memory to allocate
 * @param reAllocAdr - The address to be used in case of realloc.
 * @return pointer to the allocated memory.
 */
static void* allocMemory(int size, void* re_alloc_adr)
{
	void* mem_pointer;
	if(re_alloc_adr)
	{
		mem_pointer = realloc(re_alloc_adr,size);
	}
	else
	{
		mem_pointer = malloc(size);
	}
	if(mem_pointer == NULL)
	{
		reportError(MEM_OUT);
	}
	return mem_pointer;
}

/*
 * Get the index of a given key within a given list
 * (if it exists in the list).
 * The keys are compared using a given comparison function.
 * @param list The given list.
 * @param key The given key.
 * @param comp_func The given comparison function.
 * @return The index of the object if it is found in the list, -1 otherwise.
 */
static int getObjectIndexFromList(ConstList list,const void* key,
		const comparisonFcn comp_func)
{
	ObjectP cur_object = list.head;
	int counter = 0;
	while(cur_object != NULL)
	{
		if(!comp_func(key,cur_object->key)) //comp_func returns 0 if they are equal
		{
			return counter;
		}
		counter++;
		cur_object = cur_object->next;
	}
	return NOT_FOUND;
}

/*
 * print a list of objects to stdout, using a given print function.
 * @param list - the list to print.
 * @param print_func - a pointer to the relevant print function.
 */
static void printList(ConstList list, const printFcn print_func)
{
	ObjectP cur_object = list.head;
	while(cur_object != NULL)
	{
		print_func(cur_object->key);
		printf(NODE_ARROW_REGEX);
		cur_object = cur_object->next;
	}
	printf("\n");
}

/*
 * Add an object to the end of a given list.
 * If the list is empty the object is added as the list head.
 * @param list - The given list.
 * @param obj_to_add - The object to add.
 */
static void addToList(ListP list,const ObjectP obj_to_add)
{
	if(list->head == NULL)
	{
		list->head = obj_to_add;
	}
	else
	{
		ObjectP cur_object = list->head;
		while(cur_object->next!=NULL)
		{
			cur_object = cur_object->next;
		}
		cur_object->next = obj_to_add;
	}
	obj_to_add->next = NULL;
	list->size++;
}

/*
 * free the given list's allocated memory.
 * (free all the nodes).
 * @param list - The list to free.
 */
static void freeList(ListP list)
{
	ObjectP cur_object = list->head;
	//keeping a pointer to the next object so it won't be
	//lost after freeing the current object.
	ObjectP next_object;
	while(cur_object != NULL)
	{
		next_object = cur_object->next;
		freeObject(cur_object);
		cur_object = next_object;
	}
}

/*
 * initiate lists (cells) from the table with head node as null
 * and size 0.
 * the method can initiate a portion of the lists in the
 * table (as opposed to all of them each time),
 * by using the given parameter start.
 * @param lists - the array of lists in the table (the table cells).
 * @param size - the size of the table.
 * @param start - start position in the array to begin the iterations.
 */
static void initTableLists(ListP lists, int size,int start)
{
	int i;
	for(i=start; i<size; i++)
	{
		lists[i].head = NULL;
		lists[i].size = 0;
	}
}

/*
 * Expand the given table according to the macro GROWTH_FACTOR,
 * and add the given object to the table (called if all the lists (cells)
 * matching the hash of this object are full)
 * The array of lists (cells) contained in the table will be reallocated
 * to contain twice (or GROWTH_FACTOR) its previous memory,
 * newly allocated lists will be initiated, and existing lists
 * will be moved to even indices (each index moving to 2*index),
 * by switch pointers (thus no frees are needed).
 * the object meant to be allocated to the index [i] (which caused the
 * table to expand) will be allocated to the index [i*2 + 1] which is now
 * an empty list.
 * @param table - The table to expand.
 * @param object - The object to add to the table.
 * @return True if the process succeeded, false otherwise.
 */
static Boolean expandTable(TableP table,const ObjectP object)
{
	if(!(table->lists = (ListP)allocMemory(sizeof(List) * table->size * GROWTH_FACTOR,table->lists)))
	{ //out of memory:
		return FALSE;
	}
	initTableLists(table->lists,table->size * GROWTH_FACTOR,table->size);
	int i;
	//running from the end in order to keep the pointers' values when copying
	for(i=table->size - 1; i>0; i--) //moving table cells to even spots
	{
		table->lists[GROWTH_FACTOR * i] = table->lists[i];
		table->lists[i].head = NULL;
		table->lists[i].size = 0;
	}
	table->growth_factor *= GROWTH_FACTOR;
	table->size *= GROWTH_FACTOR;
	//adding to the hashed location + 1 (the next list is newly allocated and empty).
	addToList(&table->lists[table->hash_func(object->key,
			table->size / table->growth_factor) * table->growth_factor + 1],object);
	return TRUE;
}

/*
 * Allocate memory for an object which points to the given key.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
ObjectP createObject(void *key)
{
	isNullArg(key);
	ObjectP object = (ObjectP)allocMemory(sizeof(Object),NULL);
	if(object) //object!=null
	{
		object->key = key;
		object->next = NULL;
		return(object);
	}
	free(key);
	return(NULL);
}


/*
 * Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function,
 * report error MEM_OUT to the standard error and return NULL.
 */
TableP createTable(size_t table_size, hashFcn hfun, printFcn pfun, comparisonFcn fcomp)
{
	isNullArg(hfun);
	isNullArg(pfun);
	isNullArg(fcomp);
	TableP table = (TableP)allocMemory(sizeof(Table),NULL);
	if(table) //if table != NULL
	{
		table->lists = (ListP)allocMemory(sizeof(List) * table_size,NULL);
		if(table->lists) //if table->lists != NULL
		{
			initTableLists(table->lists,table_size,0);
			table->size = table_size;
			table->hash_func = hfun;
			table->print_func = pfun;
			table->comp_func = fcomp;
			table->growth_factor = 1;
			return table;
		}
		free(table);
	}
	return NULL;
}


/*
 * Insert an object to the table.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory during the table duplication, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return TRUE. Otherwise (an error occured) return FALSE.
 */
Boolean insertObject(TableP table, ObjectP object)
{
	int i;
	//free space for the object could be either the cell itself (location + 0) or
	for(i = 0; i<table->growth_factor; i++)
	{
		if(table->lists[i + table->hash_func(object->key,table->size / table->growth_factor) * table->growth_factor].size < MAX_LIST_SIZE)
		{
			addToList(&table->lists[i + table->hash_func(object->key,table->size / table->growth_factor) *table->growth_factor],object);
			return TRUE;
		}
	}
	return (expandTable(table,object));
}


/*
 * Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell), and its placement in the list into listNode (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If the key was not found, fill both pointers with value of -1.
 */
void findObject(ConstTableP table, const void* key, int* arr_cell, int* list_node)
{
	isNullArg(table);
	isNullArg(key);
	isNullArg(arr_cell);
	isNullArg(list_node);
	*arr_cell = table->hash_func(key,table->size / table->growth_factor) * table->growth_factor;
	List cur_list;
	int i;
	for(i = *arr_cell; i< *arr_cell + table->growth_factor; i++)
	{
		cur_list = table->lists[i];
		if(cur_list.head!= NULL) //!= NULL
		{
			if((*list_node=getObjectIndexFromList(cur_list,key,table->comp_func))!= NOT_FOUND)
			{
				//object found, *list_node and *arr_cell hold the relevant values.
				*arr_cell = i;
				return;
			}
		}
	}
	//object not found
	*arr_cell = NOT_FOUND;
}


/*
 * Print the table (use the format presented in example).
 */
void printTable(ConstTableP table)
{
	isNullArg(table);
	int i;
	for(i=0; i<table->size;i++)
	{
		printf(CELL_REGEX,i);
		printList(table->lists[i],table->print_func);
	}
}


/*
 * Free all the memory allocated for an object, including the memory allocated
 * for the key.
 * Use this function when you free the memory of the table.
 */
void freeObject(ObjectP object)
{
	isNullArg(object);
	free(object->key);
	free(object);
}


/*
 * Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table)
{
	isNullArg(table);
	int i;
	for(i=0; i<table->size; i++)
	{
		freeList(&table->lists[i]);
	}
	free(table->lists);
	free(table);
}
