#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#include "stdtypes.h"
#include "error.h"
#include "features.h"

#define slice(type) CONCAT(slice_,type)

#define can_be_slice(type)  \
    typedef struct {        \
        type *base;         \
        const uint32_t count; \
    } slice(type)

can_be_slice(uint64_t);
can_be_slice(uint32_t);
can_be_slice(uint16_t);
can_be_slice(uint8_t);
can_be_slice(int64_t);
can_be_slice(int32_t);
can_be_slice(int16_t);
can_be_slice(int8_t);
can_be_slice(char);
typedef slice(char) slice_t;
can_be_slice(slice_t);

slice_t cstr_to_def(const char* cstr);

fc_error_t throw_to_heap(void* out, void* in, uint32_t el_size);
fc_error_t malloc(uint32_t n, void* set);
fc_error_t calloc(uint32_t n, void* set);
fc_error_t realloc(uint32_t n, void* set);
fc_error_t free(void* ptr);

fc_error_t memset(slice_t ptr, uint8_t c);
fc_error_t memswap(slice_t lhs, slice_t rhs);
fc_error_t memmove(slice_t dst, slice_t src);
fc_error_t memcpy(slice_t dst, slice_t src);
fc_error_t memcmp(slice_t lhs, slice_t rhs, bool* res);
fc_error_t memcmp_min(slice_t lhs, slice_t rhs, bool* res);

#endif /* __FLIBC_MEMORY_H__ */
