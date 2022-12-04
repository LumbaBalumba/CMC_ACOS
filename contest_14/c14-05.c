#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

volatile int sig_cnt = 0;
volatile int curr_prime = 0;

void
handler(int sig)
{
    switch (sig) {
        case SIGTERM: {
            exit(EXIT_SUCCESS);
        }
        case SIGINT: {
            if (sig_cnt++ == 3) {
                exit(EXIT_SUCCESS);
            } else {
                printf("%d\n", curr_prime);
                fflush(stdout);
            }
        }
        default: {
        }
    }
}

int
prime(int n)
{
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char **argv)
{
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGTERM, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int low, high;
    scanf("%d%d", &low, &high);
    for (int i = low; i < high; ++i) {
        if (prime(i)) {
            curr_prime = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}
