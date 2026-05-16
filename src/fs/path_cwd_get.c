#include "fs_private.h"

error_t path_cwd_get
(allocator_t* alloc, path_t* p)
{
    error_t res = success;
    ssize_t ret = 0;
    
    /* Values already checked in this block via str_init */
    if((res = str_init(alloc, p, MAX_PATH))) { return res; }

    /* Call and check the syscall */
    ret = syscall_2(syscall_getcwd, p->items, (ssize_t)p->capacity);
    if(ret == 0) { return fs_error; }
    
    return success;
}
