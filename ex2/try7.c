#include <string.h>
#include <stdio.h>


void func(char *str)
{
    printf("%ld",strlen(str)-1);
    str[strlen(str)-1] = '\0';
}

int main()
{
    char str[5]= {'b','l','a','t','\0'};
    //printf("%c",str[3]);
    //printf("%c",str[4]);
    func(str);
    printf("%s",str);
    return 0;
}
