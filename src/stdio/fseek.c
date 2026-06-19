#include "stdio_private.h"

error_t fseek
(file_t* file, usz off, seek_type_t type, usz* _Nullable out)
{
    /* Init variables */
    error_t res = success;

    /* Lock mutex and call internal function which will handle it */
    mutex_lock(&file->mutex);
    res = __fseek_unlocked(file, off, type, out);
    mutex_unlock(&file->mutex);

    return res;
}
