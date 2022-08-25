/*
 * Write the function strend(s, t), which returns 1 if the string
 * t occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>

int strend(char *s, char *t)
{
    char *s2, *t2;

    s2 = s;
    t2 = t;
    while (*s)
        s++;
    while (*t)
        t++;
    while (*s == *t && s != s2 && t != t2) {
        s--;
        t--;
    }
    return s == s2 ? 1 : 0;
}

int main(void)
{
    char s[] = "hello";
    char t[] = " hello";
    printf("%d\n", strend(s, t));
    return 0;
}
