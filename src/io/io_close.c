#include "io_private.h"

error_t io_close
(file_t** file)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check user input */
        (res = (file) ? success : null_pointer) ||
        /* Early return if its a nullptr */
        (!*file) ||
        /* Start mutex block - no end because it will be invalid pointer */
        (mutex_lock(&(*file)->mutex),
            (res = __io_close_unlocked(file)),
        res)
    ), res);
}
