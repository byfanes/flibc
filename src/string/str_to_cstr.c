#include "string_private.h"

fc_error_t str_to_cstr
(allocator_t* alloc, str_t* base, char** out)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice(u8) dst = {0}, src = {0};

    /* Validate user input */
    if(!alloc || !out || !base) { return fce_null_pointer; }

    /* If string is null return a null cstr */
    if(!base->items || !base->count) {
        return calloc(alloc, 1, out);
    }

    if((res = malloc(alloc, base->count + 1, out))) { return res; }

    /* Set slices for copying */
    set_slice(&src, base->items, base->count);
    set_slice(&dst, (*out), base->count);

    /* Copy the data and set last byte to null */
    res = memcpy(&dst, &src);
    (*out)[base->count] = 0;

    if(res) { free(out); return res; }
    return fce_success;
}
