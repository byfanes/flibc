#include "string_private.h"

bool str_eq_cstr
(str_t* lhs, const char* cstr)
{
    /* Init variables */
    usz len = 0;
    bool out = false;

    len = cstr_len(cstr);

    /* Check possible combinations for early return */
    if(!lhs && !cstr) { return true; }
    if(!lhs->items && !cstr) { return true; }
    if(!lhs->items || !cstr) { return false; }
    if(lhs->count != len) { return false; }

    return (mem_cmp_raw(cstr, lhs->items, lhs->count, &out), out);
}
