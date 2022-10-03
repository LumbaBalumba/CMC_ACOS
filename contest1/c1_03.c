#include <stdio.h>

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

int main()
{
    unsigned long n;
    if (!scanf("%lu", &n))
        return 0;
    for (unsigned i = 1; i < n; ++i) {
        printf("0 ");
    }
    printf("\n");
    for (unsigned i = 1; i < n; ++i) {
        for (unsigned j = 1; j < n; ++j) {
            printf("%lu ", mod_div(i, j, n));
        }
        printf("\n");
    }
}

//Конкретно сдесь у меня вылез TL, можете поправить и пользоваться если есть
//такое желание