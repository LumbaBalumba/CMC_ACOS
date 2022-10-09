#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>

int
same_file(const char *path1, const char *path2)
{
    struct stat statbuf1, statbuf2;
    if (lstat(path1, &statbuf1) == -1 || lstat(path2, &statbuf2) == -1) {
        return -1;
    }
    int fd1 = open(path1, O_RDONLY, 0666);
    int fd2 = open(path2, O_RDONLY, 0666);
    if (fd1 == -1 || fd2 == -1) {
        return -1;
    }
    if (!strcmp(path1, path2) || fd1 == fd2) {
        return 1;
    } else if (S_ISLNK(statbuf1.st_mode) && S_ISLNK(statbuf2.st_mode)) {
        
    } else if (S_ISLNK(statbuf1.st_mode) && S_ISREG(statbuf2.st_mode)) {

    } else if ((S_ISREG(statbuf1.st_mode) && S_ISLNK(statbuf2.st_mode))) {

    } else {
        return 0;
    }
}

int
main(int argc, char *argv[])
{

}
