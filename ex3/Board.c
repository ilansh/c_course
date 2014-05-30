//##############################################################################
// FILE       : Board.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex3 summer 2011
// DESCRIPTION: Board.c is the implementation of the header file board.h
//				It implements a set of operations to be executed on a Gomoku board.
//				This file's responsibilities are mainly allocating space for the board
//				and handling player's requests.
//				Freeing space and running the game process are the user's responsibility.
//##############################################################################

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Board.h"
#include "ErrorHandle.h"

#define EMPTY_SQUARE ' '
#define X_SQUARE 'X'
#define O_SQUARE 'O'
#define OUT_OF_BOUNDS_ERROR 'E'
#define DEF_SIZE 10
//macro for accessing the matching 2D array index in a 1D array.
#define TWOD_INDEX(y,x,c) (y)*(c) + (x)
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define PRINT_AREA 50
#define WIN_SEQUENCE 5
#define EXPAND_FACTOR 2 //board expanding factor when indices are out of bounds
//directions to check for a winner in the 2D array:
#define NORTH 0,-1
#define NORTH_EAST 1,-1
#define EAST 1,0
#define SOUTH_EAST 1,1
#define SOUTH 0,1
#define SOUTH_WEST -1,1
#define WEST -1,0
#define NORTH_WEST -1,-1



typedef struct Board
{
	//when reading the exercise description I got the impression that we
	//had to keep the actual size of the array in one field, that is why I don't have
	//rows and cols as fields, but just cols.
	//this doesn't matter since rows can be acquired by
	//(board_size/sizeof(char)) / board_cols
	int board_size;
	int board_cols;
	char* board_arr;
	char winner;
	char cur_turn;
}Board;

/*
 * allocate memory and return a pointer to it.
 * print a relevant error message if there was not enough memory in the heap.
 * This method uses realloc if the given pointer is different than null.
 * This method uses malloc if the given pointer is null.
 * @param size - the size of memory to allocate
 * @param reAllocAdr - The address to be used in case of realloc.
 * @return pointer to the allocated memory.
 */
static void* allocMemory(int size, void* reAllocAdr)
{
	void* mem_pointer;
	if(reAllocAdr)
	{
		mem_pointer = realloc(reAllocAdr,size);
	}
	else
	{
		mem_pointer = malloc(size);
	}
	if(mem_pointer == NULL)
	{
		reportError(MEM_OUT);
		return NULL;
	}
	return mem_pointer;
}

/*
 * copy one array into another.
 * @param arrToCopy the array to be copied.
 * @param arrToReturn an empty array to be copied into.
 * @param size The number of entries to be copied.
 */
static void copyArray(char const * arrToCopy,char* arrToReturn, int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		arrToReturn[i] = arrToCopy[i];
	}
}

/*
 * initiate a play board array to all spaces (empty squares).
 * @param board - a pointer to the board containing the array.
 */
static void initBoard(BoardP board)
{
	int i;
	for(i=0; i<board->board_size; i++)
	{
		board -> board_arr[i] = EMPTY_SQUARE;
	}
}

/*
 * check if a given square is within the board boundaries.
 * @param x the given column of the square
 * @param y the given row of the square
 * @return true if the square is within the boundaries, false otherwise.
 */
static Boolean isWithinBoundaries(int x,int y,ConstBoardP board)
{
	if(x >= board -> board_cols || y >= board -> board_size / board -> board_cols)
	{
		return FALSE;
	}
	return TRUE;
}

/*
 * check if a given square's row and column values are positive,
 * and prints an error message if not.
 * @param x the given column of the square
 * @param y the given row of the square
 * @return true if the square is positive, false otherwise.
 */
static Boolean isPositiveIndex(int x,int y)
{
	if(x<0 || y<0)
	{
		reportError(OUT_OF_BOUND);
		return FALSE;
	}
	return TRUE;
}

