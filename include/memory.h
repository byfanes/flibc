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
can_be_slice(byte_t);
typedef slice(byte_t) def_slice_t;

def_slice_t cstr_to_def(const char* cstr);

fc_error_t throw_to_heap(void* out, void* in, uint32_t el_size);
fc_error_t malloc(uint32_t n, void* set);
fc_error_t calloc(uint32_t n, void* set);
fc_error_t realloc(uint32_t n, void* set);
fc_error_t free(void* ptr);

fc_error_t memset(def_slice_t ptr, uint8_t c);
fc_error_t memswap(def_slice_t lhs, def_slice_t rhs);
fc_error_t memmove(def_slice_t dst, def_slice_t src);
fc_error_t memcpy(def_slice_t dst, def_slice_t src);
fc_error_t memcmp(def_slice_t lhs, def_slice_t rhs, bool* res);
fc_error_t memcmp_min(def_slice_t lhs, def_slice_t rhs, bool* res);

#endif /* __FLIBC_MEMORY_H__ */
