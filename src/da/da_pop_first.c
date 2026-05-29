#include "da_private.h"

error_t __da_pop_first
(void* da, usize_t el_size, void* out)
{
    /* This is just a wrapper function */
    return __da_pop(da, el_size, out, 0);
}
