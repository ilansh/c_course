#include <stdio.h>
#include <stdlib.h>
#include "MyNR.h"

double a[7];
double b[6];

void doTest(double,double,double,double,double,double,double);
double pow1(double x, int n);
double calcPolynome(double x, double* args, int n);
void printPolynome(double* args, int n);
double f(double x);
double g(double x);



int main(void) {

	/* The function doTest(x0,a,b,c,d,e,f) tests the polynome
	 * y(x) = a + bx + cx^2 + dx^3 + ex^4 + fx^5
	 * 
	 * notice that it may not always have a point y=0, so so myNR 
	 * isn't guarenteed to always return a valid point
	 */

	doTest(10, -3,7,0,0,0,0);
	doTest(10, 0,5,2,0,0,0);
	doTest(10, -20,8,7,1,1,0);
	
	doTest(0, -20,8,7,1,1,0);
	doTest(0, -200,8,70,4,1,0);
	doTest(0, 20,-8,5,1,7,0);
	
	
	
	
	
	return EXIT_SUCCESS;
}


void doTest(double x,
		double a0, double a1, double a2,
		double a3, double a4, double a5){
	a[0]=a0;a[1]=a1;a[2]=a2;
	a[3]=a3;a[4]=a4;a[5]=a5;

	int i;
	for(i=1;i<6;i++){
			b[i-1] = a[i]*i;
	}

	double x0 = myNR(&f,&g,x);

	printf("f(x)=");
	printPolynome(a,6);
	printf("g(x)=");
	printPolynome(b,5);
	printf("start value: %.2lf\n",x);
	printf("return value: %.2lf\n",x0);
	printf("f(%.2lf)=%lf\n\n",x0,f(x0));
}

double calcPolynome(double x, double* args, int n){
	double result = 0;
	int i;
	for(i=0;i<n;i++){
		result += args[i]*pow1(x,i);
	}
	return result;
}

double pow1(double x, int n){
	double result = 1;
	int i;
	for(i=0;i<n;i++){
		result *= x;
	}
	return result;
}

void printPolynome(double* args, int n){
	if(args[0] != 0.00) printf("%.2lf",args[0]);
	int i;
	for(i=1;i<n;i++){
		if(args[i] != 0.00) printf(" + %.2lf*x^%d",args[i],i);
	}
	printf("\n");
}

double f(double x){
	return calcPolynome(x,a,6);
}

double g(double x){
	return calcPolynome(x,b,5);
}
