#include "memory.h"
#include "error.h"

fc_error_t fc_memcmp_min
(ptr_header_t lhs, ptr_header_t rhs, bool* res)
{
    if(!lhs.base || !rhs.base || !res) { return fce_mem_memcmp_nullptr; }
    uint32_t count = (lhs.len > rhs.len) ? rhs.len : lhs.len;
    for (uint32_t i = 0; i < count; ++i) {
        if(((char*)lhs.base)[i] != ((char*)rhs.base)[i]) {
            *res = false;
            return fce_success;
        }
    }
    *res = true;
    return fce_success;
}
