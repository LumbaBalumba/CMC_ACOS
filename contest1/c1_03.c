#include <stdio.h>
#include <stdlib.h>

unsigned long
bin_pow(unsigned long a, unsigned long b, unsigned long m)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a % m;
    else if (b & 1)
        return bin_pow(a, b / 2, m) * bin_pow(a, b / 2, m) * a % m;
    else
        return bin_pow(a, b / 2, m) * bin_pow(a, b / 2, m) % m;
}

unsigned long
mod_div(unsigned long a, unsigned long b, unsigned long m)
{
    return a * bin_pow(b, m - 2, m) % m;
}

int
main()
{
    unsigned long n;
    if (!scanf("%lu", &n))
        return 0;
    for (unsigned i = 1; i < n; ++i) {
        printf("0 ");
    }
    printf("\n");
    unsigned long *arr = calloc(n - 1, sizeof(n));
    for (int i = 1; i < n; ++i) {
        arr[i - 1] = mod_div(1, i, n);
    }
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = 1; j < n; ++j) {
            printf("%lu ", arr[j - 1] * i % n);
        }
        printf("\n");
    }
}