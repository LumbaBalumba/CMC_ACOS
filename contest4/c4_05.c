#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

long long
sqr_sum(long long x, long long mod)
{
    long res = x * (x + 1) * (2 * x + 1) / 6 % mod;
    return res;
}

int
main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Invalid program arguments\n");
        return EXIT_FAILURE;
    }
    int file1 = open(argv[1], O_RDONLY, 0444), file2 = open(argv[2], O_TRUNC | O_CREAT | O_WRONLY, 0666);
    if (file1 == -1 || file2 == -1) {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    }
    struct stat stbuf1, stbuf2;
    if (fstat(file1, &stbuf1) == -1 || fstat(file2, &stbuf2) == -1) {
        fprintf(stderr, "File data error\n");
        return EXIT_FAILURE;
    } else if (stbuf1.st_size == 0) {
        fprintf(stderr, "Empty file\n");
        return EXIT_SUCCESS;
    }
    char *eptr = NULL;
    long mod = strtol(argv[3], &eptr, 10);
    if (*eptr || eptr == argv[3] || mod != (int) mod) {
        fprintf(stderr, "Modulo reading error\n");
        return EXIT_FAILURE;
    }
    unsigned char c;
    int cur_byte = 0;
    int buf = 0;
    read(file1, &c, sizeof(c));
    for (int i = 0; i < CHAR_BIT; ++i) {
        if (c & (1u << i)) {
            buf = (int) sqr_sum(1 + i + CHAR_BIT * cur_byte, mod);
            //printf("%d\n", buf);
            write(file2, &buf, sizeof(buf));
        }
    }
    while (read(file1, &c, sizeof(c)) == sizeof(c)) {
        cur_byte++;
        for (int i = 0; i < CHAR_BIT; ++i) {
            if (c & (1u << i)) {
                buf = (int) sqr_sum(1 + i + 8 * cur_byte, mod);
                //printf("%d\n", buf);
                write(file2, &buf, sizeof(buf));
            }
        }
    }
    if (close(file1) == -1) {
        fprintf(stderr, "File1 closing error\n");
        return EXIT_FAILURE;
    } else if (close(file2) == -1) {
        fprintf(stderr, "File2 closing error\n");
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}