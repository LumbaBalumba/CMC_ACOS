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
main()
{
    enum
    {
        BUF_SZ = 8,
        CHILD_CNT = 3
    };
    pid_t pid;
    for (int i = 0; i < CHILD_CNT; ++i) {
        pid = fork();
        switch (pid) {
            case -1: {
                exit(EXIT_FAILURE);
            }
            case 0: {
                char buf[8];
                if (read(STDIN_FILENO, buf, BUF_SZ) == -1) {
                    exit(EXIT_FAILURE);
                }
                char *eptr = NULL;
                long num = strtol(buf, &eptr, 10);
                printf("%d %ld\n", i + 1, num * num);
                exit(EXIT_SUCCESS);
            }
        }
    }
    while (wait(NULL) > 0);
    fflush(stdout);
    _exit(EXIT_SUCCESS);
}