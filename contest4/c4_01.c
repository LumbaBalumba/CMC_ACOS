#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    uint32_t tmp;
    if (argc <= 1) {
        return EXIT_FAILURE;
    }
    int file = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
    while (scanf("%u", &tmp) != EOF) {
        unsigned char buf[sizeof(tmp)] = {
                tmp >> 20,
                (tmp >> 12 & 15) + ((tmp >> 16 & 15) << 4),
                tmp >> 8 & 15,
                tmp & 255
        };
        write(file, buf, 4);
    }
    close(file);
}
