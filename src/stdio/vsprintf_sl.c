#include "stdio_private.h"

error_t vsprintf_sl
(slice(u8) buf, usize_t* _Nullable wrote_count, slice(u8) fmt, va_list ap)
{
    /* Init variables */
    usize_t count = 0;
    error_t res = success;
    slice(u8) zero_sl = {0};

    /* Set it if its given */
    if(wrote_count) { *wrote_count = 0; }

    /* Get size first */
    if((res = __formatf(zero_sl, fmt, &count, ap))) { return res; }

    /* Check avaliable count */
    if(buf.count < count) { return small_buffer; }

    /* Format sting */
    if((res = __formatf(buf, fmt, &count, ap))) { return res; }

    /* Write count if its avaliable and return */
    if(wrote_count) { *wrote_count = count; }
    return success;
}
