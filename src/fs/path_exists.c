#include "fs_private.h"

error_t path_exists
(path_t* p, bool* out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check out parameter if its valid set it to false(default) state */
        (res = (!out) ? null_pointer : (*out = false, success)) ||
        /* Convert string to c-string - p checked here */
        (res = str_add_shadow_null(p)) ||
        /* Give to the kernel if it exists it success */
        (*out = (0 == syscall_2_linux(syscall_access, (ssz)p->items, F_OK)))
    ), res);
}
