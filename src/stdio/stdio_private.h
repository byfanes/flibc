#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "syscall.h"
#include "../helpers/helpers.h"

struct file_s {
    ssize_t fd;
    usize_t count;
    file_type_t type;
    u8 buf[FLIBC_FILE_BUFFER_SIZE];
};

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
