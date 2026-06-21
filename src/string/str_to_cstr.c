#include "string_private.h"

error_t str_to_cstr
(allocator_t* alloc, str_t* base, char** out)
{
    /* Init variables */
    error_t res = success;
    sl_u8_t dst = {0}, src = {0};

    /* Validate user input */
    if(!alloc || !out || !base) { return null_pointer; }

    /* If string is null return a null cstr */
    if(!base->items || !base->count) {
        return mem_calloc(alloc, out, 1);
    }

    if((res = mem_alloc(alloc, out, base->count + 1))) { return res; }

    /* Set slices for copying */
    slice_set(&src, base->items, base->count);
    slice_set(&dst, (*out), base->count);

    /* Copy the data and set last byte to null */
    res = mem_cpy(&dst, &src);
    (*out)[base->count] = 0;

    if(res) { mem_free(out); return res; }
    return success;
}
