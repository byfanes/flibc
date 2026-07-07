#include "string_private.h"

bool str_eq
(str_t* lhs, str_t* rhs)
{
    /* Init variables */
    bool out = false;

    /* Check possible combinations for early return */
    if(!lhs && !rhs) { return true; }
    if(!lhs || !rhs) { return false; }
    if(!lhs->items && !rhs->items) { return true; }
    if(!lhs->items || !rhs->items) { return false; }

    /* Check one by one */
    return (mem_cmp(lhs, rhs, &out), out);
}
