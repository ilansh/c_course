//##############################################################################
// FILE       : IOHelper.h
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex2 summer 2011
// DESCRIPTION: This header file defines an interface with some common file
//              handling operations for the files SeparatorMap.c and
//              Perceptron.c.
//##############################################################################

#ifndef IOHEPLER_H
#define IOHELPER_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0
//not to be confused with EOF - used when getting a sample vector from a
//samples file, since EOF == NOTAG, I used END_FILE to avoid complication.
#define END_FILE -2 
#define END_LINE_REG '\n'
#define END_LINE_EXTRA '\r'


/*
 * Checks if the number of arguments received from the command line is valid -
 * 2 arguments. prints an error message if not.
 * @param argc - number of arguments receives.
 * @param error_msg - the error string to print.
 * @return 1 if the number is valid, 0 otherwise.
 */
int isValidArgumentsNum(const int argc,const char *error_msg);

/*
 * Checks if the given file is open for work (reading or writing).
 * Prints an error message if not.
 * @param file - a pointer to the desired file.
 * @param file_name - the file name string.
 * @return 1 if the file is open, 0 otherwise.
 */
int isFileOpen(const FILE* file,const char* file_name);

/*
 * This method reads a vector from a file written in a given format -
 * each line in the file contains a single vector separated by commas and no
 * spaces, i.e 1,2,3,4 - and notifies if the end of file was reached.
 * @param input_file - The input file to read from.
 * @param vector - An array of doubles to hold the read vector.
 * @param vector_size The number of entries the vector contains.
 * @return 0 if the end of file was reached, 0 otherwise.
 */
int readVectorFromFile(FILE* input_file,double* vector,const int vector_size);

/*
 * A method for reading an extra character at the end of a line if needed,
 * since some operating systems have '\r\n' characters for line break,
 * and some have just \n.
 * @param input_file - The file to read from.
 * @param last_char_read - The end line char which was already read.
 */
void readExtraEndLineChar(FILE* input_file,char last_char_read);

/*
 * This method reads the first line of a given file expecting a single integer
 * and a line break. The read integer indicates the dimension of the vectors
 * written in the given file.
 * @param samples_file - the file to read from.
 * @return The integer read.
 */
int getSampleVectorsSize(FILE* samples_file);

/*
 * This method is used for reading a single vector from a given file with the
 * formating X:1,2,3,4 where X is a single letter representing a tag (P or N)
 * and the rest of the vector is the same as in the method readVectorFromFile,
 * which is called from this method after reading the prefix "X:".
 * @param input_file - The input file to read from.
 * @param vector - An array of doubles to hold the read vector.
 * @param vector_size - The number of entries the vector contains.
 * @return - (-2) if the end of file was reached, or a character representing
 * The read tag (either 'P' or 'N').
 */
char getSampleVectorFromFile(FILE* samples_file, double *sample_vector,
                             const int vector_size);

#endif
