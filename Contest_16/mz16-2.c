#include <stdio.h>
#include <stdlib.h>

enum Constants { N_MAX = 1048576, N_MIN = 8 };


int main(void) {
    int n;
    scanf("%d", &n);
    int *array = calloc(n, sizeof(int));
    if(n < N_MIN || n > N_MAX) {
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n - 4; ++i) {
        scanf("%d", &array[i]);
    }
    int num;
    while(scanf("%d", &num) != EOF) {
        int count = 0;
        while(array[num - 2] && num < n - 2) {
            num = array[num - 2];
            count++;
        }
        printf("%d\n", count);
    }
    exit(EXIT_SUCCESS);
}
