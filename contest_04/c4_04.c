#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>


int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Program arguments error\n");
        return EXIT_FAILURE;
    }
    int file = open(argv[1], O_RDWR, 0444);
    if (file == -1) {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    }
    struct stat statbuf;
    if (fstat(file, &statbuf) == -1) {
        fprintf(stderr, "File info error\n");
        return EXIT_FAILURE;
    } else if (statbuf.st_size == 0) {
        fprintf(stderr, "Empty file, program worked successfully\n");
        return EXIT_SUCCESS;
    }
    off_t cur_off = 1, min_off = 0;
    long long l_min = 0, l = 0;
    if (read(file, &l_min, sizeof(l_min)) != sizeof(l_min)) {
        fprintf(stderr, "File reading error\n");
        return EXIT_FAILURE;
    } else if (statbuf.st_size % sizeof(l)) {
        fprintf(stderr, "File size error\n");
        return EXIT_FAILURE;
    }
    while (read(file, &l, sizeof(l)) == sizeof(l)) {
        if (l < l_min) {
            min_off = cur_off;
            l_min = l;
        }
        cur_off++;
    }
    if (l_min != LLONG_MIN) {
        l_min = -l_min;
    }
    lseek(file, min_off * (off_t) sizeof(l), SEEK_SET);
    write(file, &l_min, sizeof(l_min));
    if (close(file) == -1) {
        fprintf(stderr, "File closing error\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Program worked successfully\n");
        return EXIT_SUCCESS;
    }
}