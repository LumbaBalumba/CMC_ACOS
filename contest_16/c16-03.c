#include <stdlib.h>
#include <stdio.h>


int
main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    int *arr = calloc(n, sizeof(*arr));
    for (int i = 0; i < n - 4; ++i) {
        scanf("%d", &arr[i]);
    }
    int curr;
    while (scanf("%d", &curr) != EOF) {
        int count = 0;
        for (; curr < n - 2 && arr[curr - 2]; ++count) {
            curr = arr[curr - 2];
        }
        printf("%d\n", count);
    }
}
