#include "memory_private.h"

fc_error_t set_slice
(const void* sl, const void* base, usize_t count)
{
    /* slice_u8 can be assign because its defined in memory.h
     * we will convert this type to perform out actions
     */
    slice_dummy_t* dummy = 0;

    /* Validate user inputs */
    if(!sl) { return fce_null_pointer; }
    if(!base && count) { return fce_invalid_slice_assignment; }

    /* Set the data */
    dummy = (void*)sl;
    dummy->base  = (void*)base;
    dummy->count = count;

    return fce_success;
}
