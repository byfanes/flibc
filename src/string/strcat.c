#include "string_private.h"

fc_error_t strcat
(str_t base, str_t extend)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t dst = {0}, src = {0};

    /* Validate user input */
    if(!base) { return fce_strcat_base_null; }
    if(!extend) { return fce_strcat_extend_null; }
    if(!extend->items || !extend->count) { return fce_success; }
    if(!base->items) { return fce_strcat_base_null; }

    /* This acts like a grow function because header is already allocated */
    res = __da_reserve_if(&base, extend->count, sizeof(*base->items));
    if(res) { return res; }

    /* Set slices for copying */
    src.base = (void*)extend->items;
    __set_slice_count(src, extend->count);
    dst.base = (void*)&base->items[base->count];
    __set_slice_count(dst, extend->count);

    /* Copy the data */
    res = memcpy(dst, src);
    if(res) { return res; }

    /* Incrase the count if its successful */
    *(u32*)(uintptr_t)&base->count += extend->count;
    return fce_success;
}
