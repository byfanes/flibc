#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "syscall.h"

struct file_s {
    ssize_t fd;
    usize_t count;
    file_type_t type;
    u8 buf[FLIBC_STACK_THRESHOLD];
};

fc_error_t __formatf(slice(u8) buf, slice(u8) fmt, va_list ap, usize_t* out_len);

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
