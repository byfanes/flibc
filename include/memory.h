#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#include "stdtypes.h"
#include "error.h"

typedef uint8_t byte_t;

struct heap_header_s {
    uint32_t alloced;
    uint32_t raw_alloced;
};

#define can_be_slice(type)  \
    typedef struct {        \
        type *base;         \
        const uint32_t len; \
    } slice_ ## type

#define slice(type) slice_ ## type

struct def_slice_s {
    byte_t* base;
    const uint32_t len;
};

typedef struct heap_header_s heap_header_t;
typedef struct def_slice_s def_slice_t;

#define slice_to_def(s) ((def_slice_t) {.base = (byte_t*)s.base,.len = s.len*(sizeof(*s.base))})

#define def_compare(type)                              \
bool type ## _compare(type *a,type *b) {               \
    def_slice_t lhs = { .base = (byte_t*)a, .len = sizeof(type) }; \
    def_slice_t rhs = { .base = (byte_t*)b, .len = sizeof(type) }; \
    bool res = false;                                  \
    fc_memcmp(lhs,rhs,&res);                           \
    return res;                                        \
}

def_slice_t conv_heap_to_ptr(void* ptr);

fc_error_t fc_malloc(uint32_t n, void** set);
fc_error_t fc_calloc(uint32_t n, void** set);
fc_error_t fc_realloc(uint32_t n, void** set);
fc_error_t fc_free(void** ptr);

fc_error_t fc_memset(def_slice_t ptr, uint8_t c);
fc_error_t fc_memswap(def_slice_t lhs, def_slice_t rhs);
fc_error_t fc_memmove(def_slice_t dst, def_slice_t src);
fc_error_t fc_memcpy(def_slice_t dst, def_slice_t src);
fc_error_t fc_memcmp(def_slice_t lhs, def_slice_t rhs, bool* res);
fc_error_t fc_memcmp_min(def_slice_t lhs, def_slice_t rhs, bool* res);

#define malloc(n,x) fc_malloc(n,(void*)x)
#define calloc(n,x) fc_calloc(n,(void*)x)
#define realloc(n,x) fc_realloc(n,(void*)x)
#define free(x) fc_free((void*)x)
#define memset fc_memset
#define memswap fc_memswap
#define memmove fc_memmove
#define memcpy fc_memcpy
#define memcmp fc_memcmp
#define memcmp_min fc_memcmp_min

#endif /* __FLIBC_MEMORY_H__ */
