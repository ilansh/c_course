//##############################################################################
// FILE       : CaseChange.c
// WRITER     : Ilan Shamir, login=ilansh, id=302514401
// EXERCISE   : slabc ex1 summer 2011
// DESCRIPTION: This program gets a character as it's input and prints a
//              result according to the following rules:
//              An upper case letter will be converted to lower case
//              A lower case letter will be converted to upper case
//              A number will be squared
//              Any other character remains the same.
//              The format of the result will be:
//              "Original Character->New Character"
//##############################################################################


#include <stdio.h>

#define LOWER_UPPER_DIFFERENCE 32

#define NUMBER_VALUE_DIFFERENCE 48

#define LOWER_A_ASCII 97

#define LOWER_Z_ASCII 123

#define UPPER_A_ASCII 64

#define UPPER_Z_ASCII 91

#define ZERO_ASCII 48

#define NINE_ASCII 57



/*
 * main function of the program.
 * performs the required operations according to the user's input.
 */
int main()
{
    char user_char;
    user_char = getchar();
    printf("%c->",user_char);
    //The following conditions determine the type of character
    //according to it's ascii value, and performs the matching operation.
    if(user_char >= LOWER_A_ASCII && user_char <= LOWER_Z_ASCII)
    {
        printf("%c",user_char - LOWER_UPPER_DIFFERENCE);
    }
    else if(user_char >= UPPER_A_ASCII && user_char <= UPPER_Z_ASCII)
    {
        printf("%c",user_char + LOWER_UPPER_DIFFERENCE);
    }
    else if(user_char >= ZERO_ASCII && user_char <= NINE_ASCII)
    {
        printf("%d",(user_char - NUMBER_VALUE_DIFFERENCE) *
               (user_char - NUMBER_VALUE_DIFFERENCE));
    }
    else
    {
        printf("%c",user_char);
    }
    printf("\n");
    return 1;
}
