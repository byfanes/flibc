#include "fs_private.h"

error_t path_cwd_get
(allocator_t* alloc, path_t* p)
{
    /* Init variables x*/
    error_t res = success;
    
    /* Values already checked in this block via str_init */
    if((res = str_init(alloc, p, MAX_PATH))) { return res; }

    /* Call and check the syscall */
    if(NULL == syscall_2_linux(syscall_getcwd, (ssz)p->items, (ssz)p->capacity))
    { return fs_error; }
    
    return success;
}
