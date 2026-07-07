#include "fs_private.h"

/* Temporary struct to use in callback */
typedef struct callback_pack_s callback_pack_t;
struct callback_pack_s {
    da_path_t* out;
    allocator_t* alloc;
};

static void __path_get_all_files_callback
(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg)
{
    /* Init variables */
    callback_pack_t *pack = arg;
    path_t tmp = {0};

    /* Construct new path */
    str_init(pack->alloc, &tmp, 128);
    str_cat_sl(&tmp, path);

    /* Append the name and its finished */
    path_join(&tmp, name);

    if(is_dir) {
        /* Its a directory so continue with rescursion */
        str_add_shadow_null(&tmp);
        path_get_all_files(&tmp, pack->out);
        da_deinit(&tmp);
    }
    else {
        /* If its a regular file append to list */
        da_push(pack->out, &tmp);
    }
}

error_t path_get_all_files
(path_t* p, da_path_t* out)
{
    /* Init variables */
    callback_pack_t pack = {0};
    error_t res = success;
    pack.out = out;

    return ((void)(
        /* Check inputs and get allocator */
        (res = (p && p->items && out && out->items) ? success : null_pointer) ||
        (res = allocator_get_from_ptr(out->items, &pack.alloc)) ||
        /* Give callback to list function which will handle everything */
        (res = dir_list_dir(p, __path_get_all_files_callback, &pack))
    ), res);
}
