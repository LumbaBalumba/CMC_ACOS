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


int
main(int argc, char *argv[])
{
    if (argc <= 1 || argc > 2) {
        return EXIT_FAILURE;
    }
    int file = open(argv[1], O_RDWR, O_CREAT, 0666);
    off_t sz = filesize(argv[1]);
    if (sz == -1) {
        return EXIT_FAILURE;
    } else if (sz == 0) {
        return EXIT_SUCCESS;
    } else {
        long long l, cur;
        ssize_t bias = 0;
        ssize_t cur_bias = 0;
        read(file, &l, sizeof(l));
        while (read(file, &cur, sizeof(l))) {
            cur_bias += sizeof(l);
            if (cur < l) {
                l = cur;
                bias = cur_bias;
            }
        }
        l = -l;
        lseek(file, bias, SEEK_SET);
        write(file, &l, sizeof(l));
        close(file);
    }
}