#include <limits.h>
#include <stdio.h>

void 
bit_swp(unsigned char* p)
{
    unsigned char tmp = 0;
    for (int i = 0; i < CHAR_BIT; ++i) {
        printf("%d %d\n", *p, tmp);
        tmp <<= 1;
        tmp += *p & 1;
        *p >>= 1;
    }
    *p = tmp;
}

void 
swap(unsigned char* a,
    unsigned char* b)
{
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

STYPE
bit_reverse(STYPE value)
{
    UTYPE z = -1;
    size_t cnt = 0;
    while (z) {
        z >>= 1;
        ++cnt;
    }
    cnt /= CHAR_BIT;
    UTYPE tmp = value;
    for (int i = 1; i <= cnt / 2; ++i) {
        swap((unsigned char*) &tmp, ((unsigned char*) &tmp) + cnt - i);
        bit_swp((unsigned char*) &tmp);
        bit_swp(((unsigned char*) &tmp) + cnt - i);
    }
    return (STYPE) tmp;
}