#include <stdio.h>
#include "Draw2DCharArray.h"

char arr[ROWS][COLS];


void fillArray1()
{
    int middleCol = COLS/2 + 1;
    int middleRow = ROWS/2 + 1;

    arr[middleRow][middleCol] = '_';

    arr[middleRow][middleCol+1] = '/';
    arr[middleRow-1][middleCol+2] = '/';
    //arr[middleRow-2][middleCol+3] = '/';

    arr[middleRow][middleCol-1] = '\\';
    arr[middleRow-1][middleCol-2] = '\\';
    //arr[middleRow-2][middleCol-3] = '\\';

    arr[middleRow-2][middleCol] = '|';
    arr[middleRow-3][middleCol] = '|';
    arr[middleRow-4][middleCol] = '|';

    arr[middleRow-5][middleCol+1] = '(';
    arr[middleRow-5][middleCol+2] = ')';

    arr[middleRow-5][middleCol-1] = ')';
    arr[middleRow-5][middleCol-2] = '(';
}

// Some characters are not visible on the screen, so make sure the char is
// from the "visible" part of the ASCII table:
char makeSureVisibleChar(char c)
{
    if ((c < ' ') || (c > '~')) {
        return ' ';
    }
    else {
        return c;
    }
}

void fillArray2(char startWith)
{
    int row,col;

    arr[0][0] = makeSureVisibleChar(startWith);

    for (col = 1; col < COLS; col ++) {
        arr[0][col] = makeSureVisibleChar(arr[0][col-1] + 1);
    }

    for (row = 1; row < ROWS; row ++) {
        arr[row][0] = makeSureVisibleChar(arr[row-1][0] + 1);
        for (col = 1; col < COLS; col ++) {
            arr[row][col] = makeSureVisibleChar(arr[row][col-1] + 1);
        }
    }
}

int main()
{

    printf("Select 1, 2 or 3:\n");
    int choice;
    scanf("%d",&choice);

    initializeArray(arr);

    switch (choice) {
      case 1:
          fillArray1();
          break;
      case 2:
          fillArray2(' ');
          break;
      case 3:
          fillArray2('A');
          break;
      default: printf("bad choice.\n");
          return -1;
    }

    DrawArray(arr);

    return 0;
}
