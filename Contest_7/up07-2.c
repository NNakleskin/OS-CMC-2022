#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    long long res = 0;
    if(argc < 2) {
        printf("%lld\n", res);
        return 0;
    }   
    for(int i = 1; i < argc; i++) {
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
        res += atoi(argv[i]) * k_indicate * sign;
    }
    printf("%lld\n", res);
    return 0;
}
