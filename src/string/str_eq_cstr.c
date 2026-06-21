#include "string_private.h"

bool str_eq_cstr
(str_t* lhs, const char* cstr)
{
    /* Init variables */
    usz i = 0, len = 0;

    len = cstr_len(cstr);

    /* Check possible combinations for early return */
    if(!lhs && !cstr) { return true; }
    if(!lhs->items && !cstr) { return true; }
    if(!lhs->items && cstr) { return false; }
    if(lhs->items && !cstr) { return false; }
    if(lhs->count != len) { return false; }

    /* Check one by one */
    for(;i < lhs->count; ++i) {
        if(lhs->items[i] != cstr[i]) { return false; }
    }

    return true;
}
