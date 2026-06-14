#include "fs_private.h"

error_t path_change_ext
(path_t* path, sl_u8_t* ext)
{
    /* Init variables */
    ssz i = 0;
    def_da_t *def = (void*)path;
    bool has_dot = false;
    bool has_ext_dot = false;
    error_t res = success;

    /* Check inputs - Right now we treat zero counts as null pointer */
    if(!path || !ext || !path->items || !path->count || !ext->items || !ext->count)
    { return null_pointer; }

    /* Check extension has a '.'  */
    has_ext_dot = (ext->items[0] == '.');

    /* Iterate over the buffer */
    /* Note: This only works for linux because of the paths */
    for(i = (ssz)path->count - 1; i >= 0; --i) {
        /* Found the end point */
        /* Set count to indicate right of the dot */
        if(path->items[i] == '.') {
            def->count = (usz)(i + 1);
            has_dot = true;
            break;
        }

        /* We could not find any extersion so we dont change anything */
        if(path->items[i] == '/') { break; }
    }

    /* Grow string memory if needed 1 is for it might need an '.'
     * so we are allocating a little bit more memory
     */
    if((res = str_grow_if(path, ext->count + 1))) { return res; }
    if(has_dot && has_ext_dot) {
        /* 'name.ext' + '.ext' or 'name.' + '.ext' cases in thise case
         * we have to remove one dont so we take a step back in the path
         */
        def->count--;
    } else if (!has_dot && !has_ext_dot) {
        /* 'name' + '.ext' case we append '.' here and we can access
         * directly here because realloc done before
         */
        def->items[def->count++] = '.';
    } else {
        /* 'name.ext' + 'ext' + 'name.' + 'ext' or 'name' + '.ext' case
         * we dont have to do anything here because when we concatenate them
         * result will have a '.'
         */
    }

    return da_push_sl(path, ext);
}
