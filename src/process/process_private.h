#ifndef __FLIBC_PROCESS_PRIVATE_H__
#define __FLIBC_PROCESS_PRIVATE_H__

#include "process.h"
#include "syscall.h"
#include "std.h"

error_t waitapid(ssz pid);

#endif /* __FLIBC_PROCESS_PRIVATE_H__ */
