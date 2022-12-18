#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>


unsigned get_alignment(unsigned x) {
    unsigned degree = (unsigned) log2(x) + 1;
    while(x % (unsigned) pow(2, degree) != 0) {
        degree--;
    }
    return degree++;
}


int main(void) {
    unsigned n = 0, count = 0;
    unsigned size = 0;
    unsigned alignment = 1, indicate = 1;
    while(scanf("%u", &n) == 1) {
        count++;
        indicate = 0;
        unsigned tmp = get_alignment(n);
        unsigned tmp2 = pow(2, tmp);
        size += n + tmp;     
        if(alignment < tmp) {
            alignment = pow(2, tmp);
        }
    }
    if(count == 1) {
        count++;
    }
    if(indicate) {
        count = 1;
        size = 1;
        alignment = 1;
    }
    printf("%u %u\n", size,  alignment);
    return 0;
}
