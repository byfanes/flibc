#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "error.h"

typedef struct allocator_s allocator_t;

#define TRACE_ARGS const char* file_name, usize_t line
#define USE_TRACE_ARGS file_name, line
#define LOC_ARGS __FILE__, __LINE__

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

/* TODO: Right now a lot of functions dont free the memory (when they failed) which they allocated
 * and this causes some leak we should migrate to goto defer system rather than if return
 */

/* We can support up to 32 flags right now this value depends
 * on allocator_t->flags size which is u32 those flags assigned
 * via bit so we need to shift them
 */
enum allocator_flags_e {
    allocator_dont_check_leaks = (1 << 0)
};

typedef enum allocator_flags_e allocator_flags_t;

error_t allocator_set_flags(allocator_t* alloc, u32 flags);
error_t allocator_init(allocator_t** set);
error_t allocator_deinit(allocator_t** set);
error_t allocator_get_from_ptr(void* ptr, allocator_t** set);

slice(u8) cstr_to_u8sl(const char* cstr);
error_t set_slice(const void* sl, const void* base, usize_t count);

error_t __malloc(allocator_t* alloc, usize_t n, void* set, TRACE_ARGS);
#define malloc(alloc, n, set) __malloc(alloc, n, set, LOC_ARGS)

error_t __calloc(allocator_t* alloc, usize_t n, void* set, TRACE_ARGS);
#define calloc(alloc, n, set) __calloc(alloc, n, set, LOC_ARGS)

/* TODO: realloc can optimized */
error_t __realloc(allocator_t* alloc, usize_t n, void* set, TRACE_ARGS);
#define realloc(alloc, n, set) __realloc(alloc, n, set, LOC_ARGS)

error_t free(void* set);

/* This is both for using typed slices and preventing mechanisim to avoid compiliers'
 * automatic memset calls because those functions collide
 */
error_t __memset(void* dst, usize_t el_size, u8 c);
#define memset(dst, c) __memset((dst), sizeof((dst)->base[0]), (c))

error_t __memcpy(void* dst, void* src, usize_t el_size);
#define memcpy(dst, src) \
    __memcpy((dst), (src), sizeof((dst)->base[0]) + 0 * sizeof((dst)->base == (src)->base))

error_t __memswap(void* lhs, void* rhs, usize_t el_size);
#define memswap(lhs, rhs) \
    __memswap((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base))

error_t __memmove(void* dst, void* src, usize_t el_size);
#define memmove(dst, src) \
    __memmove((dst), (src), sizeof((dst)->base[0]) + 0 * sizeof((dst)->base == (src)->base))

error_t __memcmp(void* lhs, void* rhs, usize_t el_size, bool* out);
#define memcmp(lhs, rhs, res) \
    __memcmp((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base), (res))

error_t __memcmp_min(void* lhs, void* rhs, usize_t el_size, bool* out);
#define memcmp_min(lhs, rhs, res) \
    __memcmp_min((lhs), (rhs), sizeof((lhs)->base[0]) + 0 * sizeof((lhs)->base == (rhs)->base), (res))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_MEMORY_H__ */
