#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    pid_t p;
    int n = 0;
    while(scanf("%d", &n) != EOF) {
        p = fork();
        if(p == -1) {
            printf("-1\n");
            return 0;
        }
        if(p == 0) {
            continue;
        }
        wait(&p);
        printf("%d\n", n);
        exit(0);
    }
    return 0;
}

