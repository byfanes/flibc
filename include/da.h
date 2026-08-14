#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "base.h"
#include "require.h"
#include "memory.h"

/* DA - Implementation
 * This is implementation uses struct which stored in stack so its faster to fetch count and capacity but
 * IT IS NOT SAFE FOR COPYING instead use pointers to dedicated struct
 * which costs less bytes to pass as an argument
 */

#define require_da_type(da) ((void)sizeof( \
require_defereable((da)->items), \
require_integer((da)->count), \
require_integer((da)->capacity), \
require_addressable((da)->count), \
require_addressable((da)->capacity), \
require_orderable((da)->capacity, (da)->count), \
0))

#define can_be_da(type, name)   \
    typedef struct {            \
        type * const items;     \
        const usz count;        \
        const usz capacity;     \
    } name

can_be_da(u8, da_u8_t);
can_be_da(u16, da_u16_t);
can_be_da(u32, da_u32_t);
can_be_da(u64, da_u64_t);
can_be_da(s8, da_s8_t);
can_be_da(s16, da_s16_t);
can_be_da(s32, da_s32_t);
can_be_da(s64, da_s64_t);
can_be_da(ssz, da_ssz_t);
can_be_da(usz, da_usz_t);

/* Those ones dont need any 'el_size' any work
 * on the struct which is same for any da type
 */
error_t da_deinit(void* da);
error_t da_truncate(void* da, usz len);
error_t da_clear(void* da);

/*
 * da_add_shadow_null_segment() is called from places such as system_run()
 * that need to convert dynamic-array contents to a C string and therefore
 * require a trailing null terminator
 *
 * When this function is used with a slice, one possible approach is to set
 * the capacity to 0. In that case da_add_shadow_null_segment() will attempt
 * to append a trailing (usz)0 value To avoid writing past the end of the
 * buffer the slice must reserve an additional sizeof(usz) bytes
 *
 * Another option is to set capacity equal to count so that no extra element
 * can be appended However capacity is a const field and cannot be modified
 * without casting away constness which is unsafe and not intended for users
 *
 * Neither approach is completely safe so callers must ensure that the
 * underlying buffer has enough space for the shadow null segment
 */
error_t __da_add_shadow_null_segment(void* da, usz el_size);
#define da_add_shadow_null_segment(da) \
(require_da_type((da)), __da_add_shadow_null_segment((da), sizeof((da)->items[0])))

error_t __da_init(allocator_t* alloc, void* da, usz el_size, usz amount);
#define da_init(allocator, da, amount) \
(require_da_type((da)), __da_init((allocator), (da), sizeof((da)->items[0]), (amount)))

error_t __da_grow(void* da, usz el_size, usz amount);
#define da_grow(da, amount) \
(require_da_type((da)), __da_grow((da), sizeof((da)->items[0]), (amount)))

error_t __da_grow_if(void* da, usz el_size, usz amount);
#define da_grow_if(da, amount) \
(require_da_type((da)), __da_grow_if((da), sizeof((da)->items[0]), (amount)))

error_t __da_unordered_remove(void* da, usz el_size, usz idx);
#define da_unordered_remove(da, idx) \
(require_da_type((da)), __da_unordered_remove((da), sizeof((da)->items[0]), (idx)))

error_t __da_unordered_remove_on_ptr(void* da, usz el_size, void *ptr);
#define da_unordered_remove_on_ptr(da, ptr) \
(require_da_type((da)), require_same_ptr((da)->items, (ptr)), \
 __da_unordered_remove_on_ptr((da), sizeof((da)->items[0]), (ptr)))

error_t __da_swap(void* da, usz el_size, usz lhs, usz rhs);
#define da_swap(da, lhs, rhs) \
(require_da_type((da)), __da_swap((da), sizeof((da)->items[0]), (lhs), (rhs)))

error_t __da_push(void* da, usz el_size, void* item);
#define da_push(da, item) \
(require_da_type((da)), require_same_ptr((da)->items, item), \
 __da_push((da), sizeof((da)->items[0]), (item)))

error_t __da_push_sl(void *da, usz el_size, const void *sl);
#define da_push_sl(da, sl) \
(require_da_type((da)), require_sl_type((sl)), \
__da_push_sl((da), sizeof((da)->items[0]), (sl)))

error_t __da_insert(void* da, usz el_size, void* in, usz idx);
#define da_insert(da, in, idx) \
(require_da_type((da)), require_same_ptr((da)->items, in), \
 __da_insert((da), sizeof((da)->items[0]), (in), (idx)))

error_t __da_remove(void* da, usz el_size, usz idx);
#define da_remove(da, idx) \
(require_da_type((da)), __da_remove((da), sizeof((da)->items[0]), (idx)))

error_t __da_pop(void* da, usz el_size, void* out, usz idx);
#define da_pop(da, out, idx) \
(require_da_type((da)), require_same_ptr((da)->items, out), \
 __da_pop((da), sizeof((da)->items[0]), (out), (idx)))

error_t __da_pop_first(void* da, usz el_size, void* out);
#define da_pop_first(da, out) \
(require_da_type((da)), require_same_ptr((da)->items, out), \
 __da_pop_first((da), sizeof((da)->items[0]), (out), (out)))

error_t __da_pop_last(void* da, usz el_size, void* out);
#define da_pop_last(da, out) \
(require_da_type((da)), require_same_ptr((da)->items, out), \
 __da_pop_last((da), sizeof((da)->items[0]), (out)))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_DA_H__ */
