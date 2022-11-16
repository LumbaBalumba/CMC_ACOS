#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int
main(int argc, char *argv[])
{
    if (argc <= 1) {
        return EXIT_FAILURE;
    }
    char *ep = NULL;
    double res = strtod(argv[1], &ep);
    if (*ep || ep == argv[1]) {
        fprintf(stderr, "data is too big\n");
        return EXIT_FAILURE;
    }
    res = round(res * 10000.0f) / 10000.0f;
    for (int i = 2; i < argc; ++i) {
        char *eptr = NULL;
        double tmp = strtod(argv[i], &eptr);
        if (*eptr || eptr == argv[i] || fabs(tmp) > 100.0) {
            fprintf(stderr, "data is too big\n");
            return EXIT_FAILURE;
        }
        res *= 1.0f + tmp / 100.0f;
        res = round(res * 10000.0f) / 10000.0f;
    }
    printf("%.4f\n", res);
}