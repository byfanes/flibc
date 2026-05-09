#include "memory.h"
#include "error.h"

fc_error_t memcpy
(slice_t dst, slice_t src)
{
    /* Init variables */
    u32 i = 0;
    
    /* Validate user inputs */
    if(!dst.base || !src.base) { return fce_mem_memcpy_nullptr; }
    if(src.count > dst.count) { return fce_mem_memcpy_smaller; }
    
    /* Iter 'src.count' times on the slices' bases and copy to dst from src */
    for(i = 0; i < src.count; ++i) { dst.base[i] = src.base[i]; }
    return fce_success;
}
