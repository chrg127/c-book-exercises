/*
 * Write a program to print all input lines that are longer than 80
 * characters.
 */

#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);

/* print longest input line */
int main(void)
{
    int len;        /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > 80)
            printf("%s\n", line);
    return 0;
}

/* get_line: read a line from input and return its lenght */
int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
