/* invert: invert n bits of x beginning at position p */
char invert(char x, char p, char n)
{
    char andop, shift, orop1, orop2;

    andop = ((char) pow(2, (double) n)) - 1;
    shift = p - n + 1;
    if (shift > 0)
        andop <<= shift;
    else if (shift < 0) {
        shift *= -1;
        andop >>= shift;
    }
    orop1 = ~x & andop;
    orop2 = x & ~andop;

    return orop1 | orop2;
}


