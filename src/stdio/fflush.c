#include "stdio_private.h"

fc_error_t fflush
(file_t* file)
{
    /* Init variables */
    arch_t ret = 0;
    uint32_t count = 0;

    /* Validate user inputs */
    if(!file) { return fce_fflush_nullptr; }

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
