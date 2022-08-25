/*
 * Write a program that will print arbitrary input in a sensible way.
 * As a minimum, it should print non-graphic characters in octal or hexadecimal
 * arccording to local custom, and break long text lines.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 80

char *process(int c, char *buf)
{
    int i;
    static int line_len = 0;

    line_len++;
    if (c == '\n' || line_len == MAX_LINE_LEN) {
        line_len = 0;
        buf[0] = '\n';
        buf[1] = '\0';
        return buf;
    }
    if ((c < 32 || c > 126) && c != '\n')
        sprintf(buf, "0x%02x", c);
    else
        sprintf(buf, "%c", c);
    return buf;
}

int main()
{
    int c, i;
    char s[100];

    while (c = getchar(), c != EOF)
        printf("%s", process(c, s));
}