/*
 * check if a given char is either 'X' or 'O' (matching one of the player's tag),
 * and prints an error message if not.
 * @param val the given char.
 * @return true if the char is valid, false otherwise.
 */
static Boolean isValidChar(char val)
{
	if(val != X_SQUARE && val != O_SQUARE)
	{
		reportError(BAD_VAL);
		return FALSE;
	}
	return TRUE;
}

/*
 * check if a given square on the board is occupied.
 * prints an error message according to a given situation.
 * This method is used both to verify empty square when putting a new value on the board,
 * and to verify full square when removing a value from the board.
 * @param x the given column of the square
 * @param y the given row of the square
 * @param board the given play board.
 * @param error the error matching the situation from which the method was called.
 * @return true if the square is full, false other wise.
 */
static Boolean isSquareFull(int x,int y,ConstBoardP board,BoardErrors error)
{
	char square_val = getBoardSquare(board,x,y);
	if(square_val == EMPTY_SQUARE)
	{
		if(error == ILLEGAL_CANCELLATION)
		{
			reportError(ILLEGAL_CANCELLATION);
		}

		return FALSE;
	}
	//square is full:
	if(error == SQUARE_FULL)
	{
		reportError(SQUARE_FULL);
	}
	return TRUE;
}

/*
 * check if the correct player has played this turn
 * (the correct value was put on the board),
 * and print an error message if not.
 * @param val the last player's tag.
 * @return true if the correct turn was played, false otherwise.
 */
static Boolean isCorrectTurn(char val, ConstBoardP board)
{
	if(val != board -> cur_turn)
	{
		reportError(WRONG_TURN);
		return FALSE;
	}
	return TRUE;
}

/*
 * check if a cancel move is valid (not a self cancel).
 * @param x the given column of the square to cancel
 * @param y the given row of the square to cancel
 * @param board -the playing board.
 * @return true if the cancel was valid, false otherwise.
 */
static Boolean isSelfCancel(int x,int y,ConstBoardP board)
{
	if(board -> cur_turn != board->board_arr[TWOD_INDEX(y,x,board->board_cols)])
	{
		return FALSE;
	}
	reportError(ILLEGAL_CANCELLATION);
	return TRUE;
}

/*
 * check that a board pointer is not null.
 * if it is null an error is printed and the program exits.
 * @param board - the playing board.
 */
static void isBoardValid(ConstBoardP board)
{
	if(board == NULL)
	{
		reportError(GENERAL_ERROR);
		exit(-1);
	}
}

/*
 * create a new playing board with to given height and width,
 * initializing and allocating all required memory.
 * @param height the height of the board to create.
 * @param width the width of the board to create.
 * @return a pointer to the new board created.
 */
static BoardP newBoard(int width, int height)
{
	BoardP newBoard = NULL;
	if((newBoard = (BoardP)allocMemory(sizeof(Board),NULL)))
	{
		if((newBoard -> board_arr = (char*)allocMemory(width * height * sizeof(char),NULL)))
		{
			newBoard -> board_size = width * height * sizeof(char);
			newBoard -> board_cols = width;
			newBoard -> winner = EMPTY_SQUARE;
			newBoard -> cur_turn = X_SQUARE;
			initBoard(newBoard);
			//the process ended successfully.
			return newBoard;
		}
		//a memory error occured, freeing the allocated board.
		free(newBoard);
	}
	return NULL;
}

/*
 * switch turns between the two players.
 * @param board - the playing board.
 * @return true if the square is within the boundaries, false otherwise.
 */
static void switchTurn(BoardP board)
{
	if(board -> cur_turn == X_SQUARE)
	{
		board -> cur_turn = O_SQUARE;
	}
	else
	{
		board -> cur_turn = X_SQUARE;
	}
}

/*
 * fill the newly allocated (and larger) game board with the values given in
 * the old game board in matching locations.
 * @param new_board the board to be filled.
 * @param y old_board the given board.
 */
