#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


volatile int count = 0;
volatile int num = 0;


int max(int f_num, int s_num) {
    return f_num > s_num ? f_num : s_num;
}


void handler_1() {
    signal(SIGINT, handler_1);
    if (count < 3) {
        printf("%d\n", num);
        fflush(stdout);
        ++count;
    } else {
        _exit(EXIT_SUCCESS);
    }
}


void handler_2() {
    _exit(EXIT_SUCCESS);
}


int 
main(int argc, char **argv) { 
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler_1, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = handler_2, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int low, high;
    scanf("%d%d", &low, &high);
    for (int i = low; i < high; ++i) {
        int indicate = 1;
        if(i < 2) { continue; }
        for(int j = 2; j * j <= i; ++j) {
            if(!(i % j)) {
                indicate = 0;
            }
        }
        if(indicate) {
            num = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    _exit(EXIT_SUCCESS);
}
