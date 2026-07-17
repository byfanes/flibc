#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "io.h"
#include "syscall.h"
#include "threads.h"
#include "../helpers/helpers.h"
#include "../os/os_private.h"

struct file_s {
    os_fid_t fd;
    usz count;
    file_type_t type;
    mutex_t mutex;
    u8 buf[FLIBC_FILE_BUFFER_SIZE];
};

/* Unlocked functions assume file->mutex is already held by the caller.
 * Calling them without holding the mutex results in undefined behavior
 * and may cause data races or corruption when accessed concurrently.
 *
 * Note: Those functions are internal so no checking is done here
 */
error_t __io_flush_unlocked(file_t* file);
error_t __io_close_unlocked(file_t** file);
error_t __io_read_unlocked(file_t* file, void* buf_ptr, usz amount, usz* read_count);
error_t __io_write_unlocked(file_t* file, const void* buf, usz n);

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
