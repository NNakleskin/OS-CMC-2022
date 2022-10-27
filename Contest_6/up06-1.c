#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


const char exe[] = ".exe";


int
is_exe(char *path, size_t len) {
    int index = len - sizeof(exe);
    if(index < 0) {
        return 0;
    }
    if(strcmp(&path[index], exe)) {
        return 0;
    }
    return 1;
}



int main(int argc, char** argv)
{
    if (argc < 2) {
        return 0;
    }
    DIR *dir = opendir(argv[1]);
    size_t path_len = strlen(argv[1]);
    if(dir == NULL) {
        return 1;
    }
    struct dirent *de = NULL;
    de = readdir(dir);
    int count = 0;
    while(de){
        size_t tmp_len = path_len + strlen(de->d_name) + 2;
        char *path;
        asprintf(&path, "%s/%s", argv[1], de->d_name);        
        struct stat buf;
        if (stat(path, &buf) < 0) {
            free(path);
            de = readdir(dir);
            continue;
        }
        if(is_exe(path, tmp_len) && S_ISREG(buf.st_mode) && access(path, X_OK) == 0) {
            count++;
        }
        free(path);
        de = readdir(dir);
    }
    closedir(dir);
    printf("%d\n", count);
    return 0;
}
