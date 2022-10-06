#include <stdio.h>
#include "up03-1.c"


typedef int STYPE;
typedef unsigned int UTYPE;
extern STYPE bit_reverse(STYPE value);


int main(void)
{
    int a = 12;
    printf("%d", bit_reverse(a));
    return 0;
}
