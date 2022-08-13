/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01) /* check if the rightmost bit is 1 */
            b++;

    return b;
}

/* a faster bitcount */
int faster_bitcount(unsigned x)
{
    int b;
    
    for (b = 0; x != 0; x &= (x-1)) {
        b++;
    }

    return b;
}
