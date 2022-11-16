#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    DIR *dir = opendir(argv[1]);
    struct dirent *dd;
    struct stat stb;
    int res = 0;
    while ((dd = readdir(dir)) != NULL) {
        char *buf;
        asprintf((char **) &buf, "%s/%s", argv[1], dd->d_name);
        stat(buf, &stb);
        if (S_ISREG(stb.st_mode) && access(buf, X_OK) == 0) {
            size_t sz = strlen(dd->d_name);
            if (sz >= 4 && strcmp(&(dd->d_name[sz - 4]), ".exe") == 0) {
                ++res;
            }
        }
        free(buf);
    }
    closedir(dir);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}
