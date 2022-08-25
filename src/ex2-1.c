/*
 * Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate
 * values from standard headers and by direct computation. Harder if you
 * compute them: determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    printf("%d\n", INT_MIN);
    printf("%d\n", INT_MAX);
    printf("%u\n", UINT_MAX);
    printf("%d\n", SHRT_MIN);
    printf("%d\n", SHRT_MAX);
    printf("%u\n", USHRT_MAX);
    printf("%ld\n", LONG_MIN);
    printf("%ld\n", LONG_MAX);
    printf("%lu\n", ULONG_MAX);
    printf("%g\n", FLT_MIN);
    printf("%g\n", FLT_MAX);
    return 0;
}
