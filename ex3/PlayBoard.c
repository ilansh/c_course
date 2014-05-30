#include <assert.h>
#include <stdio.h>
#include <stdlib.h>            /* For exit */
#include "Board.h"

int main()
{
    int curX = 0, curY = 0;
    Boolean MoveSucc;
    char nextTurn = 'X';
    BoardP theBoard = createNewDefaultBoard();
    if (theBoard == NULL) {
		// createNewDefaultBoard() reports on the error.
		exit(1);
	}
    while (1)
    {
        int sel, selsucc, getX, getY;
        printBoard(theBoard, curX, curY);
        printf("What do you want to do?\n");
        printf("1. Make a move\n");
        printf("2. Cancel a move\n");
        printf("3. Change print location.\n");
        printf("4. Quit.\n");
        selsucc = scanf("%d", &sel);
        if (sel < 1 || sel > 4 || selsucc != 1)
        {
            printf("Illegal selection.\n\n");
            freeBoard(theBoard);
            return 1;
        }
        if (sel == 4)
        {
            freeBoard(theBoard);
            break;
        }
        printf("Choose location: (");
        scanf("%d", &getY);
        printf("Choose location: (%d,", getY);
        scanf("%d", &getX);
        printf("\n\n\n");
        if (sel == 1)
        {
            MoveSucc = putBoardSquare(theBoard, getX, getY, nextTurn);
            if (getWinner(theBoard) == 'X')
            {
                printf("\n\nX wins the game!!!\n\n");
            }
            else
            if (getWinner(theBoard) == 'O')
            {
                printf("\n\nO wins the game!!!\n\n");
            }
        }
        if (sel == 2)
        {
            MoveSucc = cancelMove(theBoard, getX, getY);
        }
        if ((sel == 1 || sel == 2) && MoveSucc)
        {
            if (nextTurn == 'X')
                nextTurn = 'O';
            else
                nextTurn = 'X';
        }
        if (sel == 3)
        {
            curX = getX;
            curY = getY;
        }
    }
    return 0;
}
