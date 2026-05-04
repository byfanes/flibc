#include "da_private.h"

fc_error_t __da_reserve
(void* p_da, u32 amount, u32 n_size)
{
    /* Init variables */
    fc_error_t res = fce_success;
    def_da_t* da = 0;

    /* Validate user inputs - n_size can not be 0 via sizeof but user implicitly call with it */
    if(!p_da) { return fce_da_reserve_nullptr; }
    if(!n_size) { return fce_da_reserve_zero_nsize; }
    if(!amount) { return fce_da_reserve_zero_amount; }

    da = *(void**)p_da;

    if(da) {
        /* Update the current header */
        da->capacity += amount;

        /* Realloc new items array with new size */
        return realloc(da->capacity, &da->items);
    }

    /* Allocate new header */
    res = malloc(sizeof(def_da_t), &da);
    if(res) { return res; }

    /* Set new header for user */
    *(void**)p_da = da;

    /* Init new header */
    da->count = 0;
    da->capacity = amount;

    /* Allocate new memory for items */
    return malloc(amount*n_size, &da->items);
}
