STYPE
bit_reverse(STYPE value)
{
    UTYPE z = -1;
    unsigned sz = 0;
    for(; z != 0; ++sz) {
        z >>= 1;
    }
    UTYPE res = 0, tmp = value;
    for(unsigned i = 0; i < sz; ++i) {
        if(tmp & (1ull << i)) {
            res |= 1ull << ((sz - 1ull) - i);
        }
    }
    return (STYPE) res;
}