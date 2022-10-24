#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
void 
normalize_path(char *buf){
    int len = strlen(buf);
    int count = 0;
    if(len == 1) {
        buf[0] = '/';
        return;
    }
    if(buf[len - 1] == '/') {
        buf[len - 1] = '\0';
    }
    for(int i = len - 1; i > 1; --i){
        if(buf[i] == '.' && buf[i - 1] == '.'){
            count++;
        }
    }
    int count_slash = 0;
    for(int i = 0; i < len; i++) {
        if(buf[i] == '/') {
            count_slash++;
        }
    }
    if(count_slash - 2 * count < 0) {
        buf[0] = '/';
        buf[1] = '\0';  
        return;
    }
    if(count == 0) {
        return;
    }
    count = count_slash - count - 1;
    int i = 0;
    printf("%d\n", count);
    while(count != 0) {
        if(buf[i] == '/') {
            count--;
            i++;
            continue;
        }
        i++;
    }
    buf[i - 1] = '\0';
}
*/
void 
normalize_path(char *buf){
    int count_slash = 1, count_dots = 0, len = strlen(buf);
    if(len == 1) {
        buf[0] = '/';
        return;
    }
    if(buf[len - 1] == '/') {
        buf[len - 1] = '\0';
    }
    int indicate = 0;
    for(int i = len - 1; i > 0; --i){
        if(buf[i] == '.' && buf[i - 1] == '.' && indicate == 0){
            count_dots++;
        }
        if(buf[i] != '/' && buf[i] != '.'){
            indicate = 1;
        }
        if(buf[i] == '/') {
            count_slash++;
        }
    }
    int count_output = count_slash - count_dots * 2 + 1;
    if(count_output <= 0) {
        buf[0] = '/';
        buf[1] = '\0';  
        return;
    }
    int i;
    while(count_output != 0) {
        if(buf[i] == '/') {
            count_output--;
            i++;
            continue;
        }
        i++;
    }
    buf[i - 1] = '\0';
    if(strlen(buf) == 0) {
        buf[0] = '/';
        buf[1] = '\0';
    }
    printf("%lu\n", strlen(buf));
}


int main(void){
    char str[100];
    scanf("%s", str);
    normalize_path(str);
    printf("%s\n", str);
    return 0;
}
