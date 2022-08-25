/*
 * Write a function expand(s1, s2) that expands shorthand notation
 * like a-z in the string s1 into the equivalent complete list abc..xyz in
 * s2. Allow for letters of either case and digits and be prepared to handle
 * cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing -
 * is taken literally.
 */

#include <stdio.h>
#include <ctype.h>

int is_good_range(int c1, int c2)
{
    return c1 > c2                     ? 0
         : islower(c1) && !islower(c2) ? 0
         : isupper(c1) && !isupper(c2) ? 0
         : isdigit(c1) && !isdigit(c2) ? 0
         :                               1;
}

/* expand: expands notations such as a-z and 0-9 into the full list
 * any wrong range (such as a-9 or A-a) is taken literally */
void expand(char s1[], char s2[])
{
    int i, j, c;

    j = 0;
    for (i = 0; s1[i]; ) {
       if (s1[i+1] != '\0'
        && s1[i+2] != '\0'
        && isalnum(s1[i])
        && s1[i+1] == '-'
        && isalnum(s1[i+2])
        && is_good_range(s1[i], s1[i+2])) {
           for (c = s1[i]; c <= s1[i+2]; c++)
               s2[j++] = c;
           i += 3;
       } else {
           s2[j++] = s1[i];
           i++;
       }
    }
    s2[j] = '\0';
}

/* tests */
int main(void)
{
    char a[] = "a-z";
    char b[] = "a-b-c";
    char c[] = "a-z0-9";
    char d[] = "-a-z";
    char e[] = "9-a";
    char s2[100];

    expand(a, s2); printf("a = %s\n", s2);
    expand(b, s2); printf("b = %s\n", s2);
    expand(c, s2); printf("c = %s\n", s2);
    expand(d, s2); printf("d = %s\n", s2);
    expand(e, s2); printf("e = %s\n", s2);

    return 0;
}
