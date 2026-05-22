#ifndef __FLIBC_HELPERS_H__
#define __FLIBC_HELPERS_H__

#include "error.h"
#include "memory.h"
#include "stdarg.h"
#include "features.h"

error_t __formatf(slice(u8) buf, slice(u8) fmt, usize_t* out_len, va_list ap);
error_t formatf(slice(u8) buf, slice(u8) fmt, usize_t* out_len, ...);
u32 strlen(const char* s);
bool cstreq(const char* l, const char* r);

#endif /* __FLIBC_HELPERS_H__ */
