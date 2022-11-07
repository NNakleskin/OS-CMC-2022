#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


void reverse() {
    int num;
    if(scanf("%d", &num) != EOF) {
        pid_t p = fork();
        reverse();
        wait(&p);
        printf("%d\n", num);
        return;
    }
    //printf("%d\n", num);
    return;
}


int main(void) {
    reverse();
    return 0;
}
