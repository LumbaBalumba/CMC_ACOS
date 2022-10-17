#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    if (argc > 2) {
        return EXIT_FAILURE;
    }
    int fd = open(argv[1], O_RDWR, 0666);
    struct stat stb;
    fstat(fd, &stb);
    long long X;
    while (scanf("%lld", &X) != EOF) {
        if (X > 0 && (X - 1) / 8 <= stb.st_size) {
            X--;
            lseek(fd, X / 8, SEEK_SET);
            unsigned char buf;
            read(fd, &buf, sizeof(buf));
            buf |= (1 << X % 8);
            lseek(fd, X / 8, SEEK_SET);
            write(fd, &buf, sizeof(buf));
        } else if (X < 0 && (X + 1) / 8 >= -stb.st_size) {
            X++;
            X = -X;
            lseek(fd, X / 8, SEEK_SET);
            unsigned char buf;
            read(fd, &buf, sizeof(buf));
            buf &= ~(1 << X % 8);
            lseek(fd, X / 8, SEEK_SET);
            write(fd, &buf, sizeof(buf));
        }
    }
}
