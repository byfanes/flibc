#include "string_private.h"

fc_error_t sl_utf8len
(slice_t sl, u32* out)
{
    /* Init variables */
    u32 i = 0, count = 0;
    u8 c = 0;
    
    /* Validate user input */
    if(!out) { return fce_is_utf8_sl_out_null; }
    if(!sl.base || !sl.count) { *out = true; return fce_success; }

    /* Last byte of sequence are incremented with the loop
     * other ones should be handled in the flow
     */
    for(;i < sl.count; ++i, ++count) {
        c = sl.base[i];
        /* Ascii 0aaa bbbb */
        if(!(c >> 7)) { continue; }

        /* 2 Byte 110a bbbb (first) 6 = 0b110 */
        if((c >> 5) == 6) {
            /* Check and fetch the new byte */
            if(i + 1 >= sl.count) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            continue;
        }

        /* 3 Byte 1110 aaaa (first) 14 = 0b1110 */
        if((c >> 4) == 14) {
            /* Check and fetch the new byte */
            if(i + 2 >= sl.count) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (third) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }

            continue;
        }

        /* 4 Byte 1111 0aaa (first) 14 = 0b1110 */
        if((c >> 4) == 14) {
            /* Check and fetch the new byte */
            if(i + 3 >= sl.count) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (third) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            c = sl.base[++i];

            /* New byte should be 10aa bbbb (fourth) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }

            continue;
        }

        /* No starts match so invalid */
        goto invalid;
    }

    *out = count;
    return fce_success;

invalid:
    *out = 0;
    return fce_sl_utf8len_invalid_utf8;
}
