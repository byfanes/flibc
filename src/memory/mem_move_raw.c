#include "memory_private.h"

error_t mem_move_raw
(void* dst, void* src, usz n)
{
    /* Init variables */
    u8 *d = dst, *s = src;
    usz i = 0;
    
    /* Check null case */
    if(!d || !s) { return null_pointer; }

    /* Its same addres skip it */
    if(d == s) { return success; }

    if(d < s) {
        /* dst is before src - left-to-right copy */
        for(; i < n; ++i) { d[i] = s[i]; }
    } else {
        /* dst is after src - right-to-left copy */
        /* Its i - 1 to avoid underflowing usz */
        for(i = n; i > 0; --i) { d[i - 1] = s[i - 1]; }
    }
    
    return success;
}
