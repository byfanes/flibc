#include "stdio_private.h"

error_t vfprintf_sl
(file_t* file, sl_u8_t fmt, va_list ap)
{
    /* Init variables */
    usz count = 0;
    error_t res = success;
    u8 buf[FLIBC_STACK_THRESHOLD];
    sl_u8_t buf_sl = {0};
    void* ptr = 0;
    allocator_t* alloc = 0;

    /* Check file pointer fmt checked in format function */
    if(!file) { return null_pointer; }

    /* First get size of buffer */
    if((res = __formatf(buf_sl, fmt, &count, ap))) { return res; }

    /* Allocate stack or heap */
    if(count > FLIBC_STACK_THRESHOLD) {
        /* A little bit trick but files are allocated via an allocator
         * and they are opaque pointers so we know they must have an header
         * via that we can access an allocator which is same with the file's
         * allcator and use it to access more memory
         */
        if((res = allocator_get_from_ptr(file, &alloc))) { return res; }
        if((res = malloc(alloc, count, &ptr))) { return res; }
    } else {
        ptr = buf;
    }

    /* Set slice with the pointer and the count */
    set_slice(&buf_sl, ptr, count);

    /* Format using fmt and output to buffer */
    if((res = __formatf(buf_sl, fmt, &count, ap))) { goto fail; }

    /* Write buffer to file pointer */
    if((res = fwrite(file, &buf_sl))) { goto fail; }

fail:
    /* Free if its need */
    if(count > FLIBC_STACK_THRESHOLD && ptr) { free(&ptr); }
    return res;
}
