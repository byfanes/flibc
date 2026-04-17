#include "memory.h"
#include "stdtypes.h"

void memcpy_sized
(void* dst,void* src,uint32_t size)
{
    uint8_t* pd = dst;
    uint8_t* ps = src;
    for(uint32_t i = 0;i < size;++i){
        pd[i] = ps[i];
    }
}
