#include "io_private.h"

error_t __io_read
(file_t* file, void* buf, usz el_size, usz* _Nullable read_count)
{
    /* Init variables */
    error_t res = success;
    sl_u8_t *sl = buf;
    usz tmp = 0;

    return ((void)(
        /* Check users' inputs */
        (res = (file && sl && sl->items) ? success : null_pointer) ||
        /* Start mutex block and pass to unlocked function to
         * handle rest and give it a valid count pointer
         */
        (mutex_lock(&file->mutex),
            res = __io_read_unlocked(file, sl->items, sl->count * el_size,
                                    (read_count) ? read_count : &tmp),
        mutex_unlock(&file->mutex), res)
     ), res);
}
