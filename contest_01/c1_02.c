#include <stdio.h>

enum 
{
    NUMBERS = 10,
    LETTERS = 26,
    MAX_SYM_CODE = 63
};

int 
to_ascii(int c)
{
    int res = 0;
    if ('0' <= c && '9' >= c) {
        res = 1 + c - '0';
    } else if ('a' <= c && 'z' >= c) {
        res = 1 + NUMBERS + c - 'a';
    } else if ('A' <= c && 'Z' >= c) {
        res = 1 + NUMBERS + LETTERS + c - 'A';
    }
    return res;
}

int 
from_ascii(int c)
{
    int res = 0;
    if (c == 0) {
        res = '@';
    } else if (c == MAX_SYM_CODE) {
        res = '#';
    } else if (c >= 1 && c <= NUMBERS) {
        res = '0' + c - 1;
    } else if (c >= NUMBERS + 1 && c <= NUMBERS + LETTERS) {
        res = 'a' + c - NUMBERS - 1;
    } else if (c >= LETTERS + 1 && c <= MAX_SYM_CODE - 1) {
        res = 'A' + c - NUMBERS - LETTERS - 1;
    }
    return res;
}

int 
main(void)
{
    int c;
    while ((c = getchar()) != EOF) {
        if (('0' > c || '9' < c) && ('a' > c || 'z' < c) && ('A' > c || 'Z' < c)) {
            continue;
        }
        c = to_ascii(c);
        c ^= 0b00001000;
        c &= 0b11111011;
        c = from_ascii(c);
        putchar(c);
    }
}