#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "syscall.h"
#include "threads.h"
#include "../helpers/helpers.h"

struct file_s {
    ssz fd;
    usz count;
    file_type_t type;
    mutex_t mutex;
    u8 buf[FLIBC_FILE_BUFFER_SIZE];
};

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
