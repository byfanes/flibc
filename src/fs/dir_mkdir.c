#include "fs_private.h"

error_t dir_mkdir
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Add null to make it cstr and pass to kernel - checks done in shadow null function */
        (res = str_add_shadow_null(path)) ||
        ((0 > syscall_2_linux(syscall_mkdir, (ssz)path->items, 0755))
            ? (res = fs_error) : (res = success))
    ), res);
}
