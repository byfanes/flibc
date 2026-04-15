#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fc_free
(void** ptr)
{
    if(!ptr) return fce_success;
    if(!*ptr) return fce_success;
    heap_header_t* base = (void*)((heap_header_t*)*ptr - 1);
    uint32_t cap = base->raw_alloced;
    uint32_t res = (uint32_t) syscall_2(syscall_munmap,base,cap);
    if(res != 0) { return (fc_error_t)res; }
    *ptr = 0;
    return fce_success;
}
