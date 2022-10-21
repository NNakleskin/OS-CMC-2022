#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>


struct FileInfo {
    char *path;
    unsigned long ino;
    int dev;
};


int main(int argc, char **argv)
{
    if(argc < 2){
        return 0;
    }
    struct FileInfo *arr = malloc(argc * sizeof(struct FileInfo));



    for(int i = 1; i < argc; i++){
        struct stat buf;
        if(lstat(argv[i], &buf) == -1){
            continue;
        }
        for(int j = 0; j < argc; j++)
        {
            if(arr[j] == NULL){
                arr[j].path = (char *) argv[i];
                arr[j].ino = buf.st_ino;
                arr[j].dev = buf.st_dev;
                break;
            }
            if(arr[j].ino ==  buf.st_ino  && strcmp(buf.path, argv[i]) > 0) {   
                arr[j].path = argv[i];
            }   
        }
        
    }

    return 0;
}
