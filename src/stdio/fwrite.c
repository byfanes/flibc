#include "stdio.h"
#include "memory.h"
#include "error.h"
#include "syscall.h"

/* Todo: This function is broken */
fc_error_t fwrite
(file_t* file, def_slice_t buf)
{
    fc_error_t res = fce_success;
    uint32_t total = 0;
    if (!buf.base || !file) { return fce_fwrite_nullptr; }
    res = fce_success;
    total = buf.count + file->buf.count;
    if (total < file->buf.capacity) {
        res = __da_push_slice((void*)&file->buf, buf, sizeof(*buf.base), buf.count);
//        da_push_slice(res, &file->buf, buf);
    } else if (total > file->buf.capacity && buf.count < file->buf.capacity) {
        if((res = fflush(file))) { return res; }
        res = __da_push_slice((void*)&file->buf, buf, sizeof(*buf.base), buf.count);
//        da_push_slice(res, &file->buf, buf);
    } else {
        if((res = fflush(file))) { return res; }
        res = __da_push_slice((void*)&file->buf, buf, sizeof(*buf.base), buf.count);
        if(res) { return res; }
//        da_push_slice(res, &file->buf, buf);
        if((res = fflush(file))) { return res; }
    }
    return res;
}
