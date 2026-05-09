#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#include "stdtypes.h"
#include "error.h"
#include "features.h"

#define slice(type) const CONCAT(slice_, type)

#define can_be_slice(type)  \
    typedef struct {        \
        type *base;         \
        u32 count; \
    } CONCAT(slice_, type)

can_be_slice(u64);
can_be_slice(u32);
can_be_slice(u16);
can_be_slice(u8);
can_be_slice(i64);
can_be_slice(i32);
can_be_slice(i16);
can_be_slice(i8);
typedef slice(u8) slice_t;
can_be_slice(slice_t);

slice_t cstr_to_def(const char* cstr);
fc_error_t set_slice(const void* sl, const void* base, u32 count);

fc_error_t throw_to_heap(void* out, void* in, u32 el_size);
fc_error_t malloc(u32 n, void* set);
fc_error_t calloc(u32 n, void* set);
fc_error_t realloc(u32 n, void* set);
fc_error_t free(void* ptr);

fc_error_t memset(slice_t ptr, u8 c);
fc_error_t memswap(slice_t lhs, slice_t rhs);
fc_error_t memmove(slice_t dst, slice_t src);
fc_error_t memcpy(slice_t dst, slice_t src);
fc_error_t memcmp(slice_t lhs, slice_t rhs, bool* res);
fc_error_t memcmp_min(slice_t lhs, slice_t rhs, bool* res);

#endif /* __FLIBC_MEMORY_H__ */
