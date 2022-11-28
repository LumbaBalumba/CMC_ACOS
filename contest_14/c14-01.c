#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int sig_cnt = 0;

void
handler(int s)
{
    if (sig_cnt == 5) {
        exit(EXIT_SUCCESS);
    } else {
        printf("%d\n", sig_cnt++);
        fflush(stdout);
    }
}

int
main(int argc, char **argv)
{
    sigaction(SIGHUP, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}

