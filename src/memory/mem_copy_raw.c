#include "memory_private.h"

error_t mem_copy_raw
(void *dst, const void *src, usz n)
{
    /* Init variables */
    u8 *d = (u8 *)dst;
    const u8* s = (const u8 *)src;

    /* Check null case */
    if(!d || !s) { return null_pointer; }

    /* Copy memory */
    while(n--) { *d++ = *s++; }

    return success;
}
