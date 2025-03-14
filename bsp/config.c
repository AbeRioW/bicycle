#include "config.h"

void delay_us(uchar n) //延时 2*n+2 us
{
    while (--n)
        ;
}

void delay_ms(uint z)
{
    uint i, j;
    for (i = z; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}

