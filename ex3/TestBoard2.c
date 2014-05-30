#include <assert.h>
#include <stdio.h>
#include "Board.h"

int main()
{
    BoardP theBoard = createNewDefaultBoard();
    if (!putBoardSquare(theBoard, 1,4,'X'))
    {
        printf("Error1\n");
        return 1;
    }
    if (!putBoardSquare(theBoard, 4,1,'O'))
    {
        printf("Error2\n");
        return 1;
    }
    if (!putBoardSquare(theBoard, 2,4,'X'))
    {
        printf("Error3\n");
        return 1;
    }
    freeBoard(theBoard);
    printf("GoodTest\n");
    return 0;
}
