#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(void) {
    int fd[2];
    pipe(fd);
    int read_pipe = fd[0], write_pipe = fd[1];
    pid_t p1 = fork();
    time_t n;
    struct tm day;
    if(p1 == 0) {
        pid_t p2 = fork();
        if(p2 == 0) {
            pid_t p3 = fork();
            if(p3 == 0) {
                time_t now = time(NULL);
                for(int i = 0; i < 3; i++) {
                    write(write_pipe, &now, sizeof(now));
                }
                _exit(0);
            }
            wait(NULL);
            read(read_pipe, &n, sizeof(time_t));
            localtime_r(&n, &day);
            printf("D:%02d\n", day.tm_mday);
            fflush(stdout);
            _exit(0);
        }
        wait(NULL);
        read(read_pipe, &n, sizeof(time_t));
        localtime_r(&n, &day);
        printf("M:%02d\n", day.tm_mon + 1);
        fflush(stdout);
        _exit(0);
    }
    wait(NULL);
    read(read_pipe, &n, sizeof(time_t));
    localtime_r(&n, &day);
    printf("Y:%04d\n", day.tm_year + 1900);
    fflush(stdout);    
    return 0;
}
