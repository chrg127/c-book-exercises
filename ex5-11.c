/*
 * Modify the programs entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void detab(int argc, char *argv[])
{
    int c, i, n;

    if (argc < 2)
        n = 4;
    else if (argc == 2)
        n = atoi(argv[1]);
    else {
        printf("usage: %s [n]\n", *argv);
        return 0;
    }

    while (c = getchar(), c != EOF) {
        if (c != '\t')
            putchar(c);
        else
            for (i = 0; i < n; ++i)
                putchar(' ');
    }
}

#define MAXSTR 100

void move_left(char str[], int len);

void entab(int argc, char **argv)
{
    int c, i, n, cread;
    char buf[MAXSTR];

    if (argc < 2)
        n = 4;
    else if (argc == 2)
        n = atoi(argv[1]);
    else {
        printf("usage: %s [n]\n", *argv);
        return 0;
    }

    /*
     * buf is a sliding array of the characters we have read.
     * we put a terminator to be able to compare it.
     */
    buf[n] = '\0';
    cread = 0;
    while (c = getchar(), c != EOF) {
        ++cread;
        move_left(buf, n-1);
        buf[n-1] = c;
        /* don't do anything if str isn't filled yet */
        if (cread < 4)
            continue;
        /*
         * check if buf is currently 4 spaces.
         * if it is, put a tab and reset cread.
         */
        if (strcmp(buf, "    ") == 0) {
            putchar('\t');
            cread = 0;
        } else
            putchar(buf[0]);
    }

    /* write rest of string */
    if (c == EOF)
        for (i = 1; i < n; i++)
            putchar(buf[i]);
}

/* move_left: moves elements in a char array to the left */
void move_left(char str[], int len)
{
    int i;

    for (i = 0; i < len; i++)
        str[i] = str[i+1];
}

int main(int argc, char *argv[])
{
    /* to test, uncomment one of the following lines: */
    // detab(argc, argv);
    // enab(argc, argv);
    return 0;
}
