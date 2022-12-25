#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>


volatile char buf_outp = 0;


void handler(int sig) {
    if(sig ==SIGUSR1) {

    } else if(sig == SIGUSR2) {

    } else if(sig == SIGALRM) {

    } else if(sig == SIGIO) {
        exit(EXIT_SUCCESS);
    }
}



int main(int argc, char **argv) {
    sigaction(SIGUSR1, &(struct sigaction) {.sa_handler = handler, .sa_flags 
            = SA_RESTART}, NULL);
    sigaction(SIGUSR2, &(struct sigaction) {.sa_handler = handler, .sa_flags 
            = SA_RESTART}, NULL);
    sigaction(SIGALRM, &(struct sigaction) {.sa_handler = handler, .sa_flags 
            = SA_RESTART}, NULL);
    sigaction(SIGIO, &(struct sigaction) {.sa_handler = handler, .sa_flags 
            = SA_RESTART}, NULL);
    if(argc < 2) { exit(EXIT_FAILURE); }
    pid_t p = fork();
    if(p < 0) { exit(EXIT_FAILURE); }
    if(!p) {
        //  First son
    } else {
        p = fork();
        if(p < 0) { exit(EXIT_FAILURE); }
        if(!p) {
            // Second son
            int fd = open(argv[1], O_RDONLY);
            char buf;
            while(read(fd, &buf, 1) > 0) {
                
                for(int i = 0; i < CHAR_BIT; i++) {
                    char bit = (char) (buf << i) >> CHAR_BIT;
                    printf("%d\n", bit);
                }
            }
            close(fd);
            exit(EXIT_SUCCESS);
        }
    }
    while(wait(NULL) > 0);
    return 0;
}

