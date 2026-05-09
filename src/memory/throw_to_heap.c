#include "memory_private.h"

fc_error_t throw_to_heap
(void* out, void* in, u32 el_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    slice_t src = {0}, dst = {0};

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!out) { return fce_mem_throw_to_heap_out_nullptr; }
    if(!in) { return fce_mem_throw_to_heap_in_nullptr; }
    if(!el_size) { return fce_mem_throw_to_heap_zero_size; }

    /* Allocate new chunk of memory */
    res = malloc(el_size, out);
    if(res) { return res; }

    /* Set slices for memcpy */
    set_slice(&src, in, el_size);
    set_slice(&dst, *(void**)out, el_size);

    return memcpy(dst, src);
}
