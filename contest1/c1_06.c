#include <stdio.h>
#include <stdlib.h>

enum 
{ 
    INCORRECT_INPUT = 125,
    NULL_PTR = 1,
    MAX_ARR_SIZE = 10000,
};

int
main()
{
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        return INCORRECT_INPUT;
    }
    if (n <= 0 || n > MAX_ARR_SIZE) {
        return NULL_PTR;
    }
    int* arr = calloc(n, sizeof(*arr));
    if (arr == NULL) {
        return INCORRECT_INPUT;
    }
    for (int i = 0; i < m; ++i) {
        int cmd;
        if (scanf("%d", &cmd) != 1) {
            fprintf(stderr, "Input error\n");
            return INCORRECT_INPUT;
        }
        switch (cmd) {
        case 1: {
            int l, r, s;
            if (scanf("%d%d%d", &l, &r, &s) != 3) {
                fprintf(stderr, "Input error\n");
                return INCORRECT_INPUT;
            }
            for (int j = l; j < r; ++j) {
                arr[j] += s;
            }
            break;
        }
        case 2: {
            int l, r, res = 0;
            if (scanf("%d%d", &l, &r) != 2) {
                fprintf(stderr, "Input error\n");
                return INCORRECT_INPUT;
            }
            for (int j = l; j < r; ++j) {
                res += arr[j];
            }
            printf("%d\n", res);
            break;
        }
        default:
            break;
        }
    }
}
