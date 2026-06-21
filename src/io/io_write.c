#include "io_private.h"

error_t __io_write
(file_t* file, void* raw_sl, usz el_size)
{
    /* Init variables */
    error_t res = success;

    /* Lock mutex and call internal function which will handle it */
    mutex_lock(&file->mutex);
    res = __io_write_unlocked(file, raw_sl, el_size);
    mutex_unlock(&file->mutex);

    return res;
}
