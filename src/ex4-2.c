/*
 * Extend atof to handle scientific notation of the form
 *      123.45e-6
 * where a floating-point number may be followed by e or E
 * and an optionally signed exponent.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power, sc_power;
    int i, sign, sc_sign;

    /* skip white space */
    for (i = 0; isspace(s[i]); i++)
        ;
    /* handle sign */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    /* handle part before dot */
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    /* handle dot */
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    /* handle scientific notation */
    if (tolower(s[i]) == 'e')
        i++;
    sc_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (sc_power = 0.0; isdigit(s[i]); i++)
        sc_power = 10.0 * sc_power + (s[i] - '0');
    power *= pow(10, sc_power * sc_sign * -1);
    return sign * val / power;
}

/* tests */
int main(void)
{
    char s[] = "123.45e-6";
    printf("%g\n", atof(s));
    return 0;
}
