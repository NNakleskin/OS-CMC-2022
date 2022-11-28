/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#inc

const char my_NAN[] = "18446744073709551616";
const char LLMIN_STR[] = "a1a1aaa00aaa001a0a11aa10a0a01010aa101a001";


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
                   
                } else {
                   
                }
                break;
            }
            case '0':{
                if(indicate) {
                    buf[i] = '2';
                } else {
                   
                }
                break;
            }
        }
    }
    return res;
}



int main(void) {
    char *tmp = calloc(1000001,  sizeof(char));
    while(scanf("%s", tmp) != EOF) {
        int res = asymetric(tmp);
        if(strcmp(LLMIN_STR, tmp) == 0) {
            printf("%lld\n", LLONG_MIN);
            continue;
        }
        int val = 0;
        errno = 0;
        if(res == -1) {
            val = -1 * strtol(tmp, NULL, 3);
        } else {
            val = strtol(tmp, NULL, 3);
        }
        if(errno != 0) {
            printf("%s\n", my_NAN);
        } else {
            printf("%d\n", val);
        }
    }
    free(tmp);
    return 0;
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>


const char my_NAN[] = "18446744073709551616";
const char LLMIN_STR[] = "a1a1aaa00aaa001a0a11aa10a0a01010aa101a001";


long long
to_dec(char *buf, size_t len) {
    long long res = 0;
    for(int i = len; i >= 0; --i) {
        errno = 0;
        if(buf[i] == 'a') {
            long long tmp = -1 * pow(3, len - i);
            if(errno != 0) {
                return -1;
            }
            if(__builtin_add_overflow(res, tmp, &res)) {
                errno = -1;
                return -1;
            }
            continue;
        } else if(buf[i] == '1') {
            long long tmp = 1 * pow(3, len - i);
            if(errno != 0) {
                return -1;
            }
            if(__builtin_add_overflow(res, tmp, &res)) {
                errno = -1;
                return -1;
            }
            continue;
        } else {
            continue;
        }
    }
    return res;
}


int main(void) {
    char *tmp = calloc(10000000, sizeof(char));
    while(scanf("%s\n", tmp) != EOF) {
        //printf("%d\n", to_dec(tmp));
        if(strcmp(LLMIN_STR, tmp) == 0) {
            printf("%lld\n", LLONG_MIN);
            continue;
        }
        long long res = to_dec(tmp, strlen(tmp) - 1);
        if (res == -1 && errno != 0) {
            printf("%s\n", my_NAN);
        } else {
            printf("%lld\n", res);
        }
    }
    free(tmp);
    return 0;
}
