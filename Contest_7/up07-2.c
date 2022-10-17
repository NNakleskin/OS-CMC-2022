#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    double res = 0;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-' and argv[i][strlen(argv[i])] == '-'){
            res += double(argv);
        }
    }
    return 0;
}
