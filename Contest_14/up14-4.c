#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


void handler(){
    
}


int main(void) {
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, 
            .sa_flags = SA_RESTART}, NULL);
    int pip[2];
    pipe(pip);

    
    pid_t p = fork();
    if(p < 0) {
        exit(EXIT_FAILURE);
    } else if(!p) {
        
    } else {
        
    }
    
    return 0;
}
