#include "stdio_private.h"

fc_error_t vsprintf
(slice(u8) buf, usize_t* _Nullable wrote_count, slice(u8) fmt, va_list ap)
{
    /* Init variables */
    usize_t count = 0;
    fc_error_t res = fce_success;
    slice(u8) zero_sl = {0};

    /* Set it if its given */
    if(wrote_count) { *wrote_count = 0; }

    /* Get size first */
    if((res = __formatf(zero_sl, fmt, &count, ap))) { return res; }

    /* Check avaliable count */
    if(buf.count < count) { return fce_small_buffer; }

    /* Format sting */
    if((res = __formatf(buf, fmt, &count, ap))) { return res; }

    /* Write count if its avaliable and return */
    if(wrote_count) { *wrote_count = count; }
    return fce_success;
}
