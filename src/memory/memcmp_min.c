#include "memory_private.h"
#include "error.h"

fc_error_t __memcmp_min
(void* lhs, void* rhs, usize_t el_size, bool* res)
{
    /* Init variables */
    slice(u8) *lsl = lhs, *rsl = rhs;
    usize_t count = 0, i = 0;

    /* Validate user inputs */
    if(!lsl || !rsl || !res || !lsl->base || !rsl->base) { return fce_null_pointer; }
    if(!el_size) { return fce_elsize_zero; }

    /* Set min size */
    count = (lsl->count > rsl->count) ? rsl->count : lsl->count;

    /* Iterate over bases and compare them */
    for (; i < count * el_size; ++i) {
        if(lsl->base[i] != rsl->base[i]) {
            /* Does not match */
            *res = false;
            return fce_success;
        }
    }

    /* Does match */
    *res = true;
    return fce_success;
}
