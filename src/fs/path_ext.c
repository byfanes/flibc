#include "fs_private.h"

error_t path_ext
(path_t* base, path_t* out)
{
    /* Init variables */
    ssz i = 0;
    sl_u8_t sl = {0};

    /* Check input */
    if(!base || !base->items || !base->count || !out || !out->items)
    { return null_pointer; }

    /* Zero the out so we can use cat without junk in the buffer */
    da_clear(out);

    /* Iterate over the buffer */
    /* Note: This only works for linux because of the paths */
    for(i = (ssz)base->count - 1; i >= 0; --i) {

        /* Found the end point */
        if(base->items[i] == '.') {
            /* Append the extension to buffer */
            i++;
            slice_set(&sl, &base->items[i], base->count - (usz)i);
            return str_cat_sl(out, &sl);
        }

        /* We could not find any extersion so return cleared buffer */
        if(base->items[i] == '/') { break; }
    }

    return success;
}
