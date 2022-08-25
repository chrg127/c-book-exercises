/*
 * Write a program to remove trailing blanks and tabs from each
 * line of input, and to delete entirely blank lines.
 */

#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void trim(char line[], int len);

/* print longest input line */
int main(void)
{
    int len;        /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0) {
        trim(line, len);
        if (line[0] != '\0')
            printf("%s\n", line);
    }
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

void trim(char s[], int len)
{
    int i, j;

    j = len - 1;
    while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t' || s[j] == '\r')
        j--;
    s[j+1] = '\0';
}
