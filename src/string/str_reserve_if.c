#include "string_private.h"

fc_error_t str_reserve_if
(str_t* str, u32 amount)
{
    /* Init variables */
    struct str_s* s = 0;

    if(!str) { return fce_str_reserve_if_null_ptr; }
    if(!amount) { return fce_success; }

    s = (void*)str;

    if(s->count + amount <= s->capacity) { return fce_success; }
    s->capacity += amount;

    /* Allocate new chunk */
    return realloc(s->capacity, &s->items);
}
