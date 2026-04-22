#include "memory.h"
#include "error.h"

fc_error_t memcmp
(def_slice_t lhs, def_slice_t rhs, bool* res)
{
    /* Init variables */
    uint32_t i = 0;

    /* Validate user inputs */
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }
    if(lhs.count != rhs.count) { return false; }

    /* Iterate over bases and compare them */
    for (; i < lhs.count; ++i) {
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
