#include "string_private.h"

error_t cstr_utf8_len
(const char* s, usz* out)
{
    /* Init variables */
    usz i = 0, count = 0;
    u8 c = 0;
    u32 codepoint = 0;

    /* Validate user input */
    if(!out || !s) { return null_pointer; }

    /* Last byte of each sequence increments the loop
     * other ones should be handled in the flow
     */
    for(; s[i]; ++i, ++count) {
        c = (u8)s[i];
        codepoint = 0;
        /* Ascii 0aaa bbbb */
        if(!(c >> 7)) { continue; }

        /* 2 Byte 110a bbbb (first) 6 = 0b110 */
        if((c >> 5) == 6) {
            /* Check and fetch the new byte */
            if(!s[i + 1]) { goto invalid; }
            codepoint = ((u32)(c & 0x1F) << 6);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F));

            /* overlong */
            if(codepoint < 0x80) { goto invalid; }
            continue;
        }

        /* 3 Byte 1110 aaaa (first) 14 = 0b1110 */
        if((c >> 4) == 14) {
            /* Check and fetch the new byte */
            if(!s[i + 1] || !s[i + 2]) { goto invalid; }
            codepoint = ((u32)(c & 0x0F) << 12);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F) << 6);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (third) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F));

            /* overlong */
            if(codepoint < 0x800) { goto invalid; }

            /* surrogate */
            if(codepoint >= 0xD800 && codepoint <= 0xDFFF) { goto invalid; }
            continue;
        }

        /* 4 Byte 1111 0aaa (first) 30 = 0b11110 */
        if((c >> 3) == 30) {
            /* Check and fetch the new byte */
            if(!s[i + 1] || !s[i + 2] || !s[i + 3]) { goto invalid; }
            codepoint = ((u32)(c & 0x07) << 18);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (second) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F) << 12);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (third) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F) << 6);
            c = (u8)s[++i];

            /* New byte should be 10aa bbbb (fourth) 2 = 0b10 */
            if((c >> 6) != 2) { goto invalid; }
            codepoint |= ((u32)(c & 0x3F));

            /* overlong */
            if(codepoint < 0x10000) { goto invalid; }

            /* Max limit */
            if(codepoint > 0x10FFFF) { goto invalid; }
            continue;
        }

        /* No starts match so invalid */
        goto invalid;
    }

    *out = count;
    return success;

invalid:
    *out = 0;
    return invalid_utf8;
}
