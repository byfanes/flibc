#include "memory.h"
#include "error.h"

fc_error_t fc_memcmp
(ptr_header_t lhs, ptr_header_t rhs, bool* res)
{
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }
    if(lhs.len != rhs.len) { return fce_mem_memcmp_diffsize; }
    uint32_t count = lhs.len;
    for (uint32_t i = 0; i < count; ++i) {
        if(((char*)lhs.base)[i] != ((char*)rhs.base)[i]) {
            *res = false;
            return fce_success;
        }
    }
    *res = true;
    return fce_success;
}
