#ifndef __FLIBC_DA_PRIVATE_H__
#define __FLIBC_DA_PRIVATE_H__

#include "da.h"
#include "../memory/memory_private.h"

/* This struct should be in same order with can_be_da
 * types and first two members of slice
 */
typedef struct def_da_s def_da_t;
struct def_da_s {
    u8* items;
    usize_t count;
    usize_t capacity;
};

#endif /* __FLIBC_DA_PRIVATE_H__ */
