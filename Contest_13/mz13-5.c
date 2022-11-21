#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    if(argc < 2) {
        return 0;
    }
    int p12[2];
    int p21[2];
    pipe(p12);
    pipe(p21);
    int num = 0;
    int n = (int) strtol(argv[1], NULL, 10);
    pid_t p1 = fork();
    pid_t p2 = fork();
    if(!p1) {
    } else if(!p2) {
    } else {
        write(p21[1], &num, sizeof(num));
    }
    while (1) {
        if(!p1) {
            read(p21[0], &num, sizeof(num));
            num++;
            if(num >= n) {
                write(p12[1], &n, sizeof(n));
                
                _exit(0);
            }
            printf("1 %d\n", num);
            fflush(stdout);
            write(p12[1], &num, sizeof(num));
        } else if(!p2) {
            read(p12[0], &num, sizeof(num));
            num++;
            if(num >= n) {   
                write(p21[1], &n, sizeof(n));
                wait(NULL);
                _exit(0);
            }
            printf("2 %d\n", num);
            fflush(stdout);
            write(p21[1], &num, sizeof(num));
        } else {
            break;
        }
    }
    while (wait(NULL) > 0) {}
    printf("Done\n");
    fflush(stdout);
    close(p12[0]);
    close(p12[1]);
    close(p21[0]);
    close(p21[1]);
    exit(0);
}
