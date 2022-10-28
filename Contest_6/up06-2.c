#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


void
normalize_path(char *buf) {
    size_t len = strlen(buf);
    char *tmp = calloc(len, sizeof(char));
    if(buf[len - 1] == '/') {
        buf[len - 1] = '\0';
        len--;
    }
    int tmp_index = 0;
    int ddot_count = 0;
    for(int i = 0; i < len; ++i) {
        //printf("%s\n", tmp);
        if(i + 2 == len) {
            if(buf[i] == '/' && buf[i + 1] == '.') {
                i++;
                continue;   
            }
        } else if(i + 3 < len) {
            if(buf[i] == '/' && buf[i + 1] == '.' && buf[i + 2] == '/') {
                i += 1;
                continue;
            } 
        }
        if(i + 3 == len) {
            if(buf[i] == '/' && buf[i + 1] == '.' && buf[i + 2] == '.') {
                while(tmp[tmp_index] != '/' || tmp_index > 1) {
                    tmp[tmp_index] = '\0';
                    tmp_index--;
                }
                //tmp[tmp_index] = '\0';
                ddot_count++;
                i += 1;
                continue;
            } 
        } else if(i + 4 < len) {
            if(buf[i] == '/' && buf[i + 1] == '.' && buf[i + 2] == '.' && buf[i + 3] == '/') {
                while(tmp[tmp_index] != '/' || tmp_index > 1) {
                    tmp[tmp_index] = '\0';
                    tmp_index--;
                }
                //tmp[tmp_index] = '\0';
                ddot_count++;
                i += 2;
                continue;
            }
        }
        tmp[tmp_index] = buf[i];
        tmp_index++;
        
    }
    snprintf(buf, strlen(tmp) + 1, "%s", tmp);
    //printf("%s\n", tmp);
    //printf("%d\n", ddot_count);
}


int main(void) {
    char a[PATH_MAX];
    scanf("%s", a);
    normalize_path(a);
    printf("%s\n", a);
    return 0;
}
