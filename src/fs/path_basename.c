#include "fs_private.h"

error_t path_basename
(path_t* base, path_t* out)
{
    /* Init variables */
    ssize_t i = 0;
    ssize_t start = 0;
    ssize_t off = 0;
    bool is_set = false;
    sl_u8_t sl = {0};

    /* Check input */
    if(!base || !base->items || !base->count || !out || !out->items)
    { return null_pointer; }

    /* Zero the out so we can use cat without junk in the buffer */
    da_clear(out);

    /* Set start for cases like 'src/name' which does not have '.' */
    start = (ssize_t)base->count;

    /* Note: This only works for linux because of the paths */
    i = (ssize_t)base->count - 1;

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
    set_slice(&sl, &base->items[i], (usize_t)(start - i - off));
    strcat_sl(out, &sl);

    return success;
}
