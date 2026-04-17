#include "memory.h"
#include "error.h"

fc_error_t fc_memcmp
(def_slice_t lhs, def_slice_t rhs, bool* res)
{
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }
    if(lhs.count != rhs.count) { return fce_mem_memcmp_diffsize; }
    uint32_t count = lhs.count;
    for (uint32_t i = 0; i < count; ++i) {
        if(lhs.base[i] != rhs.base[i]) {
            *res = false;
            return fce_success;
        }
    }
    *res = true;
    return fce_success;
}
