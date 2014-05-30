#ifndef DRAW_2D_CHAR_ARRAY_H
#define DRAW_2D_CHAR_ARRAY_H

#define ROWS 21
#define COLS 71

/*
 * Initialize the given char array to be filled with space (' ') characters.
 */
void initializeArray(char arr[ROWS][COLS]);

/*
 * Draw the char array on the screen.
 * After each row go down a line ("\n").
 */
void DrawArray(char arr[ROWS][COLS]);

#endif
