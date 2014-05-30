//##############################################################################
// FILE       : MyNR.h
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex4 summer 2011
// DESCRIPTION: MyNR.h is a header file for defining the method performing the
//				Newton Raphson algorithm.
//##############################################################################

#include <stdio.h>
#include <math.h>

#define TOLERANCE 0.0001
#define MAX_ITERATIONS 1500

typedef double (*realFunction)(double);

/*
 * Method performing the Newton Raphson algorithm, using the given arguments -
 * finding a zero point of a function using its derivative.
 * @param func - func(x) the function.
 * @param der - func'(x) the derivative.
 * @param start - Starting point for the process.
 * @return - The x point where func(x) = 0 (such a point doesn't necessarily
 * exist - in this case the x value of the last iteration will be returned).
 */
double myNR(realFunction func, realFunction der, double start);
