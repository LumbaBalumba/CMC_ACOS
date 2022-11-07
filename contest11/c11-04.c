#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

void
rec_fork(int cur, int *n)
{
    if (cur == 0) {
        return;
    } else {
        pid_t pid = fork();
        if (!pid) {
            rec_fork(cur - 1, n);
        } else {
            printf("%d ", cur);
            wait(NULL);
        }
    }
}

int
main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    pid_t pid = fork();
    if (!pid) {
        n--;
        rec_fork(n, &n);
    } else {
        wait(NULL);
        printf("%d\n", n);
    }
}