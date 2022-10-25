#include <time.h>
#include <stdio.h>
#include <math.h>


int main(void) {
    int year;
    scanf("%d", &year);
    if(year > 2037 || year < 1902) {
        return 0;
    }
    int degree = 0;
    int count = 0;
    for(int month = 0; month < 12; month++) {
        for(int day = 1; day < 32; day++) {

            struct tm tmp;
            tmp.tm_year = year - 1900;
            tmp.tm_mon = month;
            tmp.tm_mday = day;
            tmp.tm_hour = 0;
            tmp.tm_min = 0;
            tmp.tm_sec = 0;
            tmp.tm_isdst = -1;

            mktime(&tmp);
            //printf("%d", (int) pow(2, degree));
            if((int) pow(2, degree) == tmp.tm_yday + 1) {
                degree++;
                if(tmp.tm_wday != 6 && tmp.tm_wday != 0) {
                    count++;
                }
            }

        }
    }
    printf("%d\n", count);
    return 0;
}
