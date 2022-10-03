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
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    off_t sz = filesize(argv[1]);
    if (sz == -1) {
        return EXIT_FAILURE;
    }
    
}