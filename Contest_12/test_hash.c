#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

void rand_string(char *str, size_t size)
{
    srand(time(NULL));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK1234567890-.,?!#$%^&*()+={}[]|~`<>_@";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
}


int main(int argc, char **argv) {
    long len = 30;
    for(int i = 0; i < argc; i++)
        switch (argv[i][1]) {
            case 'l':
                if(i + 1 == argc) {
                    printf("Missing argument");
                    fflush(stdout);
                    return 1;
                }
                errno = 0;
                len = strtol(argv[i + 1], NULL, 10);
                if(errno != 0) {
                    printf("Failed to parce a number");
                    fflush(stdout);
                    return 0;
                }
                break;
        } 
    char *tmp = calloc(len + 2, sizeof(char));
    rand_string(tmp, len + 1);
    printf("%s\n", tmp);
    fflush(stdout);
    free(tmp);
    return 0;
}
