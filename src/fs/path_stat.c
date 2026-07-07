#include "fs_private.h"

error_t path_stat
(path_t* p, fs_stat_t* out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check users' input - p is checked in shadow null */
        (res = (out) ? success : null_pointer) ||
        (res = str_add_shadow_null(p)) ||
        /* Give the path to kernel to handle the rest */
        ((0 > syscall_2_linux(syscall_stat, (ssz)p->items, (ssz)out))
            ? (res = fs_error) : (res = success))
    ), res);
}
