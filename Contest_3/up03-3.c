#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int roundfour(double x);


int main(int argc, char **argv)
{
    if(argc < 2){
        return 1;
    }
    double start_currency = atof(argv[1]);
    double res = start_currency;
    for(int i = 2; i < argc; i++){
        double percent = 1 +  atof(argv[i]) / 100.0;
        res  = roundfour(res * percent) / 10000.0;
    }
    printf("%.4lf\n", res);
    return 0;
}

int 
roundfour(double x)
{
    return (int)round(x * 10000);
}
