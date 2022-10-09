#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>


int
main(int argc, char** argv)
{
    if(argc < 2)
    {
        return 1;
    }
    int f = open(argv[1], O_RDONLY, 0666);
    if(f == -1)
    {
        return 1;
    }
    int32_t key[3];
    int indicate = read(f, &key, 3 * sizeof(int32_t));
    printf("%d\n", key[2]);
    printf("%d\n", ftell(f));
    return 0;
}
