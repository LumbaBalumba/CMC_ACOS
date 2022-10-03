#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(
    int argc,
    char* argv[])
{
    char* eptr = NULL;
    long long pos = 0, neg = 0;
    for (int i = 0; i < argc; ++i) {
        errno = 0;
        long long tmp = strtol(argv[i], &eptr, 10);
        if (errno || eptr == NULL || argv[i] == eptr || tmp != (int)tmp) {
            fprintf(stderr, "error: data reading error\n");
            return 1;
        }
        if (tmp >= 0) {
            if (__builtin_add_overflow(pos, tmp, &pos)) {
                fprintf(stderr, "data is too big\n");
                return 1;
            }
        } else {
            if (__builtin_add_overflow(neg, tmp, &neg)) {
                fprintf(stderr, "data is too big\n");
                return 1;
            }
        }
    }
    printf("%lld\n%lld\n", pos, neg);
}