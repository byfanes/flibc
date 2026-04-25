#include "da_private.h"

fc_error_t __da_pop_first
(void* da, void* out, uint32_t n_size)
{
    return __da_pop(da, out, 0, n_size);
}
