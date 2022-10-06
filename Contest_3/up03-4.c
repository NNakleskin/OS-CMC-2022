#include <stdio.h>

enum { MY_INT_MAX = 2147483647 };
enum { MY_INT_MIN = -2147483648 };

int satsum(int v1, int v2)
{
    if(v1 > 0 && v2 > 0){
        if(MY_INT_MAX - v1 - v2 > 0){
            return v1 + v2;
        } else {
            return MY_INT_MAX;
        }
    }
    if(v1 < 0 && v2 < 0){
        if(MY_INT_MIN - v1 - v2 > 0){
            return MY_INT_MIN;
        } else {
            return v1 + v2;
        }
    }
    return v1 + v2;
}
