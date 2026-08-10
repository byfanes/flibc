#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "error.h"
#include "require.h"

/* Note: The line parameters is set to u32 to which is enough
 * for the #line directive which uses 31 bits if it goes pass that
 * limit it will overflow but its a rare case which in normal day wont happend
 * except for unity builds in large projects
 */

/* Note: sizeof is not wrapped into parantheses because this macro expects
 * string literals and sizeof can only work with string literals if it does
 * not have parantheses */
#define ccstr_to_u8(ccstr) {(void*)(uintptr_t)(ccstr), sizeof ccstr - 1}

/* Those macros are used in most slice/da functions to improve readability */
#define ptr_meta(ptr) (ptr), sizeof((ptr)->items[0])
#define ptr_meta_check(ptr, item) (ptr), (sizeof((ptr)->items[0]) + 0 * sizeof((ptr)->items == item))
#define two_ptr_meta_check(lhs, rhs) \
     (lhs), (rhs), (sizeof((lhs)->items[0]) + 0 * sizeof((lhs)->items == (rhs)->items))

#define require_sl_type(sl) ((void)sizeof( \
require_defereable((sl)->items), \
require_integer((sl)->count), \
require_addressable((sl)->count), \
0))

/* Note: Dont use require_sl_type inside the require_sl_type_2
 * it will be bad for error messages
 */
#define require_sl_type_2(x, y) ((void)sizeof( \
require_defereable((x)->items), \
require_integer((x)->count), \
require_addressable((x)->count), \
require_defereable((y)->items), \
require_integer((y)->count), \
require_addressable((y)->count), \
require_same_ptr((x)->items, (y)->items), \
0))

#define can_be_slice(type, name) \
    typedef struct {             \
        type * const items;      \
        const usz count;         \
    } name

can_be_slice(u8, sl_u8_t);
can_be_slice(u16, sl_u16_t);
can_be_slice(u32, sl_u32_t);
can_be_slice(u64, sl_u64_t);
can_be_slice(s8, sl_s8_t);
can_be_slice(s16, sl_s16_t);
can_be_slice(s32, sl_s32_t);
can_be_slice(s64, sl_s64_t);
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

error_t allocator_set_flags(allocator_t *alloc, u32 flags);
error_t allocator_init(allocator_t **set);
error_t allocator_deinit(allocator_t **set);
error_t allocator_get_from_ptr(void *ptr, allocator_t **set);

error_t slice_set(void *sl, const void *items, usz count);
error_t slice_set_cstr(void *sl, const char *str);

error_t __mem_alloc(allocator_t *alloc, void *set, usz n, const char *file_name, u32 line);
#define mem_alloc(alloc, set, n) \
(require_writable_ptr(set), __mem_alloc((alloc), (set), (n), __FILE__, __LINE__))

error_t __mem_alloc_sl(allocator_t *alloc, void *set, usz el_size, usz n, const char* file_name, u32 line);
#define mem_alloc_sl(alloc, sl, n) \
(require_sl_type(sl), __mem_alloc_sl((alloc), (sl), sizeof((sl)->items[0]), n, __FILE__, __LINE__))

error_t __mem_calloc(allocator_t *alloc, void *set, usz n, const char *file_name, u32 line);
#define mem_calloc(alloc, set, n) \
(require_writable_ptr(set), __mem_calloc((alloc), (set), (n), __FILE__, __LINE__))

error_t __mem_calloc_sl(allocator_t *alloc, void *set, usz el_size, usz n, const char *file_name, u32 line);
#define mem_calloc_sl(alloc, sl, n) \
(require_sl_type(sl), __mem_calloc_sl((alloc), (sl), sizeof((sl)->items[0]), n, __FILE__, __LINE__))

/* TODO: realloc can optimized */
error_t __mem_realloc(allocator_t *alloc, void *set, usz n, const char *file_name, u32 line);
#define mem_realloc(alloc, set, n) \
(require_writable_ptr(set), __mem_realloc((alloc), (set), (n), __FILE__, __LINE__))

error_t __mem_free_sl(void *set);
#define mem_free_sl(set) (require_sl_type(set), __mem_free((set)))

error_t __mem_free(void *set);
#define mem_free(set) (require_writable_ptr(set), __mem_free((set)))

error_t __mem_set_sl(void *dst, usz el_size, u8 c);
#define mem_set(dst, c) \
(require_sl_type(dst), __mem_set_sl((dst), sizeof((dst)->items[0]), (c)))

error_t __mem_copy_sl(void *dst, const void *src, usz el_size);
#define mem_copy(dst, src) \
(require_sl_type_2((dst), (src)), __mem_copy_sl((dst), (src), sizeof((dst)->items[0])))

error_t __mem_swap_sl(void *lhs, void *rhs, usz el_size);
#define mem_swap(lhs, rhs) \
(require_sl_type_2((lhs), (rhs)), __mem_swap_sl((lhs), (rhs), sizeof((lhs)->items[0])))

error_t __mem_move_sl(void *dst, void *src, usz el_size);
#define mem_move(dst, src) \
(require_sl_type_2((dst), (src)), __mem_move_sl((dst), (src), sizeof((dst)->items[0])))

error_t __mem_cmp_sl(void *lhs, void *rhs, usz el_size, bool *out);
#define mem_cmp(lhs, rhs, out) \
(require_sl_type_2((lhs), (rhs)), __mem_cmp_sl((lhs), (rhs), sizeof((lhs)->items[0]), out))

error_t __mem_cmp_sl_min(void *lhs, void *rhs, usz el_size, bool *out);
#define mem_cmp_min(lhs, rhs, res) \
(require_sl_type_2((lhs), (rhs)), __mem_cmp_sl_min((lhs), (rhs), sizeof((lhs)->items[0]), res))

error_t mem_set_raw(void *ptr, u8 c, usz n);
error_t mem_copy_raw(void *dst, const void *src, usz n);
error_t mem_swap_raw(void *lhs, void *rhs, usz n);
error_t mem_move_raw(void *dst, const void *src, usz n);
error_t mem_cmp_raw(const void *lhs, const void *rhs, usz n, bool *out);

error_t mem_zeroed_len(void *ptr, usz size);
#define mem_zeroed(ptr) mem_zeroed_len((ptr), sizeof(*ptr))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_MEMORY_H__ */
