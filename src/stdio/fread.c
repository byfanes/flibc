#include "stdio_private.h"

fc_error_t fread
(file_t* file, slice_t* buf)
{
    /* Init variables */
    uint32_t count = 0;
    arch_t ret = 0;
    
    /* Validate user inputs */
    if(!file) { return fce_fread_file_nullptr; }
    if(!buf || !buf->base) { return fce_fread_buf_nullptr; }
    count = buf->count;

    /* Call read syscall */
    ret = syscall_3(syscall_read, (arch_t)file->fd, (arch_t)buf->base, count);

    /* Check return of the syscall */
    if(ret < 0) { return fce_fread_failed; }
    if(ret)
    {__set_slice_count((*buf), (uint32_t)ret);}
    if(ret < count) { return fce_fread_partial; }

    return fce_success;
}

