#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>


void f_hash(char *str, size_t size)
{
    srand(time(NULL));
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK1234567890-_@";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
}


int main(int argc, char **argv) {
    if(argc < 2) { return 1; }
    char *tmp_path = NULL;
    if((tmp_path = getenv("XDG_RUNTIME_DIR")) == NULL 
            && (tmp_path = getenv("TMPDIR"))  == NULL) {
        tmp_path = "/tmp";
    }
    char *hash = malloc(10 * sizeof(char));
    f_hash(hash, 9);
    char path_c[PATH_MAX + 1];
    char path_ex[PATH_MAX + 1];
    char path_bash[PATH_MAX + 1];
    snprintf(path_c, PATH_MAX + 1, "%s/%s1.c", tmp_path, hash);
    snprintf(path_ex, PATH_MAX + 1, "%s/%s2", tmp_path, hash);
    snprintf(path_bash, PATH_MAX + 1, "%s/%s3.sh", tmp_path, hash);
    free(hash);
    int c_fd = open(path_c, O_CREAT | O_RDWR | O_TRUNC, 0700);  
    if(c_fd == -1) { _exit(EXIT_FAILURE); } 
    dprintf(c_fd, 
                "#include <stdio.h>\n"
                "#include <stdlib.h>\n"
                "#include <unistd.h>\n"
                "#include <errno.h>\n\n\n"


                "int main(void) {\n"
                "    char summon[] = \"summon\";\n"
                "    char reject[] = \"reject\";\n"
                "    char disqualify[] = \"disqualify\";\n"
                "    int x;\n"
                "    while(1) {\n"
                "        int res = scanf(\"%%d\", &x);\n"
                "        if(res == EOF) { _exit(EXIT_SUCCESS); }\n"
                "        if(res != 1) { _exit(EXIT_FAILURE); }\n"
                "        printf(\"%%s\", %s);\n"
                "        putchar(10);\n"
                "        fflush(stdout);\n"
                "    }\n"
                "    _exit(EXIT_SUCCESS);\n"
                "}\n",
            argv[1]);
    if(close(c_fd) == -1) { _exit(EXIT_FAILURE); }
    int bash_fd = open(path_bash, O_CREAT | O_TRUNC | O_RDWR, 0700);
    if(bash_fd == -1) { _exit(EXIT_FAILURE); }
    dprintf(bash_fd,
                "#!/bin/bash\n"
                "gcc -o %s %s\n"
                "%s\n"
                "rm %s %s %s\n",
            path_ex, path_c, path_ex, path_bash, path_c, path_ex);
    if(close(bash_fd) == -1) { _exit(EXIT_FAILURE); }  
    execlp(path_bash, path_bash, NULL);
    _exit(EXIT_FAILURE);
}

