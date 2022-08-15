/*
 * Rewrite the function lower, which converts upper case letters
 * in lower case, with a conditional expression instead of if-else.
 */

int lower(int c)
{
    return c >= 'A' && c <= 'Z' ? c - 'A' : c;
}
