#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int i_sqrt(int N)
{
    int msb = 0;
    int n = N;
    while (n > 1) {
        n >>= 1;
        msb++;
    }
    int a = 1 << msb;
    int result = 0;
    while (a != 0) {
        if ((result + a) * (result + a) <= N)
            result += a;
        a >>= 1;
    }
    return result;
}


int main()
{
    int N = 36;
    printf("%d\n", i_sqrt(N));
    return 0;
}