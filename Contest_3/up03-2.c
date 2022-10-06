#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char **argv)
{
    long long sum_positive = 0;
    long long sum_negative = 0;
    if(argc < 2)
    {
        printf("0\n0\n");
        return 0; 
    }
    for(int i = 1; i < argc; i++)
    {
        int temp = atoi(argv[i]);
        if(temp > 0){
            sum_positive += temp;
        } else if(temp < 0) {
            sum_negative += temp;
        }
    }
    printf("%lld\n", sum_positive);
    printf("%lld\n", sum_negative);
    return 0;
}