static void fillBoard(BoardP new_board,BoardP old_board)
{
	int i,j;
	for(i=0;i<old_board -> board_size / old_board -> board_cols; i++)
	{
		for(j=0; j<old_board -> board_cols;j++)
		{
			//calculating location according to new_cols and old_cols to get
			//required position
			new_board->board_arr[TWOD_INDEX(i,j,new_board->board_cols)] =
					old_board->board_arr[TWOD_INDEX(i,j,old_board->board_cols)];
		}
	}
}

/*
 * count the number of digits in a given number.
 * @param num - the given number.
 * @return the number of digits.
 */
static int countDigits(int num)
{
	int counter = 1;
	while(num/=10)
	{
		counter++;
	}
	return counter;
}

/*
 * This method counts squares from a given starting square in a given direction
 * the number of occurrences of a given character in a 2D array.
 * Its purpose is to find a winner on the game board, counting up to 5 squares in
 * one direction.
 * @param board The given game board.
 * @param x - columns position of the starting square.
 * @param y - the rows position of the starting square.
 * @param cur_player - the character of the current player (the last one who played).
 * @param xFactor - The direction to move in the horizontal plane of the 2D array.
 * @param yFactor - The direction to move in the vertical plane of the 2D array.
 * ***(-1,0,1) are the possible values of xFactor and yFactor to accomodate all possible
 * winning sequences***
 * @return the number of occurences of the given char counted in the given direction.
 */
static int countInDirection(ConstBoardP board, int x, int y, char cur_player,
		int xFactor, int yFactor)
{
	int i=x+xFactor,j=y+yFactor;
	int counter = 0;
	//not going over 5 squares, and over the board limits.
	while(fabs(j-y)<WIN_SEQUENCE && j>=0 && j< (board->board_size / board->board_cols)
	&& fabs(i-x)<WIN_SEQUENCE && i>=0 && i< (board -> board_cols))
	{
		if(board ->board_arr[TWOD_INDEX(j,i,board->board_cols)] != cur_player)
		{
			break; //if an empty or other player's square was found, break.
		}
		counter++;
		//add to i and j according to the given movement directions.
		i+=xFactor;
		j+=yFactor;
	}
	return counter;
}

/*
 * Check if the current player (last one played) is the winner.
 * The method iterates over 5 squares in all 8 directions from the last position played
 * and checks if there is a sequence of 5 of the current player's char on the same line
 * (either horizontal line,vertical line, or both diagonals).
 * @param board - The playing board.
 * @param x - the given column of the starting square.
 * @param y - the given row of the starting square.
 * @param cur_player - The char representing the current player.
 * @return The character of the player if he was found the winner, empty square otherwise.
 */
static char checkWinner(ConstBoardP board, int x,int y, char cur_player)
{
	//check north-south line
	if((countInDirection(board,x,y,cur_player,NORTH) +
			countInDirection(board,x,y,cur_player,SOUTH)) + 1 >= WIN_SEQUENCE)
	{
		return cur_player;
	}
	//check east-west line
	else if((countInDirection(board,x,y,cur_player,EAST) +
			countInDirection(board,x,y,cur_player,WEST)) + 1 >=WIN_SEQUENCE)
	{
		return cur_player;
	}
	//check northeast-southwest line
	else if((countInDirection(board,x,y,cur_player,NORTH_EAST) +
				countInDirection(board,x,y,cur_player,SOUTH_WEST)) + 1 >=WIN_SEQUENCE)
	{
		return cur_player;
	}
	//check northwest-southeast line
	else if((countInDirection(board,x,y,cur_player,NORTH_WEST) +
				countInDirection(board,x,y,cur_player,SOUTH_EAST)) + 1 >= WIN_SEQUENCE)
	{
		return cur_player;
	}
	return EMPTY_SQUARE;
}

