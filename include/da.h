#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "stdtypes.h"
#include "memory.h"

/* DA - Implementation
 * This is implementation uses struct which stored in stack so its faster to fetch count and capacity but
 * IT IS NOT SAFE FOR COPYING instead use pointers to dedicated struct
 * which costs less bytes to pass as an argument
 */

#define can_be_da(type, name)   \
    typedef struct {            \
        type * const items;     \
        const usize_t count;    \
        const usize_t capacity; \
    } name

can_be_da(u8, da_u8_t);
can_be_da(u16, da_u16_t);
can_be_da(u32, da_u32_t);
can_be_da(u64, da_u64_t);
can_be_da(i8, da_i8_t);
can_be_da(i16, da_i16_t);
can_be_da(i32, da_i32_t);
can_be_da(i64, da_i64);
can_be_da(ssize_t, da_ssize_t);
can_be_da(usize_t, da_usize_t);

typedef usize_t idx_t;
typedef usize_t elsize_t;
typedef usize_t count_t;

/* Those ones dont need any 'el_size' any work
 * on the struct which is same for any da type
 */
error_t da_deinit(void* da);
error_t da_truncate(void* da, usize_t len);
error_t da_clear(void* da);

error_t __da_add_shadow_null_segment(void* da, elsize_t el_size);
#define da_add_shadow_null_segment(da) __da_add_shadow_null_segment(ptr_meta((da)))

error_t __da_init(allocator_t* alloc, void* da, elsize_t el_size, count_t amount);
#define da_init(allocator, da, amount) __da_init((allocator), ptr_meta((da)), (amount))

error_t __da_grow(void* da, elsize_t el_size, count_t amount);
#define da_grow(da, amount) __da_grow(ptr_meta((da)), (amount))

error_t __da_grow_if(void* da, elsize_t el_size, count_t amount);
#define da_grow_if(da, amount) __da_grow_if(ptr_meta((da)), (amount))

error_t __da_unordered_remove(void* da, elsize_t el_size, idx_t idx);
#define da_unordered_remove(da, idx)  __da_unordered_remove(ptr_meta((da)), (idx))

error_t __da_swap(void* da, elsize_t el_size, idx_t lhs, idx_t rhs);
#define da_swap(da, lhs, rhs) __da_swap(ptr_meta((da)), (lhs), (rhs))

error_t __da_push(void* da, elsize_t el_size, void* item);
#define da_push(da, item) __da_push(ptr_meta_check((da), item), (item))

error_t __da_push_sl(void* da, elsize_t el_size, void* sl);
#define da_push_sl(da, sl) __da_push_sl(ptr_meta_check((da), (sl)->items), (sl))

error_t __da_insert(void* da, elsize_t el_size, void* in, idx_t idx);
#define da_insert(da, in, idx) __da_insert(ptr_meta_check((da), (in)), (in), (idx))

error_t __da_remove(void* da, elsize_t el_size, idx_t idx);
#define da_remove(da, idx) __da_remove(ptr_meta((da)), (idx))

error_t __da_pop(void* da, elsize_t el_size, void* out, idx_t idx);
#define da_pop(da, out, idx) __da_pop(ptr_meta_check((da), (out)), (out), (idx))

error_t __da_pop_first(void* da, elsize_t el_size, void* out);
#define da_pop_first(da, out) __da_pop_first(ptr_meta_check((da), (out)), (out))

error_t __da_pop_last(void* da, elsize_t el_size, void* out);
#define da_pop_last(da, out) __da_pop_last(ptr_meta_check((da), (out)), (out))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_DA_H__ */
