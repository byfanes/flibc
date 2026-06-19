#include "stdio_private.h"

error_t fflush
(file_t* file)
{
    /* Init variables */
    error_t res = success;

    /* Lock mutex and call internal function which will handle it */
    mutex_lock(&file->mutex);
    res = __fflush_unlocked(file);
    mutex_unlock(&file->mutex);

    return res;
}
