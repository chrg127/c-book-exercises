/*
 * Revise minprintf to handle more of the other facilities of
 * printf.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include "intconversion.h"

#define MAXSTR 100

/*
 * minprintf: minimal printf with variable argument list
 * added: support for %c, return how many characters printed
 */
int minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival, printed;
    double dval;
    char cval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt, printed = 0; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            printed++;
            continue;
        }
        switch(*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printed += printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printed += printf("%f", dval);
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++) {
                putchar(*sval);
                printed++;
            }
            break;
        case 'c':
            cval = (char) va_arg(ap, int);
            printed += printf("%c", cval);
        default:
            putchar(*p);
            printed++;
            break;
        }
    }
    va_end(ap); /* clean up when done */
    return printed;
}
