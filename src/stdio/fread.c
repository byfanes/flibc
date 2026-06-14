#include "stdio_private.h"

error_t __fread
(file_t* file, void* buf, usz el_size, u32* _Nullable read_count)
{
    /* Init variables */
    ssz ret = 0;
    sl_u8_t sl = {0};
    error_t res = success;

    /* Validate user inputs */
    if(!file || !buf) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    set_slice(&sl, ((sl_u8_t*)buf)->items, ((sl_u8_t*)buf)->count * el_size);
    if(!sl.count || !sl.items) { return null_pointer; }
    set_slice(&sl, sl.items, sl.count * el_size);
    if(file->type == file_write || file->type == file_append) { return io_invalid_op; }

    mutex_lock(&file->mutex);

    /* Call read syscall */
    ret = syscall_3_linux(syscall_read, file->fd, (ssz)sl.items, (ssz)sl.count);

    /* Check return of the syscall */
    if(ret < 0) { res = io_error; goto end; }
    if(read_count) { *read_count = (u32)ret; }
    if(ret < (ssz)sl.count) { res = io_partial; goto end; }

end:
    mutex_unlock(&file->mutex);
    return res;
}
