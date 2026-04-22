#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fc_calloc
(uint32_t size, void* set)
{
    heap_header_t header = {0}, *base = 0;
    byte_t *ptr = 0;
    uint32_t i = 0;
    if(!size) { return fce_mem_malloc_zero; }
    if(!set) { return fce_mem_malloc_nullptr; }
    
    header.alloced = size;
    size += sizeof(header);
    size = (size + 7) & (uint32_t)(~7);
    header.raw_alloced = size;

    base = (heap_header_t*)(uintptr_t) syscall_6(syscall_mmap, 0, size, (PROT_READ|PROT_WRITE),
        (MAP_PRIVATE|MAP_ANONYMOUS), (arch_t)(-1), 0);

    if(base == MMAP_FAILED) { return fce_mem_malloc_mmap_failed; }
    *base = header;
    ptr = (void*)base;
    base++;
    memcpy_ptr(set, &base);
    for(i = 0; i < size; ++i) { *(ptr++) = 0; }
    return fce_success;
}
