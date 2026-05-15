#include "fs_private.h"

fc_error_t dir_mkdir
(path_t* path)
{
    /* Validate input */
    if(!path || !path->items || !path->count) { return fce_null_pointer; }
    
    /* Add null byte and call remove syscall */
    str_add_shadow_null(path);
    if(syscall_2(syscall_mkdir, path->items, 0755) != 0) { return fce_fs_error; }

    return fce_success;
}
