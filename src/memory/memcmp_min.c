#include "memory.h"
#include "error.h"

fc_error_t fc_memcmp_min
(def_slice_t lhs, def_slice_t rhs, bool* res)
{
    uint32_t count = 0, i = 0;
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }
    count = (lhs.count > rhs.count) ? rhs.count : lhs.count;
    for (; i < count; ++i) {
        if(lhs.base[i] != rhs.base[i]) {
            *res = false;
            return fce_success;
        }
    }
    *res = true;
    return fce_success;
}
