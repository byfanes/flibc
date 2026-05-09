#include "da_private.h"

fc_error_t __da_pop_first
(const void* da, void* out, u32 el_size)
{
    return __da_pop(da, out, 0, el_size);
}
