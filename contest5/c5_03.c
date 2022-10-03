#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    const char t_str[] = "rwxrwxrwx";
    if (str == NULL) {
        return -1;
    }
    size_t t_sz = sizeof(t_str) - 1;
    size_t sz = strlen(str);
    if (sz != t_sz) {
        return -1;
    }
    unsigned int res = 0;
    for (unsigned i = sz; i > 0; --i) {
        if (str[i - 1] == t_str[i - 1]) {
            res |= 1u << (sz - i);
        } else if (str[i - 1] != '-') {
            return -1;
        }
    }
    return (int) res;
}

int
main()
{
    char str[20];
    scanf("%s", str);
    int r = parse_rwx_permissions(str);
    if (r == -1) {
        printf("-1\n");
    } else {
        printf("%o\n", r);
    }
}