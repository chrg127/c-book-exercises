/*
 * There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */

#include <stdio.h>

#define DAYS_IN_YEAR 365
#define MONTHS_IN_YEAR 12

static char daytab[2][MONTHS_IN_YEAR+1] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

/* day_of_year: set day of year from month and day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (month <= 0
     || month > MONTHS_IN_YEAR
     || day <= 0
     || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday <= 0 || yearday > DAYS_IN_YEAR + leap) {
        pmonth = NULL;
        pday = NULL;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int main()
{
    int month, day;

    printf("dayofyear: %d\n", day_of_year(1980, 12, 31));
    month_day(1980, 366, &month, &day);
    printf("month: %d, day: %d\n", month, day);
}
