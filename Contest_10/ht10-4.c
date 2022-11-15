#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>


struct Funcstack {
    char tmp[64];
};


struct Funcstack buf_generate(char *signature, char **params, size_t count_params) {
    struct Funcstack stack;
    size_t offset = 0;
    for(int i = 0; i < count_params; i++) {
        if(signature[i] == 'i') {
            errno = 0;
            int tmp = (int) strtol(params[i], NULL, 10);
            if(errno != 0) {
                _exit(1);
            }
            *(int *) &stack.tmp[offset] = tmp; 
            offset += sizeof(tmp);
        } else if(signature[i] == 'd') {
            errno = 0;
            double tmp = strtod(params[i], NULL);
            if(errno != 0) {
                _exit(1);
            }
            *(double*) &stack.tmp[offset] = tmp;         
            offset += sizeof(tmp);
        } else if(signature[i] == 's') {
            char *tmp = params[i];
            *(char **) &stack.tmp[offset] = tmp;
            offset += sizeof(tmp);
        } 
    }
    return stack;
}


int main(int argc, char **argv) {
    if(argc < 3) {
        return 1;
    }
    void *lib = dlopen(argv[1], RTLD_LAZY);
    if (lib == NULL) {
        perror(dlerror());
        return 1;
    }
    void *func = dlsym(lib, argv[2]);
    dlclose(lib);
    if(func == NULL) {
        perror("Function import error");
        return 1;
    }
    struct Funcstack stack = buf_generate((argv[3] + 1), &(argv[4]), argc - 4);
    if(argv[3][0] == 'v') {
       ((void (*)(struct Funcstack)) func)(stack);
    } else if(argv[3][0] == 'i') {
        int res = ((int (*)(struct Funcstack)) func)(stack);
        printf("%d\n", res);
    } else if(argv[3][0] == 'd') {
        double res = ((double (*)(struct Funcstack)) func)(stack);
        printf("%.10g\n", res);
    } else if(argv[3][0] == 's') {
        char *res = ((char *(*)(struct Funcstack)) func)(stack);
        printf("%s\n", res);
    }   
    return 0;
}
