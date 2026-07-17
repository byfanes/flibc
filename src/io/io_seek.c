#include "io_private.h"

error_t io_seek
(file_t* file, usz off, seek_type_t type, usz* _Nullable out)
{
    /* Init variables */
    error_t res = success;
    usz tmp = 0;

    return ((void)(
        /* Check users inputs */
        (res = (file) ? success : null_pointer) ||
        /* Start mutex block and pass to os function to
         * handle rest and give it a valid out pointer
         * case type to int because of enums which are same
         */
        (mutex_lock(&file->mutex),
            res = __os_file_seek(file->fd, off, (int)type, (out) ? out : &tmp),
        mutex_unlock(&file->mutex), res)
    ), res);
}
