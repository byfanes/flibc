#include "memory_private.h"

error_t slice_set
(const void* sl, const void* base, usz count)
{
    /* slice_u8 can be assign because its defined in memory.h
     * we will convert this type to perform out actions
     */
    slice_dummy_t* dummy = 0;

    /* Validate user inputs */
    if(!sl) { return null_pointer; }
    if(!base && count) { return invalid_slice_assignment; }

    /* Set the data */
    dummy = (void*)sl;
    dummy->items  = (void*)base;
    dummy->count = count;

    return success;
}
