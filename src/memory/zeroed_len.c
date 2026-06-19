#include "memory_private.h"

error_t zeroed_len
(void* ptr, usz size)
{
    /* This is a wrapper function */
    return memset_raw(ptr, 0, size);
}
