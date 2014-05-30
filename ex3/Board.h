#ifndef BOARD_H
#define BOARD_H

typedef struct Board* BoardP;
typedef const struct Board* ConstBoardP;
typedef enum {FALSE, TRUE} Boolean;


/*
 * Allocate memory for a default empty board (size 10X10) and return it.
 * If run out of memory, free all the memory that was already allocated by the function, 
   report error MEM_OUT to the standard error and return NULL.
 */
BoardP createNewDefaultBoard();


/*
 * Allocate memory for an empty board (size width X high) and return it.
 * If run out of memory, free all the memory that was allocate, report error MEM_OUT and return NULL.
 */
BoardP createNewBoard(int width, int high);

/*
 * Duplicate the original board and return a new one.
 * The old board stays exactly the same (the memory of the old board is not
 * freed and remains the same).
 * In case the function runs out of memory while creating the new board, MEM_OUT error is reported and NULL is returned.
 * The old board stays the same. You should free all the memory that was already allocated for the new board.
 */
BoardP duplicateBoard(ConstBoardP originalBoard);


/*
 * Check the value of the square X,Y on the board. Assume the squares index is starting from zero.
 * Return 'X' if 'X' own the square, 'O' (big o, not a zero) if 'O' own the square, and ' ' (a space) if it's an empty square.
 * If X or Y are negative, report an error OUT_OF_BOUND and return 'E'.
 * If (X,Y) is out of the current memory allocated area, then it must be an empty square - return ' ' (a space).
 */
char getBoardSquare(ConstBoardP theBoard, int X, int Y);


/*
 * Make a move: mark on location (X,Y) the value 'val'.
 * If 'val' is not 'X' or 'O', report BAD_VAL and do nothing.
 * If X or Y are negative report OUT_OF_BOUND and do nothing.
 * If square (X,Y) is already full, report SQUARE_FULL and do nothing.
 * If val is 'X' but it's 'O' turn (or val is 'O' but it's 'X' turn) - report WRONG_TURN and do nothing.
 * If sqaure (X,Y) is out of the current memory area - allocate more memory for a board of size (2X, Y) / (X, 2Y) / (2X, 2Y)
   (the minimal require between the above 3 options) and do the move.
   If run out of memory during the allocation, report MEM_OUT and do nothing (the board should
   stay at the same situation as it was before the function call).
 * If the function success, update information require for GetWinner() function.
 * If everything is OK, return TRUE. Otherwise (an error accure) return FALSE.
 */
Boolean putBoardSquare(BoardP theBoard, int X, int Y, char val);


/*
 * Cancel a move (not necessarily the last move) - turn the square back to be empty.
 * If X or Y are negative, report OUT_OF_BOUND and do nothing.
 * If square (X,Y) is already empty, report ILLEGAL_CANCELLATION.
 * If canceling the move will result with more 'O' than 'X'es on the board, or if cancelling the move will result with two more 'X'es on the board than 'O', report ILLEGAL_CANCELLATION and do nothing.
 * The function *doesn't* update information for the GetWinner() function - winning can not be canceled by canceling a move.
 * If everything is OK, return TRUE. Otherwise (an error occured) return FALSE.
 */
Boolean cancelMove(BoardP theBoard, int X, int Y);


/*
 * Check if there's a winner on the board - a player that owns 5 squares in a line (vertical, horizontal or diagonal).
 * Return the player ('X' / 'O') is such exists, or ' ' (space) otherwise.
 * If both players win, return an arbitrary value (illegal situation which you may assume never happens).
 * Should work in O(1) - use information provided by the PutBoardSquare() function.
 */
char getWinner(ConstBoardP board);

/*
 * Free all the memory allocated for the board. It's the user responsibility to call this function before
   exiting the program.
 */
void freeBoard(BoardP board);

/*
 * Print the board from position (X,Y).
 * If X or Y are negative, report OUT_OF_BOUND and do nothing.
 * Squares outside of the current memory location should be printed as empty squares.
 */
void printBoard(ConstBoardP board, int X, int Y);


#endif
