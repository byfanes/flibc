#include "memory_private.h"

error_t mem_zeroed_len
(void* ptr, usz size)
{
    /* This is a wrapper function */
    return mem_set_raw(ptr, 0, size);
}
