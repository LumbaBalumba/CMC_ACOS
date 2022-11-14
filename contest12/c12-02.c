#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
execlp1(char *name)
{
    pid_t pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    } else if (!pid) {
        execlp(name, name, (char *) NULL);
    } else {
        int status;
        wait(&status);
        return (WIFEXITED(status) && !WEXITSTATUS(status));
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int r = (execlp1(argv[1]) || execlp1(argv[2])) && execlp1(argv[3]);
    return !r;
}