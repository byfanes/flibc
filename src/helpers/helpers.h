#ifndef __FLIBC_HELPERS_H__
#define __FLIBC_HELPERS_H__

#include "error.h"
#include "memory.h"
#include "stdarg.h"
#include "features.h"

fc_error_t __formatf(slice(u8) buf, slice(u8) fmt, va_list ap, usize_t* out_len);
u32 strlen(const char* s);

#endif /* __FLIBC_HELPERS_H__ */
