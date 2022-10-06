#include <stdio.h>


int
is_inside(double x, double y)
{
    const double X_MAX = 5;
    const double X_MIN = 2;
    const double Y_MAX = 7;
    const double Y_MIN = 1;
    double diff = x - y;
    if(y <= Y_MAX && y >= Y_MIN && x >= X_MIN && x <= X_MAX && diff <= 2){
        return 1;
    } else {
        return 0;
    }
}


int
main(void)
{
    double x, y;
    if(scanf("%lf%lf", &x, &y) != 2){
        return 1;
    }
    printf("%d\n", is_inside(x, y));
    return 0;
}

