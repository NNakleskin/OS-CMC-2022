#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <limits.h>


int main(void) {
    int p[2];
    if(pipe(p) == -1) { _exit(EXIT_FAILURE); } 
    int n = 0;
    pid_t p_grandson;
    pid_t p_son = fork();
    if(p_son == -1) { _exit(EXIT_FAILURE); }
    if(p_son == 0) {
        p_grandson = fork();
        if(p_grandson == -1) { _exit(EXIT_FAILURE); }
        if(p_grandson == 0) {
            long long sum = 0;
            close(p[1]);
            while(read(p[0], &n, sizeof(n)) > 0) {
                sum += n;
            }
            close(p[0]);
            printf("%lld\n", sum);
            fflush(stdout);
            _exit(EXIT_SUCCESS);
        } else {
            close(p[0]);
            close(p[1]);
            wait(NULL);
            _exit(EXIT_SUCCESS);
        }
    } else {
        close(p[0]);
        while(scanf("%d", &n) != EOF) {
            write(p[1], &n, sizeof(n));
        }
        close(p[1]);
        while (wait(NULL) > 0) { }
        _exit(EXIT_SUCCESS);
    }
    _exit(EXIT_SUCCESS);
}

