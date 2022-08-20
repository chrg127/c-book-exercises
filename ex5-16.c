/*
 * Add the -d ("directory order") option, which makes comparisons
 * only on letters, numbers and blanks. Make sure it works in conjunction
 * with -f.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */

#define NUMERIC     1 << 0
#define REVERSE     1 << 1
#define FOLD        1 << 2
#define DIRECTORY   1 << 3

typedef int (*CompFunc)(const char *, const char *);

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
CompFunc get_comp_func(int flags);

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int flags = 0;

    if (argc > 1) {
        if (strcmp(argv[1], "-n") == 0)
            flags |= NUMERIC;
        else if (strcmp(argv[1], "-r") == 0)
            flags |= REVERSE;
        else if (strcmp(argv[1], "-f") == 0)
            flags |= FOLD;
    }
    if (nlines = readlines(lineptr, MAXLINES), nlines >= 0) {
        quicksort((void **) lineptr, 0, nlines-1,
            (int (*) (void *, void *)) get_comp_func(flags));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000  /* max lenght of any input line */

char *alloc(int n);
int get_line(char s[], int lim);

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

void swap(void *v[], int i, int j);

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right)      /* do nothing if array contains fewer */
        return;             /* than two elements */
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}

/*
 * numcmp: compare s1 and s2 numerically
 * note that this version uses const char instead of char due
 * to strcmp's arguments being const char; having them as char
 * produced a warning on my compiler.
 */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int strcasecmp_reverse(const char *s1, const char *s2)
{
    int r = strcasecmp(s1, s2);
    return r < 0 ? 1 : r > 0 ? -1 : 0;
}

int numcmp_reverse(const char *s1, const char *s2)
{
    int r = numcmp(s1, s2);
    return r < 0 ? 1 : r > 0 ? -1 : 0;
}

int strcmp_reverse(const char *s1, const char *s2)
{
    int r = strcmp(s1, s2);
    return r < 0 ? 1 : r > 0 ? -1 : 0;
}

int isalnumblank(int c)
{
    return isalnum(c) && isspace(c);
}

int dircmp(const char *s1, const char *s2)
{
    for ( ; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
        if (*s1 == *s2)
            continue;
        if (isalnumblank(*s1) && isalnumblank(*s2))
            continue;
        return *s1 < *s2 ? -1 : 1;
    }
    return 0;
}

int dircasecmp(const char *s1, const char *s2)
{
    for ( ; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
        if (toupper(*s1) == toupper(*s2))
            continue;
        if (!isalnumblank(*s1) && !isalnumblank(*s2))
            continue;
        return *s1 < *s2 ? -1 : 1;
    }
    return 0;
}

int dircmp_reverse(const char *s1, const char *s2)
{
    int r = dircmp(s1, s2);
    return r < 0 ? 1 : r > 0 ? -1 : 0;
}

int dircasecmp_reverse(const char *s1, const char *s2)
{
    int r = dircasecmp(s1, s2);
    return r < 0 ? 1 : r > 0 ? -1 : 0;
}

CompFunc get_comp_func(int flags)
{
    return (flags & NUMERIC)                        && (flags & REVERSE) ? numcmp_reverse
         : (flags & NUMERIC)                                             ? numcmp
         : (flags & FOLD)    && (flags & DIRECTORY) && (flags & REVERSE) ? dircasecmp_reverse
         : (flags & FOLD)    && (flags & DIRECTORY)                      ? dircasecmp
         :                      (flags & DIRECTORY) && (flags & REVERSE) ? dircmp_reverse
         :                      (flags & DIRECTORY)                      ? dircmp
         : (flags & FOLD)    && (flags & REVERSE)                        ? strcasecmp_reverse
         : (flags & FOLD)                                                ? strcasecmp
         :                                             (flags & REVERSE) ? strcmp_reverse
         :                                                                 strcmp;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
