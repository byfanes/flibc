#include "memory_private.h"

error_t __mem_free_sl
(void* set)
{
    error_t res = success;
    slice_dummy_t *sl = set;
    
    return ((void)(
        (res = (sl) ? success : null_pointer) ||
        (res = mem_free(&sl->items)) ||
        (res = (sl->count = 0, success))
    ), res);
}
