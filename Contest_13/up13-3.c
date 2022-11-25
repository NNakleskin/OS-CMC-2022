#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



int main(int argc, char **argv) {
    if(argc < 6) { _exit(EXIT_FAILURE); }
    char *cmd1 = argv[1];
    char *cmd2 = argv[2];
    char *cmd3 = argv[3];
    int fd1 = open(argv[4], O_WRONLY);
    if(fd1 == -1) { _exit(EXIT_FAILURE); }
    int fd2 = open(argv[5], O_APPEND | O_CREAT | O_RDONLY, 0777);
    if(fd2 == -1) { _exit(EXIT_FAILURE); }
    pid_t p = fork();
    int pipeline[2];
    if(pipe(pipeline) < 0) { _exit(EXIT_FAILURE); }
    pipeline[1] 
    if(p == -1) { _exit(EXIT_FAILURE); }
    if(p == 0) {
        du
    }

    

    return 0;
}
