#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/stat.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {

        return 1;
    }
    long long res = 0;
    for(int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY, 0666);
        if(fd == -1){
            return 1;
        }
        struct stat buf;
        if(fstat(fd, &buf) == -1){
            return 1;
        }
        if(buf.st_nlink == 1 && S_ISREG(buf.st_mode) == 1 
                && S_ISLNK(buf.st_mode) == 0 && buf.st_size % 1024 == 0){
            res += buf.st_size;
        }
        if(close(fd) == -1){
            return -1;
        }
    }
    printf("%lld\n", res);
    return 0;
}
