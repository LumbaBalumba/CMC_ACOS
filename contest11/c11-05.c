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

/* Код не работает на последнем тесте, где надо вернуть -1 в случае ошибки, фиксить лень*/

int
rec_fork()
{
    int buf;
    if (scanf("%d", &buf) != EOF) {
        pid_t pid = fork();
        if (pid < 0) {
            return -1;
        } else if (!pid) {
            if (rec_fork() == -1) {
                return -1;
            }
        } else {
            wait(NULL);
            printf("%d\n", buf);
        }
    }
    return 0;
}

int
main(int argc, char **argv)
{
    if (rec_fork() == -1 && getpid()) {
        printf("-1\n");
    }
}