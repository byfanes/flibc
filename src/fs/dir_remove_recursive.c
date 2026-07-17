#include "fs_private.h"

/* Temporary struct to use in callback */
typedef struct callback_pack_s callback_pack_t;
struct callback_pack_s {
    path_t full;
    error_t res;
};

static void dir_remove_recursive_callback
(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg)
{
    /* Init variables */
    callback_pack_t *pack = arg;

    /* Construct the full path and remove if its a file or iterate inside it if its a directory */
    (void)(
        str_clear(&pack->full) ||
        str_cat_sl(&pack->full, path) ||
        path_join(&pack->full, name) ||
        (pack->res = (is_dir) ? dir_remove_recursive(&pack->full)
                              : file_remove(&pack->full))
    );
}

error_t dir_remove_recursive
(path_t* path)
{
    /* Init variables */
    error_t res = success;
    allocator_t* alloc = 0;
    callback_pack_t pack = {0};

    return ((void)(
       /* Check inputs and get allocator */
       (res = (!path || !path->count || !path->items) ? null_pointer : success) ||
       (res = allocator_get_from_ptr(path->items, &alloc)) ||
       /* Init a scratch string buffer to use */
       (res = str_init(alloc, &pack.full, 512)) ||
       /* List dir and remove files and directories */
       (res = dir_list_dir(path, dir_remove_recursive_callback, &pack)) ||
       /* If there is an error we return the if not remove this directory too */
       (res = (pack.res) ? pack.res : dir_remove(path))
    ), (void)( /* Cleanup */
        str_deinit(&pack.full)
    ), res);
}
