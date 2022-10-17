#include <stdio.h>
#include <string.h>


const char BASE[] = "rwxrwxrwx";


int
parce_rwx_permissions(const char *str){
    const char base[] = "rwxrwxrwx";
    int temp[9];
    if(str == NULL){
        return 1;
    }
    if(strlen(str) != sizeof(base) - 1){
        return 1;
    }
    for(int i = 0; i < sizeof(base) - 1; i++){
        temp[i] = str[i] ^ base[i];
        printf("base %d\n", base[i]);
        printf("%d\n", temp[i]);
        printf("%c", 85);
    }
    
    return 0;
}


int main(void){
    parce_rwx_permissions("--xr---w-");
    return 0;
}
