/* rightrot: right rotation of x by n position
 * example: 11110010 by 2
 *          10111100
 */
unsigned char rightrot(unsigned char x, unsigned char n)
{
    unsigned char carrybits = (x & ((char) pow(2, (double) n)) - 1) << CHAR_BIT - n;
    unsigned char orop = (unsigned) x >> (unsigned) n;
    return orop | carrybits;
}

