/* Write a program to count blanks, tabs and newlines. */

#include <stdio.h>

int main(void)
{
    int c, n;

    n = 0;
    while (c = getchar(), c != EOF)
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
            n++;
    printf("%d\n", n);
    return 0;
}
