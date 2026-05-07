#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#include "error.h"
#include "stdtypes.h"

/* DA - Implementation
 * This approach uses double-pointering to store count, capacity and itesm pointer.
 * It is safe to copy but is is slower. If you want to use something faster you can use chunks(tbd)
 * One down-side of this approach is double memory look-up.
 */

#define can_be_da(type)     \
    typedef struct {        \
        const u32 count;    \
        const u32 capacity; \
        const type *items;  \
    } CONCAT(da_,type)

can_be_da(u64);
can_be_da(u32);
can_be_da(u16);
can_be_da(u8);
can_be_da(i64);
can_be_da(i32);
can_be_da(i16);
can_be_da(i8);

#define da(type) CONCAT(da_,type)*

#define da_reserve(p_da, amount) __da_reserve(p_da, amount, sizeof((*p_da)->items[0]))
fc_error_t __da_reserve(void* p_da, u32 amount, u32 n_size);

#define da_reserve_if(p_da, amount) __da_reserve(p_da, amount, sizeof((*p_da)->items[0]))
fc_error_t __da_reserve_if(void* p_da, u32 amount, u32 n_size);

fc_error_t da_truncate(void* da, u32 len);

#define da_unordered_remove(da, out, idx) \
    __da_unordered_remove(da, out, idx, sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_unordered_remove(void* da, void* out, u32 idx, u32 n_size);

#define da_swap(da, lhs, rhs) __da_swap(da, lhs, rhs, sizeof(da->items[0]))
fc_error_t __da_swap(void* da, u32 lhs, u32 rhs, u32 n_size);

#define da_insert(da, in, idx) \
     __da_insert((da), (in), (idx), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (in)))
fc_error_t __da_insert(void* da, void* in, u32 idx, u32 n_size);

#define da_remove(da, idx) __da_remove(da, idx, sizeof(*da->items))
fc_error_t __da_remove(void* da, u32 idx, u32 n_size);

#define da_pop(da, out, idx) \
     __da_pop(da, out, idx, sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop(void* da, void* out, u32 idx, u32 n_size);

#define da_pop_first(da, out) \
     __da_pop_first(da, out, sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop_first(void* da, void* out, u32 n_size);

#define da_pop_last(da, out) \
     __da_pop_last(da, out, sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop_last(void* da, void* out, u32 n_size);


#endif /* __FLIBC_DA_H__ */
