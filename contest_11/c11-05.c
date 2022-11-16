#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/types.h>
#include <ctype.h>
#include <wait.h>
#include <dirent.h>

int
main(int argc, char **argv, char **envp)
{
    pid_t main_pid = fork();
    switch (main_pid) {
        case (-1): {
            _exit(EXIT_SUCCESS);
        }
        case (0): {
            int num;
            pid_t pid;
            while (scanf("%d", &num) == 1) {
                pid = fork();
                if (pid == -1) {
                    _exit(EXIT_FAILURE);
                } else if (pid) {
                    int status = EXIT_SUCCESS;
                    wait(&status);
                    if (WEXITSTATUS(status) == EXIT_FAILURE) {
                        _exit(EXIT_FAILURE);
                    } else {
                        printf("%d\n", num);
                        fflush(stdout);
                        break;
                    }
                }
            }
        }
        default: {
            int status = EXIT_SUCCESS;
            wait(&status);
            if (WEXITSTATUS(status) == EXIT_FAILURE) {
                printf("-1\n");
                fflush(stdout);
            }
        }
    }
    while (wait(NULL) > 0);
    _exit(EXIT_SUCCESS);
}
