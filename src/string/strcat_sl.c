#include "string_private.h"

error_t __strcat_sl
(str_t* base, void* raw_sl, usz el_size)
{
    /* Init variables */
    error_t res = success;
    sl_u8_t* ssl = raw_sl;

    /* Validate user input */
    if(!el_size) { return elsize_zero; }
    if(!base || !base->items) { return null_pointer; }
    if(!ssl || !ssl->items || !ssl->count) { return success; }

    /* Check for utf8 */
    if(!__is_utf8_sl(raw_sl, el_size)) { return invalid_utf8; }

    /* Allocate new memory if needed  */
    if((res = str_grow_if(base, ssl->count))) { return res; }

    /* Copy the data */
    return __str_copy_content(base, ssl->items, el_size * ssl->count);
}
