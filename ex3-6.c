/*
 * Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
 */

#include <stdio.h>
#include <string.h>

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

void itoa(int n, char s[], int min_width)
{
    int i = 0, sign, mod;

    /* same as itoa in 3-4 */
    sign = n < 0 ? -1 : 1;
    do {
        if ((mod = n % 10) < 0)
            mod = -mod;
        s[i++] = mod + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';

    while (i < min_width)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

/* tests */
int main(void)
{
    char s[100];
    itoa(10, s, 10);
    printf("%s\n", s);
    return 0;
}
