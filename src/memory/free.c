#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t free
(void* ptr)
{
    /* Init variables */
    heap_header_t *base = 0;
    u32 cap = 0, res = 0;
    
    /* Validate user inputs */
    if(!ptr) { return fce_success; }
    
    base = *(void**)ptr;
    
    /* Validate user inputs */
    if(!base) { return fce_success; }

    /* Get shadow header and capacity */
    base--;
    cap = base->raw_alloced;

    /* Give back the memory to os */
    res = (u32) syscall_2(syscall_munmap, (arch_t)base, cap);

    /* Error check */    
    if(res != 0) { return fce_mem_free_munmap_failed; }

    /* Set pointers state to zero as a correct state */
    *(void**)ptr = 0;
    return fce_success;
}
