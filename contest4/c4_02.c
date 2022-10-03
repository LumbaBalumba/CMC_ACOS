#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

off_t
filesize(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    } else {
        fprintf(stderr, "Cannot determine file size\n");
        return -1;
    }
}

long
min(long a, long b)
{
    return (a < b) ? a : b;
}

int
main(int argc, char *argv[])
{
    if (argc <= 1 || argc > 3) {
        return EXIT_FAILURE;
    }
    off_t sz = filesize(argv[1]);
    if (sz == -1) {
        return EXIT_FAILURE;
    } else if (sz == 0 || sz == sizeof(int)) {
        return EXIT_SUCCESS;
    } else {
        int file = open(argv[1], O_RDWR, 0666);
        char *eptr = NULL;
        long N = strtol(argv[2], &eptr, 10);
        if (*eptr || eptr == argv[2] || N != (int) N || N < 0) {
            return EXIT_FAILURE;
        }
        double buf = 0.0;
        double cur = 0.0;
        if (N * sizeof(double) > sz) {
            N = (long) (sz / sizeof(double));
        }
        for (int i = 0; i < N; ++i) {
            read(file, &buf, sizeof(double));
            buf -= cur;
            lseek(file, -(off_t) sizeof(double), SEEK_CUR);
            write(file, &buf, sizeof(double));
            cur = buf;
        }
        close(file);
    }
}