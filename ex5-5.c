/*
 * Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s, t, n) copies at most n characters of t to
 * s. Full descriptions in Appendix B.
 */

#include <stdio.h>

void str_n_cpy(char *dst, char *src, int n)
{
    while (*dst++ = *src++)
        if (--n == 0)
            break;
    *dst = '\0';
}

void str_n_cat(char *dst, char *src, int n)
{
    while (*dst)
        dst++;
    while (*dst++ = *src++)
        if (--n == 0)
            break;
    *dst = '\0';
}

int str_n_cmp(char *s, char *t, int n)
{
    while (*s == *t) {
        if (--n == 0 || *s == '\0' || *t == '\0')
            break;
        s++; t++;
    }
    return *s == *t;
}

int main(void)
{
    char s[] = "hello world";
    char t[100];
    str_n_cpy(t, s, 4);
    printf("%s\n", t);

    char s2[100] = "hello";
    char t2[] = "world";
    str_n_cat(s2, t2, 3);
    printf("%s\n", s2);

    printf("%d\n", str_n_cmp("hello", "hellp", 4));

    return 0;
}