/*
 * Expand the array representing the game board.
 * If x (or y) is beyond the current board space in the x direction,
 * The new board space will be double that of x (or y).
 * running time is O(oldBoardSize + newBoardSize) as required.
 */
static char* expandBoard(BoardP cur_board,int x,int y)
{
	int new_cols=cur_board -> board_cols;
	int new_rows=cur_board -> board_size / cur_board -> board_cols;
	char* expanded_board;
	//duplicate the old board for copying later onto the expanded board
	BoardP old_board_copy = duplicateBoard(cur_board);
	if(old_board_copy == NULL)
	{
		return NULL; //not enough space for duplicating
	}
	if(x >= cur_board -> board_cols)
	{
		new_cols = EXPAND_FACTOR * x;
	}
	if(y >= cur_board -> board_size / cur_board -> board_cols)
	{
		new_rows = EXPAND_FACTOR * y;
	} //allocate more space for the board array using realloc,verifying enough memory:
	if((expanded_board =
			allocMemory(new_cols * new_rows * sizeof(char),cur_board -> board_arr)))
	{
		cur_board -> board_arr = expanded_board;
		cur_board -> board_size = new_cols * new_rows * sizeof(char);
		cur_board -> board_cols = new_cols;
		//initialize the new board and rewrite the existing values
		//from the duplicated board
        initBoard(cur_board);
        fillBoard(cur_board,old_board_copy);
	}
	freeBoard(old_board_copy);
	return expanded_board;
}

/*
 * Allocate memory for a default empty board (size 10X10) and return it.
 * If run out of memory, free all the memory that was already allocated by the function, 
   report error MEM_OUT to the standard error and return NULL.
 */
BoardP createNewDefaultBoard()
{
	return newBoard(DEF_SIZE,DEF_SIZE);
}

/*
 * Allocate memory for an empty board (size width X high) and return it.
 * If run out of memory, free all the memory that was allocate, report error MEM_OUT and return NULL.
 */
BoardP createNewBoard(int width, int high)
{
	return newBoard(width,high);
}

/*
 * Duplicate the original board and return a new one.
 * The old board stays exactly the same (the memory of the old board is not
 * freed and remains the same).
 * In case the function runs out of memory while creating the new board, MEM_OUT error is reported and NULL is returned.
 * The old board stays the same. You should free all the memory that was already allocated for the new board.
 */
BoardP duplicateBoard(ConstBoardP originalBoard)
{
	isBoardValid(originalBoard);
	BoardP newBoard = NULL;
	if((newBoard = (BoardP)allocMemory(sizeof(Board),NULL)))
	{
		if((newBoard -> board_arr =
				(char*)allocMemory(originalBoard -> board_size * sizeof(char),NULL)))
		{
			newBoard -> board_size = originalBoard -> board_size;
			newBoard -> board_cols = originalBoard -> board_cols;
			copyArray(originalBoard -> board_arr,newBoard->board_arr,
					newBoard -> board_size);
			return(newBoard);
		}
		//not enough memory for the array:
		free(newBoard);
	}
	return NULL;
}

/*
 * Check the value of the square X,Y on the board. Assume the squares index is starting from zero.
 * Return 'X' if 'X' own the square, 'O' (big o, not a zero) if 'O' own the square, and ' ' (a space) if it's an empty square.
 * If X or Y are negative, report an error OUT_OF_BOUND and return 'E'.
 * If (X,Y) is out of the current memory allocated area, then it must be an empty square - return ' ' (a space).
 */
