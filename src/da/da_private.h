#ifndef __FLIBC_DA_PRIVATE_H__
#define __FLIBC_DA_PRIVATE_H__

#include "da.h"
#include "../memory/memory_private.h"

typedef struct {
    uint32_t count;
    uint32_t capacity;
    char* items;
} def_da_t;

#endif /* __FLIBC_DA_PRIVATE_H__ */
