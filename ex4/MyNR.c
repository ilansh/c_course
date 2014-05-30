//##############################################################################
// FILE       : MyNR.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex4 summer 2011
// DESCRIPTION: MyNR.c is a file implementing MyNR.h.
//				It implements the method myNR which performs the
//				Newton-Raphson process.
//##############################################################################

#include "MyNR.h"


/*
 * Method performing the Newton Raphson algorithm, using the given arguments -
 * finding a zero point of a function using its derivative.
 * @param func - func(x) the function.
 * @param der - func'(x) the derivative.
 * @param start - Starting point for the process.
 * @return - The x point where func(x) = 0 (such a point doesn't necessarily
 * exist - in this case the x value of the last iteration will be returned).
 */
static double myNR(realFunction func, realFunction der, double start)
{
	double last_point;
	double cur_point = start;
	int iteration = MAX_ITERATIONS;
	do
	{
		last_point = cur_point;
		cur_point = last_point - (func(last_point) / der(last_point));
	}while(fabs(cur_point - last_point) > TOLERANCE && --iteration);
	return cur_point;
}
