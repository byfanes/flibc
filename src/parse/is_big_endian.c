#include "parse_private.h"

bool is_big_endian
(void)
{
    union {
        u16 i;
        u8 c;
    } u = {1};

    return u.c == 0;
}
