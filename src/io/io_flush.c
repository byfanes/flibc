#include "io_private.h"

error_t io_flush
(file_t* file)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check user input */
        (res = (file) ? success : null_pointer) ||
        /* Start mutex block and pass to unlocked function */
        (mutex_lock(&file->mutex),
            res = __io_flush_unlocked(file),
        mutex_unlock(&file->mutex), res)
    ), res);
}
