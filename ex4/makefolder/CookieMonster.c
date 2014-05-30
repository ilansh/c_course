#include "Cookie.h"
#include "Jar.h"
#include "Milk.h"

int main()
{

    Cookie c;
    Jar j;

    putCookie(j,c);
    if(doWeHaveMilk(3))
    {
        drinkMilk(2.0);
    }

    return 0;

}
