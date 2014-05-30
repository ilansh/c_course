#ifndef _GENERIC_HASH_TABLE_
#define _GENERIC_HASH_TABLE_

typedef struct Object* ObjectP;
typedef struct Table* TableP;
typedef const struct Table* ConstTableP;
typedef enum {FALSE, TRUE} Boolean;


/*
 * hash function
 */
typedef int(*hashFcn)(const void *key, size_t table_size);


/*
 * key print function
 */
typedef void(*printFcn)(const void *key);


/*
 * key comparison function: returns non-zero if both keys are different, 
 * otherwise returns zero.
 */
typedef int(*comparisonFcn)(const void *key1, const void *key);




/*
 * Allocate memory for an object which points to the given key.
 * If run out of memory, free all the memory that was already allocated by the function, 
 * report error MEM_OUT to the standard error and return NULL.
 */
ObjectP createObject(void *key);


/*
 * Allocate memory for a hash table with which uses the given functions.
 * tableSize is the number of cells in the hash table.
 * If run out of memory, free all the memory that was already allocated by the function, 
 * report error MEM_OUT to the standard error and return NULL.
 */
TableP createTable(size_t table_size, hashFcn hfun, printFcn pfun, comparisonFcn fcomp);


/*
 * Insert an object to the table.
 * If all the cells appropriate for this object are full, duplicate the table.
 * If run out of memory during the table duplication, report
 * MEM_OUT and do nothing (the table should stay at the same situation
 * as it was before the duplication).
 * If everything is OK, return TRUE. Otherwise (an error occured) return FALSE.
 */
Boolean insertObject(TableP table, ObjectP object);



/*
 * Search the table and look for an object with the given key.
 * If such object is found fill its cell number into arrCell (where 0 is the
 * first cell), and its placement in the list into listNode (when 0 is the
 * first node in the list, i.e. the node that is pointed from the table
 * itself).
 * If the key was not found, fill both pointers with value of -1.
 */
void findObject(ConstTableP table, const void* key, int* arr_cell, int* list_node);


/*
 * Print the table (use the format presented in example).
 */
void printTable(ConstTableP table);


/*
 * Free all the memory allocated for an object, including the memory allocated
 * for the key.
 * Use this function when you free the memory of the table.
 */
void freeObject(ObjectP object);


/*
 * Free all the memory allocated for the table.
 * It's the user responsibility to call this function before exiting the program.
 */
void freeTable(TableP table);




#endif // _GENERIC_HASH_TABLE_
