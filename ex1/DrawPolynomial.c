//##############################################################################
// FILE       : DrawPolynomial.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex1 summer 2011
// DESCRIPTION: This program prints an estimated graph of a polynomial of the
//              form Y(x) = a + b*x + c*x^2 + d*x^3.
//              The inputs of the program are the coefficients a,b,c,d and the
//              output is an estimated graph of the polynomial with these
//              coefficients.
//##############################################################################


#include <stdio.h>
#include <math.h>

#define X_MIN -35

#define X_MAX 35

#define Y_MIN -10

#define Y_MAX 10

#define TOLERANCE 0.5

#define SQUARE(x) (x)*(x)

#define CUBE(x) (x)*(x)*(x)

#define FUNCTION_LINE "*"

#define ORIGIN "+"

#define X_AXIS "-"

#define Y_AXIS "|"

#define EMPTY_SPACE " "


/*
 * Get a single floating point coefficient from the user.
 * @param coefficient_name - The name of the coefficient (a,b,c or d).
 * @return The coefficient value received from the user.
 */
double getCoefficient(char coefficient_name)
{
    double coefficient_value;
    printf("Select %c:\n", coefficient_name);
    scanf("%lf",&coefficient_value);
    return coefficient_value;
}

/*
 * Print the polynomial with the coefficients a,b,c and d in a formated form,
 * with percision of up to 3 digits after the decimal point.
 * @param a,b,c,d - coefficients of the polynomial.
 */
void printPolynomial(double a,double b,double c,double d)
{
    printf("y(x)=(%.3f)+(%.3f)*x+(%.3f)*x^2+(%.3f)*x^3\n",a,b,c,d);
}

/*
 * Draw a graph of the polynomial with the coefficients a,b,c and d,
 * using ascii characters.
 * @param a,b,c,d - The polynomial's coefficients.
 */
void drawGraph(double a, double b, double c, double d)
{
    int x,y;
    //variables for iterating over the the x and y axes
    //starting from the top left corner moving one line at a time working
    //our way to the bottom right corner of our range.
    for(y = Y_MAX; y >= Y_MIN; y--) 
    {
        for(x = X_MIN; x <= X_MAX; x++)
        {
            //
            if(fabs(a+b*x+c*SQUARE(x)+d*CUBE(x) - y) < TOLERANCE)
            {
                printf(FUNCTION_LINE);
            }
            else if(x==0 && y==0)
            {
                printf(ORIGIN);
            }
            else if(x==0)
            {
                printf(Y_AXIS);
            }
            else if(y==0)
            {
                printf(X_AXIS);
            }
            else
            {
                printf(EMPTY_SPACE);
            }
        }
        printf("\n");
    }       
}

/*
 * Main function.
 * Receives the user input and calls functions to performs the required
 * operations.
 */
int main()
{
    //polynomial coefficients a,b,c,d:
    double a,b,c,d;
    printf("y(x)=a+b*x+c*x^2+d*x^3\n");
    a = getCoefficient('a');
    b = getCoefficient('b');
    c = getCoefficient('c');
    d = getCoefficient('d');
    printPolynomial(a,b,c,d);
    drawGraph(a,b,c,d);
    return 0;
}
