#include "memory_private.h"

slice_t cstr_to_def
(const char* cstr)
{
    /* Init variables */
    slice_t sl = {0};
    u32 i = 0;

    /* Calculate the length of cstr(null terminated) and set slice */
    if(cstr) { while(cstr[i++]){}; i--; }
    set_slice(&sl, cstr, i);

    return sl;
}
