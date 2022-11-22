#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

int
main(int argc, char *argv[], char *envp[])
{
    int pipedes[2];
    pipe(pipedes);
    pid_t pid = fork();
    if (!pid) {
        pid = fork();
        if (!pid) {
            pid = fork();
            if (!pid) {
                close(pipedes[0]);
                time_t t = time(NULL);
                for (int i = 0; i < 3; ++i) {
                    write(pipedes[1], &t, sizeof(t));
                }
            } else {
                close(pipedes[1]);
                wait(NULL);
                struct tm st_t;
                time_t t;
                read(pipedes[0], &t, sizeof(t));
                localtime_r(&t, &st_t);
                printf("D:%2d\n", st_t.tm_mday);
            }
        } else {
            close(pipedes[1]);
            wait(NULL);
            struct tm st_t;
            time_t t;
            read(pipedes[0], &t, sizeof(t));
            localtime_r(&t, &st_t);
            printf("M:%2d\n", st_t.tm_mon + 1);
        }
    } else {
        close(pipedes[1]);
        wait(NULL);
        struct tm st_t;
        time_t t;
        read(pipedes[0], &t, sizeof(t));
        localtime_r(&t, &st_t);
        printf("Y:%4d\n", st_t.tm_year + 1900);
    }
    exit(EXIT_SUCCESS);
}