/*
 * Write a private version of scanf analogous to minprintf from
 * the previous section.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#define MAXSTR 100

/* minscanf: minimal scanf with variable argument list */
int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, buf[MAXSTR];
    int *ivalp, matched_items, c, i;

    va_start(ap, fmt);
    matched_items = 0;
    for (p = fmt; *p; p++) {                /* scan format string */
        if (*p == ' ' || *p == '\t')        /* skip space */
            continue;
        if (*p != '%') {
            if (c = getchar(), c == *p) {   /* next character matches */
                matched_items++;
                continue;
            } else
                break;                      /* if doesn't match, stop and return */
        }
        switch(*++p) {
        case 'd':
            i = 0;
            while(isdigit(buf[i++] = c = getchar())) /* collect int */
                ;
            if (!isdigit(buf[0]))
                break;                                  /* not a number */
            buf[i] = '\0';
            ivalp = va_arg(ap, int *);
            *ivalp = atoi(buf);
            matched_items++;
            break;
        }
    }
    va_end(ap); /* clean up */
    return matched_items;
}

int main()
{
    int n, m;
    if (minscanf("%d %d", &n, &m) != 2) {
        printf("input error\n");
        return 1;
    }
    printf("got %d and %d\n", n, m);
}
