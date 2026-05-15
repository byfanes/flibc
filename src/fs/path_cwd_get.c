#include "fs_private.h"

fc_error_t path_cwd_get
(allocator_t* alloc, path_t* p)
{
    fc_error_t res = fce_success;
    ssize_t ret = 0;
    
    /* Values already checked in this block via str_init */
    if((res = str_init(alloc, p, MAX_PATH))) { return res; }

    /* Call and check the syscall */
    ret = syscall_2(syscall_getcwd, p->items, (ssize_t)p->capacity);
    if(ret == 0) { return fce_fs_error; }
    
    return fce_success;
}
