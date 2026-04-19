#include "memory.h"
#include "error.h"

fc_error_t fc_memset
(def_slice_t ptr,uint8_t c)
{
    uint32_t i;
    if(!ptr.base) { return fce_mem_memset_nullptr;}
    for(i = 0; i < ptr.count; ++i) {
        ptr.base[i] = c;
    }
    return fce_success;
}
