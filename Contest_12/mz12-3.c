#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdbool.h>


int my_exec(char *bin) {
    pid_t p = fork();
    if(p < 0) {
        return 1;
    } else if(p == 0) {
        execlp(bin, bin, NULL);
        _exit(1);
    } 
    int status;
    wait(&status);
    return  WIFEXITED(status) ? (!WEXITSTATUS(status)):false;
}


int main(int argc, char **argv) {
    return !((!my_exec(argv[1]) ? my_exec(argv[2]) : true)
            ? my_exec(argv[3]) : false);
}
