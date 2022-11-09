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
    int num1, num2, num3;
    scanf("%d%d%d", &num1, &num2, &num3);
    pid_t pid1 = fork();
    if (!pid1) {
        printf("1 %d\n", num1 * num1);
    } else {
        wait(NULL);
        pid_t pid2 = fork();
        if (!pid2) {
            printf("2 %d\n", num2 * num2);
        } else {
            wait(NULL);
            pid_t pid3 = fork();
            if (!pid3) {
                printf("3 %d\n", num3 * num3);
            } else {
                wait(NULL);
                fflush(stdout);
                _exit(EXIT_SUCCESS);
            }
        }
    }
}