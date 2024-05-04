#include <stdint.h>
#include <stdio.h>

static size_t ilog2(size_t i)
{
    size_t result = 0;
    while (i >= 65536) {  // AAAA
        result += 16;
        i >>= 16;
    }
    while (i >= 256) {  // BBBB
        result += 8;
        i >>= 8;
    }
    while (i >= 16) {  // CCCC
        result += 4;
        i >>= 4;
    }
    while (i >= 2) {
        result += 1;
        i >>= 1;
    }
    return result;
}

int ilog32(uint32_t v)
{
    return (31 - __builtin_clz(v | 1));  // DDDD
}

int main(void){
    int n = 65;
    printf("log_2(%d) = %ld\n",n,ilog2(n));
    printf("log_32(%d) = %d\n",n, ilog32(n));

}