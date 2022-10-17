#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/stat.h>

int main(int argc, char** argv)
{
    unsigned long long res = 0;
    for(int i = 1; i < argc; i++)
    {
        struct stat buf;
        if(lstat(argv[i], &buf) == -1){
            continue;
        }
        if(buf.st_nlink == 1 && S_ISREG(buf.st_mode) == 1 
                && S_ISLNK(buf.st_mode) == 0 && buf.st_size % 1024 == 0){
            res += buf.st_size;
        }
    }
    printf("%llu\n", res);
    return 0;
}
