/*
 * Write getfloat, the floating-point analog of getint. What
 * type does getfloat return as its function value?
 */

/* getfloat: get next float number from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float power;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1; /* handle sign */
    if (c == '+' || c == '-')
        c = getch();
    if (!isdigit(c)) {
        ungetch(c);
        return 0;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.')
        c = getch();
    if (!isdigit(c = getch())) {
        ungetch(c);
        return c;
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    *pn = sign * *pn / power;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main(void)
{
    float f;
    int r = getfloat(&f);
    printf("f = %g, r = %d\n", f, r);
    return 0;
}
