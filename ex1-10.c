/*
 * Write a program to copy its output, replacing each
 * tab by \t, each backspace by \b, and each backslash by \\. This makes tab
 * and backspaces visible in an unambigous way.
 */

#include <stdio.h>

int main(void)
{
    int c;

    while (c = getchar(), c != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            printf("%c", c);
    }
    return 0;
}
