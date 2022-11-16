#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <fcntl.h>
#include <string.h>

/* Я честно спёр этот код с консультации 12-го октября */

void
print_files(const char *path, size_t sz, int depth, size_t len)
{
    if (!(depth >= 1 && depth <= 4)) {
        return;
    }
    DIR *dir = opendir(path);
    struct dirent *dd;
    int vec_cap = 16, vec_sz = 0;
    char **vec = calloc(vec_cap, sizeof(char *));
    char buf[PATH_MAX + 1];
    while ((dd = readdir(dir)) != NULL) {
        snprintf(buf, sizeof(buf), "%s/%s", path, dd->d_name);
        struct stat stb;
        if (lstat(buf, &stb) != 0) {
            continue;
        }
        if (S_ISLNK(stb.st_mode)) {
            continue;
        } else if (S_ISDIR(stb.st_mode) && !access(buf, F_OK | R_OK)) {
            if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
                continue;
            }
            /*print_files(buf, sz, depth + 1, len);*/
            if (vec_sz == vec_cap) {
                vec = realloc(vec, (vec_cap *= 2) * sizeof(*vec));
            }
            vec[vec_sz++] = strdup(buf);
        } else if (S_ISREG(stb.st_mode) && !access(buf, F_OK | R_OK) && stb.st_size <= sz) {
            if (vec_sz == vec_cap) {
                vec = realloc(vec, (vec_cap *= 2) * sizeof(*vec));
            }
            vec[vec_sz++] = strdup(buf);
        }
    }
    closedir(dir);
    for (int i = 0; i < vec_sz; ++i) {
        struct stat stb;
        lstat(vec[i], &stb);
        if (S_ISREG(stb.st_mode)) {
            printf("%s\n", &vec[i][len + 1]);
        } else if (S_ISDIR(stb.st_mode)) {
            print_files(vec[i], sz, depth + 1, len);
        }
        free(vec[i]);
    }
    free(vec);
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *path = argv[1];
    char *eptr = NULL;
    errno = 0;
    long long sz = strtoll(argv[2], &eptr, 10);
    if (errno || eptr == argv[1] || *eptr) {
        return EXIT_FAILURE;
    }
    print_files(path, sz, 1, strlen(argv[1]));
}