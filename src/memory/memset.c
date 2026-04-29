#include "memory.h"
#include "error.h"

fc_error_t memset
(slice_t ptr, uint8_t c)
{
    /* Init variable */
    uint32_t i = 0;
    
    /* Validate user inputs */
    if(!ptr.base) { return fce_mem_memset_nullptr;}

    /* Iter 'i' times on the slice's base and set to 'c' */
    for(; i < ptr.count; ++i) { ptr.base[i] = (char)c; }

    return fce_success;
}
