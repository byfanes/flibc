#include "fs_private.h"

error_t file_remove
(path_t* path)
{
    /* Validate input */
    if(!path || !path->items || !path->count) { return null_pointer; }

    /* Add null byte and call remove syscall */
    str_add_shadow_null(path);
    if(syscall_1(syscall_unlink, path->items) != 0) { return fs_error; }

    return success;
}
