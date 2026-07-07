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
        /* If file fd is a standard io early return */
        (file->fd == UNIX_STDERR || file->fd == UNIX_STDIN || file->fd == UNIX_STDOUT) ||
        /* Close the file fd via syscall */
        (res = (0 > syscall_1_linux(syscall_close, file->fd)) ? io_error : success)
    ), (void)( /* Cleanup */
        mem_free(p_file),
        /* Still zero the users' pointer if the mem_free fails */
        (*p_file) = nullptr
    ), res);
}
