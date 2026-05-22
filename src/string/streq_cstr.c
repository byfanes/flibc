#include "string_private.h"

bool streq_cstr
(str_t* lhs, const char* cstr)
{
    /* Init variables */
    u32 i = 0;
    u32 len = 0;

    len = strlen(cstr);

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
