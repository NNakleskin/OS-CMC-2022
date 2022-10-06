#include <stdio.h>
#include <stdlib.h>


void lex_order_by_value(unsigned int n);
int fact(int n);
int degree(int a, int b);
int compare(const void * x1, const void * x2);


int
main(void)
{
    unsigned int n;
    if(scanf("%u", &n) != 1){
        return 0;
    }
    if(n > 9 || n < 0){
        return 0;
    }
    lex_order_by_value(n);
    return 0;
}


void
lex_order_by_value(unsigned int n)
{
    int len = fact(n);
    int *arr = calloc(n, sizeof(n));
    int def_arr[n];
    for(unsigned int i = 0; i < n; i++){
        def_arr[i] = i + 1;
    }
    for(unsigned int i = 0; i < len; i++){
        unsigned int point = i % (n - 1);
        def_arr[point] ^= def_arr[point + 1];
        def_arr[point + 1] ^= def_arr[point];
        def_arr[point] ^= def_arr[point + 1];
        for(unsigned int j = 0; j < n; j++){
            //printf("j = %d, i = %d, def_arr[j] = %d, degree = %d\n", j, i, def_arr[j], degree(10, j));
            arr[i] += def_arr[n - j - 1] * degree(10, j);
            //printf("%d", arr[i]);
        }
       // printf("def");
        for(int k = 0; k < n; k++){
            printf("%d", def_arr[k]);
        }
        printf("\n");
       // printf("\n%d\n", point);
       // printf("%d\n", arr[i]);
    }
    printf("||||");
    qsort(arr, len, sizeof(arr[0]), compare);
    for(int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    free(arr);
}


int
fact(int n)
{
    return n == 1 ? 1 : n * fact(n - 1);    
}


int
degree(int a, int b)
{
    int res = 1;
    for(int i = 0; i < b; i++){
        res *= a;
    }
    return res;
}


int
compare(const void * x1, const void * x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}
