/*
 * In a two's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n equal
 * to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* itoa: convert n to characters in s
 * this is the version in the book. */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do {                        /* generate digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* itoa2: convert n to characters in s, and handle INT_MIN */
void itoa2(int n, char s[])
{
    int i, sign, d;

    sign = n < 0 ? -1 : 1;      /* record sign */
    i = 0;
    do {                        /* generate digits in reverse order */
        if ((d = n % 10) < 0)   /* get next digit */
            d = -d;             /* convert to positive if necessary */
        s[i++] = d + '0';
    } while ((n /= 10) != 0);   /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/* tests */
int main(void)
{
    char s[100];
    itoa (INT_MIN, s); printf("%s\n", s);
    itoa2(INT_MIN, s); printf("%s\n", s);
    return 0;
}
