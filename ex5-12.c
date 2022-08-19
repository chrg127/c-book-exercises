/*
 * Extend entab and detab to accept the shorthand
 *
 *      entab -m +n
 *
 * to mean tab stops every n columns, starting at column m. Choose convenient
 * (for the user) default behavior.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABSTOP 4

void parse_args(int *n, int *m, int argc, char *argv[])
{
    char *arg;

    *m = 0;
    *n = 0;
    while (++argv, --argc > 0) {
        arg = *argv;
        /* a valid argument is always length > 2 */
        if (arg[0] == '\0' || arg[1] == '\0')
            printf("error: invalid argument: %s\n", arg);
        switch (arg[0]) {
        case '+':
            *m = atoi(arg+1);
            break;
        case '-':
            *n = atoi(arg+1);
            break;
        default:
            printf("error: invalid argument: %s\n", arg);
            break;
        }
    }

}

void detab(int argc, char *argv[])
{
    int c, i, m, n, row, col;
    char *arg;

    parse_args(&n, &m, argc, argv);
    row = col = 0;
    while (c = getchar(), c != EOF) {
        col++;
        if (c == '\n') {
            col = 0;
            row++;
        } else if (c == '\t')
            for (i = 0; i < TABSTOP; ++i)
                putchar(' ');
        else if (col - m > 0 && col - m % n == 0)
            putchar('\t');
        putchar(c);
    }
}

#define MAXSTR 100

void move_left(char str[], int len);

void entab(int argc, char **argv)
{
    int c, i, n, m, cread, col, row;
    char buf[MAXSTR];

    parse_args(&n, &m, argc, argv);

    /*
     * buf is a sliding array of the characters we have read.
     * we put a terminator to be able to compare it.
     */
    buf[TABSTOP] = '\0';
    cread = col = row = 0;
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
        if (strcmp(buf, "    ") == 0) {
            putchar('\t');
            cread = 0;
            continue;
        }
        col++;
        if (buf[0] == '\n') {
            col = 0;
            row++;
        }
        if (col - m > 0 && col - m % n == 0)
            putchar('\t');
        putchar(buf[0]);
    }

    /* write rest of string */
    if (c == EOF) {
        for (i = 1; i < TABSTOP; i++) {
            col++;
            if (buf[0] == '\n') {
                col = 0;
                row++;
            }
            if (col - m > 0 && col - m % n == 0)
                putchar('\t');
            putchar(buf[i]);
        }
    }
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
