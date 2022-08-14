/*
 * Write a function reverse(s) that reverses the character
 * string s. Use it to write a program that reverses its input a line at a time.
 *
 */

#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int get_line(char line[], int maxline);
void reverse(char s[], int len);

/* print longest input line */
int main(void)
{
    int len;        /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line, len);
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

/*
 * reverse: reverse the characters of a string
 * example: string -> gnirts
 */
void reverse(char s[], int len)
{
    int i, j;

    j = len - 1;
    while (s[j] == '\n')
        j--;
    s[j+1] = '\0';
    for (i = 0; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}
