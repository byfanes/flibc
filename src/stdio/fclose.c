#include "stdio_private.h"

error_t fclose
(file_t** file)
{
    /* Init variables */
    error_t res = success;

    /* Lock mutex and call internal function which will handle it */
    mutex_lock(&(*file)->mutex);
    res = __fclose_unlocked(file);

    if((*file)) {
        /* If fclose failed unlock the mutex again
         * otherwise it will be freed so it segfaults
         * that is reason we check
         */
        mutex_unlock(&(*file)->mutex);
    }

    return res;
}
