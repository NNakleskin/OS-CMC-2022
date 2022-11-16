#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    if(argc < 2) {
        return 1;
    }
    int offset = 0;
    char path[] = "/tmp/res.py";
    int fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0755);
    char buf[] = "print(";
    pwrite(fd, buf, sizeof(buf), 0);
    offset += strlen(buf);
    for(int i = 1; i < argc; ++i) {
        size_t len = strlen(argv[i]);
        pwrite(fd, argv[i], len, offset);
        offset += len;
        if(i == argc - 1) {
            pwrite(fd, ")\n\0", 3, offset);
            break;
        }
        pwrite(fd, " * ", 3, offset);
        offset += 3;
    }
    close(fd);
    pid_t p = fork();
    if(p < 0) { _exit(1); }
    if(p == 0) {
        execlp("python3", "python3", path, NULL);
        _exit(1);
    }
    wait(NULL);
    execlp("rm", "rm", path, NULL);
    _exit(1);
    return 0;
}
