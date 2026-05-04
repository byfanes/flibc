#ifndef __FLIBC_STDIO_PRIVATE_H__
#define __FLIBC_STDIO_PRIVATE_H__

#include "stdio.h"
#include "../memory/memory_private.h"
#include "syscall.h"

struct file_s {
    arch_t fd;
    u32 count;
    u8 buf[FLIBC_STACK_THRESHOLD];
};

void formatf(slice_t fmt);

#endif /* __FLIBC_STDIO_PRIVATE_H__ */
