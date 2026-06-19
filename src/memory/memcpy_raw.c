#include "memory_private.h"

error_t memcpy_raw
(void* dst, void* src, usz n)
{
    /* Init variables */
    u8 *d = dst, *s = src;
    usz i = 0;

    /* Check null case */
    if(!d || !s) { return null_pointer; }

    /* Copy memory */
    for(; i < n; ++i) { d[i] = s[i]; }

    return success;
}
