#include "string_private.h"

fc_error_t strcat_sl
(str_t* base, slice(u8) sl)
{
    /* Init variables */
    fc_error_t res = fce_success;

    /* Validate user input */
    if(!base || !base->items) { return fce_null_pointer; }
    if(!sl.base || !sl.count) { return fce_success; }

    /* Check for utf8 */
    if(is_utf8_sl(sl)) { return fce_invalid_utf8; }

    /* Allocate new memory if needed  */
    if((res = str_grow_if(base, sl.count))) { return res; }

    /* Copy the data */
    return __str_copy_content(base, sl);
}
