#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_SUCCESS);
    }
    if (!pid) {
        int fd[3];
        if ((fd[0] = open(argv[2], O_RDONLY, 0660)) < 0) {
            exit(42);
        }
        if ((fd[1] = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660)) < 0) {
            exit(42);
        }
        if ((fd[2] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660)) < 0) {
            exit(42);
        }
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[2], STDERR_FILENO);
        execlp(argv[1], argv[1], NULL);
        exit(42);
    } else {
        int status;
        wait(&status);
        printf("%d\n", status);
    }
    return EXIT_SUCCESS;
}