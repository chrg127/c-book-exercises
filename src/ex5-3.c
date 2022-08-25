/*
 * Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s, t) copies the string t to the end of s.
 */

#include <stdio.h>

/* strcat: concatenate t to the end of s; s must be big enough */
void str_cat(char *s, char *t)
{
    while (*s++ != '\0')
        ;
    s--;
    while (*s++ = *t++)
        ;
}

int main(void)
{
    char s[100] = "hello";
    char t[] = "world";
    str_cat(s, t);
    printf("%s\n", s);
    return 0;
}
