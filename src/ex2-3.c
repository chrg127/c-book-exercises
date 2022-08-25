/*
 * Write the function htoi(s), which converts a string of hexadecimal
 * digits (including an optional 0x or 0X) into its equivalent integer value.
 * The allowable digits are 0 through 9, a through f, and A through F.
 */

#include <stdio.h>
#include <ctype.h>

int htoi(char str[]);
int xtoi(char c);

/* htoi: convert str string to an int */
int htoi(char str[])
{
    int i, n;

    i = 0;
    /* skip all leading spaces */
    for ( ; str[i] == ' '; ++i)
        ;
    /* skip '0x' part */
    if (str[i+1] != '\0' && str[i] == '0' && toupper(str[i+1]) == 'X')
        i += 2;
    /* convert until it finds valid characters */
    n = 0;
    for ( ; isxdigit(str[i]); ++i)
        n = 16 * n + (xtoi(toupper(str[i])));
    return n;
}

/* xtoi: convert a single hex character to int. assumes the character is an hex digit. */
int xtoi(char c)
{
    if (isdigit(c))
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a';
    if (c >= 'A' && c <= 'F')
        return c - 'A';
    return 0;
}

/* tests */
int main(void)
{
    printf("%d\n", htoi("123"));
    printf("%d\n", htoi("0xABC"));
    printf("%d\n", htoi("0Xabc"));
    printf("%d\n", htoi("deadbeef"));
    printf("%d\n", htoi("badfood"));
    return 0;
}
