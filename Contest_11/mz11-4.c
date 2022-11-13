#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    pid_t p, id = getpid();
    int n;
    scanf("%d", &n);
    while(n > 0) {
        p = fork();
        if(p == 0) {
            n--;
            continue;
        }
        wait(&p);
        printf("%d", n);
        if(getpid() == id) { putchar(10); } else { putchar(' '); }
        exit(0);
    }
    return 0;
}

