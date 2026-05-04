#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"

struct heap_header_s {
    u32 alloced;
    u32 raw_alloced;
};

typedef struct heap_header_s heap_header_t;

#define __set_slice_count(sl, c) *(u32*)(void*)&(sl.count) = c

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */
