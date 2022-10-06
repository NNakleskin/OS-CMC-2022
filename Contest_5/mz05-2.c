#include <stdio.h>
#include <string.h>

char* 
get_f(char n)
{
    if(n == '0'){
        return "---";
    }
    if(n == '1'){
        return "--x";
    }
    if(n == '2'){
        return "-w-";
    }
    if(n == '3'){
        return "-wx";
    }
    if(n == '4'){
        return "r--";
    }
    if(n == '5'){
        return "r-x";
    }
    if(n == '6'){
        return "rw-";
    }
    if(n == '7'){
        return "rwx";
    }
    return 0;
}

int main(int argc, char** argv)
{  
    int i = 1;
    while(i < argc){
        int len = strlen(argv[i]);
        if(len == 3)
        {
            printf("%s", get_f(argv[i][0]));
            printf("%s", get_f(argv[i][1]));
            printf("%s", get_f(argv[i][2]));
        }
        if(len == 2)
        {
            printf("%s", get_f('0'));
            printf("%s", get_f(argv[i][0]));
            printf("%s", get_f(argv[i][1]));
        }
        if(len == 1)
        {
            printf("%s", get_f('0'));
            printf("%s", get_f('0'));
            printf("%s", get_f(argv[i][0]));
        }

        putchar(10);
        i++;
    }
    return 0;
}

