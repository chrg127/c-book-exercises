/*
 * Write a function setbits(x, p, n, y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y,
 * leaving the other bits unchanged.
 */

#include <stdio.h>
#include <math.h>

unsigned int bitmask(unsigned int n)
{
    return (1u << n) - 1u;
}

unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y)
{
    unsigned int mask, left, right;
    mask = bitmask(n);
    /* take the unchanged part of x. */
    left = ~(mask << p);
    left = x & left;
    /* get the rightmost n bits of y and shift them. */
    right = (y & mask) << p;
    /* join the two parts. */
    return left | right;
    /* also could've been done in one single expression:
     * return (x & ~(mask << p)) | (y & mask) << p; */
}

/* tests */
int main(void)
{
    unsigned int x = 0xffff;
    unsigned int y = 0;
    unsigned int r = setbits(x, 1, 3, y);
    printf("%x\n", r);
    return 0;
}

