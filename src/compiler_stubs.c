#include "stdtypes.h"
#include "error.h"

struct def_slice_s {
    byte_t* base;
    const uint32_t len;
};

typedef struct def_slice_s def_slice_t;

extern fc_error_t fc_memset(def_slice_t ptr, uint8_t c);
extern fc_error_t fc_memcpy(def_slice_t dst, def_slice_t src);

void* memset(void* dest, int c, uint32_t n) {
    def_slice_t slice = { dest, n };
    fc_memset(slice, (uint8_t)c);
    return dest;
}

void* memcpy(void* dest, const void* src, uint32_t n) {
    def_slice_t dst_slice = { dest, n };
    def_slice_t src_slice = { (void*)src, n };
    fc_memcpy(dst_slice, src_slice);
    return dest;
}
