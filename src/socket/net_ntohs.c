#include "socket_private.h"

u16 net_ntohs
(u16 x)
{
    union {
        u16 i;
        u8 c;
    } u = { 1 };
    return u.c ? bswap16(x) : x;
}
