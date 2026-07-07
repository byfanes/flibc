#include "memory_private.h"

error_t mem_cmp_raw
(const void* lhs, const void* rhs, usz n, bool* out)
{
    /* Init variables */
    const u8 *l = lhs, *r = rhs;
    usz i = 0;

    /* Null case */
    if(!l || !r || !out) { return null_pointer; }

    /* Iterate over the bases and compare them */
    for(; i < n; ++i) {
        if(l[i] != r[i]) {
            /* Does not match */
            *out = false;
            return success;
        }
    }

    /* Does match */
    *out = true;
    return success;
}
