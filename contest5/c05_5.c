#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>

enum
{
    BUF_SIZE = 4096
};

int
copy_file(const char *srcpath, const char *dstpath)
{
    struct stat statbuf;
    if (stat(srcpath, &statbuf) == -1) {
        fprintf(stderr, "Error: cannot read file %s, file may be not existing\n", srcpath);
        return -1;
    }
    if (S_ISDIR(statbuf.st_mode)) {
        fprintf(stderr, "Error: %s is not a file\n", srcpath);
        return -1;
    }
    size_t index = 0;
    size_t l = strlen(srcpath);
    for (size_t i = 0; i < l; ++i) {
        if (srcpath[i] == '/') {
            index = i + 1;
        }
    }
    char *dstfile;
    if (asprintf(&dstfile, "%s/%s", dstpath, &srcpath[index]) == -1) {
        fprintf(stderr, "Error: could not allocate memory for file path\n");
        return -1;
    }
    int fd_src = open(srcpath, O_RDONLY, 0444), fd_dst = open(dstfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_src == -1 || fd_dst == -1) {
        fprintf(stderr, "Error: cannot open file %s\n", srcpath);
        return -1;
    }
    if (fd_src == fd_dst) {
        return 0;
    }
    size_t cnt = 0;
    unsigned char buf[BUF_SIZE];
    while (read(fd_src, &buf[cnt], sizeof(buf[cnt])) == sizeof(buf[cnt])) {
        if (cnt + 1 == BUF_SIZE) {
            write(fd_dst, buf, sizeof(buf[0]) * (cnt + 1));
            cnt = 0;
        } else {
            ++cnt;
        }
    }
    if (cnt != 0) {
        write(fd_dst, buf, sizeof(buf[0]) * (cnt + 1));
    }
    chmod(dstfile, statbuf.st_mode);
    close(fd_src);
    close(fd_dst);
    return 0;
}
