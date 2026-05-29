#include "string_private.h"

error_t strcat_cstr
(str_t* base, const char* cstr)
{
    /* Init variables */
    sl_u8_t sl = {0};

    /* This is a wrapper function and strlen can be given null which will return 0 */
    set_slice(&sl, cstr, strlen(cstr));
    return strcat_sl(base, &sl);
}
