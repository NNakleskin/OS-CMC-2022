#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>


const char my_NAN[] = "18446744073709551616";
const char LLMIN_STR[] = "02021110011022210012102010021220101220222";


int asymetric(char *buf) {
    int res;
    size_t len = strlen(buf);
    if(buf[0] == 'a') {
        res = -1;
        for(int i = 0; i < len; ++i) {
            if(buf[i] == 'a') {
                buf[i] = '1';
            } else if(buf[i] == '1') {
                buf[i] = 'a';
                
            }
        }
    }
    int indicate = 0;
    for(int i = len; i >= 0; --i) {
        switch (buf[i]) {
            case 'a':{
                if(indicate) {
                    buf[i] = '1';         
                } else {
                    indicate = 1;
                    buf[i] = '2';
                }
                break;
            }
            case '1':{
                if(indicate) {
                    buf[i] = '0';
                    indicate = 0;
                } 
                break;
            }
            case '0':{
                if(indicate) {
                    buf[i] = '2';
                } 
                break;
            }
            default: {
                buf[i] = ' ';
            }
        }
    }
    return res;
}



int main(void) {
    char *tmp = calloc(1000001,  sizeof(char));
    while(scanf("%s", tmp) != EOF) {
        int res = asymetric(tmp);

        char *tmp2 = calloc(1000001, sizeof(char));
        int index = 0;
        for(int i = 0; i < strlen(tmp); ++i) {
            if(tmp[i] != ' ') {
                tmp2[index] = tmp[i];
                index++;
            }
        }

        long long val = 0;
        errno = 0;
        if(strcmp(LLMIN_STR, tmp2) == 0) {
            printf("%lld\n", LLONG_MIN);
            continue;
        }
        if(res == -1) {
            val = -1 * strtoll(tmp2, NULL, 3);
        } else {
            val = strtoll(tmp2, NULL, 3);
        }
        if(errno != 0) {
            printf("%s\n", my_NAN);
        } else {
            printf("%lld\n", val);
        }
    }
    free(tmp);
    return 0;
}

