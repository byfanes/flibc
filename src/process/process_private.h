#ifndef __FLIBC_PROCESS_PRIVATE_H__
#define __FLIBC_PROCESS_PRIVATE_H__

#include "process.h"
#include "syscall.h"
#include "stdlib.h"

error_t waitapid(ssize_t pid);

#endif /* __FLIBC_PROCESS_PRIVATE_H__ */
