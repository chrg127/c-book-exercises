/*
 * Write a function invert(x, p, n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */

#include <stdio.h>

unsigned int bitmask(unsigned int n)
{
    return (1u << n) - 1u;
}

unsigned int invert(unsigned int x, unsigned int p, unsigned int n)
{
    unsigned int mask, left, right;
    mask = bitmask(n);
    left  = ~x &  (mask << p);
    right =  x & ~(mask << p);
    return left | right;
}

/* tests */
int main(void)
{
    unsigned int x = 0xf0;
    unsigned int r = invert(x, 2, 4);
    printf("%x\n", r);
    return 0;
}
