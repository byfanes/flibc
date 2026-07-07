#include "string_private.h"

error_t sl_vformatf_sl
(sl_u8_t buf, usz* _Nullable wrote_count, sl_u8_t fmt, va_list ap)
{
    /* Init variables */
    usz count = 0;
    error_t res = success;
    sl_u8_t zero_sl = {0};

    return ((void)(
        /* Set it if its given */
        ((wrote_count) ? *wrote_count = 0 : (0), success) ||
        /* Get size first */
        (res = __formatf(zero_sl, fmt, &count, ap)) ||
        /* Check avaliable count */
        (res = (buf.count >= count) ? success : small_buffer) ||
        /* Format sting */
        (res = __formatf(buf, fmt, &count, ap)) ||
        /* Write count if its avaliable and return */
        ((wrote_count) ? *wrote_count = count : (0), success)
    ), res);
}
