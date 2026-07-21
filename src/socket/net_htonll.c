#include "socket_private.h"

u64 net_htonll
(u64 x)
{
    union {
        u16 i;
        u8 c;
    } u = {1};

    return u.c ? bswap64(x) : x;
}
