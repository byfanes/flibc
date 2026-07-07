#include "memory_private.h"

error_t mem_cpy_raw
(void* dst, const void* src, usz n)
{
    /* Init variables */
    u8 *d = dst;
    const u8* s = src;

    /* Check null case */
    if(!d || !s) { return null_pointer; }

    /* Copy memory */
    for(; n; n--) { *d++ = *s++; }

    return success;
}
