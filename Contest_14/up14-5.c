#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

volatile long long count = 0;
volatile long long num = 0;


void 
handler(int sig)
{
    switch (sig) {
        case SIGINT:
            if (count < 3) {
                printf("%lld\n", num);
                fflush(stdout);
                ++count;
                return;
            } else {
                exit(EXIT_SUCCESS);
            }
            break;
        case SIGTERM:
            exit(EXIT_SUCCESS);
            break;
        default: {}
    }
}


int 
main(void) {
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    long long low, high;
    scanf("%lld%lld", &low, &high);
    printf("%d\n", getpid());
    fflush(stdout);
    for (int i = low; i < high; ++i) {
        if(i < 2) { continue; }
        for(int j = 2; j <= i / 2; ++j) {
            if(!(i % j)) {
                continue;
            }
        }
        num = i;
    }
    printf("-1\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}
