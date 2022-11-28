#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

unsigned count = 0;
int num = 0;


void 
handler(int sig)
{
    switch (sig) {
        case SIGINT:
            if (count < 3) {
                printf("%d\n", num);
                fflush(stdout);
                ++count;
                return;
            } else {
                exit(EXIT_SUCCESS);
            }
            break;
        case SIGTERM:
            exit(EXIT_SUCCESS);
        default: {}
    }
}


int 
main(void) {
    int low, high;
    scanf("%d%d", &low, &high);
    sigaction(SIGINT, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    sigaction (SIGTERM, &(struct sigaction) {.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    for (int i = low; i < high; ++i) {
        int indicate = 1;
        for(int j = 2; j <= i / 2; ++j) {
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
    exit(EXIT_SUCCESS);
}
