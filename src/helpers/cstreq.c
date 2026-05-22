#include "helpers.h"

bool cstreq(const char* l, const char* r)
{
    while (*l && (*l == *r)) {
        ++l;
        ++r;
    }

    return *l == *r;
}
