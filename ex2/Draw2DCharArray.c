//##############################################################################
// FILE       : Draw2DCharArray.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex2 summer 2011
// DESCRIPTION: This program implements basic operations on a 2-dimensional
//              char array - initializing, and printing to stdout.
//##############################################################################
#include <stdio.h>
#include "Draw2DCharArray.h"


/*
 * Initialize the given char array to be filled with space (' ') characters.
 * @param arr - The array to initialize.
 */
void initializeArray(char arr[ROWS][COLS])
{
    int i,j;
    for(i=0; i<ROWS; i++)
    {
        for(j=0;j<COLS;j++)
        {
            arr[i][j] = ' ';
        }
    }
}

/*
 * Draw the char array on the screen.
 * After each row go down a line ("\n").
 * @param arr - The array to print.
 */
void DrawArray(char arr[ROWS][COLS])
{
    int i,j;
    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
}
