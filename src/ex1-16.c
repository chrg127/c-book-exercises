/*
 * Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much as possible
 * of the text.
 */

/*
 * it appears it is not possible to do this exercise without using malloc() (not introduced
 * in the first chapter), or else I'm completely misunderstanding the exercise. either way,
 * the program here is simply the unmodified 'print longest line' program.
 */

#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

/*
 * getline shall henceforth be written as get_line to avoid conflicts with getline on
 * platforms that define it
 */
int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main(void)
{
    int len;        /* current line length */
    int max;        /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while (len = get_line(line, MAXLINE), len > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)    /* there was a line */
        printf("%s\n", longest);
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
