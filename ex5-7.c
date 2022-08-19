/*
 * Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define BUFSIZE 10000       /* buffer size for lines */

int get_line(char line[], int maxline);
int readlines(char *lineptr[], int nlines);
int readlines2(char *lineptr[], int maxlines, char *buf);
void writelines(char *lineptr[], int nlines);
void quicksort(char *v[], int left, int right);
char *alloc(int n);
void afree(char *p);

char *lineptr[MAXLINES];    /* pointers to text lines */
char linebuffer[BUFSIZE];

/* sort input lines */
int main()
{
    int nlines;     /* number of input lines read */

    if (nlines = readlines2(lineptr, MAXLINES, linebuffer), nlines >= 0) {
        quicksort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000  /* max lenght of any input line */

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

/* readlines2: read input lines using a temporary buffer */
int readlines2(char *lineptr[], int maxlines, char *buf)
{
    int len, nlines;
    char *p, line[MAXLEN];
    char *bufp;

    nlines = 0;
    for (bufp = buf; len = get_line(bufp, MAXLEN), len > 0; bufp += len) {
        if (nlines >= maxlines)
            return -1;
        bufp[len-1] = '\0'; /* delete newline */
        lineptr[nlines++] = bufp;
        bufp += len;
        if (bufp - buf > BUFSIZE)
            return -1;
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", *lineptr++);
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

#define ALLOCSIZE 10000 /* size of avaiable space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n;  /* old p */
    } else      /* not enough room */
        return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

void swap(char *v[], int i, int j);

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)      /* do nothing if array contains fewer */
        return;             /* than two elements */
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1);
    quicksort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
