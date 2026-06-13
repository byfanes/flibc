#include "parse_private.h"

u16 bswap16
(u16 x)
{
    return (u16)(x<<8 | x>>8);
}
