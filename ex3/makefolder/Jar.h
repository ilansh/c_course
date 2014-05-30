#ifndef JAR_H
#define JAR_H
#include "Cookie.h"

typedef struct jar
{
    Cookie *cookies;
    int c;
} Jar;


void putCookie(Jar j, Cookie c);
Cookie* getCookie(Jar j);

#endif
