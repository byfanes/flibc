#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t malloc
(u32 size, void* set)
{
    /* Init variables */
    heap_header_t header = {0}, *base = 0;
    u32 i = 0;

    /* Validate user inputs */
    if(!size) { return fce_mem_malloc_zero; }
    if(!set) { return fce_mem_malloc_nullptr; }

    /* Set header alloced is user given size and raw is aligned size
     * there is additional arch_t end of the data which can be used in shadow null
     * tricks so we can just use last part if there is no capacity left to add a null
     * byte without changing the content.
     */
    header.alloced = size;
    size += sizeof(header) + sizeof(arch_t);
    i = size;
    size = (size + 7) & (u32)(~7);
    header.raw_alloced = size;

    /* Get memory from the os */
    base =  (void*)(uintptr_t) syscall_6(syscall_mmap, 0, size, (PROT_READ|PROT_WRITE),
        (MAP_PRIVATE|MAP_ANONYMOUS), (arch_t)(-1), 0);

    /* Error check */
    if(!base || base == MMAP_FAILED) { return fce_mem_malloc_mmap_failed; }

    /* Set shadow header */
    *base = header;

    /* Set user header */
    *(void**)set = base + 1;

    /* Null last chunk and align */
    for(;i < size; ++i) {
        ((u8*)base)[i] = 0;
    }

    return fce_success;
}
