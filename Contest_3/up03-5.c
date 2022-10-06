#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Elem
{
    struct Elem *next;
    char *str;
};


char*
int_to_str(int n)
{
    char *res = calloc(11, sizeof(char));
    if(n / 10 == 0){
        res[0] = (char) n;
        return res;
    }
    res[0] = (char) n % 10;
    return strcat(int_to_str(n / 10), res);
}


struct Elem 
*dup_elem(struct Elem *head)
{
    struct Elem *res = calloc(1, sizeof(head));
    struct Elem *pointer_head = head;
    struct Elem *pointer_res = res;
    if(res == NULL){
        return NULL;
    }
    while(pointer_head != NULL){
        char *temp = pointer_head->str;
        int indicate = 1;
        int space_indicate = 1;
        for(int i = 0; i < strlen(temp); i++){
            if((temp[i] >= '0' && temp[i] <= '9') || ((temp[i] == ' ' || temp[i] == '-') && space_indicate)){
                if(temp[i] != ' '){
                    space_indicate = 0;
                }
                continue;
            }
            indicate = 0;
        }
        if(indicate){
            if(pointer_res == NULL){
                pointer_res = calloc(1, sizeof(head));
            }
            pointer_res->str = ((int) temp + 1);
            pointer_res->next = NULL;
            pointer_res = pointer_res->next;
        }
        if(pointer_res == NULL){
            pointer_res = calloc(1, sizeof(head));
        }
        pointer_res->str = temp;
        pointer_res->next = NULL;
        pointer_res = pointer_res->next;

        pointer_head = pointer_head->next;
    } 
    return res;
}


/*
Если у некоторого элемента p в строке p->str записано текстовое десятичное представление 32-битного целого числа x, причем пробелы в начале допускаются, а в конце - нет, то перед каждым таким элементом в список добавляется новый элемент, у которого в строке записано десятичное представление числа x + 1, если оно представимо 32-битным целым знаковым значением. В текстовом представлении числа в новом элементе списка не должно быть пробелов, лишних знаков плюс и нулей.

Функция должна вернуть указатель на первый элемент получившегося списка.

Например, если в списке хранились строки "10" "5x" "alpha" " -03", то в результирующем списке должны храниться строки "11" "10" "5x" "alpha" "-2" " -03".
*/
