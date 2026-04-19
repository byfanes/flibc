#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_push_slice
(def_da_header_t* da, def_slice_t sl, uint32_t size, uint32_t count)
{
    fc_error_t res;
    def_slice_t dst;
    if ((res = __da_reserve(da, size, count))) { return res; }
    set_slice(&dst, &da->items[da->count*size], size*count);
    if ((res = fc_memcpy(dst, sl))) { return res; }
    da->count += count;
    return res;
}
