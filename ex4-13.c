/*
 * Write a recursive version of the function reverse(s), which
 * reverses the string s in place.
 */

#include <stdio.h>
#include <string.h>

void reverse_step(char s[], int i, int j)
{
    int tmp;

    if (i < j) {
        tmp  = s[i];
        s[i] = s[j];
        s[j] = tmp;
        reverse_step(s, i+1, j-1);
    }
}

/* reverse: reverse string s in place, recursively */
void reverse(char s[])
{
    reverse_step(s, 0, strlen(s) - 1);
}

int main(void)
{
    char s[] = "hello";
    reverse(s);
    printf("%s\n", s);
    char s2[] = "hello2";
    reverse(s2);
    printf("%s\n", s2);
    return 0;
}
