/*
 * Write an alternate version of squeeze(s1, s2) that deletes
 * each character in s1 that matches any character in the string s2.
 */

#include <stdio.h>

/* squeeze: delete all c from s1 that match with any c from s2 */
void squeeze(char s1[], char s2[])
{
    int i, j;

    for (i = j = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
        if (s1[i] != s2[i])
            s1[j++] = s1[i];
    s1[j] = '\0';
}

/* tests */
int main(void)
{
    char s1[] = "aabbcc";
    char s2[] = "bc";
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}
