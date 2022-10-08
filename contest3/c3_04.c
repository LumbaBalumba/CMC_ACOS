int
satsum(int a, int b)
{
    enum
    {
        MY_INT_MAX = 2147483647,
        MY_INT_MIN = -2147483648
    };
    int res;
    if((a > 0 && b > 0) && (a > MY_INT_MAX - b)) {
        res = MY_INT_MAX;
    } else if((a < 0 && b < 0) && (a < MY_INT_MIN - b)) {
        res = MY_INT_MIN;
    } else {
        res = a + b;
    }
    return res;
}