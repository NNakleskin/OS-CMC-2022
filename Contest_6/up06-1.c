#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char** argv)
{
    DIR *dir = opendir(argv[1]);
    if(dir == NULL)
    {
        perror("opendir");
        return 0;
    }
    struct dirent *de;
    de = readdir(dir);
    while(de){

        char path[100];
        strcpy(path, argv[1]);
        strncat(path, "/", 1);
        strncat(path, de->d_name, strlen(de->d_name));
        printf("%s\n", path); 
        struct stat buf;
        lstat(path, &buf);
        printf("size %lld\n", buf.st_size);
        printf("reg %d\n", S_ISREG(buf.st_mode));
        de = readdir(dir);
    }
    
    return 0;
}
