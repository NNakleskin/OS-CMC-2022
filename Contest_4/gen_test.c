#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};


struct Node *
gen_tree(int n, int32_t *arr)
{
    struct Node *head = calloc(n, sizeof(struct Node));
    for (int i = 0; i < n; i++) {
        head[i].key = 0;
        head[i].left_idx = 0;
        head[i].right_idx = 0;
    }
    head[0].key = arr[0];
    for (int i = 1; i < n; i++) {
        head[i].key = arr[i];
        struct Node *cur_node = &(head[0]);
        while(1) {
            if (head[i].key <= cur_node->key) {
                if (cur_node->left_idx == 0) {
                    cur_node->left_idx = i;
                    break;
                } else {
                    cur_node = &(head[cur_node->left_idx]);
                }
            } else if (head[i].key > cur_node->key) {
                if (cur_node->right_idx == 0) {
                    cur_node->right_idx = i;
                    break;
                } else {
                    cur_node = &(head[cur_node->right_idx]);
                }
            }
        }
    }
    return head;
}


void
print_tree(struct Node *head, int i) {
    if (head[i].left_idx != 0) {
        print_tree(head, head[i].left_idx);
    }
    printf("%d\n", head[i].key);
    if (head[i].right_idx != 0) {
        print_tree(head, head[i].right_idx);
    }
}


void
write_tree(int n, struct Node *head, int f_out)
{
    for (int i = 0; i < n; i++) {
        write(f_out, &(head[i]), sizeof(struct Node));
    }
}



int
main(int argc, char** argv)
{
    int n = 10;
    int arr[10] = {9988, -78, -100, 56, -787887, 0, 44, 42, 10, -100};
    int *din_arr = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        din_arr[i] = arr[i];
    }
    struct Node *head = gen_tree(n, din_arr);
    
    for (int i = 0; i < n; i++) {
        printf("%d : %d %d %d\n", i, head[i].key, head[i].left_idx, head[i].right_idx);
    }
    
    int f_out = open("test.bin", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
    write_tree(n, head, f_out);
    close(f_out);
    
    free(din_arr);
    free(head);
    return 0;
}




