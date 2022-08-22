/*
 * Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better
 * version.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab [] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    /*...*/
    "static_cast", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0,
};

#define NKEYS sizeof(keytab) / sizeof(keytab[0])

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int c);

/* count C keywords */
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if (n = binsearch(word, keytab, NKEYS), n >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch: find word in tab[0] ... tab [n - 1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond, low, high, mid;

    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low+high)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* skip space, comments and preprocessor control lines */
int skip_space()
{
    int c, d;
    for (;;) {
        switch (c = getch()) {
        case ' ': case '\t': case '\r':
            break;
        case '/':
            if (d = getch(), d == '*') {
                for ( ; !(c == '*' && d == '/'); ) {
                     c = d;
                     d = getch();
                }
            } else {
                ungetch(d);
                return c;
            }
            break;
        case '\n':
            if (d = getch(), d == '#') {
                while (c = getch(), c != '\n')
                    ;
            }
            break;
        default:
            return c;
        }
    }
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    c = skip_space();
    if (c != EOF)
        *w++ = c;
    if (c == '"') {
        while (*w++ = c = getch(), c != '"' && c != '\n')
            ;
        return word[0];
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (*w = getch(), !isalnum(*w) && *w != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
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
