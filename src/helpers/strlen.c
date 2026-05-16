#include "helpers.h"

u32 strlen
(const char* s)
{
    u32 i = 0;
    if(!s) return 0;
    while(s[i++]) {}
    return i - 1;
}
