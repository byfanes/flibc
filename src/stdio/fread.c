#include "stdio_private.h"

error_t __fread
(file_t* file, void* buf, usz el_size, u32* _Nullable read_count)
{
    /* Init variables */
    error_t res = success;

    /* Lock mutex and call internal function which will handle it */
    mutex_lock(&file->mutex);
    res = __fread_unlocked(file, buf, el_size, read_count);
    mutex_unlock(&file->mutex);

    return res;
}
