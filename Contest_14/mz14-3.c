#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>



int count = 0;


int main(int argc, char **argv) {
    int n;
    n = strtol(argv[1], NULL, 10);
    for(int i = 2; i < n + 2 && i < argc; ++i) {
        FILE *input = fopen(argv[i], "r");
        char buf[PATH_MAX + 1];
        fscanf(input, "%s", buf);
        int len = strlen(buf);
        buf[len] = '\0';
        pid_t p = fork();
        if(!p) {
            execlp(buf, buf, NULL);
            _exit(1);
        }
    }
    int status;
    while(wait(&status) > 0) {
        count += !WEXITSTATUS(status) && WIFEXITED(status);
    }
    for(int i = n + 2; i < argc; i++) {
        FILE *input = fopen(argv[i], "r");
        char buf[PATH_MAX + 1];
        fscanf(input, "%s", buf);
        int len = strlen(buf);
        buf[len] = '\0';
        pid_t p = fork();
        if(!p) {
            execlp(buf, buf, NULL);
            _exit(1);
        }
        int status;
        wait(&status);
        count += !WEXITSTATUS(status) && WIFEXITED(status);
    }
    printf("%d\n", count);
    fflush(stdout);
    exit(0);
}
