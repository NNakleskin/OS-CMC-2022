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


#define GCC_PATH "#!/usr/bin/gcc -o res res.c"


int main(int argc, char **argv) {
    if(argc < 2) { return 1; }
    char *tmp_path = NULL;
    if((tmp_path = getenv("XDG_RUNTIME_DIR")) == NULL 
            && (tmp_path = getenv("TMPDIR"))  == NULL) {
        tmp_path = "/tmp";
    }
    char path_c[PATH_MAX + 1];
    char path_ex[PATH_MAX + 1];
    snprintf(path_c, PATH_MAX + 1, "%s/res.c", tmp_path);
    snprintf(path_ex, PATH_MAX + 1, "%s/res", tmp_path);
    int fd = open("res.c", O_CREAT | O_RDWR | O_TRUNC, 0700); // ПОМЕНЯТЬ ПУТЬ ОБРАТНО
    dprintf(fd, "#include <stdio.h>\n"
                "#include <stdlib.h>\n"
                "#include <errno.h>\n\n\n"


                "#define summon \"summom\"\n"
                "#define disqualify \"disqualify\"\n"
                "#define reject \"reject\"\n\n\n"


                "int main(int argc, char ** argv) {\n"
                "    if(argc < 2) return 1;\n"
                "    errno = 0;"
                "    int x = strtol(argv[1], NULL, 10);\n"
                "    if(errno != 0) return 1;\n"
                "    printf(\"%%s\", %s);\n"
                "    putchar(10);\n"
                "    return 0;\n"
                "}\n",
            argv[1]);
    close(fd);
    

    _exit(0);
}
