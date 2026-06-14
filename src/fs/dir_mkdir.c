#include "fs_private.h"

error_t dir_mkdir
(path_t* path)
{
    /* Validate input */
    if(!path || !path->items || !path->count) { return null_pointer; }
    
    /* Add null byte and call mkdir syscall */
    str_add_shadow_null(path);
    if(0 != syscall_2_linux(syscall_mkdir, (ssz)path->items, 0755))
    { return fs_error; }

    return success;
}
