#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

typedef enum {MEM_OUT, OUT_OF_BOUND, SQUARE_FULL, WRONG_TURN, BAD_VAL, ILLEGAL_CANCELLATION, GENERAL_ERROR} BoardErrors;

/* Receive an error and report it. Do all the errors report through this function. */
void reportError(BoardErrors boardError);


#endif
