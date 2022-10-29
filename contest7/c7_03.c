#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    DIR *dir = opendir(argv[2]);
    struct dirent *dd;
    size_t res = 0;
    while ((dd = readdir(dir)) != NULL) {
        struct stat stb1, stb2;
        char *path1, *path2;
        asprintf(&path1, "%s/%s", argv[1], dd->d_name);
        asprintf(&path2, "%s/%s", argv[2], dd->d_name);
        stat(path2, &stb2);
        if (lstat(path1, &stb1) != -1 && S_ISREG(stb1.st_mode) && !access(path1, W_OK | R_OK) &&
            stb1.st_ino == stb2.st_ino) {
            res += stb1.st_size;
        }
        free(path1);
        free(path2);
    }
    printf("%zu\n", res);
}