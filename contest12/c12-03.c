#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>

int
main(int argc, char *argv[])
{
    int cnt = 0;
    for (int i = 1; i < argc; ++i) {
        switch (argv[i][0]) {
            case 's': {
                int status;
                while (wait(&status) > 0) {
                    cnt += WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
                }
                pid_t pid = fork();
                if (pid == -1) {
                    exit(EXIT_FAILURE);
                } else if (!pid) {
                    execlp(argv[i] + 1, argv[i] + 1, NULL);
                    exit(EXIT_FAILURE);
                } else {
                    wait(&status);
                    cnt += WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
                }
                break;
            }
            case 'p': {
                pid_t pid = fork();
                if (pid == -1) {
                    exit(EXIT_FAILURE);
                } else if (!pid) {
                    execlp(argv[i] + 1, argv[i] + 1, NULL);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default: {
                exit(EXIT_FAILURE);
            }
        }
    }
    int status;
    while (wait(&status) > 0) {
        cnt += WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS;
    }
    printf("%d\n", cnt);
    return EXIT_SUCCESS;
}