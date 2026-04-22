#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_init_cap
(def_da_header_t* da, uint32_t n_size, uint32_t amount)
{
    fc_error_t res = fce_success;
    res = fc_calloc(amount * n_size, &da->items);
    if (res) { return res; }
    da->capacity = amount;
    da->count = 0;
    return res;
}
