#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    unsigned long long sum = 0;
    struct stat st;
    for (int i = 1; i < argc; ++i) {
        sum += (lstat(argv[i], &st) >= 0 && S_ISREG(st.st_mode) && st.st_size % 1024 == 0 && st.st_nlink == 1)
                ? st.st_size : 0;
    }
    printf("%llu\n", sum);
}