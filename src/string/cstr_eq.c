#include "string_private.h"

bool cstr_eq
(const char* l, const char* r)
{
    while (*l && (*l == *r)) {
        ++l;
        ++r;
    }

    return *l == *r;
}
