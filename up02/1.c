#include <stdio.h>

int
main(void)
{
    char host[129];
    char login[129];
    char password[129];
    scanf("%s%s%s", host, login, password);
    printf("[Host:%s,Login:%s,Password:%s]\n", host, login, password);
    return 0;
}
