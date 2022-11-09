#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    pid_t p;
    int n;
    scanf("%d", &n);
    int num = n - 1;
    while(num > 0) {
        p = fork();
        if(p == 0) {
            num--;
            continue;
        }
        wait(&p);
        printf("%d\n", num);
        break;
    }
    return 0;
}

