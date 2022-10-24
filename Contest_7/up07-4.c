#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY, 0666);
    if(fd == -1) {
        return 1;
    }
    struct stat buf;
    if(fstat(fd, &buf) == -1) {
        return 1;
    }
    off_t size =  buf.st_size;
    long long x;
    while(scanf("%lld", &x) != EOF) {
        if(x < 0) {
            
        } else {
            if(fseek(fd, x/8, SET_CUR) == -1) {
                continue;
            }

        }
        int
        read(fd, )
    }
    return 0;
}
