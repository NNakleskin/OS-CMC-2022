#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#include <limits.h>


#define _GNU_SOURCE 1


int main(int argc, char **argv) {
    if(argc < 4) { exit(EXIT_FAILURE); }
    pid_t p1, p2, p3;
    int fd1, fd2[2];
    pipe(fd2);
    fd1 = open(argv[2], O_RDONLY);
    p1 = fork();
    if(!p1) {
        dup2(fd1, STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);
        _exit(EXIT_FAILURE);
    }
    close(fd1);
    close(fd2[1]);
    p2 = fork();
    if(!p2) {
        dup2(fd2[0], STDIN_FILENO);
        execlp(argv[3], argv[3], NULL);
        _exit(EXIT_FAILURE);
    }
    close(fd2[0]);
    int status1, status2;
    waitpid(p1, &status1, 0);
    waitpid(p2, &status2, 0);
    p3 = fork();
    if(!p3) {
        execlp(argv[4], argv[4], NULL);
        _exit(EXIT_FAILURE);
    }
    waitpid(p3, NULL, 0);    
    return 0;
}
