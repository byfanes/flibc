#include "fs_private.h"

/* Update the callback*/
error_t dir_list_dir
(path_t *path,
 void (*callback)(sl_cstr_t *path, sl_cstr_t *name, bool is_dir, void *arg),
 void *arg)
{
    /* Init variables */
    error_t res = success;
    /* Unfortunately we can not use sl_cstr_t type so we need to convert it */
    void (*ptr)(os_slu8_t *path, os_slu8_t *name, bool is_dir, void *arg) =
        (void (*)(os_slu8_t *path, os_slu8_t *name, bool is_dir, void *arg))
            (uintptr_t)callback;

    /* Check inputs and os specific function */
    return ((void)(
        (res = (callback) ? success : null_pointer) ||
        (res = str_add_shadow_null(path)) ||
        (res = __os_dir_list_dir((void *)path, ptr, arg))
    ), res);
}
