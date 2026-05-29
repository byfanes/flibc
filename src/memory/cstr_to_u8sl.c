#include "memory_private.h"

sl_u8_t cstr_to_u8sl
(const char* cstr)
{
    /* Init variables */
    sl_u8_t sl = {0};
    u32 len = 0;

    /* Calculate the length of cstr(null terminated) and set slice */
    len = strlen(cstr);
    set_slice(&sl, cstr, len);

    return sl;
}
