#include "fs_private.h"

error_t path_basename
(path_t* base, path_t* out)
{
    /* Init variables */
    ssz i = 0, start = 0, off = 0;
    bool is_set = false;
    sl_u8_t sl = {0};

    /* Check input */
    if(!base || !base->items || !base->count || !out || !out->items)
    { return null_pointer; }

    /* Zero the out so we can use cat without junk in the buffer */
    da_clear(out);

    /* Set start for cases like 'src/name' which does not have '.' */
    start = (ssz)base->count;

    /* Note: This only works for linux because of the paths */
    i = (ssz)base->count - 1;

    /* If its a directory skip the '/' and find directory name */
    if(base->items[i] == '/') { i--; off = 1;}

    for(; i >= 0; --i) {
        /* We found the starting point */
        if(!is_set && base->items[i] == '.') {
            is_set = true;
            start = i;
        }
        /* Find the end part */
        if(base->items[i] == '/') { ++i; break; }
    }

    /* Set the find part */
    slice_set(&sl, &base->items[i], (usz)(start - i - off));
    str_cat_sl(out, &sl);

    return success;
}
