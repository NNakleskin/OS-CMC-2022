#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


#if __unix__
#define _GNU_SOURCE
#define INTERPRETER_PATH "#!/bin/python3\nfrom os import remove\nimport sys\nsys.set_int_max_str_digits(1000000)\n"
#else
#define INTERPRETER_PATH "#!/usr/bin/python3\nfrom os import remove\n"
#endif



int 
main(int argc, char **argv) {
    if(argc < 2) { return 1; }
    char *tmp_path = NULL;
    if((tmp_path = getenv("XDG_RUNTIME_DIR")) == NULL 
            && (tmp_path = getenv("TMPDIR"))  == NULL) {
        tmp_path = "/tmp";
    }
    char path[PATH_MAX + 1];
    snprintf(path, PATH_MAX + 1, "%s/res.py", tmp_path);
    int fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0755);
    dprintf(fd, INTERPRETER_PATH);
    char buf[] = "print(";
    dprintf(fd, "%s", buf);
    for(int i = 1; i < argc; ++i) {
        dprintf(fd, "%s", argv[i]);
        if(i == argc - 1) {
            dprintf(fd, ")\nremove(\"%s\")\n", path);
            break;
        }
        dprintf(fd, " * ");
    }
    close(fd);
    execlp(path, path, NULL);
    _exit(1);
    return 0;

}