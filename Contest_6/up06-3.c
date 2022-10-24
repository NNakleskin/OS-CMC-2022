#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(void){
    int n;
    scanf("%d", &n);
    if(n > 2037 || n < 1910) {
        return 0;
    }
// 4
    int count_week = 0;
    for(int month = 0; month < 12; month++) {
        count_week = 0;
        for(int day = 1; day < 32; day++) {
            
            struct tm tmp;
            tmp.tm_year = n - 1900;
            tmp.tm_mon = month;
            tmp.tm_mday = day;
            tmp.tm_hour = 0;
            tmp.tm_min = 0;
            tmp.tm_sec = 0;
            tmp.tm_isdst = -1;
            
            mktime(&tmp);
            if(tmp.tm_wday == 4) {
                count_week++;
                if(count_week == 2 || count_week == 4) {
                    if((tmp.tm_mday) % 3 != 0) {
                        printf("%d %d\n", tmp.tm_mon  + 1, tmp.tm_mday);
                    }
                }
            }
        }
    }
    return 0;
}
