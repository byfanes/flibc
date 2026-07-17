#ifndef __FLIBC_STD_PRIVATE_H__
#define __FLIBC_STD_PRIVATE_H__

#include "std.h"
#include "syscall.h"
#include "../os/os_private.h"
#include "../helpers/helpers.h"

/* Threshold for stack allocation in for args slice */
#define MAX_ARGS_COUNT 256

void __std_from_args(std_t* std, i32 argc, char** argv, sl_u8_t *args_ptr);

#endif /* __FLIBC_STD_PRIVATE_H__ */
