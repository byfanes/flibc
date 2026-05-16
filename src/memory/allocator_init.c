#include "memory_private.h"

error_t allocator_init
(allocator_t** set)
{
    /* Init variables */
    allocator_t* alloc = 0;
    slice(u8) sl = {0};

    /* Check input */
    if(!set) { return null_pointer; }

    /* Syscall for memory allocation */
    alloc = (allocator_t*)(uintptr_t) syscall_6(syscall_mmap, 0, RAW_ALLOCATION_SIZE,
        (PROT_READ|PROT_WRITE), (MAP_PRIVATE|MAP_ANONYMOUS), (ssize_t)(-1), 0);

    /* Error check */
    if(!alloc || alloc == MMAP_FAILED) { return memory_error; }

    /* No needed for checking already done earlier */
    set_slice(&sl, alloc, sizeof(allocator_t));

    /* Zero-ed the struct so bitfields are zero now */
    memset(&sl, 0);

    *set = alloc;
    return success;
}
