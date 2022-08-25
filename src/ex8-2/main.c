/*
 * Rewrite fopen and _fillbuf with fields instead of expolicit bit
 * operations. Compare code size and execution speed.
 */

/* this file is used for testing; the exercise is in other files */

#include "stdio.h"

int main(void)
{
    int c;

    while (c = getchar(), c != EOF)
        ;
    return 0;
}
