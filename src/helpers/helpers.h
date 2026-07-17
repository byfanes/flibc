#ifndef __FLIBC_HELPERS_H__
#define __FLIBC_HELPERS_H__

#include "error.h"
#include "memory.h"
#include "base.h"
#include "../os/os_private.h"

error_t __formatf(sl_u8_t buf, sl_u8_t fmt, usz* out_len, va_list ap);
error_t formatf(sl_u8_t buf, sl_u8_t fmt, usz* out_len, ...);

#define __panic(msg) ((void)(sizeof(msg == (const char *)0)), __panic_len(msg, sizeof(msg) - 1))
noreturn __panic_len(const void* msg, usz msg_len);

#endif /* __FLIBC_HELPERS_H__ */
