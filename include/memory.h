#ifndef __FLIBC_MEMORY_H__
#define __FLIBC_MEMORY_H__

#include "stdtypes.h"
#include "error.h"

struct heap_header_s {
    uint32_t alloced;
    uint32_t raw_alloced;
};

struct ptr_header_s {
    void* base;
    uint32_t len;
};

typedef struct heap_header_s heap_header_t;
typedef struct ptr_header_s ptr_header_t;

ptr_header_t conv_heap_to_ptr(void* ptr);

fc_error_t fc_malloc(uint32_t n, void** set);
fc_error_t fc_calloc(uint32_t n, void** set);
fc_error_t fc_realloc(uint32_t n, void** set);
fc_error_t fc_free(void** ptr);

fc_error_t fc_memset(ptr_header_t ptr, uint8_t c);
fc_error_t fc_memswap(ptr_header_t lhs, ptr_header_t rhs);
fc_error_t fc_memmove(ptr_header_t dst, ptr_header_t src);
fc_error_t fc_memcpy(ptr_header_t dst, ptr_header_t src);
fc_error_t fc_memcmp(ptr_header_t lhs, ptr_header_t rhs, bool* res);
fc_error_t fc_memcmp_min(ptr_header_t lhs, ptr_header_t rhs, bool* res);

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
