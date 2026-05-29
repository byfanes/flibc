#include "fs_private.h"

/* Temporary struct to use in callback */
typedef struct callback_pack_s callback_pack_t;
struct callback_pack_s {
    path_t full;
    error_t res;
};

static void callback
(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg)
{
    /* Init variables */
    callback_pack_t *pack = arg;

    /* Construct the full path */
    str_clear(&pack->full);
    strcat_sl(&pack->full, path);
    path_join(&pack->full, name);

    if(is_dir) {
        pack->res = dir_remove_recursive(&pack->full);
    } else {
        pack->res = file_remove(&pack->full);
    }
}

error_t dir_remove_recursive
(path_t* path)
{
    /* Init variables */
    error_t res = success;
    allocator_t* alloc = 0;
    callback_pack_t pack = {0};

    /* Check inputs and get allocator */
    if(!path || !path->count || !path->items) { return null_pointer; }
    if((res = allocator_get_from_ptr(path->items, &alloc))) { return res; }
    if((res = str_init(alloc, &pack.full, 512))) { return res; }

    /* If there is an error in dir_list_dir if will
     * be skipped and dir_list_dir's error will be used
     */
    if(!(res = dir_list_dir(path, callback, &pack))) {
        /* If dir_list_dir does not fail use pack's results
         * to check if there is a file/directory which is not removed
         */
        res = pack.res;
        /* If there is not an error we remove given directory too */
        if(!res) { res = dir_remove(path); }
    }

    /* Free the memory and return */
    str_deinit(&pack.full);
    return res;
}
