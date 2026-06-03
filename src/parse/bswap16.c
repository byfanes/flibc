#include "parse_private.h"

u16 bswap16
(u16 x)
{
    return x<<8 | x>>8;
}
