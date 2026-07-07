#include "string_private.h"

bool cstr_eq
(const char* l, const char* r)
{
    if(!l && !r) { return true; }
    if(!l || !r) { return false; }

    while (*l && (*l == *r)) {
        ++l;
        ++r;
    }

    return *l == *r;
}
