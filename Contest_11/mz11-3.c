#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
    pid_t p1 = fork();

    if (p1 == 0) {
        char num1[9];
        read(STDIN_FILENO, num1, sizeof(num1) - 1);
        int n = (int)strtoll(num1, NULL, 10);
        printf("1 %d\n", n * n);
        exit(0);
    }

    pid_t p2 = fork();

    if (p2 == 0) {
        char num2[9];
        read(STDIN_FILENO, num2, sizeof(num2) - 1);
        int n = (int)strtoll(num2, NULL, 10);
        printf("2 %d\n", n * n);
        exit(0);
    }

    pid_t p3 = fork();

    if(p3 == 0) {
        char num3[9];
        read(STDIN_FILENO, num3, sizeof(num3) - 1);
        int n = (int)strtol(num3, NULL, 10);
        printf("3 %d\n", n * n);
        exit(0);
    }
    
    wait(&p1);
    wait(&p2);
    wait(&p2);

    return 0;
}
