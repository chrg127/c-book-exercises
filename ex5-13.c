/*
 * Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 *
 *      tail -n
 *
 * prints the last n lines. The program should behave rationally nop matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting program
 * of Section 5.6, not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DEFAULT 10          /* default n */
#define MAXSTR 100
#define MAXLINES 5000       /* max # lines to be sorted */

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int n);
void afree(char *p);

static char *linestorage[MAXLINES];    /* pointers to text lines */

int main(int argc, char **argv)
{
    int n, i, nlines;
    char s[MAXSTR];

    /* parse argument */
    n = DEFAULT;
    i = 1;
    if (argc < 2)
        n = DEFAULT;
    else if (argc == 2)
        n = atoi(argv[1]);
    else {
        printf("usage: %s [n]\n", *argv);
        return 0;
    }

    if (nlines = readlines(linestorage, MAXLINES), nlines >= 0) {
        n = MIN(nlines, n);
        writelines(linestorage + nlines - n, n);
    } else {
        printf("error: Input too big\n");
        return 1;
    }

    return 0;
}

#define MAXLEN 1000  /* max lenght of any input line */

/* getline: read a line from input and return its lenght */
int get_line(char *s, int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

#define ALLOCSIZE 10000 /* size of avaiable space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough room */
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
