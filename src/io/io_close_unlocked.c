#include "io_private.h"

error_t __io_close_unlocked
(file_t** p_file)
{
    /* Init variables */
    error_t res = success;
    file_t* file = *p_file;

    return ((void)(
        /* If its different than file_read flush the remaining buffer - we dont care the error here */
        (((file->type != file_read) ? __io_flush_unlocked(file) : (0)), success) ||
        /* Close the file handle and set it to invalid now on - standard io checked inside it */
        (res = __os_file_close(&file->fd))
    ), (void)( /* Cleanup */
        mem_free(p_file),
        /* Still zero the users' pointer if the mem_free fails */
        (*p_file) = nullptr
    ), res);
}
