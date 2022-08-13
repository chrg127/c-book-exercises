#include <stdio.h>

#define SWAP(T, x, y)       \
    do {                    \
        T tmp = (x);        \
        (x)   = (y);        \
        (y)   = tmp;        \
    } while (0)

int main(void)
{
    int x = 1, y = 2;
    printf("x = %d, y = %d\n", x, y);
    SWAP(int, x, y);
    printf("x = %d, y = %d\n", x, y);
    return 0;
}
