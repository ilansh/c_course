#include "Cookie.h"
#include "Jar.h"
#include <stdio.h>

int main()
{
    Jar j;
    Cookie *c = getCookie(j);
    Jar j2;
    if (c != NULL)
    {
        putCookie(j2,*c);
    }
    return 0;
}
