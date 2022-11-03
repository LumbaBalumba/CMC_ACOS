#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

void
fill_matrix(unsigned int n, unsigned int m, unsigned int *arr)
{
    long i = 0, j, k = 0;
    unsigned p = 1;
    while (i < n * m) {
        k++;
        if (i == m * n) {
            break;
        }
        for (j = k - 1; j < m - k + 1; j++) {
            arr[(k - 1) * m + j] = p++;
            i++;
        }
        if (i == m * n) {
            break;
        }

        for (j = k; j < n - k + 1; j++) {
            arr[j * m + m - k] = p++;
            i++;
        }
        if (i == m * n) {
            break;
        }
        for (j = m - k - 1; j >= k - 1; j--) {
            arr[(n - k) * m + j] = p++;
            i++;
        }
        if (i == m * n) {
            break;
        }
        for (j = n - k - 1; j >= k; j--) {
            arr[j * m + k - 1] = p++;
            i++;
        }
    }
}

int
main(int argc, char **argv)
{
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    errno = 0;
    char *eptr1, *eptr2;
    long rows = strtol(argv[2], &eptr1, 10), cols = strtol(argv[3], &eptr2, 10);
    if (errno || eptr1 == argv[2] || eptr2 == argv[3] || *eptr1 || *eptr2 || (unsigned int) rows != rows ||
        (unsigned int) cols != cols) {
        return EXIT_FAILURE;
    }
    int fdout = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    ftruncate(fdout, rows * cols * (ssize_t) sizeof(int));
    fdout = open(argv[1], O_RDWR, 0666);
    void *ptr = mmap(NULL, rows * cols * sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0);
    fill_matrix((unsigned int) rows, (unsigned int) cols, ptr);
    munmap(ptr, rows * cols);
    close(fdout);
}