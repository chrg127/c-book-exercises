/*
 * Write a program entab that replaces strings of blanks by the
 * minimum numbers of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for detab. When either a tab or a single blank would suffice
 * to reach a tab stop, which should be given preference?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 100
#define TABSTOP 4

void move_left(char str[], size_t len);
int string_compare(char s[], char t[]);

int main(int argc, char **argv)
{
    int c, i, cread;
    char buf[MAXSTR];

    /*
     * buf is a sliding array of the characters we have read.
     * we put a terminator to be able to compare it.
     */
    buf[TABSTOP] = '\0';
    cread = 0;
    while (c = getchar(), c != EOF) {
        ++cread;
        move_left(buf, TABSTOP-1);
        buf[TABSTOP-1] = c;
        /* don't do anything if str isn't filled yet */
        if (cread < 4)
            continue;
        /*
         * check if buf is currently 4 spaces.
         * if it is, put a tab and reset cread.
         */
        if (string_compare(buf, "    ") == 0) {
            putchar('\t');
            cread = 0;
        } else
            putchar(buf[0]);
    }

    /* write rest of string */
    if (c == EOF)
        for (i = 1; i < TABSTOP; i++)
            putchar(buf[i]);

    return 0;
}

/* move_left: moves elements in a char array to the left */
void move_left(char str[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        str[i] = str[i+1];
    }
}

int string_compare(char s[], char t[])
{
    int i;
    for (i = 0; s[i] != '\0' && t[i] != '\0'; i++)
        if (s[i] != t[i])
            return 1;
    return 0;
}
