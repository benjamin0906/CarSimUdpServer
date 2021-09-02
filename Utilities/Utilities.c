#include "types.h"

uint16 Swap16(uint16 Num)
{
    return (Num >> 8 | Num << 8);
}

uint32 Swap32(uint32 Num)
{
    uint32 ret = Num << 24;
    ret |= (Num << 8)&0x00FF0000;
    ret |= (Num >> 8)&0x0000FF00;
    ret |= (Num >> 24)&0x000000FF;
    return ret;
}

