#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

int
main(int argc, char *argv[], char *envp[])
{
    int pipedes[2];
    pipe(pipedes);
    pid_t pid = fork();
    if (!pid) {
        pid = fork();
        if (!pid) {
            close(pipedes[1]);
            int buf;
            long long res = 0;
            while (read(pipedes[0], &buf, sizeof(buf))) {
                res += buf;
            }
            printf("%lld\n", res);
        } else {
            close(pipedes[0]);
            close(pipedes[1]);
            wait(NULL);
        }
    } else {
        int buf;
        close(pipedes[0]);
        while (scanf("%d", &buf) != EOF) {
            write(pipedes[1], &buf, sizeof(buf));
        }
        close(pipedes[1]);
        wait(NULL);
    }
    exit(EXIT_SUCCESS);
}