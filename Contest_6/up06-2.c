#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int
find_dot(char *buf) {
    if(*buf == '.' && *(buf - 1) == '/') {
        return 1;
    }
    return 0;
}


int
find_doubledot(char *buf){
    if(*buf == '.' && *(buf - 1) == '.' && *(buf - 2) == '/') {
        return 1;
    }
    return 0;
}


char*
find_slash(char *buf) {
    while(*buf != '/') {
        *buf = *(buf - 1);
    }
    return buf;
}


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
    printf("%s", a);
    return 0;
}