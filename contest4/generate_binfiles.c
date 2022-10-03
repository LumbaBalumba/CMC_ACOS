#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    char str[] = "test.dt";
    FILE* file = fopen(str, "w");
    long long buf = LLONG_MIN;
    fwrite(&buf, sizeof(buf), 1, file);
    fclose(file);
}