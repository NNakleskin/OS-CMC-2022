#include <stdio.h>
#include <string.h>


const char BASE[] = "rwxrwxrwx";


int
parce_rwx_permissions(const char *str){ 
    int n = sizeof(BASE) - 1;
    int tmp[n + 1];
    int res = 0;
    if(str == NULL){
        return 1;
    }
    if(strlen(str) != n){
        return 1;
    }
    for(int i = 0; i < n; i++){
        tmp[i] = (int) str[i] ^ BASE[i];
        if(tmp[i] != 0){
            tmp[i] = 0;
        } else {
            tmp[i] = 1;
        }
        printf("%d", tmp[i]);
    }
    return res;
}


int main(void){
    char input[9];
    scanf("%s", input);
    printf("%o\n", parce_rwx_permissions(input));
    return 0;
}
