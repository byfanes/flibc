#ifndef __FLIBC_DA_PRIVATE_H__
#define __FLIBC_DA_PRIVATE_H__

#include "da.h"
#include "../memory/memory_private.h"

typedef struct {
    u32 count;
    u32 capacity;
    u8* items;
} def_da_t;

#endif /* __FLIBC_DA_PRIVATE_H__ */
