/*
 * Write the function strrindex(s, t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none.
 */

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

/* strrindex: get the position of the rightmost occurrence of t in s, -1 if none */
int strrindex(char s[], char t[])
{
    int i, j, k, ris;

    /* any occurrence is recorded into ris, which is always overwritten on new ones.
     * the whole string is always searched. */
    ris = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            ris = i;
    }
    return ris;
}
