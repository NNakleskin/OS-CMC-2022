#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
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
    long long a, b, n;
    a = strtoll(argv[1], NULL, 10);
    b = strtoll(argv[2], NULL, 10);
    n = strtoll(argv[3], NULL, 10);


    char *func = argv[4];
    int i = 0;
    while(func[i] != '(' && func[i] != '\0') {
        i++;
    }
    func[i] = '\0';

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
                "#include <math.h>\n"
                "#include <errno.h>\n\n\n"
                
                "double rieman_integral(double (*f)(double), double x, double delt) {\n"
                "    return f(x) * delt;\n"
                "}\n"

                "double make_integral(double(*f)(double x), double a, double b, double n) {\n"
                "    double delt = (b - a) / n;\n"
                "    double x = a;\n"
                "    double result = 0;\n"
                "    for(double i = 0; i < n; i++) { \n"
                "        result += rieman_integral(f, x, delt);\n"
                "        x += delt;\n"
                "    }\n"
                "    return result;\n"
                "}\n"


                "double integral(double(*f)(double), double a, double b, double eps) {\n"
                "    int n = 1;\n"
                "    while(fabs(make_integral(f, a, b, n) - make_integral(f, a, b, 2 * n)) >= eps) {\n"
                "        n++;\n"
                "    }\n"
                "    return make_integral(f, a, b, 2 * n);\n"
                "}\n"


                "int main(void) {\n"
                "    int x;\n"
                "    printf(\"%%.10g\", make_integral(%s, %lld, %lld, %lld + 10000));"
                "    putchar(10);"
                "    fflush(stdout);"
                "    _exit(EXIT_SUCCESS);\n"
                "}\n",
        func, a, b, n);
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

    return 0;
}
