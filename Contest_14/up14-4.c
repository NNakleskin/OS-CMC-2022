#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


int piped[2];
int pid;
int num;


void handler(int n)
{
    read(piped[0], &num, sizeof(num));
    num++;
    if(num >= n) {
        write(piped[1], &n, sizeof(n));
        _exit(EXIT_SUCCESS);
    }
    printf("2 %d\n", num);
    fflush(stdout);
    write(piped[1], &num, sizeof(num));
    kill(pid, SIGUSR1);
}


int main(int argc, char **argv) {
    if(argc < 2) {
        return EXIT_FAILURE;
    }
    pipe(piped);
    sigaction(SIGUSR1, &(struct sigaction){ .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    int num = 0;
    int n = (int) strtol(argv[1], NULL, 10);
    if(n == 0) {}
    write(piped[1], &num, sizeof(num));
    pid_t p1 = fork();
    if(p1 == -1) { _exit(EXIT_FAILURE); }
    pid_t p2;
    if(!p1) {
    } else {
        p2 = fork();
        if(p2 == -1) { _exit(EXIT_FAILURE); }
    }
    while (1) {
        if(!p1) {
            read(piped[0], &num, sizeof(num));
            num++;
            if(num >= n) {   
                write(piped[1], &n, sizeof(n));
                _exit(EXIT_SUCCESS);
            }
            printf("1 %d\n", num);
            fflush(stdout);
            write(piped[1], &num, sizeof(num));
            kill(pid, SIGUSR1);
            while (1) pause();
        } else if(!p2) {

            pid = getpid();
            while(1) { pause(); };
        } else {
            break;
        }
    }
    while (wait(NULL) > 0) {}
    printf("Done\n");
    fflush(stdout);
    close(piped[0]);
    close(piped[1]);
    exit(EXIT_SUCCESS);
}
