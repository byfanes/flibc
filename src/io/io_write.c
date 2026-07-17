#include "io_private.h"

error_t __io_write
(file_t* file, const void* raw_sl, usz el_size)
{
    /* Init variables */
    error_t res = success;
    const sl_u8_t *sl = raw_sl;

    /* Lock mutex and call internal function which will handle it */
    return ((void)(
        (res = (file && sl && sl->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (mutex_lock(&file->mutex),
            res = __io_write_unlocked(file, sl->items, sl->count * el_size),
        mutex_unlock(&file->mutex), res)
    ), res);
}
