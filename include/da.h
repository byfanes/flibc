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

#define da(type) da_ ## type

#define can_be_da(type)         \
    typedef struct {            \
        type * const items;     \
        const usize_t count;    \
        const usize_t capacity; \
    } da_ ## type

can_be_da(u8);
can_be_da(u16);
can_be_da(u32);
can_be_da(u64);
can_be_da(i8);
can_be_da(i16);
can_be_da(i32);
can_be_da(i64);
can_be_da(ssize_t);
can_be_da(usize_t);

error_t __da_add_shadow_null_segment(void* da, usize_t el_size);
#define da_add_shadow_null_segment(da) __da_add_shadow_null_segment((da), sizeof((da)->items[0]))

error_t da_deinit(void* da);
error_t __da_init(allocator_t* alloc, void* da, usize_t amount, usize_t el_size);
#define da_init(allocator, da, amount) __da_init((allocator), (da), (amount), sizeof(((da))->items[0]))

error_t __da_grow(void* da, usize_t amount, usize_t el_size);
#define da_grow(da, amount) __da_grow((da), (amount), sizeof((da)->items[0]))

error_t __da_grow_if(void* da, usize_t amount, usize_t el_size);
#define da_grow_if(da, amount) __da_grow_if((da), (amount), sizeof((da)->items[0]))

error_t da_truncate(void* da, usize_t len);

error_t da_clear(void* da);

error_t __da_unordered_remove(void* da, usize_t idx, usize_t el_size);
#define da_unordered_remove(da, idx)  __da_unordered_remove((da), (idx), sizeof((da)->items[0])))

error_t __da_swap(void* da, usize_t lhs, usize_t rhs, usize_t el_size);
#define da_swap(da, lhs, rhs) __da_swap((da), (lhs), (rhs), sizeof((da)->items[0]))

error_t __da_push(void* da, void* item, usize_t el_size);
#define da_push(da, item) __da_push((da), (item), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (item)))

error_t __da_push_sl(void* da, void* sl, usize_t el_size);
#define da_push_sl(da, sl) \
    __da_push_sl((da), (sl), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (sl)->base))

error_t __da_insert(void* da, void* in, usize_t idx, usize_t el_size);
#define da_insert(da, in, idx) \
     __da_insert((da), (in), (idx), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (in)))

error_t __da_remove(void* da, usize_t idx, usize_t el_size);
#define da_remove(da, idx) __da_remove((da), (idx), sizeof((da)->items[0]))

error_t __da_pop(void* da, void* out, usize_t idx, usize_t el_size);
#define da_pop(da, out, idx) \
     __da_pop((da), (out), (idx), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))

error_t __da_pop_first(void* da, void* out, usize_t el_size);
#define da_pop_first(da, out) \
     __da_pop_first((da), (out), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))

error_t __da_pop_last(void* da, void* out, usize_t el_size);
#define da_pop_last(da, out) \
     __da_pop_last((da), (out), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_DA_H__ */
