#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <inttypes.h>
#include <sys/types.h>
#include <stdbool.h>

int
main(int argc, char **argv)
{
    int n;
    if (scanf("%d", &n) != 1) {
        _exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d%c", i, (i == n) ? '\n' : ' ');
        fflush(stdout);
        pid_t pid = fork();
        if (pid == -1) {
            _exit(EXIT_FAILURE);
        } else if (!pid) {
            continue;
        } else {
            wait(NULL);
            break;
        }
    }
    _exit(EXIT_SUCCESS);
}