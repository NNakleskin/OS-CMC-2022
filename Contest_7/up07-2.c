#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char** argv)
{
    long long res = 0;
    if(argc < 2) {
        printf("%lld\n", res);
        return 0;
    }
    for(int i = 1; i < argc; i++) {
        errno = 0;
        int len = strlen(argv[i]);
        int sign = 1;
        int k_indicate = 1;
        if(argv[i][len - 1] != '-' && argv[i][len - 1] != '+') {
            continue;
        }
        if(argv[i][len - 1] == '-') {
            sign *= -1;
        } 
        argv[i][len - 1] = '\0';
        if(argv[i][len - 2] == 'k') {
            k_indicate = 1000;
            argv[i][len - 2] = '\0';
        }
        int indicate = 0;
        for(int j = 1; j < strlen(argv[i]); j++) {
            if(argv[i][j] < '0' || argv[i][j] > '9') {
                indicate = 1;
                break;
            }
        }
        if(indicate) {
            continue;
        }
        int tmp =  strtol(argv[i], NULL, 10) * sign;
        if(errno != 0) {
            continue;
        }
        if(__builtin_mul_overflow(tmp, k_indicate, &tmp)) {
            continue;
        } else {
            res += tmp;
        }
    }
    printf("%lld\n", res);
    return 0;
}
