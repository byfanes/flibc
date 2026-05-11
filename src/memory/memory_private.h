#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"

typedef struct heap_header_s heap_header_t;

struct heap_header_s {
    u32 alloced;
    u32 raw_alloced;
};

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */
