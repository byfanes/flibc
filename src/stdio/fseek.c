#include "stdio_private.h"

fc_error_t fseek
(file_t* file, arch_t off, seek_type_t type, arch_t* _Nullable out)
{
    /* Init variables */
    int32_t whence = 0;
    arch_t ret = 0;

    /* Validate user inputs */
    if(!file) { return fce_fseek_nullptr; }
    if(out) { *out = 0; }

    /* Set flags */
    switch(type) {
        case seek_set: { whence = SEEK_SET; } break;
        case seek_cur: { whence = SEEK_CUR; } break;
        case seek_end: { whence = SEEK_END; } break;
        default: { return fce_fseek_invalid_type; }
    }

    /* Call lseek syscall */
    ret = syscall_3(syscall_lseek, file->fd, off, whence);

    /* Check return of the syscall */
    if(ret == -1) { return fce_fseek_failed; }
    if(out) { *out = ret; }

    return fce_success;
}
