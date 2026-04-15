#include "memory.h"
#include "error.h"

fc_error_t fc_memswap
(ptr_header_t lhs, ptr_header_t rhs)
{
    if(!lhs.base || !rhs.base) { return fce_mem_memswap_nullptr; }
    if(lhs.len != rhs.len) { return fce_mem_memswap_diffsize; }
    char* plhs = lhs.base;
    char* prhs = rhs.base;
    for(uint32_t i = 0; i < lhs.len; ++i) {
        uint8_t c = *plhs;
        *(plhs++) = *prhs;
        *(prhs++) = c;
    }
    return fce_success;
}
