#include "string_private.h"

bool streq
(str_t lhs, str_t rhs)
{
    u32 i = 0;
    
    if(!lhs.items && !rhs.items) { return true; }
    if(lhs.items && !rhs.items) { return false; }
    if(!lhs.items && rhs.items) { return false; }
    if(lhs.count != rhs.count) { return false; }

    for(;i < lhs.count; ++i) {
        if(lhs.items[i] != rhs.items[i]) { return false; }
    }

    return true;
}
