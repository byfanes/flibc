#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fc_free
(void* ptr)
{
    if(!ptr) return fce_success;
    heap_header_t* sptr = 0;
    memcpy_sized(&sptr,ptr,sizeof(void*));
    if(!sptr) return fce_success;
    heap_header_t* base = (sptr - 1);
    uint32_t cap = base->raw_alloced;
    uint32_t res = (uint32_t) syscall_2(syscall_munmap,base,cap);
    if(res != 0) { return (fc_error_t)res; }
    memset_sized(ptr,0,sizeof(void*));
    return fce_success;
}
