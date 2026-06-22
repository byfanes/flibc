#include "fs_private.h"

error_t dir_remove
(path_t* path)
{
    /* Validate input */
    if(!path || !path->items || !path->count) { return null_pointer; }

    /* Add null byte and call remove syscall */
    str_add_shadow_null(path);
    if(0 > syscall_1_linux(syscall_rmdir, (ssz)path->items))
    { return fs_error; }

    return success;
}
