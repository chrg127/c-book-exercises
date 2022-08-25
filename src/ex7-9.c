/*
 * Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilities.
 */

/*
 * I honestly dunno how you're supposed to implement it better than the
 * following...
 */
int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}
