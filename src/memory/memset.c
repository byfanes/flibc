#include "memory.h"
#include "error.h"

fc_error_t fc_memset
(ptr_header_t ptr,uint8_t c)
{
    if(!ptr.base) { return fce_mem_memset_nullptr;}
    for(uint32_t i = 0; i < ptr.len; ++i) {
        ((uint8_t*)ptr.base)[i] = c;
    }
    return fce_success;
}
