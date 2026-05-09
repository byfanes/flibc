#include "string_private.h"

fc_error_t str_reserve
(str_t* str, u32 amount)
{
    /* Init variables */
    struct str_s* s = 0;

    /* Validate user input and early return */
    if(!str) { return fce_str_reserve_null_ptr; }
    if(!amount) { return fce_success; }

    /* Fetch and increase the capacity */
    s = (void*)str;
    s->capacity += amount;

    /* Allocate new chunk */
    return realloc(s->capacity, &s->items);
}
