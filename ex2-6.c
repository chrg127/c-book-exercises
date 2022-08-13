/* setbits: set the bits of x beginning at  to the rightmost bits of y.
 * bits are counted backwards: 11110000
 *                             76543210
 */
char setbits(char x, char p, char n, char y)
{
    char shift, andop, orop1, orop2;

    shift = p - n;
    andop = ((char) pow(2, (double) n)) - 1;
    if (shift > 0) {
        orop1 = x & ~(andop << shift);
        orop2 = (y & andop) << shift;
    } else if (shift < 0) {
        shift *= -1;
        orop1 = x & !(andop >> shift);
        orop2 = (y & andop) >> shift;
    } else {
        orop1 = x & !(andop);
        orop2 = (y & andop);
    }

    return orop1 | orop2;
}
