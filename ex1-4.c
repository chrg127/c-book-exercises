#include <stdio.h>

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = -17;    /* lower limit of temperature table */
    upper = 148;    /* upper limit */
    step  = 11;     /* step size */

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius / (5.0/9.0) + 32.0;
        printf("%3.0f %6.1f\n", fahr, celsius);
        celsius = celsius + step;
    }
}
