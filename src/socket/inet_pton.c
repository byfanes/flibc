#include "socket_private.h"

static error_t parse_ipv4
(const char* src, u8* dst)
{
    i32 parts = 0, val = 0;
    u8 c = 0;

    while((c = (u8)*src)) {
        if(c >= '0' && c <= '9') {
            val = val * 10 + (c - '0');
            if(val > 255) { return invalid_address; }
        } else if(c == '.') {
            if (parts >= 3) { return invalid_address; }
            dst[parts++] = (u8)val;
            val = 0;
        } else { return invalid_address; }
        src++;
    }

    if(parts != 3) { return invalid_address; }
    dst[3] = (u8) val;
    return success;
}

static error_t parse_ipv6
(const char* src, u8* dst)
{
    i32 w = 0, i = 0, val = 0, digits = 0, hv = 0;
    /* Use -1 to indicate :: has not been seen yet */
    i32 col_idx = -1;
    u16 words[8] = {0};
    u8 c = 0;

    /* '::' For cases like "::1" */
    if (src[0] == ':' && src[1] == ':') {
        col_idx = 0;
        src += 2;
    }

    while ((c = (u8)*src)) {
        val = 0; digits = 0;

        while (c && c != ':') {
            if (c >= '0' && c <= '9') { hv = c - '0'; }
            else if (c >= 'a' && c <= 'f') { hv = c - 'a' + 10; }
            else if (c >= 'A' && c <= 'F') { hv = c - 'A' + 10; }
            else { return invalid_address; }

            val = (val << 4) | hv;
            digits++;
            if (digits > 4) { return invalid_address; }

            src++;
            c = (u8)*src;
        }

        if (w >= 8) { return invalid_address; }
        words[w++] = (u16)val;

        /* If we hit a colon advance and check for a double colon */
        if (c == ':') {
            src++;
            if (*src == ':') {
                /* Multiple :: occured */
                if (col_idx != -1) { return invalid_address; }
                col_idx = w;
                src++;
            }
        }
    }

    /* If we saw a '::' shift the post-col words to the right and fill with zeros */
    if (col_idx != -1) {
        i32 zeros = 8 - w;

        /* Shift words parsed after '::' to the very end of the array */
        for (i = w - 1; i >= col_idx; --i) {
            words[i + zeros] = words[i];
        }

        /* Fill the gap with actual zeros */
        for (i = 0; i < zeros; ++i) {
            words[col_idx + i] = 0;
        }
        w = 8;
    } else if (w != 8) {
        /* No '::' was used but we didn't get exactly 8 words */
        return invalid_address;
    }

    /* Convert 16-bit words into network-byte-order 8-bit array */
    for (i = 0; i < 8; ++i) {
        dst[i * 2]     = (u8)((words[i] >> 8) & 0xff);
        dst[i * 2 + 1] = (u8)(words[i] & 0xff);
    }

    return success;
}

/* TODO: Those parsers are checking very simple thing */
error_t inet_pton
(sock_family_t family, const char* src, void* dst)
{
    if(!dst || !src) { return null_pointer; }

    if(family == AF_INET) {
        return parse_ipv4(src, dst);
    } else if(family == AF_INET6) {
        return parse_ipv6(src, dst);
    }

    return invalid_argument;
}
