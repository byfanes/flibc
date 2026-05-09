#include "stdtypes.h"

void* memset(void* dest, int c, u32 n);
void* memset
(void* dest, int c, u32 n)
{
    u32 i = 0;
    for(;i < n; ++i) {
        ((u8*)dest)[i] = (u8)c;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, uint32_t n);
void* memcpy
(void* dest, const void* src, uint32_t n)
{
    u32 i = 0;
    for(;i < n; ++i) {
        ((u8*)dest)[i] = ((u8*)src)[i];
    }
    return dest;
}
