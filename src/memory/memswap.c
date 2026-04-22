#include "memory.h"
#include "error.h"

fc_error_t fc_memswap
(def_slice_t lhs, def_slice_t rhs)
{
    uint8_t c = 0;
    uint32_t i = 0;
    if(!lhs.base || !rhs.base) { return fce_mem_memswap_nullptr; }
    if(lhs.count != rhs.count) { return fce_mem_memswap_diffsize; }
    for(; i < lhs.count; ++i) {
        c = *lhs.base;
        *(lhs.base++) = *rhs.base;
        *(rhs.base++) = c;
    }
    return fce_success;
}
