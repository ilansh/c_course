#include <stdio.h>
#include <stdlib.h>
#include <Separator.h>
#include <time.h>

double w[MAX_DIMENSION];
double x[MAX_DIMENSION];

#define TWO_D 2
#define POSITIVE_X 1
#define POSITIVE_Y 2
#define POSITIVE_BOTH 3
#define VECTORS_TO_TEST 10
#define TWO_DIGIT_PERCISION 100

void initializeSeparator (const int choice);
void printCalculations (const double separator[MAX_DIMENSION]);
void expectNoTag ();

int main (int argc, char** argv)
{
    int choice;
    printf ("Choose option for Separator:\n(1) Y axis\n(2) X axis\n(3) Y = - X\n");
    scanf ("%d", &choice);
    initializeSeparator (choice);
    printCalculations (w);
    printf ("\nThese should return NOTAG:\n");
    expectNoTag ();
    return (EXIT_SUCCESS);
}

void initializeSeparator (const int choice)
{
    switch (choice)
    {
        case POSITIVE_X:
            w[0] = 1.0;
            w[1] = 0.0;
            break;
        case POSITIVE_Y:
            w[0] = 0.0;
            w[1] = 1.0;
            break;
        case POSITIVE_BOTH:
            w[0] = 1.0;
            w[1] = 1.0;
            break;
        default:
            printf ("Invalid option");
            exit (1);
    }
}

void printCalculations (const double separator[MAX_DIMENSION])
{
    srand (time (NULL));
    int i, j;
    Tag result;
    double temp;
    for (i = 0; i < VECTORS_TO_TEST; i++)
    {
        for (j = 0; j < TWO_D; j++)
        {
            temp = (rand () % (VECTORS_TO_TEST * 2)) + ((rand () % TWO_DIGIT_PERCISION) / (double) TWO_DIGIT_PERCISION);
            if (rand () % 2)
            {
                temp *= (-1);
            }
            x[j] = temp;
        }
        result = tagNewDataPoint (x, w, TWO_D);
        printf ("Tag of (%.2lf,%.2lf) is: %d\n", x[0], x[1], result);
    }
}

void expectNoTag ()
{
    w[0] = 1;
    w[1] = 1;
    srand (time (NULL));
    int i;
    Tag result;
    double temp;
    for (i = 0; i < VECTORS_TO_TEST; i++)
    {
        temp = (rand () % (VECTORS_TO_TEST * 2)) + ((rand () % TWO_DIGIT_PERCISION) / (double) TWO_DIGIT_PERCISION);
        if (rand () % 2)
        {
            temp *= (-1);
        }
        x[0] = temp;
        x[1] = -temp;
        result = tagNewDataPoint (x, w, TWO_D);
        printf ("Tag of (%.2lf,%.2lf) is: %d\n", x[0], x[1], result);
    }
}
