#include "memory_private.h"

fc_error_t allocator_deinit
(allocator_t** set)
{
    /* Init variables */
    allocator_t* alloc = 0;
    ssize_t res = 0;

    /* Check user input */
    if(!set) { return fce_null_pointer; }

    /* Give back the memory to os */
    res = syscall_2(syscall_munmap, (ssize_t)alloc, RAW_ALLOCATION_SIZE);

    /* Check free syscall */
    if(res != 0) { return fce_memory_error; }

    /* TODO: Add system for checking the bit fields for not freed memory */

    return fce_success;
}
