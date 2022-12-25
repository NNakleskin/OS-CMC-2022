#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#include <limits.h>
    

int main(void) {
    pid_t parent = getpid();
    pid_t p;
    int pd[2];
    pipe(pd);
    int n;
    scanf("%d", &n);
    write(pd[1], &n, sizeof(n));
    printf("%d %d\n", parent, n);
    while(read(pd[0], &n, sizeof(n)) != -1) {
        pipe(pd);
        while(wait(NULL) > 0) {}
        while(n > 0) {
            p = fork();
            if(!p){
                n--;
                continue;
            }
            close(pd[1]);
            while(wait(NULL) > 0) {}
            close(pd[0]);
            close(pd[1]);
            if(getpid() != parent) { 
                exit(EXIT_SUCCESS);
            }
        }
        if(!p) {
            if(scanf("%d", &n) != 1) {
                close(pd[1]);
                close(pd[0]);
            }
            printf("%d %d\n", getpid(), n);
            write(pd[1], &n, sizeof(n));
            close(pd[0]);
            close(pd[1]);
            _exit(EXIT_SUCCESS);
            }
        }
    return 0;
}

