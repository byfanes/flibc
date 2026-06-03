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
    i32 w = 0, zeros = 0, i = 0, val = 0, digits = 0, hv = 0;
    u16 words[8] = {0};
    u8 c = 0;
    const char* col = nullptr;

    while((c = (u8)*src)) {
        if(c == ':') {
            if(*(src + 1) == ':') {
                col = src;
                src += 2;
                w++;
                break;
            }
            w++;
            src++;
            continue;
        }

        val = 0; digits = 0;

        while(c && c != ':') {
            if (c >= '0' && c <= '9') { hv = c - '0'; }
            else if (c >= 'a' && c <= 'f') { hv = c - 'a' + 10; }
            else if (c >= 'A' && c <= 'F') { hv = c - 'A' + 10; }
            else { return invalid_address; }
            val = (val << 4) | hv;
            digits++;
            if(digits > 4) { return invalid_address; }
            src++;
        }
        
        if(w >= 8) { return invalid_address; }
        words[w++] = (u16)val;
        if(c == ':') src++;
    }

    if(col) {
        zeros = 8 - w;
        for(i = 0; i < (w - zeros); ++i)
        { words[zeros + i] = words[w + i]; }
        for(i = 0; i < zeros; ++i)
        { words[i] = 0; }
    }

    for(i = 0; i < 8; ++i)
    {
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
