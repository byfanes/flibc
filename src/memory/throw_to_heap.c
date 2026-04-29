#include "memory_private.h"

fc_error_t throw_to_heap
(void* out, void* in, uint32_t el_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!out) { return fce_mem_throw_to_heap_out_nullptr; }
    if(!in) { return fce_mem_throw_to_heap_in_nullptr; }
    if(!el_size) { return fce_mem_throw_to_heap_zero_size; }

    res = malloc(el_size, out);
    if(res) { return res; }
    src.base = in;
    dst.base = *(void**)out;
    __set_slice_count(src, el_size);
    __set_slice_count(dst, el_size);

    return memmove(dst, src);
}
