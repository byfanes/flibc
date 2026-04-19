#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fc_free
(void* ptr)
{
    heap_header_t *sptr, *base;
    uint32_t cap, res;
    if(!ptr) { return fce_success; }
    memcpy_sized(&sptr, ptr, sizeof(void*));
    if(!sptr) { return fce_success; }
    base = (sptr - 1);
    cap = base->raw_alloced;
    res = (uint32_t) syscall_2(syscall_munmap, (arch_t)base, cap);
    if(res != 0) { return (fc_error_t)res; }
    memset_sized(ptr, 0, sizeof(void*));
    return fce_success;
}
