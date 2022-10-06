#include <stdio.h>
#include "up03-4.c"

extern int satsum(int v1, int v2);


int main(void)
{
    int a, b;
    scanf("%d%d", &a, &b); 
    printf("%d\n", satsum(a, b));
    return 0;
}
