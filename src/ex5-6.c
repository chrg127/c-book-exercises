/*
 * Rewrite appropriate programs from earlier chapters and exercises
 * with pointers instead of arrays indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4),
 * reverse (Chapter 3), and strindex and getop (CHapter 4)
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

int get_line(char *s, int lim)
{
    int c;
    char *start;

    for (start = s; (s - start) < lim-1 && (c = getchar()) != EOF && c != '\n'; s++)
        *s = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}

void reverse(char s[]);

/* atoi: convert s to integer */
int atoi(char *s)
{
    int n, sign;

    for ( ; isspace(*s); s++) /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s + '0');
    return sign * n;
}

/* itoa: convert n to characters in s
 * this version also handles INT_MIN */
void itoa(int n, char *s)
{
    int sign, d;
    char *start;

    sign = n < 0 ? -1 : 1;      /* record sign */
    start = s;
    do {                        /* generate digits in reverse order */
        if ((d = n % 10) < 0)   /* get next digit */
            d = -d;             /* convert to positive if necessary */
        *s++ = d + '0';
    } while ((n /= 10) != 0);   /* delete it */
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(start);
}

/* reverse: reverse string s in place */
void reverse(char *s)
{
    int c;
    char *t;

    for (t = s + strlen(s)-1; s < t; s++, t--) {
        c  = *s;
        *s = *t;
        *t = c;
    }
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    char *s2, *t2, *s_start;

    for (s_start = s; *s != '\0'; s++) {
        for (s2 = s, t2 = t; *t2 != '\0' && *s2 == *t2; s2++, t2++)
            ;
        if (t2 > t && *t2 == '\0')
            return s - s_start;
    }
    return -1;
}

#define NUMBER '0'  /* signal that a number was found */

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char *s)
{
    int i, c;

    while (*s = c = getch(), c == ' ' || c == '\t')
        ;
    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    i = 0;
    if (isdigit(c)) /* collect integer part */
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')   /* collect fraction part */
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
