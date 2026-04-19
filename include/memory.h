#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#include "stdtypes.h"
#include "error.h"
#include "features.h"

struct heap_header_s {
    uint32_t alloced;
    uint32_t raw_alloced;
};

#define can_be_slice(type)  \
    typedef struct {        \
        type *base;         \
        const uint32_t count; \
    } slice_ ## type

#define slice(type) CONCAT(slice_,type)

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

struct def_slice_s {
    byte_t* base;
    const uint32_t count;
};

typedef struct heap_header_s heap_header_t;
typedef struct def_slice_s def_slice_t;

#define slice_to_def(s) ((def_slice_t) {.base = (byte_t*)s.base,.count = s.count*(sizeof(*s.base))})

#define def_compare(type)                              \
bool compare_ ## type (type *a,type *b) {              \
    def_slice_t lhs = { .base = (byte_t*)a, .count = sizeof(type) }; \
    def_slice_t rhs = { .base = (byte_t*)b, .count = sizeof(type) }; \
    bool res = false;                                  \
    fc_memcmp(lhs,rhs,&res);                           \
    return res;                                        \
}

#define add_compare_func(type,a,b) \
    bool compare_ ## type (type *a,type *b)

INTERNAL void memcpy_ptr(void* dst,void* src)
{ *(arch_t*)dst = (arch_t)src; }

INTERNAL void memset_sized(void* dst,uint8_t c,uint32_t size)
{ uint32_t i; for(i = 0;i < size;++i) { ((uint8_t*)dst)[i] = c; } }

INTERNAL void memcpy_sized(void* dst,void* src,uint32_t size)
{ uint32_t i; for(i = 0;i < size;++i) { ((uint8_t*)dst)[i] = ((uint8_t*)src)[i]; } }

void conv_heap_to_ptr(void* ptr,def_slice_t* s);

INTERNAL void set_slice
(def_slice_t* s, byte_t* base, uint32_t c)
{
    s->base = base;
    memcpy_sized((void*)&s->count,&c,sizeof(uint32_t));
}

INTERNAL void copy_slice
(def_slice_t* dst, def_slice_t* src)
{
    memcpy_sized(dst,src,sizeof(def_slice_t));
}

fc_error_t fc_malloc(uint32_t n, void* set);
fc_error_t fc_calloc(uint32_t n, void* set);
fc_error_t fc_realloc(uint32_t n, void* set);
fc_error_t fc_free(void* ptr);

fc_error_t fc_memset(def_slice_t ptr, uint8_t c);
fc_error_t fc_memswap(def_slice_t lhs, def_slice_t rhs);
fc_error_t fc_memmove(def_slice_t dst, def_slice_t src);
fc_error_t fc_memcpy(def_slice_t dst, def_slice_t src);
fc_error_t fc_memcmp(def_slice_t lhs, def_slice_t rhs, bool* res);
fc_error_t fc_memcmp_min(def_slice_t lhs, def_slice_t rhs, bool* res);

#define malloc(n,x) fc_malloc(n,x)
#define calloc(n,x) fc_calloc(n,x)
#define realloc(n,x) fc_realloc(n,x)
#define free(x) fc_free(x)
#define memset fc_memset
#define memswap fc_memswap
#define memmove fc_memmove
#define memcpy fc_memcpy
#define memcmp fc_memcmp
#define memcmp_min fc_memcmp_min

#endif /* __FLIBC_MEMORY_H__ */
