#include "stdtypes.h"

void* memset(void* dest, int c, u64 n);
void* memset
(void* dest, int c, u64 n)
{
    u64 i = 0;
    for(;i < n; ++i) {
        ((u8*)dest)[i] = (u8)c;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, u64 n);
void* memcpy
(void* dest, const void* src, u64 n)
{
    u64 i = 0;
    for(;i < n; ++i) {
        ((u8*)dest)[i] = ((u8*)src)[i];
    }
    return dest;
}
