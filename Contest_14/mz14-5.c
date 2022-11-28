#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


int count = 0;
int n;


void simple() {
    for(int i = 0; i < n; ++i) {
        int j = 2, k = 1;
        while(i * j <= i) {
            if(i % j == 0) {
                k == 0;
                break;
            }
            j++;
            if(k) {
                n = i;
            }
        }
    }

}


void handler(int sig) {
    if(sig == SIGTERM) {
        _exit(0);
    }
    if(sig == SIGINT) {
        if(count  < 3) {
            printf("%d\n", n);
            fflush(stdout);
            break;
        }
    }
    

}


int main(void) {
    sigaction(SIGTERM, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    int low, high;
    scanf("%d%d", &low, &high);
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(stdout);

    printf("-1\n");    
    fflush(stdout);
    _exit(0);
}
