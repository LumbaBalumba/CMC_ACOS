enum 
{
    MY_INT_MAX = 2147483647,
    MY_INT_MIN = -2147483648
};

int 
satsum(int v1, int v2)
{
    int res;
    if (v1 > MY_INT_MAX - v2) {
        res = MY_INT_MAX;
    } else if (v1 < MY_INT_MIN + v2) {
        res = MY_INT_MIN;
    } else {
        res = v1 + v2;
    }
    return res;
}
