#include "string.h"

usz cstr_len
(const char* s)
{
    usz i = 0;
    if(!s) return 0;
    while(s[i++]) {}
    return i - 1;
}
