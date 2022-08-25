/*
 * Write a program to print a histogram of the frequencies of
 * different characters in its input.
 */

#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* print histogram of frequencies of characters */
int main(void)
{
    int ndigits[10];
    int c, i, j, nwhite, nother;

    for (i = 0; i < 10; i++)
        ndigits[i] = 0;

    nwhite = nother = 0;
    while (c = getchar(), c != EOF) {
        if (c >= '0' && c <= '9')
            ++ndigits[c - '0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    }

    for (i = 0; i < 10; i++) {
        printf("%6d ", i);
        for (j = 0; j < ndigits[i]; j++)
            printf("#");
        printf("\n");
    }
    printf("whites ");
    for (j = 0; j < nwhite; j++)
        printf("#");
    printf("\n");
    printf("other  ");
    for (j = 0; j < nother; j++)
        printf("#");
    printf("\n");

    return 0;
}
