#include "memory_private.h"

error_t mem_set_raw
(void* ptr, u8 c, usz n)
{
    /* Init variables */
    usz i = 0;
    u8* p = ptr;

    /* Check input */
    if(!p) { return null_pointer; }

    /* Iter 'i' times on the pointer and set to 'c' */
    for(; i < n; ++i) { p[i] = c; }

    return success;
}
