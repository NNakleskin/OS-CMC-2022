#include <stdio.h>

int
main(int argc, char** argv)
{
    if(argc < 2)
    {
        return 1;
    }
    int f = open(argv[1], O_WRONLY, 0666);
    if(f == -1)
    {
        return 1;
    }
    
    return 0;
}
