//##############################################################################
// FILE       : Perceptron.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex2 summer 2011
// DESCRIPTION: This file contains a program for calculating a separator using
//              the perceptron algorithm.
//              The input for this program is a file conatining vectors with
//              known tags, the program performs the perceptron algorithm on
//              those vectors and outputs the stages of operation into a file,
//              each stage representing the current optimal separator
//              calculated.
//##############################################################################

#include "IOHelper.h"
#include <stdio.h>
#include "Separator.h"

//ascii difference between P to 1 and N to -1 (tags).
#define TAG_ASCII_DIFFERENCE 79 

/*
 * Initialize the separator according to the perceptron algorithm, to contain
 * 1 in all its entries.
 * @param separator - The separator vector.
 * @param size - The size of the vector.
 */
void initSeparator(double *separator,const int vector_size)
{
    int i;
    for(i=0; i<vector_size; i++)
    {
        separator[i] = 1;
    }
}

/*
 * Update a given separator according to the perceptron algorithm.
 * @param separator - The separator vector to update.
 * @param sample - The sample vector used for the update process.
 * @param tag - The tag of the sample vector.
 * @param vector_size - The size of the vectors.
 */
void updateSeparator(double *separator,const double *sample,const Tag tag,
                     const int vector_size)
{
    int i;
    for(i=0; i<vector_size; i++)
    {
        separator[i]+= (tag*sample[i]);
    }
}

/*
 * Output a given separator to a given file.
 * The separator entries are written in a new line with commas separating them,
 * no spaces.
 * @param output_file - The file to write to.
 * @separator - the given separator vector.
 * @vector size - the size of the given vector.
 */
void writeSeparatorToFile(FILE* output_file, const double *separator,
                          const int vector_size)
{
    int i;
    for(i=0; i<vector_size-1; i++)
    {
        fprintf(output_file,"%lf,",separator[i]);
    }
    fprintf(output_file,"%lf\n",separator[vector_size-1]);
}

/*
 * This method iterates over the sample vectors in a given file and
 * performs the required operations according the the perceptron algorithm,
 * writing the result into an output file.
 * @param input_file - The file containing the sample vectors.
 * @param output_file - The file to write the results into.
 */
void perceptron(FILE* input_file, FILE* output_file)
{
    int vector_size = getSampleVectorsSize(input_file);
    double cur_separator[MAX_DIMENSION];
    double cur_sample[MAX_DIMENSION];
    char cur_sample_tag;
    char cur_calc_tag;
    initSeparator(cur_separator,vector_size);
    writeSeparatorToFile(output_file,cur_separator,vector_size);//initial write
    while((cur_sample_tag = getSampleVectorFromFile(input_file,
          cur_sample,vector_size))!= END_FILE)
        //if cur_sample_tag gets -2, it means the samples file had ended
    {
        //casting to the matching ascii code to get P/N
        cur_calc_tag = tagNewDataPoint(cur_sample,cur_separator,vector_size)
            + TAG_ASCII_DIFFERENCE; 
        if(cur_calc_tag != cur_sample_tag)
        {
            //casting tag back to -1/1
            updateSeparator(cur_separator,cur_sample,
                            cur_sample_tag - TAG_ASCII_DIFFERENCE,vector_size);
        }
        writeSeparatorToFile(output_file,cur_separator,vector_size);
    }

}

/*
 * Main method.
 * This method is responsible for opening the input and output files and
 * closing them at the end (or if an error occured).
 */
int main(int argc, char *argv[])
{
    if(isValidArgumentsNum(argc,"Usage: Perceptron <input file> <output file>\n"))
    {
        //making sure files opened properly, and closing only opened files.
        FILE* input_file = fopen(argv[1],"r");
        if(isFileOpen(input_file,argv[1]))
        {
            FILE* output_file = fopen(argv[2],"w");
            if(isFileOpen(output_file,argv[2]))
            {
                perceptron(input_file,output_file);
                fclose(output_file);
            }
            fclose(input_file);
        }
    }
    return 0;
}
