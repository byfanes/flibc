#include "stdtypes.h"
#include "error.h"

struct def_slice_s {
    byte_t* base;
    const uint32_t count;
};

typedef struct def_slice_s def_slice_t;

extern void memset_sized(void* dst,uint8_t c,uint32_t size);
extern void memcpy_sized(void* dst,void* src,uint32_t size);

void* memset(void* dest, int c, uint32_t n) {
    memset_sized(dest,c,n);
    return dest;
}

void* memcpy(void* dest, const void* src, uint32_t n) {
    memcpy_sized(dest, (void*)src, n);
    return dest;
}
