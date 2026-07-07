#include "io_private.h"

error_t io_vprintf_sl
(file_t* file, sl_u8_t fmt, va_list ap)
{
    /* Init variables */
    usz count = 0;
    error_t res = success;
    u8 buf[FLIBC_STACK_THRESHOLD] = {0};
    sl_u8_t buf_sl = {0};
    void* ptr = 0;
    allocator_t* alloc = 0;
    va_list va1, va2;

    va_copy(va1, ap);
    va_copy(va2, ap);

    /* Note: Allocation is a little bit tricky becayse files are allocated via
     * an allocator and they are opaque pointers so we know they must have an
     * header via that we can access an allocator which is same with the file's
     * allcator and use it to access more memory
     */

    return ((void)(
        /* Check file pointer fmt checked in format function */
        (res = (file) ? success : null_pointer) ||
        /* First get size of buffer */
        (res = __formatf(buf_sl, fmt, &count, va1)) ||
        /* Allocate stack or heap */
        ((count <= FLIBC_STACK_THRESHOLD) ? (ptr = buf, success)
            : ((res = allocator_get_from_ptr(file, &alloc)) ||
              (res = mem_alloc(alloc, &ptr, count))), res) ||
        /* Set slice with the pointer and the count */
        (res = slice_set(&buf_sl, ptr, count)) ||
        /* Format using fmt and output to buffer */
        (res = __formatf(buf_sl, fmt, &count, va2)) ||
        /* Write buffer to file pointer */
        (res = io_write(file, &buf_sl))
    ), ( /* Cleanup - If we allocate memory - no (void) because useless-cast */
        ((count > FLIBC_STACK_THRESHOLD) ? (mem_free(&ptr)) : (0)),
        (va_end(va1)),
        (va_end(va2))
    ), res);
}
