#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


int
is_dot(char *buf) {
    if(*buf == '.' && *(buf - 1) == '/') {
        return 1;
    }
    return 0;
}


int
is_doubledot(char *buf){
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
    int doubledot_count = 0;
    int len = strlen(buf);
    if(buf[len - 1] == '/') {
        buf[len - 1] = '\0';
        len--;
    }
    for(int i = len - 1; i > 1; ++i) {
        if(i > 2) {
            if(is_doubledot(buf[i]) {
                doubledot_count++;
                i -= 3;
            } else if (is_dot(buf[i])) {
                i -= 2;
            } 
       }
    }
}


int main(void) {
    char a[PATH_MAX];
    scanf("%s", a);
    normalize_path(a);
    printf("%s", a);
    return 0;
}
