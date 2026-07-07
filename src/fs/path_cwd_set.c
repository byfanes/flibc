#include "fs_private.h"

error_t path_cwd_set
(path_t* p)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* p checked here and convert it to a c-string and give it to kernel */
        (res = str_add_shadow_null(p)) ||
        (res = (0 > syscall_1_linux(syscall_chdir, (ssz)p->items)
             ? fs_error : success))
    ), res);
}
