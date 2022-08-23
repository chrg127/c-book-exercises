/*
 * Write a program that converts upper case to lower or lower case
 * to upper, depending on the name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void copy(int (*f)(int))
{
    int c;

    while (c = getchar(), c != EOF)
        putchar(f(c));
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[0], "toupper") == 0)
        copy(toupper);
    else
        copy(tolower);
    return 0;
}
