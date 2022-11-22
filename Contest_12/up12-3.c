#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int status = 0;
    pid_t p;
    int count = 0;
    for(int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case 's':
                while(wait(&status) > 0){
                    count += (!WEXITSTATUS(status) && WIFEXITED(status));
                }
                p = fork();
                if(p == -1) {
                    _exit(EXIT_FAILURE);
                } else if(!p) {
                    execlp(&argv[i][1], &argv[i][1], NULL);
                    _exit(EXIT_FAILURE);
                }
                wait(&status);
                count += (!WEXITSTATUS(status) && WIFEXITED(status));     
                break;
            case 'p':
                p = fork();
                if(p == -1) {
                    _exit(EXIT_FAILURE);
                }
                if(!p) {
                    execlp(&argv[i][1], &argv[i][1], NULL);
                    _exit(EXIT_FAILURE);
                }
                break;
            default:
                while(wait(NULL) > 0) {}
                _exit(EXIT_FAILURE);
        }
    }
    while(wait(&status) > 0) {
        count += (!WEXITSTATUS(status) && WIFEXITED(status));        
    }
    printf("%d\n", count);
    fflush(stdout);
    _exit(EXIT_SUCCESS);
}