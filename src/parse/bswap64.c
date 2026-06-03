#include "parse_private.h"

u64 bswap64
(u64 x)
{
    return (u64)bswap32((u32)x) << 32 | (u64)bswap32((u32)(x>>32));
}
