#include "memory.h"
#include "error.h"

fc_error_t fc_memswap
(def_slice_t lhs, def_slice_t rhs)
{
    if(!lhs.base || !rhs.base) { return fce_mem_memswap_nullptr; }
    if(lhs.count != rhs.count) { return fce_mem_memswap_diffsize; }
    byte_t* plhs = lhs.base;
    byte_t* prhs = rhs.base;
    for(uint32_t i = 0; i < lhs.count; ++i) {
        uint8_t c = *plhs;
        *(plhs++) = *prhs;
        *(prhs++) = c;
    }
    return fce_success;
}
