/*
 * Write a program to "fold" long input lines into two or more shorter
 * lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */

#include <stdio.h>

#define COLUMN 80
#define MAXSTR 1000

int get_line(char line[], int maxline);
int get_last_nonblank(char s[], int n);
void move_left(char str[], int len, int n);
void copy(char to[], char from[], int len);

int main(int argc, char **argv)
{
    int len, index;
    char line[MAXSTR], tmp[MAXSTR];

    while (len = get_line(line, MAXSTR), len > 0) {
        /* check if the line is long enough */
        while (len > COLUMN) {
            /* find index of last non-blank character before column */
            if (index = get_last_nonblank(line, COLUMN), index != -1) {
                copy(tmp, line, index);
                tmp[index] = '\n';
                tmp[index+1] = '\0';
                printf("%s", tmp);
                move_left(line, MAXSTR - COLUMN - 1, COLUMN);
                len -= index;
            } else
                break;
        }
        printf("%s", line);
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
 * get_last_nonblank: finds the last non-blank character before the column n.
 * assumes the string is longer than n characters.
 * returns the index if it finds a blank, returns -1 otherwise.
 */
int get_last_nonblank(char s[], int n)
{
    for (; n >= 0; n--)
        if (s[n] == ' ' || s[n] == '\t')
            return n;
    return -1;
}

/* move_left: moves elements in a char array to the left for n times. */
void move_left(char str[], int len, int n)
{
    int i;
    for (i = 0; i < len; i++)
        str[i] = str[i+n];
}

/* copy: copy 'from' into 'to' for len elements; assume to is big enough */
void copy(char to[], char from[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        to[i] = from[i];
}
