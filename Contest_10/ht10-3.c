#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
// hexdump -C ht10-3.c


int main(int argc, char **argv) { 
    if(argc != 4) {
        return EXIT_FAILURE;
    }
    int rows = (int) strtol(argv[2], NULL, 10);
    int cols = (int) strtol(argv[3], NULL, 10);
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC , 0777);
    if (fd == -1) {
        return 1;
    }
    ftruncate(fd, rows * cols * (ssize_t) sizeof(int));
    fd = open(argv[1], O_RDWR, 0777);
    int *matrix = mmap(NULL, rows * cols * sizeof(int), 
            PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    int l_up = 0, l_down = 0, r_up = cols - 1, r_down = rows - 1;
    int num = 1; 
    while(num <= rows * cols) {
        for(int i = l_down; i <= r_up; ++i) {
            if(num > rows * cols) { break; }
            matrix[l_up * rows + i] = num;
            num++;
        }
        l_up++;
        for(int i = l_up; i <= r_down; ++i) {
            if(num > rows * cols) { break; }
            matrix[i * rows + r_up] = num;
            num++;
        }
        r_up--;
        for(int i = r_up; i >= l_down; --i) {
            if(num > rows * cols) { break; }
            matrix[r_down * rows + i] = num;
            num++;
        }
        r_down--;
        for(int i = r_down; i >= l_up; --i) {
            if(num > rows * cols) { break; }
            matrix[i * rows + l_down] = num;
            num++;
        }
        l_down++;
    }
    munmap(matrix, rows * cols);
    close(fd);
    return 0;
}

