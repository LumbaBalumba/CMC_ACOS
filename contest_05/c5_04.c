#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

struct File
{
    char *path;
    ino_t fd;
};

int
cmp(const void *a, const void *b)
{
    return strcmp((*(struct File *) a).path, (*(struct File *) b).path);
}


int
main(int argc, char *argv[])
{
    if (argc == 1) {
        return EXIT_SUCCESS;
    } else {
        int sz = 0;
        struct File *arr = calloc(argc - 1, sizeof(struct File));
        for (int i = 1; i < argc; ++i) {
            struct stat stb;
            if (stat(argv[i], &stb) == -1) {
                continue;
            }
            int flag = 0;
            for (int j = 0; j < sz; ++j) {
                if (stb.st_ino == arr[j].fd) {
                    if (strcmp(argv[i], arr[j].path) > 0) {
                        arr[j] = (struct File) { .path = argv[i], .fd = stb.st_ino };
                    }
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                arr[sz] = (struct File) { .path = argv[i], .fd = stb.st_ino };
                ++sz;
            }
        }
        qsort(arr, sz, sizeof(struct File), cmp);
        for (int i = 0; i < sz; ++i) {
            printf("%s\n", arr[i].path);
        }
        return EXIT_SUCCESS;
    }
}
