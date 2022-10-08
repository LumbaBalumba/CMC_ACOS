#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

int
print_tree(int file, long bias)
{
    struct Node buf;
    lseek(file, bias * (long) sizeof(buf), SEEK_SET);
    if (read(file, &buf, sizeof(buf)) != sizeof(buf)) {
        return -1;
    } else {
        if (buf.right_idx && print_tree(file, buf.right_idx) == -1) {
            return -1;
        }
        printf("%d\n", buf.key);
        if (buf.left_idx && print_tree(file, buf.left_idx) == -1) {
            return -1;
        }
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Arguments error\n");
        return EXIT_FAILURE;
    }
    int file = open(argv[1], O_RDONLY, 0444);
    if (file == -1) {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    }
    struct stat statbuf;
    if (fstat(file, &statbuf) == -1) {
        fprintf(stderr, "File info error\n");
        return EXIT_FAILURE;
    } else if (statbuf.st_size == 0) {
        fprintf(stderr, "Empty file, program stops working\n");
        return EXIT_SUCCESS;
    } else if (print_tree(file, 0) == -1) {
        fprintf(stderr, "Node reading error\n");
        return EXIT_FAILURE;
    } else if (close(file) == -1) {
        fprintf(stderr, "File opening error\n");
        return EXIT_FAILURE;
    } else {
        fprintf(stderr, "Program worked successfully\n");
        return EXIT_SUCCESS;
    }
}