char getBoardSquare(ConstBoardP theBoard, int X, int Y)
{
	isBoardValid(theBoard);
	int cols = theBoard -> board_cols;
	if(!isPositiveIndex(X,Y))
	{
		return OUT_OF_BOUNDS_ERROR;
	}
	else if(!isWithinBoundaries(X,Y,theBoard))
	{
		return EMPTY_SQUARE;
	}
	return theBoard -> board_arr[TWOD_INDEX(Y,X,cols)];
}

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
Boolean putBoardSquare(BoardP theBoard, int X, int Y, char val)
{
	isBoardValid(theBoard);
	if(!isValidChar(val) || !isPositiveIndex(X,Y) || isSquareFull(X,Y,theBoard,SQUARE_FULL)
			|| !isCorrectTurn(val,theBoard))
	{
		return FALSE;
	}
	if(!isWithinBoundaries(X,Y,theBoard))
	{
		if(!expandBoard(theBoard,X,Y))
		{
			return FALSE;
		}
	}
	theBoard -> board_arr[TWOD_INDEX(Y,X,theBoard->board_cols)] = val;
	theBoard -> winner = checkWinner(theBoard,X,Y,val);
	switchTurn(theBoard);
	return TRUE;
}

/*
 * Cancel a move (not necessarily the last move) - turn the square back to be empty.
 * If X or Y are negative, report OUT_OF_BOUND and do nothing.
 * If square (X,Y) is already empty, report ILLEGAL_CANCELLATION.
 * If canceling the move will result with more 'O' than 'X'es on the board, or if cancelling the move will result with two more 'X'es on the board than 'O', report ILLEGAL_CANCELLATION and do nothing.
 * The function *doesn't* update information for the GetWinner() function - winning can not be canceled by canceling a move.
 * If everything is OK, return TRUE. Otherwise (an error occured) return FALSE.
 */
Boolean cancelMove(BoardP theBoard, int X, int Y)
{
	isBoardValid(theBoard);
	if(!isPositiveIndex(X,Y) || !isSquareFull(X,Y,theBoard,ILLEGAL_CANCELLATION)
			|| isSelfCancel(X,Y,theBoard))
	{
		return FALSE;
	}
	theBoard->board_arr[TWOD_INDEX(Y,X,theBoard->board_cols)] = EMPTY_SQUARE;
	switchTurn(theBoard);
	return TRUE;
}

/*
 * Check if there's a winner on the board - a player that owns 5 squares in a line (vertical, horizontal or diagonal).
 * Return the player ('X' / 'O') is such exists, or ' ' (space) otherwise.
 * If both players win, return an arbitrary value (illegal situation which you may assume never happens).
 * Should work in O(1) - use information provided by the PutBoardSquare() function.
 */
char getWinner(ConstBoardP board)
{
	//the algorithm for finding the winner is implemented at checkWinner method
	//It also takes O(1) as required.
	isBoardValid(board);
	return board -> winner;
}

/*
 * Free all the memory allocated for the board. It's the user responsibility to call this function before
   exiting the program.
 */
void freeBoard(BoardP board)
{
	if(board != NULL)
	{
		free(board -> board_arr);
		free(board);
	}
}


/*
 * Print the board from position (X,Y).
 * If X or Y are negative, report OUT_OF_BOUND and do nothing.
 * Squares outside of the current memory location should be printed as empty squares.
 */
void printBoard(ConstBoardP board, int X, int Y)
{
	isBoardValid(board);
	int i,j;
	//defining the number of columns to be displayed as the
	//total area divided by the size given to each column (determined by the num
	//of digits).
	int column_space = countDigits(MIN(X,Y)) + 2;
	int columns_num = PRINT_AREA / column_space;
	printf("\t");
	for(i=X; i<X+columns_num ; i++)
	{
		printf("%*d",column_space,i);
	}
	printf("\n");
	for(i = Y; i< Y + columns_num ; i++)
	{
		printf("%6d\t",i);
		for(j = X; j< X + columns_num; j++)
		{
			if(j<board->board_cols  && i< board->board_size / board->board_cols)
			{
				printf("%*c",column_space,board ->
						board_arr[TWOD_INDEX(i,j,board->board_cols)]);
			}
			else
			{
				printf("%*c",column_space,EMPTY_SQUARE);
			}
		}
		printf("\n");
	}
}

