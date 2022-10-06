#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "up03-5.c"


extern struct Elem *dup_elem(struct Elem *head);


int main(void)
{
    struct Elem *head = calloc(1, sizeof(struct Elem));
    struct Elem *temp = head;
    char *a[] = {"10", "5x", "alph", "-03", "hyi"};

    for(int i = 0; i < 5; i++)
    {
        if(temp == NULL)
        {
            temp = calloc(1, sizeof(head));
        }
        temp->str = a[i];
        temp->next = NULL;
        temp = temp->next;
    }
    struct Elem *res;
    res = dup_elem(head);

    while(res != NULL){
        printf("%s\n", res->str);
        res = res->next;
    }
    
    free(res);
    free(head);
    free(temp);
    return 0;
}
