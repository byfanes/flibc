#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "error.h"

#define TRACE_ARGS const char* file_name, u32 line
#define USE_TRACE_ARGS file_name, line
#define LOC_ARGS __FILE__, __LINE__

#define ccstr_to_u8(ccstr) {(void*)(uintptr_t)((ccstr)), sizeof(((ccstr))) - 1}

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

/* sl_cstr_t type is same as sl_u8_t only difference
 * is items pointer is a null-terminated C string
 *
 * sl_ccstr_t is a constant version of sl_cstr_t used
 * string initzilation
 */
struct sl_ccstr_s {
    const u8 *const items;
    const usz count;
};

typedef struct sl_ccstr_s sl_ccstr_t;
typedef sl_u8_t sl_cstr_t;

/* TODO: Right now a lot of functions dont free the memory (when they failed) which they allocated
 * and this causes some leak we should migrate to goto defer system rather than if return
 */

/* We can support up to 32 flags (its usize_t but it shrinks down to 32 bits in x86 system)
 * this value depends so to be safe we can only use maxium 32 flags
 * on allocator_t->flags size which is usize_t those flags assigned
 * via bit so we need to shift them
 */

/* TODO: We might add changable sized null segment which will align better or can be used for
 * users' requirements
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

error_t slice_set(void* sl, const void* items, usz count);
error_t slice_set_cstr(void* sl, const char* str);

error_t __mem_alloc(allocator_t* alloc, void* set, usz n, TRACE_ARGS);
#define mem_alloc(alloc, set, n) __mem_alloc((alloc), (set), (n), LOC_ARGS)

error_t __mem_alloc_sl(allocator_t* alloc, void* set, usz el_size, usz n, TRACE_ARGS);
#define mem_alloc_sl(alloc, sl, n) __mem_alloc_sl((alloc), ptr_meta(sl), n, LOC_ARGS)

error_t __mem_calloc(allocator_t* alloc, void* set, usz n, TRACE_ARGS);
#define mem_calloc(alloc, set, n) __mem_calloc((alloc), (set), (n), LOC_ARGS)

error_t __mem_calloc_sl(allocator_t* alloc, void* set, usz el_size, usz n, TRACE_ARGS);
#define mem_calloc_sl(alloc, sl, n) __mem_calloc_sl((alloc), ptr_meta(sl), n, LOC_ARGS)

/* TODO: realloc can optimized */
error_t __mem_realloc(allocator_t* alloc, void* set, usz n, TRACE_ARGS);
#define mem_realloc(alloc, set, n) __mem_realloc((alloc), (set), (n), LOC_ARGS)

error_t mem_free(void* set);

error_t __mem_set_sl(void* dst, usz el_size, u8 c);
#define mem_set(dst, c) __mem_set_sl(ptr_meta((dst)), (c))

error_t __mem_cpy_sl(void* dst, void* src, usz el_size);
#define mem_cpy(dst, src) __mem_cpy_sl(two_ptr_meta_check((dst), (src)))

error_t __mem_swap_sl(void* lhs, void* rhs, usz el_size);
#define mem_swap(lhs, rhs) __mem_swap_sl(two_ptr_meta_check((lhs), (rhs)))

error_t __mem_move_sl(void* dst, void* src, usz el_size);
#define mem_move(dst, src) __mem_move_sl(two_ptr_meta_check((dst), (src)))

error_t __mem_cmp_sl(void* lhs, void* rhs, usz el_size, bool* out);
#define mem_cmp(lhs, rhs, res) __mem_cmp_sl(two_ptr_meta_check((lhs), (rhs)), (res))

error_t __mem_cmp_sl_min(void* lhs, void* rhs, usz el_size, bool* out);
#define mem_cmp_min(lhs, rhs, res)  __mem_cmp_sl_min(two_ptr_meta_check((lhs), (rhs)), (res))

error_t mem_set_raw(void* ptr, u8 c, usz n);
error_t mem_cpy_raw(void* dst, const void* src, usz n);
error_t mem_swap_raw(void* lhs, void* rhs, usz n);
error_t mem_move_raw(void* dst, const void* src, usz n);
error_t mem_cmp_raw(const void* lhs, const void* rhs, usz n, bool* out);

error_t mem_zeroed_len(void* ptr, usz size);
#define mem_zeroed(ptr) mem_zeroed_len((ptr), sizeof(*ptr))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_MEMORY_H__ */
