#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "error.h"
#include "../memory/memory_private.h"
#include "syscall.h"

struct file_s {
    arch_t fd;
    u32 count;
    u8 buf[FLIBC_STACK_THRESHOLD];
};

fc_error_t formatf(slice_t buf, slice_t fmt, va_list ap, u32* out_len);

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
