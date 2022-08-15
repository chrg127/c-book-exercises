/*
 * Write a loop equivalent to the for loop above without using &&
 * or ||.
 */

#include <stdio.h>

int main(void)
{
    int i, lim, c;

    lim = 1000;

    /* example for loop: */
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        ;

    /* the exercise: */
    i = 0;
    while (c = getchar(), c != EOF) {
        if (i >= lim - 1)
            break;
        if (c == '\n')
            break;
        i++;
    }

    return 0;
}
