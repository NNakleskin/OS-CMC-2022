#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void
print_arr_int(int* array, int count)
{
    for(int i = 0; i < count; i++){
        printf("%d ", array[i]);
    }
    putchar(10);
}


int 
compare_inc(const void * x1, const void * x2)   
{
    return *(int*)x1 - *(int*)x2;             
}



int 
compare_dec(const void * x1, const void * x2)  
{
    return *(int*)x2 - *(int*)x1;           
}


void 
concat_arr(int* arr_1, int len_1, int *arr_2, int len_2, int* res)
{
    int res_index = 0;
    for(int i = 0; i < len_1; i++){
        res[res_index] = arr_1[i];
        res_index++;
    }
    for(int i = 0; i < len_2; i++){
        res[res_index] = arr_2[i];
        res_index++;
    }
    free(arr_1);
    free(arr_2);
}


void 
sort_even_odd(size_t count, int *data)
{
        int even_index = 0;
        int odd_index = 0;
        int *even_arr = calloc(count, sizeof(data));
        int *odd_arr = calloc(count, sizeof(data));
        for(int i = 0; i < count; i++){
            if(data[i] % 2 == 0){
                even_arr[even_index] = data[i];
                even_index++;
            } else {
                odd_arr[odd_index] = data[i];
                odd_index++;
            }
        }
        qsort(even_arr, even_index, sizeof(even_arr[0]), compare_inc);
        qsort(odd_arr, odd_index, sizeof(odd_arr[0]), compare_dec);
        concat_arr(even_arr, even_index, odd_arr, odd_index, data);
}


