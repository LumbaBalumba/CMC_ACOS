#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    FUNCTION_STACK_SIZE = 64,
    FIRST_FUNC_ARG = 3
};

struct FunctionStack
{
    char buf[FUNCTION_STACK_SIZE];
};


int
main(int argc, char *argv[])
{
    void *lib = dlopen(argv[1], RTLD_LAZY);
    if (!lib) {
        _exit(EXIT_FAILURE);
    }
    struct FunctionStack stack = {};
    size_t size = 0;
    void *func = dlsym(lib, argv[2]);
    if (!func) {
        dlclose(lib);
        _exit(EXIT_FAILURE);
    }
    for (int i = 4; i < argc; ++i) {
        switch (argv[FIRST_FUNC_ARG][i - FIRST_FUNC_ARG]) {
            case 's': {
                char *res = argv[i];
                *(char **) (stack.buf + size) = res;
                size += sizeof(res);
                break;
            }
            case 'i': {
                char *eptr = NULL;
                errno = 0;
                long tmp = strtol(argv[i], &eptr, 10);
                if (errno || eptr == argv[i] || *eptr || tmp != (int) tmp) {
                    dlclose(lib);
                    fprintf(stderr, "Integer number conversion error\n");
                    _exit(EXIT_FAILURE);
                }
                int res = (int) tmp;
                *(int *) (stack.buf + size) = res;
                size += sizeof(res);
                break;
            }
            case 'd': {
                char *eptr = NULL;
                errno = 0;
                double res = strtod(argv[i], &eptr);
                if (errno || eptr == argv[i] || *eptr) {
                    dlclose(lib);
                    fprintf(stderr, "Floating-point number conversion error\n");
                    _exit(EXIT_FAILURE);
                }
                *(double *) (stack.buf + size) = res;
                size += sizeof(res);
                break;
            }
            default: {
                dlclose(lib);
                fprintf(stderr, "Incorrect number error\n");
                _exit(EXIT_FAILURE);
            }
        }
    }
    switch (argv[FIRST_FUNC_ARG][0]) {
        case 'v': {
            ((void (*)(struct FunctionStack)) func)(stack);
            break;
        }
        case 'i': {
            int res = ((int (*)(struct FunctionStack)) func)(stack);
            printf("%d\n", res);
            break;
        }
        case 's': {
            char *res = ((char *(*)(struct FunctionStack)) func)(stack);
            printf("%s\n", res);
            break;
        }
        case 'd': {
            double res = ((double (*)(struct FunctionStack)) func)(stack);
            printf("%.10g\n", res);
            break;
        }
        default: {
            dlclose(lib);
            _exit(EXIT_FAILURE);
        }
    }
    fflush(stdout);
    dlclose(lib);
    _exit(EXIT_SUCCESS);
}