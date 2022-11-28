#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define min(a, b) (a < b ? a : b)


int
main(int argc, char **argv)
{
    int N, cnt = 0, status;
    N = (int) strtol(argv[1], NULL, 10);
    for (int i = 0; i < min(N, argc - 2); ++i) {
        FILE *fd = fopen(argv[i + 2], "rt");
        char buf[PATH_MAX + 1];
        fscanf(fd, "%s", buf);
        pid_t pid = fork();
        if (pid < 0) {
            exit(EXIT_FAILURE);
        } else if (!pid) {
            execlp(buf, buf, NULL);
            exit(EXIT_FAILURE);
        } else {
            fclose(fd);
        }
    }
    while (wait(&status) > 0) {
        cnt += WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
    }
    for (int i = N + 2; i < argc; ++i) {
        FILE *fd = fopen(argv[i], "rt");
        char buf[PATH_MAX + 1];
        fscanf(fd, "%s", buf);
        pid_t pid = fork();
        if (pid < 0) {
            exit(EXIT_FAILURE);
        } else if (!pid) {
            execlp(buf, buf, NULL);
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
            cnt += WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
            fclose(fd);
        }
    }
    printf("%d\n", cnt);
}