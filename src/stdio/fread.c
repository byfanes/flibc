#include "stdio_private.h"

fc_error_t fread
(file_t* file, slice_t buf, uint32_t* _Nullable read_count)
{
    /* Init variables */
    arch_t ret = 0;
    
    /* Validate user inputs */
    if(!file) { return fce_fread_file_nullptr; }

    /* Call read syscall */
    ret = syscall_3(syscall_read, (arch_t)file->fd, (arch_t)buf.base, buf.count);

    /* Check return of the syscall */
    if(ret < 0) { return fce_fread_failed; }
    if(read_count) { *read_count = (uint32_t)ret; }
    if(ret < buf.count) { return fce_fread_partial; }

    return fce_success;
}

