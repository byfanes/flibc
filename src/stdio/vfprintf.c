#include "stdio_private.h"

fc_error_t vfprintf
(file_t* file, slice_t fmt, va_list ap)
{
    /* Init variables */
    u32 count = 0;
    fc_error_t res = fce_success;
    u8 buf[FLIBC_STACK_THRESHOLD];
    va_list c_ap;
    slice_t buf_sl = {0};
    void* ptr = 0;

    /* Copy va because it is unusable after it has been consumed */
    va_copy(c_ap, ap);

    /* First get size of buffer */
    res = formatf(buf_sl, fmt, c_ap, &count);
    if(res) { return res; }

    /* Allocate stack or heap */
    if(count > FLIBC_STACK_THRESHOLD) {
        res = malloc(count, &ptr);
        if(res) { return res; }
    } else {
        ptr = buf;
    }

    /* Set slice with the pointer and the count */
    set_slice(&buf_sl, ptr, count);

    /* Format using fmt and output to buffer */
    res = formatf(buf_sl, fmt, ap, &count);
    if(res) { return res; }

    /* Write buffer to file pointer */
    res = fwrite(file, buf_sl);
    if(res) { return res; }

    /* Free if its need */
    if(count > FLIBC_STACK_THRESHOLD) {
        return free(&ptr);
    }

    return fce_success;
}
