#include "memory.h"
#include "stdtypes.h"

void memset_sized
(void* dst,uint8_t c,uint32_t size)
{
    uint8_t* pd = dst;
    for(uint32_t i = 0;i < size;++i){
        pd[i] = c;
    }
}
