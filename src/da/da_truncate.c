#include "da.h"
#include "error.h"

fc_error_t __da_truncate
(def_da_header_t* da, uint32_t len)
{
    if(!da) { return fce_da_truncate_nullptr; }
    uint32_t count = da->count;
    if(len < count) {
        da->count = len;
    }
    return fce_success;
}
