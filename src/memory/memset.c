#include "memory.h"
#include "error.h"

fc_error_t memset
(slice_t ptr, u8 c)
{
    /* Init variable */
    u32 i = 0;
    
    /* Validate user inputs */
    if(!ptr.base) { return fce_mem_memset_nullptr;}

    /* Iter 'i' times on the slice's base and set to 'c' */
    for(; i < ptr.count; ++i) { ptr.base[i] = c; }

    return fce_success;
}
