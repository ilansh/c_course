//##############################################################################
// FILE       : SeparationMap.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex2 summer 2011
// DESCRIPTION: This file contains a program for representing a 2D separation
//              Map visually - using ascii characters printed to the stdout.
//              In addition, The progam allows to display given vectors with
//              known tags on the map.
//              The map parameters and given sample vectors are received in the
//              program via input files.
//##############################################################################

#include <stdio.h>
#include <stdlib.h>
#include "Separator.h"
#include "IOHelper.h"
#include <string.h>
#include <math.h>
#include "Draw2DCharArray.h"

#define X_MAX 35
#define X_MIN -35
#define Y_MAX 10
#define Y_MIN -10
#define MAP_DIMENSION 2
#define POS_CHAR '*'
#define NEG_CHAR '.'
#define NOTAG_CHAR ' '
#define ORIGIN '+'
#define X_AXIS '-'
#define Y_AXIS '|'

/*
 * This method creates a 2D separation map using a given separator, according
 * to required description.
 * The map is stored inside a 2D char array.
 * @param map - The 2D array to store the map in.
 * @param Separator - A vector representing the given separator.
 */
void createMapArray(char map[ROWS][COLS],const double separator[MAX_DIMENSION])
{
    int x,y;
    double cur_point[MAX_DIMENSION]; //The current point in the map.
    Tag cur_tag; //The tag calculated for the current point.
    //variables for iterating over the the x and y axes
    //starting from the top left corner moving one line at a time working
    //our way to the bottom right corner of our range.
    for(y = Y_MAX; y >= Y_MIN; y--)
    {
        for(x = X_MIN; x <= X_MAX; x++)
        {
            cur_point[0] = x;
            cur_point[1] = y;
            cur_tag = tagNewDataPoint(cur_point,separator,MAP_DIMENSION);
            if(x==0 && y ==0)
            {
                //start from [0][0] working our way to [ROWS-1][COLS-1]
                map[Y_MAX - y][x+X_MAX] = ORIGIN;
            }
            else if(x==0)
            {
                map[Y_MAX - y][x+X_MAX] = Y_AXIS;
            }
            else if(y==0)
            {
                map[Y_MAX - y][x+X_MAX] = X_AXIS;
            }
            else if(cur_tag == POS)
            {
                map[Y_MAX - y][x+X_MAX] = POS_CHAR;
            }
            else if(cur_tag == NEG)
            {
                map[Y_MAX - y][x+X_MAX] = NEG_CHAR;
            }
            else
            {
                map[Y_MAX - y][x+X_MAX] = NOTAG_CHAR;
            }
        }
    }
}


/*
 * This method reads the sample vectors from the given samples file and
 * adds their tags to the given separation map (map already complete).
 * @param samples_file - A pointer to the file with the sample vectors.
 * @param map - The given separation map.
 */
void addSampleVectorsToMap(FILE *samples_file,char map[ROWS][COLS])
{
    double cur_sample_vector[MAX_DIMENSION];
    char cur_tag;
    int vector_size;
    int x,y;
    vector_size = getSampleVectorsSize(samples_file);
    //input value to cur_tag and checking for end file:
    while((cur_tag = getSampleVectorFromFile(samples_file,cur_sample_vector,
                                             vector_size))!= END_FILE)
        //if cur_tag gets -2, it means the samples file has ended
    {
        //rounding read points according to ex description.
        x = (int)round(cur_sample_vector[0]); 
        y = (int)round(cur_sample_vector[1]);
        map[Y_MAX - y][x + X_MAX] = cur_tag; 
    }
}

/*
 * This method iterates over all vectors in the given separators file and
 * prints a separation map, complete with the sample vectors for each
 * separator in the file.
 * @param samples_file_name - name of The input file containing the separators.
 * @param separators_file_name - name of the input file containing the samples.
 */
void drawAllMaps(const char *samples_file_name,const char *separators_file_name)
{
    FILE* separators_file = fopen(separators_file_name,"r");
    FILE* samples_file;
    if(isFileOpen(separators_file,separators_file_name))
    {
        char cur_map[ROWS][COLS];
        double cur_separator[MAX_DIMENSION];
        while(readVectorFromFile(separators_file,cur_separator,MAP_DIMENSION))
        {
            createMapArray(cur_map,cur_separator);
            samples_file = fopen(samples_file_name,"r");
            if(!isFileOpen(samples_file,samples_file_name))
            {
                break; //this is used to close separators_file properly
            }
            addSampleVectorsToMap(samples_file,cur_map);
            DrawArray(cur_map);
            printf("\n");
            fclose(samples_file);
        }
        //closing the file only if it was opened
        fclose(separators_file);
    }
}

/*
 * main method for running the program.
 * A basic check for usage is performed here, and drawAllMaps is invoked.
 */
int main(int argc, char* argv[])
{
    if(isValidArgumentsNum(argc,"Usage: SeparationMap <data points input file> <separators input file>\n"))
    {
        drawAllMaps(argv[1],argv[2]);
    }
    return 0;
}
