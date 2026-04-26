#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "../memory/memory_private.h"
#include "syscall.h"

struct file_s {
    arch_t fd;
    uint32_t count;
    byte_t buf[FLIBC_STACK_THRESHOLD];
};

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
