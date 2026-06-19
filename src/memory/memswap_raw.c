#include "memory_private.h"

error_t memswap_raw
(void* lhs, void* rhs, usz n)
{
    /* Init variables */
    u8 *l = lhs, *r = rhs;
    usz i = 0;
    u8 c = 0;

    /* Check null case */
    if(!l || !r) { return null_pointer; }

    /* Swap memory */
    for(; i < n; ++i) {
        c = l[i];
        l[i] = r[i];
        r[i] = c;
    }

    return success;
}
