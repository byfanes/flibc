#include "da.h"
#include "memory.h"
#include "error.h"

fc_error_t __da_reserve
(def_da_header_t* da, uint32_t n_size, uint32_t amount)
{
    fc_error_t res = fce_success;
    if (!da->items) {
        da->count = 0;
        da->capacity = 0;
    }    
    if (da->count + amount >= da->capacity) {
        uint32_t new_cap = (da->capacity == 0) ? FLIBC_DA_INIT : (da->capacity * 2);
        new_cap = (new_cap > (amount + da->capacity)) ? new_cap : (amount + da->capacity)*2;
        if (da->items) {
            if ((res = fc_realloc(new_cap * n_size, (void**)&da->items))) {
                return res;
            }
        } else {
            if ((res = fc_calloc(new_cap * n_size, (void**)&da->items))) {
                return res;
            }
        }
        da->capacity = new_cap;
    }
    return fce_success;
}

