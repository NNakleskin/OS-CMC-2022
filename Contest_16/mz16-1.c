#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {
    int *mem = calloc(100, sizeof(int));
    char x[] = "000d";
    int n = strtol(x, NULL, 16);
    printf("%d\n", n);
    return 0;
}
