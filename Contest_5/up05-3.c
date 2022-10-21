#include <stdio.h>
#include <string.h>


const char BASE[] = "rwxrwxrwx";


int
parse_rwx_permissions(const char *str){
    int n = sizeof(BASE) - 1;
    int res = 0;
    if(str == NULL){
        return -1;
    }
    if(strlen(str) != n){ 
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(str[i] == '-'){
            res <<= 1;
        } else if(str[i] == BASE[i]) {
            res <<= 1;
            res |= 1;
        } else {
            return -1;
        }
    }
    return res;
}