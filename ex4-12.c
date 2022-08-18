/*
 * Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 */

#include <stdio.h>

int itoa_step(int i, int n, char s[])
{
    if (n / 10)
        i = itoa_step(i, n / 10, s);
    s[i] = n % 10 + '0';
    s[i+1] = '\0';
    return i+1;
}

void itoa(int n, char s[])
{
    int i;

    i = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }
    itoa_step(i, n, s);
}

int main(void)
{
    char s[100];
    itoa( 12345, s); printf("%s\n", s);
    itoa(-12345, s); printf("%s\n", s);
    return 0;
}
