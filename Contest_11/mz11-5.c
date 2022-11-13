#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    pid_t p;
    int n = 0;
    int ret_value = 0;
    p = fork();
    if(p == 0) {
        while(scanf("%d", &n) != EOF) {
            p = fork();
            if(p == -1) {
                _exit(EXIT_FAILURE);
            } else if(p == 0) {
                continue;
            }
            wait(&ret_value);
            if(WEXITSTATUS(ret_value) == EXIT_FAILURE) { 
                _exit(EXIT_FAILURE);
            }
            fflush(stdout);
            printf("%d\n", n);
            _exit(EXIT_SUCCESS);
        }
    }
    wait(&ret_value);
    if(WEXITSTATUS(ret_value) == EXIT_FAILURE) {
        printf("-1\n");
        fflush(stdout);
    }
    _exit(EXIT_SUCCESS);  
} 

