/*
 * Write to function itob(n, s, b) that converts the integer n
 * int a base b character representation in the string s. In particular,
 * itob(n, s, 16) formats n as a hexadecimal integer in s.
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

/* itob: convert n into its equivalent in base b. */
char * itob(int n, char s[], int b)
{
    static char lookup[100] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    int i, sign, mod;

    if (b < 2 || b > 16)
        return 0;

    /* same as itoa, except we divide by b instead of 10
     * and we use the lookup above for writing digits */
    sign = n < 0 ? -1 : 1;
    i = 0;
    do {
        if ((mod = n % b) < 0)
            mod = -mod;
        s[i++] = lookup[mod];
    } while ((n /= b) != 0);

    /* formatting if b = 2, 8 or 16 */
    if (b == 2 || b == 8 || b == 16) {
        switch (b) {
        case 2:
            s[i++] = 'b';
            break;
        case 8:
            s[i++] = 'o';
            break;
        case 16:
            s[i++] = 'x';
            break;
        }
        s[i++] = '0';
    }
    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
    return s;
}

/* tests */
int main(void)
{
    char s[100];

    itob(0xff, s, 16); printf("%s\n", s);
    itob(0xcc, s, 2);  printf("%s\n", s);

    return 0;
}
