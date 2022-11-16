#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

void
print1()
{
    printf("1\n");
}

void
print2()
{
    printf("2 ");
}

void
print3()
{
    printf("3 ");
}

int
main(int argc, char **argv)
{
    pid_t son = fork();
    if (!son) {
        pid_t grandson = fork();
        if (!grandson) {
            print3();
        } else {
            wait(NULL);
            print2();
        }
    } else {
        wait(NULL);
        print1();
    }
}