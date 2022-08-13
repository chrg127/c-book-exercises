#include <stdio.h>

#define DAYSINYEAR 365
#define MONTHSINYEAR 12

static char daytab[2][MONTHSINYEAR+1] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int, int, int);

void month_day(int, int, int *, int *);

/* day_of_year: set day of year from month and day */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *start, *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (month <= 0 || month > MONTHSINYEAR)
        return -1;
    if (day <= 0 || day > daytab[leap][month])
        return -1;

    for (p = *(daytab + leap) + 1; p < *(daytab + leap) + month; p++)
        day += *p;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    /* error checking */
    if (yearday <= 0 || yearday > DAYSINYEAR + leap) {
        pmonth = NULL;
        pday = NULL;
        return;
    }

    for (p = *(daytab+leap)+1; yearday > *p; p++)
        yearday -= *p;
    *pmonth = p - *(daytab+leap);
    *pday = yearday;
}

int main()
{
    int month, day;

    printf("dayofyear: %d\n", day_of_year(1980, 12, 31));
    month_day(1980, 366, &month, &day);
    printf("month: %d, day: %d\n", month, day);
}
