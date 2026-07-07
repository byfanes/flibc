#include "fs_private.h"

error_t file_remove
(path_t* path)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Input checks done in shadow_null function */
        (res = str_add_shadow_null(path)) ||
        /* Remove the file via syscall and check the result */
        ((0 > syscall_1_linux(syscall_unlink, (ssz)path->items)) ? (res = fs_error) : success)
    ), res);
}
