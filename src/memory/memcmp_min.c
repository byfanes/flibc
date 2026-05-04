#include "memory.h"
#include "error.h"

fc_error_t memcmp_min
(slice_t lhs, slice_t rhs, bool* res)
{
    /* Init variables */
    u32 count = 0, i = 0;

    /* Validate user inputs */
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }

    /* Set min size */
    count = (lhs.count > rhs.count) ? rhs.count : lhs.count;

    /* Iterate over bases and compare them */
    for (; i < count; ++i) {
        if(lhs.base[i] != rhs.base[i]) {
            /* Does not match */
            *res = false;
            return fce_success;
        }
    }

    /* Does match */
    *res = true;
    return fce_success;
}
