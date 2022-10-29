#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

long long process(char *str, ssize_t sz, int *err) {
    while (str[0] == '0') {
        ++str;
        --sz;
    }
    if (sz == 0) {
        return 0;
    }
    int negative = 0;
    if (str[0] == 'a') {
        negative = 1;
        for (ssize_t i = 0; i < sz; ++i) {
            if (str[i] == '1') {
                str[i] = 'a';
            } else if (str[i] == 'a') {
                str[i] = '1';
            }
        }

    }
    long long res;
    int flag = 0;
    char *tmp;
    if (negative) {
        tmp = calloc(sz + 2, sizeof(char));
        tmp[0] = '-';
    } else {
        tmp = calloc(sz + 1, sizeof(char));
    }
    ssize_t i = sz - 1 + negative;
    for (ssize_t index = sz - 1; index >= 0; --index) {
        switch (str[index]) {
            case 'a':
                if (flag) {
                    tmp[i] = '1';
                } else {
                    tmp[i] = '2';
                }
                --i;
                flag = 1;
                break;
            case '0':
                if (flag) {
                    tmp[i] = '2';
                } else {
                    tmp[i] = '0';
                }
                --i;
                break;
            case '1':
                if (flag) {
                    tmp[i] = '0';
                    flag = 0;
                } else {
                    tmp[i] = '1';
                }
                --i;
                break;
        }
    }
    while (i >= negative) {
        tmp[i--] = '0';
    }
    tmp[sz + negative] = '\0';
    char *eptr = NULL;
    errno = 0;
    res = strtoll(tmp, &eptr, 3);
    if (errno || eptr == tmp || *eptr) {
        *err = 1;
        return 0;
    }
    free(tmp);
    return res;
}

int
main(void) {
    int buf = 0;
    ssize_t sz = 0, cap = 17;
    char *str = calloc(cap, sizeof(char));
    if (str == NULL) {
        return EXIT_FAILURE;
    }
    int err = 0;
    while ((buf = getchar()) != EOF) {
        if (isspace(buf)) {
            if (sz > 0) {
                str[sz] = '\0';
                long long tmp = process(str, sz, &err);
                if (!err) {
                    printf("%lld\n", tmp);
                } else {
                    printf("18446744073709551616\n");
                }
                err = 0;
            }
            sz = 0;
            cap = 17;
            str = realloc(str, sizeof(char) * cap);
        } else if (buf == '1' || buf == 'a' || buf == '0') {
            if (sz == cap - 1) {
                cap = (cap - 1) * 2 + 1;
                str = realloc(str, sizeof(char) * cap);
            }
            str[sz++] = (char) buf;
        }
    }
    free(str);
    return 0;
}