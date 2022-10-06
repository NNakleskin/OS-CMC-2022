#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void get_lex(int n, char **array);
int get_ex(int n, int base, char *result, int endline);


int main(void)
{
    int n;
    scanf("%d", &n);
    char **lex_arr;
    char res[100];
    get_ex(3, 2, res, 0);
    printf("%s\n", res);
    return 0;
}


void get_lex(int n, char **array)
{

}


int get_ex(int n, int base, char *result, int endline)
{
    endline += 1;
    if(n / base <= 1){
        result[get_ex(n / 2, base, result, endline)] = (char) n % base;
        return endline + 1;
    }
    result[endline] = (char) n % base;
    result[endline - 1] = (char) n / base;
    return endline + 1;
}
