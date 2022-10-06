#include <stdio.h>


typedef int STYPE;
typedef unsigned int UTYPE;


STYPE lroll(STYPE x, int y);
STYPE rrol(STYPE x, int y);
int len(STYPE x);


int sizeoff(STYPE value)
{
    int i = 1;
    STYPE tmp = rrol(value, i);
    while(tmp != value){
        i++;
        tmp = rrol(value, i);
    }
    return i;
}


STYPE bit_reverse(STYPE value)
{
    char chres[65];
    long long temp = (long long) value;
    int i = 0;
    while(temp != 1){
        chres[i] = (temp % 2) + '0';
        temp /= 2;
        i++;
    }
    printf("%s\n", chres);
    return 0;
}


STYPE lrol(STYPE x, int y)
{
    return ((x << y) | (x >> (8 - y)));
}


STYPE rrol(STYPE x, int y)
{
    return ((x >> y) | (x << (8 - y)));
}
