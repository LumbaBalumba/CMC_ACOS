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
    int pipedes12[2], pipedes21[2];
    pipe(pipedes12);
    pipe(pipedes21);
    pid_t son1 = -1, son2 = -1;
    int value = 1, n = (int) strtol(argv[1], NULL, 10);
    son1 = fork();
    if (!son1) {
        close(pipedes21[1]);
        close(pipedes12[0]);
        while (read(pipedes21[0], &value, sizeof(value)) > 0 && value < n && value) {
            printf("1 %d\n", value);
            fflush(stdout);
            value++;
            write(pipedes12[1], &value, sizeof(value));
        }
        value = 0;
        write(pipedes12[1], &value, sizeof(value));
        close(pipedes21[0]);
        close(pipedes12[1]);
        exit(EXIT_SUCCESS);
    } else {
        son2 = fork();
        if (!son2) {
            close(pipedes21[0]);
            close(pipedes12[1]);
            while (read(pipedes12[0], &value, sizeof(value)) > 0 && value < n && value) {
                printf("2 %d\n", value);
                fflush(stdout);
                value++;
                write(pipedes21[1], &value, sizeof(value));
            }
            value = 0;
            write(pipedes21[1], &value, sizeof(value));
            close(pipedes21[1]);
            close(pipedes12[0]);
            exit(EXIT_SUCCESS);
        } else {
            write(pipedes21[1], &value, value);
            while (wait(NULL) > 0) {
            }
            printf("Done\n");
        }
    }
    exit(EXIT_SUCCESS);
}