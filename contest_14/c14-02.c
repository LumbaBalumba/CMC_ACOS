#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int mode = 0;

void
handler(int s)
{
    switch (s) {
        case SIGINT: {
            mode = 0;
            break;
        }
        case SIGQUIT: {
            mode = 1;
        }
        default: {

        }
    }
}

int
main(int argc, char **argv)
{
    sigaction(SIGINT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);
    sigaction(SIGQUIT, &(struct sigaction) { .sa_handler = handler, .sa_flags = SA_RESTART }, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    long long cur;
    long long res = 0;
    while (scanf("%lld", &cur) == 1) {
        switch (mode) {
            case 0: {
                res += cur;
                break;
            }
            case 1: {
                res *= cur;
                break;
            }
            default: {

            }
        }
        res = (int) res;
        printf("%lld\n", res);
        fflush(stdout);
    }
}

