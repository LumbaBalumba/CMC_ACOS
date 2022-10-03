#include <stdio.h>

enum 
{
    INCORRECT_INPUT = 125,
    MAX_ARR_SIZE = 10
};

void 
print_arr(
    int size,
    int* arr)
{
    for (int i = 0; i < size; ++i) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void 
perms(
    int size,
    int cnt,
    int arr[MAX_ARR_SIZE],
    int u[MAX_ARR_SIZE])
{
    if (size == cnt) {
        print_arr(size, arr);
    } else {
        for (int i = 0; i < size; ++i) {
            if (u[i] == 1)
                continue;
            arr[cnt] = i + 1;
            u[i] = 1;
            perms(size, cnt + 1, arr, u);
            u[i] = 0;
        }
    }
}

int
main()
{
    int arr[MAX_ARR_SIZE];
    int u[MAX_ARR_SIZE];
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Input error\n");
        return INCORRECT_INPUT;
    }
    if (n < 0 || n > MAX_ARR_SIZE) {
        return INCORRECT_INPUT;
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
        u[i] = 0;
    }
    perms(n, 0, arr, u);
}