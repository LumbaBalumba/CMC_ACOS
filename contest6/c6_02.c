#include <stdio.h>

void
normalize_path(char *path)
{
    ssize_t index1 = 0, index2 = 0;
    while (path[index1] != '\0') {
        if (path[index1] == '/' && path[index1 + 1] == '.' && (path[index1 + 2] == '/' || path[index1 + 2] == '\0')) {
            index1 += 2;
            continue;
        } else if (path[index1] == '/' && path[index1 + 1] == '.' && path[index1 + 2] == '.' &&
                (path[index1 + 3] == '/' || path[index1 + 3] == '\0')) {
            for (; index2 > 0 && path[index2 - 1] != '/'; --index2) {
            }
            index2 -= index2 > 1 ? 1 : 0;
            index1 += 3;
            continue;
        } else if (index2 > 0 && path[index2 - 1] == '/' && path[index1] == '/') {
            index1++;
        }
        path[index2++] = path[index1++];
    }
    for (; index2 > 1 && path[index2 - 1] == '/'; --index2) {}
    if (index2 == 0) {
        path[index2++] = '/';
    }
    path[index2] = '\0';
}
