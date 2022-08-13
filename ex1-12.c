// Write a program that prints its input one word per line.

#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
int main(void)
{
    int c, state;

    state = OUT;
    while (c = getchar(), c != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
            state = IN;
        if (state == IN)
            putchar(c);
        else
            printf("\n");
    }
    return 0;
}
