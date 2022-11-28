#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>


int count = 0;


void handler() {
    if(count < 5) {
        printf("%d\n", count);
        fflush(stdout);
        count++;
        return;
    } else {
        _exit(0);
    }
}



int main(void) {
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    pid_t pid = getpid();
    printf("%lld\n", (long long) pid);
    fflush(stdout);
    while(1) { 
        pause();
    }
    _exit(0);
}
