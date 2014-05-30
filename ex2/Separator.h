#ifndef SEPARATOR_H
#define SEPARATOR_H

#define MAX_LINE_SIZE 200
#define MAX_DIMENSION ((MAX_LINE_SIZE-2) / 2 + 1)


typedef enum {NEG = -1, POS = 1, NOTAG = 0} Tag;

/*
 * Tag a new data point x (first argument - a vector of real values in
 * dimension MAX_DIMENSION,
 * according to the hypothesis separator vector w (second argument). 
 * d (third argument) - the actual relevant dimension of the data.
 */
Tag tagNewDataPoint(const double x[MAX_DIMENSION],
                    const double w[MAX_DIMENSION],
                    const int d);

#endif
