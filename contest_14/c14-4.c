#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int pfd[2][2];
volatile int proc_num;
volatile int max_num;

void
sighndlr(int sig)
{
    if (sig == SIGKILL) {
        exit(EXIT_SUCCESS);
    } else if (sig == SIGUSR1) {
        pid_t pid;
        read(pfd[proc_num][0], &pid, sizeof(pid));
        int n;
        read(pfd[proc_num][0], &n, sizeof(n));
        if (n == max_num) {
            kill(pid, SIGKILL);
            exit(EXIT_SUCCESS);
        }
        printf("%d %d\n", proc_num + 1, n++);
        fflush(stdout);
        kill(pid, SIGUSR1);
        pid = getpid();
        write(pfd[1 - proc_num][1], &pid, sizeof(pid));
        write(pfd[1 - proc_num][1], &n, sizeof(n));
    }
}


int
main(int argc, char **argv)
{
    sigaction(SIGKILL, &(struct sigaction) { .sa_flags = SA_RESTART, .sa_handler = sighndlr }, NULL);
    sigaction(SIGUSR1, &(struct sigaction) { .sa_flags = SA_RESTART, .sa_handler = sighndlr }, NULL);
    max_num = (int) strtol(argv[1], NULL, 10);
    pipe(pfd[0]);
    pipe(pfd[1]);
    pid_t pid = fork();
    if (!pid) {
        close(pfd[0][1]);
        close(pfd[1][0]);
        proc_num = 0;
        while (1) {
            pause();
        }
    }
    kill(pid, SIGUSR1);
    pid = fork();
    if (!pid) {
        close(pfd[1][1]);
        close(pfd[0][0]);
        proc_num = 1;
        while (1) {
            pause();
        }
    }
    {
        int n = 1;
        write(pfd[0][1], &pid, sizeof(pid));
        write(pfd[0][1], &n, sizeof(n));
    }
    while (wait(NULL) > 0);
    printf("Done\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}