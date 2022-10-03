#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    MASK = 0xfe00,
};

int
main(int argc, char *argv[])
{
    if (argc < 1) {
        return EXIT_FAILURE;
    } else {
        const char template[] = "rwxrwxrwx";
        for (int i = 1; i < argc; ++i) {
            char *eptr = NULL;
            long cur = strtol(argv[i], &eptr, 8);
            if (cur != (short) cur || *eptr || eptr == argv[i] || (cur & MASK)) {
                return EXIT_FAILURE;
            } else {
                for (unsigned int j = 9; j > 0; --j) {
                    if ((1u << (j - 1)) & cur) {
                        printf("%c", template[9 - j]);
                    } else {
                        printf("-");
                    }
                }
            }
            printf("\n");
        }
    }
}