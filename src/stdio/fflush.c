#include "stdtypes.h"
#include "stdio.h"
#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fflush
(file_t* file)
{
    int res;
    if (!file) { return fce_fwrite_nullptr; }
    if (!file->buf.items) { return fce_success; }
    if (!file->buf.count && !file->buf.capacity) { return fce_success; }
    res = syscall_3(syscall_write, file->fd, (arch_t)file->buf.items, file->buf.count);
    if (res < 0) { return fce_fwrite_failed; }
    if (res == (int)file->buf.count) { da_clear(&file->buf); return fce_success; }
    if (res != (int)file->buf.count) { return fce_fwrite_partial; }
    return fce_fwrite_unknown;
}
