#include "stdio_private.h"

fc_error_t fflush
(file_t* file)
{
    /* Init variables */
    arch_t ret = 0;
    u32 count = 0;

    /* Validate user inputs */
    if(!file) { return fce_fflush_nullptr; }
    if(file->type == file_read) { return fce_fflush_got_read_file; }

    /* Store count */
    count = file->count;
    file->count = 0;

    /* Call write syscall */
    ret = syscall_3(syscall_write, (arch_t)file->fd, (arch_t)file->buf, count);

    /* Check return of the syscall */
    if(ret < 0) { return fce_fflush_failed; }
    if(ret != count) { return fce_fflush_partial; }

    return fce_success;
}
