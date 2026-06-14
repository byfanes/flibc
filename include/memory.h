#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "error.h"

#define TRACE_ARGS const char* file_name, u32 line
#define USE_TRACE_ARGS file_name, line
#define LOC_ARGS __FILE__, __LINE__

#define ccstr_to_u8(ccstr)  {(u8*)((ccstr)), sizeof(((ccstr))) - 1}

/* Those macros are used in most slice/da functions to improve readability */
#define ptr_meta(ptr) (ptr), sizeof((ptr)->items[0])
#define ptr_meta_check(ptr, item) (ptr), (sizeof((ptr)->items[0]) + 0 * sizeof((ptr)->items == item))
#define two_ptr_meta_check(lhs, rhs) \
     (lhs), (rhs), (sizeof((lhs)->items[0]) + 0 * sizeof((lhs)->items == (rhs)->items))

#define can_be_slice(type, name) \
    typedef struct {             \
        type * const items;      \
        const usz count;         \
    } name

can_be_slice(u8, sl_u8_t);
can_be_slice(u16, sl_u16_t);
can_be_slice(u32, sl_u32_t);
can_be_slice(u64, sl_u64_t);
can_be_slice(i8, sl_i8_t);
can_be_slice(i16, sl_i16_t);
can_be_slice(i32, sl_i32_t);
can_be_slice(i64, sl_i64_t);
can_be_slice(ssz, sl_ssz_t);
can_be_slice(usz, sl_usz_t);

/* This type is same as sl_u8_t only difference
 * is items pointer is a null-terminated C string
 */
typedef sl_u8_t sl_cstr_t;

/* TODO: Right now a lot of functions dont free the memory (when they failed) which they allocated
 * and this causes some leak we should migrate to goto defer system rather than if return
 */

/* We can support up to 32 flags (its usize_t but it shrinks down to 32 bits in x86 system)
 * this value depends so to be safe we can only use maxium 32 flags
 * on allocator_t->flags size which is usize_t those flags assigned
 * via bit so we need to shift them
 */

/* TODO: We can add skip mutex flags and make the allocator little bit faster and
 * the usage will be for single threaded
 */
enum allocator_flags_e {
    allocator_dont_check_leaks = (1 << 0)
};

typedef struct allocator_s allocator_t;
typedef enum allocator_flags_e allocator_flags_t;

error_t allocator_set_flags(allocator_t* alloc, u32 flags);
error_t allocator_init(allocator_t** set);
error_t allocator_deinit(allocator_t** set);
error_t allocator_get_from_ptr(void* ptr, allocator_t** set);

sl_u8_t cstr_to_u8sl(const char* cstr);
error_t set_slice(const void* sl, const void* items, usz count);
error_t set_slice_cstr(const void* sl, const char* str);

error_t __malloc(allocator_t* alloc, usz n, void* set, TRACE_ARGS);
#define malloc(alloc, n, set) __malloc(alloc, n, set, LOC_ARGS)

error_t __calloc(allocator_t* alloc, usz n, void* set, TRACE_ARGS);
#define calloc(alloc, n, set) __calloc(alloc, n, set, LOC_ARGS)

/* TODO: realloc can optimized */
error_t __realloc(allocator_t* alloc, usz n, void* set, TRACE_ARGS);
#define realloc(alloc, n, set) __realloc(alloc, n, set, LOC_ARGS)

error_t free(void* set);

error_t __memset(void* dst, usz el_size, u8 c);
#define memset(dst, c) __memset(ptr_meta((dst)), (c))

error_t __memcpy(void* dst, void* src, usz el_size);
#define memcpy(dst, src) __memcpy(two_ptr_meta_check((dst), (src)))

error_t __memswap(void* lhs, void* rhs, usz el_size);
#define memswap(lhs, rhs) __memswap(two_ptr_meta_check((lhs), (rhs)))

error_t __memmove(void* dst, void* src, usz el_size);
#define memmove(dst, src) __memmove(two_ptr_meta_check((dst), (src)))

error_t __memcmp(void* lhs, void* rhs, usz el_size, bool* out);
#define memcmp(lhs, rhs, res) __memcmp(two_ptr_meta_check((lhs), (rhs)), (res))

error_t __memcmp_min(void* lhs, void* rhs, usz el_size, bool* out);
#define memcmp_min(lhs, rhs, res)  __memcmp_min(two_ptr_meta_check((lhs), (rhs)), (res))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_MEMORY_H__ */
