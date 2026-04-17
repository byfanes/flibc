#include "stdio.h"
#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fwrite
(file_t* file,def_slice_t buf)
{
    if (!buf.base || !file) { return fce_fwrite_nullptr; }
    fc_error_t res = fce_success;
    uint32_t total = buf.count + file->buf.count;
    if (total < file->buf.capacity) {
        da_push_slice(&file->buf,buf);
    } else if (total > file->buf.capacity && buf.count < file->buf.capacity) {
        if((res = fflush(file))) { return res; }
        da_push_slice(&file->buf,buf);
    } else {
        if((res = fflush(file))) { return res; }
        da_push_slice(&file->buf,buf);
        if((res = fflush(file))) { return res; }
    }
    return res;
}
