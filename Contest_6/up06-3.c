#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { SEC_IN_D = 86400 };


int main(void){
    int n;
    scanf("%d", &n);
    time_t *diff;
    diff = 0;
    struct tm start;
    start.tm_year = n - 1900;
    time_t time_start = mktime(&start);
    struct tm fin;
    printf("%d\n", n);
    fin.tm_year = n - 1899;
    printf("%d\n", fin.tm_year);
    time_t time_fin = mktime(&fin);
   
    printf("%ld\n", time_start);
    printf("%ld\n", time_fin);

    for(long i = time_start; i < time_fin; i += SEC_IN_D){
        struct tm day;
        gmtime_r(&i, &day);
        printf("nnn%d\n", day.tm_wday);
    }

    return 0;
}
