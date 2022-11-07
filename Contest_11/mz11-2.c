#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(void) {
    pid_t p = fork();

    if (p == 0) {
        pid_t p = fork();
        if(p == 0) { 
            printf("3 "); 
            exit(0);
        }
        wait(&p);
        printf("2 ");
        exit(0);
    }
    wait(&p);
    printf("1\n");
    return 0;
}
