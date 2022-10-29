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

int
string_to_llong(char *str, size_t sz)
{
    long long res;
    int mul = 1;
    if (str[sz - 1] == 'k') {
        mul = 1000;
        str[sz - 1] = '\0';
    }
    errno = 0;
    char *eptr = NULL;
    res = strtoll(str, &eptr, 10);
    if (errno || eptr == str || *eptr || (int) res != res) {
        res = 0;
    }
    int tmp = (int) res;
    if (__builtin_mul_overflow(tmp, mul, &tmp)) {
        res = 0;
    } else {
        res = tmp;
    }
    return (int) res;
}

int
main(int argc, char *argv[])
{
    long long res = 0;
    for (int i = 1; i < argc; ++i) {
        size_t sz = strlen(argv[i]);
        char sign = argv[i][sz - 1];
        argv[i][sz - 1] = '\0';
        if (sign == '+') {
            res += string_to_llong(argv[i], sz - 1);
        } else if (sign == '-') {
            res -= string_to_llong(argv[i], sz - 1);
        }

    }
    printf("%lld\n", res);
}