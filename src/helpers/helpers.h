#ifndef __FLIBC_HELPERS_H__
#define __FLIBC_HELPERS_H__

#include "error.h"
#include "memory.h"
#include "stdarg.h"
#include "features.h"

error_t __formatf(sl_u8_t buf, sl_u8_t fmt, usz* out_len, va_list ap);
error_t formatf(sl_u8_t buf, sl_u8_t fmt, usz* out_len, ...);
u32 strlen(const char* s);
bool cstreq(const char* l, const char* r);

#endif /* __FLIBC_HELPERS_H__ */
