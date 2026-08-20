#ifndef __FLIBC_HELPERS_H__
#define __FLIBC_HELPERS_H__

#include "error.h"
#include "memory.h"
#include "base.h"
#include "../os/os_private.h"
#include "require.h"

#define __helper_panic(msg) \
     (require_typed_ptr(msg, const char), __helper_panic_len(msg, sizeof(msg) - 1))
noreturn __helper_panic_len(const void* msg, usz msg_len);

#endif /* __FLIBC_HELPERS_H__ */
