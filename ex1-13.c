// Write a program to print a histogram of the lengths of word in
// its input. It is easy to draw the histogram with the bars horizontal; a vertical
// orientation is much more challenging

#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */
#define MAX_WORD_LENGTH 25

/* print histogram of lengths of words */
int main(void)
{
    /* keep lengths in this array.
     * arr[1] -> words with length 1.
     * arr[2] -> words with length 2.
     * etc.
     * we don't care about words with lengths > MAX_WORD_LENGTH.
     */
    int lengths[MAX_WORD_LENGTH];
    int c, i, j, state, length;

    for (i = 0; i < MAX_WORD_LENGTH; i++)
        lengths[i] = 0;

    state = OUT;
    length = 0;
    while (c = getchar(), c != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                /* got to the end of a word: update the lengths array */
                lengths[length]++;
                length = 0;
            }
            state = OUT;
        } else if (state == OUT) {
            state = IN;
        }
        if (state == IN)
            length++;
    }

    /* print a vertical histogram */
    for (i = 0; i < MAX_WORD_LENGTH; i++) {
        printf("%3d ", i);
        for (j = 0; j < lengths[i]; j++) {
            printf("#");
        }
        printf("\n");
    }

    /* a horizontal histogram is indeed hard */

    return 0;
}
