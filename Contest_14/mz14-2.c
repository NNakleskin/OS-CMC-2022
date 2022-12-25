#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


int indicate = 0;
unsigned int res = 0;


void handler_1() {
    indicate = 0;
}


void handler_2() {
    indicate = 1;
}



int main(void) {
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler_1, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGQUIT, &(struct sigaction) { .sa_handler = handler_2, .sa_flags = SA_RESTART }, NULL);
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);
    int n;
    indicate = 0;
    res = 0;
    while(scanf("%d", &n) == 1) {
        if(!indicate) {
            res += (unsigned int) n;
            printf("%d\n", (int) res);
            fflush(stdout);
        } else if(indicate) {
            res *= (unsigned int) n;
            printf("%d\n", (int) res);
            fflush(stdout);
        }
    }
    _exit(0);
}
