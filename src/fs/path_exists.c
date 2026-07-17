#include "fs_private.h"

error_t path_exists
(path_t* p, bool* out)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check out parameter - defualt value set in os layer */
        (res = (!out) ? null_pointer : success) ||
        /* Convert string to c-string - p checked here */
        (res = str_add_shadow_null(p)) ||
        /* Ask os layer to check the path */
        (res = __os_path_exists(p->items, out))
    ), res);
}
