#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>


struct Funcstack {
    char tmp[64];
};


void buf_generate(char *signature, char **params, struct Funcstack *stack, int count_params) {
    size_t offset = 0;
    for(int i = 0; i < count_params; i++) {
        if(signature[i] == 'i') {
            errno = 0;
            int tmp = (int) strtol(params[i], NULL, 10);
            if(errno != 0) {
                _exit(1);
            }
            memcpy((stack->tmp + offset), &tmp, sizeof(tmp));
            offset += sizeof(tmp);
        } else if(signature[i] == 'd') {
            errno = 0;
            double tmp = strtod(params[i], NULL);
            if(errno != 0) {
                _exit(1);
            }
            memcpy((stack->tmp + offset), &tmp, sizeof(tmp));
            offset += tmp;
        } else if(signature[i] == 's') {
            memcpy((stack->tmp + offset), params[i],
                    strlen(params[i]) * sizeof(char));
            offset += strlen(params[i]) * sizeof(char);
        } 
    }
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
    struct Funcstack stack;
    buf_generate((argv[3] + 1), (argv + 4), &stack, argc - 4);
    for(int i = 4; i < argc; i++) {
        if(argv[3][0] == 'v') {
            ((void (*)(struct Funcstack)) func)(stack);
        } else if(argv[3][0] == 'i') {
            
        } else if(argv[3][0] == 'd') {
            
        } else if(argv[3][0] == 's') {
            
        }
    }
    

    return 0;
}
