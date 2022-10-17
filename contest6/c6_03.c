#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

int
main()
{
    int yr;
    scanf("%d", &yr);
    struct tm date = {};
    date.tm_year = yr - 1900;
    date.tm_mday = 1;
    date.tm_isdst = -1;
    mktime(&date);
    int month = date.tm_mon;
    int count = 0;
    while (date.tm_year == yr - 1900) {

        if (date.tm_wday == 4) {
            if (date.tm_mday % 3 && count % 2) {
                printf("%d %d\n", date.tm_mon + 1, date.tm_mday);
            }
            ++count;
        }
        ++date.tm_mday;
        date.tm_isdst = -1;
        mktime(&date);
        if (month != date.tm_mon) {
            month = date.tm_mon;
            count = 0;
        }
    }
    return 0;
}