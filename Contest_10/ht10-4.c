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


struct Funcstack *buf_generate(char *signature, char **params, size_t count_params) {
    struct Funcstack *stack = calloc(1, sizeof(struct Funcstack));
    size_t offset = 0;
    for(int i = 0; i < count_params; i++) {
        if(signature[i] == 'i') {
            errno = 0;
            //int tmp = (int) strtol(params[i], NULL, 10);
            if(errno != 0) {
                _exit(1);
            }
            char *tmp = params[i];
            //stack->tmp[offset] = tmp;
            //*(int *) &stack->tmp[offset] = tmp; 
            memcpy(&stack->tmp[offset], tmp, strlen(tmp));   
            offset += strlen(tmp) - 1;
        } else if(signature[i] == 'd') {
            errno = 0;
            double tmp = strtod(params[i], NULL);
            //if(errno != 0) {
            //    _exit(1);
            //}
            //char *tmp = params[i];
            //*(double*) &stack->tmp[offset] = tmp;    
            memcpy(&stack->tmp[offset], tmp, strlen(tmp));    
            //stack->tmp[offset] = tmp;  
            offset += strlen((str)tmp) - 1;
        } else if(signature[i] == 's') {
            char *tmp = params[i];
            memcpy(&stack->tmp[offset], tmp, strlen(tmp));
            //stack->tmp[offset] = tmp;
            offset += strlen(tmp) - 1;
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
    struct Funcstack *stack = buf_generate((argv[3] + 1), &(argv[4]), argc - 4);
    if(argv[3][0] == 'v') {
       ((void (*)(struct Funcstack*)) func)(stack);
    } else if(argv[3][0] == 'i') {
        
    } else if(argv[3][0] == 'd') {
            
    } else if(argv[3][0] == 's') {
            
    }   
    return 0;
}
