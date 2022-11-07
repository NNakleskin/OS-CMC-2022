#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    int num = 1;
    pid_t p;
    int n;
    scanf("%d", &n);
    p = fork();
    while(num < n) {
        num += 1;
        p = fork();
       // printf("%d\n", num - 1);
        if(p == 0) {
            break;
        } else {
            printf("%d\n", num);
        }
    }
    return 0;
}

