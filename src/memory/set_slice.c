#include "memory_private.h"

fc_error_t set_slice
(const void* sl, const void* base, u32 count)
{
    /* slice_u8 can be assign because its defined in memory.h
     * we will convert this type to perform out actions
     */
    slice_u8* dummy = 0;
    
    /* Validate user inputs */
    if(!sl) { return fce_set_slice_null_ptr; }
    if(!base) { return fce_set_slice_cant_assing_null; }
    if(!count) { return fce_set_slice_cant_assing_zero; }

    /* Set the data */
    dummy = (void*)sl;
    dummy->base = (void*)base;
    dummy->count = count;
    
    return fce_success;
}
