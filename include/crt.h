#ifndef __FLIBC_CRT_H__
#define __FLIBC_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdlib.h"
#include "stdio.h"
#include "memory.h"

can_be_slice(slice_u8);

typedef struct std_s std_t;
struct std_s {
    allocator_t* alloc;
    stdio_t io;
    slice(u8) exe;
    slice(slice_u8) args;
};

extern int main(std_t);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_CRT_H__ */
