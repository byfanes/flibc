#include "memory_private.h"

error_t allocator_init
(allocator_t** set)
{
    /* Init variables */
    allocator_t* alloc = 0;
    sl_u8_t sl = {0};

    /* Check input */
    if(!set) { return null_pointer; }

    /* Syscall for memory allocation */
    alloc = (allocator_t*)(uintptr_t) syscall_6_linux(syscall_mmap, 0, RAW_ALLOCATION_SIZE,
        (PROT_READ|PROT_WRITE), (MAP_PRIVATE|MAP_ANONYMOUS), (ssz)(-1), 0);

    /* Error check */
    if(!alloc || alloc == MMAP_FAILED) { return memory_error; }

    /* No needed for checking already done earlier */
    set_slice(&sl, alloc, sizeof(allocator_t));

    /* Zero-ed the struct so bitfields are zero now */
    memset(&sl, 0);

    /* This is an default allocator so we can use default functions */
    alloc->meta.alloc_pointer = allocator_alloc_pointer;
    alloc->meta.free_pointer = allocator_free_pointer;
    alloc->meta.init = allocator_init;
    alloc->meta.deinit = allocator_deinit;
    alloc->meta.overflow = allocator_overflow;
    alloc->meta.underflow = allocator_underflow;
    alloc->meta.mutex.state = 0;
    alloc->meta.next = 0;

    *set = alloc;
    return success;
}
