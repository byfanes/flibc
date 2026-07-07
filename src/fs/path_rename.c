#include "fs_private.h"

error_t path_rename
(path_t* from, path_t* to)
{
    /* Init variables */
    error_t res = success;
    
    return ((void)(
        /* Validate user input and make them c-strings */
        (res = str_add_shadow_null(from)) ||
        (res = str_add_shadow_null(to)) ||
        /* Call the kernel and ask it to rename it */
        ((0 > syscall_2_linux(syscall_rename, (ssz)from->items, (ssz)to->items))
            ? (res = fs_error) : (res = success))
    ), res);
}
