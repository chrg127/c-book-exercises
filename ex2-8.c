/*
 * Write a function rightrot(x, n) that returns the value of the
 * integer x rotated to the right by n bit positions.
 */

#include <stdio.h>
#include <limits.h>

unsigned int bitmask(unsigned int n)
{
    return (1u << n) - 1u;
}

unsigned int rightrot(unsigned int x, unsigned int n)
{
    unsigned int int_bits;
    int_bits = sizeof(unsigned int) * CHAR_BIT;
    return (x >> n) | (x << (int_bits - n));
}

/* tests */
int main(void)
{
    printf("%x\n", rightrot(0x000000f0, 1));
    printf("%x\n", rightrot(0x0000000f, 1));
    return 0;
}

