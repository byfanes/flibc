#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"

struct heap_header_s {
    uint32_t alloced;
    uint32_t raw_alloced;
};

typedef struct heap_header_s heap_header_t;

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */
