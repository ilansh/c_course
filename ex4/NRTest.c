


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "MyNR.h"
#define RANGE 0.01
#define LOOPS 100
#define RAND_RANGE 1000


double f0(double x) {
	return 3*x*x - 200;
}
double g0(double x) {
	return 6*x;
}
double f1(double x) {
	return 3*x*x*x - 200;
}
double g1(double x) {
	return 6*x*x;
}
double f2(double x) {
	return x*x*x*x - 32*x*x*x -1.2345*x*x +3.0054*x +23.112;
}
double g2(double x) {
	return 4*x*x*x - 96*x*x - 2.469*x + 3.0054;
}
double f3(double x) {
	return sin(x);
}
double g3(double x) {
	return cos(x);
}



int TestImplementationOfNR (realFunction f, realFunction g, double x0, int funcNum)
{
	double stud_final_x = myNR(f, g, x0);

	// See if the resulted x point is really a point where the function f gets zero:
	if (fabs(f(stud_final_x)) < RANGE) {
//		printf("function: f%d  Good test \n", funcNum);
		return 0; // OK
	}

	printf("XXX Failed test XXX\n");

	printf("function: f%d x0: %g final x: %g  final f(x): %g  \n",funcNum, x0, stud_final_x, f(stud_final_x) );


	return 1; // failure
}




int main ()
{
	realFunction* f[] = {f0,f1,f2,f3};
	realFunction* g[] = {g0,g1,g2,g3};
	int i,j,status = 0;
	for(i = 0 ; i < sizeof(f) / sizeof(f[0]) ; i++)
	{
		for(j = 0 ; j < LOOPS ; j++)
		{
			int ran = (rand() % RAND_RANGE) - RAND_RANGE /  2;
			if (g[i](ran) == 0) continue;
			status += TestImplementationOfNR((f[i]), (g[i]), ran,  i);
		}
		if(status == 0)
		{
			printf("function: f%d  Good test \n", i);
		}
	}


	return 0;

}
