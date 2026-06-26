#ifndef __FLIBC_STD_PRIVATE_H__
#define __FLIBC_STD_PRIVATE_H__

#include "std.h"
#include "syscall.h"

/* Threshold for stack allocation in for args slice */
#define MAX_ARGS_COUNT 256

void __std_early_panic(const char* msg);

#endif /* __FLIBC_STD_PRIVATE_H__ */
