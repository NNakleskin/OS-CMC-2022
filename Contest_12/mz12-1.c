#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    pid_t p = fork();
    if(p < 0) {
        _exit(42);
    }
    if(p == 0) {
        int fd1 = open(argv[2], O_RDONLY, 0660);
        int fd2 = open(argv[3], O_CREAT | O_WRONLY | O_APPEND, 0660);
        int fd3 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0660);
        if(fd1 < 0 || fd2 < 0 || fd3 < 0) {
            _exit(42);
        }
        if(dup2(fd1, STDIN_FILENO) < 0 || dup2(fd2, STDOUT_FILENO) < 0 
                || dup2(fd3, STDERR_FILENO) < 0) {
            _exit(42);
        }
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    } else {
        int status = EXIT_SUCCESS;
        wait(&status);
        printf("%d\n", status);
    }
    return 0;
}
