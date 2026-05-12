#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "error.h"

typedef struct allocator_s allocator_t;

#define slice(type) CONCAT(slice_, type)

#define can_be_slice(type)   \
    typedef struct {         \
        type * const base;   \
        const usize_t count; \
    } CONCAT(slice_, type)

can_be_slice(u8);
can_be_slice(u16);
can_be_slice(u32);
can_be_slice(u64);
can_be_slice(i8);
can_be_slice(i16);
can_be_slice(i32);
can_be_slice(i64);
can_be_slice(ssize_t);
can_be_slice(usize_t);

/* TODO move it to crt.h later */
can_be_slice(slice_u8);

slice(u8) cstr_to_u8sl(const char* cstr);
fc_error_t set_slice(const void* sl, const void* base, usize_t count);

fc_error_t malloc(allocator_t* alloc, usize_t n, void* set);
fc_error_t calloc(allocator_t* alloc, usize_t n, void* set);
/* TODO: realloc can optimized */
fc_error_t realloc(allocator_t* alloc, usize_t n, void* set);
fc_error_t free(void* set);

/* This is both for using typed slices and preventing mechanisim to avoid compiliers'
 * automatic memset calls because those functions collide
 */
fc_error_t __memset(void* dst, usize_t el_size, u8 c);
#define memset(dst, c) __memset((dst), sizeof((dst)->base[0]), (c))

fc_error_t __memcpy(void* dst, void* src, usize_t el_size);
#define memcpy(dst, src) \
    __memcpy((dst), (src), sizeof((dst)->base[0]) + 0 * sizeof((dst)->base == (src)->base))

fc_error_t __memswap(void* lhs, void* rhs, usize_t el_size);
#define memswap(lhs, rhs) \
    __memswap((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base))

fc_error_t __memmove(void* dst, void* src, usize_t el_size);
#define memmove(dst, src) \
    __memmove((dst), (src), sizeof((dst)->base[0]) + 0 * sizeof((dst)->base == (src)->base))

fc_error_t __memcmp(void* lhs, void* rhs, usize_t el_size, bool* res);
#define memcmp(lhs, rhs, res) \
    __memcmp((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base), (res))

fc_error_t __memcmp_min(void* lhs, void* rhs, usize_t el_size, bool* res);
#define memcmp_min(lhs, rhs, res) \
    __memcmp_min((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base), (res))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_MEMORY_H__ */
