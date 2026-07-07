#include "fs_private.h"

error_t dir_remove
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Add null to make it cstr and pass to kernel - checks done in shadow null function */
        (res = str_add_shadow_null(path)) ||
        ((0 > syscall_1_linux(syscall_rmdir, (ssz)path->items))
            ? (res = fs_error) : (res = success))
    ), res);
}
