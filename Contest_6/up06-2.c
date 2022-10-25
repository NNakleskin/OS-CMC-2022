#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int
find_dot(char *buf);


int
find_doubledot(char *buf);


char*
find_slash(char *buf);


void
normalize_path(char *buf) {
    int len = strlen(buf);
    if(buf[len - 1] == '/') {
        buf[len - 1] = '\0';
        len--;
    }
}


int main(void) {
    char a[100];
    scanf("%s", a);
    normalize_path(a);
    printf("%d", a);
    return 0;
}