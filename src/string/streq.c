#include "string_private.h"

bool streq
(str_t* lhs, str_t* rhs)
{
    /* Init variables */
    u32 i = 0;

    /* Check possible combinations for early return */
    if(!lhs && !rhs) { return true; }
    if(!lhs || !rhs) { return false; }
    if(!lhs->items && !rhs->items) { return true; }
    if(lhs->items && !rhs->items) { return false; }
    if(!lhs->items && rhs->items) { return false; }
    if(lhs->count != rhs->count) { return false; }

    /* Check one by one */
    for(;i < lhs->count; ++i) {
        if(lhs->items[i] != rhs->items[i]) { return false; }
    }

    return true;
}
