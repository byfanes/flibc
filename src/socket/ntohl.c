#include "socket_private.h"

u32 ntohl
(u32 x)
{
    union {
        u16 i;
        u8 c;
    } u = { 1 };
    return u.c ? bswap32(x) : x;
}
