#include "parse_private.h"

u32 bswap32
(u32 x)
{
    return x>>24 | ( x>>8 & 0xff00) | (x<<8 & 0xff0000) | x<<24;
}
