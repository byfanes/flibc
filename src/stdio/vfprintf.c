#include "stdio_private.h"

fc_error_t vfprintf
(file_t* file, slice(u8) fmt, va_list ap)
{
    /* Init variables */
    usize_t count = 0;
    fc_error_t res = fce_success;
    u8 buf[FLIBC_STACK_THRESHOLD];
    slice(u8) buf_sl = {0};
    void* ptr = 0;

    /* First get size of buffer */
    if((res = __formatf(buf_sl, fmt, &count, ap))) { return res; }

    /* Allocate stack or heap */
    if(count > FLIBC_STACK_THRESHOLD) {
        /* TODO: Make it use chunks it will crash other wise*/
        if((res = malloc(nullptr, count, &ptr))) { return res; }
    } else {
        ptr = buf;
    }

    /* Set slice with the pointer and the count */
    set_slice(&buf_sl, ptr, count);

    /* Format using fmt and output to buffer */
    if((res = __formatf(buf_sl, fmt, &count, ap))) { return res; }

    /* Write buffer to file pointer */
    if((res = fwrite(file, buf_sl))) { return res; }

    /* Free if its need */
    if(count > FLIBC_STACK_THRESHOLD) { return free(&ptr); }

    return fce_success;
}
