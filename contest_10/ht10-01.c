#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>

enum
{
    FILE_SIZE = 64 * 1024,
    PAGE_SIZE = 512
};

int
main(int argc, char **argv)
{
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    long tmp_fd = open(argv[1], O_RDONLY, 0666);
    if (tmp_fd == -1) {
        exit(EXIT_FAILURE);
    }
    int fd = (int) tmp_fd;
    errno = 0;
    char *eptr = NULL;
    unsigned long table_offset = strtoul(argv[2], &eptr, 16);
    if (errno || eptr == argv[2] || *eptr || table_offset != (unsigned short) table_offset) {
        exit(EXIT_FAILURE);
    }
    unsigned char *mem = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (mem == NULL) {
        exit(EXIT_FAILURE);
    }
    unsigned virt_addr;
    while (scanf("%xu", &virt_addr) == 1) {
        unsigned short page_no = virt_addr / PAGE_SIZE, page_off =
                (((unsigned short) mem[table_offset + 2 * page_no + 1]) << CHAR_BIT) + mem[table_offset + 2 * page_no];
        printf("%u\n", (((unsigned short) mem[page_off + virt_addr % PAGE_SIZE + 1]) << CHAR_BIT) +
                mem[page_off + virt_addr % PAGE_SIZE]);
    }
    if (munmap(mem, FILE_SIZE) < 0) {
        exit(EXIT_FAILURE);
    }
    if (close(fd) < 0) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
