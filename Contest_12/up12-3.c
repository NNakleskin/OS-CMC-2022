#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    int status = 0;
    pid_t p;
    for(int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case 's':
                while(wait(&status) > 0){
                    if(status != 0) { _exit(1); }
                }
                p = fork();
                if(p == -1) {
                    _exit(1);
                } else if(!p) {
                    execlp(&argv[i][1], &argv[i][1], NULL);
                    _exit(1);
                }
                wait(&status);
                if(status != 0) {
                    _exit(1);
                }
                break;
            case 'p':
                p = fork();
                if(p == -1) {
                    _exit(1);
                }
                if(!p) {
                    execlp(&argv[i][1], &argv[i][1], NULL);
                    _exit(1);
                }
                break;
            default:
                while(wait(NULL) > 0) {}
                return 1;
        }
    }
    while(wait(NULL) > 0) {}
    _exit(0);
}
