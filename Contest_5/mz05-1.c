#include <stdio.h>
#include <sys/stat.h>


off_t fsize(char *file) {
    struct stat filestat;
    if (stat(file, &filestat) == 0) {
        return filestat.st_size;
    }
    return 0;
}


int main(int argc, char **argv)
{
    if(argc < 2){
        return 1;
    }
    FILE* file = fopen("test.txt", "r");
    printf("%lld\n", fsize((char *)file));
    return 0;
}
