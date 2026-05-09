#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#include "error.h"
#include "stdtypes.h"
#include "features.h"

/* DA - Implementation
 * This is implementation uses struct which stored in stack so its faster to fetch count and capacity but
 * IT IS NOT SAFE FOR COPYING instead use pointers to dedicated struct
 * which costs less bytes to pass as an argument
 */

#define can_be_da(type)     \
    typedef struct {        \
        const u32 count;    \
        const u32 capacity; \
        type *items;        \
    } CONCAT(da_,type)

can_be_da(u64);
can_be_da(u32);
can_be_da(u16);
can_be_da(u8);
can_be_da(i64);
can_be_da(i32);
can_be_da(i16);
can_be_da(i8);

#define da(type) CONCAT(da_,type)

#define da_reserve(da, amount) __da_reserve((da), (amount), sizeof((da)->items[0]))
fc_error_t __da_reserve(const void* da, u32 amount, u32 el_size);

#define da_reserve_if(da, amount) __da_reserve((da), (amount), sizeof((da)->items[0]))
fc_error_t __da_reserve_if(const void* da, u32 amount, u32 el_size);

fc_error_t da_truncate(const void* da, u32 len);

#define da_unordered_remove(da, idx)  __da_unordered_remove((da), (idx), sizeof((da)->items[0])))
fc_error_t __da_unordered_remove(const void* da, u32 idx, u32 el_size);

#define da_swap(da, lhs, rhs) __da_swap((da), (lhs), (rhs), sizeof((da)->items[0]))
fc_error_t __da_swap(const void* da, u32 lhs, u32 rhs, u32 el_size);

#define da_insert(da, in, idx) \
     __da_insert((da), (in), (idx), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (in)))
fc_error_t __da_insert(const void* da, void* in, u32 idx, u32 el_size);

#define da_remove(da, idx) __da_remove((da), (idx), sizeof((da)->items[0]))
fc_error_t __da_remove(const void* da, u32 idx, u32 el_size);

#define da_pop(da, out, idx) \
     __da_pop((da), (out), (idx), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop(const void* da, void* out, u32 idx, u32 el_size);

#define da_pop_first(da, out) \
     __da_pop_first((da), (out), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop_first(const void* da, void* out, u32 el_size);

#define da_pop_last(da, out) \
     __da_pop_last((da), (out), sizeof((da)->items[0]) + 0 * sizeof((da)->items == (out)))
fc_error_t __da_pop_last(const void* da, void* out, u32 el_size);

#endif /* __FLIBC_DA_H__ */
