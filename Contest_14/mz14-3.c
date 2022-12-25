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

void process(char *filename)
{
    FILE *input = fopen(filename, "r");
    char buf[PATH_MAX + 1];
    int i = 0;
    while (fscanf(input, "%s", buf) == 1 && i < PATH_MAX + 1){
        i++;
    }
    pid_t p = fork();
    fclose(input);
    if (!p){
        execlp(buf, buf, NULL);
        _exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    int count = 0;
    int n;
    n = strtol(argv[1], NULL, 10);
    for (int i = 2; i < n + 2 && i < argc; ++i){
        process(argv[i]);
    }
    int status;
    while (wait(&status) > 0){
        count += !WEXITSTATUS(status) && WIFEXITED(status);
    }
    for (int i = n + 2; i < argc; i++){
        process(argv[i]);
        int status;
        wait(&status);
        count += !WEXITSTATUS(status) && WIFEXITED(status);
    }
    printf("%d\n", count);
    fflush(stdout);
    exit(EXIT_SUCCESS);
}
