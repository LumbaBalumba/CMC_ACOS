#include <stdlib.h>

int 
cmp(
    const void* pa,
    const void* pb)
{
    int a = *(int*)pa, b = *(int*)pb;
    int res = 0;
    if (a == b) {
        res = 0;
    } else if ((a & 1) == 0 && (b & 1) == 0) {
        res = a > b ? 1 : -1;
    } else if ((a & 1) == 0 && (b & 1) == 1) {
        res = -1;
    } else if ((a & 1) == 1 && (b & 1) == 0) {
        res = 1;
    } else if ((a & 1) == 1 && (b & 1) == 1) {
        res = a > b ? -1 : 1;
    }
    return res;
}

void 
sort_even_odd(
    size_t count,
    int* data)
{
    qsort(data, count, sizeof(data[0]), cmp);
}