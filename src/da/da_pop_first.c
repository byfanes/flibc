#include "da_private.h"

error_t __da_pop_first
(void* da, void* out, usize_t el_size)
{
    /* This is just a wrapper function */
    return __da_pop(da, out, 0, el_size);
}
