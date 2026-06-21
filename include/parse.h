#ifndef __FLIBC_PARSE_H__
#define __FLIBC_PARSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

u16 bswap16(u16 x);
u32 bswap32(u32 x);
u64 bswap64(u64 x);

bool is_little_endian(void);
bool is_big_endian(void);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_PARSE_H__ */
