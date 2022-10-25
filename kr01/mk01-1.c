#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"


char max(int* a, int* b)
{
    for(int i = 10000; i >= 0; --i)
    {
        if (a[i] < b[i])
            return 'b';
        else if (a[i] > b[i])
            return 'a';
    }
    return 'a';
}

int num_st(int* res)
{
    int num_start = 12;
    while((num_start >= 0) && (res[num_start] == 0))
    {
        num_start--;
    }
    return num_start;
}

void outp(int* res)
{
    int was_printed = 0;
    int i = num_st(res);
    while(i >= 0)
    {
        was_printed = 1;
        printf("%d", res[i]);
        i--;
    }
    if(!was_printed)
    {
        printf("0");
    }
}

int copy(int*destination, char*where,  int first, int last) // Копирование куска строки
{
    for(int j = 0; j < last - first; j++)
    {
        destination[j] = where[last - j - 1] - '0';
    }
    return 0;

}

int*
summ(int* a, int* b)
{
    int* res;
    res = calloc(12, sizeof(int));
    for(int i = 0; i < 12; i++)
    {
        int sum_help = a[i] + b[i] + res[i];
        res[i] = sum_help % 10;
        res[i + 1] = sum_help / 10;
    }
    free(a);
    return res;
}

int*
diff(int* a, int* b)
{
    int* res;
    res = calloc(12, sizeof(int));
    for(int i = 0; i < 12; i++)
    {
        if (a[i] >= b[i]) {
            res[i] = a[i] - b[i];
            continue;
        }
        res[i] = a[i] - b[i] + 10;
        int j = i + 1;
        while (a[j] == 0) {
            a[j] = 9;
            ++j;
        }
        --a[j];
    }
    free(a);
    return res;
}


int main(int argc, char **argv)
{
    int *a = calloc(12, sizeof(char));
    int *b;
    b = calloc(12, sizeof(int));
    for(int i = 0; i < argc; i++) {
        char sign = '+';
        if(argv[i][0] == '-') {
            sign = '-';
            argv[i][0] = 0;
        }
        copy(b, argv[i], 0, strlen(argv[i]));
        if(sign == '+')
        {
            outp(summ(a, b));
            a = summ(a, b);
        }
        if(sign == '-') // Вычитание
        {
            if(max(a, b) == 'a')
            {
                a = diff(a, b);
            }
            else
            {
                a = diff(b, a);
                a[0] *= -1;
            }
        }
    }
    outp(a);
    free(a);
    free(b);
    return 0;
}
